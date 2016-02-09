#include "Map/Map.h"

uint32_t XML_depth     = 0;
uint32_t XML_NthColumn = 0;

Map::Map(Updatable* parent, File& file) : Updatable(parent), GroupTransformable(), m_parser(XML_ParserCreate(NULL)), m_nbCasesX(0), m_nbCasesY(0), m_caseSizeX(0), m_caseSizeY(0)
{
	//Reinit global variables
	XML_depth = XML_NthColumn = 0;

	//Init XML parser
	XML_SetUserData(m_parser, (void*)this);
	XML_SetElementHandler(m_parser, &startElement, &endElement);

	//Then parse the file
	std::string xmlCode;
	char* line;
	while((line = file.readLine()) != NULL)
	{
		if(line == NULL)
			break;
		xmlCode.append(line);
		free(line);
	}
	if(XML_Parse(m_parser, xmlCode.c_str(), xmlCode.size(), 1) == 0)
		LOG_ERROR("Error while parsing the file. Abort");
	XML_ParserFree(m_parser);
}

void startElement(void* map, const char* name, const char** attrs)
{
	Map* self = (Map*)map;
	//Get Window datas
	if(!strcmp(name, "Window"))
	{
		uint32_t i;
		for(i=0; attrs[i]; i+=2)
		{
			if(!strcmp(attrs[i], "numberCases"))
				getXYFromStr(attrs[i+1], &self->nbCasesX, &self->nbCasesY);
			else if(!strcmp(attrs[i], "tileSize"))
				getXYFromStr(attrs[i+1], &self->caseSizeX, &self->caseSizeY);
		}
	}

	//Set the correct start function following the section (Files for Files, etc.)
	else if(!strcmp(name, "Files"))
		XML_SetElementHandler(self->m_parser, startElementFiles, endElement);
	else if(!strcmp(name, "Objects"))
		XML_SetElementHandler(self->m_parser, startElementObjects, endElement);
	else if(!strcmp(name, "Traces"))
		XML_SetElementHandler(self->m_parser, startElementTraces, endElement);
	XML_depth++;
}

void startElementFiles(void *data, const char* name, const char** attrs)
{
	uint32_t i;
	Map* map = (Map*)data;

	if(XML_depth == 2)
	{
		Texture* texture= NULL; //The image file

		//If the section if for Static files
		if(!strcmp(name, "Static"))
		{
			//Then get the information about it
			uint32_t spacingX, spacingY, tileSizeX, tileSizeY;
			for(i=0; attrs[i]; i+=2)
			{
				//The path
				if(!strcmp(attrs[i], "file"))
				{
					char p[60];
					sprintf(p, "Resources/%s", attrs[i+1]);
					texture = Texture::loadAndroidFile(p);
				}

				//The spacing
                else if(!strcmp(attrs[i], "spacing"))
                    getXYFromStr(attrs[i+1], &(spacingX), &(spacingY));

				//And tile size
                else if(!strcmp(attrs[i], "tileSize"))
                    getXYFromStr(attrs[i+1], &(tileSizeX), &(tileSizeY));
			}
			//Then create it and store it
			StaticFile* sf = new StaticFile(texture, tileSizeX, tileSizeY, spacingX, spacingY);
			map->m_staticTraces.push_back(sf);
		}

		//Or if the file is a Dynamic file
        else if(!strcmp(name, "Dynamic"))
        {
			for(i=0; attrs[i]; i+=2)
			{
				//Get the path of the file
				if(!strcmp(attrs[i], "file"))
				{
					char p[60];
					sprintf(p, "Resources/%s", attrs[i+1]);
					texture = Texture::loadAndroidFile(p);
				}
			}

			//Then create it and store it
			DynamicFile* df = new DynamicFile(texture);
			map->m_dynamicFile.push_back(df);
        }

		//If a file isn't created
		if(file==NULL)
		{
			LOG_ERROR("Exit because can't load a file \n");
			return;
		}
		//Store this file (the image one)
		map->m_texture.push_back(texture);
	}

	else if(XML_depth == 3)
	{
		if(map->texture.size() == map->staticFiles.size()) //Because we load static files before dynamic files, if the len is equal, then the last file was static
		{
			//Get the last static file
			StaticFile* sf = map->staticFiles[map->staticFiles.size()-1];
			const char* name;
			const char* type;
			for(uint32_t i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "name"))
					name = attrs[i+1];
				else if(!strcmp(attrs[i], "type"))
					type = attrs[i+1];
			}
			StaticDatas* sd = map->getStaticDatas(name, type);
			sf->addStaticDatas(sd);
		}

		//If we aren't dealing with static files, then we are with dynamic files
		else
		{
			DynamicFile* df = map->dynamicFiles[map->dynamicFiles.size()-1];

			//Creating a dynamic entity which will contain all the subrect for this animation (dynamic == animation), and the create function for this tile
			const char* name;
			const char* type;
			for(uint32_t i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "name"))
					name = attrs[i+1];
				else if(!strcmp(attrs[i], "type"))
					type = attrs[i+1];
			}
			DynamicEntity* de = map->getDynamicDatas(name, type);
		}
	}

	//This part is only for dynamic files, wich contain position and size for dynamic entities
	else if(XML_depth == 4)
	{
		//Get the last dynamic files
		DynamicFile* df = (DynamicFile*)List_getData(map->dynamicFiles, List_getLen(map->dynamicFiles)-1);
		DynamicEntity* de = (DynamicEntity*)ResourcesManager_getDataByID(df->dynamicEntities, ResourcesManager_getLen(df->dynamicEntities)-1);

		//Then create the rect for this animation
		SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
		uint32_t i;
		for(i=0; attrs[i]; i+=2)
		{
			if(!strcmp(attrs[i], "pos"))
				getXYFromStr(attrs[i+1], &(rect->x), &(rect->y));

			else if(!strcmp(attrs[i], "size"))
				getXYFromStr(attrs[i+1], &(rect->w), &(rect->h));
		}
		List_addData(de->tileRects, (void*)rect);
	}
	XML_depth++; //We see to the next XML depth
}

void endElement(void *data, const char* name)
{
	XML_depth--;
	if(XML_depth == 1)
		XML_SetElementHandler(((Map*)data)->m_parser, startElement, endElement);
}

void getXYFromStr(const char* str, uint32_t* x, uint32_t* y)
{
    uint32_t i;
    for(i=0; str[i] != 'x' && str[i] != 'X' && str[i] != '\0'; i++);

    if(str[i] != '\0')
    {
        *x = atoi(str);
        *y = atoi(&(str[i+1]));
    }
}
