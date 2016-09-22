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
		 * \param pointerEvent the indice pointer of the Touch Event
		 * \param render the Render which has catch the event.*/
		virtual void updateFocus(uint32_t pointerEvent, Render& render);

		/** \brief The test function for telling if the Updatable can be focused following the pointerEvent and the render passed on parameters
		 * \param pointerEvent the indice pointer of the Touch Event
		 * \param render the Render which has catch the event.*/
		virtual bool testFocus(uint32_t pointerEvent, Render& render);

		/** \brief called when the object has the focus
		 * \param pointerEvent the indice pointer of the Touch Event
		 * \param render the Render which has catch the event.*/
		virtual void onFocus(uint32_t pointerEvent, Render& render);

		/** \brief pass the keyCode for a keyUpEvent to each child, until a child handle the event
		 * \param keyCode the code of the key*/
		void keyUp(int32_t keyCode);

		/** \brief pass the keyCode for a keyDownEvent to each child, until a child handle the event
		 * \param keyCode the code of the key*/
		void keyDown(int32_t keyCode);

		/** \brief handle the key up event.
		 * \param keyCode the code of the key
		 * \return if the key was handled or not. Should be true if override*/
		virtual bool onKeyUp(int32_t keyCode);

		/** \brief handle the key down event.
		 * \param keyCode the code of the key
		 * \return if the key was handled or not. Should be true if override*/
		virtual bool onKeyDown(int32_t keyCode);

		/** \brief Update the Updatable and its children.
		 *  \param render the render from where the updatable could interact
		 */
		virtual void update(Render &render);

		/** \brief Update the Updatable and its children toward the GPU (draw function for example)
		 *  \param render the render from where the updatable could interact
		 */
		virtual void updateGPU(Render &render);

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

		/** \brief set if the updatable should be updated
		 * \param u the value of canUpdate*/
		void setCanUpdate(bool u);

		/** \brief Tell if the Updatableshould be updated on GPU side
		 * \param d the value of m_canDraw.*/
		virtual void setCanDraw(bool d);

		/** \brief Return Updatable's parent.
		 * \return the Updatable parent
		*/
		const Updatable* getParent() const;

		/** \brief tell if the updatable will be updated after each call of update()
		 * \return return the value of m_canUpdate*/
		bool getCanUpdate() const;

		/** \brief Set the callback when the Updatable is on focus
		 * \param focusCallback the functon to call
		 * \param data the data to pass */
		void setFocusCallback(void (*focusCallback)(Updatable*, void*), void* data=NULL);

		/** \brief Tell if the Updatable can be update on GPU side.
		 * \return m_canDraw*/
		virtual bool canDraw() const;

		static Updatable* objectFocused;
	protected:
		std::list <Updatable*> m_child; /**< Child's list. */
		Updatable *m_parent; /**< The Updatable's parent. */
		bool m_updateFocus;
		bool m_canUpdate;
		bool m_canDraw;
		void (*m_focusCallback)(Updatable*, void*)=NULL;
		void* m_focusDatas=NULL;

		static bool focusIsCheck;   /** Tell if we have finished to get the focus*/
		static bool keyUpIsCheck;   /** Tell if the key event was handled of not*/
		static bool keyDownIsCheck; /** Tell if the key event was handled of not*/
};

#endif
