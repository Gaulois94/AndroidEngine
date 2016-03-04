#include "Map/Traces/Trace.h"

Trace::Trace(Updatable* parent, const Rectangle3f& defaultConf, const std::string& name) : Drawable(parent, NULL, defaultConf), m_name(name)
{}

Trace::~Trace()
{
	for(uint32_t i=0; i < m_tiles.size(); i++)
	{
		for(uint32_t j=0; j < m_tiles[i].size(); j++)
		{
			Tile* tile = m_tiles[i][j];
			if(tile)
				delete tile;
		}
	}
}

void Trace::onUpdate(Render& render)
{
	for(uint32_t i=0; m_tiles.size(); i++)
	{
		for(uint32_t j=0; j < m_tiles[i].size(); j++)
		{
			Tile* tile = m_tiles[i][j];
			if(tile)
			{
				//Destroy tiles if needed
				if(tile->canDestroy())
				{
					delete tile;
					m_tiles[i][j] = NULL;
				}
			}
		}
	}
}
