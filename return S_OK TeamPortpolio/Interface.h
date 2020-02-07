#pragma once

class Interface
{

private:
	
	RECT NewRunRect;
	RECT MapToolRect;
	RECT OptionRect;
	RECT CursorRect;
	
	image* MainMenuImage;
	image* CursorImage;

	
public:
	Interface();
	~Interface();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);


};

