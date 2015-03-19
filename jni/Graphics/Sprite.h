#ifndef DEF_SPRITE_INCLUDE
#define DEF_SPRITE_INCLUDE

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <GLES2/gl2.h>

#include "Drawable.h"
#include "Texture.h"
#include "Rectangle2.h"

//Square with a Texture. If Texture==NULL, it will show a white square.
class Sprite : public Drawable
{
	public:
		Sprite(Material* material, const Texture* texture);

		void onDraw(Renderer* renderer, glm::mat4& mvp);
		void setTexture(const Texture* texture, bool resetSubTextureRect=true);
		void setSubTextureRect(const FloatRect2& subTextureRect);

		const Texture* getTexture() const;
		const FloatRect2& getSubTextureRect() const;
	private:
		static short drawOrder[6];
		void initVbos(float* vertexCoords, float* textureCoords);
		FloatRect2 m_subTextureRect;
		const Texture* m_texture;
};

#endif
