#ifndef  GROUPTRANSFORMABLE_INC
#define  GROUPTRANSFORMABLE_INC

#include "Transformable.h"
#include <vector>

/** \brief Class for grouping Transformable in another Transformable. Used for setting (for example in a scrolling) all a vector of Transformable by the same transformation added*/
class GroupTransformable : public Transformable
{
	public:
		/** \brief default constructor*/
		GroupTransformable(const Rectangle3f& defaultConf);

		/** \brief add a Transformable in the Group Transformable
		 * \param transformable The Transformable to add*/
		void addTransformable(Transformable* transformable);

		/** \brief should we transform all the Transformable ?
		 * \param e the parameter enable*/
		void setEnableTransformation(bool e);

		/** \brief the characteristic enable of the GroupTransformable*/
		bool getEnableTransformation();
	private:
		bool m_enabled;
		std::vector<Transformable*> m_vectorTransformable;
};

#endif
