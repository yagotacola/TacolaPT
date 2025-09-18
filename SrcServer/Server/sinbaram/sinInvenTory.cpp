
#include "sinLinkHeader.h"
#include "Character/playmain.h"
#include "Character/playsub.h"
#include "netplay.h"
#include "Character/character.h"
#include "fileread.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "field.h"
#include "SrcServer\\onserver.h"
//ReformItem( sITEMINFO *lpItemInfo ); //������ �����ޱ� 
//CheckItemForm( sITEMINFO *lpItemInfo ); //������ ����Ȯ�� 


//ReformCharForm(); //������ 
//CheckCharForm(); //���� 
int LbuttonUpCheckFlag = 0; //�̺�Ʈ �����̸� �ֱ����ؼ� 

int sinInterHeight2 = -50; //������ġ�� �ִ� �������̽��� ��ġ�� �����Ѵ� 

int sinTempDamage2[2] = {0,0}; //���÷��̽ÿ��� ������ ������
int sinTempAbsorb = 0;
int sinTempBlock  = 0;

sITEMINFO TempLinkCoreItem;
POINT UnionCorePosi = {0,0};
int   sinOverWeightCnt = 0;
int sinMyShopItemPass = 0;  


// �庰 - �Է�â
int nName = 0;
int nYesButton= 0;
int nNoButton = 0;
int BackUpPosX , BackUpPosY = 0;
int BackUpButton2X , BackUpButton2Y = 0;
int BackUpButton3X , BackUpButton3Y = 0;

/*----------------------------------------------------------------------------*
*								�������� 			
*-----------------------------------------------------------------------------*/	
cINVENTORY	cInvenTory;

sINVENTORY_EFFECT	sInven_Effect[MAX_INVEN_PARTICLE];	//�κ� ��ƼŬ 
sINVENTORY_EFFECT   UnionCore_Effect[100];				//���Ͽ� �ھ� �κ� ��ƼŬ 
sINVENTORY_EFFECT   UnionCore_Effect_Bone[10];			//���Ͽ� �ھ� �κ� ��ƼŬ 
sINVENTORY_EFFECT   UnionCore_Effect_Bomb[50];			//���Ͽ� �ھ� ������ ����Ʈ

sINVENTORY_EFFECT   ForceOrb_Effect;  //ForceOrb ����Ʈ 
int MatForceOrbEffect[8] = {0};
sITEM MyShopMouseItem;

sELEMENT_ATTACK	sElement_Attack;
sUNIONCORE_EFFECT   sUCore_Effect[10];

int StartX;  //�κ� �ڽ��� ������ X
int StartY;  // Y

int EndX;    //�ڽ�ũ���ϳ��� �� ������ ���� X
int EndY;    //Y 

int ColorIndex;					//�÷� �ڽ��� �ε��� 
RECT ColorRect = {0,0,0,0};		//���� ǥ�õ� ���� 

int CrashItemIndex[2] = {0,0};	//�������� 2���̻� ��ġ�ԵǸ� ������ �Ҽ����� 
int AutoSetItemIndex = 0;       //��չ��⸦ �����Ұ�� �ڵ����� ���õ� �������� �ε��� 

int SelectInvenItemIndex=0;		//���õ� �������� �ε��� 

int SelectPotionIndex = 0;

int ArrowState[2] = {0,0};

int InvenArrowPosi = 0;

sITEM *pUsePotion = 0;          //����� ������ ������ 

int sinLoadOK=0;				//�ε尡 �Ǹ� 1�� �ش� 

int PotionIndex=0;              //�ڽ� �ŷ��� ���� �ε����� �����Ѵ�

sITEM *sinPosionItem= 0;        //���� �����ذ��� ���� ������ 
int BackUpItemIndex = 0;		//���� �����ذ��� ���� ������ �ε��� 
int NotPotionFlag = 0;			//������ �������� �ƴ����� äũ 	

char sinTestBuff[128];			//�׽�Ʈ�� �ϱ����� ���� 

int GhostPotionCheckFlag=0;		// 'E'Ű������ ���� ������� ���׸� �����ϱ����� ��ġ�� �÷� 

int sinChangeSetFlag = 0;

int sinUsePotionDelayFlag = 0;
int PotionCheckNumJumpFlag = 1;

/////////////// ��ų����
int sinUndeadAbsorb = 0;

int sinItemPickUpDelayFlag = 0;
float   sinAdd_fMagic_Mastery	= 0;			//�������õ� 
int sinDamageFunction[3] = {0,0,0};

void*	lpInvenMain;

void*	lpUnionCoreEffect[4];

int MatUnionCoreEffect = 0;

void*   lpGold7=0;
void*   lpExp7=0;


void*   lpSpecialItem[2];
void*   lpSpecialItemInfo[2];

void*   lpSpecialInven;


int IndiShopIconFlag = 0;

//������ Make
sWINGQUEST sWingQuest[MAX_WINGQUEST] = {
	#include "sinWingItem.h"
};


int SpecialItemShowFlag = 0;
int NotChangeSetItemFlag = 0;
int PuzzleOkFlag = 0;

int PuzzleOkY = 0;

int sinTestFlag2 = 0;

/*
void haTest(char *buff)
{
	HANDLE hFile;
    DWORD dwAcess =0;
	
    hFile = CreateFile( "ha.log", GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                        NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

    if( hFile != INVALID_HANDLE_VALUE ) {
        SetFilePointer( hFile , 0 , NULL , FILE_END );
		strcat(buff,"\r\n");
        //����Ÿ ����     ����    ��ũ��    ������ ������ ����Ʈ��
        int chk = WriteFile( hFile , buff , lstrlen(buff) , &dwAcess , NULL );
        //���� �ݱ�
        CloseHandle( hFile );
   }
}
*/
///////////ĳ���� �ɷ�ġ + ������ (���� �ٲ��ַ��� �ܺμ����� Flag �Ⱦ����� ��������)
/*----------------------------------------------------------------------------*
*   	                      �������� ���õ� ���� 
*-----------------------------------------------------------------------------*/	
sINVENTORY sInven[INVENTORY_MAX_POS] = {
	{INVENTORY_POS_RHAND  ,{ 574+1 , 433+1 , 640 , 544}},  //������			0
	{INVENTORY_POS_LHAND  ,{ 722+1 , 433+1 , 788 , 544}},  //�޼�			1
	{INVENTORY_POS_ARMOR  ,{ 648+1 , 433+1 , 714 , 544}},  //����			2
	{INVENTORY_POS_AMULET ,{ 304+1 , 438+1 , 326 , 460}},  //�����			3
	{INVENTORY_POS_RRING  ,{ 356+1 , 438+1 , 378 , 460}},  //������ ��		4
	{INVENTORY_POS_LRING  ,{ 330+1 , 438+1 , 352 , 460}},  //���� ��		5
	{INVENTORY_POS_SHELTOM,{ 382+1 , 438+1 , 404 , 460}},  //����			6
	{INVENTORY_POS_ARMLET ,{ 411+1 , 438+1 , 455 , 482}},  //�Ϸ�			7
	{INVENTORY_POS_GLOVES ,{ 462+1 , 438+1 , 506 , 482}},  //�尩			8
	{INVENTORY_POS_BOOTS  ,{ 513+1 , 438+1 , 557 , 482}},  //�Ź�			9
	{INVENTORY_POS_POTION ,{ 495   , 565   , 495+26 , 565+26}},  //���� 1			10
	{INVENTORY_POS_POTION ,{ 495+26 , 565  , 495+26+26 , 565+26}},  //���� 2			11
	{INVENTORY_POS_POTION ,{ 495+26+26 , 565 , 495+26+26+26 , 565+26}},  //���� 3			12
};

//ȭ��ǥ ��ǥ 
int ArrowPosi[9][4] = {
	{26,572,26+22,591},
	{48,572,48+22,591},
	{519,514,538,533},
	{541,514,560,533},
	{266,572,266+22,591},//�κ� �ݱ� 
	{302,467,321,486},//���� ������ 
	{120,572,120+20,591},//�� ������ 
	{70,572,70+22,591},//����Ʈ ������
	{98,572,98+22,591},//���λ���
};


int InvenTextPosi[2][4] = {
	{121,579,209,592}, //�� 
	{322,473,404,486}, //���� 

};
//Force Orb �� ����Ѵ�
int ForceOrbUseLevel[][2] = {												 // ����� : ���� ���� �߰�(�䱸 ���� 50+)
	{1,19},{1,29},{1,39},{1,49},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},{50,200},
};

// ����� - ���� ����(��� ����, �䱸 ����)
int MagicForceOrbUseLevel[][2] = {	
	{1,19},{1,29},{1,39},{1,49},{50,200},{50,200},{60,200},{70,200},{80,200},{80,200},{90,200},{90,200},
};

// ����� - ���� ���� ���� �߰�(��� ����)
int BillingMagicForceOrbUseLevel[][2] = {	// ����� - ���� ���� ���� �߰�(�䱸 ����)
	{1,200},{1,200},{1,200},
};

int ForceOrbUseTime[] = { 500,500,500,500,700,900,1800,2400,3600,4800,6000,7200,8400,10000,12000 };

// ����� - ���� ���� �߰� 
int MagicForceOrbUseTime[] = {500,500,500,500,700,900,1800,2400,3600,3600,3600,3600,3600,3600}; // ����� - ���� ���� �߰�(�����ð� �߰�)

// ����� - ���� ���� ���� �߰�
int BillingMagicForceOrbUseTime[] = {3600, 10800, 86400}; // ����� - ���� ���� ���� �����ð� �߰�

int ForceOrbDamage[]  = {2,4,7,10,15,25,40,60,80,100,120,140,160,180,200}; // ����� - ���� ���� �߰� ���ݷ�(����, ������ ���� �߰�)
int MagicForceOrbDamage[]  = {2,4,7,10,15,25,40,60,80,100,120,140,160,180}; // ����� - ���� ���� �߰� ���ݷ� 
int BillingMagicForceOrbDamage[]  = {0,0,0}; // ����� - ���� ���� ���� �߰� ���ݷ� 

int BoosterItem_UseTime[] = {3600,10800,86400}; // ����� - �ν��� ������(1�ð�, 3�ð�, 1��) �����ð� �߰�
int BoosterItem_DataPercent[] = {15,15,15}; // ����� - �ν��� ������(�����, ���, �ٷ�) ���� �ۼ�Ʈ

// �庰 - ��ų ������
int nSkillDelay_UseTime[] = {300,10800,86400};

/*----------------------------------------------------------------------------*
*						(�κ� �丮)�κ�  �÷� �ʱ�ȭ 
*-----------------------------------------------------------------------------*/	


//�ϰ����� ũ����Ż ����  ũ����Ż �ڵ�
DWORD CristalEventCODE[12]={(sinGP1|sin01),(sinGP1|sin02),(sinGP1|sin03),(sinGP1|sin04),(sinGP1|sin05)
					       ,(sinGP1|sin06),(sinGP1|sin07),(sinGP1|sin08),(sinGP1|sin09),
						    (sinGP1|sin11),(sinGP1|sin12),(sinGP1|sin13)};

//����� - ���� ��ƿ���(ȣ��) //����� - ���ϴ��� �ҿ� �̺�Ʈ
DWORD WatermelonEventCODE = (sinSP1|sin42);
// �庰 - �߷�Ÿ�� �̺�Ʈ
DWORD ValentineEventCODE = (sinSP1|sin35);

// ����� - ���ĺ� ���� �̺�Ʈ
DWORD PristonAlphabetEventCODE[7] = { (sinSP1|sin27), (sinSP1|sin28), (sinSP1|sin29),
									  (sinSP1|sin30), (sinSP1|sin31), (sinSP1|sin32), (sinSP1|sin33) };

// �庰 - ĵ������
DWORD CandydaysEventCODE = (sinSP1|sin36);

// �庰 - �����ñ׸�
DWORD MagicalGreenEventCODE[2] = { (sinSP1|sin37), (sinSP1|sin38) };

// �庰 - ī���� ����
DWORD TeatOfKaraEventCODE = (sinSP1|sin39);

// �庰 - ������� ã�ƶ� - ���¿�����
DWORD FindinvestigatorEventCODE[2] = { (sinGF1|sin07), (sinGF1|sin08) };

/*----------------------------------------------------------------------------*
*							Ŭ���� �ʱ�, ���� 
*-----------------------------------------------------------------------------*/	
cINVENTORY::cINVENTORY()
{
	//�κ��丮 ���� �ʱ�ȭ 
	for(int i=0 ; i<INVENTORY_MAXITEM;i++)
		memset(&InvenItem[i],0,sizeof(sITEM));

}
cINVENTORY::~cINVENTORY()
{

}

/*----------------------------------------------------------------------------*
*							     �ʱ�ȭ 
*-----------------------------------------------------------------------------*/
void cINVENTORY::Init() {}
/*----------------------------------------------------------------------------*
*						    Bmp������ �ε��Ѵ� 
*-----------------------------------------------------------------------------*/	
void cINVENTORY::Load() {}
void cINVENTORY::InvenItemLoad() {}
//�������� Release�Ѵ� 
void cINVENTORY::InvenItemRelease() {}

/*----------------------------------------------------------------------------*
*						     Release
*-----------------------------------------------------------------------------*/	
void cINVENTORY::Release() {}
/*----------------------------------------------------------------------------*
*							     �׸���  
*-----------------------------------------------------------------------------*/	
int CoreEffectTime = 0;
int CoreEffectFlag = 0;
void cINVENTORY::Draw() {}
/*----------------------------------------------------------------------------*
*							     ����  
*-----------------------------------------------------------------------------*/	
int InvenMainCount = 0;   // �κ��丮 ���� ī��Ʈ 
int SetDelayFlag = 0;     // ���� ������ �÷� 
bool bGiftBoxDelay = false;	// pluto ��������
DWORD dwUsePotionDelayTime = 0;
DWORD dwCheckHackCharStateTime = 0;
DWORD dwCheckHackCharStateFlag = 0;
DWORD dwCheckPickUpItemTime = 0;
int	  CharToItemFirstFlag = 0;
DWORD CharToItemFirstTime = 0;
DWORD dwUseCristalDelayTime  = 0;
int   sinUseCristalDelayFlag = 0;


DWORD dwCheckAutoMouseTime = 0;

int   CheckPosiFlag = 0;
#define   CHECKAUTOMOUSE_DISTANCE		(200*200)
#define   CHECKAUTOMOUSE_SETITEM_MAX	500
#define   CHECKAUTOMOUSE_TIME			(70*60*30)

//#define   CHECKAUTOMOUSE_SETITEM_MAX	100
//#define   CHECKAUTOMOUSE_TIME			(70*60*10)

int   CheckX = 0 , CheckZ = 0;
int   CheckResultX = 0 , CheckResultZ = 0;

DWORD dwPuzzleOkTime = 0;
int ReversEffectFlag = 0;
DWORD dwForceOrbTime = 0;
int   ForceOrbEffectIndex = 0;
void cINVENTORY::Main()
{		
	dwForceOrbTime++; 
	if(dwForceOrbTime > 8){   
		dwForceOrbTime = 0;
		ForceOrbEffectIndex++;
		if(ForceOrbEffectIndex > 7)
			ForceOrbEffectIndex = 0;
	}

	if(PuzzleOkFlag){    
		dwPuzzleOkTime++;
		if(dwPuzzleOkTime >2){ 
			dwPuzzleOkTime = 0;
			if(PuzzleOkY  > 82)ReversEffectFlag=1;
			if(ReversEffectFlag){
				PuzzleOkY --;
				if(PuzzleOkY <=0 )
					ReversEffectFlag = 0;
			}
			else PuzzleOkY ++;

		}
	}
	else{
		PuzzleOkY   = 0;
		dwPuzzleOkTime = 0;
	}
	//////////�׽�Ʈ
//	sInven[10].Rect.left = 499;   
//	sInven[10].Rect.top  = 575;


	int dist = 0;
	//////////���丶�콺�� üũ�Ѵ�
	if(!CheckPosiFlag){
		CheckX = lpCurPlayer->pX;
		CheckZ = lpCurPlayer->pZ;
		CheckPosiFlag = 1;
	}

	dwCheckAutoMouseTime++;
	if(dwCheckAutoMouseTime >= CHECKAUTOMOUSE_TIME){
		if(sinOverWeightCnt > CHECKAUTOMOUSE_SETITEM_MAX){
			CheckResultX = ( lpCurPlayer->pX-CheckX )>>FLOATNS;
			CheckResultZ = ( lpCurPlayer->pZ-CheckZ )>>FLOATNS;
			dist   = CheckResultX*CheckResultX+CheckResultZ*CheckResultZ;
			if(CHECKAUTOMOUSE_DISTANCE >=dist){
				//�Ű� 
				sinOverWeightCnt = 0;
				CheckPosiFlag = 0;
				dwCheckAutoMouseTime = 0;
			}
			else{
				//���� �ʰ��� �����ʰ� ī��Ʈ�� �Ѿ����� ĳ���� �̵��Ÿ��� Ŭ���� �����Ѵ�
				sinOverWeightCnt = 0;
				CheckPosiFlag = 0;
				dwCheckAutoMouseTime = 0;
			}

		}
		else{
			sinOverWeightCnt = 0;
			CheckPosiFlag = 0;
			dwCheckAutoMouseTime = 0;
		}

	}

	if(sinUseCristalDelayFlag){
		dwUseCristalDelayTime++;
		if(dwUseCristalDelayTime >70){
			sinUseCristalDelayFlag = 0;
			dwUseCristalDelayTime  = 0;
		}
	}

	UnionCoreParticleProcess();
	//��ŷ������ ���ؼ� 30�ʸ��� �ѹ��� üũ�Ѵ�
	dwCheckHackCharStateTime++; 
	if(dwCheckHackCharStateTime >= 30*70){
		SetItemToChar(TRUE);
		dwCheckHackCharStateTime = 0;

	}


	if(sinUsePotionDelayFlag){
		dwUsePotionDelayTime++;
		if(dwUsePotionDelayTime > 50){
			dwUsePotionDelayTime = 0;
			sinUsePotionDelayFlag = 0;

		}

	}

	if(SetDelayFlag){ //�����Ҷ� Delay�ð��� �ش� 
		InvenMainCount++;	
		if(InvenMainCount >=70){ //1�� �����̸� �ش� 
			SetDelayFlag = 0;
			InvenMainCount = 0;
		}

	}


	// pluto ��������
	if( bGiftBoxDelay )
	{
		InvenMainCount++;
		if(InvenMainCount >= 140 )
		{
			bGiftBoxDelay = false;
			InvenMainCount = 0;
		}
	}
	InvenArrowPosi = 0; //�����ϱ����� ���� �ʱ�ȭ���ش� 
	int i = 0;
			


	int BackdsDrawOffsetArray = 0;
	if(MouseItem.Flag){
		SetInvenItemAreaCheck(&MouseItem); 
		sinItemPickUpDelayFlag =1;

	}
	if(sinItemPickUpDelayFlag){
		dwCheckPickUpItemTime++;
		if(dwCheckPickUpItemTime >  70){
			sinItemPickUpDelayFlag = 0;
			dwCheckPickUpItemTime = 0;
		}

	}
	else{
		sinItemPickUpDelayFlag = 0;
		dwCheckPickUpItemTime = 0;
	}

	if(!PotionCheckNumJumpFlag)
		CheckPotionNumForm();

	//�κ��丮 ����Ʈ ��~
	if(OpenFlag){
		//ShowInvenEffectParticle(); //�κ��丮 ��ƼŬ�� �����Ѵ�  
		//MoveInvenParticle(); //�κ��丣 ��ƼŬ�� �����δ� 
	}

	//ĳ���� �ɷº����� ���� ������ �ѹ� �������ش� 
	if(!CharToItemFirstFlag){
		CharToItemFirstTime++;
		if(CharToItemFirstTime >= 70*3){
			SetItemToChar(0); 
			SetItemToChar(); 
			CharToItemFirstFlag = 1;
		}
	}

}
/*----------------------------------------------------------------------------*
*							     ���� 
*-----------------------------------------------------------------------------*/	
void cINVENTORY::Close()
{
	Release();	
}
/*----------------------------------------------------------------------------*
*							    Down
*-----------------------------------------------------------------------------*/	
#include "..\\language.h"
int sinButtonFlag=0;
void cINVENTORY::LButtonDown(int x, int y) {}
/*----------------------------------------------------------------------------*

*							   LButtonUp
*-----------------------------------------------------------------------------*/	
void cINVENTORY::LButtonUp(int x, int y) {}
/*----------------------------------------------------------------------------*
*							   RButtonDown
*-----------------------------------------------------------------------------*/

DWORD dwBoosterItemCode[] = {sin21,sin22,sin23,sin24,sin25,sin26,sin27,sin28,sin29,0}; // ����� - �ν��� ������
DWORD dwCastlItemCODE[]={sin01,sin02,sin03,sin04,sin05,sin06,sin07,sin08,sin09,sin10,sin11,sin12,sin13,sin14,sin15,sin16,0};
DWORD dwNotUseVillageItemCODE[3]={(sinBI1|sin05),(sinBI1|sin06),(sinBI1|sin07)};
DWORD dwNotUseItemCODE[6][3]={{SCROLL_INVULNERABILITY,(sinBC1|sin01),1},{SCROLL_CRITICAL,(sinBC1|sin02),2},{SCROLL_EVASION,(sinBC1|sin03),3},
							  {SCROLL_P_INVULNERABILITY,(sinBI1|sin05),1},{SCROLL_P_CRITICAL,(sinBI1|sin06),2},{SCROLL_P_EVASION,(sinBI1|sin07),3}};
DWORD dwSkillDelayItemCode[] = {sin30,sin31,sin32, 0}; // �庰 - ��ų ������
void cINVENTORY::RButtonDown(int x, int y) {}
/*----------------------------------------------------------------------------*
*							   RButtonUp
*-----------------------------------------------------------------------------*/	
void cINVENTORY::RButtonUp(int x , int y)
{

}
/*----------------------------------------------------------------------------*
*							    KeyDown
*-----------------------------------------------------------------------------*/	
void cINVENTORY::KeyDown() {}
/*----------------------------------------------------------------------------*
*							  Ŭ���� �Լ� 
*-----------------------------------------------------------------------------*/	
int cINVENTORY::LoadItemInfo() { return TRUE; }

//Ư���� �������� ����Ʈ �κ��丮�� �����Ѵ� (�ػ� �������� ���� ��ǥ������ �������ش�)
int cINVENTORY::ReSetQuestItemPosi()
{

	sITEM *pItem=0;
	for(int  i = 0; i < INVENTORY_MAXITEM*2 ; i++){
		if(i<100){
			if(!InvenItem[i].Flag)continue;
			pItem = &InvenItem[i];
		}
		else{
			if(!InvenItemTemp[i-100].Flag)continue;
			pItem = &InvenItemTemp[i-100];
		}
		if(pItem->x >1000 && pItem->x < 2000){
			pItem->x += 9000;
		}
	}
	return TRUE;
}

int cINVENTORY::SetSpecialItem(sITEM *pItem)
{
	if(pItem->sItemInfo.SpecialItemFlag[1] != ITEM_KIND_SPECIAL)return FALSE;

	int cntx,cnty;
	int cx,cy;

	RECT	rect;
	int		flag;

	cx = (44*6)-pItem->w; //�������� �����ִ� ���� �� X��ǥ 
	cy = (44*3)-pItem->h; //�������� �����ִ� ���� �� Y��ǥ

	int TempWidth = 0;
	if(SpecialItemShowFlag){
		TempWidth = 0;
	}
	else
		TempWidth = 10000;

	//�ڵ尡 ���� �ʰų� �������� ������� ���� ���� �����Ҷ� �˻��ؼ� ��ġ�� ã�Ƴ��� 
	for( cntx=(StartX+TempWidth) ; cntx <= StartX+TempWidth+cx ; cntx+=44){
		for( cnty=StartY ; cnty <= StartY+cy ; cnty+=44){ 
			flag = 0;
			for(int i=84 ; i<INVENTORY_MAXITEM ; i++){
				if(InvenItem[i].Flag && InvenItem[i].sItemInfo.SpecialItemFlag[1] ==ITEM_KIND_SPECIAL){
					if(InvenItem[i].x < TempWidth){
						rect.left   = InvenItem[i].x+TempWidth;
						rect.right  = InvenItem[i].x+TempWidth+InvenItem[i].w;
					}
					else{
						rect.left   = InvenItem[i].x;
						rect.right  = InvenItem[i].x+InvenItem[i].w;
					}
					rect.top    = InvenItem[i].y;
					rect.bottom = InvenItem[i].y+InvenItem[i].h;

					if( cntx > rect.left-pItem->w && cntx< rect.right && 
						cnty > rect.top-pItem->h && cnty< rect.bottom )
						flag++;
				}
			}
			if ( flag==0 ) {
				pItem->SetX = cntx+((44-pItem->w)/2);
				pItem->SetY = cnty+((44-pItem->h)/2);
				pItem->ItemPosition = 0; 

				for(int j=84 ; j < INVENTORY_MAXITEM ; j++){
					if(InvenItem[j].Flag == 0){
						CheckInvenItemForm();
						memcpy(&InvenItem[j],pItem,sizeof(sITEM));
						InvenItem[j].x = pItem->SetX;
						InvenItem[j].y = pItem->SetY;
						ReFormInvenItem();
						SetItemToChar();
						CheckWeight();   //���Ը� üũ 

						//////////////// ��⼭ ������ �޼����� ������ 
						SendCheckItemToServer(&InvenItem[j].sItemInfo);
						CheckDamage(); //�ִ뵥������ ���� ����� ����Ͽ� ������ �����ش� 
						ReFormPotionNum(); //����ī��Ʈ�� �������ش�
						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}

//���� ���� 
int cINVENTORY::AutoSetInvenItem(sITEM *pItem , int PostBox ) { return TRUE; }

//�κ��丮������ ����� üũ�Ѵ� 
int cINVENTORY::InvenEmptyAearCheck(sITEM *pItem)
{
	int cntx,cnty;
	int cx,cy;

	RECT	rect;
	int		flag;

	if(AutoSetPotionToBox(pItem))return TRUE;

	cx = (22*INVENTORY_BOX_ROW)-pItem->w; //�������� �����ִ� ���� �� X��ǥ 
	cy = (22*INVENTORY_BOX_COL)-pItem->h; //�������� �����ִ� ���� �� Y��ǥ

	//�ڵ尡 ���� �ʰų� �������� ������� ���� ���� �����Ҷ� �˻��ؼ� ��ġ�� ã�Ƴ��� 
	for( cntx=StartX ; cntx <= StartX+cx ; cntx+=22){
		for( cnty=StartY ; cnty <= StartY+cy ; cnty+=22){ 
			flag = 0;
			for(int i=0 ; i<INVENTORY_MAXITEM ; i++){
				if(InvenItem[i].Flag){
					rect.left   = InvenItem[i].x;
					rect.right  = InvenItem[i].x+InvenItem[i].w;
					rect.top    = InvenItem[i].y;
					rect.bottom = InvenItem[i].y+InvenItem[i].h;

					if( cntx > rect.left-pItem->w && cntx< rect.right && 
						cnty > rect.top-pItem->h && cnty< rect.bottom )
						flag++;
				}

			}
			if ( flag==0 ) {
				pItem->SetX = cntx;
				pItem->SetY = cnty;
				pItem->ItemPosition = 0; 
				LastSetInvenItem(pItem,1); //��������ϰ�쿡�� ����1�� �ѱ�� 
					return TRUE;
			}
		}
	}
return FALSE;
}

//�κ��丮 ���������� �����Ѵ� 
int cINVENTORY::LastSetInvenItem(sITEM *pItem , int AutoSet)
{
	int PassFlag=0; //���� ������ ó���Ѵ� 
	if(!AutoSet) //��������� �ƴҰ�쿡�� ó���Ѵ� 
		if(!InvenNotOpenCheck(pItem))return FALSE; //�κ� �������࿩�θ� üũ�Ѵ� 

	for(int j=0 ; j < INVENTORY_MAXITEM ; j++){
		if(InvenItem[j].Flag == 0){
			if(sinPosionItem){ //������ ���� ó���� ���� �ڵ� ���� ���� 
				if(sinPosionItem->sItemInfo.ItemHeader.Head == InvenItem[j].sItemInfo.ItemHeader.Head)
					continue;

			}
			CheckInvenItemForm();
			memcpy(&InvenItem[j],pItem,sizeof(sITEM));
			InvenItem[j].x = pItem->SetX;
			InvenItem[j].y = pItem->SetY;
			if(InvenItem[j].ItemPosition){ //���õ� �������� ������ ���� �����Ѵ� 
				SetTwoHandItem(&InvenItem[j]);//���ڵ� ���������� üũ�Ѵ� 
				sInven[InvenItem[j].ItemPosition-1].ItemIndex = j+1;//���õɶ� �κ��������� ������ �ε����� �����Ѵ�
				sinSetCharItem(InvenItem[j].CODE , pItem->SetModelPosi, TRUE); //����� ������ �����Ѵ� 
			
			}
			pItem->Flag = 0; //�ʱ�ȭ 
			ReFormInvenItem();
			SetItemToChar();
			CheckWeight();   //���Ը� üũ 
			//////////////������ ��ġ�� �����Ѵ�
			if(InvenItem[j].x < StartX || InvenItem[j].x > 800 || InvenItem[j].y < StartY || InvenItem[j].y > 600){
				AutoSetInvenItem(&InvenItem[j]);
			}

			//////////////// ��⼭ ������ �޼����� ������ 
			SendCheckItemToServer(&InvenItem[j].sItemInfo);
			CheckDamage(); //�ִ뵥������ ���� ����� ����Ͽ� ������ �����ش� 
			ReFormPotionNum(); //����ī��Ʈ�� �������ش�

			//������ üũ�Ѵ�
			CheckPuzzle();
			return TRUE;
			
		}
	}
	ReFormInvenItem();
	return FALSE;
}
//////////////////////////////////
//         *���� 
//////////////////////////////////
int cINVENTORY::UsePotion(int x , int y)
{   //������ ����Ѵ� {
	for(int i=0 ; i < INVENTORY_MAXITEM ; i++){
		if(InvenItem[i].Flag){
			if ( InvenItem[i].x < x  && InvenItem[i].x + InvenItem[i].w > x  && 
				InvenItem[i].y < y  && InvenItem[i].y + InvenItem[i].h > y ){
				if(InvenItem[i].ItemPosition == 11 || InvenItem[i].ItemPosition == 12 || InvenItem[i].ItemPosition == 13){
					if(InvenItem[i].Class == ITEM_CLASS_POTION){ //�����ϰ��� ����Ѵ� 
						if(sinActionPotion()){ //������ ����ϴ� ����� ���Ѵ�  ����� ������ ������ ����Ѵ� 
							pUsePotion = &InvenItem[i]; //����� ������ ����Ѵ� 
							sinUsePotionDelayFlag = 1;
						}
						
					}

				}
				else{
					if(!OpenFlag)break;
					if(InvenItem[i].Class == ITEM_CLASS_POTION){ //�����ϰ��� ����Ѵ� 
						if(sinActionPotion()){ //������ ����ϴ� ����� ���Ѵ�  ����� ������ ������ ����Ѵ� 
							pUsePotion = &InvenItem[i]; //����� ������ ����Ѵ� 
							sinUsePotionDelayFlag = 1;
						}
					}
				}
			}
		}
	}
	ReFormPotionNum();	//���� ������ üũ�Ѵ�
	return FALSE;

}

int cINVENTORY::ReSettingPotion()
{ //���� ������ ������ ��� ������ �����Ѵ� 
	sITEM TempPotionItem;
	int i=0,j=0,cnt=0;
	
	memset(&TempPotionItem,0,sizeof(sITEM));
	for(i=10 ; i < 13; i++){ //���� ���ùڽ��� �˻��Ѵ� 
		if(sInven[i].ItemIndex){
			if(InvenItem[sInven[i].ItemIndex-1].Flag){
				memcpy(&TempPotionItem,&InvenItem[sInven[i].ItemIndex-1],sizeof(sITEM));
				cnt = TempPotionItem.sItemInfo.PotionCount;
				if(sinChar->Potion_Space < InvenItem[sInven[i].ItemIndex-1].sItemInfo.PotionCount){ //���� �Ҵ� �������� ������ �������� 
					TempPotionItem.sItemInfo.PotionCount = InvenItem[sInven[i].ItemIndex-1].sItemInfo.PotionCount -sinChar->Potion_Space;
					InvenItem[sInven[i].ItemIndex-1].sItemInfo.PotionCount -= TempPotionItem.sItemInfo.PotionCount;
					if(!InvenEmptyAearCheck(&TempPotionItem)){
						NoSettingThrowItem(&TempPotionItem);// ������ �ȵɶ��� �ٴڿ� �������� ������ 
					}

				}
			}
		
		}

	}
	ReFormPotionNum();	//���� ������ üũ�Ѵ�

	return TRUE;
}
int BackUpX,BackUpY,BackUpPosi=0;
int cINVENTORY::MouseSetPotion(sITEM *pItem) { return TRUE; }

int cINVENTORY::AutoSetPotionToBox(sITEM *pItem) { return TRUE; }
int cINVENTORY::AutoSetPotion(sITEM *pItem) { return TRUE; }
//////////////////////////////////
//         *���ڵ�
//////////////////////////////////
int cINVENTORY::ClearTwoHandPosiAndItem(sITEM *pItem)
{
	if(pItem->Class == ITEM_CLASS_WEAPON_TWO){
		if(sInven[0].ItemIndex){  //������ 
			InvenItem[sInven[0].ItemIndex-1].Flag = 0;
			sInven[0].ItemIndex = 0;
			if(InvenItem[sInven[0].ItemIndex-1].ItemPosition){
				if(InvenItem[sInven[0].ItemIndex-1].SetModelPosi){				
					sinSetCharItem(InvenItem[sInven[0].ItemIndex-1].CODE , InvenItem[sInven[0].ItemIndex-1].SetModelPosi, FALSE); //����� ������ �����Ѵ� 
				}

			}

		}
		if(sInven[1].ItemIndex){
			InvenItem[sInven[1].ItemIndex-1].Flag = 0;
			sInven[1].ItemIndex = 0;
			if(InvenItem[sInven[1].ItemIndex-1].ItemPosition){
				if(InvenItem[sInven[1].ItemIndex-1].SetModelPosi){				
					sinSetCharItem(InvenItem[sInven[1].ItemIndex-1].CODE , InvenItem[sInven[1].ItemIndex-1].SetModelPosi, FALSE); //����� ������ �����Ѵ� 
				}
			}
		}
	}
	return TRUE;
}
int cINVENTORY::SetTwoHandItem(sITEM *pItem)
{ //���� 

	sITEM TempTwoHandItem;

	memset(&TempTwoHandItem,0,sizeof(sITEM)); //�ʱ�ȭ ���ش� 

	if(pItem->Class == ITEM_CLASS_WEAPON_TWO){ //���ڵ� ���⸦ üũ�Ѵ� 
		if(pItem->ItemPosition == 2 ){ //�޼��̸� 
			pItem->ItemPosition = 1;   //�������� ������ ���������� �ٲ۴�  ��ǥ�� �����Ѵ� 
			pItem->x = sInven[0].Rect.left + (((sInven[0].Rect.right - sInven[0].Rect.left)-pItem->w)/2);
			pItem->y = sInven[0].Rect.top  + (((sInven[0].Rect.bottom - sInven[0].Rect.top)-pItem->h)/2);	


		}
		TempTwoHandItem.x = sInven[1].Rect.left + (((sInven[1].Rect.right - sInven[1].Rect.left)-pItem->w)/2);
		TempTwoHandItem.y = sInven[1].Rect.top + (((sInven[1].Rect.bottom - sInven[1].Rect.top)-pItem->h)/2);
		TempTwoHandItem.w = pItem->w; 
		TempTwoHandItem.h = pItem->h;
		TempTwoHandItem.ItemPosition = 2; //�������� ��ġ�� �޼� 
		TempTwoHandItem.Class = pItem->Class; 
		TempTwoHandItem.sItemInfo.CODE = pItem->CODE; //�ڵ带 �־��ش� (������Load�� ������ �������ڷ� ����)
		TempTwoHandItem.sItemInfo.Price = pItem->sItemInfo.Price; //������ �־��ش� 
		memcpy(&TempTwoHandItem.lpItem,&pItem->lpItem,sizeof(void*));
		TempTwoHandItem.Flag = 1;
		for(int j=0 ; j < INVENTORY_MAXITEM ; j++){
			if(InvenItem[j].Flag == 0){
				memcpy(&InvenItem[j],&TempTwoHandItem,sizeof(sITEM));
				sInven[1].ItemIndex = j+1; //���õɶ� �κ��������� ������ �ε����� �����Ѵ�
				break;
			}
		}

	}

	return TRUE;
}

int cINVENTORY::PickUpTwoHandItem(sITEM *pItem)
{//���� 
	sITEM TempPickItem;
	memset(&TempPickItem,0,sizeof(sITEM));

	if(pItem->ItemPosition){ //���� �ڽ����� ������ ��쿡�� 
		if(sInven[0].ItemIndex && sInven[1].ItemIndex){
			memcpy(&TempPickItem,&InvenItem[sInven[0].ItemIndex-1],sizeof(sITEM)); //�������� �������� �����Ѵ� 
			InvenItem[sInven[0].ItemIndex-1].Flag = 0; //������ �������� �����ش� 
			InvenItem[sInven[1].ItemIndex-1].Flag = 0; //�޼� �������� �����ش� 
			sInven[0].ItemIndex = 0; //������� �ڽ��� ������ �����ǵ� �����ش� 
			sInven[1].ItemIndex = 0; //������� �ڽ��� ������ �����ǵ� �����ش� 
			memcpy(pItem,&TempPickItem,sizeof(sITEM));
			ReFormInvenItem();
			ReformCharForm();//������ 
			ReFormPotionNum();
			return TRUE;
		}
	}
	return FALSE;
}

//���ڵ� ���������� ��ġ�� ��츦 üũ�Ѵ�  (������� �����϶��� ȣ��ȴ� )
int cINVENTORY::OverlapTwoHandItem(sITEM *pItem)
{
	AutoSetItemIndex  = 0; //�ڵ����� ���õ� �������� �ε��� 
	if(pItem->Class == ITEM_CLASS_WEAPON_TWO){      //���ڵ� �������� ��� 
		if(sInven[1].ItemIndex){
			if(InvenItem[sInven[1].ItemIndex-1].Class !=ITEM_CLASS_WEAPON_TWO){ //���� ���������ǿ� �ִ� �������� ���ڵ� ���Ⱑ �ƴҰ�쿡
				if(pItem->ItemPosition == 1 ){ //������ 
					if(sInven[1].ItemIndex)
						AutoSetItemIndex = sInven[1].ItemIndex; //�޼� �������� �ε����� �����Ѵ� 
				}
				if(pItem->ItemPosition == 2 ){ //�޼� 
					if(sInven[0].ItemIndex)
						AutoSetItemIndex = sInven[0].ItemIndex; //������ �������� �ε����� �����Ѵ� 
				}
			}
		}
	}
	return TRUE;

}

//���ڵ� ���������� ��ġ�� ��츦 üũ�Ѵ�  (������� �������� ���� �����տ� �������� üũ������ ���а� �ε������´�)
int cINVENTORY::OverlapTwoHandSwitch(sITEM *pItem)
{
	if(pItem->Class == ITEM_CLASS_WEAPON_TWO){      //���ڵ� �������� ��� 
		if(pItem->ItemPosition == 1 ) //������ 
			if(sInven[1].ItemIndex)
				CrashItemIndex[0] = sInven[1].ItemIndex;
		if(pItem->ItemPosition == 2 ) //�޼� 
			if(sInven[0].ItemIndex)
				CrashItemIndex[0] = sInven[0].ItemIndex;

	}
	return TRUE;
}


//�κ��丮 üũ ���� (����ڽ��� üũ���� ���� )
int cINVENTORY::InvenNotOpenCheck(sITEM *pItem )
{
	if(!OpenFlag) //�κ��丮�� �����ְ�  ���� �������� �ƴϸ� �����Ѵ� 
		if(pItem->ItemPosition != 11 && pItem->ItemPosition != 12 && pItem->ItemPosition != 13)
			return FALSE; 
	return TRUE;
}

int cINVENTORY::PickUpInvenItem(int x , int y , int PickUpFlag) { return TRUE; }


//���콺�� �������� ������ �������� ���õ� ������ üũ�Ѵ� 
int cINVENTORY::SetInvenItemAreaCheck(sITEM *pItem)
{

	int i,j;
	ColorIndex= 0; //�ʱ�ȭ 
	CrashItemIndex[0] = 0; //�浹�� ������ Index �ʱ�ȭ 
	CrashItemIndex[1] = 0;
	AutoSetItemIndex  = 0; //�ڵ����� ���õ� �������� �ε��� 

	///////////���� ���� &���� ���� 
	if(!cInvenTory.OpenFlag)return FALSE; //�κ��丮�� �������� �����ÿ��� �������� �����Ҽ� ����
	for( i=0 ; i < INVENTORY_MAX_POS ; i++){ 
		if(CheckInvenPos(pItem->x+11 , pItem->y+11 ,pItem->x +pItem->w -11 ,pItem->y +pItem->h -11 , sInven[i].Rect)){
			ColorRect.left   = sInven[i].Rect.left;     //�÷� �ڽ��� RECT
			ColorRect.top    = sInven[i].Rect.top;
			ColorRect.right  = sInven[i].Rect.right  - sInven[i].Rect.left;
			ColorRect.bottom = sInven[i].Rect.bottom - sInven[i].Rect.top;
			pItem->SetX = sInven[i].Rect.left + ((ColorRect.right-pItem->w)/2);
			pItem->SetY = ColorRect.top  + ((ColorRect.bottom - pItem->h)/2);
			pItem->ItemPosition = i+1;

			if(!(sInven[i].Position & pItem->Class)){ //Ŭ������ ���� �ʴ´� 
				ColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			if(pItem->sItemInfo.NotUseFlag){ //Ŭ������ ���� �ʰų� ������ �ɼ�������  
				ColorIndex = NOT_USE_COLOR;
				return FALSE;

			}
			/*
			if(CrashItemIndex[0] = CrashInvenItem(ColorRect)){  //��ġ�� �������� �ֳ� üũ 
				if(InvenItem[CrashItemIndex[0]-1].sItemInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON &&
					InvenItem[CrashItemIndex[0]-1].sItemInfo.ItemAgingNum[0] < 4){
					ColorIndex = NOT_SETTING_COLOR;
					return FALSE;
				}
			}
			*/

			if(CrashItemIndex[0] = CrashInvenItem(ColorRect)){  //��ġ�� �������� �ֳ� üũ 
				OverlapTwoHandItem(pItem); //���ڵ� ����� ��ġ�� �� �������� üũ�Ѵ�
				ColorIndex = OVERLAP_BOX_COLOR;
				return TRUE;
			}
			OverlapTwoHandSwitch(pItem); //���ڵ� �������� �ݴ��� ��ġ�� üũ 
			ColorIndex = SET_ITEM_CHECK_COLOR; //�����ҿ��� 
			return TRUE;
		}

	}
	
	///////////�ڽ� ���� 
	for(i=pItem->x+11 ; i<pItem->x+pItem->w ; i+=22){
		for( j=pItem->y+11 ; j<pItem->y+pItem->h ; j+=22){
			if(StartX <= i && EndX > i && StartY <=j && EndY > j){ //�κ��丮 �ڽ��� �������� üũ 
				ColorRect.left =  StartX +( ( ( i - StartX) /22)*22) ; 
				ColorRect.top  =  StartY +( ( ( j - StartY) /22)*22) ; 
				ColorRect.right  = pItem->w;
				ColorRect.bottom = pItem->h;
				if(EndX < (ColorRect.left + ColorRect.right)-11 || EndY < (ColorRect.top + ColorRect.bottom)-11){
					InitColorRect(); //�÷� �ڽ� RECT �ʱ�ȭ (�÷� �ڽ� RECT�� �ϳ���� 0 �̸� �����Ҽ� ���� 
					return FALSE;
				}
				pItem->SetX = ColorRect.left;
				pItem->SetY = ColorRect.top;
				pItem->ItemPosition = 0; //�迭�� �ε����� �����Ѵ� 
				ColorIndex = SET_ITEM_CHECK_COLOR; //�����ҿ���


				/*
				if(CrashItemIndex[0] = CrashInvenItem(ColorRect)){  //��ġ�� �������� �ֳ� üũ 
					if(InvenItem[CrashItemIndex[0]-1].sItemInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON &&
						InvenItem[CrashItemIndex[0]-1].sItemInfo.ItemAgingNum[0] < 4){
						ColorIndex = NOT_SETTING_COLOR;
						return FALSE;
					}
					
				}
				*/
				if(CrashItemIndex[0] = CrashInvenItem(ColorRect)){  //��ġ�� �������� �ֳ� üũ
					/*
					if(!CheckSpecialItem(&InvenItem[CrashItemIndex[0]-1])){ //���� ������ Ư���� �������� üũ
						ColorIndex = NOT_SETTING_COLOR;
						return FALSE;
					}
					*/

					if(CrashItemIndex[1] = CrashInvenItem(ColorRect,CrashItemIndex[0])){ //�ΰ� �̻� ��ġ�� üũ 
						ColorIndex = NOT_SETTING_COLOR;
						CrashItemIndex[1] = 0; //�ʱ�ȭ 
						return FALSE;

					}
					ColorIndex = OVERLAP_ITEM_COLOR;
					return TRUE;
				}
				return TRUE;
			}
				
		}
	
	}

	return TRUE;	
}

//�÷� �ڽ� RECT �ʱ�ȭ 
int cINVENTORY::InitColorRect()
{
	ColorRect.left   = 0;   
	ColorRect.top    = 0;
	ColorRect.right  = 0;
	ColorRect.bottom = 0;
	return TRUE;

}

//������ ������ �浹������ üũ�Ѵ�
int cINVENTORY::CrashInvenItem(RECT &desRect , int PassItemIndex)
{

	RECT rect;

	for(int i=0 ; i<INVENTORY_MAXITEM ; i++){
		if(InvenItem[i].Flag){
			if(PassItemIndex != 0)
				if(PassItemIndex == i+1)continue;
			rect.left   = InvenItem[i].x;
			rect.right  = InvenItem[i].x+InvenItem[i].w;
			rect.top    = InvenItem[i].y;
			rect.bottom = InvenItem[i].y+InvenItem[i].h;

			if( desRect.left > rect.left - desRect.right  && desRect.left < rect.right &&
				desRect.top > rect.top - desRect.bottom && desRect.top< rect.bottom ){
					return i+1; //�浹 üũ�� ������ �ε����� �ϳ����ؼ� �����Ѵ� 
			}
		}
	}

	return FALSE;

}
//�������� ���� ���� �浹 üũ 
int cINVENTORY::CheckInvenPos(int x , int y , int lx ,int ly , RECT &rect)
{
	if(x <= rect.left){
		if(rect.left >= lx)return FALSE;
	}
	else{ 
		if(x >=rect.right)return FALSE;
	}

	if(y <= rect.top ){
		if(rect.top >= ly)return FALSE;
	}
	else {
		if(y >= rect.bottom)return FALSE;
	}

	return TRUE;

}

int cINVENTORY::ChangeInvenItem(sITEM *pItem) { return TRUE; }

//������ �ȵɶ����� �ٴڿ� �������� ������ 
int cINVENTORY::NoSettingThrowItem(sITEM *pItem , int Flag)
{
	//��ġ�� ���� ��� ���Ƶд� 
	if(!pItem)return FALSE;  
	if(!pItem->Flag)return FALSE;
	if(!Flag){ //�������� �������� �ٴۿ� ������ (������������ ���¿����� ���� �� Ʈ���̵� â���� ��������쿡�� ����������) // pluto ����
		if(cTrade.OpenFlag || cWareHouse.OpenFlag || cCraftItem.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag)return FALSE; //Ʈ���̵峪 â�� �������� �������� ������ �ʴ´� // ������ - �ͽ��� ���� â �߰�
	}
	if(!pItem->sItemInfo.ItemHeader.Head || pItem->sItemInfo.ItemHeader.Head < 0)return FALSE;
	if(pItem->sItemInfo.CODE == ( sinGF1|sin01))return FALSE;
	//if(pItem->sItemInfo.CODE == ( sinGF1|sin02))return FALSE;

	int kk =0;
	//��ϵ� �������� ���������پ������� ���������� 
	for(kk = 0 ; kk < NotDrow_Item_CODECnt ; kk++){
		if(NotDrow_Item_CODE[kk] == pItem->sItemInfo.CODE)return FALSE;

	}
	for(kk = 0 ; kk < NotDrow_Item_MASKCnt ; kk++){
		if((pItem->sItemInfo.CODE & sinITEM_MASK2) == NotDrow_Item_MASK[kk])return FALSE;

	}
	for(kk = 0 ; kk < NotDrow_Item_KINDCnt ; kk++){
		if(NotDrow_Item_KIND[kk] == pItem->sItemInfo.ItemKindCode)return FALSE;

	}

	if(sinThrowItemToFeild(pItem)){
		pItem->Flag = 0;
	}
	else{
		pItem->Flag = 0; //������ ���ص� ������ �ȵǹǷ� ���������� 
		
	}

	return TRUE;
}

//�������� ������ 
int cINVENTORY::ThrowInvenItemToField(sITEM *pItem) { return TRUE; }

//�ڽ��� �����ִ� �������� �����Ѵ� 
int cINVENTORY::CharOnlySetItem(sITEM *pItem)
{
	//��Ƽ�� �ڽ�Ƭ ������
	//����
	if(sinChar->JOB_CODE == JOBCODE_PRIESTESS || sinChar->JOB_CODE == JOBCODE_ATALANTA || sinChar->JOB_CODE == JOBCODE_ARCHER){	
		if((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinDA1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinDA2 ){
			if( (pItem->sItemInfo.CODE & sinITEM_MASK3) == sin31 || (pItem->sItemInfo.CODE & sinITEM_MASK3) == sin32 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin35 || (pItem->sItemInfo.CODE & sinITEM_MASK3) == sin36 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin39 || (pItem->sItemInfo.CODE & sinITEM_MASK3) == sin40 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin43 || (pItem->sItemInfo.CODE & sinITEM_MASK3) == sin44 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin51 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin54 )
			{
				pItem->sItemInfo.NotUseFlag = 1; 			
			}
		}		
	}
	else{ // ����
		if((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinDA1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinDA2 ){
			if( (pItem->sItemInfo.CODE & sinITEM_MASK3) == sin33 || (pItem->sItemInfo.CODE & sinITEM_MASK3) == sin34 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin37 || (pItem->sItemInfo.CODE & sinITEM_MASK3) == sin38 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin41 || (pItem->sItemInfo.CODE & sinITEM_MASK3) == sin42 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin45 || (pItem->sItemInfo.CODE & sinITEM_MASK3) == sin46 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin45 || (pItem->sItemInfo.CODE & sinITEM_MASK3) == sin46 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin52 ||
				(pItem->sItemInfo.CODE & sinITEM_MASK3) == sin55 )
			{

				pItem->sItemInfo.NotUseFlag = 1; 			
			}
		}
	}

	///////////// ����
	if(sinChar->JOB_CODE == 7 || sinChar->JOB_CODE == 8){
		if((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinDA1){
			pItem->sItemInfo.NotUseFlag = 1; //�Ϲ� ������ ���簡 �����Ҽ�����

		}
	}
	else{ //���� 
		if((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinDA2 ||
			(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinOM1 ){
				pItem->sItemInfo.NotUseFlag = 1; //�κ� �� ����� �� ���簡 �����Ҽ�����

			}
	}	

	return TRUE;
}

//���� ���¸� üũ�Ѵ� (���� ,�� ,��ø ....) 
int cINVENTORY::CheckRequireItem()
{
	int NotUseItemFlag = 0;
	int i;

	for( i=0 ; i < INVENTORY_MAXITEM ; i++){   
		if(InvenItem[i].Flag){
			if(InvenItem[i].sItemInfo.Level     > sinChar->Level)NotUseItemFlag = 1;
			if(InvenItem[i].sItemInfo.Dexterity > sinChar->Dexterity)NotUseItemFlag = 1;
			if(InvenItem[i].sItemInfo.Strength  > sinChar->Strength)NotUseItemFlag = 1;
			if(InvenItem[i].sItemInfo.Talent    > sinChar->Talent)NotUseItemFlag = 1;
			if(InvenItem[i].sItemInfo.Spirit    > sinChar->Spirit)NotUseItemFlag = 1;
			if(InvenItem[i].sItemInfo.Health    > sinChar->Health)NotUseItemFlag = 1;
			if(DeleteEventItem_TimeOut( &InvenItem[i].sItemInfo)==TRUE) NotUseItemFlag = 1;  //	����� : �Ⱓ�� ������ ����Ǿ�����(Ŭ��ġ���� ���)
			if(NotUseItemFlag){
				InvenItem[i].sItemInfo.NotUseFlag = 1;
				NotUseItemFlag = 0;
			}
			else
				InvenItem[i].sItemInfo.NotUseFlag = 0;
			CharOnlySetItem(&InvenItem[i]); //ĳ���ͺ� �������� üũ�Ѵ�
			if((InvenItem[i].sItemInfo.CODE & sinITEM_MASK2) == sinFO1){
				int j = 0;
				for(j = 0; j < 14 ; j++){ // ����� - ���� ���� �߰�
					if((InvenItem[i].sItemInfo.CODE&sinITEM_MASK3)== SheltomCode2[j] || (InvenItem[i].sItemInfo.CODE&sinITEM_MASK3)== MagicSheltomCode[j]){
						break;
					}
				}
				if( (InvenItem[i].sItemInfo.CODE&sinITEM_MASK3) < sin21 ) // ����� - �Ϲ� ����
				{
					if(sinChar->Level < ForceOrbUseLevel[j][0] ||
						sinChar->Level > ForceOrbUseLevel[j][1]){
							InvenItem[i].sItemInfo.NotUseFlag = 1;
							NotUseItemFlag = 0;

						}
					else{
						InvenItem[i].sItemInfo.NotUseFlag = 0;

					}
				}
				else if( (InvenItem[i].sItemInfo.CODE&sinITEM_MASK3) < sin35) // ����� - ���� ����
				{
					if(sinChar->Level < MagicForceOrbUseLevel[j][0] ||
						sinChar->Level > MagicForceOrbUseLevel[j][1]){
							InvenItem[i].sItemInfo.NotUseFlag = 1;
							NotUseItemFlag = 0;

						}
					else{
						InvenItem[i].sItemInfo.NotUseFlag = 0;

					}
				}
			}

		}	

	}
	return TRUE;
}

//�����Ҽ� �ִ����� üũ 
int cINVENTORY::CheckRequireItemToSet(sITEM *pItem)
{
	int NotUseItemFlag = 0;

	if(pItem->sItemInfo.Level     > sinChar->Level )NotUseItemFlag = 1;
	if(pItem->sItemInfo.Dexterity > sinChar->Dexterity)NotUseItemFlag = 1;
	if(pItem->sItemInfo.Strength  > sinChar->Strength)NotUseItemFlag = 1;
	if(pItem->sItemInfo.Talent    > sinChar->Talent)NotUseItemFlag = 1;
	if(pItem->sItemInfo.Spirit    > sinChar->Spirit)NotUseItemFlag = 1;
	if(pItem->sItemInfo.Health    > sinChar->Health)NotUseItemFlag = 1;
	if(NotUseItemFlag){
		pItem->sItemInfo.NotUseFlag = 1;
		NotUseItemFlag = 0;
	}
	else{
		pItem->sItemInfo.NotUseFlag = 0;


	}
	CharOnlySetItem(pItem); //ĳ���ͺ� �������� üũ�Ѵ�
	return TRUE;

}

//�κ��丮 �ؽ�Ʈ 
int cINVENTORY::DrawInvenText() { return TRUE; }

//������ ������ ���ؿ´� 
int cINVENTORY::SearchJobAndSetting()
{
	int cnt;

	JobName[0] = 0;

	cnt = 0;
	//���߿� ��������!
	/*
	if(smConfig.DebugMode){ 
		if(sinChar->ChangeJob > 1)
			sinChar->ChangeJob = 1;
	}
	*/
	while(1) {
		if ( JobDataBase[cnt].JobCode==0 ) break;
		if ( JobDataBase[cnt].JobCode==sinChar->JOB_CODE ) {
			sinJobList = GetJobDataCode(sinChar->JOB_CODE , sinChar->ChangeJob);
			lstrcpy( JobName , sinJobList->szName2 );
			sinChar->JobBitMask = JobDataBase[cnt].JobBitCode;
			sinChar->LifeFunction = JobDataBase[cnt].LifeFunction; //����� �Լ� 
			sinChar->ManaFunction = JobDataBase[cnt].ManaFunction; //��� �Լ� 
			sinChar->StaminaFunction = JobDataBase[cnt].StaminaFunction; //�ٷ��Լ� 
			sinDamageFunction[0] = JobDataBase[cnt].DamageFunction[0];  //���� ���� 
			sinDamageFunction[1] = JobDataBase[cnt].DamageFunction[1];  //���Ÿ� ���� 
			sinDamageFunction[2] = JobDataBase[cnt].DamageFunction[2];  //���� ����

           	break;
		}
		cnt++;
	}
	return TRUE;

}

//ĳ���� �ɷ�ġ ���� 
int cINVENTORY::SetItemToChar(int CheckHackFlag) { return TRUE; }

//ĳ���� ������ �о�´� 
void cINVENTORY::LoadCharState()
{

  
}

//�������� �ٲ۴� 
int cINVENTORY::ChangeABItem(int Posi) { return TRUE; }
//�������� ���������� ���´� 
sITEMPRICE cINVENTORY::GetInvenItemPrice(sITEM *pItem)
{
	
	sITEMPRICE sinItemPrice;

	if(pItem->Class == ITEM_CLASS_WEAPON_TWO){
		if(pItem->ItemPosition){
			pItem = &InvenItem[sInven[0].ItemIndex-1];

		}
	}

	float Dur[2];		//������ 
	float Price;		//���� ���� 

	Dur[0] = pItem->sItemInfo.Durability[0];
	Dur[1] = pItem->sItemInfo.Durability[1];
	Price  = (float)pItem->sItemInfo.Price;
	if(Dur[0] == 0)Dur[0] = 1; //���� 0�̵Ǵ°��� �����Ѵ� 
	if(Dur[1] == 0)Dur[1] = 1;

	sinItemPrice.PureSellPrice = (int)((Price*(Dur[0]/Dur[1]))+(Price-(Price*(Dur[0]/Dur[1])))*0.25);
	
	sinItemPrice.SellPrice =  (int)sinItemPrice.PureSellPrice/5;  

	sinItemPrice.RepairCost = (pItem->sItemInfo.Price -sinItemPrice.PureSellPrice)/8; 
/*
	//��ǥ Kyle

	if( pItem->sItemInfo.CODE == (sinBI1|sin35)	||
		pItem->sItemInfo.CODE == (sinBI1|sin36)	||
		pItem->sItemInfo.CODE == (sinBI1|sin37)	||
		pItem->sItemInfo.CODE == (sinBI1|sin38)
		)
	{
		sinItemPrice.PureSellPrice	= 0;
		sinItemPrice.SellPrice		= (int)Price;
		sinItemPrice.RepairCost		= 0; 
	}
	else
	{
		sinItemPrice.PureSellPrice = (int)((Price*(Dur[0]/Dur[1]))+(Price-(Price*(Dur[0]/Dur[1])))*0.25);
		sinItemPrice.SellPrice =  (int)sinItemPrice.PureSellPrice/5;  
		sinItemPrice.RepairCost = (pItem->sItemInfo.Price -sinItemPrice.PureSellPrice)/8; 
	}
*/
	return sinItemPrice; //����ü�� �����Ѵ� 

}


//�������� �����Ѵ� 
int cINVENTORY::RepairInvenItem(sITEM *pItem , int RepairCost) 
{
	if(pItem->Class == ITEM_CLASS_WEAPON_TWO){
		if(pItem->ItemPosition){
			pItem = &InvenItem[sInven[0].ItemIndex-1];

		}
	}

	CheckCharForm();//���� 
	//ReformCharForm();//������
	if(!pItem->sItemInfo.Durability[1])return FALSE;
	if(sinChar->Money - RepairCost > 0){
		if(pItem->sItemInfo.Durability[0] < pItem->sItemInfo.Durability[1]){
			//sinChar->Money -= RepairCost;
			sinMinusMoney(RepairCost);
			pItem->sItemInfo.Durability[0] = pItem->sItemInfo.Durability[1];
			ReformCharForm();//������ 
			SendSaveMoney(); //�ݾ� ������ ���ϰ��ϱ����� ȣ���Ѵ� 
			return TRUE;
		}
	}
	return FALSE;
	
}

//���Ը� üũ�Ѵ� 
void cINVENTORY::CheckWeight()
{

	CheckCharForm();//����
	
	sinChar->Weight[0] = 0; //���� �ʱ�ȭ �� �ٽ� ���� 
	for(int i=0; i <INVENTORY_MAXITEM ; i++){
		if(InvenItem[i].Flag){
			if(InvenItem[i].Class == ITEM_CLASS_POTION){
				if( InvenItem[i].sItemInfo.PotionCount < 0 )continue;
				sinChar->Weight[0] += InvenItem[i].sItemInfo.PotionCount;
				continue;

			}
			if(InvenItem[i].sItemInfo.Weight < 0)continue;
			sinChar->Weight[0] += InvenItem[i].sItemInfo.Weight;
		}
	}
	for(int j=0; j <INVENTORY_MAXITEM ; j++){
		if(InvenItemTemp[j].Flag){
			if(InvenItemTemp[j].Class == ITEM_CLASS_POTION){
				if( InvenItemTemp[j].sItemInfo.PotionCount < 0 )continue;
				sinChar->Weight[0] += InvenItemTemp[j].sItemInfo.PotionCount;
				continue;

			}
			if(InvenItemTemp[j].sItemInfo.Weight < 0)continue;
			sinChar->Weight[0] += InvenItemTemp[j].sItemInfo.Weight;
		}
	}

	ReformCharForm();//������ 

}

// �����Ҽ��ִ����� üũ�Ѵ� 
int cINVENTORY::CheckSetOk(sITEM *pItem , int AutoFlag) { return TRUE; }


//����� �������� ���ش�  
int cINVENTORY::CopyItemClear(sITEM *pItem)
{ //���콺�� ����ִ� �����۰� ���� �������� �ִ����� �˻��Ѵ�

	int CopyItemCnt = 0;
	for(int i = 0 ; i < INVENTORY_MAXITEM ; i++){ 
		if(InvenItem[i].Flag){		//�ո� �κ��丮 
			if(CompareItems(&pItem->sItemInfo ,  &InvenItem[i].sItemInfo)){
				//����� �������� �����ش� 
				InvenItem[i].Flag = 0;
				if(InvenItem[i].ItemPosition){
					sInven[InvenItem[i].ItemPosition-1].ItemIndex = 0;
					sinSetCharItem(InvenItem[i].CODE , InvenItem[i].SetModelPosi, FALSE); //����� ������ �����Ѵ� 
					ClearTwoHandPosiAndItem(&InvenItem[i]);//���ڵ� �����̸� ���ڵ� ���⸦ �����ش� 

				}
				CopyItemCnt++;
				

			}

		}
		if(InvenItemTemp[i].Flag){	//�޸� �κ��丮 
			if(CompareItems(&pItem->sItemInfo ,  &InvenItemTemp[i].sItemInfo)){//����� �������� �����ش� 
				InvenItemTemp[i].Flag = 0;
				if(InvenItemTemp[i].Class == ITEM_CLASS_WEAPON_TWO){
					if(InvenItemTemp[i].ItemPosition == 1 ||InvenItemTemp[i].ItemPosition == 2){
						for(int k = 0 ; k < INVENTORY_MAXITEM ; k++){ 
							if(InvenItemTemp[k].Flag){
								if(InvenItemTemp[k].ItemPosition == 1 ||InvenItemTemp[k].ItemPosition == 2){
									if(InvenItemTemp[i].sItemInfo.CODE == InvenItemTemp[k].sItemInfo.CODE){
										InvenItemTemp[k].Flag = 0;		
									}
								}
							}
						}
					}
				}
				CopyItemCnt++;
			}
		}
	}
	if(CopyItemCnt){
		SendCopyItemUser(CopyItemCnt); //������ ī�ǵ� �������� ������ ������ 
		CopyItemCnt = 0;
	}
	return TRUE;	

}

//�ӽ÷� ������ �̹����� üũ�ϱ����ؼ� ���δ� 
int cINVENTORY::ImsiCheckItemImageSize() { return TRUE; }


//�߸��� ��ǥ�� �������ش� 
int cINVENTORY::CheckOverlapItem(sITEM *pItem , int PassItemIndex)
{
	int ReSetXYFlag =0 ;
	if(!pItem)return FALSE;
	if(pItem->ItemPosition){
		if(pItem->ItemPosition < 11){ //���� �������� �ƴϸ� 
			sInven[pItem->ItemPosition-1].ItemIndex = 0; //������ �ʱ�ȭ 
			pItem->ItemPosition = 0;
			ReSetXYFlag = 1;
		}
		else 
			ReSetXYFlag = 0;
	}

	RECT Rect;
	int  TempPosiFlag = 0;
	Rect.left   = pItem->x; 
	Rect.top    = pItem->y;
	Rect.right  = pItem->w;
	Rect.bottom = pItem->h;

	int cntx,cnty;
	int cx,cy;

	RECT	rect;
	int		flag;

	cx = (22*INVENTORY_BOX_ROW)-pItem->w; //�������� �����ִ� ���� �� X��ǥ 
	cy = (22*INVENTORY_BOX_COL)-pItem->h; //�������� �����ִ� ���� �� Y��ǥ

	//�ڵ尡 ���� �ʰų� �������� ������� ���� ���� �����Ҷ� �˻��ؼ� ��ġ�� ã�Ƴ��� 

	if(CrashInvenItem(Rect,PassItemIndex)||ReSetXYFlag){
		for( cntx=StartX ; cntx <= StartX+cx ; cntx+=22){
			for( cnty=StartY ; cnty <= StartY+cy ; cnty+=22){ 
				flag = 0;
				for(int i=0 ; i<INVENTORY_MAXITEM ; i++){
					if(InvenItem[i].Flag){
						rect.left   = InvenItem[i].x;
						rect.right  = InvenItem[i].x+InvenItem[i].w;
						rect.top    = InvenItem[i].y;
						rect.bottom = InvenItem[i].y+InvenItem[i].h;
	
						if( cntx > rect.left-pItem->w && cntx< rect.right && 
							cnty > rect.top-pItem->h && cnty< rect.bottom )
							flag++;
					}
				}
				if ( flag==0 ) {
					pItem->x = cntx;
					pItem->y = cnty;
					sInven[pItem->ItemPosition-1].ItemIndex =0;
					pItem->ItemPosition = 0; 
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

//�ӽ÷� �߸��� ��ǥ�� �������ش� 
int cINVENTORY::ReSetPotionXY(sITEM *pItem,int kind)
{

	RECT Rect;
	Rect.left   = pItem->x; 
	Rect.top    = pItem->y;
	Rect.right  = pItem->w;
	Rect.bottom = pItem->h;

	int cntx,cnty;
	int cx,cy;

	RECT	rect;
	int		flag;

	cx = (22*INVENTORY_BOX_ROW)-pItem->w; //�������� �����ִ� ���� �� X��ǥ 
	cy = (22*INVENTORY_BOX_COL)-pItem->h; //�������� �����ִ� ���� �� Y��ǥ

	//�ڵ尡 ���� �ʰų� �������� ������� ���� ���� �����Ҷ� �˻��ؼ� ��ġ�� ã�Ƴ��� 

	if(kind == 1){
		for( cntx=StartX ; cntx <= StartX+cx ; cntx+=22){
			for( cnty=StartY ; cnty <= StartY+cy ; cnty+=22){ 
				flag = 0;
				for(int i=0 ; i<INVENTORY_MAXITEM ; i++){
					if(InvenItemTemp[i].Flag){
						rect.left   = InvenItemTemp[i].x;
						rect.right  = InvenItemTemp[i].x+InvenItemTemp[i].w;
						rect.top    = InvenItemTemp[i].y;
						rect.bottom = InvenItemTemp[i].y+InvenItemTemp[i].h;
		
						if( cntx > rect.left-pItem->w && cntx< rect.right && 
							cnty > rect.top-pItem->h && cnty< rect.bottom )
							flag++;
					}
				}
				if ( flag==0 ) {
					pItem->x = cntx;
					pItem->y = cnty;
					//sInven[pItem->ItemPosition-2].ItemIndex =0; //���� �����������̶� �� ���д� 
					pItem->ItemPosition = 0; 
					return TRUE;
				}

			}
		}
	}
	else{
		for( cntx=StartX ; cntx <= StartX+cx ; cntx+=22){
			for( cnty=StartY ; cnty <= StartY+cy ; cnty+=22){ 
				flag = 0;
				for(int i=0 ; i<INVENTORY_MAXITEM ; i++){
					if(InvenItem[i].Flag){
						rect.left   = InvenItem[i].x;
						rect.right  = InvenItem[i].x+InvenItem[i].w;
						rect.top    = InvenItem[i].y;
						rect.bottom = InvenItem[i].y+InvenItem[i].h;
		
						if( cntx > rect.left-pItem->w && cntx< rect.right && 
							cnty > rect.top-pItem->h && cnty< rect.bottom )
							flag++;
					}
				}
				if ( flag==0 ) {
					pItem->x = cntx;
					pItem->y = cnty;
					sInven[pItem->ItemPosition-2].ItemIndex =0;
					pItem->ItemPosition = 0; 
					return TRUE;
				}

			}
		}
	}
	return FALSE;

}

//��ȯ �������� ����Ѵ� 
int cINVENTORY::UseEcore(sITEM *pItem) { return TRUE; }

//������ �Դ´� 
int cINVENTORY::EatSongPyeun(sITEM *pItem) { return TRUE; }
//���콺�� �ִ� �������� �����Ѵ� 
int cINVENTORY::ResetMouseItem() { return TRUE; }
//CheckInvenItemForm();
//ReFormInvenItem();
//////////////////////�κ��丮 �������� ������ �����Ѵ� 
int cINVENTORY::CheckInvenItemForm()
{ //����Ÿ�� ���� ���ؼ� ������ �־��ش� 
	DWORD TempCheckDataSum = 0;

	for(int i=0 ; i<INVENTORY_MAXITEM ; i++){
		if(InvenItem[i].Flag){
			if(InvenItem[i].Class != ITEM_CLASS_POTION){
				//TempCheckDataSum += (i+1)*InvenItem[i].x;
				TempCheckDataSum += (i+1)*InvenItem[i].y;
				TempCheckDataSum += (i+1)*InvenItem[i].Class;
				TempCheckDataSum += InvenItem[i].sItemInfo.ItemHeader.dwChkSum;
				TempCheckDataSum += InvenItem[i].sItemInfo.ItemHeader.Head;
			}

		}
		if(InvenItemTemp[i].Flag){
			if(InvenItemTemp[i].Class != ITEM_CLASS_POTION){
				//TempCheckDataSum += (i+1)*InvenItemTemp[i].x;
				TempCheckDataSum += (i+1)*InvenItemTemp[i].y;
				TempCheckDataSum += (i+1)*InvenItemTemp[i].Class;
				TempCheckDataSum += InvenItemTemp[i].sItemInfo.ItemHeader.dwChkSum;
				TempCheckDataSum += InvenItemTemp[i].sItemInfo.ItemHeader.Head;
			}

		}

	}
	if(TempCheckDataSum != InvenDataCheckSum){
		SendSetHackUser(2); //��ŷ�� �Ϸ����ߴ� ���� ������ ��� TRUE ���� ���� 
		//TempCheckDataSum = 0;

	}
	return TRUE;
}

//����Ÿ�� ���� �����Ѵ� 
int cINVENTORY::ReFormInvenItem()
{
	DWORD Temp = 0;
	InvenDataCheckSum = 0;

	for(int i=0 ; i<INVENTORY_MAXITEM ; i++){
		if(InvenItem[i].Flag){
			if(InvenItem[i].Class != ITEM_CLASS_POTION){
				//InvenDataCheckSum += (i+1)*InvenItem[i].x;
				InvenDataCheckSum += (i+1)*InvenItem[i].y;
				InvenDataCheckSum += (i+1)*InvenItem[i].Class;
				InvenDataCheckSum += InvenItem[i].sItemInfo.ItemHeader.dwChkSum;
				InvenDataCheckSum += InvenItem[i].sItemInfo.ItemHeader.Head;
			}

		}
		if(InvenItemTemp[i].Flag){
			if(InvenItemTemp[i].Class != ITEM_CLASS_POTION){
				//InvenDataCheckSum += (i+1)*InvenItemTemp[i].x;
				InvenDataCheckSum += (i+1)*InvenItemTemp[i].y;
				InvenDataCheckSum += (i+1)*InvenItemTemp[i].Class;
				InvenDataCheckSum += InvenItemTemp[i].sItemInfo.ItemHeader.dwChkSum;
				InvenDataCheckSum += InvenItemTemp[i].sItemInfo.ItemHeader.Head;
			}

		}

	}
	Temp = InvenDataCheckSum;
	
	return TRUE;

}

int cINVENTORY::CheckMoneyLimit(int Money)
{

	int CheckMoney = 0;  
	if(sinChar->Level <= 10){
		if((sinChar->Money + Money) <= MAX_GOLD_LOW_LEVEL)
			return TRUE;

	}
	else{
		switch(sinChar->ChangeJob){
			case 0:
				if((sinChar->Money + Money) <= (sinChar->Level* MAX_GOLD_LOW_LEVEL)-1800000)
					return TRUE;
			break;

			case 1:
				if( ( sinChar->Money + Money) <= MAX_GOLD_TIER2)return TRUE;
			break;
			case 2:
				if( ( sinChar->Money + Money) <= MAX_GOLD_TIER3)return TRUE;

			break;
			//4�� ����(�ӽ�)
			case 3:
				if( ( sinChar->Money + Money) <= MAX_GOLD_TIER4)return TRUE;
			break;

		}
	}	

	return FALSE;

/*
	int CheckMoney = 0;  
	if(sinChar->Level <= 20){
		if((sinChar->Money + Money) <= 200000 )
			return TRUE;

	}
	else{
		if((sinChar->Money + Money) <= (sinChar->Level*200000)-1800000) 
			return TRUE;

	}
	
	cMessageBox.ShowMessage(MESSAGE_OVER_MONEY);
	return FALSE;
*/

}

//////������ ������ ���Ѵ� 
int sinPotionNum[4] = {0,0,0,0};
int CheckPotionNum[4] = { 0,0,0,0};
int cINVENTORY::ReFormPotionNum()
{
	PotionCheckNumJumpFlag =1;
	
	for(int j=0;j<4;j++){
		sinPotionNum[j] = 0;
	
	}	
	for(int i=0;i<INVENTORY_MAXITEM ; i++){ 
		if(InvenItem[i].Flag){
			if(InvenItem[i].Class  == ITEM_CLASS_POTION){
				switch(InvenItem[i].CODE & sinITEM_MASK3){
				case sin01:
					sinPotionNum[0] += InvenItem[i].sItemInfo.PotionCount;

				break;
				case sin02:
					sinPotionNum[1] += InvenItem[i].sItemInfo.PotionCount;

				break;
				case sin03:
					sinPotionNum[2] += InvenItem[i].sItemInfo.PotionCount;

				break;
				case sin04:
					sinPotionNum[3] += InvenItem[i].sItemInfo.PotionCount;

				break;
				}
			}
		}
		if(InvenItemTemp[i].Flag){
			if(InvenItemTemp[i].Class  == ITEM_CLASS_POTION){
				switch(InvenItemTemp[i].CODE & sinITEM_MASK3){
				case sin01:
					sinPotionNum[0] += InvenItemTemp[i].sItemInfo.PotionCount;

				break;
				case sin02:
					sinPotionNum[1] += InvenItemTemp[i].sItemInfo.PotionCount;

				break;
				case sin03:
					sinPotionNum[2] += InvenItemTemp[i].sItemInfo.PotionCount;

				break;
				case sin04:
					sinPotionNum[3] += InvenItemTemp[i].sItemInfo.PotionCount;

				break;
				}
			}
		}
	}
	/*
	if(MouseItem.Flag){
		if(MouseItem.Class  == ITEM_CLASS_POTION){
			switch(MouseItem.sItemInfo.CODE & sinITEM_MASK3){
				case sin01:
					sinPotionNum[0] += MouseItem.sItemInfo.PotionCount;

				break;
				case sin02:
					sinPotionNum[1] += MouseItem.sItemInfo.PotionCount;

				break;
				case sin03:
					sinPotionNum[2] += MouseItem.sItemInfo.PotionCount;

				break;
				case sin04:
					sinPotionNum[3] += MouseItem.sItemInfo.PotionCount;

				break;
			}
		}
	}
	*/
	PotionCheckNumJumpFlag = 0;
	return TRUE;
}

//������ üũ�Ѵ� 

DWORD PotionCheckDelayTime = 0;
int cINVENTORY::CheckPotionNumForm()
{
/*	
	PotionCheckDelayTime++;
	if(PotionCheckDelayTime < 70*10)return FALSE;
	PotionCheckDelayTime = 0;
*/	
	
	for(int k=0;k<4;k++){
		CheckPotionNum[k] = 0;
	
	}	
	for(int i=0;i<INVENTORY_MAXITEM ; i++){ 
		if(InvenItem[i].Flag){
			if(InvenItem[i].Class  == ITEM_CLASS_POTION){
				switch(InvenItem[i].CODE & sinITEM_MASK3){
				case sin01:
					CheckPotionNum[0] += InvenItem[i].sItemInfo.PotionCount;

				break;
				case sin02:
					CheckPotionNum[1] += InvenItem[i].sItemInfo.PotionCount;

				break;
				case sin03:
					CheckPotionNum[2] += InvenItem[i].sItemInfo.PotionCount;

				break;
				case sin04:
					CheckPotionNum[3] += InvenItem[i].sItemInfo.PotionCount;

				break;
				}
			}
		}
		if(InvenItemTemp[i].Flag){
			if(InvenItemTemp[i].Class  == ITEM_CLASS_POTION){
				switch(InvenItemTemp[i].CODE & sinITEM_MASK3){
				case sin01:
					CheckPotionNum[0] += InvenItemTemp[i].sItemInfo.PotionCount;

				break;
				case sin02:
					CheckPotionNum[1] += InvenItemTemp[i].sItemInfo.PotionCount;

				break;
				case sin03:
					CheckPotionNum[2] += InvenItemTemp[i].sItemInfo.PotionCount;

				break;
				case sin04:
					CheckPotionNum[3] += InvenItemTemp[i].sItemInfo.PotionCount;

				break;
				}
			}
		}
	}
	/*
	if(MouseItem.Flag){
		if(MouseItem.Class  == ITEM_CLASS_POTION){
			switch(MouseItem.sItemInfo.CODE & sinITEM_MASK3){
				case sin01:
					CheckPotionNum[0] += MouseItem.sItemInfo.PotionCount;

				break;
				case sin02:
					CheckPotionNum[1] += MouseItem.sItemInfo.PotionCount;

				break;
				case sin03:
					CheckPotionNum[2] += MouseItem.sItemInfo.PotionCount;

				break;
				case sin04:
					CheckPotionNum[3] += MouseItem.sItemInfo.PotionCount;

				break;
			}
		}
	}
	*/

	for(int j=0;j<4;j++){
		if(CheckPotionNum[j] !=sinPotionNum[j]){
			//SendSetHackUser(TRUE); //��ŷ�� �Ϸ����ߴ� ���� ������ ��� TRUE ���� ���� 
			SendSetHackUser2(1510,j); //��ŷ�� ������ �Ű��Ѵ�
		}
	}
	return TRUE;

}


//////////////// ���� Ư���� �������� üũ�Ѵ� 
int cINVENTORY::CheckSpecialItem(sITEM *pItem)
{
	//////����Ʈ�� �������ϰ�� 
	if(pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST || pItem->sItemInfo.UniqueItem)
		return FALSE;


	return TRUE;
}


/*----------------------------------------------------------------------------*
*						�κ��丮 ����Ʈ 
*-----------------------------------------------------------------------------*/	
//�κ��丮 ��ƼŬ�� �����ش� 
int dwInvenParticleShowTime = 0;
int cINVENTORY::ShowInvenEffectParticle()
{
	dwInvenParticleShowTime++; 
	if(dwInvenParticleShowTime <= 5)return FALSE;
	dwInvenParticleShowTime = 0;

	int TempX,TempY;
	
	if(MouseItem.Flag){
		if(MouseItem.sItemInfo.ItemKindCode == ITEM_KIND_QUEST || MouseItem.sItemInfo.UniqueItem){
			TempX = rand()%MouseItem.w;
			TempY = rand()%MouseItem.h;
			SetInvenParticle(MouseItem.x+TempX,MouseItem.y+TempY,SIN_EFFECT_SHOW_INVEN);

		}
	}

	for(int i = 0 ; i < INVENTORY_MAXITEM ; i++){  
		if(InvenItem[i].Flag){
			//////// ��ǰ�� ����Ʈ�� ������ �־�� (�ϴ� ����)
			/*
			if((InvenItem[i].sItemInfo.CODE & sinITEM_MASK2 ) == sinGP1 ){
				TempX = rand()%InvenItem[i].w;
				TempY = rand()%InvenItem[i].h;
				SetInvenParticle(InvenItem[i].x+TempX,InvenItem[i].y+TempY,SIN_EFFECT_SHOW_GYUNGFUM);

			}
			*/

			if(InvenItem[i].sItemInfo.ItemKindCode == ITEM_KIND_QUEST || InvenItem[i].sItemInfo.UniqueItem){
				TempX = rand()%InvenItem[i].w;
				TempY = rand()%InvenItem[i].h;
				SetInvenParticle(InvenItem[i].x+TempX,InvenItem[i].y+TempY,SIN_EFFECT_SHOW_INVEN);

				if(InvenItem[i].Class == ITEM_CLASS_WEAPON_TWO){
					if(i == sInven[0].ItemIndex-1 ){ //��չ��⿡���� ����Ʈ�� ������ ��¦ ������ �غ��ϴ�
						TempX = rand()%(sInven[1].Rect.right-10 - sInven[1].Rect.left+10);
						TempY = rand()%(sInven[1].Rect.bottom-10 - sInven[1].Rect.top+10);
						SetInvenParticle(sInven[1].Rect.left+TempX,sInven[1].Rect.top+TempY,SIN_EFFECT_SHOW_INVEN);
					}

				}

			}
		}
	}
	
	//Ʈ���̵� â���� ����Ʈ ���̱� 
	for ( int i = 0; i < MAX_TRADE_ITEM; i++ )
	{
		if(sTrade.TradeItem[i].Flag){
			if(sTrade.TradeItem[i].sItemInfo.UniqueItem){
				TempX = rand()%sTrade.TradeItem[i].w;
				TempY = rand()%sTrade.TradeItem[i].h;
				SetInvenParticle(sTrade.TradeItem[i].x+TempX,sTrade.TradeItem[i].y+TempY,SIN_EFFECT_SHOW_TRADE);

			}
		}
		if(sTradeRecv.TradeItem[i].Flag){
			if(sTradeRecv.TradeItem[i].sItemInfo.UniqueItem){
				TempX = rand()%sTradeRecv.TradeItem[i].w;
				TempY = rand()%sTradeRecv.TradeItem[i].h;
				SetInvenParticle(sTradeRecv.TradeItem[i].x+TempX,sTradeRecv.TradeItem[i].y+TempY,SIN_EFFECT_SHOW_TRADE);

			}
		}

	}

	//â������ۿ��� ����Ʈ ���̱�
	for ( int i = 0; i < 100; i++ )
	{
		if(sWareHouse.WareHouseItem[i].Flag){
			if(sWareHouse.WareHouseItem[i].sItemInfo.UniqueItem){
				TempX = rand()%sWareHouse.WareHouseItem[i].w;
				TempY = rand()%sWareHouse.WareHouseItem[i].h;
				SetInvenParticle(sWareHouse.WareHouseItem[i].x+TempX,sWareHouse.WareHouseItem[i].y+TempY,SIN_EFFECT_SHOW_WAREHOUSE);
			}
		}
	}
	return TRUE;
}

//����Ʈ�� �����Ѵ� 
int cINVENTORY::SetInvenParticle(int x , int y , int Kind)
{
	
	int i , k;
	int TempSize;
	int Count=0; 

	for(i = 0 ; i < MAX_INVEN_PARTICLE ; i++){     
		if(!sInven_Effect[i].Time){
			sInven_Effect[i].Kind = Kind;
			sInven_Effect[i].Time = 1; 
			sInven_Effect[i].Max_Time = rand()%20 +3;

			sInven_Effect[i].InvenFace.x = x;
			sInven_Effect[i].InvenFace.y = y;
			TempSize = rand()%13+1;
			sInven_Effect[i].InvenFace.width  = TempSize; 
			sInven_Effect[i].InvenFace.height = TempSize;

			//sInven_Effect[i].Speed.x = rand()%3+1;
			sInven_Effect[i].Speed.y = rand()%12+3;

			if(Kind == SIN_EFFECT_SHOW_GYUNGFUM){ //��� ��ǰ��  
				sInven_Effect[i].InvenFace.MatNum =	MatInvenParticle[4]; 
	//			sInven_Effect[i].InvenFace.r = 0;//rand()%255;
	//			sInven_Effect[i].InvenFace.g = rand()%255;
	//			sInven_Effect[i].InvenFace.b = rand()%255;
				sInven_Effect[i].InvenFace.r = 255;
				sInven_Effect[i].InvenFace.g = 255;
				sInven_Effect[i].InvenFace.b = 255;
				sInven_Effect[i].InvenFace.Transparency = rand()%55 + 200; 
				sInven_Effect[i].FadeType = 1;
				if(sInven_Effect[i].InvenFace.width > 5 ){
					sInven_Effect[i].InvenFace.width -= 2;
					sInven_Effect[i].InvenFace.height -= 2;

				}
				if(sInven_Effect[i].InvenFace.width < 5 ){
					memset(&sInven_Effect[i],0,sizeof(sINVENTORY_EFFECT));  //����� �� ��ġ�� -_-;;

				}

			}
			else{
				sInven_Effect[i].InvenFace.MatNum =	MatInvenParticle[0];
	//			sInven_Effect[i].InvenFace.r = 0;//rand()%255;
	//			sInven_Effect[i].InvenFace.g = rand()%255;
	//			sInven_Effect[i].InvenFace.b = rand()%255;
				sInven_Effect[i].InvenFace.r = 255;
				sInven_Effect[i].InvenFace.g = 255;
				sInven_Effect[i].InvenFace.b = 255;
				sInven_Effect[i].InvenFace.Transparency = rand()%55 + 200; 
				sInven_Effect[i].FadeType = 1;
			}
			///////��ġ�� ����(������ ��ġ�� ������ٳ� ��...) 
			if(Kind == 1){ //�κ��丮
				for(k = 0 ; k < MAX_INVEN_PARTICLE ; k++){    
					if(!sInven_Effect[k].Time){
						Count++;
						if(Count > 2){
							Count = 0;
							break;

						}
						memcpy(&sInven_Effect[k],&sInven_Effect[i],sizeof(sINVENTORY_EFFECT));
					}
					
				}
			}
			break;
		}

	}
	
	return TRUE;
}

DWORD dwInvenParticleMoveTime =0;
//�κ��丮 ����Ʈ�� �����δ�
int cINVENTORY::MoveInvenParticle() //������ ���� �ǵ��� ����!
{
	dwInvenParticleMoveTime++;
	if(dwInvenParticleMoveTime <= 5)return FALSE;
	dwInvenParticleMoveTime = 0;

	int i = 0;
	for(i = 0 ; i < MAX_INVEN_PARTICLE ; i++){    
		if(sInven_Effect[i].Time){ 
			sInven_Effect[i].Time++;
			//if(sInven_Effect[i].Time >= sInven_Effect[i].Max_Time)sInven_Effect[i].Time = 0;
			sInven_Effect[i].InvenFace.y -= sInven_Effect[i].Speed.y;

			if(sInven_Effect[i].FadeType == 1) 
				sInven_Effect[i].InvenFace.Transparency += 14;
			if(sInven_Effect[i].FadeType == 2)
				sInven_Effect[i].InvenFace.Transparency -= 30;
			
			if(sInven_Effect[i].InvenFace.Transparency >= 255)
				sInven_Effect[i].FadeType = 2;
			
			if(sInven_Effect[i].InvenFace.Transparency <= 0)
				sInven_Effect[i].Time = 0;

			if(sInven_Effect[i].Kind != SIN_EFFECT_SHOW_GYUNGFUM){ 
				if((sInven_Effect[i].Time%5) == 0){ 
					sInven_Effect[i].AniCount++;
					if(sInven_Effect[i].AniCount > 3)sInven_Effect[i].AniCount = 0;
					sInven_Effect[i].InvenFace.MatNum = MatInvenParticle[sInven_Effect[i].AniCount];

				}
			}

			if(sInven_Effect[i].InvenFace.Transparency <= 0)sInven_Effect[i].Time = 0; 
			
		}

	}

	return TRUE;
}

//����Ʈ �̹����� �׸��� 
int cINVENTORY::sinDrawInvenTexImage(smFACE2D *Face) { return TRUE; }


//�������� ���õɼ��ִ� ���� üũ 
int cINVENTORY::CheckSetEmptyArea(sITEM *pItem)
{
	int cntx,cnty;
	int cx,cy;

	RECT	rect={0,0,0,0};
	int		flag=0;

	cx = (22*INVENTORY_BOX_ROW)-pItem->w; //�������� �����ִ� ���� �� X��ǥ 
	cy = (22*INVENTORY_BOX_COL)-pItem->h; //�������� �����ִ� ���� �� Y��ǥ

	//�ڵ尡 ���� �ʰų� �������� ������� ���� ���� �����Ҷ� �˻��ؼ� ��ġ�� ã�Ƴ��� 
	for( cntx=StartX ; cntx <= StartX+cx ; cntx+=22){
		for( cnty=StartY ; cnty <= StartY+cy ; cnty+=22){ 
			flag = 0;
			for(int i=0 ; i<INVENTORY_MAXITEM ; i++){
				if(InvenItem[i].Flag){
					rect.left   = InvenItem[i].x;
					rect.right  = InvenItem[i].x+InvenItem[i].w;
					rect.top    = InvenItem[i].y;
					rect.bottom = InvenItem[i].y+InvenItem[i].h;

					if( cntx > rect.left-pItem->w && cntx< rect.right && 
						cnty > rect.top-pItem->h && cnty< rect.bottom )
						flag++;
				}
			}
			if ( flag==0 ) {
				pItem->SetX = cntx;
				pItem->SetY = cnty;
				pItem->ItemPosition = 0; 
				return TRUE;

			}
		}
	}

	return FALSE;

}

//������ ������ (���� �޼���) 
int cINVENTORY::ResetInvenItemToServer(DWORD CODE ,DWORD Head , DWORD CheckSum , DWORD Time )
{	
	int i = 0;
	for(i = 0; i < INVENTORY_MAXITEM ; i++){
		if(InvenItem[i].Flag){
			if(InvenItem[i].CODE == CODE && 
				InvenItem[i].sItemInfo.ItemHeader.Head == Head &&
				InvenItem[i].sItemInfo.ItemHeader.dwChkSum == CheckSum ){
					InvenItem[i].sItemInfo.ItemHeader.dwTime = Time;
					return TRUE;

				}

		}
		if(InvenItemTemp[i].Flag){
			if(InvenItemTemp[i].CODE == CODE && 
				InvenItemTemp[i].sItemInfo.ItemHeader.Head == Head &&
				InvenItemTemp[i].sItemInfo.ItemHeader.dwChkSum == CheckSum ){
					InvenItemTemp[i].sItemInfo.ItemHeader.dwTime = Time;
					return TRUE;

				}

		}
	}
	return FALSE;
}

//������ ���� (���� �޼���)
int cINVENTORY::DeleteInvenItemToServer(DWORD CODE ,DWORD Head , DWORD CheckSum)				
{

	//���콺 �������� üũ���ش� 
	if(MouseItem.Flag && MouseItem.CODE == CODE && 
		MouseItem.sItemInfo.ItemHeader.Head == Head &&
		MouseItem.sItemInfo.ItemHeader.dwChkSum == CheckSum ){
			MouseItem.Flag = 0;
	}

	int i = 0;
	for(i = 0; i < INVENTORY_MAXITEM ; i++){
		if(InvenItem[i].Flag){
			if(InvenItem[i].CODE == CODE && 
				InvenItem[i].sItemInfo.ItemHeader.Head == Head &&
				InvenItem[i].sItemInfo.ItemHeader.dwChkSum == CheckSum ){
					InvenItem[i].Flag = 0;
					if(InvenItem[i].ItemPosition){
						//��վ������� �Ѽտ� ������쿡�� �����ش� 
						if(InvenItem[i].Class == ITEM_CLASS_WEAPON_TWO){
							if(InvenItem[i].ItemPosition == 1 ){//������ 
								if(InvenItem[i].CODE != InvenItem[sInven[1].ItemIndex-1].CODE){
									InvenItem[sInven[1].ItemIndex-1].Flag = 0;
									InvenItem[i].Flag = 0;
									sInven[1].ItemIndex = 0; //�κ��丮 �ڽ� �ʱ�ȭ 
									sInven[0].ItemIndex = 0; //�κ��丮 �ڽ� �ʱ�ȭ 
									if(InvenItem[i].SetModelPosi)
										sinSetCharItem(InvenItem[i].CODE , InvenItem[i].SetModelPosi, FALSE); 

								}
							}
							if(InvenItem[i].ItemPosition == 2 ){//�޼� 
								if(InvenItem[i].CODE != InvenItem[sInven[0].ItemIndex-1].CODE){
									InvenItem[sInven[0].ItemIndex-1].Flag = 0;
									InvenItem[i].Flag = 0;
									sInven[0].ItemIndex = 0; //�κ��丮 �ڽ� �ʱ�ȭ 
									sInven[1].ItemIndex = 0; //�κ��丮 �ڽ� �ʱ�ȭ 
									if(InvenItem[i].SetModelPosi)
										sinSetCharItem(InvenItem[i].CODE , InvenItem[i].SetModelPosi, FALSE); 

								}
							}

						}
						sInven[InvenItem[i].ItemPosition-1].ItemIndex  = 0 ;
							if(InvenItem[i].SetModelPosi)
								sinSetCharItem(InvenItem[i].CODE , InvenItem[i].SetModelPosi, FALSE); 

					}
					ReFormInvenItem();
					ReformCharForm();//������ 
					ReFormPotionNum();
					SetItemToChar();
					break;

				}

		}
		if(InvenItemTemp[i].Flag){
			if(InvenItemTemp[i].CODE == CODE && 
				InvenItemTemp[i].sItemInfo.ItemHeader.Head == Head &&
				InvenItemTemp[i].sItemInfo.ItemHeader.dwChkSum == CheckSum ){
					InvenItemTemp[i].Flag = 0;
					ReFormInvenItem();
					ReformCharForm();//������ 
					ReFormPotionNum();
					SetItemToChar();
					break;

				}
		}
	}

	//��� �������� ������� üũ�ؼ� �ٽ��ѹ� �����ش�
	if(!sInven[0].ItemIndex){
		if(sInven[1].ItemIndex){
			if(InvenItem[sInven[1].ItemIndex-1].Flag){
				if(InvenItem[sInven[1].ItemIndex-1].Class == ITEM_CLASS_WEAPON_TWO){
					if(!InvenItem[sInven[1].ItemIndex-1].sItemInfo.ItemHeader.Head){
						InvenItem[sInven[1].ItemIndex-1].Flag = 0;
						sInven[1].ItemIndex = 0;
						ReFormInvenItem();
						ReformCharForm();//������ 
						ReFormPotionNum();
						SetItemToChar();
					}
				}
			}
		}
	}
	cInvenTory.CheckWeight();
	return TRUE;
}

//ĳ���� �Ķ���� ������ �����Ѵ� 
int cINVENTORY::HackCharStateCheck(smCHAR_INFO *pChar_Info , smCHAR_INFO *desChar_Info)
{
	int HackFlag = 0;

	if(pChar_Info->Attack_Damage[0] < desChar_Info->Attack_Damage[0]){
		HackFlag = 1;

	}
	if(pChar_Info->Attack_Damage[1] < desChar_Info->Attack_Damage[1]){
		HackFlag = 1;

	}
	if(pChar_Info->Defence < desChar_Info->Defence){
		HackFlag = 1;

	}
	if(pChar_Info->Absorption < desChar_Info->Absorption){
		HackFlag = 1;

	}
	if(pChar_Info->Accuracy < desChar_Info->Accuracy){
		HackFlag = 1;

	}
	if(pChar_Info->Attack_Speed < desChar_Info->Attack_Speed){
		HackFlag = 1;

	}
	if(pChar_Info->Chance_Block < desChar_Info->Chance_Block){
		HackFlag = 1;

	}
	if(pChar_Info->Critical_Hit < desChar_Info->Critical_Hit){
		HackFlag = 1;

	}
	if(pChar_Info->Shooting_Range < desChar_Info->Shooting_Range){
		HackFlag = 1;

	}
	if(HackFlag){
		smTRANS_COMMAND	smTransCommand;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_FIX_ATTACK;
		smTransCommand.WParam = pChar_Info->Attack_Damage[1];
		smTransCommand.LParam = pChar_Info->Defence;
		smTransCommand.SParam = (int)(pChar_Info->Absorption*256);
		smTransCommand.EParam = 0;
		if ( smWsockDataServer ) 
			smWsockDataServer->Send( (char *)&smTransCommand , smTransCommand.size , TRUE );

		return FALSE;
	}
	return TRUE;
}
	
//�߸� ��ġ�� �������� ���ġ�Ѵ� 
int cINVENTORY::CheckResetInvenItem()
{
	RECT rect;
	for(int i = 0; i < INVENTORY_MAXITEM ; i++){
		if(InvenItem[i].Flag){
			if(InvenItem[i].ItemPosition){
				if(!sInven[InvenItem[i].ItemPosition-1].ItemIndex || sInven[InvenItem[i].ItemPosition-1].ItemIndex-1 != i )continue;
				rect.left   = sInven[InvenItem[i].ItemPosition-1].Rect.left;
				rect.top    = sInven[InvenItem[i].ItemPosition-1].Rect.top;
				rect.right  = sInven[InvenItem[i].ItemPosition-1].Rect.right;
				rect.bottom = sInven[InvenItem[i].ItemPosition-1].Rect.bottom;
				
				if(InvenItem[i].x <	rect.left || InvenItem[i].y < rect.top ||
					InvenItem[i].x + InvenItem[i].w > rect.right+2 || InvenItem[i].y + InvenItem[i].h > rect.bottom+2 ){
						
						InvenItem[i].x = rect.left + (((rect.right - rect.left) - InvenItem[i].w)/2);
						InvenItem[i].y = rect.top + (((rect.bottom - rect.top) - InvenItem[i].h)/2);
						ReFormInvenItem();
				}
			}

		}
		if(InvenItemTemp[i].Flag){
			if(InvenItemTemp[i].ItemPosition){
				rect.left   = sInven[InvenItemTemp[i].ItemPosition-1].Rect.left;
				rect.top    = sInven[InvenItemTemp[i].ItemPosition-1].Rect.top;
				rect.right  = sInven[InvenItemTemp[i].ItemPosition-1].Rect.right;
				rect.bottom = sInven[InvenItemTemp[i].ItemPosition-1].Rect.bottom;
				
				if(InvenItemTemp[i].x <	rect.left || InvenItemTemp[i].y < rect.top ||
					InvenItemTemp[i].x + InvenItemTemp[i].w > rect.right+2 || InvenItemTemp[i].y + InvenItemTemp[i].h > rect.bottom+2 ){
						
						InvenItemTemp[i].x = rect.left + (((rect.right - rect.left) - InvenItemTemp[i].w)/2);
						InvenItemTemp[i].y = rect.top + (((rect.bottom - rect.top) - InvenItemTemp[i].h)/2);
						ReFormInvenItem();

				}
			}
		}
	}
	return TRUE;
}

//���� �ڵ��� �������� �ִ����� ã�´�
int cINVENTORY::SearchItemCode(DWORD CODE , int KindFlag)
{
	int ItemCount=0;
	if(CODE){
		for(int i = 0; i < INVENTORY_MAXITEM ; i++){
			if(InvenItem[i].Flag){
				if(InvenItem[i].CODE == CODE)ItemCount++;
			}
			if(InvenItemTemp[i].Flag){
				if(InvenItemTemp[i].CODE == CODE)ItemCount++;
			}
		}
		return ItemCount;
	}

	if(KindFlag){
		for(int i = 0; i < INVENTORY_MAXITEM ; i++){
			if(InvenItem[i].Flag){
				if(InvenItem[i].sItemInfo.ItemKindCode == KindFlag)ItemCount++;
			}
			if(InvenItemTemp[i].Flag){
				if(InvenItemTemp[i].sItemInfo.ItemKindCode == KindFlag)ItemCount++;
			}
		}
		return ItemCount;
	}
	return FALSE;
}

//�ִ뵥������ ���ü��ִ� �������� üũ�ؼ� ������ �����ش� 
int cINVENTORY::CheckDamage()
{
	int Damage[2] = {0,0};
	int Critical = 0;
	int SendDamage[2] = {0,0};
	int SendCritical = 0;
	int RealDamage[2] = {0,0};
	int RealSendCritical = 0;

	int i = 0 , j = 0 , k=0 ,t=0;

	DWORD WeaponCode[8] = {sinWA1,sinWS1,sinWP1,sinWS2,sinWT1,sinWM1,sinWM1};
	int   CharCode[8]   = {SIN_CHAR_FIGHTER,SIN_CHAR_ARCHER,SIN_CHAR_PIKEMAN,SIN_CHAR_KNIGHT,SIN_CHAR_ATALANTA,SIN_CHAR_PRIESTESS,SIN_CHAR_MAGICIAN, JOBCODE_ASSASSIN };

	sITEM *pItem=0;
	pItem = new sITEM;
	for( i = 0; i < INVENTORY_MAXITEM*2 ; i++){
		Damage[0] = 0; Damage[1] = 0; Critical = 0; //�ʱ�ȭ 
		if(i<100){
			if(!InvenItem[i].Flag)continue;
			if(InvenItem[i].NotUseFlag)continue;
			memcpy(pItem,&InvenItem[i],sizeof(sITEM));

		}
		else{
			if(!InvenItemTemp[i-100].Flag)continue;
			if(InvenItemTemp[i-100].NotUseFlag)continue;
			memcpy(pItem,&InvenItemTemp[i-100],sizeof(sITEM));
		}
		if(pItem->sItemInfo.Damage[0] || pItem->sItemInfo.Damage[1] || pItem->sItemInfo.Critical_Hit){
			Damage[0] += pItem->sItemInfo.Damage[0];
			Damage[1] += pItem->sItemInfo.Damage[1];
			Critical  += pItem->sItemInfo.Critical_Hit;

			//�ڻ��ް�����
			if((sinDamageFunction[0] == 1 && (pItem->WeaponClass == 1 || pItem->WeaponClass == 3))){
				SendDamage[0] = 1+(Damage[0]*(sinChar->Strength+130)/130) +
											((sinChar->Talent + sinChar->Dexterity)/40)+((Damage[0]+Damage[1])/16);
				SendDamage[1] = 3+(Damage[1]*(sinChar->Strength+130)/130) + 
											((sinChar->Talent + sinChar->Dexterity)/40);
			}

			if((sinDamageFunction[0] == 2 && (pItem->WeaponClass == 1 || pItem->WeaponClass == 3))){
			////(������2)
				SendDamage[0] = 1+(Damage[0]*(sinChar->Strength+150)/150) +
											((sinChar->Talent + sinChar->Dexterity)/45)+((Damage[0]+Damage[1])/16);
				SendDamage[1] = 3+(Damage[1]*(sinChar->Strength+150)/150) +
											((sinChar->Talent + sinChar->Dexterity)/45);
			}
			if((sinDamageFunction[0] == 3 && (pItem->WeaponClass == 1 || pItem->WeaponClass == 3))){
			////(������3)
				SendDamage[0] = 1+(Damage[0]*(sinChar->Strength+190)/190) +
											((sinChar->Talent + sinChar->Dexterity)/50)+((Damage[0]+Damage[1])/16);
				SendDamage[1] = 3+(Damage[1]*(sinChar->Strength+190)/190) +
											((sinChar->Talent + sinChar->Dexterity)/50);
			}
			if(sinDamageFunction[1] == 1 && pItem->WeaponClass == 2){
			////(�߻���1)
				SendDamage[0] = 1+(Damage[0]*(sinChar->Dexterity+130)/130) + 
											((sinChar->Talent + sinChar->Strength)/40)+ ((Damage[0]+Damage[1])/16);
				SendDamage[1] = 3+(Damage[1]*(sinChar->Dexterity+130)/130) + 
											((sinChar->Talent + sinChar->Strength)/40);
			}

			if(sinDamageFunction[1] == 2 && pItem->WeaponClass == 2){
			////(�߻���2)
				SendDamage[0] = 1+(Damage[0]*(sinChar->Dexterity+190)/190) +
											((sinChar->Talent + sinChar->Strength)/50)+((Damage[0]+Damage[1])/16);
				SendDamage[1] = 3+(Damage[1]*(sinChar->Dexterity+190)/190) +
											((sinChar->Talent + sinChar->Strength)/50);
			}



			if(sinDamageFunction[2] == 1 && pItem->WeaponClass == 3){
			////(������1)
				SendDamage[0] = 1+(Damage[0]*(sinChar->Spirit+150)/150) +
											((sinChar->Talent)/30)+((Damage[0]+Damage[1])/16);
				SendDamage[1] = 3+(Damage[1]*(sinChar->Spirit+150)/150) +
											((sinChar->Talent)/30);
			}

			if(sinDamageFunction[2] == 2 && pItem->WeaponClass == 3){
			////(������2)
				SendDamage[0] = 1+(Damage[0]*(sinChar->Spirit+180)/180) +
											((sinChar->Talent)/30);
				SendDamage[1] = 2+(Damage[1]*(sinChar->Spirit+180)/180) +
											((sinChar->Talent)/25);
			}
			if(sinDamageFunction[2] == 2 && pItem->WeaponClass == 3){
			////(������2)
				SendDamage[0] = 1+(Damage[0]*(sinChar->Spirit+170)/170) +
											((sinChar->Talent)/30)+ ((Damage[0]+Damage[1])/16);
				SendDamage[1] = 3+(Damage[1]*(sinChar->Spirit+170)/170) +
											((sinChar->Talent)/30);
			}

			//�ֹ��ⱺ 
			for( j= 0 ; j < 8 ; j++){ 
				if(CharCode[j] == sinChar->JOB_CODE){
					if(WeaponCode[j] == (pItem->sItemInfo.CODE & sinITEM_MASK2)){
						SendDamage[0] += sinChar->Level/6;
						SendDamage[1] += sinChar->Level/6;
					}
				}
			}
			//��ī�ϼ��� �ֹ��ⱺ�� Ưȭ�� �����Ǿ��ִ� 
			if(sinChar->JOB_CODE == SIN_CHAR_MECANICIAN){
				if(sinChar->JobBitMask & pItem->sItemInfo.JobCodeMask){
					SendDamage[0] += sinChar->Level/6;
					SendDamage[1] += sinChar->Level/6;
				}		
			}


			//��ų
			//////////////////////// ������ ����ġ 
			for(k = 1 ; k < MAX_USESKILL  ; k++){ //��� ������ ���ش� 
				if(sinSkill.UseSkill[k].Flag && sinSkill.UseSkill[k].Point){ //��� ����Ʈ�� ������ 
					//////////////���� �迭�����ϰ�쿡 �ش� 
					for(t = 0; t < 8 ; t++){
						switch(sinSkill.UseSkill[k].CODE){
							case SKILL_MELEE_MASTERY:       //������ ���� 
								if(sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItemInfo.CODE&sinITEM_MASK2)){
									SendDamage[0] += (int)(((float)Melee_Mastery_DamagePercent[sinSkill.UseSkill[k].Point-1]/100)*pItem->sItemInfo.Damage[0]);
									SendDamage[1] += (int)(((float)Melee_Mastery_DamagePercent[sinSkill.UseSkill[k].Point-1]/100)*pItem->sItemInfo.Damage[1]);
								}
							break;
							case SKILL_SHOOTING_MASTERY:    //Ȱ ������ ����  
								if(sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItemInfo.CODE&sinITEM_MASK2)){
									SendDamage[0] += (int)(((float)S_Mastery_DamagePercent[sinSkill.UseSkill[k].Point-1]/100)*pItem->sItemInfo.Damage[0]);
									SendDamage[1] += (int)(((float)S_Mastery_DamagePercent[sinSkill.UseSkill[k].Point-1]/100)*pItem->sItemInfo.Damage[1]);
							
								}	
							break;
							case SKILL_THROWING_MASTERY:
								if(sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItemInfo.CODE&sinITEM_MASK2)){
									SendDamage[0] += (int)(((float)T_Mastery_Damage[sinSkill.UseSkill[k].Point-1]/100)*pItem->sItemInfo.Damage[0]);
									SendDamage[1] += (int)(((float)T_Mastery_Damage[sinSkill.UseSkill[k].Point-1]/100)*pItem->sItemInfo.Damage[1]);
							}
							break;
							case SKILL_CRITICAL_MASTERY:
								if(sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItemInfo.CODE&sinITEM_MASK2)){
									Critical += Critical_Mastery_Critical[sinSkill.UseSkill[k].Point-1];

								}
							break;
							case SKILL_SWORD_MASTERY:
								if(sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItemInfo.CODE&sinITEM_MASK2)){
									SendDamage[0] += (int)(((float)Sword_Mastery_DamagePercent[sinSkill.UseSkill[k].Point-1]/100)*pItem->sItemInfo.Damage[0]);
									SendDamage[1] += (int)(((float)Sword_Mastery_DamagePercent[sinSkill.UseSkill[k].Point-1]/100)*pItem->sItemInfo.Damage[1]);
							
								}	
							break;

						}
					}
				}
			}

			//Ưȭ 
			if(sinChar->JobBitMask & pItem->sItemInfo.JobCodeMask){
				if(pItem->sItemInfo.JobItem.Lev_Damage[1]) // LV/x Ưȭ +������ sinLev_Damage[0]�� ����ϰ������ʴ�
					SendDamage[1] +=  (sinChar->Level /pItem->sItemInfo.JobItem.Lev_Damage[1]);			//���ݷ�
				if(pItem->sItemInfo.JobItem.Add_Critical_Hit)
					Critical  += pItem->sItemInfo.JobItem.Add_Critical_Hit;	//1.5�� ������Ȯ��
			}
			SendCritical = Critical;
			SendDamage[0] += 1; //�߰� ������ 
			SendDamage[1] += 1;

			if(RealDamage[0] < SendDamage[0] ){
				RealDamage[0] = SendDamage[0];
			}
			if(RealDamage[1] < SendDamage[1] ){
				RealDamage[1] = SendDamage[1];
			}
			if(RealSendCritical < SendCritical )
				RealSendCritical = SendCritical;
		}
	}

	//��⼭ ���� �����ش� SendDamage�� ������ 
	SendMaxDamageToServer(RealDamage[0],RealDamage[1],RealSendCritical);
	return TRUE;
}


//����Ʈ �������� üũ�ؼ� ���������� 
int cINVENTORY::ClearQuestItem()
{
	sITEM *pItem=0;
	for(int i = 0; i < INVENTORY_MAXITEM*2 ; i++){
		if(i<100){
			if(!InvenItem[i].Flag)continue;
			pItem = &InvenItem[i];
		}
		else{
			if(!InvenItemTemp[i-100].Flag)continue;
			pItem = &InvenItemTemp[i-100];
		}
		if((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA2){
			pItem->Flag = 0;
		}
	}	
	cInvenTory.ReFormInvenItem();
	ResetInvenItemCode();
	return TRUE;
}

// pluto Ŀ�ø�
int cINVENTORY::DeleteCoupleRing()
{
	sITEM *pItem=0;
	for(int i = 0; i < INVENTORY_MAXITEM*2 ; i++)
	{
		if(i<100)
		{
			if(!InvenItem[i].Flag)continue;
			pItem = &InvenItem[i];
		}
		else
		{
			if(!InvenItemTemp[i-100].Flag)continue;
			pItem = &InvenItemTemp[i-100];
		}
		if( pItem->sItemInfo.CODE == (sinSP1|sin16) )
		{
			pItem->Flag = 0;
			break;
		}
	}	
	cInvenTory.ReFormInvenItem();
	ResetInvenItemCode();
	return TRUE;
}

//��ũ�ھ� ����Ÿ�� �������� �޴´�
int cINVENTORY::RecvLinkCore(sITEMINFO *pItemInfo)
{
	sITEMINFO *pItemInfo2=0;
	for(int i = 0; i < INVENTORY_MAXITEM*2 ; i++){
		if(i<100){
			if(!InvenItem[i].Flag)continue;
			pItemInfo2 = &InvenItem[i].sItemInfo;
		}
		else{
			if(!InvenItemTemp[i-100].Flag)continue;
			pItemInfo2 = &InvenItemTemp[i-100].sItemInfo;
		}
		if(pItemInfo->BackUpChkSum == pItemInfo2->BackUpChkSum &&
			pItemInfo->BackUpKey == pItemInfo2->BackUpKey &&
			pItemInfo->CODE == pItemInfo2->CODE){
				memcpy(pItemInfo2,pItemInfo,sizeof(sITEMINFO));
				CheckWeight();//���� ���� 
				ReFormInvenItem();
				return TRUE;

			}
	}
	return FALSE;
}
int sinMousePotionNum[4] = {0,0,0,0};
int ChecMousekPotionNum[4] = { 0,0,0,0};

//���콺�� ������ üũ�Ѵ�
int cINVENTORY::CheckMousePotionNumForm()
{
	for(int k=0;k<4;k++){
		ChecMousekPotionNum[k] = 0;
	
	}	

	if(MouseItem.Flag){
		if(MouseItem.Class  == ITEM_CLASS_POTION){
			switch(MouseItem.sItemInfo.CODE & sinITEM_MASK3){
				case sin01:
					ChecMousekPotionNum[0] += MouseItem.sItemInfo.PotionCount;

				break;
				case sin02:
					ChecMousekPotionNum[1] += MouseItem.sItemInfo.PotionCount;

				break;
				case sin03:
					ChecMousekPotionNum[2] += MouseItem.sItemInfo.PotionCount;

				break;
				case sin04:
					ChecMousekPotionNum[3] += MouseItem.sItemInfo.PotionCount;

				break;
			}
		}
	}
	for(int j=0;j<4;j++){
		if(ChecMousekPotionNum[j] !=sinMousePotionNum[j]){
			//SendSetHackUser(TRUE); //��ŷ�� �Ϸ����ߴ� ���� ������ ��� TRUE ���� ���� 
			SendSetHackUser2(1510,j); //��ŷ�� ������ �Ű��Ѵ�
			

		}

	}

	return TRUE;
}
//���콺�� ������ �����Ѵ� 
int cINVENTORY::ReFormMousePotionNum()
{
	for(int j=0;j<4;j++){
		sinMousePotionNum[j] = 0;
	
	}	
	if(MouseItem.Flag){
		if(MouseItem.Class  == ITEM_CLASS_POTION){
			switch(MouseItem.sItemInfo.CODE & sinITEM_MASK3){
				case sin01:
					sinMousePotionNum[0] += MouseItem.sItemInfo.PotionCount;

				break;
				case sin02:
					sinMousePotionNum[1] += MouseItem.sItemInfo.PotionCount;

				break;
				case sin03:
					sinMousePotionNum[2] += MouseItem.sItemInfo.PotionCount;

				break;
				case sin04:
					sinMousePotionNum[3] += MouseItem.sItemInfo.PotionCount;

				break;
			}
		}
	}
	return TRUE;
}

//���Ͽ� �ھ� ����Ʈ�� �����Ѵ�
int cINVENTORY::SetUnionCoreEffect(int x , int y) { return TRUE; }

int cINVENTORY::UnionCoreParticleProcess() { return TRUE; }

int cINVENTORY::UnionCoreParticle(int x , int y) { return TRUE; }

//���Ͽ� �ھ� ������ ����Ʈ 
int cINVENTORY::UnionCoreParticle2(int x , int y , int Flag) { return TRUE; }


//�ڵ�� �κ��丮 ������ üũ�Ѵ� 
int cINVENTORY::CheckInvenEmpty(sITEM *pItem) { return TRUE; }

//���̹����� ����ġ �̹����� �ε��Ѵ� 
int cINVENTORY::LoadMoneyExpImage(sITEM *pItem) { return TRUE; }

//sItemInfo�� �������� �κ��丮�� �����Ѵ�
int cINVENTORY::SetInvenToItemInfo(sITEMINFO *pItemInfo)
{

	//���� ���
	if(pItemInfo->CODE == (sinGG1|sin01)){
		CheckCharForm();//���� 
		sinPlusMoney(pItemInfo->Money);
		ReformCharForm();//������ 	
		SendSaveMoney(); //�ݾ� ������ ���ϰ��ϱ����� ȣ���Ѵ� 
		return TRUE;
	}

	//����ġ�ϰ�� 
	if(pItemInfo->CODE == (sinGG1|sin02)){
		AddExp(pItemInfo->Money );
		return TRUE;

	}

	//�������� ��� 
	sITEM TempItem;
	if(LoadItemImage(pItemInfo , &TempItem)){
		if(cInvenTory.CheckRequireItemToSet(&TempItem)){         //��ٷ� ���õɼ��ִ����� üũ�Ѵ�  
			if(!cInvenTory.AutoSetInvenItem(&TempItem,1)){
				TempItem.Flag = 0;
				return FALSE;
			}
		}
	}
	return TRUE;
}

/*******************************************************************************
*						Wing Item 
********************************************************************************/	
int cINVENTORY::sinWingQuestNpc() { return TRUE; }

//�����Ҽ��ִ� ������������ �ѹ��� üũ�Ѵ� 
int cINVENTORY::CheckRequireItemToSet2(sITEM *pItem)
{
	int NotUseItemFlag = 0;

	if(pItem->sItemInfo.Level     > sinChar->Level )NotUseItemFlag = 1;
	if(pItem->sItemInfo.Dexterity > sinChar->Dexterity)NotUseItemFlag = 1;
	if(pItem->sItemInfo.Strength  > sinChar->Strength)NotUseItemFlag = 1;
	if(pItem->sItemInfo.Talent    > sinChar->Talent)NotUseItemFlag = 1;
	if(pItem->sItemInfo.Spirit    > sinChar->Spirit)NotUseItemFlag = 1;
	if(pItem->sItemInfo.Health    > sinChar->Health)NotUseItemFlag = 1;
	if((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinFO1){
		int i = 0;
		for(i = 0; i < 12 ; i++){ 
			if((pItem->CODE&sinITEM_MASK3)== SheltomCode2[i]){
				break;
			}
		}
		if(sinChar->Level < ForceOrbUseLevel[i][0] ||
			sinChar->Level > ForceOrbUseLevel[i][1]){
			NotUseItemFlag = 1;
		}
		else{
			NotUseItemFlag = 0;

		}

	}

	if(NotUseItemFlag){
		return FALSE;
	}
	return TRUE;
}

//����Ⱦ����� ����
int cINVENTORY::CheckSpecialItemPosi()
{
	int j = 0;
	for(int i=0 ; i < 84 ; i++){ 
		if(InvenItem[i].Flag){ 
			if(InvenItem[i].sItemInfo.SpecialItemFlag[1] == ITEM_KIND_SPECIAL){
				for( j = 84 ; j < INVENTORY_MAXITEM ; j++){
					if(!InvenItem[j].Flag){
						memcpy(&InvenItem[j],&InvenItem[i],sizeof(sITEM));
						memset(&InvenItem[i],0,sizeof(sITEM));

					}
				}
			}
		}
		if(InvenItemTemp[i].Flag){ 
			if(InvenItemTemp[i].sItemInfo.SpecialItemFlag[1] == ITEM_KIND_SPECIAL){
				for( j = 84 ; j < INVENTORY_MAXITEM ; j++){
					if(!InvenItem[j].Flag){
						memcpy(&InvenItem[j],&InvenItemTemp[i],sizeof(sITEM));
						memset(&InvenItemTemp[i],0,sizeof(sITEM));

					}
				}
			}
		}

	}
	ReFormInvenItem();
	ReformCharForm();//������ 
	ReFormPotionNum();
	SetItemToChar();
	return TRUE;
}

//����Ⱦ������� �����ش�
int cINVENTORY::ChangeSpecialItem(int Flag)
{
	if(Flag==1){ //AB��ư���� ������ �յڰ� �ٲ� ����Ⱦ�����â�� �������� �ٲ��ش�
		if(SpecialItemShowFlag){
			SpecialItemShowFlag = 0;

		}
		else return FALSE;
	}
	else if (Flag ==2){ //�������� �Լ��Ҷ��� �ŷ��Ҷ� â�� ���� ������ ���� ��� â�� �ٲ۴�
		SpecialItemShowFlag = 0;

	}
	else SpecialItemShowFlag ^=1;


	//����Ⱦ������� ��ǥ�� �̵���Ų��
	for(int i=0 ; i < INVENTORY_MAXITEM ; i++){ 
		if(InvenItem[i].Flag){ 
			if(SpecialItemShowFlag){ //Ư���� �������� ���÷��̸� �ٸ����Ѵ�
				if(InvenItem[i].sItemInfo.SpecialItemFlag[1] == ITEM_KIND_SPECIAL){
					if(InvenItem[i].x > 10000){
						InvenItem[i].x -= 10000;
					}
				}
				else {
					if(!InvenItem[i].ItemPosition && InvenItem[i].x < 10000){
							InvenItem[i].x += 10000;
					}
				}
			}
			else{
				if(InvenItem[i].sItemInfo.SpecialItemFlag[1] == ITEM_KIND_SPECIAL){
					if(InvenItem[i].x < 10000){
						InvenItem[i].x += 10000;
					}
				}
				else{
					if(!InvenItem[i].ItemPosition){
						if(InvenItem[i].x > 10000){
							InvenItem[i].x -= 10000;
						}
					}
				}
			}
		}
	}
	return TRUE;
}
//�ڵ峪 ������ ������ �κ��丮 ������ �ε����� �����Ѵ�
int cINVENTORY::SearchItemIndex(DWORD CODE , int KindFlag)
{
	int i = 0; 
	if(CODE){
		for(i = 0; i < INVENTORY_MAXITEM ; i++){
			if(InvenItem[i].Flag){
				if(InvenItem[i].CODE == CODE){
					return i+1;

				}
			}
		}
		for(i = 0; i < INVENTORY_MAXITEM ; i++){
			if(InvenItemTemp[i].Flag){
				if(InvenItemTemp[i].CODE == CODE){
					return 100+i+1;
				}
			}
		}
	}

	if(KindFlag){
		for(int i = 0; i < INVENTORY_MAXITEM ; i++){
			if(InvenItem[i].Flag){
				if(InvenItem[i].sItemInfo.ItemKindCode == KindFlag){
					return i+1;

				}
			}
			if(InvenItemTemp[i].Flag){
				if(InvenItemTemp[i].sItemInfo.ItemKindCode == KindFlag){
					return 100+i+1;
					
				}
			}
		}
	}
	return FALSE;
}

//����� - ���� ��ƿ���
int WatermelonEventItemIndex[INVENTORY_MAXITEM*2] = {0,};

//�庰 - �߷�Ÿ�� ���ݷ� ��ƿ���
int ValentineEventItemIndex[INVENTORY_MAXITEM*2] = {0,};

// �庰 - ĵ������
int CandydaysEventItemIndex[INVENTORY_MAXITEM*2] = {0,};

// �庰 - �����ñ׸�
int MagicalGreenEventItemIndex[INVENTORY_MAXITEM*2] = {0,}; 
int MagicalGreenEmeraldEventItemIndex[INVENTORY_MAXITEM*2] = {0,}; 

// �庰 - ī���� ����
int TearOfKaraEventItemIndex[INVENTORY_MAXITEM*2] = {0,};

// �庰 - ������� ã�ƶ� 
int FindinvestigatorNineEventItemIndex[INVENTORY_MAXITEM*2] = {0,}; // ���� �ƹķ�
int FindinvestigatorTaleEventItemIndex[INVENTORY_MAXITEM*2] = {0,}; // ���� �ƹķ�

// ����� - ���� �������� ������ �����Ѵ�.(�κ����� ���� ���� �����ϱ�)
int cINVENTORY::CheckItemCount(DWORD CODE)
{
	int i = 0; 
	int item_count = 0;
	if(CODE)
	{
		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItem[i].Flag)
			{
				if(InvenItem[i].CODE == CODE)
				{
					item_count++;
					WatermelonEventItemIndex[item_count-1] = i+1;
				}
			}
		}

		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItemTemp[i].Flag)
			{
				if(InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					WatermelonEventItemIndex[item_count-1] = 100+i+1;
				}
			}
		}
	}

	return item_count;
}


// �庰 - ���� �������� ������ �����Ѵ�.(�κ����� �߷�Ÿ�� ���ݷ� ���� �����ϱ�)
int cINVENTORY::CheckValentineItemCount(DWORD CODE) 
{
	int i = 0; 
	int item_count = 0;
	if(CODE)
	{
		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItem[i].Flag)
			{
				if(InvenItem[i].CODE == CODE)
				{
					item_count++;
					ValentineEventItemIndex[item_count-1] = i+1;
				}
			}
		}

		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItemTemp[i].Flag)
			{
				if(InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					ValentineEventItemIndex[item_count-1] = 100+i+1;
				}
			}
		}
	}

	return item_count;
}


// �庰 - ĵ������ ���� �������� ������ �����Ѵ�.(�κ����� ĵ�� ���� �����ϱ�)
int cINVENTORY::CheckCandyItemCount(DWORD CODE) 
{
	int i = 0; 
	int item_count = 0;
	if(CODE)
	{
		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItem[i].Flag)
			{
				if(InvenItem[i].CODE == CODE)
				{
					item_count++;
					CandydaysEventItemIndex[item_count-1] = i+1;
				}
			}
		}

		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItemTemp[i].Flag)
			{
				if(InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					CandydaysEventItemIndex[item_count-1] = 100+i+1;
				}
			}
		}
	}

	return item_count;
}


// �庰 - �����ñ׸�
int cINVENTORY::CheckMagicalGreenItemCount(DWORD CODE) 
{
	int i = 0; 
	int item_count = 0;
	if(CODE)
	{
		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItem[i].Flag)
			{
				if(InvenItem[i].CODE == CODE)
				{
					item_count++;
					MagicalGreenEventItemIndex[item_count-1] = i+1;
				}
			}
		}

		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItemTemp[i].Flag)
			{
				if(InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					MagicalGreenEventItemIndex[item_count-1] = 100+i+1;
				}
			}
		}
	}

	return item_count;
}

// �庰 - �����ñ׸�
int cINVENTORY::CheckMagicalGreenItemEmeraldCount(DWORD CODE) 
{
	int i = 0; 
	int item_count = 0;
	if(CODE)
	{
		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItem[i].Flag)
			{
				if(InvenItem[i].CODE == CODE)
				{
					item_count++;
					MagicalGreenEmeraldEventItemIndex[item_count-1] = i+1;
				}
			}
		}

		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItemTemp[i].Flag)
			{
				if(InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					MagicalGreenEmeraldEventItemIndex[item_count-1] = 100+i+1;
				}
			}
		}
	}

	return item_count;
}


// �庰 - ī���� ���� - �̺�Ʈ ������ ���� ����
int cINVENTORY::CheckTearOfKaraItemCount(DWORD CODE) 
{
	int i = 0; 
	int item_count = 0;
	if(CODE)
	{
		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItem[i].Flag)
			{
				if(InvenItem[i].CODE == CODE)
				{
					item_count++;
					TearOfKaraEventItemIndex[item_count-1] = i+1;
				}
			}
		}

		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItemTemp[i].Flag)
			{
				if(InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					TearOfKaraEventItemIndex[item_count-1] = 100+i+1;
				}
			}
		}
	}

	return item_count;
}


// �庰 - ������� ã�ƶ� - ���� �ƹķ� ���� ����
int cINVENTORY::CheckFindinvestigatorNineItemCount(DWORD CODE) 
{
	int i = 0; 
	int item_count = 0;
	if(CODE)
	{
		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItem[i].Flag)
			{
				if(InvenItem[i].CODE == CODE)
				{
					item_count++;
					FindinvestigatorNineEventItemIndex[item_count-1] = i+1;
				}
			}
		}

		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItemTemp[i].Flag)
			{
				if(InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					FindinvestigatorNineEventItemIndex[item_count-1] = 100+i+1;
				}
			}
		}
	}

	return item_count;
}


// �庰 - ������� ã�ƶ� - ���� �ƹķ� ���� ����
int cINVENTORY::CheckFindinvestigatorTaleItemCount(DWORD CODE) 
{
	int i = 0; 
	int item_count = 0;
	if(CODE)
	{
		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItem[i].Flag)
			{
				if(InvenItem[i].CODE == CODE)
				{
					item_count++;
					FindinvestigatorTaleEventItemIndex[item_count-1] = i+1;
				}
			}
		}

		for(i = 0; i < INVENTORY_MAXITEM ; i++)
		{
			if(InvenItemTemp[i].Flag)
			{
				if(InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					FindinvestigatorTaleEventItemIndex[item_count-1] = 100+i+1;
				}
			}
		}
	}

	return item_count;
}

//���ָӴϿ��� ����� �����Ѵ�
int cINVENTORY::ChangePuzzle(sITEM *pItem)
{
	char szTestBuff2[256];
	szTestBuff2[0] = 0; //�����ʱ�ȭ  
	if((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinPZ2){
		if(pItem->sItemInfo.PotionCount <= 1){
			pItem->sItemInfo.PotionCount = 2;
			for(int j=0 ; j < MAX_ITEM ; j++){ 
				if(pItem->sItemInfo.CODE == sItem[j].CODE){	
					CheckInvenItemForm(); 
					//memcpy(pItem,&sItem[j],sizeof(sITEM));
					wsprintf(szTestBuff2 ,"Image\\sinImage\\Items\\%s\\it%s.bmp",sItem[j].ItemFilePath,sItem[j].LastCategory);
					pItem->lpItem = sItem[j].lpTempItem;
					pItem->w = sItem[j].w;
					pItem->h = sItem[j].h;
					pItem->CODE = sItem[j].CODE;   //���� ������ �̿��� ���� �ڵ嵵 �Ѱ��ش�.
					CheckWeight();//���� ���� 
					ReFormInvenItem();
					sinMinusMoney(1000);
					ReformCharForm();//������ 
					SendSaveMoney(); //�ݾ� ������ ���ϰ��ϱ����� ȣ���Ѵ� 
					sinUsePotionDelayFlag = 1;
					cInvenTory.UnionCoreParticle2(pItem->x , pItem->y,1); //����Ʈ 
					cInvenTory.UnionCoreParticle2(pItem->x , pItem->y,1); //����Ʈ 
					cInvenTory.UnionCoreParticle2(pItem->x , pItem->y,1); //����Ʈ 
//					SetPuzzleEffect(pItem->x , pItem->y); //����Ʈ 
					SaveGameData();
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

DWORD CheckPuzzleIndex[4][4] = {
	{sin01,0,sin02,0},
	{sin03,sin04,0,sin06},
	{0,sin05,0,0},
	{sin07,0,sin08,0},
};

// ����� - �Ϻ� ���� �̺�Ʈ(���� ���� ����)
DWORD CheckPuzzleIndex2[4][4] = {
	{sin01,0,sin02,0},
	{sin03,sin04,0,sin06},
	{0,sin05,0,0},
	{sin07,0,sin08,0},
};
/*
DWORD CheckPuzzleIndex2[4][4] = {
	{sin01,0,sin03,sin04},
	{sin02,0,0,0},
	{sin05,sin06,sin07,0},
	{0,0,sin08,0},
};
*/
DWORD CheckPuzzleX[4] = {8,9,10,11};
int   PuzzleIndex[8] = {0,};

//������ üũ�Ѵ�
int cINVENTORY::CheckPuzzle()
{
	int Count = 0;
	int Count2 = 0;
	int i,j,k;
	PuzzleOkFlag = 0;
	for(int p = 0 ; p < 8 ; p++){
		PuzzleIndex[p] = 0;

	}

	for(i = 0 ; i < INVENTORY_MAXITEM ; i++){  
		if(InvenItem[i].Flag){
			if((InvenItem[i].sItemInfo.CODE & sinITEM_MASK2) == sinPZ1){
				for(j = 0; j < 4 ; j++){
					for(k = 0; k < 4 ; k++){
						if((InvenItem[i].sItemInfo.CODE & sinITEM_MASK3) == CheckPuzzleIndex[j][k]){
							if((StartX+(CheckPuzzleX[k]*22)) == InvenItem[i].x &&
								(StartY+(j*22)) == InvenItem[i].y){
								PuzzleIndex[Count] = i+1;
								Count++;

							}
						}
					}
				}
			}

			if((InvenItem[i].sItemInfo.CODE & sinITEM_MASK2) == sinPZ2){
				for(j = 0; j < 4 ; j++){
					for(k = 0; k < 4 ; k++){
						if((InvenItem[i].sItemInfo.CODE & sinITEM_MASK3) == CheckPuzzleIndex2[j][k]){
							if((StartX+(CheckPuzzleX[k]*22)) == InvenItem[i].x &&
								(StartY+(j*22)) == InvenItem[i].y){
								PuzzleIndex[Count2] = i+1;
								Count2++;

							}
						}
					}
				}
			}
		}
	}
	if(Count == 8 || Count2 == 8){
		//if(!PuzzleOkFlag)
		//	cMessageBox.ShowMessage(MESSAGE_PERPFECT_PUZZLE);
		PuzzleOkFlag = 1;

	}
	return TRUE;
}


//�ٺ��� ���� üũ�Ѵ�
int cINVENTORY::CheckEventItem()
{
	
	return TRUE;
}

//�ٺ��� ���� ������
int cINVENTORY::SendEventItem()
{
	return TRUE;	

}

//�������� �ƹ����� üũ�Ѵ�
int cINVENTORY::CheckFoxEventItem() { return TRUE; }

//�������� �ƹ����� ������
int cINVENTORY::SendFoxEventItem() { return TRUE; }


//��¦��¦ ���縦 üũ�Ѵ�
int cINVENTORY::CheckChristMasEventItem() { return TRUE; }

//��¦��¦ ���縦 ������
int cINVENTORY::SendChristmasEventItem() { return TRUE; }
//������ ������
int cINVENTORY::CheckSendPuzzle() { return TRUE; }
	
int cINVENTORY::SendPuzzleNpc() { return TRUE; }

//�������� �������� �����Ѵ� 
int cINVENTORY::IncreViewDamage(int Persent , int Num)
{
	ViewDamagePercent = Persent;
	ViewDamageNum = Num;
	SetItemToChar();
	return TRUE;
}

//ForceOrb�� ����Ʈ�� �׸���
int cINVENTORY::DrawForceOrbEffect(int x , int y) { return TRUE; }

//sITEM UseForceOrbBak;
int cINVENTORY::UseForceOrb(sITEM *pItem , int Flag) { return TRUE; }

// ����� - ���� ���� �߰�(���� ������ ����Ѵ�)
int cINVENTORY::UseMagicForceOrb(sITEM *pItem , int Flag) { return TRUE; }

// ����� - ���� ���� ���� �߰�(���� ���� ������ ����Ѵ�)
int cINVENTORY::UseBillingMagicForceOrb(sITEM *pItem , int Flag) { return TRUE; }

// ����� - ���� ���� �߰� (���� ������ �����Ѵ�.)
int cINVENTORY::SetMagicForceOrb(DWORD ItemCODE , int Time) { return TRUE; }

// ����� - ���� ���� ���� �߰� (���� ���� ������ �����Ѵ�.)
int cINVENTORY::SetBillingMagicForceOrb(DWORD ItemCODE , int Time) { return TRUE; }

//������������ �����Ѵ�(���������,��Ÿ���)
int cINVENTORY::SetForceOrb(DWORD ItemCODE , int Time) { return TRUE; }

// ����� - ĸ�������� ����ϱ�(ȣ���� ĸ�� ���)
int cINVENTORY::UseCapsuleItem(sITEM *pItem) { return TRUE; }

int CristalEventItemIndex[7]={0,};

int PristonAlphabetEventItemIndex[7] = {0,}; // ����� - ���ĺ� ���� �̺�Ʈ

//<ha>�ϰ�������  ���� ũ����Ż üũ
int cINVENTORY::CheckCristalEventItem() { return TRUE; }
//<ha>�ϰ������� ���� ũ����Ż�� ������ ������
int cINVENTORY::SendCristalEventItem() { return TRUE; }

//����� - ���� ��ƿ��� ���� ������ ������ üũ�Ѵ�.
int cINVENTORY::CheckWatermelonEventItem() { return TRUE; }


//�庰 - �߷�Ÿ�� ���ݷ� ��ƿ��� ���ݷ� ������ ������ üũ�Ѵ�.
int cINVENTORY::CheckValentineEventItem() { return TRUE; }


// �庰 - ĵ������ ĵ�� ��ƿ��� ĵ�� ������ ������ üũ�Ѵ�.
int cINVENTORY::CheckCandydaysEventItem() { return TRUE; }

// �庰 - �����ñ׸�  ���޶���, ���� ������ ������ üũ�Ѵ�.
int cINVENTORY::CheckMagicalGreenEventItem() { return TRUE; }

// �庰 - ī���� ���� ������ ������ üũ�Ѵ�.
int cINVENTORY::CheckTearOfKaraEventItem() { return TRUE; }


// �庰 - ������� ã�ƶ� ������ ������ üũ�Ѵ�. - ���� ������
int cINVENTORY::CheckFindinvestigatorEventItem() { return TRUE; }


// �庰 - ������� ã�ƶ� ������ ������ üũ�Ѵ�. - ī����
int cINVENTORY::CheckFindinvestigatorKamiuEventItem() { return TRUE; }


// �庰 - ������� ã�ƶ� ������ ������ üũ�Ѵ�. - ����
int cINVENTORY::CheckFindinvestigatorEtoEventItem() { return TRUE; }


//����� - ���� ��ƿ��� ���� �������� ������ ������
int cINVENTORY::SendWatermelonEventItem() { return TRUE; }




//�庰 - �߷�Ÿ�� �̺�Ʈ // �߷�Ÿ�� ���ݷ� �������� ������ ������
int cINVENTORY::SendValentineEventItem() { return TRUE; }

// ����� - ���ĺ� ���� �̺�Ʈ
int cINVENTORY::CheckPristonAlphabetEventItem() { return TRUE; }

// ����� - ���ĺ� ���� �̺�Ʈ(���ĺ� �������� ������ ������)
int cINVENTORY::SendPristonAlphabetEventItem() { return TRUE; }


// �庰 - ĵ������ // ĵ�� �������� ������ ������
int cINVENTORY::SendCandydaysEventItem() { return TRUE; }



// �庰 - �����ñ׸� - �������� ������ ������
int cINVENTORY::SendMagicalGreenEventItem() { return TRUE; }


// �庰 - �����ñ׸� - �������� ������ ������
int cINVENTORY::SendMagicalGreenEmeraldEventItem() { return TRUE; }


// �庰 - ī���� ���� // ���� �������� ������ ������
int cINVENTORY::SendTearOfKaraEventItem() { return TRUE; }

// ����� - 2010 ������ �̺�Ʈ - �౸�� ���� ����ϱ�
int cINVENTORY::UseSoccerBallPotionItem(sITEM *pItem)
{
	pItem->sItemInfo.PotionCount = 100;
	sinThrowItemToFeild(pItem);
	pItem->Flag = 0;

	cInvenTory.SetItemToChar(); //�������� ���õǸ� �ɷ�ġ�� �����Ѵ� 
	cInvenTory.ReFormInvenItem();
	cInvenTory.CheckWeight();   //���Ը� �����Ѵ� 
	sinUsePotionDelayFlag = 1;

	return TRUE;
}



// �庰 - ������� ã�ƶ� - ���¿�����
int cINVENTORY::SendFindinvestigatorNineEventItem() { return TRUE; }


// �庰 - ������� ã�ƶ� - ī����
int cINVENTORY::SendFindinvestigatorTaleEventItem() { return TRUE; }


// �庰 - ������� ã�ƶ� - ����
int cINVENTORY::SendFindinvestigatorTaleEtoEventItem() { return TRUE; }