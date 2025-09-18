#pragma once

class UIWindow_ : public Element_
{
public:
	UIWindow_(int ID, char* path, int x, int y, bool fixed = true);
	UIWindow_(int ID, char* top, char* mid, char* bot, int x, int y, bool fixed = true);
	UIWindow_(int ID, int x, int y, int w, int h, bool fixed = true);
	~UIWindow_();

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseMove(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseScroll(int zDelta, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnKeyDown(char Code);
	bool OnKeyChar(char Code);
	bool GetToggle() { return bMouseToggle; };
	void setMidHeight(int height);
	int getMidHeight() { if (getType() == 2) return bgSplit[1]->getHeight(); else return 0; }
	void setDefaultMidHeight(int height) { iDefaultMidHeight = height; }
	void setExpandLimit(int limit) { iExpandLimit = limit; }
	void setExpandRate(int rate) { iExpandRate = rate; }
	void ExpandMidWindow();
	void AdjustScrollBar();
	void SetScrollBarValue(int value);

	void setElementMax(int val) { iElementMax = val; }

	int getMaxY() { return iMaxY; }

	void AddElement(Element_* pElement);
	void RemoveElementByID(int ID);

	void SetScrollBar(UIVerticalScroll_* pScroll);

	void setScroll(bool scroll) { bScroll = scroll; }

	template<typename T>
	inline T* GetElement(int iID)
	{
		for (auto pElement : vElements)
			if (pElement->getID() == iID)
				return static_cast<T*>(pElement);
		return nullptr;
	}

	vector<Element_*> GetAllElements() { return vElements; }
private:
	UIImage_* Background;
	UIImage_* bgSplit[3];

	vector<Element_*> vElements;
	UIVerticalScroll_* pVerticalScroll = nullptr;

	int iMaxY = 0;
	bool bMouseToggle = false;
	int iPaddingX = 0;
	int iPaddingY = 0;
	int iDefaultMidHeight = 0;
	int iExpandCount = 0;
	int iExpandLimit = 0;
	int iExpandRate = 0;

	int iElementMax = 0;
	bool bScroll = true;
};
