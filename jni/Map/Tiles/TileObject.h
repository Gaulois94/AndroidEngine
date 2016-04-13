#ifndef  TILEOBJECT_INC
#define  TILEOBJECT_INC

#include "Map/Tiles/Tile.h"

class TileObject : public Tile
{
	public:
		TileObject(Updatable* parent, uint32_t nbCasesX, uint32_t nbCasesY, uint32_t tileSizeX, uint32_t tileSizeY, void* info);
		virtual void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f));

		/** \brief Add the tile 'tile' at the position x, y which are case coords */
		void addTile(Tile* tile, uint32_t x, uint32_t y);

		uint32_t getNbCasesX() const;
		uint32_t getNbCasesY() const;
	private:
		std::vector<std::vector<Tile*>> m_tiles;
		uint32_t m_nbCasesX;
		uint32_t m_nbCasesY;
		uint32_t m_tileSizeX;
		uint32_t m_tileSizeY;
};

#endif
