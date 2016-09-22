#ifndef DRAWABLE_INCLUDE
#define DRAWABLE_INCLUDE

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "GroupTransformable.h"
#include "Updatable.h"
#include "Shader.h"
#include "Materials/Material.h"
#include "EventManager.h"
#include "Render.h"
#include <GLES2/gl2.h>

/** \brief Basic class drawable */
class Drawable : public GroupTransformable, public Updatable
{
	public:
		/** \brief create a Drawable associated with a material (thus a shader)
		 * \param parent the Drawable parent
		 * \param material The drawable material*/
		Drawable(Updatable *parent, Material* material, const Rectangle3f& defaultConfiguration=Rectangle3f(0, 0, 0, 0, 0, 0));

		virtual ~Drawable();

		/** \brief draw the drawable
		 * \param render The render where the drawable will be drawn
		 * \param transformation Transform the coord of the drawable itself transformed by the render's camera before.*/
		virtual void draw(Render& render, const glm::mat4& transformation=glm::mat4(1.0));

		virtual bool testFocus(uint32_t indicePointer, Render& render);
		virtual void updateGPU(Render& render);

		/** \brief is called by draw.
		 * \param render The render where the drawable will be drawn.
		 * \param mvp The transformation matrix generate by the camera, the transformation gived in draw function and the transformation used on the drawable itself.
		 *
		 * This function called the shader and gives it the parameters.
		 */
		virtual void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f))=0;

		virtual void onMove(const glm::vec3& v, bool useScale);
		virtual void onRotate(float angle, const glm::vec3& axis, const glm::vec3& origin);
		virtual void onScale(const glm::vec3& s);

		/** \brief Be static from the camera. If true, the next calls on draw function will ignore the camera.
		 * \param s the value of the staticity of the object.*/
		virtual void staticToCamera(bool s);

		/** \brief set the material (and thus the shader) of the object. For many fo the drawable, if the material is null, the draw function will be ignored.
		 * \param material the new material associated with the Drawable. */
		virtual void setMaterial(Material* material);

		/** \brief Get the material associated with the drawable.
		 * \return The material associated with the object. Can't be modified.*/
		virtual Material* getMaterial();

		/** \brief Tell if the Drawable is static to the Camera
		 * \return the staticity of the Drawable*/
		virtual bool isStaticToCamera() const;

		static void initShaders();
	protected:
		virtual void deleteVbos();
		Material* m_material;
		GLuint m_vboID;
		bool m_canDraw;
		bool m_staticToCamera;
};

#endif
