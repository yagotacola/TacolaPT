#pragma once

class UICombobox_ : public Element_
{
public:
	UICombobox_(int iID);

	int iSelectedID = 0;

	void createButton(int iID, int x, int y, char* path, char* path_);
	UIWindow_* createWindow(int iID, int x, int y, char* top, char* mid, char* bot);
	void addOption(int iID, char* path, char* label, bool line = true);
	void addOption1(int iID, char* path, char* label, bool line = true);
	void addOption2(int iID, char* path, char* label, bool line = true);
	void addOption3(int iID, char* path, char* label, bool line = true);
	void addOption4(int iID, char* path, char* label, bool line = true);
	void addOption5(int iID, char* path, char* label, bool line = true);
	void addOption6(int iID, char* path, char* label, bool line = true);
	void selectOption(int iID);
	void setOnSelect(std::function<void()> callback) { OnSelect = callback; }

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	void OnSelectOption(int iID);

	void setY(int y);

private:
	UIButton_* pButton = nullptr;
	UIWindow_* pWindow = nullptr;

	vector<std::pair<int, UIImage_*>> vLabels;

	std::function<void()> OnSelect = 0;

	void OnClickToggleWindow();
};