#include "UILinker_.h"

UICombobox_::UICombobox_(int iID)
{
	setID(iID);
}

void UICombobox_::createButton(int iID, int x, int y, char * path, char * path_)
{
	pButton = new UIButton_(iID, path, path_, x, y, true, false, std::bind(&UICombobox_::OnClickToggleWindow, this));

	setX(x);
	setY(y);
	setWidth(pButton->getWidth());
	setHeight(pButton->getHeight());
}

UIWindow_ * UICombobox_::createWindow(int iID, int x, int y, char * top, char * mid, char * bot)
{
	pWindow = new UIWindow_(iID, top, mid, bot, x, y);
	pWindow->hide();
	return pWindow;
}

void UICombobox_::addOption(int iID, char * path, char * label, bool line)
{
	pWindow->ExpandMidWindow();
	pWindow->AddElement(new UIButton_(iID, path, path, 1, 1, true, false, std::bind(&UICombobox_::OnSelectOption, this, iID)));

	/*if(line)
		pWindow->AddElement(new UIImage_(0, "game\\GUI\\Chat\\chat_combo_line.png", 5, pWindow->getMaxY() + 2));*/

	if (pButton)
		vLabels.push_back(std::pair<int, UIImage_*>(iID, new UIImage_(iID, label, pButton->getX(), pButton->getY())));
}

void UICombobox_::addOption1(int iID, char * path, char * label, bool line)
{
	pWindow->ExpandMidWindow();
	pWindow->AddElement(new UIButton_(iID, path, path, 42, 1, true, false, std::bind(&UICombobox_::OnSelectOption, this, iID)));

	/*if(line)
		pWindow->AddElement(new UIImage_(0, "game\\GUI\\Chat\\chat_combo_line.png", 5, pWindow->getMaxY() + 2));*/

	if (pButton)
		vLabels.push_back(std::pair<int, UIImage_*>(iID, new UIImage_(iID, label, pButton->getX(), pButton->getY())));
}

void UICombobox_::addOption2(int iID, char * path, char * label, bool line)
{
	pWindow->ExpandMidWindow();
	pWindow->AddElement(new UIButton_(iID, path, path, 84, 1, true, false, std::bind(&UICombobox_::OnSelectOption, this, iID)));

	/*if(line)
		pWindow->AddElement(new UIImage_(0, "game\\GUI\\Chat\\chat_combo_line.png", 5, pWindow->getMaxY() + 2));*/

	if (pButton)
		vLabels.push_back(std::pair<int, UIImage_*>(iID, new UIImage_(iID, label, pButton->getX(), pButton->getY())));
}

void UICombobox_::addOption3(int iID, char * path, char * label, bool line)
{
	pWindow->ExpandMidWindow();
	pWindow->AddElement(new UIButton_(iID, path, path, 125, 1, true, false, std::bind(&UICombobox_::OnSelectOption, this, iID)));

	/*if(line)
		pWindow->AddElement(new UIImage_(0, "game\\GUI\\Chat\\chat_combo_line.png", 5, pWindow->getMaxY() + 2));*/

	if (pButton)
		vLabels.push_back(std::pair<int, UIImage_*>(iID, new UIImage_(iID, label, pButton->getX(), pButton->getY())));
}

void UICombobox_::addOption4(int iID, char * path, char * label, bool line)
{
	pWindow->ExpandMidWindow();
	pWindow->AddElement(new UIButton_(iID, path, path, 166, 1, true, false, std::bind(&UICombobox_::OnSelectOption, this, iID)));

	/*if(line)
		pWindow->AddElement(new UIImage_(0, "game\\GUI\\Chat\\chat_combo_line.png", 5, pWindow->getMaxY() + 2));*/

	if (pButton)
		vLabels.push_back(std::pair<int, UIImage_*>(iID, new UIImage_(iID, label, pButton->getX(), pButton->getY())));
}

void UICombobox_::addOption5(int iID, char * path, char * label, bool line)
{
	pWindow->ExpandMidWindow();
	pWindow->AddElement(new UIButton_(iID, path, path, 207, 1, true, false, std::bind(&UICombobox_::OnSelectOption, this, iID)));

	/*if(line)
		pWindow->AddElement(new UIImage_(0, "game\\GUI\\Chat\\chat_combo_line.png", 5, pWindow->getMaxY() + 2));*/

	if (pButton)
		vLabels.push_back(std::pair<int, UIImage_*>(iID, new UIImage_(iID, label, pButton->getX(), pButton->getY())));
}

void UICombobox_::addOption6(int iID, char * path, char * label, bool line)
{
	pWindow->ExpandMidWindow();
	pWindow->AddElement(new UIButton_(iID, path, path, 252, 1, true, false, std::bind(&UICombobox_::OnSelectOption, this, iID)));

	/*if(line)
		pWindow->AddElement(new UIImage_(0, "game\\GUI\\Chat\\chat_combo_line.png", 5, pWindow->getMaxY() + 2));*/

	if (pButton)
		vLabels.push_back(std::pair<int, UIImage_*>(iID, new UIImage_(iID, label, pButton->getX(), pButton->getY())));
}

void UICombobox_::selectOption(int iID)
{
	for (auto pLabel : vLabels)
	{
		if (pLabel.first == iID)
			pLabel.second->show();
		else
			pLabel.second->hide();
	}

	iSelectedID = iID;
	pWindow->hide();
}

void UICombobox_::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{
		if (pButton)
		{
			pButton->Render(iX, iY, iWidth, iHeight, iSourceX, iSourceY);
			for (auto pLabel : vLabels)
				pLabel.second->Render(iX, iY, iWidth, iHeight, iSourceX, iSourceY);
		}

		if (pWindow)
			pWindow->Render(iX, iY, iWidth, iHeight, iSourceX, iSourceY);
	}
}

bool UICombobox_::OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	bool bRet = false;
	if (isVisible())
	{
		if (pButton)
			if (pButton->OnMouseClick(Type, iX, iY, iWidth, iHeight, iSourceX, iSourceY))
				bRet = true;

		if (pWindow)
			if (pWindow->OnMouseClick(Type, iX, iY, iWidth, iHeight, iSourceX, iSourceY))
				bRet = true;
	}
	return bRet;
}

void UICombobox_::setY(int y)
{
	if (pButton && pWindow)
	{
		pButton->setY(y + (iY - pButton->getY()));
		pWindow->setY(y - (iY - pWindow->getY()));

		for (auto pLabel : vLabels)
			pLabel.second->setY(pButton->getY());
	}

	iY = y;
}

void UICombobox_::OnSelectOption(int iID)
{
	selectOption(iID);
	if (OnSelect)
		OnSelect();
}

void UICombobox_::OnClickToggleWindow()
{
	if (pWindow)
	{
		if (pWindow->isVisible())
			pWindow->hide();
		else
			pWindow->show();
	}
}
