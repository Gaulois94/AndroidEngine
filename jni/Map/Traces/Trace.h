#ifndef  TRACE_INC
#define  TRACE_INC

#include "Updatable.h"
#include "Map/Tiles/Tile.h"

/** \class Trace
 * \brief Basic abstract class for traces. Don't use it directly*/

class Trace : public Drawable
{
	public:
		/** \brief Basic constructor for Trace.*/
		Trace(Updatable* parent, const Rectangle3f& defaultConf, const std::string& name);

		/** \brief Basic destructor for Trace.*/
		~Trace();

		/** \brief get the tile at a position
		 * \param x the x position in world coords
		 * \param y the y position in world coords
		 * \return Tile the tile at the position x, y. NULL if nothing.*/
		virtual Tile* getTileWorldCoords(double x, double y)=0;

		virtual Tile* getTileTraceCoords(int x, int y)=0;

		virtual void onDraw(Render& render, const glm::mat4& mvp=glm::mat4(1.0f));
		void onUpdate(Render& render);

		/** \brief add the tile at the position x, y.
		 * \param x the x position in pixels coords
		 * \param y the y position in pixels coords*/
		virtual void addTile(Tile* tile, uint32_t x, uint32_t y);

		const std::string& getName() const;
	protected:
		std::vector<std::vector<Tile*>> m_tiles;
		std::string m_name;
};

#endif
