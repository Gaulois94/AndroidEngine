#ifndef  DYNAMICTRACE_INC
#define  DYNAMICTRACE_INC

#include "Map/Traces/Trace.h"

/** \class DynamicTrace
 * \brief Trace for managing dynamic tiles. They don't have any pattern at all.*/
class DynamicTrace : public Trace
{
	public:
		/** \brief DynamicTrace constructor. nbCases and size help for cutting the trace in sub part, useful for collisions
		 * \param nbCasesX how many rows do you want ?
		 * \param nbCasesY how many column do you want ?
		 * \param sizeX the width for each case
		 * \param sizeY the height for each case*/
		DynamicTrace(uint32_t nbCasesX, uint32_t nbCasesY, uint32_t sizeX, uint32_t sizeY);
		void onUpdate(Render& render);
		virtual Tile* getTile(uint32_t x, uint32_t y);
		void addTile(Tile* tile, uint32_t x, uint32_t y);
	private:
		uint32_t m_sizeX;
		uint32_t m_sizeY;
		uint32_t m_nbCasesX;
		uint32_t m_nbCasesY;
};

#endif
