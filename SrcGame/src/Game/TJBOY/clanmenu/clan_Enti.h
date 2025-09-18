#pragma once
#ifndef __CLAN_ENTI_HPP__
#define __CLAN_ENTI_HPP__

//#define CLANHELPICON_NUM_ENIT		100

class CLANEntity
{
public:
	int				life;	
	CLANEntity      *parent;


public:
	CLANEntity();
	~CLANEntity();

	virtual int Init() ;
	virtual int Clear();

	//***************************************************************************************
	virtual void Main();
	virtual void RenderMain();

	//***************************************************************************************
	void	setParent(CLANEntity      *p){parent = p;}
	void			Kill()			{ life = 0; };
	int				IsDead()		{ return(life); };

	//virtual void main();
	virtual void Draw();
	//***************************************************************************************
	virtual void menuInit(int num);

	//***************************************************************************************
	void Draw_C_Text(char *str, int x, int y, int sw=0);
	void Draw_C_Text2(char *str, int x, int y, int sw=0); //Ŭ���� �������� ������(red)����
	void Draw_C_Text3(char *str, int x, int y, int sw=0);  //ä�ø���Ʈ���� ����Ʈ ���(green)����

//��öȣ
//#ifdef PARKMENU
	void Draw_C_TextPark(char *str, int x, int y, int RedColor, int GreenColor, int BlueColor, int sw);

	


	//***************************************************************************************
	//int  menuSu;
	//RECT menuPos[30];		//�޴�����.
	int  chkMenu(int x, int y, RECT *r);
	int  chkeckMenuN();



	//data �Ľ� ========================================
	void ParsingIsClanMember(char* data);
	void ParsingIsClanMember2(char *data);
	int chk_readStrBuf(char *cmd, char *readbuf, char *retBuf);
	void ParsingData(char* cmd, char* data, char* save);
	void ParsingMakeClanMoney(char* data,int* money);


	void ParsigClanWon(char* data);
	
	void ParsingClanWonStrLen();

	void LoadToFile();
	

	//���� ���� �Լ���================
	void LoadHelp(char *help);
	void DestroyClanHelpIcon();
	void LoadHelpImage();
	BOOL ReadClanHelpScr(char *filename);
	void ReMoveClanWon(char *src);
	//void Updatecldata();
	void WriteMyClanInfo();
	int CheckMark(BOOL bFlag);

	void CheckClanExp(char* byte); //Ŭ�� ���� ���� ����



	

	//�Ʒ� ���ҽ� �ε� Ŭ���� �Լ���
	void Load();
	void Load2();

	virtual void Close();
	void copy_LoadResource(CLANEntity *copyDest);
	void copy_LoadResource2(CLANEntity *copyDest);
	//��ũ �Ѱ��ֱ�
	inline void SetBase(CLANEntity *copyDest){parent = copyDest;}

	#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��
	#else
	inline HBITMAP GetClanMark(){return parent->hMark;}
	#endif

	//PartyInterface ���ҽ�..
	#ifdef USE_PROSTONTALE		//=========== �������ϼҽ��ΰ��
	
	int	MatPartyBackGround;		//���
	int	hBoxCorner,hBoxLine;	//�ڽ��׸���
	int	hBox1,hBox2,hBox3,hBox4,hBox6,hBox7,hBox8,hBox9; //�ڽ��׸���
	int	hScl_Bar_tj;
	int	hScl_icon_tj;
	int   hLine;
	

	inline LPDIRECT3DTEXTURE9 GetClanMark(){return parent->hMark;}


	LPDIRECT3DTEXTURE9	hBt_Help;
	LPDIRECT3DTEXTURE9	hMark_box;
	LPDIRECT3DTEXTURE9	hOk_Gray,hOk_Yellow; //Ȯ��
	LPDIRECT3DTEXTURE9	hCancel_Gray,hCancel_Yellow; //���
	LPDIRECT3DTEXTURE9	hYes_Gray,hYes_Yellow; // ��
	LPDIRECT3DTEXTURE9	hNo_Gray,hNo_Yellow; //�ƴϿ�

	LPDIRECT3DTEXTURE9	hMark,hClanName;
	LPDIRECT3DTEXTURE9	hSecession[2];
	LPDIRECT3DTEXTURE9	hClose[2];
	LPDIRECT3DTEXTURE9	hIcon;
	LPDIRECT3DTEXTURE9	hIcon_Click;
	LPDIRECT3DTEXTURE9	hHelp1;
	LPDIRECT3DTEXTURE9	hClinetMark;
	LPDIRECT3DTEXTURE9	hServerMark;
	LPDIRECT3DTEXTURE9	hWareHouse[2]; //���콺�� ���� �ö������
	LPDIRECT3DTEXTURE9	hWHRight[2];
	LPDIRECT3DTEXTURE9	hClanMark[2];
	LPDIRECT3DTEXTURE9	hRemove[2];
	LPDIRECT3DTEXTURE9	hClanRelease[2];
	LPDIRECT3DTEXTURE9	hHelp[2];
	LPDIRECT3DTEXTURE9	hOut[2];

	LPDIRECT3DTEXTURE9	hButton_Box;
	LPDIRECT3DTEXTURE9	hClanTitle;
	LPDIRECT3DTEXTURE9	hRemoveToMenu[2];
	LPDIRECT3DTEXTURE9	hScl_Bar;
	LPDIRECT3DTEXTURE9	hScl_icon;
	LPDIRECT3DTEXTURE9	hClanHelpIcon[CLANHELPICON_NUM][4];
	LPDIRECT3DTEXTURE9    hClanNameInput;

	LPDIRECT3DTEXTURE9   hTxt_Remove[2]; //�߹�
	LPDIRECT3DTEXTURE9   hTxt_Release[2]; //��ü
	LPDIRECT3DTEXTURE9   hTxt_Mark[2]; //��ũ
	LPDIRECT3DTEXTURE9   hTxt_Help[2]; //����
	LPDIRECT3DTEXTURE9   hTxt_Secession[2];//Ż��
	LPDIRECT3DTEXTURE9   hTxt_LeaveClan[2];//����
	LPDIRECT3DTEXTURE9   hTxt_SubChip[2];//��Ŭ��Ĩ
	LPDIRECT3DTEXTURE9   hSubChip;

	

	
	char		szHelpMsg1[HELPMSG_MAX];
	char		szErrorMsg[256];

	#else

	HBITMAP	hLine;

	HBITMAP	hBox1,hBox2,hBox3,hBox4,hBox6,hBox7,hBox8,hBox9;
	HBITMAP	MatPartyBackGround;
	HBITMAP	hMark_box;
	HBITMAP	hBt_Help;
	
	HBITMAP	hOk_Gray,hOk_Yellow; //Ȯ��
	HBITMAP	hCancel_Gray,hCancel_Yellow; //���
	HBITMAP	hYes_Gray,hYes_Yellow; // ��
	HBITMAP	hNo_Gray,hNo_Yellow; //�ƴϿ�

	HBITMAP	hMark,hClanName;
	HBITMAP	hSecession[2];
	HBITMAP	hClose[2];
	HBITMAP	hIcon;
	HBITMAP   hIcon_Click;
	HBITMAP	hHelp1;
	HBITMAP	hClinetMark;
	HBITMAP	hServerMark;
	HBITMAP	hWareHouse[2]; //���콺�� ���� �ö������
	HBITMAP	hWHRight[2];
	HBITMAP	hClanMark[2];
	HBITMAP	hRemove[2];
	HBITMAP	hClanRelease[2];
	HBITMAP	hHelp[2];
	HBITMAP	hOut[2];
	HBITMAP	hButton_Box;
	HBITMAP	hClanTitle;
	HBITMAP	hRemoveToMenu[2];
	HBITMAP	hScl_Bar;
	HBITMAP	hScl_icon;
	HBITMAP   hClanHelpIcon[CLANHELPICON_NUM][4]; //������ �迭�� ó��

	HBITMAP   hTxt_Remove[2]; //�߹�
	HBITMAP   hTxt_Release[2]; //��ü
	HBITMAP   hTxt_Mark[2]; //��ũ
	HBITMAP   hTxt_Help[2]; //����
	HBITMAP   hTxt_Secession[2]; //Ż��
	HBITMAP   hTxt_LeaveClan[2];//����
	HBITMAP   hTxt_SubChip[2];//��Ŭ��Ĩ
	HBITMAP   hSubChip;

	HBITMAP    hClanNameInput;

	HWND		m_hClanName;	
	char		szErrorMsg[256];

	#endif
	BOOL bImageDown;
};

#endif //__CLAN_ENTI_HPP__





#if defined (CLAN_EITI_CPP)


	class CLANEntity  cBaseMenu;

#else

	extern class CLANEntity  cBaseMenu;


#endif




