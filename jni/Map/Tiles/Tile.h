#ifndef  TILE_INC
#define  TILE_INC

#include "Graphics/Drawable.h"

class Tile : public Drawable
{
	public:
		Tile(Updatable* parent, Material* mtl, const Rectangle3f& rect);		
		virtual void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f))=0;

		/** \brief return the information about the tile. Use bitmask to get them
		 * \return the information about the tile*/
		uint32_t getInfo();

		/** \brief tell if the tile can be destroyed or not.
		 * return return if the tile can be destroyed*/
		bool canDestroy();
	private:
		uint32_t m_info;
		bool m_canDestroy;
};

#endif
