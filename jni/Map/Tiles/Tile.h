#ifndef  TILE_INC
#define  TILE_INC

#include "Graphics/Drawable.h"

class Tile : public Drawable
{
	public:
		Tile(Updatable* parent, Material* mtl, const Rectangle3f& rect, void* info);		
		virtual void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f))=0;

		/** \brief return the information about the tile.
		 * \return the information about the tile. The information is stock as a pointer on void*/
		void* getInfo();

		uint32_t getNbCasesX() const;
		uint32_t getNbCasesY() const;

		/** \brief tell if the tile can be destroyed or not.
		 * return return if the tile can be destroyed*/
		bool canDestroy();
	protected:
		void* m_info;
		bool m_canDestroy;
		uint32_t m_nbCasesX;
		uint32_t m_nbCasesY;
};

#endif
