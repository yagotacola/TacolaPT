#pragma once

#define     MAX_SHOP_CLASS_ITEM	30  //�� Ŭ������ 30��

#define     SHOP_ROW			9  //�ӽ� ���� ������ ���� 
#define     SHOP_COL			9
	
#define 	SINALLREPAIR		1 
#define 	SINREPAIR			2    
#define 	SINSELL				3      
#define 	SINBUY				4       
#define 	SINRIGHTARROW		5
#define 	SINLEFTARROW		6  
#define     SINSHOPEXIT			7

#define 	SIN_WEAPON			1 
#define 	SIN_DEFENSE			2 
#define 	SIN_ETC				3 


struct	sMYSHOP_ITEM{
	sITEMINFO	sItem;
	int			Price;
	short       Posi[2];
	DWORD		dwTemp[3];
};

struct sMYSHOP{
	DWORD			CHAR_CODE;
	DWORD			dwTemp[6];
	sMYSHOP_ITEM	sMyShopItem[30]; //������ �޴� ������
};

struct sMYSHOP_ITEM_SERVER{ //���λ������� ������ ������ 
	DWORD CODE;
	DWORD CkSum;
	DWORD Head;
	DWORD sTime;
	DWORD Price;
	DWORD SendFlag;
	DWORD Buyer;

	DWORD Temp[4];

};

class cSHOP{


public:

	int OpenFlag;	//���� �κ��丮�� �����ֳ� �ƴѰ��� ���� �÷� 
	int UseItemFlag; // ����� - �̵� ���� ������

	int PosX;
	int PosY;

	int MatShop[10];

	int SelectShop; // 1���� ,2 �� ,3 �׿� �͵� 

	int ShopIconPosi;

	
	sITEM ShowShopItem[30];	//�ѹ��� ������ ������ �ִ� 30
	sITEM ShopItem[60]; //����� ������ 
	

	int RevWeaponCnt;
	int RevDefenseCnt;
	int RevEtcCnt;
	int MatMyShop_Button;
	
	LPDIRECT3DTEXTURE9 lpGoldEdit;

	LPDIRECT3DTEXTURE9 lpAllRepair;
	LPDIRECT3DTEXTURE9 lpRepair;

	LPDIRECT3DTEXTURE9 lpSell;
	LPDIRECT3DTEXTURE9 lpBuy;

	LPDIRECT3DTEXTURE9 lpAllRepair_D;
	LPDIRECT3DTEXTURE9 lpRepair_D;

	LPDIRECT3DTEXTURE9 lpSell_D;
	LPDIRECT3DTEXTURE9 lpBuy_D;

	LPDIRECT3DTEXTURE9 lpRightArrow;
	LPDIRECT3DTEXTURE9 lpLeftArrow;

	
	LPDIRECT3DTEXTURE9 lpTabAttack;
	LPDIRECT3DTEXTURE9 lpTabDefense;
	LPDIRECT3DTEXTURE9 lpTabEtc;

	LPDIRECT3DTEXTURE9 lpTabAttack_D;
	LPDIRECT3DTEXTURE9 lpTabDefense_D;
	LPDIRECT3DTEXTURE9 lpTabEtc_D;

	LPDIRECT3DTEXTURE9 lpExit;
	LPDIRECT3DTEXTURE9 lpGrid;

	LPDIRECT3DTEXTURE9 lpRepairAllInfo;	
	LPDIRECT3DTEXTURE9 lpRepairInfo;
	LPDIRECT3DTEXTURE9 lpDefaultRepairAll;	
	LPDIRECT3DTEXTURE9 lpDefaultRepair;

	LPDIRECT3DTEXTURE9 lpSellInfo;
	LPDIRECT3DTEXTURE9 lpBuyInfo;


	LPDIRECT3DTEXTURE9 lpTitle_Attack;
	LPDIRECT3DTEXTURE9 lpTitle_T;
	LPDIRECT3DTEXTURE9 lpTitle_Etc;
	LPDIRECT3DTEXTURE9 lpTitle_Trade;
	LPDIRECT3DTEXTURE9 lpTitle_WareHouse;

	LPDIRECT3DTEXTURE9 lpWeightEdit;

	LPDIRECT3DTEXTURE9 lpNoUseBox;

	LPDIRECT3DTEXTURE9 lpCraftItemMain;
	LPDIRECT3DTEXTURE9 lpCraftItemButton;
	LPDIRECT3DTEXTURE9 lpCraftItemButtonInfo;
	LPDIRECT3DTEXTURE9 lpTitle_CraftItem;

	// pluto ����
	LPDIRECT3DTEXTURE9 lpSmeltingItemMain;
	LPDIRECT3DTEXTURE9 lpTitle_SmeltingItem;
	LPDIRECT3DTEXTURE9 lpSmeltingItemButtonInfo;

	// pluto ����
	LPDIRECT3DTEXTURE9 lpManufactureItemMain;
	LPDIRECT3DTEXTURE9 lpTitle_ManufactureItem;
	LPDIRECT3DTEXTURE9 lpManufactureItemButtonInfo;

	// ������ - �ͽ��� ���¿� �̹��� �ε� �߰�
	LPDIRECT3DTEXTURE9 lpMResetTitle;
	LPDIRECT3DTEXTURE9 lpMResetMain;
	LPDIRECT3DTEXTURE9 lpMResetButton;
	LPDIRECT3DTEXTURE9 lpMResetButtonInfo;

	LPDIRECT3DTEXTURE9 lpSocketTitle;
	LPDIRECT3DTEXTURE9 lpSocketMain;
	LPDIRECT3DTEXTURE9 lpSocketButton;
	LPDIRECT3DTEXTURE9 lpSocketButtonInfo;

	LPDIRECT3DTEXTURE9 lpElementTitle;
	LPDIRECT3DTEXTURE9 lpElementMain;
	LPDIRECT3DTEXTURE9 lpElementButton;
	LPDIRECT3DTEXTURE9 lpElementButtonInfo;

	
	LPDIRECT3DTEXTURE9 lpTitle_Aging;
	LPDIRECT3DTEXTURE9 lpAging_Info;
	
	LPDIRECT3DTEXTURE9 lpAging_Info2;
	LPDIRECT3DTEXTURE9 lpModifyButtonInfo;
	LPDIRECT3DTEXTURE9 lpAging_btnInfo;
	LPDIRECT3DTEXTURE9 lpAging_btnInfo_;

	LPDIRECT3DTEXTURE9	lpShopMain;
	LPDIRECT3DTEXTURE9	lpShopMain2;


	//���� ����
	LPDIRECT3DTEXTURE9	lpMyShopExp;
	LPDIRECT3DTEXTURE9	lpMyShopExp_;
	LPDIRECT3DTEXTURE9	lpMyShopExp_T;
	LPDIRECT3DTEXTURE9	lpMyShopNoSale;
	LPDIRECT3DTEXTURE9	lpMyShopNoSale_;
	LPDIRECT3DTEXTURE9	lpMyShopNoSale_T;
	LPDIRECT3DTEXTURE9	lpMyShopSale;
	LPDIRECT3DTEXTURE9	lpMyShopSale_;
	LPDIRECT3DTEXTURE9	lpMyShopSale_T;
	LPDIRECT3DTEXTURE9    lpTitle_MyShop;
	LPDIRECT3DTEXTURE9    lpImage_MyShop;
	LPDIRECT3DTEXTURE9    lpMyShop_T;
	

	LPDIRECT3DTEXTURE9    MainCaravan_Arma;
	LPDIRECT3DTEXTURE9    MainCaravan_Hopy;
	LPDIRECT3DTEXTURE9    MainCaravan_Buma;

	LPDIRECT3DTEXTURE9    Caravan_Stay;
	LPDIRECT3DTEXTURE9    Caravan_Stay_;
	LPDIRECT3DTEXTURE9    Caravan_Stay_gray;

	LPDIRECT3DTEXTURE9    Caravan_Follow;
	LPDIRECT3DTEXTURE9    Caravan_Follow_;
	LPDIRECT3DTEXTURE9    Caravan_Follow_gray;

	LPDIRECT3DTEXTURE9    Caravan_Rename;
	LPDIRECT3DTEXTURE9    Caravan_Rename_;

	LPDIRECT3DTEXTURE9    Caravan_BtnOkRename;
	LPDIRECT3DTEXTURE9    Caravan_BtnOkRename_;

	LPDIRECT3DTEXTURE9    Caravan_BtnCancel;
	LPDIRECT3DTEXTURE9    Caravan_BtnCancel_;

	LPDIRECT3DTEXTURE9    Caravan_BtnUndo;
	LPDIRECT3DTEXTURE9    Caravan_BtnUndo_;

	LPDIRECT3DTEXTURE9    Caravan_RenameBox;

	LPDIRECT3DTEXTURE9    Caravan_TipFollow;
	LPDIRECT3DTEXTURE9    Caravan_TipRename;
	LPDIRECT3DTEXTURE9    Caravan_TipStay;
	
public:
	cSHOP();
	~cSHOP();

	void Init(); //Ŭ���� �ʱ�ȭ
	void Load();
	void Release();
	void Draw();
	void Close();//Ŭ���� ���� 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); 

	void CheckShopNpcState();  //NPC�� ������� üũ�Ѵ� 

	//void CopyShopItemToShow(int Index);//�������� �޾ƿ� �������� ������ ���������� �����Ѵ� 
	void CopyShopItemToShow(int Index,int Kind=0);

	int GetShopItemXY(sITEM *pItem); //�������� ��ǥ�� ���Ѵ� 

	void DrawShopText(); //���� �ؽ�Ʈ�� ǥ���Ѵ� 

	////////////////////�ƾ��� ��� �ȱ� 
	int RecvBuyItemToServer(sITEM *pItem ,int ItemCount=1); //�������� ��� 
	int SellItemToShop(sITEM *pItem,int ItemCount=1); //�ƾ����� �Ǵ� 

	int SendBuyItemToServer(sITEM *pItem , int ItemCount=1 ); //���������������� ��´� 

	void DeleteShopItem(); //������ ������ ������������ �ʱ�ȭ�Ѵ�

	int CheckHighRankItem(sITEM *pItem); //���������� üũ

	//���� �������� ����ִ� �� üũ�Ѵ�.
	int haBuyMoneyCheck(int BuyMoney);
	//���� ������ ��������� ������ ǥ�����ش�.
	int haShopItemPrice(int Money);
};

/*----------------------------------------------------------------------------*
*								���λ��� ��� Ŭ���� 
*-----------------------------------------------------------------------------*/
class cMYSHOP{
public:
	int OpenFlag;	
	sITEM MyShopItem[30];

	char szDoc[128];     //ȫ������
	char szSendDoc[128]; //������ ���� ȫ������

public:
	
	//�������� ���õɰ����� ã�´�
	int SetMyShopItem(sITEM *pItem);
	int CanSellItem(sITEM* pItem);
	int GetEmptyArea(sITEM* pItem, POINT* EmptyPos);

	//�����Ѵ�
	int LastSetMyShopItem(sITEM *pItem);

	//�κ��������� ����Ѵ�
	int SetShopItemToInven(sITEM *pItem);

	//������ ����� �������� ã�´�
	int SearchShopItemToInven(sITEM *pItem);

	//�������� ������ ������ 
	int SendMyShopItem(); 

	//�������� ���ſ�û�� ���� �������� �޴´�
	int RecvMyShopItem( DWORD dwCharCode , sMYSHOP_ITEM_SERVER *lpShopItem );

	//�ڽ��� ������ �ִ� �ݾ��� �����Ѵ�
	int GetLimitMoney(int Money);

	//������ ���ȸ��� ������ �ݴ´�
	int AutoCloseShop();

	//���λ����� ���� ���ؿ´�
	int GetTotalMyShopItemMoney();

};
/*----------------------------------------------------------------------------*
*								���λ��� Ŭ���� 
*-----------------------------------------------------------------------------*/
class cCHARSHOP{
public:
	int OpenFlag;	

public:
	sITEM CharShopItem[30];
	
	//�������� �޴´�
	int RecvShopItem(sMYSHOP *sMyShop);

	//���� �������� ã�´�
	int SearchMyShopItem(DWORD CODE ,DWORD Head , DWORD CheckSum);

	//���λ��������� �������� �κ��丮�� �����Ѵ�
	int SetCharShopItemToInven(sITEMINFO *pItem_Info);

	//���λ������� �������� ���
	int BuyItem(int Index);

};

extern cSHOP cShop;

extern int sinShopKind;  //���� ������ ����  1  ���� 2 ��� 3 ���� (defalt �� ����)

extern int TalkNpcState; //���� ���� NPC�� �Բ� ������� 

extern int ShopGoldEdit[2][4];

extern int ShopArrowPosi; //���� ȭ��ǥ ���� 

extern int BuyItemServerFlag; //�������� ������ �춧 �޼����� ���������� ������� 

extern cMYSHOP cMyShop;
extern cCHARSHOP cCharShop;

extern sMYSHOP     sMyShop;       //������ MyShop ����ü
extern sMYSHOP     sRecvMyShop;   //�޴� MyShop ����ü
extern int MyShopSendButton;

extern int MyShopExpBox;
extern int MyShopItemSellMoney2;
extern sMYSHOP_ITEM_SERVER sMyShop_Server;
extern sITEMINFO MyShopPotion;
extern int MyShopItemCancelIndex[2];
