#include "UILinker_.h"

UIVerticalScroll_::UIVerticalScroll_(int iID, int x, int y, int w, int h, int minValue, int maxValue)
{
	setID(iID);
	setX(x);
	setY(y);

	ScrollBarBg = new UIImage_(0, "game\\GUI\\Chat\\scroll\\barbg_v.png", 0, 0);
	ScrollButton = new UIImage_(0, "game\\GUI\\Chat\\scroll\\icon_2.png", -1, 0);

	if (w <= 0)
	{
		setWidth(ScrollButton->getWidth());
		ScrollBarBg->setX((getWidth() - ScrollBarBg->getWidth()) / 2);
	}
	else
	{
		setWidth(w);
		ScrollBarBg->setWidth(getWidth());
	}

	if (h <= 0)
		setHeight(ScrollBarBg->getHeight());
	else
	{
		setHeight(h);
		ScrollBarBg->setHeight(h);
	}

	setMin(minValue);
	setMax(maxValue);

	setValue(maxValue);
}

void UIVerticalScroll_::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
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

		ScrollBarBg->Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
		ScrollButton->Render(iRenderX, iRenderY - (ScrollButton->getHeight() / 2), iRenderWidth, iRenderHeight + 10, iSourceX, iSourceY);
	}
}

bool UIVerticalScroll_::OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{
		if (iWidth <= 0 || iHeight <= 0)
			return false;

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

		if (isMousePos(iRenderX, iRenderY - iStartY, iRenderWidth, iRenderHeight))
		{
			if (Type == Down)
			{
				bTrackY = true;

				if (pRealCursorPos.y >= iRenderY && pRealCursorPos.y <= iRenderY + iRenderHeight)
					updateButtonPos(pRealCursorPos.y - iRenderY - 4);
			}
			else if (Type == Up)
			{
				bTrackY = false;
			}
			return true;
		}

		if (Type == Up)
		{
			bTrackY = false;
		}
	}
	return false;
}

bool UIVerticalScroll_::OnMouseMove(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{
		if (iWidth <= 0 || iHeight <= 0)
			return false;

		if (bTrackY)
		{
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

			updateButtonPos(pRealCursorPos.y - iRenderY - 4);
		}
		return true;
	}
	return false;
}

bool UIVerticalScroll_::OnMouseScroll(int zDelta, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{
		if (iWidth <= 0 || iHeight <= 0)
			return false;

		if (zDelta < 0)
		{
			updateButtonPos(ScrollButton->getY() + (getHeight() / 25) + 1);
		}
		else
		{
			updateButtonPos(ScrollButton->getY() - (getHeight() / 25) - 1);
		}
		return true;
	}
	return false;
}

void UIVerticalScroll_::setHeight(int val)
{
	iHeight = val;
	ScrollBarBg->setHeight(val);
}

void UIVerticalScroll_::updateButtonPosByValue()
{
	float percent = getValue() / (float)getMax();
	char buff[255];
	sprintf(buff, "%.2f | %.2f", percent, (float)getHeight() * percent);
	updateButtonPos((float)getHeight() * percent);
}

void UIVerticalScroll_::updateButtonPos(int iY)
{
	if (iY < 0)
		iY = 0;

	if (iY > getHeight())
		iY = getHeight();

	ScrollButton->setY(iY);

	int interval = iY;
	float percent = interval / (float)getHeight();
	/*char buff[255];
	sprintf(buff, "%.2f | %d", percent, ((getMax() - getMin()) * percent) + getMin());*/
	setValue(((getMax() - getMin()) * percent) + getMin());
}
