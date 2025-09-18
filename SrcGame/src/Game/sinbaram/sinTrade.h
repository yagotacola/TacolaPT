#pragma once

#define MAX_TRADE_ITEM			20
#define MAX_CRAFTITEM_INFO		300
#define MAX_AGINGITEM_INFO		100
#define MAX_MAKEITEM_INFO		100

#define T_SET_BOX				0
#define T_MONEY_POSI			1
#define T_MONEY_TEXT_POSI		2
#define T_WEIGHT_TEXT_POSI		3
#define T_CHECK_POSI			4
#define T_CLOSE_POSI			5
#define T_TRADE_CLOSE_POSI		6
#define T_COIN_POSI				7
#define T_COIN_TEXT_POSI		8

#define MAX_SHELTOM				30
#define MAX_AGING				24 // N�vel do Aging aqui m�ximo
#define MAX_RUNE				14
#define MAX_RECIPE_KIND			11
#define MAX_RECIPE_ITEM			60
#define MAX_HANDMADEITEM		176

#define MAX_SEEL_COUNT			12
#define MAX_SOCKET				5
#define MAX_ELEMENT				6

struct sTRADE{
	sITEM TradeItem[MAX_TRADE_ITEM];
	int Money;	
	int Coin;
	int Weight;
	int CheckFlag;
	int CheckMoney;
};

///////â�� ����ü 
struct sWAREHOUSE{
	sITEM WareHouseItem[100]; 
	int Money;
	short Weight[2];
	int BuyAreaCount; //â�� �󸶸�ŭ ��ԵǾ��� 
	int FakeMoney;


};

struct sCARAVAN 
{
	sITEM CaravanItem[100];
	int Money;
	short Weight[2];
	int BuyAreaCount;
	int FakeMoney;
};

struct sCRAFTITEM{
	sITEM CraftItem[15];
	int   SheltomIndex[12];

};

struct sCRAFTITEM_SERVER{
	int size, code;
	int DocIndex;
	int Result;
	sITEM DesCraftItem;
	DWORD SheltomCode[12];
	DWORD Head[12];
	DWORD CheckSum[12];
	int  Index;
	int  Money;

	DWORD A_StoneItemCode;
	DWORD A_StoneHead;
	DWORD A_StoneCheckSum;
};

struct sCRAFTITEM_INFO{
	int iMixType;
	DWORD MainItemCode[8];
	int AddItem[15];
	int PlusElementCode[8];
	float AddElement[8];
	int ElementKind[8];
	char Doc[256];
};


struct sMIXTURE_RESET_ITEM
{
	sITEM	MixtureResetItem[2];

	sMIXTURE_RESET_ITEM()
	{
		ZeroMemory(&MixtureResetItem, sizeof(MixtureResetItem));
	}
};

struct sMIXTURE_RESET_ITEM_SERVER
{
	int		size, code;
	int		DocIndex;
	int		Result;
	int		Index;

	sITEM	DesMixtureResetItem;

	DWORD	dwMixtureResetStoneItemCode;
	DWORD	dwMixtureResetStoneHead;
	DWORD	dwMixtureResetStoneCheckSum;

	sMIXTURE_RESET_ITEM_SERVER()
	{
		size = 0;
		code = 0;
		DocIndex = 0;
		Result = 0;
		Index = 0;

		dwMixtureResetStoneItemCode = 0;
		dwMixtureResetStoneHead = 0;
		dwMixtureResetStoneCheckSum = 0;
	}

};

struct ELEMENT_ITEM_SERVER
{
	int		size, code;
	int		Result;
	int		Index;
	int		Money;
	sITEM	DesItem;
	DWORD	SheltomCode[5];
	DWORD	Head[5];
	DWORD	CheckSum[5];
};

struct SOCKET_ITEM_SERVER
{
	int size, code;
	int Result;
	int Index;
	int Money;
	sITEM DesItem;
	DWORD SheltomCode[4];
	DWORD Head[4];
	DWORD CheckSum[4];
};

struct sAGINGITEM{
	sITEM AgingItem[15];
	int   SheltomIndex[12];
	int   AgingOkFlag;

	sAGINGITEM()
	{
		ZeroMemory(&AgingItem, sizeof(AgingItem));
	}

};

struct sAGINGITEM_INFO{
	DWORD MainItemCode;		//������ ������ �ڵ� 
	int PlusElementCode[8];	//�߰��� ���� 
	float AddElement[8];	//�߰��� ��ġ 
	int ElementKind[8];		//��ġ�� ���� (+ % �Ҽ�)
	char Doc[128];			//���� 

	sAGINGITEM_INFO()
	{
		MainItemCode = 0;
		ZeroMemory(&PlusElementCode, sizeof(PlusElementCode));
		ZeroMemory(&AddElement, sizeof(AddElement));
		ZeroMemory(&ElementKind, sizeof(ElementKind));
		ZeroMemory(Doc, sizeof(Doc));
	}

};

///// MakeItem
struct sMAKEITEM_INFO{
	DWORD CODE[15];			//���յǴ� �������� �ڵ�
	DWORD Result_CODE;		//���յ� ������ �ڵ� 

};

struct sPOSTBOX_ITEM{
	char	szName[64];
	DWORD	CODE;

	sPOSTBOX_ITEM()
	{
		ZeroMemory(szName, sizeof(szName));
		CODE = 0;
	}
};

//������ �籸�� ����ü
struct sRECON_ITEM{
	DWORD  dwCODE;    //..
	int	   iLevel[2]; //min~max
	int	   iCount;    //�ʿ� ����
	int    iPrice;    //����?
};

// pluto ����
struct SSmeltingItem
{
	sITEM SmeltingItem[5];	//���յ� ������ 
	int   SheltomIndex[12];
};

// pluto ����
struct sSMELTINGITEM_SERVER
{
	int size, code;
	int DocIndex;
	int Result;
	sITEM DesSmeltingItem;
	DWORD SmeltingCode[5];
	DWORD Head[5];
	DWORD CheckSum[5];
	int  Index;
	int  Money;

	DWORD A_StoneItemCode;
	DWORD A_StoneHead;
	DWORD A_StoneCheckSum;
};

// pluto ����
struct SManufactureItem
{
	sITEM	ManufactureItem[4];
	int		RuneIndex[12];
};

// pluto ����
struct SManufactureItem_Server
{
	int size, code;
	int DocIndex;
	int Result;
	sITEM DesManufactureItem;
	DWORD RuneCode[4];
	DWORD Head[4];
	DWORD CheckSum[4];
	int  Index;
	int  Money;

	DWORD A_StoneItemCode;
	DWORD A_StoneHead;
	DWORD A_StoneCheckSum;
};

// pluto ����
struct SManufacture_Rune
{
	int RecipeCode;
	int NeedRuneIndex[3];
};

// pluto ���� �� ���� ���� ������ �ش� ������ �ڵ� �߻�
struct SManufacture_CreateItemCode
{
	DWORD RecipeKind[2];
	DWORD CheckRuneCode[8][3];
	DWORD CreateItemCode[2][8];
};

// pluto ���� ������ ����, ���� ����
struct SManufacture_ResultItemInfo
{
	DWORD ItemCode;
	int	Weight;
	int Price;
	char ItemName[32];
};

// pluto ���� ������ ����, ���� ����  // �庰 - ���� 160(144) // �庰 - ���������� ȥ
struct SManufacture_ResultItemInfo_Server
{
	smTRANS_COMMAND		smTransCommand;
	DWORD ItemCode[MAX_HANDMADEITEM];
	int Weight[MAX_HANDMADEITEM];
	int Price[MAX_HANDMADEITEM];
	char ItemName[MAX_HANDMADEITEM][32];
};
/*----------------------------------------------------------------------------*
*							����¡  ������ Ŭ���� 
*-----------------------------------------------------------------------------*/
class cAGING{
public:

	int OpenFlag;
	int AgingItemCheckSum;
	LPDIRECT3DTEXTURE9	lpGraySheltom[MAX_SHELTOM];

public:
	//����¡ �� ���Ŵ� ����   //1.����¡���� 
	int  AginStoneKind;         //2.���� ����
								//����� - 3.���� ���� ����
								//����� - 4.���� ����¡ ����
                                //���� �߰���
	
public:

	int  AgingItem(int MakeItemFlag =0);		//�������� ����¡�Ѵ� 
	int  CancelAgingItem(int Flag=0);	//����¡ �������� ĵ���Ѵ� 
	int  CheckItem(sITEM *pItem);		//����¡�� �������� üũ�Ѵ� 
	int  CheckAgingItemOk(); //����¡�� �Ҽ��ִ����� üũ�Ѵ� 

	int  SetAgingItemAreaCheck(sITEM *pItem );	//����¡ �������� ���õ� ������ üũ�Ѵ� 
	
	///////////// ����¡ �������� ���ۿ��θ� ������ 
	int  CheckAgingData();

	/////////// �������� �������� ����¡�Ѵ�
	int sinSendAgingItem();
	int sinRecvAgingItem(sCRAFTITEM_SERVER *pCraftItem_Server);
	int sinRecvAgingItemResult(sCRAFTITEM_SERVER *pCraftItem_Server);

	//new functions aging xxstr
	bool isSheltomAreaEmpty(sITEM* Item, int Area);
	bool isAgeableItem(sITEM * pItem);
	bool isItemAreaEmpty();
	bool isStoneAreaEmpty();

};

/*----------------------------------------------------------------------------*
*						������ - �ͽ��� ���� Ŭ���� 
*-----------------------------------------------------------------------------*/
class cMIXTURERESET
{
public:

	int	OpenFlag;					// �����ִ°�?
	int	MixtureResetItemCheckSum;	// �˻��
	int	HaveMixtureResetStone;		// �ͽ��� ���� ������ �ִ°�?

public:

	int	SetMixtureItemResetAreaCheck(sITEM *pItem);		// �ͽ��� ���µ� �������� ������ üũ�Ѵ�.
	int PickUpMixtureResetItem( int x, int y, int PickUpFlag = 0, int Kind = 0 );	// �ͽ��� ���� �������� �����Ѵ�.
	int LastSetMixtureResetItem( sITEM *pItem, int kind );	// �ͽ��� ���¿� �ʿ��� ������ ���´�
	int	CancelMixtureItemReset(int Flag=0);		// �ͽ��� ������ ����ϸ� â�� �ݴ´�.
	int	CheckMixtureResetItemForm();	// ������ üũ?
	int	ReformMixtureResetItem();		// ������ �ٽ� üũ?


	bool cMIXTURERESET::isStoneOkay(sITEM* pItem);
	bool cMIXTURERESET::isItemOkay(sITEM* pItem);
	bool cMIXTURERESET::isEmpty(int Index);

	int	MixtureItemReset();	
	int	CheckItem();
	int	CheckMixtureItemResetOk();
	int	CheckMixtureItemData();	



	int	sinSendMixtureItemReset();			// ������ �ͽ��ĸ����� �������� ����
	int	sinRecvMixtureItemReset(sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem);		// �ͽ��� ���µ� �������� Recv�� ������ ����
	int	sinRecvMixtureItemResetResult(sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem_Server);
};

// pluto
/*----------------------------------------------------------------------------*
*								������ ���� Ŭ���� 
*-----------------------------------------------------------------------------*/
class cELEMENT
{
public:
	int OpenFlag;
	int ElementItemCheckSum;
	sITEM ElementItem[MAX_ELEMENT];
	sITEM ElementItemBackUp[MAX_ELEMENT];
	int ElementCheckFlag;
	ELEMENT_ITEM_SERVER ElementItemServer;
public:
	int CheckItem();
	int ReformElementItem();
	int PickUpElementItem(int x, int y, int PickUpFlag = 0, int Kind = 0);
	int SetElementItemAreaCheck(sITEM* pItem);
	int SetElementItem(sITEM* pItem);
	int CancelElementItem(int Flag = 0);
	int LastSetElementItem(sITEM* pItem, int Kind = 0);
	int SendElementItem();
	int RecvItem(ELEMENT_ITEM_SERVER* pItemServer);
	int CreateElementItem();
	int GetEmptyArea(sITEM* pItem);
	int RecvElementResult(ELEMENT_ITEM_SERVER* pItemServer);
};
class cSOCKET
{
public:
	int OpenFlag;
	int SocketItemCheckSum;
	sITEM SocketItem[MAX_SOCKET];
	sITEM SocketItemBackUp[MAX_SOCKET];
	int SocketCheckFlag;
	SOCKET_ITEM_SERVER SocketItemServer;
public:
	int CheckItem();
	int RecvItem(SOCKET_ITEM_SERVER* pItemServer);
	int CreateSocketItem();
	int ReformSocketItem();
	int CancelSocketItem(int Flag);
	int SendSocketItem();
	int RecvSocketResult(SOCKET_ITEM_SERVER* pItemServer);
	int SetSocketItem(sITEM* pItem);
	int LastSetSocketItem(sITEM* pItem, int Kind);
	int SetSocketItemAreaCheck(sITEM* pItem);
	int GetEmptyArea(sITEM* pItem);
	int PickUpSocketItem(int x, int y, int PickUpFlag, int Kind);
};


class CSmeltingItem
{
public:
	int OpenFlag;
	int SmeltingItemCheckSum;
	int m_SmeltingPrice;
public:
	int CancelSmeltingItem();
	int SetSmeltingItemAreaCheck( sITEM *pItem, int Kind = 0 );
	int LastSetSmeltingItem( sITEM *pItem, int Kind = 0);
	int CheckSmeltingItemForm();
	int ReFormSmeltingItem();
	int PickUpSmeltingItem( int x, int y, int PickUpFlag = 0, int Kind = 0 );
	int sinSendSmeltingItem(); // ������ ���� ������ ������
	int sinRecvSmeltingItem( sSMELTINGITEM_SERVER *pSmeltingItem_Server ); // ���� ������ �޴´�
	int sinRecvSmeltingItemResult( sSMELTINGITEM_SERVER *pSmeltingItem_Server );
	int SmeltingCheckEmptyArea( sITEM *pItem );
	int GetSmeltingCheckEmptyArea();
	int CheckSmeltingPrice();		// ���� ��� �˻�
	int GetSheltomIndex( DWORD SmeltingItemCode ); // ���� ȸ�� �̹��� ����
	bool CSmeltingItem::GetEmptyArea(POINT* Area);
	bool CSmeltingItem::isAreaEmpty(sITEM* pITEM, int Index);
};

/*----------------------------------------------------------------------------*
* pluto							������ ���� Ŭ���� 
*-----------------------------------------------------------------------------*/

class CManufacture
{
public:
	int m_OpenFlag;
	int m_ManufactureItemCheckSum;
	int m_ManufacturePrice;
	LPDIRECT3DTEXTURE9 m_lpGrayRune[MAX_SHELTOM];
public:
	void RuneIndexInit();	// �ʿ��� �� ȸ�� �̹���
	int CancelManufactureItem(); // ���� ���
	int SetManufactureItemAreaCheck( sITEM *pItem ); // ���� ������ �� �ڸ� �˻�
	int LastSetManufactureItem( sITEM *pItem );		// ���� ������ ���´�
	int CheckManufactureItem();
	int ReFormManufactureItem();
	int PickUpManufactureItem( int x, int y, int PickUpFlag = 0 );
	int sinSendManufactureItem();	// ������ ������
	int sinRecvManufactureItem( SManufactureItem_Server *pManufactureItem_Server );
	int RecvManufactureItemResult( SManufactureItem_Server *pManufactureItem_Server ); // �������� ���� ���
	int ManufactureCheckEmptyArea( sITEM *pItem );
	int GetRecipeIndex( DWORD Code ); // ������ �ε����� �����´�
	int GetManufactureCheckEmptyArea();
	SManufacture_ResultItemInfo ManufactureCheckItem( sITEM *pItemCode, smCHAR_INFO *charInfo );	// ���۵� ������ �ڵ�. ���� �˻� �ҷ��� // �庰 - ���������� ȥ
	bool CManufacture::GetEmptyArea(sITEM* pItem, POINT* Area);
	bool CManufacture::isAreaEmpty(int Index);
};

/*----------------------------------------------------------------------------*
*							ũ����Ʈ ������ Ŭ���� 
*-----------------------------------------------------------------------------*/
class cCRAFTITEM{
public:
	int OpenFlag;
	int CraftItemCheckSum;
	int ForceFlag;
	int ForceItemPrice;
	int iReconItemFlag;
public:

	int SetCraftItemAreaCheck(sITEM *pItem,int Kind=0); //�������� �����Ѵ� 
	int LastSetCraftItem(sITEM *pItem,int Kind=0);
	int PickUpCraftItem(int x , int y , int PickUpFlag=0,int Kind=0); //�������� ���ų� ������ �����ش� 

	//�������� �����Ѵ� 
	int MixingItem();

	//������ ������ üũ�Ѵ� 
	int CraftCheckEmptyArea(sITEM *pItem);
	int CancelMixItem(); //�ͽ��� �������� ����Ѵ� 

	int CheckHackCraftItem(); //ũ����Ʈ ������ ���� ����
	int CheckCraftItemForm(); //�����ϴ� ����� �ڽĵ��� �׿������� ơ!!
	int ReFormCraftItem();    //�����ϴ� ����� �ڽĵ��� �׿������� ơ!!


	int sinSendCraftItem();	  //������ �ͽ��� �������� ������ 	
	int sinRecvCraftItem(sCRAFTITEM_SERVER *pCraftItem_Server);   //�������� �ͽ��� �������� �޴´� 

	//�ͽ��� ������� �޴´� 
	int sinRecvCraftItemResult(sCRAFTITEM_SERVER *pCraftItem_Server);

	//Force Orb �������� ������ üũ�Ѵ�
	int CheckForceOrbPrice();
	int CheckForceOrbPrice(sITEM *pItem);

	//������ �籸�� �ý���
	int haCheckReconItem(); //������ �籸�� 
	int haSendReconItem();  //������ �籸�� �� ������ ������.
	/*----------------------------------------------------------------------------*
	* �ۼ��� : �ϴ��  			
	* Desc   : �߰��Ŵ� �Լ���  		
	*-----------------------------------------------------------------------------*/

	//�κ��丮 ����� üũ�Ѵ�.
	int GetCraftCheckEmptyArea();
	//sorting function
	int haCraftSortItem(sCRAFTITEM *pCraftItem);

	// new functions mix xxstr
	bool isSheltomAreaEmpty(sITEM* Item, int Area);
	bool isMixableItem(sITEM* Item);

	bool isItemAreaEmpty();
	bool isStoneAreaEmpty();
};



/*----------------------------------------------------------------------------*
*								â�� Ŭ���� 
*-----------------------------------------------------------------------------*/

class cWAREHOUSE{
public:
	int OpenFlag;	//�Լ��� ����ȭ�� ���� ��¿�� ���� Ŭ���� ���� 
	int WareHouseCheckSum;

public:

	int SetWareHouseItemAreaCheck(sITEM *pItem); //������ üũ�Ѵ� 
	int CrashWareHouseItem(RECT &desRect, int PassItemIndex=0); //�������� ������������ ã�´� 
	int ChangeWareHouseItem(sITEM *pItem); //������ �������� �����Ѵ� 
	int LastSetWareHouseItem(sITEM *pItem); //�������� �����Ѵ� 
	int PickUpWareHouseItem(int x , int y , int PickUpFlag=0); //�������� ���ų� ������ �����ش� 
	bool cWAREHOUSE::GetEmptyArea(sITEM* pItem, POINT* EmptyPos);
	bool cWAREHOUSE::CanStoreItem(sITEM* pItem);
	//���Ը� ���Ѵ� 
	int GetWeight();

	//������ �̹����� �ε��Ѵ�
	int LoadWareHouseItemIamge();	
	
	//�κ��丮 �������� ��� ����Ѵ� 
	int BackUpInvenItem();
	//�������� �������ش� 
	int RestoreInvenItem(); 
	//â�� �ݴ´� 
	int CloseWareHouse();

	//////////////////���� ���� 
	int ReFormWareHouse();
	int CheckWareHouseForm();

	//////////////////���� �����ۿ� ���� ó�� (�������� ����������)
	int CopyItemNotPickUp(sITEM *pItem,int JumpIndex);
	int CheckCopyItem(); //����� �������� �ִ����� üũ�Ѵ� 
	int DeleteCopyItem(); //���� �������� �����ش� (���� �̻����� â�� ����������� ���� ������)

};

/*----------------------------------------------------------------------------*
*								��ų Ŭ���� 
*-----------------------------------------------------------------------------*/
class cTRADE{

public:

	int OpenFlag;
	int MatTrade[4];
	int MatWareHouse[3]; //â�� (�̹����ϳ��� �������� �����´�)
	int MatTradebuttonMain;
	int LpButtonYes;
	int LpButtonYes_;
	int LpButtonNo;
	int LpButtonNo_;

	LPDIRECT3DTEXTURE9 lpbuttonCancel;

	LPDIRECT3DTEXTURE9 lpbuttonCancelInfo;

	LPDIRECT3DTEXTURE9 lpbuttonOk;
	LPDIRECT3DTEXTURE9 lpCheck;

	LPDIRECT3DTEXTURE9 lpCheck_Glay;
	LPDIRECT3DTEXTURE9 lpCheckInfo;
	LPDIRECT3DTEXTURE9 lpDelayCheck;

	LPDIRECT3DTEXTURE9 lpCenterBox;

	sITEM CheckItem[100];
	sITEM CheckRecvItem[MAX_TRADE_ITEM];

	////��� ���� 
	int   TradeRequestFlag;
	DWORD TradeCharCode;
	char  szTradeCharName[64];

	int   TradeItemCheckSum;



public:
	cTRADE();
	~cTRADE();

	void Init(); //Ŭ���� �ʱ�ȭ
	void Load();
	void Release();
	void Draw();
	void DrawImage(int Mat, int x, int y, int w, int h);
	void Close();//Ŭ���� ���� 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); 

	void DrawTradeText(); //�ؽ��� ����ش� 

	///////////// Ʈ���̵� �Լ� 
	int SetTradeItemAreaCheck(sITEM *pItem); //������ üũ�Ѵ� 
	int CrashTradeItem(RECT &desRect, int PassItemIndex=0 , int Kind=0); //�������� ������������ ã�´� 
	int InitTradeColorRect(); //�÷� �ڽ� �ʱ�ȭ 
	int ChangeTradeItem(sITEM *pItem); //������ �������� �����Ѵ� 
	int LastSetTradeItem(sITEM *pItem); //�������� �����Ѵ� 
	int PickUpTradeItem(int x , int y , int PickUpFlag=0); //�������� ���ų� ������ �����ش� 
	bool cTRADE::GetEmptyArea(sITEM* pItem, POINT* EmptyPos);
	bool cTRADE::IsItemOkay(sITEM* pItem);
	//�������� ���ð������� �˾ƺ��� 
	int CheckTradeItemSet(); //���� üũ ����(���Ը� üũ�ϰ� ������ �Լ��� ȣ���Ѵ�)
	int TradeCheckEmptyArea(sITEM *pItem); //�������� ���õɼ��ִ��� üũ�Ѵ�
	int ChecketInvenItem(sITEM *pItem); //�������� �ӽ÷� �����Ѵ� 

	//�������� �κ��丮�� �����Ѵ� 
	int CheckOkTradeItem();			//Ʈ���̵� Ȯ�� 
	int CancelTradeItem();			//Ʈ���̵� ��� 
	int LoadTradeItemIamge();
	int CheckInvenItemStatus(sITEM* pItem);
	//������ �̹����� �ε��Ѵ�
	int ReFormInvenItemStatus();
	//���� ���� 
	int CheckTradeButtonOk();		//������ ������ ��´� 

	//���Ը� ���Ѵ� 
	int GetWeight();

	////////////////////�������� �����ϴ� ����� �ڽĵ��� �׿������� ơ!!
	int CheckTradeItemForm();	//�˻� 
	int ReFormTradeItem();		//���� 


};


class cModifyItem
{
public:
	struct ItemOperationRecv
	{
		int Size;
		int Code;
		int Operation;
		int ItemType;
		int ItemSpec;

		sITEMINFO RecvItem;
	};

public:
	int OpenFlag;
	int TradeItemCode;

	cModifyItem();

	void Load();
	void RestoreItems();
	void DeleteItems();
	void ProcessRecvItem(ItemOperationRecv* Op, sITEMINFO* Item);

	void LButtonDown();
	void LButtonUp();
	void KeyDown(WPARAM wParam);
	void MouseWheel(short Z);

	void Draw();
	void Main();

	int GetBaseCode(std::string Text);
	BYTE GetModifyFlag();
	bool IsItemOkay(sITEM* Item);
	bool IsStoneOkay(sITEM* Item);

	// Texturas.
	LPDIRECT3DTEXTURE9 lpMainTexture;
	LPDIRECT3DTEXTURE9 lpPerfectize;
	LPDIRECT3DTEXTURE9 lpTrade;
	LPDIRECT3DTEXTURE9 lpUpgrade;
	LPDIRECT3DTEXTURE9 lpBarHover;
	LPDIRECT3DTEXTURE9 lpBar;
	LPDIRECT3DTEXTURE9 lpBarGlow;

	int m_ColorIndex;
	RECT m_ColorRect;

	BYTE m_ClickFlag;
	BYTE m_ModifyFlag;
	bool m_EnableFlag;
	bool m_HoverFlag;
	bool m_WaitFlag;

	int m_Type;
	int m_SkipType;
	int m_SkipSpec;
	int m_SelectedType;
	int m_SelectedSpec;
	bool m_HoverBar;
	bool m_HoverSpec;
	bool m_ShowItems;
	bool m_ShowSpecs;

	sITEM m_Items[2];
	sITEM m_NextItem;
};


// pluto ���� ������ ����, ����
int ManufactureItemResultInfo( SManufacture_ResultItemInfo_Server *pResultItemInfo );
///////////// �Լ�
int CopyMixItemCheckDelete(sITEM *pItem);
int sinMakeItemCheck(); //MakeItem�� üũ�Ѵ�
int sinPosBoxNpc();     //PostBox Npc���׼� �޼����� �޴´� 
extern SManufacture_ResultItemInfo g_Manufacture_ItemInfo[MAX_HANDMADEITEM]; // �庰 - ���� // �庰 - ���������� ȥ
extern cTRADE cTrade;
extern sTRADE sTrade;
extern sTRADE sTradeRecv;

extern int RequestTradeButtonFlag; //�ŷ��䱸 ��ư Ŭ�� 
	   
extern cWAREHOUSE cWareHouse; //â�� Ŭ���� 
extern sWAREHOUSE sWareHouse; //â�� ����ü 
extern sITEM *BackUpInvenItem2; //�κ������� �ӽ� ��� 

extern sCARAVAN sCaravan;

extern int TempShowCoin;
extern cCRAFTITEM cCraftItem;	//������ ���� 

extern CSmeltingItem SmeltingItem; // pluto ����
extern SSmeltingItem S_smeltingItem; // pluto ����
extern sSMELTINGITEM_SERVER sSmeltingItem_Send; // pluto ���� ������ ����
extern sSMELTINGITEM_SERVER sSmeltingItem_Recv; // pluto ���� �������� ����

extern CManufacture ManufactureItem; // pluto ����
extern SManufactureItem g_sManufactureItem; // pluto ����
extern SManufactureItem_Server g_sManufactureItem_Send; // pluto ���� ������ ����
extern SManufactureItem_Server g_sManufactureItem_Recv; // pluto ���� �������� ����
extern SManufacture_Rune g_sManufacture_Rune[MAX_RECIPE_KIND];
//extern SManufacture_ResultItemInfo_Server g_Item_Recv;
extern sCRAFTITEM sCraftItem;
extern sCRAFTITEM_INFO sCraftItem_Info[MAX_CRAFTITEM_INFO]; //������ ���� ����

extern sCRAFTITEM_SERVER sCraftItem_Send; //������ ������ ������ 
extern sCRAFTITEM_SERVER sCraftItem_Recv; //�������� ���� ������

extern sCRAFTITEM_SERVER sAging_Send; //������ ������ ������ 
extern sCRAFTITEM_SERVER sAging_Recv; //�������� ���� ������ 


extern int ShowItemCraftMessageFlag; //���յ� ������ ���ڸ� �����ش� 
extern int ShowItemAgingMessageFlag; //�������� ����¡������ �޼����� �����ش� 
extern int ShowItemSmeltingMessageFlag; // pluto �������� ���� ������
extern int ShowItemManufactureMessageFlag; // pluto �������� ���� ������
extern int ShowItemOverSpace;	// pluto ��������

extern int TempShowMoney;	  //�������⸸ �ϴ� �� 
extern int ItemPickUpFlag;	  //�������� ���ؼ� �����̸� �ش� 	
extern int WareHouseSaveFlag;
extern int CaravanSaveFlag;

extern cAGING	cAging;		  //����¡ 
extern sAGINGITEM sAgingItem;
extern sAGINGITEM_INFO sAgingItem_Info[MAX_AGINGITEM_INFO];

extern int AgingLevelAttack[30];
extern int AgingLevelCritical[30];

extern char szAgingItemBuff[128];
extern POINT CraftItemMessageSize;

extern int AgingCheckSheltomFlag; //����¡ ���� �÷� �ʱ�ȭ 
extern int AgingSheltomCnt2;
extern int MixItemNoCopyFlag;
extern int CheckMixItemCopyFlag;
extern sMAKEITEM_INFO sMakeItem_Info[MAX_MAKEITEM_INFO];
extern cSOCKET cSocket;
extern cELEMENT cElement;

// �ͽ��� ���� ��ü �� ������ ����ȭ �ϱ�
extern cMIXTURERESET cMixtureReset;						// ������ - �ͽ��� ���� ��ü
extern sMIXTURE_RESET_ITEM	sMixtureResetItem;			// ������ - �ͽ��� ���� ������ ���� ����ü
extern sMIXTURE_RESET_ITEM sMixtureResetItemBackUp;		// ������ - �ͽ��� ���� ������ ���� ����ü ���
extern int	MixtureResetCheckFlag;						// ������ - �ͽ��� ������ �����Ѱ�?
extern sMIXTURE_RESET_ITEM_SERVER	sMixtureReset_Send;	// ������ - �ͽ��� ���� ������ ������ ����ü
extern sMIXTURE_RESET_ITEM_SERVER	sMixtureReset_Recv;	// ������ - �ͽ��� ���� �������� ���� ����ü

extern char *PostBoxDocFilePath[];

extern sPOSTBOX_ITEM sPostbox_Item[50];
extern int PostBoxIndexCnt;
extern DWORD ExpressItemCode;
extern char  szExpressItemName[64]; //���� ������ �̸� 

extern sCRAFTITEM_SERVER sWingItem_Send; //������ ������ ��������
extern sCRAFTITEM_SERVER sWingItem_Recv; //�������� ���� ������ (�� �ʿ��Ѱ� �ְڳ�)

extern int DownTradePosi[9][4];
extern DWORD SheltomCode2[];
extern DWORD MagicSheltomCode[]; // ����� - ���� ���� �߰�
extern DWORD BillingMagicSheltomCode[]; // ����� - ���� ���� ���� �߰�
extern int ForceItemPrice2;
extern sRECON_ITEM sReconItem[MAX_SEEL_COUNT]; // ����� - ���̿��� �� �߰�
extern int		MixCancelButtonDelayFlag; // pluto �ܺ� ������ �ٲ�� -_-

extern cModifyItem ModifyItem;