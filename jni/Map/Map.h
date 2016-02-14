#ifndef  MAP_INC
#define  MAP_INC

#include "Updatable.h"
#include "Map/MapFiles.h"
#include "Map/Datas/StaticDatas.h"
#include "Map/Datas/ObjectDatas.h"
#include "Map/Datas/DynamicDatas.h"
#include "expat.h"

/** \class Map 
 * \brief basic class for decompiling Map files
 * The xml format file is like this :
 * <map>
 *	<Window numberCase="axb" tileSize="axb" title="title"/>
 *
 *	<Files>
 *	 <Static file="path" spacing="axb" tileSize="axb">
 *	  <StaticTile name="name" type="type"/>
 *	 </Static>
 *	 <Dynamic file="path"> //Used for animation
 *	  <DynamicEntity name="name">
 *	   <DynamicTile name="name" pos="axb" size="axb" type="type"/>
 *	  </DynamicEntity>
 *	 </Dynamic>
 *	</Files>
 *
 *  <Objects name="name" numberCases = "axb" tileSize="axb" type="type">
 *   <ObjectsColumn fileID="fileID" tileID="tileID"/>
 *  </Objects>
 *
 *  <Traces>
 *   <StaticTrace name="name" shift="axb" size="axb">
 *    <Column fileID="fileID" tileID="tileID" objectID="objectID"/>
 *   </StaticTraces>
 *   <DynamicTrace name="name">
 *    <DynamicTile animName="name" animeTime="time" fileID="fileID" origin="axb" position="axb" tileID="tileID"/>
 *    <StaticTile fileID="fileID" tileID="tileID" position="axb"/>
 *   </DynamicTrace>
 *  </Traces>
 * </map> 
 *
 * each fileID et tileID are represented in csv format for StaticTrace. It earns us some time process and file spaces. This couple tells us which tile it is (which file and which tile in this file)*/
class Map : public Updatable, GroupTransformable
{
	public:
		/** \brief Constructor of the class Map. It creates and parse a XML file. The default position of the Map is (1.0, 1.0) with the size (nbCaseX * tileSizeX, nbCaseY * tileSizeY). Remember to scale the Map after its creation
		 * \param parent the parent of the Map
		 * \param file the XML file*/
		Map(Updatable* parent, File& file);

		/** \brief destructor of the class Map. It will destroy each traces, each texture used in this map*/
		~Map();

		void onUpdate(Render& render);

		/** \brief get the pointer function to create a static tile from name and type. This function is aimed to be overwrited.
		 * \param name the name of the tile contained on the xml file
		 * \param type the type of the tile contained on the xml file
		 * \return a pointer function to create static tiles. NULL if not correct*/
		virtual createStaticTilePtr getStaticTileFunction(const char* name, const char* type)const; 

		/** \brief Get a pointer to a Material for a specific static tile (following its name and its type). This function is aimed to be overwrited
		 * \param name the name of the tile contained on the xml file
		 * \param type the type of the tile contained on the xml file
		 * \return a pointer to a Material. NULL if not correct*/
		virtual Material*           getStaticTileMaterial(const char* name, const char* type)const;

		/** \brief get the pointer function to create a dynamic tile from name and type. This function is aimed to be overwrited.
		 * \param name the name of the tile contained on the xml file
		 * \param type the type of the tile contained on the xml file
		 * \return a pointer function to create dynamic tiles. NULL if not correct*/
		virtual createDynamicTilePtr getDynamicTileFunction(const char* name, const char* type) const; 

		/** \brief Get a pointer to a Material for a specific dynamic tile (following its name and its type). This function is aimed to be overwrited
		 * \param name the name of the tile contained on the xml file
		 * \param type the type of the tile contained on the xml file
		 * \return a pointer to a Material. NULL if not correct*/
		virtual Material*           getDynamicTileMaterial(const char* name, const char* type) const;

		/** \brief set the pointer function for this ObjectDatas following its name and its type
		 * \param name the name of the tile contained on the xml file
		 * \param type the type of the tile contained on the xml file
		 * \return a pointer function to create object. NULL if not correct*/
		virtual createObjectPtr getObjectFunction(const char* name, const char* type) const;

		/** \brief get the tile on the coord x, y in pixels coords (and not OpenGL)
		 * \param x the x component
		 * \param y the y component
		 * \return the Tile at this position. NULL if nothing*/
		Tile* getTile(uint32_t x, uint32_t y);

		/** \brief get the tile on the coord x, y in pixels coords in a specific trace
		 * \param x the x component
		 * \param y the y component
		 * \param traceName the trace name. We will check this position on this trace only.
		 * \return the Tile at this position. NULL if nothing (trace not found or position not found)*/
		Tile* getTile(uint32_t x, uint32_t y, const char* traceName);

		/** \brief tell if the position x, y is outside the Map. The Map Rect is (0, 0, nbCaseX*tileSizeX, nbCaseY*tileSizeY)
		 * \param x the x coords
		 * \param y the y coords
		 * \return tells if the coords are outsize the Map or not.*/
		bool isOutside(uint32_t x, uint32_t y) const;

	//Don't modifie these variables. They are public because of the parser functions that need to modify them directly
	public:
		//The Parser
		XML_Parser m_parser;
		//Files
		std::vector<Texture*>      m_textures;
		std::vector<StaticFile*>   m_staticFiles;
		std::vector<DynamicFile*>  m_dynamicFiles;

		//Objects
		std::vector<ObjectDatas*>  m_objects;

		//Traces
		std::vector<StaticTrace*>  m_staticTraces;
		std::vector<DynamicTrace*> m_dynamicTraces;

		//Map datas
		uint32_t m_nbCasesX;
		uint32_t m_nbCasesY;
		uint32_t m_caseSizeX;
		uint32_t m_caseSizeY;
};

/** \brief Default fonction called on a new element of the XML. It will set the correct startElement function following the section name (Files, Objects or Traces)
 * \param name the name of the section
 * \param attrs the attributes of the section
 *  */
void startElement(void* map, const char* name, const char** attrs);

/** \brief Parse the section Files of the XML
 * \param name the name of the section
 * \param attrs the attributes of the section
 *  */
void startElementFiles(void* map, const char* name, const char** attrs);

/** \brief Parse the section Objects of the XML
 * \param name the name of the section
 * \param attrs the attributes of the section
 *  */
void startElementObjects(void* map, const char* name, const char** attrs);

/** \brief Parse the section Trace of the XML
 * \param name the name of the section
 * \param attrs the attributes of the section
 *  */
void startElementTraces(void* map, const char* name, const char** attrs);

/** \brief Function called after that the section is readed
 * \param name the name of the section
 * \param attrs the attributes of the section*/
void endElement(void* map, const char* name);

/** \brief extract x and y from a str like xxy where the second x is a cross
 * \param str the str
 * \param x pointer to store the x coordinate
 * \param y pointer to store the y coordinate
 *  */
void getXYFromStr(const char* str, uint32_t* x, uint32_t* y);

extern uint32_t XML_depth; /** <!XML depth on the current XML file*/
extern uint32_t XML_NthColumn; /** <!XML column number for static files on the current XML file*/

#endif
