#ifndef DEF_UPDATABLE
#define DEF_UPDATABLE

#include <list>
#include <iostream>
#include <stdexcept>
#include "JniMadeOf.h"

class Renderer
{};

/** \brief basic class for updating components*/
class Updatable
{
	public:
		Updatable(Updatable *parent);

		virtual ~Updatable();

		/** \brief Update the Updatable and its child.
		 *  \param render the renderer from where the updatable could interact
		 */
		virtual void update(Renderer &render);

		/** \brief Add a child.
		 *
		 * \param child Updatable who will be the child
		 * \param pos It indicated where the child will be placed in the child's list (the order is important for the update's order). At the default, the child will be placed at the end of the child's list.
		 * */
		virtual void addChild(Updatable *child, int pos = -1);

		/** \brief Set the Updatable's parent.
		 *
		 *  \param parent The Updatable who will be the parent.
		 *  \param pos The widget's position in the parent's child list. At the default, the Updatable will be placed at the end of the child's list.
		 * */
		virtual void setParent(Updatable *parent, int pos = -1);

		/** \brief Remove the child of the Updatable's child's list. It return true if the removing is correct, else it return false(maybe the parameter child is not an updatable child).
		 *  \param child The pointer of the child who will be deleted of the update's child list. 
		 */
		virtual bool removeChild(Updatable *child);

		/** \brief Remove the child who is in the position indicate. It return true if the removing is correct, else it return false(maybe the position is wrong).
		 * \param pos The child's position in the Updatable's child's list.
		 * */
		bool removeChild(unsigned int pos);

		/** \brief Return true if "child" is an Updatable's child, else it returns false.
		 *  \param child The Updatable which can be an Updatable's child.
		 *  \return the child is present on the Updatable's child list or not.
		 * */
		bool isChild(const Updatable *child);

		/** \brief Return Updatable's parent.
		 * \return the Updatable parent
		*/
		const Updatable* getParent() const;
	protected:
		std::list <Updatable*> m_child; /**< Child's list. */
		Updatable *m_parent; /**< The Updatable's parent. */

		/** \brief extract a list of T object from the Updatable child's list(Widget for example)
		 * \return a list of all T objects from Updatable's children*/
		template <typename T>
		std::list<T*> extractFromUpdatableChild() const
		{
			return extractFromUpdatableList<T>(m_child);
		}

		/** \brief extract a list of T object from the Updatable list.
		 * \return a list of all T objects from Updatable list*/
		template <typename T>
		static std::list<T*> extractFromUpdatableList(std::list<Updatable*> fromExtract) const
		{
			std::list<T*> list;
			for(std::list<Updatable*>::const_iterator it = fromExtract.begin(); it != fromExtract.end(); ++it)
				if(T* extracted = dynamic_cast<T*>(*it))
					list.push_back(extracted);

			return list;
		}
};

#endif
