#ifndef  TRACE_INC
#define  TRACE_INC

#include "Updatable.h"
#include "Map/Tiles/Tile.h"

/** \class Trace
 * \brief Basic abstract class for traces. Don't use it directly*/
class Trace : public Updatable, GroupTransformable
{
	public:
		/** \brief Basic constructor for Trace.*/
		Trace(const std::string& name);

		/** \brief Basic destructor for Trace.*/
		~Trace();

		/** \brief get the tile at a position
		 * \param x the x position in pixels coords
		 * \param y the y position in pixels coords
		 * \return Tile the tille at the position x, y. NULL if nothing.*/
		virtual Tile* getTile(uint32_t x, uint32_t y)=0;

		void onUpdate(Render& render);

		/** \brief add the tile at the position x, y.
		 * \param x the x position in pixels coords
		 * \param y the y position in pixels coords*/
		virtual void addTile(Tile* tile, uint32_t x, uint32_t y)=0;
	private:
		std::vector<std::vector<Tile*>> m_tiles;
		std::string m_name;
};

#endif
