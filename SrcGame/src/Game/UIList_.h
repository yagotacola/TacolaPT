#pragma once

class UIListBox_ : public Element_
{
public:
	UIListBox_(int ID, int x, int y, int w, int h);
	~UIListBox_();

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseMove(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseScroll(int zDelta, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnKeyDown(char Code);
	bool OnKeyChar(char Code);

	UIListItem_* getSelectedItem() { return pSelectedItem; }
	void selectItem(int iID);

	void AddListItem(UIListItem_* pListItem);

	template<typename T>
	inline T* GetListItem(int iID)
	{
		for (auto pListItem : vListItems)
			if (pListItem->getID() == iID)
				return static_cast<T*>(pListItem);
		return nullptr;
	}

private:
	vector<UIListItem_*> vListItems;
	UIListItem_* pSelectedItem;
};