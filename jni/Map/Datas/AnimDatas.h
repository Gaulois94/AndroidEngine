#ifndef  ANIMDATAS_INC
#define  ANIMDATAS_INC

#include "Map/Tiles/DynamicAnim.h"
#include "Map/Tiles/StaticAnim.h"
#include "Graphics/Texture.h"
#include "Graphics/Rectangle2.h"
#include "Updatable.h"
#include <vector>

//parent, mtl, texture, animRect, info, currentN, nbFrames, posX, posY
typedef DynamicAnim*(*createDynamicAnimPtr)(Updatable*, Material*, const Texture*, const std::vector<Rectangle2ui*>&, void*, uint32_t, uint32_t, uint32_t posX, uint32_t posY);

//parent, mtl, texture, info, tileID (currentN), n, nX, posX, posY, sizeX, sizeY, spacX, spacY, tilePosX, tilePosY
typedef StaticAnim*(*createStaticAnimPtr)(Updatable*, Material*, const Texture*, void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

struct DynamicEntity
{
	public:
		DynamicEntity(createDynamicAnimPtr create);
		~DynamicEntity();

		const createDynamicAnimPtr createDynamicAnim;

		void addTile(Rectangle2ui* subRect, const char* name, const char* type);
		const std::vector<Rectangle2ui*>* getSubRects() const;
		const std::vector<std::string>&  getNames() const;
		const std::vector<std::string>&  getTypes() const;

		Material* material;
		void *info;
	private:
		std::vector<Rectangle2ui*> m_tileRects;
		std::vector<std::string> m_names;
		std::vector<std::string> m_types;
};

class StaticEntity
{
	public:
		StaticEntity(createStaticAnimPtr create, uint32_t n, uint32_t nX, uint32_t posX, uint32_t posY, uint32_t sizeX, uint32_t sizeY, uint32_t spacX, uint32_t spacY);
		StaticAnim* createStaticAnim(Updatable* parent, const Texture*, uint32_t tileID, uint32_t posX, uint32_t posY) const;

		const std::vector<std::string>&  getNames() const;
		const std::vector<std::string>&  getTypes() const;
		void addEntity(const char* name, const char* type);

		Material* material;
		void* info;
	private:
		uint32_t m_n, m_nX, m_posX, m_posY, m_sizeX, m_sizeY, m_spacX, m_spacY;
		std::vector<std::string> m_names;
		std::vector<std::string> m_types;
		createStaticAnimPtr m_createStaticAnim;
};

#endif
