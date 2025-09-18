#pragma once

class UIButton_ : public Element_
{
public:
	UIButton_(int ID, char* path, char* path_, int x, int y, bool hover = true, bool selected = false, std::function<void()> callback = 0);

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

private:
	UIImage_* Image;
	UIImage_* Image_;

	std::function<void()> Activation;
};