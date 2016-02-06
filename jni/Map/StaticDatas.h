#ifndef  STATICDATAS_INC
#define  STATICDATAS_INC

struct StaticDatas
{
	Tile*(*createStaticTile)(Texture*, const Rectangle2f*);
};

#endif
