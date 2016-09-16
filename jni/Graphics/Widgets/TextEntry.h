#ifndef  TEXTENTRY_INC
#define  TEXTENTRY_INC

class TextEntry : public GroupDrawable
{
	public:
		TextEntry(Updatable* parent, const std::string& defaultText, Material* textMaterial, Material* backgroundMaterial);
	private:
};

#endif
