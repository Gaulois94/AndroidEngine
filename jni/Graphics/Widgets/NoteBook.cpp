#include "Widgets/NoteBook.h"

NoteBook::NoteBook(Updatable* parent, Material* buttonMaterial, const Rectangle3f& rect) : GroupDrawable(parent, rect), m_nbPage(0)
{
	m_deleteAuto = true;
}

NoteBook::~NoteBook()
{
	for(std::list<ActiveNoteBook*>::iterator it = m_activeNoteBook.begin(); it != m_activeNoteBook.end(); it++)
		if(*it)
			delete (*it);
}

void NoteBook::addNotePage(NotePage* notePage, const std::string& name)
{
	addChild(notePage);
	Button* button = new Button(this, *(m_textButton.push_back(new Text(NULL, buttonMaterial))));
	m_drawables.push_back(button);

	ActiveNoteBook* act = new ActiveNoteBook(.noteBook = this, .index = m_nbPage);
	m_activeNoteBook.push_back(act);
	button->setActiveFunc();

	notePage->setButtonRect(Rectangle3f(m_nbPage * getDefaultPos(), 0.0, 0.0, 0.2, 0.1, 0.0));
	m_nbPage++;
}
