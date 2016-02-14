#ifndef  TILE_INC
#define  TILE_INC

class Tile : public Drawable
{
	public:
		Tile(Updatable* parent, Material* mtl, const Rectangle3f& rect);		
		uint32_t getInfo();
	private:
		uint32_t m_info;
};

#endif
