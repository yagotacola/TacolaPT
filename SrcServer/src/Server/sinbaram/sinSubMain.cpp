/*----------------------------------------------------------------------------*
*	���ϸ� :  sinSubMain.cpp	
*	�ϴ��� :  ���� �Լ����� �����Ѵ� 
*	�ۼ��� :  ����������Ʈ 12��
*	������ :  �ڻ� 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"
#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\Help.h"
#include "Character/playmain.h"
#include "Character/playsub.h"
#include "netplay.h"
#include "Character/character.h"
#include "fileread.h"


/*----------------------------------------------------------------------------*
*								�������� 			
*-----------------------------------------------------------------------------*/	
HFONT sinFont = 0;   //��Ʈ 
HFONT sinMessageFont = 0;   //�޼��� ��Ʈ 
HFONT sinBoldFont = 0;   //�޼��� ��Ʈ 


int sinTestFlag;     //�׽�Ʈ �÷� 
int sinSecretFlag = 0;  //��ȣ �÷� 


int sinMouseButton[2] = { 0,0 };
int sinKeyClick[256];

int MouseButtonUpEvent = 0;   

int MatCursorDefault;       //������ �ȱ� Ŀ�� 
int MatCursorSell;          //������ �ȱ� Ŀ�� 
int MatCursorBuy;			//������ ��� Ŀ�� 
int MatCursorRepair;	   	//��ġ�� Ŀ�� �̹��� 	
int MatCursorAttack;		//���� 
int MatCursorGetItem1;		//������ �ݱ� 
int MatCursorGetItem2;		//������ �ݱ� 2
int MatCursorTalk;			//���ϱ� 

int CursorClass = 1;        //Ŀ������ (default�� 1�� �ش�  �������� ���� �� CursorClass = 0�����ش� )

int sinMoveKindInter[MAX_SIN_KIND_INTER]={0,0,0,0,0,0,0,0,0,0,0,0,0}; //���� ���� �����̴� �� // ������ - �ͽ��� ���� �߰��� ���� �ϳ��� �߰�

int sinSec = 0;         //�ʸ� ���Ѵ� 
int sinMainCounter = 0; //���η����� ���� ī��Ʈ���ش� 

float DeCreaSTM  = 0;
float InCreaSTM  = 0;
float InCreaLIFE = 0;
float InCreaMANA = 0;


char szTestBuff2[64]; //�̹��� �ε�� �̹����� ���� ���� Ȯ�����ش� 
POINT TestImageSize = {0,0};

int Accuracy_Table[][2] = {
	   
#include "sinTable.h"
	-1
};


int ItemIndex1[3] = {0,0,0};	//������ ���� ��ġ�� �ε��� ���� 
int ItemIndex2[3] = {0,0,0};

int ChangeJobButonCheck2 = 0; //��ư�ٿ��� �ѹ� �ųʶٴ� �÷�(�̰͵� ���� �����̴� ����!!)
int ItemImageNotExitFlag = 0;
int DownNum = 0;


void InitSub()
{
	
	sinCreatFont(); //��Ʈ���� 	
}
/*----------------------------------------------------------------------------*
*						������� ����
*-----------------------------------------------------------------------------*/	
void MainSub()
{
	sinProc(SINKEYDOWN);		//Ű�Է��� ������ 	
	sinSec++;
	sinMainCounter++; //������ ī���� 

	if(sinSec >= 70){ // 1�ʸ��� �ѹ��� ���� 
		sinRegen();      //���׹̳���� (����� ���׹̳��� ����Ѵ� )
		sinUseStamina(); //���׹̳��� ����Ѵ� 
		sinSec = 0;

	}
	if((sinMainCounter&3) == 0) //70�� 1/4�϶� ���� 
		sinSetRegen();

	if((sinMainCounter % 70) == 0)
		AgingRing();

	////////////////////////////////////�̴ϸʶ����� �̰����λ���
	cSkill.CheckSkillMastery(); //�����͸��� üũ�Ѵ� 
	CheckContinueSkill(); //���������� ���� ��ų�� üũ�ؼ� �ð��� ������ �����ش� 
	

}
/*----------------------------------------------------------------------------*
*						������� �׸��� 
*-----------------------------------------------------------------------------*/	
void DrawSub()     
{

}
/*----------------------------------------------------------------------------*
*						������� ���� 
*-----------------------------------------------------------------------------*/	
void CloseSub()
{
    
}
/*----------------------------------------------------------------------------*
*							  Ŀ�� 
*-----------------------------------------------------------------------------*/	
void InitCursor() {}
void DrawCursor() {}
/*----------------------------------------------------------------------------*
*				     ��������Ʈ �̹����� �׸��� 
*-----------------------------------------------------------------------------*/	
void DrawSprite(int winX, int winY, void* pdds, int x, int y, int width, int height, int Bltflag) {}
/*----------------------------------------------------------------------------*
*		�������� ����(ASE)�� ���ؿͼ� ������(*szImagePath)�� �����Ѵ� 
*-----------------------------------------------------------------------------*/	
int  sinGetItemInfo(DWORD CODE, char* szImagePath) { return TRUE; }

/*----------------------------------------------------------------------------*
*					   �������� Data�� �޴´� 
*-----------------------------------------------------------------------------*/	
extern int DecodeCompress( BYTE *lpSrcData , BYTE *lpDestData ); //���൥��Ÿ �ص� ( Z/NZ ��� )
int sinRecvMessage( DWORD dwCode , void *RecvBuff )
{
	sITEMINFO *lpItemInfo;
	smTRANS_SELL_ITEM		*lpTransSellItem;
	BYTE *lpBuff;
	int cnt;

	switch(dwCode) {
	case smTRANSCODE_SHOP_ITEMLIST:
		lpTransSellItem = (smTRANS_SELL_ITEM *)RecvBuff;

		lpItemInfo = new sITEMINFO[ lpTransSellItem->ItemCounter ];
		lpBuff = (BYTE *)RecvBuff+sizeof(smTRANS_SELL_ITEM);
		for( cnt=0;cnt<lpTransSellItem->ItemCounter;cnt++) {
			lpBuff += DecodeCompress( lpBuff , (BYTE *)&lpItemInfo[cnt] );
		}
		sinSetShopItem(lpItemInfo ,lpTransSellItem->ItemCounter, lpTransSellItem->ItemKind ); //���⸸ ���� 

		delete lpItemInfo;
		break;

	}

	return TRUE;
}
int RecvCountFlag = 0; //���� ���� �������� �ʱ�ȭ�� �ѹ��� �Ѵ� 

//������ ���� ������ �������� �޴´� 
int sinSetShopItem(sITEMINFO *pItem,int ItemCount, int ItemKind) { return TRUE; }

/*----------------------------------------------------------------------------*
*			    ���콺 or �κ��丮�� �������� �����Ѵ� 
*-----------------------------------------------------------------------------*/	
int sinSetQuestItem(sITEMINFO *sItemInfo )
{
	
	sinSetSpecialItemCode(sItemInfo); //����Ⱦ������� �����Ѵ� 

	int sArrowPosi=0 , i=0;
	sITEM sinTempItem;  //�����ۿ� ���õ� ������ ��� �־�δ� Temp

	//if(cInvenTory.SearchItemCode((sinQT1|sin01)))return FALSE; //1���� �ۿ� ����������
	//if(cInvenTory.SearchItemCode((sinQT1|sin02)))return FALSE;
	//if(cInvenTory.SearchItemCode((sinQT1|sin03)))return FALSE;

	if(sinChar->ChangeJob == 0 && !sinQuest_ChangeJob.CODE && !sinQuest_ChangeJob2.CODE){
		if((sItemInfo->CODE == (sinQT1|sin01)) || (sItemInfo->CODE == (sinQT1|sin02)) || (sItemInfo->CODE == (sinQT1|sin03)) ||
		    (sItemInfo->CODE == (sinQT1|sin04)) || (sItemInfo->CODE == (sinQT1|sin05)) || (sItemInfo->CODE == (sinQT1|sin06))){
			return FALSE;
			}
	}

	//////////�� ����Ʈ�� �����ʴ� �������� �����Ҽ�����

	if(sinQuest_ChangeJob.CODE == SIN_QUEST_CODE_CHANGEJOB){
		if(cInvenTory.SearchItemCode(sItemInfo->CODE))return FALSE; //���� �ڵ��� �������� ������ �����Ѵ�
		if(sItemInfo->CODE == (sinQT1|sin04))return FALSE;
		if(sItemInfo->CODE == (sinQT1|sin05))return FALSE;
		if(sItemInfo->CODE == (sinQT1|sin06))return FALSE;
		if(sItemInfo->CODE == (sinQT1|sin16))return FALSE;

	}


	if(sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M || 
		sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D  ){
			if(sItemInfo->CODE == (sinQT1|sin01))return FALSE;
			if(sItemInfo->CODE == (sinQT1|sin02))return FALSE;
			if(sItemInfo->CODE == (sinQT1|sin03))return FALSE;
			if(sItemInfo->CODE == (sinQT1|sin06))return FALSE;

	}

	//����Ʈ�� ������ ������������ ���ð�� �����Ѵ�
	if(sinChar->ChangeJob >= 1 ){
		if((sItemInfo->CODE == (sinQT1|sin01)) || (sItemInfo->CODE == (sinQT1|sin02)) || (sItemInfo->CODE == (sinQT1|sin03)) ||
		    (sItemInfo->CODE == (sinQT1|sin04)) || (sItemInfo->CODE == (sinQT1|sin05))){
			return FALSE;
			}
	}

	if(sinQuest_ChangeJob3.CODE == SIN_QUEST_CODE_CHANGEJOB3){
		if(sItemInfo->CODE == (sinQT1|sin01))return FALSE;
		if(sItemInfo->CODE == (sinQT1|sin02))return FALSE;
		if(sItemInfo->CODE == (sinQT1|sin03))return FALSE;
		if(sItemInfo->CODE == (sinQT1|sin04))return FALSE;
		if(sItemInfo->CODE == (sinQT1|sin05))return FALSE;

	}
	if(!sinQuest_Level80_2.CODE){
		if(sItemInfo->CODE == (sinQT1|sin09))return FALSE;
		if(sItemInfo->CODE == (sinQT1|sin10))return FALSE;
		if(sItemInfo->CODE == (sinQT1|sin11))return FALSE;
	}
	else{
		if(cInvenTory.SearchItemCode(sinQT1|sin09))
			if(sItemInfo->CODE == (sinQT1|sin09))return FALSE;
		if(cInvenTory.SearchItemCode(sinQT1|sin10))
			if(sItemInfo->CODE == (sinQT1|sin10))return FALSE;
		if(cInvenTory.SearchItemCode(sinQT1|sin11))
			if(sItemInfo->CODE == (sinQT1|sin11))return FALSE;

	}

	//if(sItemInfo->CODE

	//����Ʈ ���⸦ �����Ŀ��� ������ ����������
	if(sItemInfo->CODE == (sinQT1|sin06) && sinQuest_ChangeJob3.State >=3){
		return FALSE;
	}

	//����Ʈ�� ������ ������������ ���ð�� �����Ѵ�
	if(sinChar->ChangeJob >= 2 && sItemInfo->CODE == (sinQT1|sin06)){
		return FALSE;
	}

	///////�ڵ带 ������ ��
	switch(sItemInfo->CODE & sinITEM_MASK2){
		case sinQT1:
			sItemInfo->ItemKindCode = ITEM_KIND_QUEST;

		break;
		case sinSP1:
			sItemInfo->ItemKindCode = ITEM_KIND_EVENT;
		break;
	}


	if(LoadItemImage(sItemInfo,&sinTempItem)){
		if(sinTempItem.sItemInfo.PotionCount <= 0 )     //����ī��Ʈ�� �����Ѵ�
			sinTempItem.sItemInfo.PotionCount = 1;

		if(!cInvenTory.AutoSetInvenItem(&sinTempItem,1)){ //����Ʈ�������� ���Կ� ������� �����Ҽ��ִ�
			if(ArrowState[0]==0)sArrowPosi = 2;
			else sArrowPosi = 1;
			sinButtonFlag = sArrowPosi;
			SelectInvenItemIndex = 0; //���׸� �ھ���� �������� �ʱ�ȭ
			cInvenTory.ChangeABItem(sArrowPosi); // 2���� ������ �κ� �ڽ� 
			if(!cInvenTory.AutoSetInvenItem(&sinTempItem,1)){
				//if(sinThrowItemToFeild(&sinTempItem)){          //�������� ������ 
				sinTempItem.Flag = 0;
				return FALSE;
				
			}
		}
	}

	return TRUE;
}

/*----------------------------------------------------------------------------*
*			    ���콺 or �κ��丮�� �������� �����Ѵ� 
*-----------------------------------------------------------------------------*/
//���� ���� ���� �÷�
int CheckPotionDelayFlag = 0;
int sinSetInvenItem(sITEMINFO *sItemInfo ) { return TRUE; }


//����Ʈ �κ��丮�� ���õɾ�����
DWORD sinSpecialCODE[] = {(sinQT1|sin01),(sinQT1|sin02),(sinQT1|sin03),(sinQT1|sin04),(sinQT1|sin05),(sinQT1|sin06),
						(sinMA1|sin01),(sinMA2|sin01),(sinMA2|sin02),(sinQW1|sin01),(sinQW1|sin02),(sinQW1|sin03),
						(sinQW1|sin04),(sinQW1|sin05),(sinQT1|sin07),(sinQT1|sin08),
						(sinQT1|sin09),(sinQT1|sin10),(sinQT1|sin11),(sinQT1|sin12),(sinQT1|sin13),
						(sinQT1|sin14),(sinQT1|sin15),(sinQT1|sin16),(sinQW1|sin06),0};
//�ν�Ʈ ���Ϸ��� �ͽ�Ʈ���� �����߰� (sinQW1|sin06)
int sinSetSpecialItemCode(sITEMINFO *pItemInfo)
{
	int Count = 0;
	while(1){
		if(sinSpecialCODE[Count]){
			if(pItemInfo->CODE == sinSpecialCODE[Count]){
				pItemInfo->SpecialItemFlag[1] = ITEM_KIND_SPECIAL;
				break;

			}
			Count++;
		}
		else break;
	}
	cInvenTory.ChangeSpecialItem(2); //����Ʈ�������� �����Ѵ�
	return TRUE;
}

 
//�������� �̹����� �ε��Ѵ� 
int LoadItemImage(sITEMINFO *sItemInfo , sITEM *TempItem) { return TRUE; }

/*----------------------------------------------------------------------------*
*				         Ű��ư  �� ���콺 �Լ� 
*-----------------------------------------------------------------------------*/	
void sinLButtonUp()
{
	MouseButtonUpEvent = SINLBUTTONUP;
}
void sinRButtonUp()
{
	MouseButtonUpEvent = SINRBUTTONUP;
}
void sinLButtonDown() 
{

}
/*----------------------------------------------------------------------------*
*					Ű�Է°� ���콺 �Է��� �ѹ����� �����Ѵ� 
*-----------------------------------------------------------------------------*/	
int sinGetMouseButton(int num) { return TRUE; }
//-------------------------------------------------------------------------------
void sinMouseMain()
{
}
/*----------------------------------------------------------------------------*
*					Ű���� �Է��� �ѹ��� üũ�ϰ��Ѵ�
*-----------------------------------------------------------------------------*/	
int sinGetKeyClick(int num) { return TRUE; }
//-----------------------------------------------------------------------------
void sinKeyClickMain() {}


class sinFlag{
public:
	int	OpenFlag;
};

int FirstMove[MAX_SIN_KIND_INTER] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; // ������ - �ͽ��� ���� �߰��� ���� �ϳ��� �߰�

void ShowInterFace() {}

//��Ʈ ���� 
int sinCreatFont() { return TRUE; }

//�ؽ�Ʈ�� ���� ��ġ�� �����Ѵ�
int CheckEditSize(int x , int lx , char *String)
{
	int len = 0;  
	int ResultX = 0;
	int Temp=0,Temp2=0,Temp3=0;

	len = lstrlen(String);

	Temp = lx - x;
	Temp2 = (Temp - len*6)/2;

	return Temp2+x;

}

/*----------------------------------------------------------------------------*
*					����� ���������� ������ ����Ѵ� 
*-----------------------------------------------------------------------------*/	
#define SIN_POTION_LIFE			1
#define SIN_POTION_MANA			2
#define SIN_POTION_STAMINA		3
#define SIN_POTION_SONGPYEUN	4

int sinUsePotion() //����� ���������� ������ ����Ѵ� 
{
	
	CheckCharForm();//���� 
	
	int PotionKind = 0;
	int ResultPotion = 0;
	int TempRandPotion = 0;

	if(pUsePotion == 0) return FALSE;
	if(!pUsePotion->Flag)return FALSE;
	if(MouseItem.Flag){//���콺�� �����ִ� �����۰� ���� �������� ������ �����Ѵ� (�� �׷����� -_-; ���� ����̾ȳ��� �հ������������״� ���д�)
		if(MouseItem.sItemInfo.ItemHeader.Head == pUsePotion->sItemInfo.ItemHeader.Head)
			return FALSE;

	}

	if((pUsePotion->CODE & sinITEM_MASK2) ==sinPL1 ){ //�������ϰ�� 
		TempRandPotion = pUsePotion->sItemInfo.Life[1] -  pUsePotion->sItemInfo.Life[0];
		ResultPotion = pUsePotion->sItemInfo.Life[0]+(rand()%TempRandPotion);
		sinSetLife((sinGetLife()+ResultPotion));	//������ ���� 
		PotionKind = SIN_POTION_LIFE;
	}
	if((pUsePotion->CODE & sinITEM_MASK2) == sinPM1){ //�����ϰ�� 
		TempRandPotion = pUsePotion->sItemInfo.Mana[1] -  pUsePotion->sItemInfo.Mana[0];
		ResultPotion = pUsePotion->sItemInfo.Mana[0]+(rand()%TempRandPotion);
		sinSetMana((sinGetMana()+ResultPotion));	//������ ���� 
		PotionKind = SIN_POTION_MANA;
	}
	if((pUsePotion->CODE & sinITEM_MASK2) == sinPS1 ){ //���׹̳� �����ϰ�� 
		TempRandPotion = pUsePotion->sItemInfo.Stamina[1] -  pUsePotion->sItemInfo.Stamina[0];
		ResultPotion = pUsePotion->sItemInfo.Stamina[0]+(rand()%TempRandPotion);
		sinSetStamina((sinGetStamina()+ResultPotion));	//������ ���� 
		PotionKind = SIN_POTION_STAMINA;
	}
	if((pUsePotion->CODE & sinITEM_MASK2) == sinSP1)
	{
		if( (pUsePotion->CODE & sinITEM_MASK3) == sin01 || (pUsePotion->CODE & sinITEM_MASK3) == sin02 ||
			(pUsePotion->CODE & sinITEM_MASK3) == sin03 || (pUsePotion->CODE & sinITEM_MASK3) == sin15 || // ����� - ���� ������ �߰�
			(pUsePotion->CODE & sinITEM_MASK3) == sin35 ||  // �庰 - �߷�Ÿ�� ���ݸ� ������ �߰�
			 (pUsePotion->CODE & sinITEM_MASK3) == sin36 || (pUsePotion->CODE & sinITEM_MASK3) == sin42 ) // �庰 - ĵ������ // �庰 - ����
		{
			pUsePotion->sItemInfo.PotionCount = 0;			//���� ���� ī��Ʈ 0
			if(cInvenTory.EatSongPyeun(pUsePotion)){
				PotionKind = SIN_POTION_SONGPYEUN;
			}
			else
				PotionKind = 5;
		}
		// ��������
		if( (pUsePotion->CODE & sinITEM_MASK3) == sin05 || (pUsePotion->CODE & sinITEM_MASK3) == sin06 || (pUsePotion->CODE & sinITEM_MASK3) == sin07 ||
			(pUsePotion->CODE & sinITEM_MASK3) == sin08 || (pUsePotion->CODE & sinITEM_MASK3) == sin09 || (pUsePotion->CODE & sinITEM_MASK3) == sin10 )
		{
			PotionKind = 6;		// pluto ��������
		}

		// ����� - ĸ�� ������(ȣ���� ĸ�� ���)
		if( (pUsePotion->CODE & sinITEM_MASK3) == sin34 )
		{
			PotionKind = 7;		// ����� - ȣ���� ĸ�� �������� ����Ҷ� ��ȣ ����� �Ѵ�. 
		}

	}
	if(PotionKind){
		if(pUsePotion->sItemInfo.PotionCount >=2){ //������ ���� ���δ� 
			pUsePotion->sItemInfo.PotionCount--;
			/*
			if(( pUsePotion->sItemInfo.CODE & sinITEM_MASK3 ) == sin03 ||
				( pUsePotion->sItemInfo.CODE & sinITEM_MASK3 ) == sin04 ){
				sinPlaySound(SIN_SOUND_EAT_POTION2); //���� �Դ� �Ҹ� 
			}
			else
			*/

		}
		else{
			pUsePotion->Flag =0;
			sInven[pUsePotion->ItemPosition-1].ItemIndex = 0; //������ �ʴ´� 
			if(PotionKind != 5){
			/*			
				if(( pUsePotion->sItemInfo.CODE & sinITEM_MASK3 ) == sin03 ||
					( pUsePotion->sItemInfo.CODE & sinITEM_MASK3 ) == sin04 ){
					sinPlaySound(SIN_SOUND_EAT_POTION2); //���� �Դ� �Ҹ� 
				}
				else
			*/

			}

		} 
	
	pUsePotion = 0; //������ �ʱ�ȭ 		
	ReformCharForm();//������ 
	cInvenTory.CheckWeight(); //���Ը� üũ�Ѵ� 
	cInvenTory.ReFormPotionNum();	//���� ������ üũ�Ѵ� 
	cInvenTory.ReFormInvenItem();   //�κ��丮 ������ ����
	return PotionKind;
	}

	return FALSE;	

}

//�Źٶ� ��� 
void sinRegen()
{

	InCreaSTM  = 0;
	InCreaMANA = 0;
	InCreaLIFE = 0;

	float	fLevel=0;
	float	fStrength=0;
	float	fHealth=0;
	float	fSpirit=0;

	//���׹̳� ��� 
	if(lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_STAND){
		switch(sinChar->StaminaFunction){
			case 1:
				InCreaSTM = (float)(3.8 +sinChar->Level/7+sinChar->Stamina_Regen);
			break;
			case 2:
				InCreaSTM = (float)(3.3 +sinChar->Level/7+sinChar->Stamina_Regen);
			break;
			case 3:
				InCreaSTM = (float)(2.9 +sinChar->Level/7+sinChar->Stamina_Regen);
			break;
			default: //Ȥ�ó� �ؼ� �ϳ� �־�д� 
				InCreaSTM = (float)(3.8 +sinChar->Level/7+sinChar->Stamina_Regen);
			break;
		}

	}
	if(lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_WALK){
		switch(sinChar->StaminaFunction){
			case 1:
				InCreaSTM = (float)((3.8 +sinChar->Level/7+sinChar->Stamina_Regen)*0.6);
			break;
			case 2:
				InCreaSTM = (float)((3.3 +sinChar->Level/7+sinChar->Stamina_Regen)*0.6);
			break;
			case 3:
				InCreaSTM = (float)((2.9 +sinChar->Level/7+sinChar->Stamina_Regen)*0.6);
			break;
			default:
				InCreaSTM = (float)((3.8 +sinChar->Level/7+sinChar->Stamina_Regen)*0.6);
			break;

		}

	}
	fLevel = (float)sinChar->Level;
	fStrength = (float)sinChar->Strength;
	fHealth = (float)sinChar->Health;
	fSpirit = (float)sinChar->Spirit;

	
	if(lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD){
		//������ ���  
		InCreaLIFE = (float)(((fLevel+(fStrength/2)+fHealth)/180 + sinChar->Life_Regen)/1.5);
		//���� ��� 
		InCreaMANA = (fLevel+(fSpirit*1.2f)+(fHealth/2))/115 + sinChar->Mana_Regen;
	}

}

void sinUseStamina()
{

	DeCreaSTM = 0;
	if(lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_RUN){
		//DeCreaSTM = (float)(100+(sinChar->Weight[0]/2))/(100+(sinChar->Strength/5)); 
		//DeCreaSTM = (float)1000/(((sinChar->Weight[1] - sinChar->Weight[0])+(sinChar->Strength/2)+500)+0.5);
		DeCreaSTM = (float)((1000+sinChar->Weight[0]) / (sinChar->Weight[1]+(sinChar->Strength/2)+500)+0.4);
	
	}
}


float fTempLIFE = 0;
float fTempMANA = 0;
float fTempSTM_Incre  = 0;
float fTempSTM_Decre  = 0;

//���׹̳��� �����Ѵ� 
void sinSetRegen()
{
	
	CheckCharForm();//���� 

	//���׹̳� ���� 
	if(DeCreaSTM){ 
		fTempSTM_Decre += DeCreaSTM/(70/4);
		if(fTempSTM_Decre >=1){
			sinSetStamina(sinGetStamina()-(short)fTempSTM_Decre);
			fTempSTM_Decre -=1;
		}

	}
	//���׹̳� ���� 
	if(InCreaSTM){
		fTempSTM_Incre += InCreaSTM/(70/4);
		if(fTempSTM_Incre >= 1){
			sinSetStamina(sinGetStamina()+(short)fTempSTM_Incre);
			while(1){
				if(fTempSTM_Incre > 1)
					fTempSTM_Incre -=1;
				else break;

			}

		}

	}

	//������ ���� 
	if(InCreaLIFE){
		fTempLIFE += InCreaLIFE/(70/4);
		if(fTempLIFE >=1){
			sinSetLife(sinGetLife()+(short)fTempLIFE);
			while(1){
				if(fTempLIFE > 1)
					fTempLIFE -=1;
				else break;
			}

		}
		

	}
	
	//���� ���� 
	if(InCreaMANA){
		fTempMANA += InCreaMANA/(70/4);
		if(fTempMANA >= 1){
			sinSetMana(sinGetMana()+(short)fTempMANA);
			while(1){
				if(fTempMANA > 1)
					fTempMANA -=1;
				else break;
			}


		}

	}
	ReformCharForm();//������ 

}
/*----------------------------------------------------------------------------*
*				 (���� ������ ������ ���� �����Ѵ� )
*-----------------------------------------------------------------------------*/	
int sinGetAC(int AC)
{
	int cnt = 0;
	while(1){
		if(Accuracy_Table[cnt][0] == 0)break;
		if( AC > Accuracy_Table[cnt][0] && AC < Accuracy_Table[cnt+1][0] ){
			return Accuracy_Table[cnt+1][1];	
		}
		cnt++;
	}
	return FALSE;
}

int cnt  = 0;
int AC_R = 0;    //������� ���� �� 
int RealAC=0;    //���̺��� ���� ���� ��ġ 
int Result=0;
float fDesLV = 0;
float fMyLV  = 0;
float fWeifht[2] = {0,0};


//���߷��� �����Ѵ� (��Ȯ�ϴ�) (������ ������������ �ǽ�����������)
int sinGetAccuracy(int desLV , int desDefense)
{
	cnt = 0;
	AC_R = (int)(((float)sinChar->Attack_Rating - (float)desDefense)*1.4);

	while(1){
		if(AC_R <-190){
			RealAC = 50;
			break;
		}
		if(AC_R >2100){
			RealAC = 95;
			break;
		}
		if(Accuracy_Table[cnt][1] == 0)break; 
		if( AC_R >= Accuracy_Table[cnt][0] && AC_R <= Accuracy_Table[cnt+1][0] ){
			RealAC = Accuracy_Table[cnt+1][1];	
			break;

		}
		cnt++;
	}
	fDesLV = (float)desLV;
	fMyLV  = (float)sinChar->Level;
	fWeifht[0] = sinChar->Weight[0];
	fWeifht[1] = sinChar->Weight[1];


	//Result = (int)(RealAC - (((fDesLV - fMyLV)/100)*28)-(( fWeifht[0] / fWeifht[1])*3));
	Result = (int)(RealAC - ((fDesLV - fMyLV)/100)*28);

	if(Result < 30) Result = 30;
	if(Result > 95) Result = 95;
	return Result;
}

//���� ���߷�  
int sinGetMonsterAccuracy(int MonsterLV , int MonsterAttack_Rating) 
{
	cnt = 0;
	AC_R = (MonsterAttack_Rating - sinChar->Defence)*2;

	while(1){
		if(Accuracy_Table[cnt][0] == 0)break;
		if( AC_R > Accuracy_Table[cnt][0] && AC_R < Accuracy_Table[cnt+1][0] ){
			RealAC = Accuracy_Table[cnt+1][1];	
			break;

		}
		cnt++;
	}
	fDesLV = (float)sinChar->Level;
	fMyLV  = (float)MonsterLV;

	Result = (int)(RealAC - ((fDesLV - fMyLV)/100)*50);

	if(Result < 30) Result = 30;
	if(Result > 95) Result = 95;

	return Result;
}

//���� VS ���� ���߷�
int sinGetPVPAccuracy(int MyLevel , int MyAttack_Rating , int DesLevel , int DesDefense)
{
	cnt = 0;
	AC_R = (int)(((float)MyAttack_Rating - (float)DesDefense)*1.4);

	while(1){
		if(AC_R <-190){
			RealAC = 50;
			break;
		}
		if(AC_R >2100){
			RealAC = 95;
			break;
		}
		if(Accuracy_Table[cnt][1] == 0)break; 
		if( AC_R > Accuracy_Table[cnt][0] && AC_R < Accuracy_Table[cnt+1][0] ){
			RealAC = Accuracy_Table[cnt+1][1];	
			break;

		}
		cnt++;
	}
	fDesLV = (float)DesLevel;
	fMyLV  = (float)MyLevel;

	Result = (int)(RealAC - ((fDesLV - fMyLV)/100)*28);

	if(Result < 30) Result = 30;
	if(Result > 95) Result = 95;
	return Result;
}

//���� ũ��Ƽ�� 
int sinGetCritical(int desLV)
{

	fDesLV = (float)desLV;
	fMyLV  = (float)sinChar->Level;

	Result = (int)(sinChar->Critical_Hit + ((fMyLV - fDesLV)/100)*25);
	if(Result > 70)
		Result = 70;
	
	return Result;

}

int sinGetBlockRating(int desLV)
{

	fDesLV = (float)desLV;
	fMyLV  = (float)sinChar->Level;

	Result = (int)(sinChar->Chance_Block+((fMyLV - fDesLV)/100)*25);
	return Result;
	
}

#define SIN_MONSTER_UNDEAD		1
//������� �����Ѵ� 
int sinGetAbsorb(int Type)
{

	switch(Type){
		case SIN_MONSTER_UNDEAD:
			return sinChar->Absorption+sinUndeadAbsorb;
		break;
		default:
			return sinChar->Absorption;

		break;
	}
	return TRUE;
}


void sinReload() {}

int StopCharMotion(int x ,int y) { return TRUE; }
//�׽�Ʈ�� ���� �޼����� �����ش� 
int CheatHelpOpenFlag = 0;
void sinTestDrawText() {}
/*
//Tempscron 4�� ������ ��...
static char *szTempFighterFaceName[] = {
	"char\\tmABCD\\tmh-b01.inf",
	"char\\tmABCD\\tmh-b02.inf",
	"char\\tmABCD\\tmh-b03.inf"
};

static char *szTempMechFaceName[] = {
	"char\\tmABCD\\tmh-a01.inf",
	"char\\tmABCD\\tmh-a02.inf",
	"char\\tmABCD\\tmh-a03.inf"
};

static char *szTempArcherFaceName[] = {
	"char\\tmABCD\\tfh-D01.inf",
	"char\\tmABCD\\tfh-d02.inf",
	"char\\tmABCD\\tfh-d03.inf"
};
static char *szTempPikeFaceName[] = {
	"char\\tmABCD\\tmh-c01.inf",
	"char\\tmABCD\\tmh-c02.inf",
	"char\\tmABCD\\tmh-c03.inf"
};
*/

/////////////////////////////////TEST KEY
void sinTestKey() {}


//Ʈ���̵� �䱸�� ������ ���� �����Ѵ� 
int sinRequestTrade(DWORD CODE , char *CharName)
{
	if(cTrade.OpenFlag)
		return FALSE;

	cTrade.TradeRequestFlag = 1;
	cTrade.TradeCharCode = CODE;
	lstrcpy(cTrade.szTradeCharName,CharName);
	return TRUE;
	
}

DWORD dwCurrentTime = 0;

//��ų�� ���� ������ �Ѵ� 
int sinSkillMaster(int ChangeJob) { return TRUE; }

//��ų ���⸦ ��ģ�� 
int sinSkillMasterClose()
{
	/*
	if(ChangeJobButtonclick){
		cInterFace.CheckAllBox(SIN_SKILL); //��ųâ�� ����ش� 

	}
	else{
	*/
		SkillMasterFlag = 0;	//��ų�� �Ҵ��Ҽ��ִ� ���� �ʱ�ȭ�Ѵ� 
		cSkill.OpenFlag = 0;	//��ų â�� �ݾ��ش� 
dwCurrentTime = dwPlayTime+5000;
	//}
	return TRUE;
}


static int LastPartyMode = -1;
int haSiegeBoardTempFlag = 0; //������ ����â�� ����� ����  
//��Ƽ â�� �����ش� 
int ShowParty() { return TRUE; }

//����Ʈ â�� �����ش� 
int ShowQuest() { return TRUE; }

///////////////////////////////// ������ , ���� , ���׹̳� ���� �ڵ�ȭ 

//�������� �о�´� 
short sinGetLife()
{

		return (sinChar->Life[0])^CodeXorLife;
}

//������ ���´� 
short sinGetMana()
{

	return sinChar->Mana[0];
}

//���׹̳��� ���´� 
short sinGetStamina()
{

	return sinChar->Stamina[0];
}

//�������� �����Ѵ�				//kyle xtrapHeap
void sinSetLife(short Life)
{
#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func11_Protect( &(sinChar->Life), sizeof(sinChar->Life) );	//��ȣ���� ���Ἲ üũ
#endif

	//CheckCharForm(); //���� 
	sinChar->Life[0] = Life;
	if(sinChar->Life[0] < 0 ) sinChar->Life[0] = 0;
	if(sinChar->Life[0] >= sinChar->Life[1] )sinChar->Life[0] = sinChar->Life[1];
	sinChar->Life[0] ^= CodeXorLife;
	ReformCharForm(); //������ 

#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func12_Protect( &(sinChar->Life), sizeof(sinChar->Life) );	//��ȣ���� ��ȣ
	XTrap_CE1_Func13_Free( &(sinChar->Life), sizeof(sinChar->Life) );		//��ȣ���� ����
#endif
	
}

//������ �����Ѵ� 
void sinSetMana(short Mana)
{
#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func11_Protect( &(sinChar->Mana), sizeof(sinChar->Mana) );	//��ȣ���� ���Ἲ üũ
#endif

	//CheckCharForm(); //���� 
	sinChar->Mana[0] = Mana;
	if(sinChar->Mana[0] < 0 ) sinChar->Mana[0] = 0;
	if(sinChar->Mana[0] >= sinChar->Mana[1] )sinChar->Mana[0] = sinChar->Mana[1];
	ReformCharForm(); //������ 

#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func12_Protect( &(sinChar->Mana), sizeof(sinChar->Mana) );	//��ȣ���� ��ȣ
	XTrap_CE1_Func13_Free( &(sinChar->Mana), sizeof(sinChar->Mana) );		//��ȣ���� ����
#endif
}

//���׹̳��� �����Ѵ� 
void sinSetStamina(short Stamina)
{
#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func11_Protect( &(sinChar->Stamina), sizeof(sinChar->Stamina) );	//��ȣ���� ���Ἲ üũ
#endif

	//CheckCharForm(); //���� 
	sinChar->Stamina[0] = Stamina;
	if(sinChar->Stamina[0] < 0 ) sinChar->Stamina[0] = 0;
	if(sinChar->Stamina[0] >= sinChar->Stamina[1] )sinChar->Stamina[0] = sinChar->Stamina[1];
	ReformCharForm(); //������ 

#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func12_Protect( &(sinChar->Stamina), sizeof(sinChar->Stamina) );	//��ȣ���� ��ȣ
	XTrap_CE1_Func13_Free( &(sinChar->Stamina), sizeof(sinChar->Stamina) );		//��ȣ���� ����
#endif

}

//	short   ItemAgingNum[2];	//0�� ����¡+�� 1�� ����¡�� �ǰ��ֳ� �ƴѰ�?
//	short   ItemAgingCount[2];	//0������ ���� ī��Ʈ 1����ġ �ִ� 

//////����¡ ������ üũ���� �÷��ش�(����¡��ġ)
/*
char *AgingMsgDamageMax = "�ִ���ݷ�";
char *AgingMsgDamageMin = "�ּҰ��ݷ�";
char *AgingMsgAttack_Rate = "���߷�";
char *AgingMsgDur = "������";
char *AgingMsgCritical = "ũ��Ƽ��";
char *AgingMsgShooting_Range = "�����Ÿ�";
char *AgingMsgMana = "���";
char *AgingMsgBlock = "����";
char *AgingMsgAbsorb = "�����";
char *AgingMsgDefense = "�����";
*/
//������
int sinSetDurabilityAging(sITEMINFO *pItem)
{
	int Temp = 0;
	Temp = pItem->Durability[1]/100;
	Temp += 1;
	pItem->Durability[1] -= Temp;
	if(pItem->Durability[1] < 0 ) pItem->Durability[1] = 0;
	if(pItem->Durability[1] < pItem->Durability[0] ) pItem->Durability[0] = pItem->Durability[1]; //���� ������ ���� 

	return TRUE;
}
//���ݷ�
int sinSetDamageAging(sITEMINFO *pItem)
{
	pItem->Damage[0]++;
	pItem->Damage[1]++;

	if(pItem->ItemAgingNum[0] >= 9){ //10�����ʹ� ������ +2
		pItem->Damage[0]++;
		pItem->Damage[1]++;
	}

	// ����� - ����¡ ���� ����(����� ������ ���ݷ� �߰�)
	if(pItem->ItemAgingNum[0] >= 19){ //20�����ʹ� ������ +3
		pItem->Damage[0]++;
		pItem->Damage[1]++;
	}

	return TRUE;
}
//����
int sinSetDefenseAging(sITEMINFO *pItem , int Percent)
{
	float Temp = 0;
	Temp = (float)pItem->Defence/(100.0f / (float)Percent);
	pItem->Defence += (int)Temp;
	return TRUE;
}

//���߷�
int sinSetAttackRateAging(sITEMINFO *pItem , int AddNum)
{
	pItem->Attack_Rating += AddNum;
	return TRUE;
}
//�����
int sinSetAbsorbAging(sITEMINFO *pItem , float Percent)
{
	pItem->fAbsorb += Percent;

	if(pItem->ItemAgingNum[0] >= 9){ //10�����ʹ� 2��
		pItem->fAbsorb += Percent;
	}

	// ����� - ����¡ ���� ����(����� ������ ���ݷ� �߰�)
	if(pItem->ItemAgingNum[0] >= 19){ //20�����ʹ� 3��
		pItem->fAbsorb += Percent;
	}
	return TRUE;
}

//ũ��Ƽ��
int sinSetCriticalAging(sITEMINFO *pItem)
{
	if(pItem->ItemAgingNum[0] && (pItem->ItemAgingNum[0]%2) == 1){
		pItem->Critical_Hit += 1;

	}
	return TRUE;
}

//����
int sinSetBlockRateAging(sITEMINFO *pItem)
{
	if(pItem->ItemAgingNum[0] && (pItem->ItemAgingNum[0]%2) == 1){
		pItem->fBlock_Rating += 1;

	}
	return TRUE;
}

int sinSetAgingItemIncreState(sITEMINFO *pItem)
{
	float TempDefense[2] = {0,0};
	//����¡ �ʱ�ȭ
	switch(pItem->CODE & sinITEM_MASK2){
		case sinWA1: //���� 
			//���ݷ� 
			sinSetDamageAging(pItem);
			//���߷�
			sinSetAttackRateAging(pItem , 10);
			//������
			sinSetDurabilityAging(pItem); 

		break;
		case sinWC1: //Ŭ��
			//���ݷ� 
			sinSetDamageAging(pItem);
			//���߷�
			sinSetAttackRateAging(pItem , 5);
			//ũ��Ƽ��  
			sinSetCriticalAging(pItem);

		break;

		case sinWH1: //�ظ� 
			//���ݷ� 
			sinSetDamageAging(pItem);

			//���߷�
			sinSetAttackRateAging(pItem , 10);
			//������
			sinSetDurabilityAging(pItem); 

		break;
		case sinWM1: //������ ������ 
			//���ݷ� 
			sinSetDamageAging(pItem);

			//���߷�
			sinSetAttackRateAging(pItem , 10);

			//���  
			pItem->fIncrease_Mana += 10;

		break;
		case sinWP1: //â 
			//���ݷ� 
			sinSetDamageAging(pItem);

			//���߷�
			sinSetAttackRateAging(pItem , 5);

			//ũ��Ƽ��  
			sinSetCriticalAging(pItem);

		break;
		case sinWS1: //Ȱ 
			//���ݷ� 
			sinSetDamageAging(pItem);

			//ũ��Ƽ��  
			sinSetCriticalAging(pItem);

			//������
			sinSetDurabilityAging(pItem); 
		break;

		case sinWS2: //Į  
			//���ݷ� 
			sinSetDamageAging(pItem);

			//���߷�
			sinSetAttackRateAging(pItem , 5);
			
			//ũ��Ƽ��  
			sinSetCriticalAging(pItem);

		break;

		case sinWT1: //�ں��� 
			//���ݷ� 
			sinSetDamageAging(pItem);

			//ũ��Ƽ��  
			sinSetCriticalAging(pItem);

			//������
			//sinSetDurabilityAging(pItem); 
		break;
		case sinWD1:
			sinSetDamageAging(pItem);
			sinSetAttackRateAging(pItem, 5);
			sinSetCriticalAging(pItem);
			break;
		case sinDS1: //���� 
			//���� 
			sinSetBlockRateAging(pItem);
			//�����
			sinSetAbsorbAging(pItem , 0.2f);
			//������
			sinSetDurabilityAging(pItem); 
		break;

		case sinOM1: //������ ���� 
			//���� 
			sinSetDefenseAging(pItem,10);

			//�����
			sinSetAbsorbAging(pItem , 0.5f);

			//������
			sinSetDurabilityAging(pItem); 

		break;
		case sinDA1: case sinDA2://���� 
			//���� 
			sinSetDefenseAging(pItem,5);

			//�����
			sinSetAbsorbAging(pItem , 0.5f);

			//������
			sinSetDurabilityAging(pItem); 

		break; 
		case sinDB1: // ����� - ����¡ ������ �߰�(����)
			//���� 
			sinSetDefenseAging(pItem,10);
			//�����
			sinSetAbsorbAging(pItem , 0.5f);
			//������
			sinSetDurabilityAging(pItem); 
			break;
		case sinDG1: // ����� - ����¡ ������ �߰�(�尩)
			//���� 
			sinSetDefenseAging(pItem,10);
			//�����
			sinSetAbsorbAging(pItem , 0.5f);
			//������
			sinSetDurabilityAging(pItem); 
			break;
		case sinOA2: // ����� - ����¡ ������ �߰�(�ϸ�)
			//���� 
			sinSetDefenseAging(pItem,10);
			//���߷�
			sinSetAttackRateAging(pItem , 5);
			//������
			sinSetDurabilityAging(pItem); 
			break;
		}
		
		

		pItem->ItemAgingNum[0]++;	//�������� ������ �÷��ش� 
			
		pItem->ItemAgingNum[1] = 0; //�ʱ�ȭ 
		pItem->ItemAgingCount[0] = 0;
		pItem->ItemAgingCount[1] = 0;

		
		if( pItem->Level == 100 || pItem->Level == 102 || pItem->Level == 105 ||	// pluto 102���� ���� ���� ���� �ҷ��� // �庰 - 105�� ������ ����
			cAging.AginStoneKind == 3 || cAging.AginStoneKind == 4 || // ����� - ���� ���� ����, ���� ����¡ ���� ���ÿ��� ����¡ ������ ����ص� ������ ������ �ö��� �ʴ´�.
			cAging.AginStoneKind == 5  ) // �庰 - ���� ����¡ ���� 1.5
		{
			pItem->Level += 0;
		}
		else
		{
		}
				
	ReformItem(pItem);  //������ ���� �ޱ� 
	return TRUE;
}



int sinSetAgingItemIncreStateRestaure(sITEMINFO* pItem)
{
	float TempDefense[2] = { 0,0 };
	//����¡ �ʱ�ȭ
	switch (pItem->CODE & sinITEM_MASK2) {
	case sinWA1: //���� 
		//���ݷ� 
		sinSetDamageAging(pItem);
		//���߷�
		sinSetAttackRateAging(pItem, 10);
		//������
		sinSetDurabilityAging(pItem);

		break;
	case sinWC1: //Ŭ��
		//���ݷ� 
		sinSetDamageAging(pItem);
		//���߷�
		sinSetAttackRateAging(pItem, 5);
		//ũ��Ƽ��  
		sinSetCriticalAging(pItem);

		break;

	case sinWH1: //�ظ� 
		//���ݷ� 
		sinSetDamageAging(pItem);

		//���߷�
		sinSetAttackRateAging(pItem, 10);
		//������
		sinSetDurabilityAging(pItem);

		break;
	case sinWM1: //������ ������ 
		//���ݷ� 
		sinSetDamageAging(pItem);

		//���߷�
		sinSetAttackRateAging(pItem, 10);

		//���  
		pItem->fIncrease_Mana += 10;

		break;
	case sinWP1: //â 
		//���ݷ� 
		sinSetDamageAging(pItem);

		//���߷�
		sinSetAttackRateAging(pItem, 5);

		//ũ��Ƽ��  
		sinSetCriticalAging(pItem);

		break;
	case sinWS1: //Ȱ 
		//���ݷ� 
		sinSetDamageAging(pItem);

		//ũ��Ƽ��  
		sinSetCriticalAging(pItem);

		//������
		sinSetDurabilityAging(pItem);
		break;

	case sinWS2: //Į  
		//���ݷ� 
		sinSetDamageAging(pItem);

		//���߷�
		sinSetAttackRateAging(pItem, 5);

		//ũ��Ƽ��  
		sinSetCriticalAging(pItem);

		break;

	case sinWT1: //�ں��� 
		//���ݷ� 
		sinSetDamageAging(pItem);

		//ũ��Ƽ��  
		sinSetCriticalAging(pItem);

		//������
		//sinSetDurabilityAging(pItem); 
		break;

	case sinWD1:
		sinDownDamageAging(pItem);
		sinDownAttackRateAging(pItem, 5);
		sinDownCriticalAging(pItem);
		break;

	case sinDS1: //���� 
		//���� 
		sinSetBlockRateAging(pItem);
		//�����
		sinSetAbsorbAging(pItem, 0.2f);
		//������
		sinSetDurabilityAging(pItem);
		break;

	case sinOM1: //������ ���� 
		//���� 
		sinSetDefenseAging(pItem, 10);

		//�����
		sinSetAbsorbAging(pItem, 0.5f);

		//������
		sinSetDurabilityAging(pItem);

		break;
	case sinDA1: case sinDA2://���� 
		//���� 
		sinSetDefenseAging(pItem, 5);

		//�����
		sinSetAbsorbAging(pItem, 0.5f);

		//������
		sinSetDurabilityAging(pItem);

		break;
	case sinDB1: // ����� - ����¡ ������ �߰�(����)
		//���� 
		sinSetDefenseAging(pItem, 10);
		//�����
		sinSetAbsorbAging(pItem, 0.5f);
		//������
		sinSetDurabilityAging(pItem);
		break;
	case sinDG1: // ����� - ����¡ ������ �߰�(�尩)
		//���� 
		sinSetDefenseAging(pItem, 10);
		//�����
		sinSetAbsorbAging(pItem, 0.5f);
		//������
		sinSetDurabilityAging(pItem);
		break;
	case sinOA2: // ����� - ����¡ ������ �߰�(�ϸ�)
		//���� 
		sinSetDefenseAging(pItem, 10);
		//���߷�
		sinSetAttackRateAging(pItem, 5);
		//������
		sinSetDurabilityAging(pItem);
		break;
	}



	pItem->ItemAgingNum[0]++;	//�������� ������ �÷��ش� 

	pItem->ItemAgingNum[1] = 0; //�ʱ�ȭ 
	pItem->ItemAgingCount[0] = 0;
	pItem->ItemAgingCount[1] = 0;


	if (pItem->Level == 100 || pItem->Level == 102 || pItem->Level == 105 ||	// pluto 102���� ���� ���� ���� �ҷ��� // �庰 - 105�� ������ ����
		cAging.AginStoneKind == 3 || cAging.AginStoneKind == 4 || // ����� - ���� ���� ����, ���� ����¡ ���� ���ÿ��� ����¡ ������ ����ص� ������ ������ �ö��� �ʴ´�.
		cAging.AginStoneKind == 5) // �庰 - ���� ����¡ ���� 1.5
	{
		pItem->Level += 0;
	}
	else
	{
	}

	ReformItemRestaure(pItem);  //������ ���� �ޱ� 
	return TRUE;
}




//�������� ������
int sinDownDurabilityAging(sITEMINFO *pItem)
{
	int Temp = 0;
	Temp = pItem->Durability[1]/100;
	Temp += 1;
	pItem->Durability[1] += Temp*DownNum;
	if(pItem->Durability[1] < 0 ) pItem->Durability[1] = 0;
	if(pItem->Durability[1] < pItem->Durability[0] ) pItem->Durability[0] = pItem->Durability[1]; //���� ������ ���� 

	return TRUE;
}	
																																																																																									
// ����¡ ���ݷ�
int sinDownDamageAging(sITEMINFO *pItem , int Level)
{
	/*
		DownNum =  Down + 1;		
	*/
	if( Level < 10 ){
		pItem->Damage[0] -= DownNum; 
		pItem->Damage[1] -= DownNum;
	}
	else{
		switch( DownNum ){
			case 1:
				pItem->Damage[0] -= 2; 
				pItem->Damage[1] -= 2;
			break;
			case 2:
				if( Level == 10 ){
					pItem->Damage[0] -= 2+1; 
					pItem->Damage[1] -= 2+1;				
				}
				else{
					pItem->Damage[0] -= 2*2; 
					pItem->Damage[1] -= 2*2;
				}
			break;
			case 3:
				if( Level == 10 ){
					pItem->Damage[0] -= 2+1+1; 
					pItem->Damage[1] -= 2+1+1;
				}
				else if( Level == 11 ){
					pItem->Damage[0] -= 2*2+1; 
					pItem->Damage[1] -= 2*2+1;
				}
				else{
					pItem->Damage[0] -= 2*3; 
					pItem->Damage[1] -= 2*3;
				}
			break;
		}		
	}
	

	return TRUE;
}
//����
int sinDownDefenseAging(sITEMINFO *pItem , int Percent)
{

	float Temp = 0;
	int   TempDefence =0;
	for(int i = 0 ; i< DownNum ;i++){
		Temp = (100.0f*(float)pItem->Defence)/(100.0f+(float)Percent);
		TempDefence = pItem->Defence - (int)Temp;
		pItem->Defence -= TempDefence;
	}
	return TRUE;
}

//���߷�
int sinDownAttackRateAging(sITEMINFO *pItem , int AddNum)
{

	pItem->Attack_Rating -= AddNum*DownNum;
	return TRUE;

}
//�����
int sinDownAbsorbAging(sITEMINFO *pItem , float Percent , int Level)
{

	pItem->fAbsorb -= Percent*(float)DownNum; 

	int Temp = Level-9; //���� 10�̻��� ������ ����ŭ�� �����ش�
	if(Temp >0 ){
		if(Temp == 1){
			pItem->fAbsorb -= Percent;
		}
		else{
			pItem->fAbsorb -= Percent*(float)DownNum;

		}

	}
	return TRUE;

}

//ũ��Ƽ��
int sinDownCriticalAging(sITEMINFO *pItem)
{
	pItem->Critical_Hit -=1; //�ϴ� �ϳ������ְ�
	if(DownNum > 2){
		if(pItem->ItemAgingNum[0] && (pItem->ItemAgingNum[0]%2) == 1){
			pItem->Critical_Hit -= 1;
		}
	}
	return TRUE;

}

//����
int sinDownBlockRateAging(sITEMINFO *pItem)
{
	pItem->fBlock_Rating -=1; //�ϴ� �ϳ������ְ�
	if(DownNum > 2){
		if(pItem->ItemAgingNum[0] && (pItem->ItemAgingNum[0]%2) == 1){
			pItem->fBlock_Rating -= 1;

		}
	}
	return TRUE;

}

//����¡ �����ʱ�ȭ
int sinAgingItemInit(sITEMINFO *pItem , int Down)
{

	float TempDefense[2] = {0,0}; 
	DownNum = Down + 1;	
	int AgingLevelTemp = 0;
	AgingLevelTemp = pItem->ItemAgingNum[0];

	pItem->ItemAgingNum[0] -= DownNum;	//���� ������ �����ش� (ũ��Ƽ�� ��깮��)
/*
	if((pItem->CODE & sinITEM_MASK2) == sinMA1){
	}
	else{
	
*/	
	//����¡ �����ٿ� --
	switch(pItem->CODE & sinITEM_MASK2){
		case sinWA1: //���� 
			//���ݷ� 
			sinDownDamageAging(pItem,AgingLevelTemp);
			//���߷�
			sinDownAttackRateAging(pItem , 10);
			//������
			sinDownDurabilityAging(pItem); 

		break;
		case sinWC1: //Ŭ��
			//���ݷ� 
			sinDownDamageAging(pItem,AgingLevelTemp);
			//���߷�
			sinDownAttackRateAging(pItem , 5);
			//ũ��Ƽ��  
			sinDownCriticalAging(pItem);

		break;

		case sinWH1: //�ظ� 
			//���ݷ� 
			sinDownDamageAging(pItem,AgingLevelTemp);

			//���߷�
			sinDownAttackRateAging(pItem , 10);
			//������
			sinDownDurabilityAging(pItem); 

		break;
		case sinWM1: //������ ������ 
			//���ݷ� 
			sinDownDamageAging(pItem,AgingLevelTemp);

			//���߷�
			sinDownAttackRateAging(pItem , 10);

			//���  
			pItem->fIncrease_Mana -= 10*DownNum;

		break;
		case sinWP1: //â 
			//���ݷ� 
			sinDownDamageAging(pItem,AgingLevelTemp);

			//���߷�
			sinDownAttackRateAging(pItem , 5);

			//ũ��Ƽ��  
			sinDownCriticalAging(pItem);

		break;
		case sinWS1: //Ȱ 
			//���ݷ� 
			sinDownDamageAging(pItem,AgingLevelTemp);

			//ũ��Ƽ��  
			sinDownCriticalAging(pItem);

			//������
			sinDownDurabilityAging(pItem); 
		break;

		case sinWS2: //Į  
			//���ݷ� 
			sinDownDamageAging(pItem,AgingLevelTemp);

			//���߷�
			sinDownAttackRateAging(pItem , 5);
			
			//ũ��Ƽ��  
			sinDownCriticalAging(pItem);

		break;

		case sinWT1: //�ں��� 
			//���ݷ� 
			sinDownDamageAging(pItem,AgingLevelTemp);

			//ũ��Ƽ��  
			sinDownCriticalAging(pItem);

			//������
			//sinSetDurabilityAging(pItem); 
		break;
			
		case sinDS1: //���� 
			//���� 
			sinDownBlockRateAging(pItem);
			//�����
			sinDownAbsorbAging(pItem , 0.2f ,AgingLevelTemp );
			//������
			sinDownDurabilityAging(pItem); 
		break;

		case sinOM1: //������ ���� 
			//���� 
			sinDownDefenseAging(pItem,10);

			//�����
			sinDownAbsorbAging(pItem , 0.5f,AgingLevelTemp);

			//������
			sinDownDurabilityAging(pItem); 

		break;
		case sinDA1: case sinDA2://���� 
			//���� 
			sinDownDefenseAging(pItem,5);

			//�����
			sinDownAbsorbAging(pItem , 0.5f,AgingLevelTemp);

			//������
			sinDownDurabilityAging(pItem); 

		break; 
		case sinDB1: // ����� - ����¡ ������ �߰�(����)
			//���� 
			sinDownDefenseAging(pItem,10);
			//�����
			sinDownAbsorbAging(pItem , 0.5f, AgingLevelTemp);
			//������
			sinDownDurabilityAging(pItem); 
		break;
		case sinDG1: // ����� - ����¡ ������ �߰�(�尩)
			//���� 
			sinDownDefenseAging(pItem,10);
			//�����
			sinDownAbsorbAging(pItem , 0.5f, AgingLevelTemp);
			//������
			sinDownDurabilityAging(pItem); 
		break;
		case sinOA2: // ����� - ����¡ ������ �߰�(�ϸ�)
			//���� 
			sinDownDefenseAging(pItem,10);
			//���߷�
			sinDownAttackRateAging(pItem , 5);
			//������
			sinDownDurabilityAging(pItem); 
		break;
		}

		pItem->ItemAgingNum[1] = 0; //�ʱ�ȭ 
		pItem->ItemAgingCount[0] = 0;
		pItem->ItemAgingCount[1] = 0;
	
		// pluto ����¡
		if( pItem->Level >= 100 ){
			pItem->Level -= 0 ;
		}
		else

			pItem->Level -= 1; //������ ���ְ�
			if(DownNum > 2){
				if((pItem->ItemAgingNum[0] % 2 ) == 1){
					pItem->Level -=1; //����¡������ Ȧ���ϰ�� ������ �� �����ش� 
			}
	}


	ReformItem(pItem);  //������ ���� �ޱ� 
//	ReformMixItem( pItem ); //����¡ ������ 
	return TRUE;
}

int sinCheckAgingLevel(int Kind, bool bBillingUse)
{

	sITEM *pItem = 0;
	switch(Kind){
		case  SIN_AGING_ATTACK:
			if(!cInvenTory.InvenItem[sInven[0].ItemIndex-1].Flag ||
			!cInvenTory.InvenItem[sInven[0].ItemIndex-1].sItemInfo.ItemAgingNum[1])return FALSE;
			
			if((cInvenTory.InvenItem[sInven[0].ItemIndex-1].CODE &sinITEM_MASK2) == sinWA1 ||
				(cInvenTory.InvenItem[sInven[0].ItemIndex-1].CODE &sinITEM_MASK2) == sinWH1 ||
				(cInvenTory.InvenItem[sInven[0].ItemIndex-1].CODE &sinITEM_MASK2) == sinWM1 ){
					pItem = &cInvenTory.InvenItem[sInven[0].ItemIndex-1];
				}

		break;
		/*
		case  SIN_AGING_DEFENSE:
			//////////// ���� , ����  (�ι� üũ�� �ؾ��ϱ⶧���� �̷����س��´�)
			if(cInvenTory.InvenItem[sInven[1].ItemIndex-1].Flag ||
				cInvenTory.InvenItem[sInven[1].ItemIndex-1].sItemInfo.ItemAgingNum[1]){
					if((cInvenTory.InvenItem[sInven[1].ItemIndex-1].CODE &sinITEM_MASK2) == sinOM1){
						pItem = &cInvenTory.InvenItem[sInven[1].ItemIndex-1];
						if( pItem && pItem->sItemInfo.ItemKindCode == ITEM_KIND_AGING) {
							///////////ȣ��ɶ����� �÷��ش�  
							if(smConfig.DebugMode){
								pItem->sItemInfo.ItemAgingCount[0] +=200;
							}
							else{
								pItem->sItemInfo.ItemAgingCount[0]++;
							}
							if(pItem->sItemInfo.ItemAgingCount[1] &&  pItem->sItemInfo.ItemAgingCount[0] >= pItem->sItemInfo.ItemAgingCount[1] ){
								//������ �������� ������ 
								SendAgingUpgradeItemToServer(&pItem->sItemInfo); 
							}
						}
						pItem = 0;
					}
				}

			// ���� , �κ� 	
			if(cInvenTory.InvenItem[sInven[2].ItemIndex-1].Flag ||
				cInvenTory.InvenItem[sInven[2].ItemIndex-1].sItemInfo.ItemAgingNum[1]){
				if((cInvenTory.InvenItem[sInven[2].ItemIndex-1].CODE &sinITEM_MASK2) == sinDA1 ||
					(cInvenTory.InvenItem[sInven[2].ItemIndex-1].CODE &sinITEM_MASK2) == sinDA2 ){
					pItem = &cInvenTory.InvenItem[sInven[2].ItemIndex-1];
				}
			}
		
		break;
		*/
		case  SIN_AGING_CRITICAL:
			if(!cInvenTory.InvenItem[sInven[0].ItemIndex-1].Flag ||
			!cInvenTory.InvenItem[sInven[0].ItemIndex-1].sItemInfo.ItemAgingNum[1])return FALSE;
			if((cInvenTory.InvenItem[sInven[0].ItemIndex-1].CODE &sinITEM_MASK2) == sinWC1 ||
				(cInvenTory.InvenItem[sInven[0].ItemIndex-1].CODE &sinITEM_MASK2) == sinWS2 ||
				(cInvenTory.InvenItem[sInven[0].ItemIndex-1].CODE &sinITEM_MASK2) == sinWS1 ||
				(cInvenTory.InvenItem[sInven[0].ItemIndex-1].CODE &sinITEM_MASK2) == sinWP1 ||
				(cInvenTory.InvenItem[sInven[0].ItemIndex-1].CODE &sinITEM_MASK2) == sinWT1){
					pItem = &cInvenTory.InvenItem[sInven[0].ItemIndex-1];

				}

		break;

		case  SIN_AGING_BLOCK:
			if(	!cInvenTory.InvenItem[sInven[1].ItemIndex-1].Flag ||
				!cInvenTory.InvenItem[sInven[1].ItemIndex-1].sItemInfo.ItemAgingNum[1])return FALSE;

			if((cInvenTory.InvenItem[sInven[1].ItemIndex-1].CODE &sinITEM_MASK2) == sinDS1)
				pItem = &cInvenTory.InvenItem[sInven[1].ItemIndex-1];

		break;

		// ����� - ����¡ ������ ������
		case SIN_AGING_DEFENSE_ARMOR: // ����, �κ�
			// ���� , �κ� 	
			if(cInvenTory.InvenItem[sInven[2].ItemIndex-1].Flag ||
				cInvenTory.InvenItem[sInven[2].ItemIndex-1].sItemInfo.ItemAgingNum[1]){
					if((cInvenTory.InvenItem[sInven[2].ItemIndex-1].CODE &sinITEM_MASK2) == sinDA1 ||
						(cInvenTory.InvenItem[sInven[2].ItemIndex-1].CODE &sinITEM_MASK2) == sinDA2 ){
							pItem = &cInvenTory.InvenItem[sInven[2].ItemIndex-1];
						}
				}
		break;
		
		// ����� - ����¡ ������ ������
		case SIN_AGING_DEFENSE_ORB: // ���� ����
			if(cInvenTory.InvenItem[sInven[1].ItemIndex-1].Flag ||
				cInvenTory.InvenItem[sInven[1].ItemIndex-1].sItemInfo.ItemAgingNum[1]){
					if((cInvenTory.InvenItem[sInven[1].ItemIndex-1].CODE &sinITEM_MASK2) == sinOM1){
						pItem = &cInvenTory.InvenItem[sInven[1].ItemIndex-1];
					}
				}
		break;

		// ����� - ����¡ ������ �߰�(����)
		case SIN_AGING_DEFENSE_BOOTS: // ����
			if(	!cInvenTory.InvenItem[sInven[9].ItemIndex-1].Flag ||
				!cInvenTory.InvenItem[sInven[9].ItemIndex-1].sItemInfo.ItemAgingNum[1])return FALSE;

			if((cInvenTory.InvenItem[sInven[9].ItemIndex-1].CODE &sinITEM_MASK2) == sinDB1)
				pItem = &cInvenTory.InvenItem[sInven[9].ItemIndex-1];
			break;

			// ����� - ����¡ ������ �߰�(�尩)
		case SIN_AGING_DEFENSE_GLOVES: // �尩
			if(	!cInvenTory.InvenItem[sInven[8].ItemIndex-1].Flag ||
				!cInvenTory.InvenItem[sInven[8].ItemIndex-1].sItemInfo.ItemAgingNum[1])return FALSE;

			if((cInvenTory.InvenItem[sInven[8].ItemIndex-1].CODE &sinITEM_MASK2) == sinDG1)
				pItem = &cInvenTory.InvenItem[sInven[8].ItemIndex-1];
			break;

			// ����� - ����¡ ������ �߰�(�ϸ�)
		case SIN_AGING_DEFENSE_ARMLETS: // �ϸ�
			if(	!cInvenTory.InvenItem[sInven[7].ItemIndex-1].Flag ||
				!cInvenTory.InvenItem[sInven[7].ItemIndex-1].sItemInfo.ItemAgingNum[1])return FALSE;

			if((cInvenTory.InvenItem[sInven[7].ItemIndex-1].CODE &sinITEM_MASK2) == sinOA2)
				pItem = &cInvenTory.InvenItem[sInven[7].ItemIndex-1];
			break;
	}

	if(!pItem || pItem->sItemInfo.ItemKindCode != ITEM_KIND_AGING)return FALSE;

	///////////ȣ��ɶ����� �÷��ش�  
	if(smConfig.DebugMode)
	{
		if(bBillingUse == false)
		{
			pItem->sItemInfo.ItemAgingCount[0] +=200;
		}
		else if(bBillingUse == true)
			pItem->sItemInfo.ItemAgingCount[0] = pItem->sItemInfo.ItemAgingCount[1];
	}
	else
	{   // mature item age xxstr
		if(bBillingUse == false)
		{
			//pItem->sItemInfo.ItemAgingCount[0]++;
			pItem->sItemInfo.ItemAgingCount[0] += 50;
		}
		else if(bBillingUse == true)
		{
			pItem->sItemInfo.ItemAgingCount[0] = pItem->sItemInfo.ItemAgingCount[1];
		}
	}

	if(pItem->sItemInfo.ItemAgingCount[1] && pItem->sItemInfo.ItemAgingCount[0] >= pItem->sItemInfo.ItemAgingCount[1] ){
		//������ �������� ������ 
		SendAgingUpgradeItemToServer(&pItem->sItemInfo);
	}



	/*

	//����¡ �������� �ƴϰų� ����¡�� ���� �������� �����Ѵ� 
	if(pItem->sItemInfo.ItemKindCode != ITEM_KIND_AGING ||
		(pItem->sItemInfo.ItemAgingCount[0] >= pItem->sItemInfo.ItemAgingCount[1]) )
		return FALSE;
		

	//////////////�� �밡�� �۾� 
	if(!CheckItemForm(&pItem->sItemInfo)){ //������ �����ޱ� 
		SendSetHackUser(12); //��ŷ�� �Ϸ����ߴ� ����!! ������ ��� TRUE ���� ���� 
		return FALSE;

	}

	//����¡ ������ ����Ȯ�� 
	if(!CheckMixItem( &pItem->sItemInfo )){
		SendSetHackUser(52); //��ŷ�� �Ϸ����ߴ� ���� ������ ��� TRUE ���� ���� 
		return FALSE;
	}
	*/

	return TRUE;	
}

//�ɷ�ġ�� ���� �������� �޴´� 
int sinRecvAgingIncreStateItem(sITEMINFO *pItem)
{
	for(int i = 0; i  < INVENTORY_MAXITEM ; i++){ 
		if(cInvenTory.InvenItem[i].sItemInfo.BackUpChkSum  == pItem->BackUpChkSum &&
			cInvenTory.InvenItem[i].sItemInfo.BackUpKey == pItem->BackUpKey &&
			cInvenTory.InvenItem[i].sItemInfo.CODE == pItem->CODE){
				memcpy(&cInvenTory.InvenItem[i].sItemInfo,pItem,sizeof(sITEMINFO));
				cInvenTory.ReFormInvenItem();   //�κ��丮 ������ ���� 
				cInvenTory.CheckRequireItemToSet(&cInvenTory.InvenItem[i]); 
				cInvenTory.SetItemToChar(); //�ɷ�ġ ������
				break;

		}
	}

	return TRUE;
}

//����¡ �����ۿ� ���� ��ŷ�� ���´� 
int sinCheckAgingItemHack(sITEM *pItem)
{ 
	if(	pItem->sItemInfo.ItemKindCode == ITEM_KIND_CRAFT){
		return FALSE;

	}
	return TRUE;
}

///////////////��ŷ������ ���� ���� �Ѱ����� �����Ѵ� 
int sinMinusMoney(int Money,int Kind)
{
	//������ ������ ����޴´�.
	if(Kind){
		//--------------------------------------------------------------------------//
		#ifdef HASIEGE_MODE
		    //������ �������� ���̳ʽ� �Ӵ� ����
			
		    sinChar->Money -= Money+((Money*cSinSiege.GetTaxRate())/100);
			SetTotalSubMoney(Money+(Money*cSinSiege.GetTaxRate())/100);
		#else
			sinChar->Money -=Money;
		#endif
		//---------------------------------------------------------------------------//
	}
	else{
		sinChar->Money -=Money;
		SetTotalSubMoney(Money);
	
	}

	ReformCharForm();//������ 
	
	SendSaveMoney(); //�ݾ� ������ ���ϰ��ϱ����� ȣ���Ѵ� 

	return TRUE	;		
}

int sinPlusMoney(int Money)
{
	sinChar->Money += Money;

	ReformCharForm();//������ 
	SetTotalAddMoney(Money);
	SendSaveMoney(); //�ݾ� ������ ���ϰ��ϱ����� ȣ���Ѵ� 

	return TRUE;
}

///////////////��ŷ������ ���� ���� �Ѱ����� �����Ѵ� (â�� ���� ���� )
int sinMinusMoney2(int Money)
{
	sinChar->Money -= Money;

	ReformCharForm();//������ 
	SendSaveMoney(); //�ݾ� ������ ���ϰ��ϱ����� ȣ���Ѵ� 

	return TRUE;
}

int sinPlusMoney2(int Money)
{
	sinChar->Money += Money;

	ReformCharForm();//������ 
	SendSaveMoney(); //�ݾ� ������ ���ϰ��ϱ����� ȣ���Ѵ� 

	return TRUE;
}

//���ҼӼ��� ���Ѵ� 
int sinGetElement(smCHAR_INFO *pCharInfo)
{
/*
	sinSkillResistance[sITEMINFO_BIONIC] += Zenith_Element[sinSkill.UseSkill[i].Point-1]/TempDivide;
	sinSkillResistance[sITEMINFO_FIRE] += Zenith_Element[sinSkill.UseSkill[i].Point-1]/TempDivide;
	sinSkillResistance[sITEMINFO_ICE] += Zenith_Element[sinSkill.UseSkill[i].Point-1]/TempDivide;
	sinSkillResistance[sITEMINFO_LIGHTING] += Zenith_Element[sinSkill.UseSkill[i].Point-1]/TempDivide;
	sinSkillResistance[sITEMINFO_POISON] += Zenith_Element[sinSkill.UseSkill[i].Point-1]/TempDivide;
*/	
	
	
//	pCharInfo->Resistance
	
	return TRUE;
}

// Premiacao dos eventos

char  *PresentWeaponName[5][9] ={
	{"sp103" , 0,0,0,0,0,0,0,0 },
	{"fo104","fo105","fo106",0,0,0,0,0,0},
	{"fo101","fo102","fo103","os106",0,0,0,0,0},
	{"fo107","se103","se102","os107",0,0,0,0,0},
	{"se101","os108","fo108","gp111",0,0,0,0,0},
	
};


char  *PresentArmorName[5][9] ={
	{"pm104" , 0,0,0,0,0,0,0,0 },
	{"gp104","gp105","gp106","gp107",0,0,0,0,0},
	{"gp101","gp102","gp103","os106",0,0,0,0,0},
	{"gp108","gp109","gp110","os107",0,0,0,0,0},
	{"se101","os108","fo108","gp111",0,0,0,0,0},
	
};

int PresentPercentIndex[5] = {5900,2250,1450,250,150};

// Premia��o evento quebra-cabe�a aqui
char  *PresentWeaponName2[8][9] ={
	{"ca120",0,0,0,0,0,0,0,0 }, // 2500
	{"fo109",0,0,0,0,0,0,0,0 }, // 2500
	{"ca119",0,0,0,0,0,0,0,0 }, // 1590
	{"os108",0,0,0,0,0,0,0,0 }, // 1500
	{"os109",0,0,0,0,0,0,0,0 }, // 700
	{"bi245",0,0,0,0,0,0,0,0 }, // 700
	{"bi256",0,0,0,0,0,0,0,0 }, // 500
	{"bi255",0,0,0,0,0,0,0,0 }, // 10
};

//��
char  *PresentArmorName2[8][9] ={
	{"ca120",0,0,0,0,0,0,0,0 }, // 2500
	{"fo129",0,0,0,0,0,0,0,0 }, // 2500
	{"ca119",0,0,0,0,0,0,0,0 }, // 1590
	{"os108",0,0,0,0,0,0,0,0 }, // 1500
	{"os109",0,0,0,0,0,0,0,0 }, // 700
	{"bi245",0,0,0,0,0,0,0,0 }, // 700
	{"bi256",0,0,0,0,0,0,0,0 }, // 500
	{"bi255",0,0,0,0,0,0,0,0 }, // 10
};


int PresentPercentIndex2[8] = {2000,2000,1590,1500,600,600,900,900};

char  *PresentChocoWeaponName3[17][9] ={
	{"sp115",0,0,0,0,0,0,0,0 },		//1
	{"pm104",0,0,0,0,0,0,0,0 },		//2
	{"GP120",0,0,0,0,0,0,0,0 },		//3
	{"GP109",0,0,0,0,0,0,0,0 },		//4
	{"bi106",0,0,0,0,0,0,0,0},		//5
	{"Bi107",0,0,0,0,0,0,0,0},		//6
	{"OS107",0,0,0,0,0,0,0,0},		//7
	{"OS108",0,0,0,0,0,0,0,0},		//8
	{"Da131",0,0,0,0,0,0,0,0},		//9
	{"Da231",0,0,0,0,0,0,0,0},		//10
	{"Da133",0,0,0,0,0,0,0,0},		//11
	{"Da233",0,0,0,0,0,0,0,0},		//12
	{"OR233",0,0,0,0,0,0,0,0},		//13
	{"FO107",0,0,0,0,0,0,0,0},		//14
	{"FO106",0,0,0,0,0,0,0,0},		//15
	{"bi108",0,0,0,0,0,0,0,0},		//16
	{"OS109",0,0,0,0,0,0,0,0},		//17
};

char  *PresentChocoArmorName3[17][9] ={
	{"sp115",0,0,0,0,0,0,0,0 },		//1
	{"pm104",0,0,0,0,0,0,0,0 },		//2
	{"GP120",0,0,0,0,0,0,0,0 },		//3
	{"GP109",0,0,0,0,0,0,0,0 },		//4
	{"bi106",0,0,0,0,0,0,0,0},		//5
	{"Bi107",0,0,0,0,0,0,0,0},		//6
	{"OS107",0,0,0,0,0,0,0,0},		//7
	{"OS108",0,0,0,0,0,0,0,0},		//8
	{"Da131",0,0,0,0,0,0,0,0},		//9
	{"Da231",0,0,0,0,0,0,0,0},		//10
	{"Da133",0,0,0,0,0,0,0,0},		//11
	{"Da233",0,0,0,0,0,0,0,0},		//12
	{"OR233",0,0,0,0,0,0,0,0},		//13
	{"FO107",0,0,0,0,0,0,0,0},		//14
	{"FO106",0,0,0,0,0,0,0,0},		//15
	{"bi108",0,0,0,0,0,0,0,0},		//16
	{"OS109",0,0,0,0,0,0,0,0},		//17
};

int PresentChocoPercentIndex3[17] = {1000,1000,100,200,1200,1200,489,10,600,600,600,600,400,900,900,200,1};


// �庰 - ĵ������ ���� ������
char  *PresentCandyWeaponName3[17][9] ={
	{"sp115",0,0,0,0,0,0,0,0 },		//1
	{"pm104",0,0,0,0,0,0,0,0 },		//2
	{"GP121",0,0,0,0,0,0,0,0 },		//3
	{"GP109",0,0,0,0,0,0,0,0 },		//4
	{"bi106",0,0,0,0,0,0,0,0},		//5
	{"Bi107",0,0,0,0,0,0,0,0},		//6
	{"OS107",0,0,0,0,0,0,0,0},		//7
	{"OS108",0,0,0,0,0,0,0,0},		//8
	{"Da139",0,0,0,0,0,0,0,0},		//9
	{"Da239",0,0,0,0,0,0,0,0},		//10
	{"Da141",0,0,0,0,0,0,0,0},		//11
	{"DA241",0,0,0,0,0,0,0,0},		//12
	{"OA137",0,0,0,0,0,0,0,0},		//13
	{"FO107",0,0,0,0,0,0,0,0},		//14
	{"FO106",0,0,0,0,0,0,0,0},		//15
	{"bi108",0,0,0,0,0,0,0,0},		//16
	{"OS109",0,0,0,0,0,0,0,0},		//17
};



char  *PresentCandyArmorName3[17][9] ={
	{"sp115",0,0,0,0,0,0,0,0 },		//1
	{"pm104",0,0,0,0,0,0,0,0 },		//2
	{"GP121",0,0,0,0,0,0,0,0 },		//3
	{"GP109",0,0,0,0,0,0,0,0 },		//4
	{"bi106",0,0,0,0,0,0,0,0},		//5
	{"Bi107",0,0,0,0,0,0,0,0},		//6
	{"OS107",0,0,0,0,0,0,0,0},		//7
	{"OS108",0,0,0,0,0,0,0,0},		//8
	{"Da139",0,0,0,0,0,0,0,0},		//9
	{"Da239",0,0,0,0,0,0,0,0},		//10
	{"Da141",0,0,0,0,0,0,0,0},		//11
	{"DA241",0,0,0,0,0,0,0,0},		//12
	{"OA137",0,0,0,0,0,0,0,0},		//13
	{"FO107",0,0,0,0,0,0,0,0},		//14
	{"FO106",0,0,0,0,0,0,0,0},		//15
	{"bi108",0,0,0,0,0,0,0,0},		//16
	{"OS109",0,0,0,0,0,0,0,0},		//17
};

int PresentCandyPercentIndex3[17] = {1000,1000,100,200,1200,1200,489,10,600,600,600,600,400,900,900,200,1};


// �庰 - �����ñ׸� ���޶��� ���� ������
char  *PresentMagicalGreenEmeraldWeaponName3[18][9] ={
	{"pm104",0,0,0,0,0,0,0,0 },	//1
	{"bi119",0,0,0,0,0,0,0,0 },		//2
	{"gp118",0,0,0,0,0,0,0,0 },		//3
	{"gp120",0,0,0,0,0,0,0,0 },		//4
	{"gp119",0,0,0,0,0,0,0,0},		//5
	{"se101",0,0,0,0,0,0,0,0},		//6
	{"os107",0,0,0,0,0,0,0,0},		//7
	{"os108",0,0,0,0,0,0,0,0},		//8
	{"os109",0,0,0,0,0,0,0,0},		//9
	{"os110",0,0,0,0,0,0,0,0},		//10
	{"os111",0,0,0,0,0,0,0,0},		//11
	{"bi112",0,0,0,0,0,0,0,0},		//12
	{"bi108",0,0,0,0,0,0,0,0},		//13
	{"bi107",0,0,0,0,0,0,0,0},		//14
	{"bi106",0,0,0,0,0,0,0,0},		//15
	{"fo107",0,0,0,0,0,0,0,0},		//16
	{"fo108",0,0,0,0,0,0,0,0},		//17
	{"fo109",0,0,0,0,0,0,0,0},		//18
};



char  *PresentMagicalGreenEmeraldArmorName3[18][9] ={
	{"pm104",0,0,0,0,0,0,0,0 },	//1
	{"bi119",0,0,0,0,0,0,0,0 },		//2
	{"gp118",0,0,0,0,0,0,0,0 },		//3
	{"gp120",0,0,0,0,0,0,0,0 },		//4
	{"gp119",0,0,0,0,0,0,0,0},		//5
	{"se101",0,0,0,0,0,0,0,0},		//6
	{"os107",0,0,0,0,0,0,0,0},		//7
	{"os108",0,0,0,0,0,0,0,0},		//8
	{"os109",0,0,0,0,0,0,0,0},		//9
	{"os110",0,0,0,0,0,0,0,0},		//10
	{"os111",0,0,0,0,0,0,0,0},		//11
	{"bi112",0,0,0,0,0,0,0,0},		//12
	{"bi108",0,0,0,0,0,0,0,0},		//13
	{"bi107",0,0,0,0,0,0,0,0},		//14
	{"bi106",0,0,0,0,0,0,0,0},		//15
	{"fo107",0,0,0,0,0,0,0,0},		//16
	{"fo108",0,0,0,0,0,0,0,0},		//17
	{"fo109",0,0,0,0,0,0,0,0},		//18
};

int PresentMagicalGreenEmeraldPercentIndex3[18] = {1400,300,400,200,100,1,300,200,1,1,1,100,1500,1500,1500,1200,800, 496};


// �庰 - �����ñ׸� ���� ���� ������
char  *PresentMagicalGreenJadeWeaponName3[15][9] ={
	{"pm103",0,0,0,0,0,0,0,0 },	//1
	{"Gp109",0,0,0,0,0,0,0,0 },	//2
	{"Gp121",0,0,0,0,0,0,0,0 },	//3
	{"Fo104",0,0,0,0,0,0,0,0 },		//4
	{"Fo105",0,0,0,0,0,0,0,0},		//5
	{"Fo106",0,0,0,0,0,0,0,0},		//6
	{"Os105",0,0,0,0,0,0,0,0},		//7
	{"Os106",0,0,0,0,0,0,0,0},		//8
	{"Da135",0,0,0,0,0,0,0,0},		//9
	{"Da137",0,0,0,0,0,0,0,0},		//10
	{"da235",0,0,0,0,0,0,0,0},		//11
	{"Da237",0,0,0,0,0,0,0,0},		//12
	{"Bi112",0,0,0,0,0,0,0,0},		//13
	{"Bi119",0,0,0,0,0,0,0,0},		//14
	{"bi121",0,0,0,0,0,0,0,0},		//15
};



char  *PresentMagicalGreedJadeArmorName3[15][9] ={
	{"pm103",0,0,0,0,0,0,0,0 },	//1
	{"Gp109",0,0,0,0,0,0,0,0 },	//2
	{"Gp121",0,0,0,0,0,0,0,0 },	//3
	{"Fo104",0,0,0,0,0,0,0,0 },		//4
	{"Fo105",0,0,0,0,0,0,0,0},		//5
	{"Fo106",0,0,0,0,0,0,0,0},		//6
	{"Os105",0,0,0,0,0,0,0,0},		//7
	{"Os106",0,0,0,0,0,0,0,0},		//8
	{"Da135",0,0,0,0,0,0,0,0},		//9
	{"Da137",0,0,0,0,0,0,0,0},		//10
	{"da235",0,0,0,0,0,0,0,0},		//11
	{"Da237",0,0,0,0,0,0,0,0},		//12
	{"Bi112",0,0,0,0,0,0,0,0},		//13
	{"Bi119",0,0,0,0,0,0,0,0},		//14
	{"bi121",0,0,0,0,0,0,0,0},		//15
};

int PresentMagicalGreedJadePercentIndex3[15] = {1500,1500,200,1500,1500,1000,300,200,500,500,500,500,100,100,100};


// �庰 - ī���� ���� ���� ������
char  *PresentTearOfKaraWeaponName3[18][9] ={
	{"pm104",0,0,0,0,0,0,0,0 },		//1
	{"bi119",0,0,0,0,0,0,0,0 },		//2
	{"gp109",0,0,0,0,0,0,0,0 },		//3
	{"gp121",0,0,0,0,0,0,0,0 },		//4
	{"gp119",0,0,0,0,0,0,0,0},		//5
	{"se101",0,0,0,0,0,0,0,0},		//6
	{"os107",0,0,0,0,0,0,0,0},		//7
	{"os108",0,0,0,0,0,0,0,0},		//8
	{"os109",0,0,0,0,0,0,0,0},		//9
	{"os110",0,0,0,0,0,0,0,0},		//10
	{"os111",0,0,0,0,0,0,0,0},		//11
	{"bi112",0,0,0,0,0,0,0,0},		//12
	{"bi108",0,0,0,0,0,0,0,0},		//13
	{"bi107",0,0,0,0,0,0,0,0},		//14
	{"bi106",0,0,0,0,0,0,0,0},		//15
	{"fo107",0,0,0,0,0,0,0,0},		//16
	{"fo108",0,0,0,0,0,0,0,0},		//17
	{"fo109",0,0,0,0,0,0,0,0},		//18
};



char  *PresentTearOfKaraArmorName3[18][9] ={
	{"pm104",0,0,0,0,0,0,0,0 },		//1
	{"bi119",0,0,0,0,0,0,0,0 },		//2
	{"gp109",0,0,0,0,0,0,0,0 },		//3
	{"gp121",0,0,0,0,0,0,0,0 },		//4
	{"gp119",0,0,0,0,0,0,0,0},		//5
	{"se101",0,0,0,0,0,0,0,0},		//6
	{"os107",0,0,0,0,0,0,0,0},		//7
	{"os108",0,0,0,0,0,0,0,0},		//8
	{"os109",0,0,0,0,0,0,0,0},		//9
	{"os110",0,0,0,0,0,0,0,0},		//10
	{"os111",0,0,0,0,0,0,0,0},		//11
	{"bi112",0,0,0,0,0,0,0,0},		//12
	{"bi108",0,0,0,0,0,0,0,0},		//13
	{"bi107",0,0,0,0,0,0,0,0},		//14
	{"bi106",0,0,0,0,0,0,0,0},		//15
	{"fo107",0,0,0,0,0,0,0,0},		//16
	{"fo108",0,0,0,0,0,0,0,0},		//17
	{"fo109",0,0,0,0,0,0,0,0},		//18
};

int PresentTearOfKaraPercentIndex3[18] = {1400,300,400,200,100,1,300,200,1,1,1,100,1500,1500,1500,1200,800,496};

// Corre��o quebra cabe�a, estava pegando premia��o aqui
char  *PresentFindinvestigatorNineWeaponName3[1][9] = {"gf107",0,0,0,0,0,0,0,0 };
char  *PresentFindinvestigatorNineArmorName3[1][9] = {"gf107",0,0,0,0,0,0,0,0 };
int PresentFindinvestigatorNinePercentIndex3[1] = {10000};

// �庰 - ������� ã�ƶ� ���Ͼƹķ� ����
char  *PresentFindinvestigatorNineTaleWeaponName3[1][9] = {"gf108",0,0,0,0,0,0,0,0 };
char  *PresentFindinvestigatorNineTaleArmorName3[1][9] = {"gf108",0,0,0,0,0,0,0,0 };
int PresentFindinvestigatorNineTalePercentIndex3[1] = {10000};

// �庰 - ������� ã�ƶ� ���� ���� ������
char  *PresentFindinvestigatorWeaponName3[12][9] ={
	{"bi109",0,0,0,0,0,0,0,0 },		//1
	{"pm104",0,0,0,0,0,0,0,0 },		//2
	{"fo109",0,0,0,0,0,0,0,0 },		//3
	{"fo110",0,0,0,0,0,0,0,0 },		//4
	{"gp110",0,0,0,0,0,0,0,0},		//5
	{"gp119",0,0,0,0,0,0,0,0},		//6
	{"gp120",0,0,0,0,0,0,0,0},		//7
	{"bi178",0,0,0,0,0,0,0,0},		//8
	{"bi183",0,0,0,0,0,0,0,0},		//9
	{"bi177",0,0,0,0,0,0,0,0},		//10
	{"oa135",0,0,0,0,0,0,0,0},		//11
	{"or230",0,0,0,0,0,0,0,0},		//12
};



char  *PresentFindinvestigatorArmorName3[12][9] ={
	{"bi109",0,0,0,0,0,0,0,0 },		//1
	{"pm104",0,0,0,0,0,0,0,0 },		//2
	{"fo109",0,0,0,0,0,0,0,0 },		//3
	{"fo110",0,0,0,0,0,0,0,0 },		//4
	{"gp110",0,0,0,0,0,0,0,0},		//5
	{"gp119",0,0,0,0,0,0,0,0},		//6
	{"gp120",0,0,0,0,0,0,0,0},		//7
	{"bi178",0,0,0,0,0,0,0,0},		//8
	{"bi183",0,0,0,0,0,0,0,0},		//9
	{"bi177",0,0,0,0,0,0,0,0},		//10
	{"oa135",0,0,0,0,0,0,0,0},		//11
	{"or230",0,0,0,0,0,0,0,0},		//12
};

int PresentFindinvestigatorPercentIndex3[12] = {1500,1500,1300,1000,1500,1000,1500,300,200,100,50,50};


// Premia��o Evento Melancia
char  *PresentWeaponName3[9][9] ={
	{"OS107",0,0,0,0,0,0,0,0 },		//1
	{"SE101",0,0,0,0,0,0,0,0 },		//2
	{"fo109",0,0,0,0,0,0,0,0 },		//3
	{"os107",0,0,0,0,0,0,0,0},		//4
	{"bi119",0,0,0,0,0,0,0,0},		//5
	{"os109",0,0,0,0,0,0,0,0},		//6
	{"bc127",0,0,0,0,0,0,0,0},		//7
	{"os108",0,0,0,0,0,0,0,0},		//8
	{"BI246",0,0,0,0,0,0,0,0 },		//9
};

char  *PresentArmorName3[9][9] ={
	{"SE101",0,0,0,0,0,0,0,0 },		//1
	{"bi177",0,0,0,0,0,0,0,0 },		//2
	{"bc124",0,0,0,0,0,0,0,0 },		//3
	{"bc121",0,0,0,0,0,0,0,0},		//4
	{"SE101",0,0,0,0,0,0,0,0},		//5
	{"os108",0,0,0,0,0,0,0,0},		//6
	{"BI244",0,0,0,0,0,0,0,0},		//7
	{"BI246",0,0,0,0,0,0,0,0},		//8
	{"BI248",0,0,0,0,0,0,0,0 },		//9
};

int PresentPercentIndex3[9] = {2000,2000,1300,1200,1000,1000,1000,600,600};


// ����� - ���ĺ� ���� �̺�Ʈ
char  *PresentWeaponName5[11][9] ={
	{"pm104",0,0,0,0,0,0,0,0},													//1
	{"bi108",0,0,0,0,0,0,0,0},													//2
	{"bi106","bi107",0,0,0,0,0,0,0},											//3
	{"fo107",0,0,0,0,0,0,0,0},													//4
	{"or228","oa133",0,0,0,0,0,0,0},											//5
	{"os107","os108","fo109",0,0,0,0,0,0},										//6
	{"bi119",0,0,0,0,0,0,0,0},													//7
	{"gp119","gp120","gp121",0,0,0,0,0,0},										//8
	{"bi112",0,0,0,0,0,0,0,0},													//9
	{"bi213","bi214","bi215","bi216","bi217","bi218","bi219","bi220",0},		//10
	{"os109","se101",0,0,0,0,0,0,0},											//11
};

char  *PresentArmorName5[11][9] ={
	{"pm104",0,0,0,0,0,0,0,0},													//1
	{"bi108",0,0,0,0,0,0,0,0},													//2
	{"bi106","bi107",0,0,0,0,0,0,0},											//3
	{"fo107",0,0,0,0,0,0,0,0},													//4
	{"or228","oa133",0,0,0,0,0,0,0},											//5
	{"os107","os108","fo109",0,0,0,0,0,0},										//6
	{"bi119",0,0,0,0,0,0,0,0},													//7
	{"gp119","gp120","gp121",0,0,0,0,0,0},										//8
	{"bi112",0,0,0,0,0,0,0,0},													//9
	{"bi213","bi214","bi215","bi216","bi217","bi218","bi219","bi220",0},		//10
	{"os109","se101",0,0,0,0,0,0,0},											//11
};

int PresentPercentIndex5[11] = {1450,1300,2600,1198,1000,1000,300,100,50,1000,20};


DWORD sinForceOrbCode[] = {(sinFO1|sin01),(sinFO1|sin02),(sinFO1|sin03),(sinFO1|sin04),(sinFO1|sin05),(sinFO1|sin06),(sinFO1|sin07),(sinFO1|sin08),(sinFO1|sin09),(sinFO1|sin10),(sinFO1|sin11),(sinFO1|sin12),(sinFO1|sin13),(sinFO1|sin14),(sinFO1|sin15)}; // ����� - ����, ������ ���� �߰�

// ����� - ���� ���� �߰�
DWORD sinMagincForceOrbCode[] = {(sinFO1|sin21),(sinFO1|sin22),(sinFO1|sin23),(sinFO1|sin24),(sinFO1|sin25),(sinFO1|sin26),(sinFO1|sin27),(sinFO1|sin28),(sinFO1|sin29),(sinFO1|sin30),(sinFO1|sin31),(sinFO1|sin32),(sinFO1|sin33),(sinFO1|sin34)};
// ����� - ���� ���� ���� �߰�
DWORD sinBillingMagicForceOrbCode[] = {(sinFO1|sin35),(sinFO1|sin36),(sinFO1|sin37)};

DWORD sinWingItemQuestServer(sCRAFTITEM_SERVER *pWingItem , smCHAR_INFO *pChar_Info)
{
	//3�� ��������Ʈ
	int i = 0, j = 0 , k = 0; 
	int CodeCount = 0;
	int ItemCount = 0;
	int ItemCountPuzzle = 0;
	int PresentPercent = 0;
	int PresentItemIndex = 0;
	int PresentPercentSum = 0;
	int PresentItemCount = 0;
	int PotionNum = 0;
	short ItemCount80_2[4] = {0,};

	int ItemIndex = 0; 
	char *((*pPresentWeaponName)[9]);
	char *((*pPresentArmorName)[9]);
	int  *pPresentPercentIndex;

	int RandomTemp = 0 ;

	int CristalCount=0;
	int CristalFlag =0;
	//�ϰ����� ũ����Ż�� �ٽ�üũ�Ѵ�.
	for( i = 0 ; i < 7 ; i++ ){
		for( j = 0 ; j < 12 ; j++ ){
			if( pWingItem->SheltomCode[i]==CristalEventCODE[j] ){
				CristalCount = i+1;
			}
		}
	}
	
	int WatermelonCount=0;
	int WatermelonFlag =0;
	//����� - ���� ��ƿ���(7���� ������ �ٽ�üũ�Ѵ�.)
	for(int n = 0 ; n < 7 ; n++ )
	{
		if( pWingItem->SheltomCode[n]==WatermelonEventCODE )
		{
			WatermelonCount = n+1;
		}
	}

	int ValentineCount=0;
	int ValentineFlag =0;
	//�庰 - �߷�Ÿ�� ���ݸ� ��ƿ���(7���� ���ݸ��� �ٽ�üũ�Ѵ�.)
	for(int n = 0 ; n < 7 ; n++ )
	{
		if( pWingItem->SheltomCode[n]==ValentineEventCODE )
		{
			ValentineCount = n+1;
		}
	}


	int CandydaysCount=0;
	int CandydaysFlag =0;
	// �庰 - ĵ������ (7���� ĵ�� �ٽ�üũ�Ѵ�.)
	for(int n = 0 ; n < 7 ; n++ )
	{
		if( pWingItem->SheltomCode[n]==CandydaysEventCODE )
		{
			CandydaysCount = n+1;
		}
	}


	int MagicalGreenEmeraldCount=0;
	int MagicalGreenEmeraldFlag =0;
	int MagicalGreenJadeCount=0;
	int MagicalGreenJadeFlag =0;
	// �庰 - �����ñ׸� (7���� ���޶��� �ٽ�üũ�Ѵ�.)
	for(int a = 0 ; a < 7 ; a++ )
	{
		if( pWingItem->SheltomCode[a]==MagicalGreenEventCODE[1] )
		{
			MagicalGreenEmeraldCount = a+1;
		}
	}

	// �庰 - �����ñ׸� (7���� ���� �ٽ�üũ�Ѵ�.)
	for(int b = 0 ; b < 7 ; b++ )
	{
		if( pWingItem->SheltomCode[b]==MagicalGreenEventCODE[0] )
		{
			MagicalGreenJadeCount = b+1;
		}
	}

	int TearOfKaraCount=0;
	int TearOfKaraFlag =0;
	// �庰 - ī���� ���� (7���� ���� �ٽ�üũ�Ѵ�.)
	for(int n = 0 ; n < 7 ; n++ )
	{
		if( pWingItem->SheltomCode[n]==TeatOfKaraEventCODE )
		{
			TearOfKaraCount = n+1;
		}
	}


	// �庰 - ������� ã�ƶ�
	int FindinvestigatorNineCount=0;
	int FindinvestigatorNineFlag =0;
	int FindinvestigatorTaleCount=0;
	int FindinvestigatorTaleFlag =0;
	
	for(int a = 0 ; a < 1 ; a++ )
	{
		if( pWingItem->SheltomCode[a]==FindinvestigatorEventCODE[0] )
		{
			FindinvestigatorNineCount = a+1;
		}
	}

	for(int b = 0 ; b < 1 ; b++ )
	{
		if( pWingItem->SheltomCode[b]==FindinvestigatorEventCODE[1] )
		{
			FindinvestigatorTaleCount = b+1;
		}
	}


	// ����� - ���ĺ� ���� �̺�Ʈ
	int PristonAlphabetCount = 0;
	int PristonAlphabetFlag = 0;
	for( int c = 0 ; c < 7 ; c++ )
	{
		for( int d = 0 ; d < 7 ; d++ )
		{
			if( pWingItem->SheltomCode[c]==PristonAlphabetEventCODE[d] )
			{
				PristonAlphabetCount = c+1;
			}
		}
	}

	//�ٺ������� 
	if( pWingItem->SheltomCode[0] == (sinGF1 | sin02) ){
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 5;
		pPresentWeaponName = PresentWeaponName; //������ ����
		pPresentArmorName = PresentArmorName;
		pPresentPercentIndex = PresentPercentIndex;
		PotionNum = 30;
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;

		}
	}
	// ����ȣ������
	else if(pWingItem->SheltomCode[0] == (sinGF1 | sin03) &&  pWingItem->SheltomCode[1] == (sinGF1 | sin04)){
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 6;
		pPresentWeaponName = PresentWeaponName2;
		pPresentArmorName = PresentArmorName2;
		pPresentPercentIndex = PresentPercentIndex2;
		PotionNum = 20;
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;

		}
	}

	// ������ ����
	else if(pWingItem->SheltomCode[0] == (sinGF1|sin05) ) { //&&  pWingItem->SheltomCode[1] == (sinGF1 | sin04)){
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 6;
		pPresentWeaponName = PresentWeaponName2;
		pPresentArmorName = PresentArmorName2;
		pPresentPercentIndex = PresentPercentIndex2;
		PotionNum = 20;
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;

		}
	}
	//�ϰ����� ũ����Ż�� ���� ������ �ֱ�
	else if(CristalCount==7){
		CristalFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 5;
		//�ӽ÷�
		pPresentWeaponName   = PresentWeaponName3; //������ ����
		pPresentArmorName    = PresentArmorName3;
		pPresentPercentIndex = PresentPercentIndex3;
		PotionNum = 40;
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}
	//����� - ���� ��ƿ���
	else if(WatermelonCount==7)
	{
		WatermelonFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 9; // ����� - ���� �̺�Ʈ 12���� �� �Ѱ��� �������� �����Ѵ�. // ȣ�� �̺�Ʈ 9���� �� �Ѱ����� �����Ѵ�. // ���ϴ��� �ҿ� �̺�Ʈ 9������ �Ѱ����� �����Ѵ�.
		//�ӽ÷�
		pPresentWeaponName   = PresentWeaponName3; //������ ����
		pPresentArmorName    = PresentArmorName3;
		pPresentPercentIndex = PresentPercentIndex3;
		PotionNum = 5; // ����� - ���� �̺�Ʈ ���� �������� ������ ��� ���� ������ �����Ѵ�. //����� - ���ϴ��� �ҿ� �̺�Ʈ(���� ���� 5��)
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}

	//�庰 - �߷�Ÿ�� ���ݸ� ��ƿ���
	else if(ValentineCount==7)
	{
		ValentineFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 17; // �庰 - �߷�Ÿ�� ���ݸ� �̺�Ʈ 17���� �� �Ѱ��� �������� �����Ѵ�. 
		//�ӽ÷�
		pPresentWeaponName   = PresentChocoWeaponName3; //������ ����
		pPresentArmorName    = PresentChocoArmorName3;
		pPresentPercentIndex = PresentChocoPercentIndex3;
		PotionNum = 5; // �庰 - �߷�Ÿ�� �̺�Ʈ ���� �������� ������ ��� ���� ������ �����Ѵ�.
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}
	// ����� - ���ĺ� ���� �̺�Ʈ
	else if(PristonAlphabetCount==7){
		PristonAlphabetFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 11;
		//�ӽ÷�
		pPresentWeaponName   = PresentWeaponName5; //������ ����
		pPresentArmorName    = PresentArmorName5;
		pPresentPercentIndex = PresentPercentIndex5;
		PotionNum = 20;
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}


	// �庰 - ĵ������ ĵ�� ��ƿ���
	else if(CandydaysCount==7)
	{
		CandydaysFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 17; // �庰 - ĵ������ �̺�Ʈ 17���� �� �Ѱ��� �������� �����Ѵ�. 
		//�ӽ÷�
		pPresentWeaponName   = PresentCandyWeaponName3; //������ ����
		pPresentArmorName    = PresentCandyArmorName3;
		pPresentPercentIndex = PresentCandyPercentIndex3;
		PotionNum = 5; // �庰 - ĵ������ �̺�Ʈ ���� �������� ������ ��� ���� ������ �����Ѵ�.
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}

	// �庰 - �����ñ׸� -  ���� ��ƿ���
	else if(MagicalGreenJadeCount==7)
	{
		MagicalGreenJadeFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 15; // �庰 - �����ñ׸� �̺�Ʈ 15���� �� �Ѱ��� �������� �����Ѵ�. 
		//�ӽ÷�
		pPresentWeaponName    = PresentMagicalGreenJadeWeaponName3; //������ ����
		pPresentArmorName	 = PresentMagicalGreedJadeArmorName3;
		pPresentPercentIndex = PresentMagicalGreedJadePercentIndex3;
		PotionNum = 10; // �庰 - �����ñ׸� �̺�Ʈ ���� �������� ������ ��� ���� ������ �����Ѵ�.
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}


	// �庰 - �����ñ׸� -  ���޶��� ��ƿ���
	else if(MagicalGreenEmeraldCount==7)
	{
		MagicalGreenEmeraldFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 18; // �庰 - �����ñ׸� �̺�Ʈ 18���� �� �Ѱ��� �������� �����Ѵ�. 
		//�ӽ÷�
		pPresentWeaponName    = PresentMagicalGreenEmeraldWeaponName3; //������ ����
		pPresentArmorName	 = PresentMagicalGreenEmeraldArmorName3;
		pPresentPercentIndex = PresentMagicalGreenEmeraldPercentIndex3;
		PotionNum = 20; // �庰 - �����ñ׸� �̺�Ʈ ���� �������� ������ ��� ���� ������ �����Ѵ�.
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}

	// �庰 - ī���� ����  ���� ��ƿ���
	else if(TearOfKaraCount==7)
	{
		TearOfKaraFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 18; // ī���� ���� �̺�Ʈ 18���� �� �Ѱ��� �������� �����Ѵ�. 
		//�ӽ÷�
		pPresentWeaponName   = PresentTearOfKaraWeaponName3; //������ ����
		pPresentArmorName    = PresentTearOfKaraArmorName3;
		pPresentPercentIndex = PresentTearOfKaraPercentIndex3;
		PotionNum = 10; // �庰 - ĵ������ �̺�Ʈ ���� �������� ������ ��� ���� ������ �����Ѵ�.
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}


	// Corre��o quebra cabe�a
	else if( FindinvestigatorNineCount == 1 && FindinvestigatorTaleCount == 1 &&  pWingItem->DesCraftItem.CODE != 1000  )
	{
		for(i = 0 ; i < 5 ; i++)
		{
			

			if(sWingQuest[pWingItem->Index].ChangeItemCode)
			{
				if(sWingQuest[pWingItem->Index].NeedItemCode[i]  == pWingItem->SheltomCode[i]) break;
			}


			switch(pWingItem->SheltomCode[i])
			{
				case (sinQT1|sin09):
				case (sinQT1|sin10):
				case (sinQT1|sin11):
				case (sinQT1|sin06):
				case (sinQT1|sin12):
				break;
				default:
					FindinvestigatorNineFlag = 1;
					RandomTemp = GetRandomPos(0,100);
					ItemIndex = 1; 

					pPresentWeaponName   = PresentFindinvestigatorNineWeaponName3;
					pPresentArmorName    = PresentFindinvestigatorNineArmorName3;
					pPresentPercentIndex = PresentFindinvestigatorNinePercentIndex3;
					PotionNum = 10; 
					if(RandomTemp < 50){
						ItemCountPuzzle = 8;
					}
					else{
						ItemCountPuzzle = 16;
					}
					break;
			}

/*
		//	if( pWingItem->SheltomCode[i] == sinQT1|sin06 || pWingItem->SheltomCode[i] == sinQT1|sin09 || pWingItem->SheltomCode[i] == sinQT1|sin10 
		//			|| pWingItem->SheltomCode[i] == sinQT1|sin11 || pWingItem->SheltomCode[i] == sinQT1|sin12 ) break;
				

		//		if(sWingQuest[pWingItem->Index].NeedItemCode[i]  != pWingItem->SheltomCode[i])
		//		{
					FindinvestigatorNineFlag = 1;
					RandomTemp = GetRandomPos(0,100);
					ItemIndex = 1; // ������� ã�ƶ� ���ξƹķ� ����
					//�ӽ÷�
					pPresentWeaponName   = PresentFindinvestigatorNineWeaponName3; //������ ����
					pPresentArmorName    = PresentFindinvestigatorNineArmorName3;
					pPresentPercentIndex = PresentFindinvestigatorNinePercentIndex3;
					PotionNum = 10; 
					if(RandomTemp < 50){
						ItemCountPuzzle = 8;
					}
					else{
						ItemCountPuzzle = 16;
					}
					break;
	//			}
			*/
		}
	}

	// �庰 - ������� ã�ƶ�( ���ξƹķ��� �����ϰ� ������)
	else if( FindinvestigatorNineCount == 1 )
	{
		FindinvestigatorNineFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 1; // ������� ã�ƶ� ���Ͼƹķ� ����
		//�ӽ÷�
		pPresentWeaponName   = PresentFindinvestigatorNineTaleWeaponName3; //������ ����
		pPresentArmorName    = PresentFindinvestigatorNineTaleArmorName3;
		pPresentPercentIndex = PresentFindinvestigatorNineTalePercentIndex3;
		PotionNum = 10; 
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}

	// �庰 - ������� ã�ƶ�( ���Ͼƹķ��� �����ϰ� ������)
	else if( FindinvestigatorTaleCount == 1 ) 
	{
		FindinvestigatorTaleFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 12; 
		//�ӽ÷�
		pPresentWeaponName   = PresentFindinvestigatorWeaponName3; //������ ����
		pPresentArmorName    = PresentFindinvestigatorArmorName3;
		pPresentPercentIndex = PresentFindinvestigatorPercentIndex3;
		PotionNum = 10; 
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}
	else{
		ItemIndex = 8;
		pPresentWeaponName = PresentWeaponName2;
		pPresentArmorName = PresentArmorName2;
		pPresentPercentIndex = PresentPercentIndex2;
		PotionNum = 10;

		//����
		for(i = 0 ; i < 8 ; i++){
			if((pWingItem->SheltomCode[i] & sinITEM_MASK2) == sinPZ1 ||
				(pWingItem->SheltomCode[i] & sinITEM_MASK2) == sinPZ2 ){
					for( j = 0 ; j < 8 ; j++){
						if(i == j)continue;
						if(pWingItem->SheltomCode[i] == pWingItem->SheltomCode[j]){
							pWingItem->Result = FALSE;
							return FALSE;

						}
					}
					if((pWingItem->SheltomCode[i] & sinITEM_MASK2) == sinPZ1)
						ItemCountPuzzle++;
					if((pWingItem->SheltomCode[i] & sinITEM_MASK2) == sinPZ2)
						ItemCountPuzzle +=2;

			}
		}

	}
	// Premiacao evento quebra cabe�a
	if(ItemCountPuzzle == 8 || ItemCountPuzzle == 16){
		PresentPercent = GetRandomPos(0,10000);
		for(i = 0 ; i < ItemIndex ; i++){
			if(PresentPercent >= PresentPercentSum && (pPresentPercentIndex[i]+PresentPercentSum) >=PresentPercent ){
				PresentItemCount = 0;

				if(ItemCountPuzzle == 8){
					for(k = 0 ; k < 9 ; k++){
						if(pPresentWeaponName[i][k]){
							PresentItemCount++;
						}
					}
					PresentItemIndex = GetRandomPos(0,PresentItemCount-1);
					while(1)
					{
						if(pPresentWeaponName[i][PresentItemIndex])
						{
							for(j=0;j<MAX_ITEM;j++) 
							{
								if ( lstrcmpi( pPresentWeaponName[i][PresentItemIndex] , sItem[j].LastCategory )==0 ) 
								{
									pWingItem->DesCraftItem.sItemInfo.CODE = sItem[j].CODE;
									if((pWingItem->DesCraftItem.sItemInfo.CODE & sinITEM_MASK2) == sinPM1) 
										pWingItem->DesCraftItem.sItemInfo.PotionCount = PotionNum;
									if(CristalFlag)pWingItem->Result = SIN_WINGRESULT_CRISTAL;
									else pWingItem->Result = TRUE;
									return TRUE;
								}
							}
						}
						PresentItemIndex--;
						if(PresentItemIndex < 0 )break; 
					}
				}

				PresentItemCount = 0;
				if(ItemCountPuzzle == 16){
					for(k = 0 ; k < 9 ; k++){
						if(pPresentArmorName[i][k]){
							PresentItemCount++;
						}
					}
					PresentItemIndex = GetRandomPos(0,PresentItemCount-1);
					while(1){
						if(pPresentArmorName[i][PresentItemIndex]){
							for(j=0;j<MAX_ITEM;j++) {
								if ( lstrcmpi( pPresentArmorName[i][PresentItemIndex] , sItem[j].LastCategory )==0 ) {
									pWingItem->DesCraftItem.sItemInfo.CODE = sItem[j].CODE;
									if((pWingItem->DesCraftItem.sItemInfo.CODE & sinITEM_MASK2) == sinPM1) 
										pWingItem->DesCraftItem.sItemInfo.PotionCount = PotionNum;
									if(CristalFlag)pWingItem->Result = SIN_WINGRESULT_CRISTAL;
									else pWingItem->Result = TRUE;
									return TRUE;
								}
							}
						}
						PresentItemIndex--;
						if(PresentItemIndex < 0 )break; //���ѷ��� ����
					}
				}
			}
			else PresentPercentSum += pPresentPercentIndex[i];
		}
	}
	
	//80_2 Lv����Ʈ
	for(i = 0 ; i < 3 ; i++){
		switch(pWingItem->SheltomCode[i]){
			case (sinQT1|sin09):
				ItemCount80_2[0] = 1;
			break;
			case (sinQT1|sin10):
				ItemCount80_2[1] = 1;
			break;
			case (sinQT1|sin11):
				ItemCount80_2[2] = 1;
			break;

		}
	}
	if(ItemCount80_2[0] && ItemCount80_2[1] && ItemCount80_2[2]){
		pWingItem->Result = TRUE;
		pWingItem->DesCraftItem.sItemInfo.CODE = (sinQT1|sin12);
		return TRUE;

	}
	for(i = 0 ; i < 3 ; i++){
		if(pWingItem->SheltomCode[i] == (sinQT1|sin06)){
			ItemCount++;
		}
	}
	if(ItemCount == 3 && pChar_Info){
		pWingItem->Result = TRUE;
		switch(pChar_Info->JOB_CODE){
			case 1:		//������
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWA1 | sin08);
			break;
			case 2:		//��ī�ϼ�
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWC1 | sin08);
			break;
			case 3:		//����
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWS1 | sin10);
			break;
			case 4:		//����ũ��
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWP1 | sin09);
			break;
			case 5:		//��Ż��Ÿ
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWT1 | sin09);
			break;
			case 6:		//����Ʈ
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWS2 | sin10);
			break;
			case 7:		//������
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWM1 | sin09);
			break;
			case 8:		//������Ƽ��
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWM1 | sin09);
			break;
		}
		//�������� �������ش�
		pWingItem->DesCraftItem.sItemInfo.ItemKindCode = ITEM_KIND_QUEST_WEAPON;
		//SetChangeJob3QuestItem(&pWingItem->DesCraftItem.sItemInfo); //������ �ʱ����
		return TRUE;

	}
	//���� ����
	if(pWingItem->DesCraftItem.CODE == 1000){
		for( i = 0 ; i < 12 ; i++){
			for(j = 0 ; j < 16 ; j++){ // ����� - ����, ������ ���� �߰�(12 -> 14))
				if((pWingItem->SheltomCode[i] & sinITEM_MASK3) == SheltomCode2[j]){
					pWingItem->Head[i] = 0;
					pWingItem->CheckSum[i] = 0;
					pWingItem->SheltomCode[i] = sinForceOrbCode[j];
					break;
				}
				// ����� - ���� ���� �߰�
				else if((pWingItem->SheltomCode[i] & sinITEM_MASK3) == MagicSheltomCode[j]){
					pWingItem->Head[i] = 0;
					pWingItem->CheckSum[i] = 0;
					pWingItem->SheltomCode[i] = sinMagincForceOrbCode[j];
					break;
				}
			}
		}
		pWingItem->Result = TRUE;
		return 0x100;
	}
	else{
		for(i = 0 ; i < 5 ; i++){
			if(sWingQuest[pWingItem->Index].ChangeItemCode){
				CodeCount++;
				if(sWingQuest[pWingItem->Index].NeedItemCode[i]  == pWingItem->SheltomCode[i]){
					ItemCount++;
				}
			}
		}
		if(CodeCount == ItemCount){
			pWingItem->DesCraftItem.sItemInfo.CODE = sWingQuest[pWingItem->Index].ChangeItemCode;
			pWingItem->DesCraftItem.sItemInfo.ItemKindCode = 0;
			pWingItem->Result = TRUE; 
			return TRUE;

		}
	}
	pWingItem->Result = FALSE;
	return FALSE;
}

//������ ���������� ������
int SendWingQuestItem() //�������� ����Ʈ 
{
	SendWingItemToServer( &sWingItem_Send );   
	return TRUE;
}

//�������� ���������� �޴´�
int RecvWingItem(sCRAFTITEM_SERVER *pWingItem)
{
 
	sITEM *pItem=0; 
	int   Index = 0; 
	int   i = 0; 
	sITEM sinTempItem;  //�����ۿ� ���õ� ������ ��� �־�δ� Temp

	//if(pWingItem->Result != TRUE)return FALSE;

	//�����ϰ��� �����ϳ� -0-

	for( i = 0; i < INVENTORY_MAXITEM*2 ; i++){
		if(i<100){
			if(!cInvenTory.InvenItem[i].Flag)continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else{
			if(!cInvenTory.InvenItemTemp[i-100].Flag)continue;
			pItem = &cInvenTory.InvenItemTemp[i-100];
		}

		//����� FALSE�ϰ�쿡�� �� �����۵� �����Ѵ�
		if(pWingItem->Result == FALSE){
			cInvenTory.DeleteInvenItemToServer(pWingItem->DesCraftItem.sItemInfo.CODE , pWingItem->DesCraftItem.sItemInfo.ItemHeader.Head ,
			 pWingItem->DesCraftItem.sItemInfo.ItemHeader.dwChkSum);

		}

		//�����ڵ尡 ���� ���ڵ� ����� üũ�����ʴ´� 
		if(pItem->ItemPosition == 2){  
			if(pItem->Class == ITEM_CLASS_WEAPON_TWO)
				continue; 
		}

		for(int j = 0 ; j < 8 ; j++){
			if(pItem->sItemInfo.CODE == pWingItem->SheltomCode[j] &&
				pItem->sItemInfo.ItemHeader.Head == pWingItem->Head[j] &&
				pItem->sItemInfo.ItemHeader.dwChkSum == pWingItem->CheckSum[j]){
					pItem->Flag = 0; //�������� �����ش�
					cInvenTory.ReFormInvenItem();
					cInvenTory.CheckWeight();
				}
				
		}
	}	
	
	//�����Ͽ�����쿡 �������� �������� �����Ѵ�
	if(pWingItem->Result == TRUE){
		sinMinusMoney(pWingItem->Money);//���� ����
		SendSaveMoney(); //�ݾ� ������ ���ϰ��ϱ����� ȣ���Ѵ� 

		//�������� �κ��丮�� �����Ѵ�
		if(pWingItem->DesCraftItem.sItemInfo.CODE){
			if(LoadItemImage(&pWingItem->DesCraftItem.sItemInfo,&sinTempItem)){
				//����Ʈ �������� �ް� ������ ����
				if(sinTempItem.sItemInfo.ItemKindCode ==ITEM_KIND_QUEST_WEAPON){
					sinQuest_ChangeJob3.StartLevel = sinChar->Level;

				}
				sinSetSpecialItemCode(&sinTempItem.sItemInfo); //����Ⱦ������� �����Ѵ�
				cInvenTory.AutoSetInvenItem(&sinTempItem,1+pWingItem->DocIndex); //�ε����� 1��������� ��ǥ�� �����Ѵ�
				cInvenTory.ReFormInvenItem();
				ResetPotion();
				cInvenTory.ReFormPotionNum();	//���� ������ üũ�Ѵ�
			}
		}
	}

	ReformCharForm();//������ 
	cInvenTory.SetItemToChar();
	cInvenTory.CheckWeight();
	
	sinbaram_Stop = 0; //�̺�Ʈ�� �����۵��ǰ��Ѵ�
	cInvenTory.CheckPuzzle();

	return TRUE;	
}

//���� ����¡ �Ѵ�
int AgingRing()
{
	if(sInven[4].ItemIndex){
		if(cInvenTory.InvenItem[sInven[4].ItemIndex-1].sItemInfo.ItemAgingCount[1] && cInvenTory.InvenItem[sInven[4].ItemIndex-1].sItemInfo.CODE == (sinOR2|sin01)){
			if(smConfig.DebugMode){
				cInvenTory.InvenItem[sInven[4].ItemIndex-1].sItemInfo.ItemAgingCount[0] +=100;
			}
			else
				cInvenTory.InvenItem[sInven[4].ItemIndex-1].sItemInfo.ItemAgingCount[0]++;
			if(cInvenTory.InvenItem[sInven[4].ItemIndex-1].sItemInfo.ItemAgingCount[0] >= 
				cInvenTory.InvenItem[sInven[4].ItemIndex-1].sItemInfo.ItemAgingCount[1]){
					SendAgingUpgradeItemToServer(&cInvenTory.InvenItem[sInven[4].ItemIndex-1].sItemInfo);

				}
		}
	}
	if(sInven[5].ItemIndex){
		if( cInvenTory.InvenItem[sInven[5].ItemIndex-1].sItemInfo.ItemAgingCount[1] &&cInvenTory.InvenItem[sInven[5].ItemIndex-1].sItemInfo.CODE == (sinOR2|sin01)){
			if(smConfig.DebugMode){
				cInvenTory.InvenItem[sInven[5].ItemIndex-1].sItemInfo.ItemAgingCount[0] +=100;
			}
			else
				cInvenTory.InvenItem[sInven[5].ItemIndex-1].sItemInfo.ItemAgingCount[0]++;
			if(cInvenTory.InvenItem[sInven[5].ItemIndex-1].sItemInfo.ItemAgingCount[0] >= 
				cInvenTory.InvenItem[sInven[5].ItemIndex-1].sItemInfo.ItemAgingCount[1]){
					SendAgingUpgradeItemToServer(&cInvenTory.InvenItem[sInven[5].ItemIndex-1].sItemInfo);

				}

		}
	}

	return TRUE;
}

//���ڿ� �޸����� �ѱ��
int NumLineComa(int Num , char *pBuff)
{

	int i = 0;
	char strBuff[128];
	wsprintf(strBuff,"%d",Num);   
	int cnt = 0;
	int cnt2 = 0;
	int cnt3 = 0;

	int len = lstrlen(strBuff);
	while(1){
		if(strBuff[cnt]){ 
			pBuff[cnt+cnt2] = strBuff[cnt];
			cnt3 = (len-1)-cnt;
			if((cnt3 % 3) ==0 && cnt3 != 0){
				cnt2++;
				pBuff[cnt+cnt2] = ',';
			}
			cnt++;

		}
		else break;
	}

	return TRUE;
}

//������ ������ ��� ������ �����Ѵ� (����μ�)
int sinSaveGame(DWORD CODE , int Count)
{
	DWORD MASK_CODE = (CODE & sinITEM_MASK2);

	//����ϰ�� 
	if(MASK_CODE == sinPM1 && Count >= 4 ){
		SaveGameData();

	}
	if((  MASK_CODE == sinPL1 || MASK_CODE == sinPS1 ) && Count >= 10){
		SaveGameData();
	}
	return TRUE;
}

//��¥�� ������������ ������� �����ش�
int OverDay_Item_Flag = 0;
int OverDay_Item_Delete(sITEM *pItem)
{ 
	return TRUE;
}


//��� �������̽��� �ݴ´�
int sinCloseInterFace() { return TRUE; }

int sinCheck_ShowHelpMap() { return TRUE; }

//���� �������� �޴´�
int sinRecvForceOrb(sITEMINFO *pItemInfo , int Count) { return TRUE; }

DWORD SummonSkillCode[] = {
	SKILL_METAL_GOLEM,
	SKILL_FIRE_ELEMENTAL,
	SKILL_RECALL_WOLVERIN,
	0,

};
int SummonSkillCodeIndex[10] = {0,};

//����Ŭ���̺�Ʈ
int sinDoubleClick() { return TRUE; }

