#ifndef DEF_UPDATABLE
#define DEF_UPDATABLE

#include <list>
#include <iostream>
#include <stdexcept>
#include "JniMadeOf.h"

class Render;

/** \brief basic class for updating components*/
class Updatable : public JniMadeOf
{
	public:
		Updatable(Updatable *parent);

		virtual ~Updatable();

		/** \brief call when a TouchEvent is called. Try to get the Updatable who get the focus
		 * \param render the Render which has catch the event.*/
		virtual void updateFocus(Render& render);

		/** \brief called when the object has the focus
		 * \param render the Render which has catch the event.*/
		virtual void onFocus(Render& render);

		/** \brief Update the Updatable and its children.
		 *  \param render the render from where the updatable could interact
		 */
		virtual void update(Render &render);

		/** \brief because maybe you don't want to update the Updatable children on some case, you can just put your updates operations here.
		 * \param render the render from where the updatable could interact*/
		virtual void onUpdate(Render &render);

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

		/** \brief set if the updatable should be updated for its focus
		 * \param f the new value of m_updateFocus*/
		void setUpdateFocus(bool f);

		/** \brief Return Updatable's parent.
		 * \return the Updatable parent
		*/
		const Updatable* getParent() const;
	protected:
		std::list <Updatable*> m_child; /**< Child's list. */
		Updatable *m_parent; /**< The Updatable's parent. */
		bool m_updateFocus;
		bool m_canUpdate;

		/** \brief extract a list of T object from the Updatable child's list(Widget for example)
		 * \return a list of all T objects from Updatable's children*/
		template <typename T>
		std::list<T*> extractFromUpdatableChild()
		{
			return extractFromUpdatableList<T>(m_child);
		}

		/** \brief extract a list of T object from the Updatable list.
		 * \return a list of all T objects from Updatable list*/
		template <typename T>
		static std::list<T*> extractFromUpdatableList(std::list<Updatable*> fromExtract)
		{
			std::list<T*> list;
			for(std::list<Updatable*>::const_iterator it = fromExtract.begin(); it != fromExtract.end(); ++it)
				if(T* extracted = dynamic_cast<T*>(*it))
					list.push_back(extracted);

			return list;
		}

		static bool focusIsCheck; /** Tell if we have finish to get the focus*/
};

#endif
