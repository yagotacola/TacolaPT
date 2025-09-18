#pragma once

#include <Windows.h>
#include "smLib3d/smType.h"

//��a���� ����A�� ����A��A��
struct smCONFIG {
	char ratio[5];
	bool bAdjustWindow;
	bool bNoLag;
	bool CameraInvRot;
	int Width;
	int Height;
	bool bIsWidescreen;
	bool hpWarning;
	bool glow;
	bool showDamage;

	int	WinMode;					//E����e ������a
	POINT	ScreenSize;					//E����e C����o���
	DWORD	ScreenColorBit;				//��o��o ��n����


	int		TextureQuality;				//A������AA C��Au
	int		BGM_Mode;					//��e�Ʃ� A����C ��c��e 
	int		NetworkQuality;				//�������碯oA�� C��Au
	int		WeatherSwitch;				// pluto C����U ��n

	char	szFile_BackGround[2][64];	//��e�Ʃ� E����e
	char	szFile_Menu[64];			//�������� E����e
	char	szFile_Player[64];			// AOAI�Ʃ�
	POINT	Posi_Player;
	char	szFile_Enemy[64];			// ������U����
	POINT	Posi_Enemy;

	char	szFile_Stage[64];				//AoCu
	POINT	Posi_Stage;						//AoCu ��AAU A��A��
	char	szFile_StageObject[100][64];	//AoCu���� ��A��o�Ƣ���A ��A��eA�ר���
	int		StageObjCnt;					//AoCu ��A��eA�ר��� �Ʃ���o

	//######################################################################################
	//AU ���� AU : ��A ���� ����
	int		IsStageAniObject[100];
	//######################################################################################

	//��A��O ��E ��O��? ��A�ҡע��� Au��e��E
	int		MapBright;						//��a��a
	int		MapContrast;					//������i���
	POINT3D	MapLightVector;					//����AI

	char	szServerIP[32];					//������oAO��O
	DWORD	dwServerPort;					//������o��������
	char	szDataServerIP[32];				//���AIA�� ������oAO��O
	DWORD	dwDataServerPort;				//���AIA�� ������o��������
	char	szUserServerIP[32];				//A?Au ������oAO��O
	DWORD	dwUserServerPort;				//A?Au ������o��������
	char	szExtendServerIP[32];			//E��Aa ������oAO��O
	DWORD	dwExtendServerPort;				//E��Aa ������o��������

	DWORD	DebugMode;						//�쩣��o��e ������a ����A��


	char	szCmdOpenMonster[CONFIG_KEY_MONSTER_MAX][32];		//��y������AA�� ��o����AI AI����
	int		CmdMonsterCount;

	int CameraSight;

	smCONFIG()
	{
		bAdjustWindow = false;
		bNoLag = false;
		Width = 0;
		Height = 0;
		bIsWidescreen = false;
		CameraSight = 0;
		CameraInvRot = false;
		hpWarning = false;
		glow = false;
		showDamage = false;
		ZeroMemory(ratio, sizeof(ratio));
		ZeroMemory(szFile_BackGround, sizeof(szFile_BackGround));
		ZeroMemory(szFile_Menu, sizeof(szFile_Menu));
		ZeroMemory(szFile_Player, sizeof(szFile_Player));
		Posi_Player.x = 0;
		Posi_Player.y = 0;
		ZeroMemory(szFile_Enemy, sizeof(szFile_Enemy));
		Posi_Enemy.x = 0;
		Posi_Enemy.y = 0;
		ZeroMemory(szFile_Stage, sizeof(szFile_Stage));
		Posi_Stage.x = 0;
		Posi_Stage.y = 0;
		ZeroMemory(szFile_StageObject, sizeof(szFile_StageObject));
		StageObjCnt = 0;
		ZeroMemory(IsStageAniObject, sizeof(IsStageAniObject));
		MapBright = DEFAULT_BRIGHT;
		MapContrast = DEFAULT_CONTRAST;
		MapLightVector.x = fONE;
		MapLightVector.y = -fONE;
		MapLightVector.z = fONE / 2;
		ZeroMemory(IsStageAniObject, sizeof(szCmdOpenMonster));
		CmdMonsterCount = 0;
	}
};
