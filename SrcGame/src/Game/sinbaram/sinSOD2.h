#pragma once

#include <vector>
#include <string>
#include <algorithm>

#define SIN_CLANSKILL_ABSORB			1
#define SIN_CLANSKILL_DAMAGE			2
#define SIN_CLANSKILL_EVASION			3

//SOD XXSTR
#define SIN_SODSKILL_GOLD			1
#define SIN_SODSKILL_SILVER			2
#define SIN_SODSKILL_BRONZE			3

#define SIN_GURAD_CRISTAL_ICE		    1
#define SIN_GURAD_CRISTAL_LIGHTNING		2
#define SIN_GURAD_CRISTAL_FIRE			3

#define SIN_CASTLEITEMSKILL_S_INVU         1    //���� ��ũ��
#define SIN_CASTLEITEMSKILL_S_CRITICAL     2    //ũ��Ƽ�ý�ũ��
#define SIN_CASTLEITEMSKILL_S_EVASION      3    //�߰� ȸ�� ��ũ��
#define SIN_CASTLEITEMSKILL_S_P_LIFE       4    
#define SIN_CASTLEITEMSKILL_S_RES          5    

#define SIN_CASTLEITEMSKILL_R_FIRE_C       6    //���̾� ũ����Ż ���׼�
#define SIN_CASTLEITEMSKILL_R_ICE_C        7    //���̽� ũ����Ż ��Ȳ��
#define SIN_CASTLEITEMSKILL_R_LIGHTING_C   8    //����Ʈ�� ũ����Ż ���׼�
#define SIN_CASTLEITEMSKILL_A_FIGHTER      9    //�������� ���ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_MECHANICIAN  10   //���ī�ϼ� ���ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_PIKEMAN      11   //������ũ�ǰ��ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_ARCHER       12   //����� ���ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_KNIGHT       13   //�볪��Ʈ ���ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_ATALANTA     14   //���Ʋ��Ÿ ���ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_MAGICIAN     15   //������� ���ݷ� ��ȭ��
#define SIN_CASTLEITEMSKILL_A_PRIESTESS    16   //��������Ƽ�� ���ݷ� ��ȭ��

/*----------------------------------------------------------------------------*
*							������ Ŭ���޴�
*-----------------------------------------------------------------------------*/	
class cSINSIEGE{
//private:
public:
	int            TaxRate;				    //����
	int            TotalTax;				//���� ���� //�ؿܼ���
	int			   ExpectedTotalTax;		//����� ���� ���Ǵ� ���� //�ؿ�
	int            Price;					//���� �ݾ�����
public:
	short		   TowerType[6];			//Ÿ�� Ÿ��
	int			   ClanSkill;				//Ŭ�� ��ų
	unsigned char  MercenaryNum[4];			//�뺴 ���� 0 -> 255
	int            TowerTypeDraw[6][2];	    //������
	int            MercenaryNumDraw;		//�뺴���� 


public:
	cSINSIEGE(){};
	~cSINSIEGE(){};

	int GetTaxRate();				    //���� ��������
	int	SetTaxRate(int TempTaxRate);	//���� ����

	int GetTotalTax();						//������� �Ⱦ���� ��������
	int cSINSIEGE::GetTaxMoney(int Money );	//�ݾ��� ã�´�


}; 

/*----------------------------------------------------------------------------*
*							MessageBox
*-----------------------------------------------------------------------------*/	
struct sinMESSAGEBOX_NEW{
	int Flag;
	int PosiX;
	int PosiY;
	int SizeW;
	int SizeH;


	//////////////Button
	int ButtonIndex;
	int ButtonNum;
	int ButtonintPosiX[3]; //�ϴ� 5���� ��Ƴ��´�
	int ButtonintPosiY[3]; //�ϴ� 5���� ��Ƴ��´�
	RECT ButtonRect[3];

};

/*----------------------------------------------------------------------------*
*							cHELPPET 	class		
*-----------------------------------------------------------------------------*/	
class cSINSOD2{

public:
	int UserType; //1 �Ϲ����� , 2 Ŭ���� ,3 Ŭ��������
	int BoxIndex; //���� �����ִ� ������
	char sinSod2Buff[65536];
	LPDIRECT3DTEXTURE9 ClanMark[10];
	LPDIRECT3DTEXTURE9 ClanMark_32;
	int  ClanMark_32Time;
	int  ClanMark_32Index;
	int  ClanMarkNum[10];
	int  ClanMarkIndex[10];
	int  ClanMarkLoadTime[10];
	int  TotalEMoney;
	int  Tax;
	int  TotalMoney;
	int  ClanImageNum;
	vector<string> sinClanRank;
	char szClanName[32];
	vector<string> sinClanMessage;

	int SendClanMoneyFlag; //�ߺ����� �޼����� �������ʰ� �÷��� �ش�
	int RecvRemainMoney;
	char szClanMaster[24];
	int ClanMasterMessageBoxFlag; //â�� �ߺ����ζ��� �÷����ش�
	int ClanRankFlag; //Ŭ����ũ �޼����� �ѹ��� ������

	//�����ϴ� �ϳ���
	DWORD ClanMoney;
	
public:
	cSINSOD2(){};
	~cSINSOD2(){};

	void Init(); //Ŭ���� �ʱ�ȭ
	void Load();
	void Release();
	void Draw();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);
	void DrawText();
	void Close();//Ŭ���� ���� 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); //Ű üũ 

	void ShowSod2MessageBox(); //�޼��� �ڽ� �����ֱ�

	void CloseSod2MessageBox(); //�޼��� �ڽ� �ݱ�

	void RecvWebDaTa();

	void RecvClanRank(char *szBuff);

	//Space�������� String�� ����
	vector<string> Split_ClanRankDaTa(const string& s);

	//String�� ���̸� �������� String�� ����
	vector<string> Split_ClanMessage(const string& s , const int Len[]);

	//�� DB���� �޼����� �޴´�
	int RecvWebData(int Index ,const string& s); //1���� 2 Ŭ������Ʈ

	//�� DB���� ���� ����Ÿ�� �����Ѵ�
	vector<string> cSINSOD2::Split_Sod2DaTa(const string& s);

};

//�޼��� �ڽ�
int ShowSinMessageBox_New(int PosiX , int PosiY , int SizeW , int SizeH , RECT *rect ,int ButtonNum=3);

//�������� ���� �޴´�
int sinRecvClanMoney(int RemainMoney , int GetMoney);



//////////////////// ������ //////////////////////////////
int sinShowSeigeMessageBox();
int RecvSeigeWebData(int Index , char *string);

/*----------------------------------------------------------------------------*
*						  ������ 
*-----------------------------------------------------------------------------*/	
//�ӽ� ����
#define HASIEGE_MODE   //������ ��������  

//������ ���� ����
#define HASIEGE_TAXRATES    1  //���� ����
#define HASIEGE_DEFENSE     2  //��� ����


//Ŭ�� ����
#define HACLAN_MAX    10   //Ŭ������

//Ŭ�� ������ ���� ����ü
struct sHACLANDATA{
	int		Flag;         //Ŭ�� �÷�
	int		Score;        //Ŭ�� ����
	int     ClanInfoNum;  //���忡 ǥ�õ� ��ǥ   
	char    ClanName[40]; //Ŭ���̸�

	DWORD   CLANCODE;     //Ŭ�� �ڵ�

	LPDIRECT3DTEXTURE9 lpClanMark;  //Ŭ�� ��ũ	   
};

class cHASIEGE{

public:
    /*---�������� ȣ��Ŵ� �Լ���----*/
	int   ShowSiegeMenu(smTRANS_BLESSCASTLE *);    //�����޴��� ����.
	int   ShowSiegeScore(rsUSER_LIST_TOP10 *);     //���� Ŭ������ ������ ǥ���Ѵ�
	int   ShowExitMessage();         //���� �޼���
	int   ShowPlayTime(int);        //���� �޼���

	/*---Ŭ�� ��ų-----*/
	int   SetClanSkill(int);			  //Ŭ����ų�� ������ �����Ѵ�.
	int   SetCastleItemSkill(int);	      //������ ������ ��뽺ų

	int   SendServerSiegeData();          //������ ����Ÿ�� ������.
	int   SetCastleInit();				  //�ʱ�ȭ �Ѵ�.   
	int   SetCastleMenuInit();            //�ʱ�ȭ �Ұ��� ���⿡�� �� ó�����ش�.  

	int	  ShowPickUserKillPoint(int x,int y,int KillCount);

	//�������� �����Ű��.
	int   ShowCastlePlayMovie(char *szPath,char *TitleName,int Option);

	BOOL bCaptureScreen = FALSE;
	DWORD dwTickScreen = 0;
public:
	
	cHASIEGE();
	~cHASIEGE();
	//�ʿ��Ѱ͸� �׽�Ʈ
	void init();
	void Main();
	void Draw();
	void KeyDown(); //Ű üũ
	void Release();
	void LButtonDown(int x , int y);
	void LButtonUp(int x,int y);
	void DrawText();
	void ImageLoad();
	
public:
	LPDIRECT3DTEXTURE9  lpSiegeTax;             //��������
	LPDIRECT3DTEXTURE9  lpSiegeDefense;         //������
	LPDIRECT3DTEXTURE9  lpCastleButton;         //������
	LPDIRECT3DTEXTURE9  lpMercenary;            //�뺴����


	LPDIRECT3DTEXTURE9  lpDefenseButton[2];     //��/�뺴���� ��ư
	LPDIRECT3DTEXTURE9  lpTax_Ok[2];            //��ã�� Ȯ�ι�ư
	
	LPDIRECT3DTEXTURE9  lpSiegeDefeseIcon_[3];     //���� ���� ������ �׷���
	LPDIRECT3DTEXTURE9  lpSiegeMercenaryIcon_[3];  //�뺴 ������ �׷���


	LPDIRECT3DTEXTURE9  lpSiegeDefeseIcon[3];    //���� ���� ������
	LPDIRECT3DTEXTURE9  lpSiegeClanskillIcon[3]; //Ŭ�� ��ų ������
	LPDIRECT3DTEXTURE9  lpSiegeMercenaryIcon[3]; //�뺴������

	LPDIRECT3DTEXTURE9  lpSiegeTaxButton;        //�������� ���ι�ư
	LPDIRECT3DTEXTURE9  lpSiegeDefenseButton;    //���� ���ι�ư
	LPDIRECT3DTEXTURE9  lpSiegeOkButton;         //Ȯ�� ��ư 
	LPDIRECT3DTEXTURE9  lpSiegeCancelButton;     //��ҹ�ư

	LPDIRECT3DTEXTURE9  lpCastleIcon[6];         //���� ���� Ȱ��ȭ ��ư
	LPDIRECT3DTEXTURE9  lpTaxScroll[2];          //��ũ�� ��ư
	LPDIRECT3DTEXTURE9  lpTaxGraph;              //��ũ��
	LPDIRECT3DTEXTURE9  lpDefenseRect[6];        //���� Ȱ��ȭ

	LPDIRECT3DTEXTURE9  lpTwoerImage;

	//
	LPDIRECT3DTEXTURE9 haPlayerButton_G[3];
	LPDIRECT3DTEXTURE9 haPlayerButton[3];
	LPDIRECT3DTEXTURE9 haPlayerButtonBox[3];
	LPDIRECT3DTEXTURE9 haPlayerButtonDown[3];
};



//extern ���� ����
extern cHASIEGE chaSiege;
extern int haSiegeMenuFlag;        //�޴� �÷�
extern int haMercenrayIndex;       //�뺴 ������ �ε���
extern int HaTestMoney;            //�ӽ� �����Ѿ�
extern int haMercenrayMoney[3];    //�뺴���� �Ӵ�
extern int haSiegeBoardFlag;    
extern int haSendTowerIndex;      
extern int haTowerMoney; 
extern int haMovieFlag;

//////////////////// ������  end //////////////////////////////
extern cSINSOD2 cSinSod2;
extern sinMESSAGEBOX_NEW sinMessageBox_New;
extern LPDIRECT3DTEXTURE9	lpbltr_Button_OK;
extern LPDIRECT3DTEXTURE9	lpbltr_Button_OK_G;
extern int haCastleSkillUseFlag;
extern cSINSIEGE cSinSiege;
