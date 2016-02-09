#ifndef  MAPFILES_INC
#define  MAPFILES_INC

#include "Map/StaticDatas.h"

class StaticFile
{
	public:
		StaticFile(Texture* texture, uint32_t spacX, uint32_t spacY, uint32_t sizeX, uint32_t sizeY);
		void   addTileDatas(TileDatas* tileDatas);
		Tile*  createTile(uint32_t tileID, bool def);
	private:
		Texture* m_texture;
		std::vector<TileDatas*> m_tileDatas;
		uint32_t m_spacingX;
		uint32_t m_spacingY;
		uint32_t m_tileSizeX;
		uint32_t m_tileSizeY;
};

class DynamicFile
{
	public:
		DynamicFile(Texture* texture);
	private:
		Texture* m_texture;
};

#endif
