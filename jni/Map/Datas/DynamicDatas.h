#ifndef  DYNAMICDATAS_INC
#define  DYNAMICDATAS_INC

#include "Map/Tiles/DynamicAnim.h"
#include "Graphics/Texture.h"
#include "Graphics/Rectangle2.h"
#include "Updatable.h"
#include <vector>

typedef DynamicAnim*(*createDynamicAnimPtr)(Updatable*, Material*, const Texture*, const Rectangle2f&, const std::vector<Rectangle2f*>&, uint32_t, uint32_t);

//n, nX, currentN, posX, posY, sizeX, sizeY, spacX, spacY, tilePosX, tilePosY
typedef StaticAnim*(*createStaticAnimPtr)(Updatable*, Material*, const Texture*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

struct DynamicEntity
{
	std::vector<Rectangle2f> tileRects;
	createDynamicAnimPtr     createDynamicAnim;
	Material*                material;
};

class StaticEntity
{
	public:
		StaticEntity(createStaticAnim createStaticAnim, n, nX, posX, posY, sizeX, sizeY, spacX, spacY);
		Tile* createStaticAnim(Updatable* parent, const Texture*, uint32_t tileID, uint32_t posX, uint32_t posY);
		Material* material;
	private:
		uint32_t m_n, m_nX, m_posX, m_posY, m_sizeX, m_sizeY, m_spacX, m_spacY;
		std::vector<std::string> m_names;
		std::vector<std::string> m_types;
		createStaticAnimPtr m_createStaticAnim;
};

#endif
