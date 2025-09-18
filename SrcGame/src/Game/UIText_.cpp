#include "UILinker_.h"
#include "Engine/CFontHandler.h"

char* FormatString(char* fmt, ...)
{
	static char buff[4096];

	ZeroMemory(buff, sizeof(buff));

	va_list args;

	va_start(args, fmt);
	vsprintf(buff, fmt, args);
	va_end(args);

	return buff;
}

UIText_::UIText_(int iID, char* Text, int x, int y, bool bold, DWORD dwColor)
{
	setID(iID);
	setX(x);
	setY(y);
	setHover(false);
	TextColor = dwColor;
	HoverColor = dwColor;

	pFont = CFONTHANDLER->GetFontDefault(bold);

	ZeroMemory(szText, sizeof(szText));
	lstrcpy(szText, Text);

	update();
	setOrientation(EORIENT_Left);
}

UIText_::UIText_(int iID, char* FontName, int FontSize, bool bold, char* Text, int x, int y, DWORD dwColor, DWORD dwHoverColor)
{
	setID(iID);
	setX(x);
	setY(y);
	setHover(false);
	TextColor = dwColor;
	HoverColor = dwHoverColor;

	ZeroMemory(szText, sizeof(szText));
	lstrcpy(szText, Text);

	pFont = CFONTHANDLER->GetFont(FontName, FontSize, bold);

	update();
	setOrientation(EORIENT_Left);
}

void UIText_::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{
		if (iWidth <= 0 || iHeight <= 0)
			return;

		int cX = getX();
		int cY = getY();
		int cWidth = getWidth();
		int cHeight = getHeight();
		int iStartX = cX < iSourceX ? abs(cX - iSourceX) : 0;
		int iStartY = cY < iSourceY ? abs(cY - iSourceY) : 0;

		int iRenderX = cX + iX + iStartX;
		int iRenderY = cY + iY + iStartY;
		int iRenderWidth = low(cWidth, iWidth);
		int iRenderHeight = low(cHeight, iHeight);

		if (cX + iRenderWidth > iWidth)
			iRenderWidth -= (cX + iRenderWidth) - iWidth;

		if (cY + iRenderHeight > iHeight)
			iRenderHeight -= (cY + iRenderHeight) - iHeight;

		if (iStartY < iRenderHeight && iStartX < iRenderWidth)
		{
			UINT uFormat = 0;

			if (iStartX > 0)
			{
				uFormat |= DT_RIGHT;
			}
			else if (iRenderWidth < cWidth)
			{
				if (eOrientation == EORIENT_Left)
					uFormat |= DT_LEFT;
				else
					uFormat |= DT_RIGHT;
			}

			if (iStartY > 0)
			{
				uFormat |= DT_BOTTOM;
			}

			if (eOrientation == EORIENT_Wrap)
			{
				uFormat |= DT_CENTER;
				uFormat |= DT_WORDBREAK;
			}
			else if (eOrientation == EORIENT_WrapLeft)
				uFormat |= DT_WORDBREAK;
			else if (eOrientation == EORIENT_Center)
				uFormat |= DT_CENTER;

			if (Outline > 0)
			{
				pFont->SetFontColor(dwOutlineColor);
				pFont->DrawRect(RECT({ iRenderX - Outline, iRenderY, iRenderX - Outline + iRenderWidth - iStartX, iRenderY + iRenderHeight - iStartY }), szText, lstrlen(szText), uFormat);
				pFont->DrawRect(RECT({ iRenderX, iRenderY - Outline, iRenderX + iRenderWidth - iStartX, iRenderY - Outline + iRenderHeight - iStartY }), szText, lstrlen(szText), uFormat);
				pFont->DrawRect(RECT({ iRenderX + Outline, iRenderY, iRenderX + Outline + iRenderWidth - iStartX, iRenderY + iRenderHeight - iStartY }), szText, lstrlen(szText), uFormat);
				pFont->DrawRect(RECT({ iRenderX, iRenderY + Outline, iRenderX + iRenderWidth - iStartX, iRenderY + Outline + iRenderHeight - iStartY }), szText, lstrlen(szText), uFormat);
			}

			pFont->SetFontColor(getHover() || getSelected() ? HoverColor : TextColor);
			pFont->DrawRect(RECT({ iRenderX, iRenderY, iRenderX + iRenderWidth - iStartX, iRenderY + iRenderHeight - iStartY }), szText, lstrlen(szText), uFormat);
		}
	}
}

void UIText_::AddChar(char Code)
{
	if (lstrlen(szText) < sizeof(szText) - 1)
	{
		szText[lstrlen(szText)] = Code;
		szText[lstrlen(szText)] = 0;

		update();
	}
}

void UIText_::RemoveChar(int count)
{
	if (lstrlen(szText) >= count && count > 0)
	{
		szText[lstrlen(szText) - count] = 0;

		update();
	}
}

void UIText_::setText(string text)
{
	lstrcpy(szText, text.c_str());

	update();
}

void UIText_::append(string text)
{
	lstrcat(szText, text.c_str());

	update();
}

void UIText_::setOutline(int outline, DWORD color)
{
	Outline = outline;
	dwOutlineColor = color;
}

void UIText_::update()
{
	SIZE sz = {};

	if (eOrientation == EORIENT_Wrap || eOrientation == EORIENT_WrapLeft)
	{
		pFont->GetTextSize(szText, &sz, getWidth());
		iHeight = sz.cy;
	}
	else
	{
		pFont->GetTextSize(szText, &sz);
		iWidth = sz.cx;
		iHeight = sz.cy;
	}

}
