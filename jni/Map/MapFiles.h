#ifndef  MAPFILES_INC
#define  MAPFILES_INC

#include "Map/Datas/StaticDatas.h"
#include "Map/Datas/DynamicDatas.h"
#include "Map/Tiles/DefaultTile.h"

/** \class StaticFile
 * \brief contain information about a static file.*/
class StaticFile
{
	public:
		/** \brief Default constructor for a StaticFile
		 * \param texture the Texture of the file
		 * \param spacX the spacing in X between each tile
		 * \param spacY the spacing in Y between each tile
		 * \param sizeX the width of tiles
		 * \param sizeY the height of tiles*/
		StaticFile(Texture* texture, uint32_t spacX, uint32_t spacY, uint32_t sizeX, uint32_t sizeY);

		/** \brief Default destructor. Destroy each TileDatas*/
		~StaticFile();

		/** \brief Add a TileDatas on this file. Has to be allocated dynamically, and doesn't have to be destroy by the user (the object will do it itself)
		 * \param tileDatas the TileDatas to add*/
		void   addTileDatas(TileDatas* tileDatas);

		/** \brief Create a tile placed at the place tileID. If you want to create a default tile, use def=true
		 * \param tileID the position of the tile on the file.
		 * \param def put def to true if you want to create a DefaultTile
		 * \return the Tile created. NULL if can't be created*/
		Tile*  createTile(uint32_t tileID, bool def);
	private:
		Texture* m_texture;
		std::vector<TileDatas*> m_tileDatas;
		uint32_t m_spacingX;
		uint32_t m_spacingY;
		uint32_t m_tileSizeX;
		uint32_t m_tileSizeY;
};

/** \class DynamicFile*/
class DynamicFile
{
	public:
		/** \brief Constructor for DynamicFile
		 * \param texture the texture of the file*/
		DynamicFile(Texture* texture);

		/** \brief Default Destructor. Will destroy each entity*/
		~DynamicFile();

		/** \brief add a DynamicEntity to this file.
		 * \param key the name of the entity
		 * \param DynamicEntity the DynamicEntity itself*/
		void addDynamicEntity(const std::string& key, DynamicEntity* entity);

		/** \brief get the last DynamicEntity added to this file
		 * \return The last DynamicEntity added*/
		DynamicEntity* getLastDynamicEntity();
	private:
		Texture* m_texture;
		std::map<std::string, DynamicEntity*> m_dynamicEntities;
};

#endif
