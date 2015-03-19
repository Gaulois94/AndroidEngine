#include "MaterialWrapper.h"

MaterialWrapper::MaterialWrapper(File& file)
{
	float ambientColor[3];
	float diffuseColor[3];
	float specularColor[3];
	std::string name;
	float transparent       = 0.0f;
	float specularHighlight = 0.0f;
	bool initCurrentMaterial = false;

	while(1)
	{
		char* buffer = file.readLine();
		std::string line;

		if(buffer != NULL)
		{
			line = std::string(buffer);
			unsigned int loc;
			while((loc = line.find("  ")) != std::string::npos)
				line.replace(loc,2," ");
			if(std::regex_match(line, std::regex("^ *#$")))
				free(buffer);
			continue;
		}

		if(buffer == NULL || std::regex_match(line, std::regex("^o ")))
		{
			if(initCurrentMaterial)
			{
				Color dC = Color(diffuseColor[0], diffuseColor[1], diffuseColor[2]);
				Color sC = Color(specularColor[0], specularColor[1], specularColor[2]);
				m_mtl.add(name, new ObjMaterial(dC, sC, NULL, true, false, true, true, specularHighlight, transparent));
			}

			if(buffer == NULL)
				break;

			name                = split(line, ' ')[1];
			transparent         = 0.0f;
			specularHighlight   = 0.0f;
			initCurrentMaterial = true;
		}

		else if(std::regex_match(line, std::regex("^Ns ")))
		{
			std::vector<std::string> specularHighlightValue = split(line, ' ');
			specularHighlight = atof(specularHighlightValue[1].c_str());
		}

		else if(std::regex_match(line, std::regex("^Ka ")))
		{
			std::vector<std::string> ambientValue = split(line, ' ');
			for(int i=1; i < 4; i++)
				ambientColor[i-1] = atof(ambientValue[i].c_str());
		}

		else if(std::regex_match(line, std::regex("^Kd ")))
		{
			std::vector<std::string> diffuseValue = split(line, ' ');
			for(int i=1; i < 4; i++)
				diffuseColor[i-1] = atof(diffuseValue[i].c_str());
		}

		else if(std::regex_match(line, std::regex("^Ks ")))
		{
			std::vector<std::string> specularValue = split(line, ' ');
			for(int i=1; i < 4; i++)
				specularColor[i-1] = atof(specularValue[i].c_str());
		}

		else if(std::regex_match(line, std::regex("^d ")))
			transparent = atof(split(line, ' ')[1].c_str());

		free(buffer);
	}
}

MaterialWrapper::~MaterialWrapper()
{

}

ObjMaterial* MaterialWrapper::getMaterial(const std::string& id)
{
	return m_mtl.get(id);
}
