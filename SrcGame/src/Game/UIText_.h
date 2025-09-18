#pragma once


enum EOrientation
{
	EORIENT_Left = 1,
	EORIENT_Right = 2,
	EORIENT_Wrap = 3,
	EORIENT_WrapLeft = 4,
	EORIENT_Center = 5,
};

class UIText_ : public Element_
{
public:
	UIText_(int iID, char* Text, int x, int y, bool bold = false, DWORD dwColor = D3DCOLOR_ARGB(255, 255, 255, 255));
	UIText_(int iID, char* FontName, int FontSize, bool bold, char* Text, int x, int y, DWORD dwColor = D3DCOLOR_ARGB(255, 255, 255, 255), DWORD dwHoverColor = D3DCOLOR_ARGB(255, 255, 255, 255));

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	void AddChar(char Code);
	void RemoveChar(int count = 1);

	void setText(string text);
	string getText() { return string(szText); }

	void append(string text);

	int Length() { return lstrlen(szText); }
	void setOrientation(EOrientation orientation) { eOrientation = orientation; if (eOrientation == EORIENT_Wrap || eOrientation == EORIENT_WrapLeft) update(); }
	void setWidth(int width) { iWidth = width; if (eOrientation == EORIENT_Wrap || eOrientation == EORIENT_WrapLeft) update(); }
	void setHeight(int height) { iHeight = height; if (eOrientation == EORIENT_Wrap || eOrientation == EORIENT_WrapLeft) update(); }

	void setOutline(int outline, DWORD color = D3DCOLOR_ARGB(255, 0, 0, 0));
	void setColor(DWORD color) { TextColor = color; }
	void setHoverColor(DWORD color) { HoverColor = color; }

	CFont* GetFont() { return pFont; }

private:
	char szText[5000];
	DWORD TextColor;
	DWORD HoverColor;
	EOrientation eOrientation;
	void update();
	CFont* pFont = nullptr;
	int Outline = 0;
	DWORD dwOutlineColor = D3DCOLOR_ARGB(255, 0, 0, 0);
};

extern char* FormatString(char* fmt, ...);