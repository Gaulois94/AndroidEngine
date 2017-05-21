#ifndef  MAPFILES_INC
#define  MAPFILES_INC

#include <map>
#include "Map/Datas/StaticDatas.h"
#include "Map/Datas/AnimDatas.h"
#include "Map/Tiles/DefaultTile.h"
#include "Graphics/Texture.h"

class MapFile
{
	public:
		MapFile(const Texture* texture);
		const Texture* getTexture() const;
	protected:
		const Texture* m_texture;
};

/** \class StaticFile
 * \brief contain information about a static file.*/
class StaticFile : public MapFile
{
	public:
		/** \brief Default constructor for a StaticFile
		 * \param texture the Texture of the file
		 * \param spacX the spacing in X between each tile
		 * \param spacY the spacing in Y between each tile
		 * \param sizeX the width of tiles
		 * \param sizeY the height of tiles*/
		StaticFile(const Texture* texture, uint32_t siZEx, uint32_t sizeY, uint32_t spacX, uint32_t spacY);

		/** \brief Default destructor. Destroy each TileDatas*/
		~StaticFile();

		/** \brief Add a StaticDatas on this file. Has to be allocated dynamically, and doesn't have to be destroy by the user (the object will do it itself)
		 * \param tileDatas the StaticDatas to add*/
		void   addStaticDatas(StaticDatas* tileDatas);

		/** \brief Create a tile placed at the place tileID. If you want to create a default tile, use def=true
		 * \param parent the parent of the new Tile*
		 * \param tileID the position of the tile on the file.
		 * \param def put def to true if you want to create a DefaultTile
		 * \return the Tile created. NULL if can't be created*/
		Tile*  createTile(Updatable* parent, uint32_t tileID, bool def);

		/** \brief Retrieve the name of the tileID
		 * \param tileID the tile identifiant
		 * \return the name*/
		const std::string& getTileName(uint32_t tileID) const{return m_tileDatas[tileID]->name;}

		/** \brief Retrieve the type of the tileID
		 * \param tileID the tile identifiant
		 * \return the type*/
		const std::string& getTileType(uint32_t tileID) const{return m_tileDatas[tileID]->type;}
	private:
		std::vector<StaticDatas*> m_tileDatas;
		uint32_t m_spacingX;
		uint32_t m_spacingY;
		uint32_t m_tileSizeX;
		uint32_t m_tileSizeY;
};

/** \class DynamicFile*/
class DynamicFile : public MapFile
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

		/** \brief add a StaticEntity to this file.
		 * \param key the name of the entity
		 * \param StaticEntity the StaticEntity itself*/
		void addStaticEntity(const std::string& key, StaticEntity* entity);

		/** \brief get the last DynamicEntity added to this file
		 * \return The last DynamicEntity added*/
		DynamicEntity* getLastDynamicEntity();

		/** \brief get the last StaticEntity added to this file
		 * \return The last StaticEntity added*/
		StaticEntity* getLastStaticEntity();

		/** \brief get the DynamicEntity bound to the key name
		 * \param name the name of the animation
		 * \return the DynamicEntity which corresponds to the name. NULL if not found*/
		DynamicEntity* getDynamicEntity(const std::string& name);

		/** \brief get the StaticEntity bound to the key name
		 * \param name the name of the animation
		 * \return the StaticEntity which corresponds to the name. NULL if not found*/
		StaticEntity* getStaticEntity(const std::string& name);
	private:
		std::multimap<std::string, DynamicEntity*> m_dynamicEntities;
		std::multimap<std::string, StaticEntity*>  m_staticEntities;
};

#endif
