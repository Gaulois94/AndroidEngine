#ifndef  TILE_INC
#define  TILE_INC

class Tile : public Drawable
{
	public:
		Tile(Updatable* parent, Material* mtl, const Rectangle3f& rect);		
		virtual void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f))=0;
		uint32_t getInfo();
	private:
		uint32_t m_info;
};

#endif
