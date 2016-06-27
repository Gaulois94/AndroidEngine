#ifndef  NOTEBOOK_INC
#define  NOTEBOOK_INC

#include "Widgets/NotePage.h"
#include "GroupDrawable.h"
#include "Text.h"

typedef struct ActiveNoteBook
{
	NoteBook* noteBook;
	int index;
}ActiveNoteBook;

class NoteBook : public GroupDrawable
{
	public:
		NoteBook(Updatable* parent, Material* buttonMaterial, const Rectangle3f& rect);
		~NoteBook();
		void addNotePage(NotePage* notePage, const std::string& name);
	private:
		uint32_t m_nbPage;
		std::list<Text*> m_textButton;
		std::list<ActiveNoteBook*> m_activeNoteBook;
};

#endif   /* ----- #ifndef NOTEBOOK_INC  ----- */
