#pragma once

#include <Windows.h>
#include <string>
#include <Utils/Geometry.h>
#include <Engine/UI/UIWindow.h>
#include <Engine/UI/UIEvent.h>
#include <Engine/UI/UICheckBox.h>
#include <smLib3d/smStage3d.h>

//#include "DXVideoRenderer.h"

enum ELoginState
{
	LOGINSTATE_None,
	LOGINSTATE_Opening,
	LOGINSTATE_Connecting,
	LOGINSTATE_ServerSelect,
	LOGINSTATE_Finish,
};

enum class ELoginScreenFunction
{
	LOGIN_SCREEN_CONSTRUCTOR = 0x0059E490,
	LOGIN_SCREEN_DECONSTRUCTOR = 0x0059F8F0,

};

enum class CHECKBOX_ID
{
	IS_IMAGE_BACKGROUND,
	IS_VIDEO_BACKGROUND,
	REMEMBER_LOGIN,
	WORLD_ID_WORLD = 14
};

#define LOGINSCREENHANDLER CLoginScreen::GetInstance()

class CLoginScreen
{
public:
	static              CLoginScreen* GetInstance() { static CLoginScreen instance; return &instance; }

	CLoginScreen();
	~CLoginScreen();


	BOOL				Init();
	void				Shutdown();

	void				Render3D();
	void				Render2D();

	void				Frame();

	void				OnMouseMove(class CMouse* pcMouse);
	BOOL				OnMouseClick(class CMouse* pcMouse);

	void				SetCamera(Point3D sPosition, Point3D sLookAt);

	void				SetLoginBoxPosition(int x, int y) { sLoginBoxPosition.iX = x; sLoginBoxPosition.iY = y; }
	void				SetLoginBoxSize(int iWidth, int iHeight) { iLoginBoxWidth = iWidth; iLoginBoxHeight = iHeight; }

	ELoginState			GetCurrentState() { return iCurrentStateLogin; }

	BOOL				IsLoginVideo() { return isLoginVideo; }

	smSTAGE3D* pcStage = NULL;

private:
	static const std::string loginVideoAnimationPath;
	static const std::string backgroundSelectorImagePath;
	static const std::string backgroundServersSelectorImagePath;

	typedef struct checkboxData
	{
		int id;
		bool state;
		std::string text;
		UI::Window_ptr windowSelector;

		checkboxData(const int& id, const bool& state, const std::string& text, UI::Window_ptr windowSelector) : id(id), state(state), text(text), windowSelector(windowSelector)
		{
		}
	} checkBoxData;


	void onCheckboxClick(int checkboxID, UIEventArgs e);
	void setVideoModeBackground();
	void setImageModeBackground();
	void setCurrentWorld(int worldID);

	void SaveRememberLogin();

	UI::CheckBox_ptr    createCheckbox(const Rectangle2D& checkBoxRectangle, checkboxData& checkBoxInformation);

	char				cPadding001[0x0080];

	ELoginState			iCurrentStateLogin;			//0x080

	ELoginState			iNextStateLogin;			//0x084

	int					iMode;						//0x088

	char				cPadding002[0x004];

	BOOL				bFailed;					//0x090

	char				cPadding003[0x78C];			//0x094

	Point2D				sLoginBoxPosition;			//0x820


	Point2D				sLoginBoxAccountPosition;	//0x828

	int					iUnk;						//0x830

	int					iLoginBoxWidth;				//0x834
	int					iLoginBoxHeight;			//0x838

	char				size[0x088];				//0x83C

	UI::Window_ptr		loginScreenSelector = NULL;
	UI::Window_ptr		pWindowSeasonalInfo = NULL;
	UI::Window_ptr		serverSelector = NULL;
	UI::Window_ptr		serverSelector2 = NULL;

	int					currentSelectedLoginRender = 0; //for image / video based login
	int					currentSelectedWorld;


	BOOL				bShowNotify = FALSE;

	Point3D				sPositionCamera;
	Point3D				sAngleCamera;

	BOOL isLoginVideo = FALSE;
};

