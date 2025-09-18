/*----------------------------------------------------------------------------*
*	ÆÄÀÏ¸í :  sinSubMain.cpp	
*	ÇÏ´ÂÀÏ :  °¢Á¾ ÇÔ¼öµéÀ» °ü¸®ÇÑ´Ù 
*	ÀÛ¼ºÀÏ :  ÃÖÁ¾¾÷µ¥ÀÌÆ® 12¿ù
*	Àû¼ºÀÚ :  ¹Ú»ó¿­ 
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
*								Àü¿ªº¯¼ö 			
*-----------------------------------------------------------------------------*/	
HFONT sinFont = 0;   //ÆùÆ® 
HFONT sinMessageFont = 0;   //¸Þ¼¼Áö ÆùÆ® 
HFONT sinBoldFont = 0;   //¸Þ¼¼Áö ÆùÆ® 


int sinTestFlag;     //Å×½ºÆ® ÇÃ·¢ 
int sinSecretFlag = 0;  //¾ÏÈ£ ÇÃ·¢ 


int sinMouseButton[2] = { 0,0 };
int sinKeyClick[256];

int MouseButtonUpEvent = 0;   

int MatCursorDefault;       //¾ÆÀÌÅÛ ÆÈ±â Ä¿¼­ 
int MatCursorSell;          //¾ÆÀÌÅÛ ÆÈ±â Ä¿¼­ 
int MatCursorBuy;			//¾ÆÀÌÅÛ »ç±â Ä¿¼­ 
int MatCursorRepair;	   	//°íÄ¡±â Ä¿¼­ ÀÌ¹ÌÁö 	
int MatCursorAttack;		//°ø°Ý 
int MatCursorGetItem1;		//¾ÆÀÌÅÛ ÁÝ±â 
int MatCursorGetItem2;		//¾ÆÀÌÅÛ ÁÝ±â 2
int MatCursorTalk;			//¸»ÇÏ±â 

int CursorClass = 1;        //Ä¿¼­Á¾·ù (default·Î 1À» ÁØ´Ù  ¾ÆÀÌÅÛÀ» ÁýÀ» ¶§ CursorClass = 0À¸·ÎÁØ´Ù )

int sinMoveKindInter[MAX_SIN_KIND_INTER]={0,0,0,0,0,0,0,0,0,0,0,0,0}; //°¢Á¾ ÆûÀÌ ¿òÁ÷ÀÌ´Â °ª // ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ãß°¡·Î °ªÀ» ÇÏ³ª´õ Ãß°¡

int sinSec = 0;         //ÃÊ¸¦ ±¸ÇÑ´Ù 
int sinMainCounter = 0; //¸ÞÀÎ·çÇÁ¸¦ µ¹¶§ Ä«¿îÆ®ÇØÁØ´Ù 

float DeCreaSTM  = 0;
float InCreaSTM  = 0;
float InCreaLIFE = 0;
float InCreaMANA = 0;


char szTestBuff2[64]; //ÀÌ¹ÌÁö ·Îµå½Ã ÀÌ¹ÌÁö°¡ ¾ø´Â °ÍÀ» È®ÀÎÇØÁØ´Ù 
POINT TestImageSize = {0,0};

int Accuracy_Table[][2] = {
	   
#include "sinTable.h"
	-1
};


int ItemIndex1[3] = {0,0,0};	//ÀüÁ÷À» À§ÇÑ ³¯Ä¡±â ÀÎµ¦½º ÀúÀå 
int ItemIndex2[3] = {0,0,0};

int ChangeJobButonCheck2 = 0; //¹öÆ°´Ù¿îÀ» ÇÑ¹ø °Å³Ê¶Ù´Â ÇÃ·¢(ÀÌ°ÍµÎ ¿ª½Ã ¶¯»§ÀÌ´Ù ¾¾¹Ù!!)
int ItemImageNotExitFlag = 0;
int DownNum = 0;


void InitSub()
{
	
	sinCreatFont(); //ÆùÆ®»ý¼º 	
}
/*----------------------------------------------------------------------------*
*						¼­ºê¸ÞÀÎ ¸ÞÀÎ
*-----------------------------------------------------------------------------*/	
void MainSub()
{
	sinProc(SINKEYDOWN);		//Å°ÀÔ·ÂÀÌ ÀÖÀ»¶§ 	
	sinSec++;
	sinMainCounter++; //¸ÞÀÎÀÇ Ä«¿îÅÍ 

	if(sinSec >= 70){ // 1ÃÊ¸¶´Ù ÇÑ¹ø¾¿ ½ÇÇà 
		sinRegen();      //½ºÅ×¹Ì³ªÀç»ý (ÇöÀç´Â ½ºÅ×¹Ì³ª¸¸ Àç»ýÇÑ´Ù )
		sinUseStamina(); //½ºÅ×¹Ì³ª¸¦ »ç¿ëÇÑ´Ù 
		sinSec = 0;

	}
	if((sinMainCounter&3) == 0) //70ÀÇ 1/4ÀÏ¶§ ½ÇÇà 
		sinSetRegen();

	if((sinMainCounter % 70) == 0)
		AgingRing();

	////////////////////////////////////¹Ì´Ï¸Ê¶§¹®¿¡ ÀÌ°÷À¸·Î»°´Ù
	cSkill.CheckSkillMastery(); //¸¶½ºÅÍ¸®¸¦ Ã¼Å©ÇÑ´Ù 
	CheckContinueSkill(); //Áö¼ÓÀûÀ¸·Î ¾²´Â ½ºÅ³À» Ã¼Å©ÇØ¼­ ½Ã°£ÀÌ Áö³ª¸é ¾ø¾ÖÁØ´Ù 
	

}
/*----------------------------------------------------------------------------*
*						¼­ºê¸ÞÀÎ ±×¸®±â 
*-----------------------------------------------------------------------------*/	
void DrawSub()     
{

}
/*----------------------------------------------------------------------------*
*						¼­ºê¸ÞÀÎ Á¾·á 
*-----------------------------------------------------------------------------*/	
void CloseSub()
{
    
}
/*----------------------------------------------------------------------------*
*							  Ä¿¼­ 
*-----------------------------------------------------------------------------*/	
void InitCursor() {}
void DrawCursor() {}
/*----------------------------------------------------------------------------*
*				     ½ºÇÁ¶óÀÌÆ® ÀÌ¹ÌÁö¸¦ ±×¸°´Ù 
*-----------------------------------------------------------------------------*/	
void DrawSprite(int winX, int winY, void* pdds, int x, int y, int width, int height, int Bltflag) {}
/*----------------------------------------------------------------------------*
*		¾ÆÀÌÅÛÀÇ Á¤º¸(ASE)¸¦ ±¸ÇØ¿Í¼­ Æ÷ÀÎÅÍ(*szImagePath)¿¡ ¼ÂÆÃÇÑ´Ù 
*-----------------------------------------------------------------------------*/	
int  sinGetItemInfo(DWORD CODE, char* szImagePath) { return TRUE; }

/*----------------------------------------------------------------------------*
*					   ¼­¹ö¿¡¼­ Data¸¦ ¹Þ´Â´Ù 
*-----------------------------------------------------------------------------*/	
extern int DecodeCompress( BYTE *lpSrcData , BYTE *lpDestData ); //¾ÐÃàµ¥ÀÌÅ¸ ÇØµ¶ ( Z/NZ ¹æ½Ä )
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
		sinSetShopItem(lpItemInfo ,lpTransSellItem->ItemCounter, lpTransSellItem->ItemKind ); //¹«±â¸¸ ¼ÂÆÃ 

		delete lpItemInfo;
		break;

	}

	return TRUE;
}
int RecvCountFlag = 0; //¹«±â ¹æ¾î±¸¸¦ ¹ÞÀ»¶§´Â ÃÊ±âÈ­¸¦ ÇÑ¹ø¸¸ ÇÑ´Ù 

//»óÁ¡¿¡ ´ëÇÑ Á¤º¸¿Í ¾ÆÀÌÅÛÀ» ¹Þ´Â´Ù 
int sinSetShopItem(sITEMINFO *pItem,int ItemCount, int ItemKind) { return TRUE; }

/*----------------------------------------------------------------------------*
*			    ¸¶¿ì½º or ÀÎº¥Åä¸®·Î ¾ÆÀÌÅÛÀ» ¼ÂÆÃÇÑ´Ù 
*-----------------------------------------------------------------------------*/	
int sinSetQuestItem(sITEMINFO *sItemInfo )
{
	
	sinSetSpecialItemCode(sItemInfo); //½ºÆä¼È¾ÆÀÌÅÛÀ» ±¸ºÐÇÑ´Ù 

	int sArrowPosi=0 , i=0;
	sITEM sinTempItem;  //¾ÆÀÌÅÛ¿¡ °ü·ÃµÈ »çÇ×À» Àá½Ã ³Ö¾îµÎ´Â Temp

	//if(cInvenTory.SearchItemCode((sinQT1|sin01)))return FALSE; //1°³¾¿ ¹Û¿¡ °¡Áú¼ö¾ø´Ù
	//if(cInvenTory.SearchItemCode((sinQT1|sin02)))return FALSE;
	//if(cInvenTory.SearchItemCode((sinQT1|sin03)))return FALSE;

	if(sinChar->ChangeJob == 0 && !sinQuest_ChangeJob.CODE && !sinQuest_ChangeJob2.CODE){
		if((sItemInfo->CODE == (sinQT1|sin01)) || (sItemInfo->CODE == (sinQT1|sin02)) || (sItemInfo->CODE == (sinQT1|sin03)) ||
		    (sItemInfo->CODE == (sinQT1|sin04)) || (sItemInfo->CODE == (sinQT1|sin05)) || (sItemInfo->CODE == (sinQT1|sin06))){
			return FALSE;
			}
	}

	//////////°¢ Äù½ºÆ®¿¡ ¸ÂÁö¾Ê´Â ¾ÆÀÌÅÛÀº ¼ÂÆÃÇÒ¼ö¾ø´Ù

	if(sinQuest_ChangeJob.CODE == SIN_QUEST_CODE_CHANGEJOB){
		if(cInvenTory.SearchItemCode(sItemInfo->CODE))return FALSE; //°°Àº ÄÚµåÀÇ ¾ÆÀÌÅÛÀÌ ÀÖÀ¸¸é ¸®ÅÏÇÑ´Ù
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

	//Äù½ºÆ®¸¦ ³¡³»°í Àü¾÷¾ÆÀÌÅÛÀÌ µé¾î¿Ã°æ¿ì ¸®ÅÏÇÑ´Ù
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

	//Äù½ºÆ® ¹«±â¸¦ ¹ÞÀºÈÄ¿¡´Â ¹ìÇÁ¸¦ ¹ÞÀ»¼ö¾ø´Ù
	if(sItemInfo->CODE == (sinQT1|sin06) && sinQuest_ChangeJob3.State >=3){
		return FALSE;
	}

	//Äù½ºÆ®¸¦ ³¡³»°í Àü¾÷¾ÆÀÌÅÛÀÌ µé¾î¿Ã°æ¿ì ¸®ÅÏÇÑ´Ù
	if(sinChar->ChangeJob >= 2 && sItemInfo->CODE == (sinQT1|sin06)){
		return FALSE;
	}

	///////ÄÚµå¸¦ ¼ÂÆÃÇÑ ´Ù
	switch(sItemInfo->CODE & sinITEM_MASK2){
		case sinQT1:
			sItemInfo->ItemKindCode = ITEM_KIND_QUEST;

		break;
		case sinSP1:
			sItemInfo->ItemKindCode = ITEM_KIND_EVENT;
		break;
	}


	if(LoadItemImage(sItemInfo,&sinTempItem)){
		if(sinTempItem.sItemInfo.PotionCount <= 0 )     //Æ÷¼ÇÄ«¿îÆ®¸¦ º¸Á¤ÇÑ´Ù
			sinTempItem.sItemInfo.PotionCount = 1;

		if(!cInvenTory.AutoSetInvenItem(&sinTempItem,1)){ //Äù½ºÆ®¾ÆÀÌÅÛÀº ¹«°Ô¿¡ »ó°ü¾øÀÌ ¼ÂÆÃÇÒ¼öÀÖ´Ù
			if(ArrowState[0]==0)sArrowPosi = 2;
			else sArrowPosi = 1;
			sinButtonFlag = sArrowPosi;
			SelectInvenItemIndex = 0; //¿¡Å×¸£ ÄÚ¾î³²¹ßÀ» ¸·±âÀ§ÇØ ÃÊ±âÈ­
			cInvenTory.ChangeABItem(sArrowPosi); // 2º¸´Ù ÀÛÀ»¶§ ÀÎº¥ ¹Ú½º 
			if(!cInvenTory.AutoSetInvenItem(&sinTempItem,1)){
				//if(sinThrowItemToFeild(&sinTempItem)){          //¾ÆÀÌÅÛÀ» ¹ö¸°´Ù 
				sinTempItem.Flag = 0;
				return FALSE;
				
			}
		}
	}

	return TRUE;
}

/*----------------------------------------------------------------------------*
*			    ¸¶¿ì½º or ÀÎº¥Åä¸®·Î ¾ÆÀÌÅÛÀ» ¼ÂÆÃÇÑ´Ù 
*-----------------------------------------------------------------------------*/
//¹°¾à º¹»ç ¹æÁö ÇÃ·¢
int CheckPotionDelayFlag = 0;
int sinSetInvenItem(sITEMINFO *sItemInfo ) { return TRUE; }


//Äù½ºÆ® ÀÎº¥Åä¸®¿¡ ¼ÂÆÃµÉ¾ÆÀÌÅÛ
DWORD sinSpecialCODE[] = {(sinQT1|sin01),(sinQT1|sin02),(sinQT1|sin03),(sinQT1|sin04),(sinQT1|sin05),(sinQT1|sin06),
						(sinMA1|sin01),(sinMA2|sin01),(sinMA2|sin02),(sinQW1|sin01),(sinQW1|sin02),(sinQW1|sin03),
						(sinQW1|sin04),(sinQW1|sin05),(sinQT1|sin07),(sinQT1|sin08),
						(sinQT1|sin09),(sinQT1|sin10),(sinQT1|sin11),(sinQT1|sin12),(sinQT1|sin13),
						(sinQT1|sin14),(sinQT1|sin15),(sinQT1|sin16),(sinQW1|sin06),0};
//·Î½ºÆ® ¾ÆÀÏ·£µå ÀÍ½ºÆ®¸²À® ¼º±ÙÃß°¡ (sinQW1|sin06)
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
	cInvenTory.ChangeSpecialItem(2); //Äù½ºÆ®¾ÆÀÌÅÛÀ» Á¤¸®ÇÑ´Ù
	return TRUE;
}

 
//¾ÆÀÌÅÛÀÇ ÀÌ¹ÌÁö¸¦ ·ÎµåÇÑ´Ù 
int LoadItemImage(sITEMINFO *sItemInfo , sITEM *TempItem) { return TRUE; }

/*----------------------------------------------------------------------------*
*				         Å°¹öÆ°  ¹× ¸¶¿ì½º ÇÔ¼ö 
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
*					Å°ÀÔ·Â°ú ¸¶¿ì½º ÀÔ·ÂÀ» ÇÑ¹øÀ¸·Î Á¦ÇÑÇÑ´Ù 
*-----------------------------------------------------------------------------*/	
int sinGetMouseButton(int num) { return TRUE; }
//-------------------------------------------------------------------------------
void sinMouseMain()
{
}
/*----------------------------------------------------------------------------*
*					Å°º¸µå ÀÔ·ÂÀ» ÇÑ¹ø¸¸ Ã¼Å©ÇÏ°ÔÇÑ´Ù
*-----------------------------------------------------------------------------*/	
int sinGetKeyClick(int num) { return TRUE; }
//-----------------------------------------------------------------------------
void sinKeyClickMain() {}


class sinFlag{
public:
	int	OpenFlag;
};

int FirstMove[MAX_SIN_KIND_INTER] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; // ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ãß°¡·Î °ªÀ» ÇÏ³ª´õ Ãß°¡

void ShowInterFace() {}

//ÆùÆ® »ý¼º 
int sinCreatFont() { return TRUE; }

//ÅØ½ºÆ®°¡ ³õÀ» À§Ä¡¸¦ º¸Á¤ÇÑ´Ù
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
*					¸ð¼ÇÀÌ ³¡³­´ÙÀ½¿¡ Æ÷¼ÇÀ» »ç¿ëÇÑ´Ù 
*-----------------------------------------------------------------------------*/	
#define SIN_POTION_LIFE			1
#define SIN_POTION_MANA			2
#define SIN_POTION_STAMINA		3
#define SIN_POTION_SONGPYEUN	4

int sinUsePotion() //¸ð¼ÇÀÌ ³¡³­´ÙÀ½¿¡ Æ÷¼ÇÀ» »ç¿ëÇÑ´Ù 
{
	
	CheckCharForm();//ÀÎÁõ 
	
	int PotionKind = 0;
	int ResultPotion = 0;
	int TempRandPotion = 0;

	if(pUsePotion == 0) return FALSE;
	if(!pUsePotion->Flag)return FALSE;
	if(MouseItem.Flag){//¸¶¿ì½º¿¡ Áý°íÀÖ´Â ¾ÆÀÌÅÛ°ú »ç¿ëµÉ ¾ÆÀÌÅÛÀÌ °°À¸¸é ¸®ÅÏÇÑ´Ù (¿Ö ±×·±°ÅÁã -_-; ÇèÇè ±â¾ïÀÌ¾È³­´Ù ¸Õ°¡ÀÌÀ¯°¡ÀÖÀ»Å×´Ï ³ÀµÐ´Ù)
		if(MouseItem.sItemInfo.ItemHeader.Head == pUsePotion->sItemInfo.ItemHeader.Head)
			return FALSE;

	}

	if((pUsePotion->CODE & sinITEM_MASK2) ==sinPL1 ){ //¶óÀÌÇÁÀÏ°æ¿ì 
		TempRandPotion = pUsePotion->sItemInfo.Life[1] -  pUsePotion->sItemInfo.Life[0];
		ResultPotion = pUsePotion->sItemInfo.Life[0]+(rand()%TempRandPotion);
		sinSetLife((sinGetLife()+ResultPotion));	//¶óÀÌÇÁ ¼ÂÆÃ 
		PotionKind = SIN_POTION_LIFE;
	}
	if((pUsePotion->CODE & sinITEM_MASK2) == sinPM1){ //¸¶³ªÀÏ°æ¿ì 
		TempRandPotion = pUsePotion->sItemInfo.Mana[1] -  pUsePotion->sItemInfo.Mana[0];
		ResultPotion = pUsePotion->sItemInfo.Mana[0]+(rand()%TempRandPotion);
		sinSetMana((sinGetMana()+ResultPotion));	//¶óÀÌÇÁ ¼ÂÆÃ 
		PotionKind = SIN_POTION_MANA;
	}
	if((pUsePotion->CODE & sinITEM_MASK2) == sinPS1 ){ //½ºÅ×¹Ì³ª Æ÷¼ÇÀÏ°æ¿ì 
		TempRandPotion = pUsePotion->sItemInfo.Stamina[1] -  pUsePotion->sItemInfo.Stamina[0];
		ResultPotion = pUsePotion->sItemInfo.Stamina[0]+(rand()%TempRandPotion);
		sinSetStamina((sinGetStamina()+ResultPotion));	//¶óÀÌÇÁ ¼ÂÆÃ 
		PotionKind = SIN_POTION_STAMINA;
	}
	if((pUsePotion->CODE & sinITEM_MASK2) == sinSP1)
	{
		if( (pUsePotion->CODE & sinITEM_MASK3) == sin01 || (pUsePotion->CODE & sinITEM_MASK3) == sin02 ||
			(pUsePotion->CODE & sinITEM_MASK3) == sin03 || (pUsePotion->CODE & sinITEM_MASK3) == sin15 || // ¹ÚÀç¿ø - ¼ö¹Ú ¾ÆÀÌÅÛ Ãß°¡
			(pUsePotion->CODE & sinITEM_MASK3) == sin35 ||  // Àåº° - ¹ß·»Å¸ÀÎ ÃÊÄÝ¸´ ¾ÆÀÌÅÛ Ãß°¡
			 (pUsePotion->CODE & sinITEM_MASK3) == sin36 || (pUsePotion->CODE & sinITEM_MASK3) == sin42 ) // Àåº° - Äµµðµ¥ÀÌÁî // Àåº° - ¼ö¹Ú
		{
			pUsePotion->sItemInfo.PotionCount = 0;			//¼ÛÆí Æ÷¼Ç Ä«¿îÆ® 0
			if(cInvenTory.EatSongPyeun(pUsePotion)){
				PotionKind = SIN_POTION_SONGPYEUN;
			}
			else
				PotionKind = 5;
		}
		// ¼±¹°»óÀÚ
		if( (pUsePotion->CODE & sinITEM_MASK3) == sin05 || (pUsePotion->CODE & sinITEM_MASK3) == sin06 || (pUsePotion->CODE & sinITEM_MASK3) == sin07 ||
			(pUsePotion->CODE & sinITEM_MASK3) == sin08 || (pUsePotion->CODE & sinITEM_MASK3) == sin09 || (pUsePotion->CODE & sinITEM_MASK3) == sin10 )
		{
			PotionKind = 6;		// pluto ¼±¹°»óÀÚ
		}

		// ¹ÚÀç¿ø - Ä¸½¶ ¾ÆÀÌÅÛ(È£¶ûÀÌ Ä¸½¶ »ç¿ë)
		if( (pUsePotion->CODE & sinITEM_MASK3) == sin34 )
		{
			PotionKind = 7;		// ¹ÚÀç¿ø - È£¶ûÀÌ Ä¸½¶ ¾ÆÀÌÅÛÀ» »ç¿ëÇÒ¶§ ¾ßÈ£ ¸ð¼ÇÀ» ÇÑ´Ù. 
		}

	}
	if(PotionKind){
		if(pUsePotion->sItemInfo.PotionCount >=2){ //Æ÷¼ÇÀÇ ¼ö¸¦ ÁÙÀÎ´Ù 
			pUsePotion->sItemInfo.PotionCount--;
			/*
			if(( pUsePotion->sItemInfo.CODE & sinITEM_MASK3 ) == sin03 ||
				( pUsePotion->sItemInfo.CODE & sinITEM_MASK3 ) == sin04 ){
				sinPlaySound(SIN_SOUND_EAT_POTION2); //¹°¾à ¸Ô´Â ¼Ò¸® 
			}
			else
			*/

		}
		else{
			pUsePotion->Flag =0;
			sInven[pUsePotion->ItemPosition-1].ItemIndex = 0; //»ç¿ëµÇÁö ¾Ê´Â´Ù 
			if(PotionKind != 5){
			/*			
				if(( pUsePotion->sItemInfo.CODE & sinITEM_MASK3 ) == sin03 ||
					( pUsePotion->sItemInfo.CODE & sinITEM_MASK3 ) == sin04 ){
					sinPlaySound(SIN_SOUND_EAT_POTION2); //¹°¾à ¸Ô´Â ¼Ò¸® 
				}
				else
			*/

			}

		} 
	
	pUsePotion = 0; //Æ÷ÀÎÅÍ ÃÊ±âÈ­ 		
	ReformCharForm();//ÀçÀÎÁõ 
	cInvenTory.CheckWeight(); //¹«°Ô¸¦ Ã¼Å©ÇÑ´Ù 
	cInvenTory.ReFormPotionNum();	//Æ÷¼Ç °¹¼ö¸¦ Ã¼Å©ÇÑ´Ù 
	cInvenTory.ReFormInvenItem();   //ÀÎº¥Åä¸® ¾ÆÀÌÅÛ ÀÎÁõ
	return PotionKind;
	}

	return FALSE;	

}

//½Å¹Ù¶÷ Àç»ý 
void sinRegen()
{

	InCreaSTM  = 0;
	InCreaMANA = 0;
	InCreaLIFE = 0;

	float	fLevel=0;
	float	fStrength=0;
	float	fHealth=0;
	float	fSpirit=0;

	//½ºÅ×¹Ì³ª Àç»ý 
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
			default: //È¤½Ã³ª ÇØ¼­ ÇÏ³ª ³Ö¾îµÐ´Ù 
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
		//¶óÀÌÇÁ Àç»ý  
		InCreaLIFE = (float)(((fLevel+(fStrength/2)+fHealth)/180 + sinChar->Life_Regen)/1.5);
		//¸¶³ª Àç»ý 
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

//½ºÅ×¹Ì³ª¸¦ ¼ÂÆÃÇÑ´Ù 
void sinSetRegen()
{
	
	CheckCharForm();//ÀÎÁõ 

	//½ºÅ×¹Ì³ª °¨¼Ò 
	if(DeCreaSTM){ 
		fTempSTM_Decre += DeCreaSTM/(70/4);
		if(fTempSTM_Decre >=1){
			sinSetStamina(sinGetStamina()-(short)fTempSTM_Decre);
			fTempSTM_Decre -=1;
		}

	}
	//½ºÅ×¹Ì³ª Áõ°¡ 
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

	//¶óÀÌÇÁ Áõ°¡ 
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
	
	//¸¶³ª Áõ°¡ 
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
	ReformCharForm();//ÀçÀÎÁõ 

}
/*----------------------------------------------------------------------------*
*				 (°¢Á¾ °ø½ÄÀ» Àû¿ëÈÄ °ªÀ» ¸®ÅÏÇÑ´Ù )
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
int AC_R = 0;    //°è»êÀ¸·Î ³ª¿Â °ª 
int RealAC=0;    //Å×ÀÌºí¿¡¼­ ³ª¿Â ½ÇÁ¦ ¼öÄ¡ 
int Result=0;
float fDesLV = 0;
float fMyLV  = 0;
float fWeifht[2] = {0,0};


//¸íÁß·üÀ» ¸®ÅÏÇÑ´Ù (Á¤È®ÇÏ´Ù) (¹«°ÔÀÇ ¿äÀÎÀÌÀÖÀ¸´Ï ÀÇ½ÉÇÏÁö¸¶¼¼¿ä)
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

//¸ó½ºÅÍ ¸íÁß·ü  
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

//¸ó½ºÅÍ VS ¸ó½ºÅÍ ¸íÁß·ü
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

//½ÇÁ¦ Å©¸®Æ¼ÄÃ 
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
//Èí¼öÀ²À» ¸®ÅÏÇÑ´Ù 
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
//Å×½ºÆ®½Ã »ç¿ëµÉ ¸Þ¼¼Áö¸¦ º¸¿©ÁØ´Ù 
int CheatHelpOpenFlag = 0;
void sinTestDrawText() {}
/*
//Tempscron 4°³ Á÷¾÷º° ¾ó±¼...
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


//Æ®·¹ÀÌµå ¿ä±¸°¡ µé¾î¿À¸é °ªÀ» ¼ÂÆÃÇÑ´Ù 
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

//½ºÅ³À» ¹è¿ì°í Àü¾÷À» ÇÑ´Ù 
int sinSkillMaster(int ChangeJob) { return TRUE; }

//½ºÅ³ ¹è¿ì±â¸¦ ¸¶Ä£´Ù 
int sinSkillMasterClose()
{
	/*
	if(ChangeJobButtonclick){
		cInterFace.CheckAllBox(SIN_SKILL); //½ºÅ³Ã¢À» ¶ç¿öÁØ´Ù 

	}
	else{
	*/
		SkillMasterFlag = 0;	//½ºÅ³À» ÇÒ´çÇÒ¼öÀÖ´Â °ªÀ» ÃÊ±âÈ­ÇÑ´Ù 
		cSkill.OpenFlag = 0;	//½ºÅ³ Ã¢À» ´Ý¾ÆÁØ´Ù 
dwCurrentTime = dwPlayTime+5000;
	//}
	return TRUE;
}


static int LastPartyMode = -1;
int haSiegeBoardTempFlag = 0; //°ø¼ºÀü º¸µåÃ¢À» ¼û±â±â À§ÇÑ  
//ÆÄÆ¼ Ã¢À» º¸¿©ÁØ´Ù 
int ShowParty() { return TRUE; }

//Äù½ºÆ® Ã¢À» º¸¿©ÁØ´Ù 
int ShowQuest() { return TRUE; }

///////////////////////////////// ¶óÀÌÇÁ , ¸¶³ª , ½ºÅ×¹Ì³ª °ü·Ã ÄÚµåÈ­ 

//¶óÀÌÇÁ¸¦ ÀÐ¾î¿Â´Ù 
short sinGetLife()
{

		return (sinChar->Life[0])^CodeXorLife;
}

//¸¶³ª¸¦ ¾ò¾î¿Â´Ù 
short sinGetMana()
{

	return sinChar->Mana[0];
}

//½ºÅ×¹Ì³ª¸¦ ¾ò¾î¿Â´Ù 
short sinGetStamina()
{

	return sinChar->Stamina[0];
}

//¶óÀÌÇÁ¸¦ ¼ÂÆÃÇÑ´Ù				//kyle xtrapHeap
void sinSetLife(short Life)
{
#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func11_Protect( &(sinChar->Life), sizeof(sinChar->Life) );	//º¸È£¿µ¿ª ¹«°á¼º Ã¼Å©
#endif

	//CheckCharForm(); //ÀÎÁõ 
	sinChar->Life[0] = Life;
	if(sinChar->Life[0] < 0 ) sinChar->Life[0] = 0;
	if(sinChar->Life[0] >= sinChar->Life[1] )sinChar->Life[0] = sinChar->Life[1];
	sinChar->Life[0] ^= CodeXorLife;
	ReformCharForm(); //ÀçÀÎÁõ 

#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func12_Protect( &(sinChar->Life), sizeof(sinChar->Life) );	//º¸È£¿µ¿ª º¸È£
	XTrap_CE1_Func13_Free( &(sinChar->Life), sizeof(sinChar->Life) );		//º¸È£¿µ¿ª ÇØÁ¦
#endif
	
}

//¸¶³ª¸¦ ¼ÂÆÃÇÑ´Ù 
void sinSetMana(short Mana)
{
#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func11_Protect( &(sinChar->Mana), sizeof(sinChar->Mana) );	//º¸È£¿µ¿ª ¹«°á¼º Ã¼Å©
#endif

	//CheckCharForm(); //ÀÎÁõ 
	sinChar->Mana[0] = Mana;
	if(sinChar->Mana[0] < 0 ) sinChar->Mana[0] = 0;
	if(sinChar->Mana[0] >= sinChar->Mana[1] )sinChar->Mana[0] = sinChar->Mana[1];
	ReformCharForm(); //ÀçÀÎÁõ 

#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func12_Protect( &(sinChar->Mana), sizeof(sinChar->Mana) );	//º¸È£¿µ¿ª º¸È£
	XTrap_CE1_Func13_Free( &(sinChar->Mana), sizeof(sinChar->Mana) );		//º¸È£¿µ¿ª ÇØÁ¦
#endif
}

//½ºÅ×¹Ì³ª¸¦ ¼ÂÆÃÇÑ´Ù 
void sinSetStamina(short Stamina)
{
#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func11_Protect( &(sinChar->Stamina), sizeof(sinChar->Stamina) );	//º¸È£¿µ¿ª ¹«°á¼º Ã¼Å©
#endif

	//CheckCharForm(); //ÀÎÁõ 
	sinChar->Stamina[0] = Stamina;
	if(sinChar->Stamina[0] < 0 ) sinChar->Stamina[0] = 0;
	if(sinChar->Stamina[0] >= sinChar->Stamina[1] )sinChar->Stamina[0] = sinChar->Stamina[1];
	ReformCharForm(); //ÀçÀÎÁõ 

#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func12_Protect( &(sinChar->Stamina), sizeof(sinChar->Stamina) );	//º¸È£¿µ¿ª º¸È£
	XTrap_CE1_Func13_Free( &(sinChar->Stamina), sizeof(sinChar->Stamina) );		//º¸È£¿µ¿ª ÇØÁ¦
#endif

}

//	short   ItemAgingNum[2];	//0Àº ¿¡ÀÌÂ¡+¸î 1Àº ¿¡ÀÌÂ¡ÀÌ µÇ°íÀÖ³ª ¾Æ´Ñ°¡?
//	short   ItemAgingCount[2];	//0¾ÆÀÌÅÛ ¼÷·Ã Ä«¿îÆ® 1¼÷·ÃÄ¡ ÃÖ´ë 

//////¿¡ÀÌÂ¡ ·¹º§À» Ã¼Å©ÇÑÈÄ ¿Ã·ÁÁØ´Ù(¿¡ÀÌÂ¡¼öÄ¡)
/*
char *AgingMsgDamageMax = "ÃÖ´ë°ø°Ý·Â";
char *AgingMsgDamageMin = "ÃÖ¼Ò°ø°Ý·Â";
char *AgingMsgAttack_Rate = "¸íÁß·Â";
char *AgingMsgDur = "³»±¸·Â";
char *AgingMsgCritical = "Å©¸®Æ¼ÄÃ";
char *AgingMsgShooting_Range = "»çÁ¤°Å¸®";
char *AgingMsgMana = "±â·Â";
char *AgingMsgBlock = "ºí·°À²";
char *AgingMsgAbsorb = "Èí¼öÀ²";
char *AgingMsgDefense = "¹æ¾îÀ²";
*/
//³»±¸·Â
int sinSetDurabilityAging(sITEMINFO *pItem)
{
	int Temp = 0;
	Temp = pItem->Durability[1]/100;
	Temp += 1;
	pItem->Durability[1] -= Temp;
	if(pItem->Durability[1] < 0 ) pItem->Durability[1] = 0;
	if(pItem->Durability[1] < pItem->Durability[0] ) pItem->Durability[0] = pItem->Durability[1]; //ÇöÁ¦ ³»±¸·Â º¸Á¤ 

	return TRUE;
}
//°ø°Ý·Â
int sinSetDamageAging(sITEMINFO *pItem)
{
	pItem->Damage[0]++;
	pItem->Damage[1]++;

	if(pItem->ItemAgingNum[0] >= 9){ //10Â÷ºÎÅÍ´Â µ¥¹ÌÁö +2
		pItem->Damage[0]++;
		pItem->Damage[1]++;
	}

	// ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¼³Á¤ º¯°æ(¹«±â·ù ·¹º§º° °ø°Ý·Â Ãß°¡)
	if(pItem->ItemAgingNum[0] >= 19){ //20Â÷ºÎÅÍ´Â µ¥¹ÌÁö +3
		pItem->Damage[0]++;
		pItem->Damage[1]++;
	}

	return TRUE;
}
//¹æ¾î·Â
int sinSetDefenseAging(sITEMINFO *pItem , int Percent)
{
	float Temp = 0;
	Temp = (float)pItem->Defence/(100.0f / (float)Percent);
	pItem->Defence += (int)Temp;
	return TRUE;
}

//¸íÁß·Â
int sinSetAttackRateAging(sITEMINFO *pItem , int AddNum)
{
	pItem->Attack_Rating += AddNum;
	return TRUE;
}
//Èí¼öÀ²
int sinSetAbsorbAging(sITEMINFO *pItem , float Percent)
{
	pItem->fAbsorb += Percent;

	if(pItem->ItemAgingNum[0] >= 9){ //10Â÷ºÎÅÍ´Â 2¹è
		pItem->fAbsorb += Percent;
	}

	// ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¼³Á¤ º¯°æ(¹«±â·ù ·¹º§º° °ø°Ý·Â Ãß°¡)
	if(pItem->ItemAgingNum[0] >= 19){ //20Â÷ºÎÅÍ´Â 3¹è
		pItem->fAbsorb += Percent;
	}
	return TRUE;
}

//Å©¸®Æ¼ÄÃ
int sinSetCriticalAging(sITEMINFO *pItem)
{
	if(pItem->ItemAgingNum[0] && (pItem->ItemAgingNum[0]%2) == 1){
		pItem->Critical_Hit += 1;

	}
	return TRUE;
}

//ºí·°À²
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
	//¿¡ÀÌÂ¡ ÃÊ±âÈ­
	switch(pItem->CODE & sinITEM_MASK2){
		case sinWA1: //µµ³¢ 
			//°ø°Ý·Â 
			sinSetDamageAging(pItem);
			//¸íÁß·Â
			sinSetAttackRateAging(pItem , 10);
			//³»±¸·Â
			sinSetDurabilityAging(pItem); 

		break;
		case sinWC1: //Å¬·¯
			//°ø°Ý·Â 
			sinSetDamageAging(pItem);
			//¸íÁß·Â
			sinSetAttackRateAging(pItem , 5);
			//Å©¸®Æ¼ÄÃ  
			sinSetCriticalAging(pItem);

		break;

		case sinWH1: //ÇØ¸Ó 
			//°ø°Ý·Â 
			sinSetDamageAging(pItem);

			//¸íÁß·Â
			sinSetAttackRateAging(pItem , 10);
			//³»±¸·Â
			sinSetDurabilityAging(pItem); 

		break;
		case sinWM1: //¸ÞÁöÄÃ ½ºÅ×ÇÁ 
			//°ø°Ý·Â 
			sinSetDamageAging(pItem);

			//¸íÁß·Â
			sinSetAttackRateAging(pItem , 10);

			//±â·Â  
			pItem->fIncrease_Mana += 10;

		break;
		case sinWP1: //Ã¢ 
			//°ø°Ý·Â 
			sinSetDamageAging(pItem);

			//¸íÁß·Â
			sinSetAttackRateAging(pItem , 5);

			//Å©¸®Æ¼ÄÃ  
			sinSetCriticalAging(pItem);

		break;
		case sinWS1: //È° 
			//°ø°Ý·Â 
			sinSetDamageAging(pItem);

			//Å©¸®Æ¼ÄÃ  
			sinSetCriticalAging(pItem);

			//³»±¸·Â
			sinSetDurabilityAging(pItem); 
		break;

		case sinWS2: //Ä®  
			//°ø°Ý·Â 
			sinSetDamageAging(pItem);

			//¸íÁß·Â
			sinSetAttackRateAging(pItem , 5);
			
			//Å©¸®Æ¼ÄÃ  
			sinSetCriticalAging(pItem);

		break;

		case sinWT1: //ÀÚº§¸° 
			//°ø°Ý·Â 
			sinSetDamageAging(pItem);

			//Å©¸®Æ¼ÄÃ  
			sinSetCriticalAging(pItem);

			//³»±¸·Â
			//sinSetDurabilityAging(pItem); 
		break;
		case sinWD1:
			sinSetDamageAging(pItem);
			sinSetAttackRateAging(pItem, 5);
			sinSetCriticalAging(pItem);
			break;
		case sinDS1: //¹æÆÐ 
			//ºí·°À² 
			sinSetBlockRateAging(pItem);
			//Èí¼öÀ²
			sinSetAbsorbAging(pItem , 0.2f);
			//³»±¸·Â
			sinSetDurabilityAging(pItem); 
		break;

		case sinOM1: //¸ÅÁöÄÃ °¨ÀÚ 
			//¹æ¾î·Â 
			sinSetDefenseAging(pItem,10);

			//Èí¼öÀ²
			sinSetAbsorbAging(pItem , 0.5f);

			//³»±¸·Â
			sinSetDurabilityAging(pItem); 

		break;
		case sinDA1: case sinDA2://°©¿Ê 
			//¹æ¾î·Â 
			sinSetDefenseAging(pItem,5);

			//Èí¼öÀ²
			sinSetAbsorbAging(pItem , 0.5f);

			//³»±¸·Â
			sinSetDurabilityAging(pItem); 

		break; 
		case sinDB1: // ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ Ãß°¡(ºÎÃ÷)
			//¹æ¾î·Â 
			sinSetDefenseAging(pItem,10);
			//Èí¼öÀ²
			sinSetAbsorbAging(pItem , 0.5f);
			//³»±¸·Â
			sinSetDurabilityAging(pItem); 
			break;
		case sinDG1: // ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ Ãß°¡(Àå°©)
			//¹æ¾î·Â 
			sinSetDefenseAging(pItem,10);
			//Èí¼öÀ²
			sinSetAbsorbAging(pItem , 0.5f);
			//³»±¸·Â
			sinSetDurabilityAging(pItem); 
			break;
		case sinOA2: // ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ Ãß°¡(¾Ï¸´)
			//¹æ¾î·Â 
			sinSetDefenseAging(pItem,10);
			//¸íÁß·Â
			sinSetAttackRateAging(pItem , 5);
			//³»±¸·Â
			sinSetDurabilityAging(pItem); 
			break;
		}
		
		

		pItem->ItemAgingNum[0]++;	//¾ÆÀÌÅÛÀÇ ·¹º§À» ¿Ã·ÁÁØ´Ù 
			
		pItem->ItemAgingNum[1] = 0; //ÃÊ±âÈ­ 
		pItem->ItemAgingCount[0] = 0;
		pItem->ItemAgingCount[1] = 0;

		
		if( pItem->Level == 100 || pItem->Level == 102 || pItem->Level == 105 ||	// pluto 102·¹º§ ¾ÆÅÛ ·¹º§ °íÁ¤ ÇÒ·Á°í // Àåº° - 105·¾ ¾ÆÀÌÅÛ °íÁ¤
			cAging.AginStoneKind == 3 || cAging.AginStoneKind == 4 || // ¹ÚÀç¿ø - ¿¤´õ ÄÚÆÛ ¿À¾î, ½´ÆÛ ¿¡ÀÌÂ¡ ½ºÅæ »ç¿ë½Ã¿¡´Â ¿¡ÀÌÂ¡ Â÷¼ö°¡ »ó½ÂÇØµµ ¾ÆÀÌÅÛ ·¹º§ÀÌ ¿Ã¶ó°¡Áö ¾Ê´Â´Ù.
			cAging.AginStoneKind == 5  ) // Àåº° - ½´ÆÛ ¿¡ÀÌÂ¡ ½ºÅæ 1.5
		{
			pItem->Level += 0;
		}
		else
		{
		}
				
	ReformItem(pItem);  //¾ÆÀÌÅÛ ÀÎÁõ ¹Þ±â 
	return TRUE;
}



int sinSetAgingItemIncreStateRestaure(sITEMINFO* pItem)
{
	float TempDefense[2] = { 0,0 };
	//¿¡ÀÌÂ¡ ÃÊ±âÈ­
	switch (pItem->CODE & sinITEM_MASK2) {
	case sinWA1: //µµ³¢ 
		//°ø°Ý·Â 
		sinSetDamageAging(pItem);
		//¸íÁß·Â
		sinSetAttackRateAging(pItem, 10);
		//³»±¸·Â
		sinSetDurabilityAging(pItem);

		break;
	case sinWC1: //Å¬·¯
		//°ø°Ý·Â 
		sinSetDamageAging(pItem);
		//¸íÁß·Â
		sinSetAttackRateAging(pItem, 5);
		//Å©¸®Æ¼ÄÃ  
		sinSetCriticalAging(pItem);

		break;

	case sinWH1: //ÇØ¸Ó 
		//°ø°Ý·Â 
		sinSetDamageAging(pItem);

		//¸íÁß·Â
		sinSetAttackRateAging(pItem, 10);
		//³»±¸·Â
		sinSetDurabilityAging(pItem);

		break;
	case sinWM1: //¸ÞÁöÄÃ ½ºÅ×ÇÁ 
		//°ø°Ý·Â 
		sinSetDamageAging(pItem);

		//¸íÁß·Â
		sinSetAttackRateAging(pItem, 10);

		//±â·Â  
		pItem->fIncrease_Mana += 10;

		break;
	case sinWP1: //Ã¢ 
		//°ø°Ý·Â 
		sinSetDamageAging(pItem);

		//¸íÁß·Â
		sinSetAttackRateAging(pItem, 5);

		//Å©¸®Æ¼ÄÃ  
		sinSetCriticalAging(pItem);

		break;
	case sinWS1: //È° 
		//°ø°Ý·Â 
		sinSetDamageAging(pItem);

		//Å©¸®Æ¼ÄÃ  
		sinSetCriticalAging(pItem);

		//³»±¸·Â
		sinSetDurabilityAging(pItem);
		break;

	case sinWS2: //Ä®  
		//°ø°Ý·Â 
		sinSetDamageAging(pItem);

		//¸íÁß·Â
		sinSetAttackRateAging(pItem, 5);

		//Å©¸®Æ¼ÄÃ  
		sinSetCriticalAging(pItem);

		break;

	case sinWT1: //ÀÚº§¸° 
		//°ø°Ý·Â 
		sinSetDamageAging(pItem);

		//Å©¸®Æ¼ÄÃ  
		sinSetCriticalAging(pItem);

		//³»±¸·Â
		//sinSetDurabilityAging(pItem); 
		break;

	case sinWD1:
		sinDownDamageAging(pItem);
		sinDownAttackRateAging(pItem, 5);
		sinDownCriticalAging(pItem);
		break;

	case sinDS1: //¹æÆÐ 
		//ºí·°À² 
		sinSetBlockRateAging(pItem);
		//Èí¼öÀ²
		sinSetAbsorbAging(pItem, 0.2f);
		//³»±¸·Â
		sinSetDurabilityAging(pItem);
		break;

	case sinOM1: //¸ÅÁöÄÃ °¨ÀÚ 
		//¹æ¾î·Â 
		sinSetDefenseAging(pItem, 10);

		//Èí¼öÀ²
		sinSetAbsorbAging(pItem, 0.5f);

		//³»±¸·Â
		sinSetDurabilityAging(pItem);

		break;
	case sinDA1: case sinDA2://°©¿Ê 
		//¹æ¾î·Â 
		sinSetDefenseAging(pItem, 5);

		//Èí¼öÀ²
		sinSetAbsorbAging(pItem, 0.5f);

		//³»±¸·Â
		sinSetDurabilityAging(pItem);

		break;
	case sinDB1: // ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ Ãß°¡(ºÎÃ÷)
		//¹æ¾î·Â 
		sinSetDefenseAging(pItem, 10);
		//Èí¼öÀ²
		sinSetAbsorbAging(pItem, 0.5f);
		//³»±¸·Â
		sinSetDurabilityAging(pItem);
		break;
	case sinDG1: // ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ Ãß°¡(Àå°©)
		//¹æ¾î·Â 
		sinSetDefenseAging(pItem, 10);
		//Èí¼öÀ²
		sinSetAbsorbAging(pItem, 0.5f);
		//³»±¸·Â
		sinSetDurabilityAging(pItem);
		break;
	case sinOA2: // ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ Ãß°¡(¾Ï¸´)
		//¹æ¾î·Â 
		sinSetDefenseAging(pItem, 10);
		//¸íÁß·Â
		sinSetAttackRateAging(pItem, 5);
		//³»±¸·Â
		sinSetDurabilityAging(pItem);
		break;
	}



	pItem->ItemAgingNum[0]++;	//¾ÆÀÌÅÛÀÇ ·¹º§À» ¿Ã·ÁÁØ´Ù 

	pItem->ItemAgingNum[1] = 0; //ÃÊ±âÈ­ 
	pItem->ItemAgingCount[0] = 0;
	pItem->ItemAgingCount[1] = 0;


	if (pItem->Level == 100 || pItem->Level == 102 || pItem->Level == 105 ||	// pluto 102·¹º§ ¾ÆÅÛ ·¹º§ °íÁ¤ ÇÒ·Á°í // Àåº° - 105·¾ ¾ÆÀÌÅÛ °íÁ¤
		cAging.AginStoneKind == 3 || cAging.AginStoneKind == 4 || // ¹ÚÀç¿ø - ¿¤´õ ÄÚÆÛ ¿À¾î, ½´ÆÛ ¿¡ÀÌÂ¡ ½ºÅæ »ç¿ë½Ã¿¡´Â ¿¡ÀÌÂ¡ Â÷¼ö°¡ »ó½ÂÇØµµ ¾ÆÀÌÅÛ ·¹º§ÀÌ ¿Ã¶ó°¡Áö ¾Ê´Â´Ù.
		cAging.AginStoneKind == 5) // Àåº° - ½´ÆÛ ¿¡ÀÌÂ¡ ½ºÅæ 1.5
	{
		pItem->Level += 0;
	}
	else
	{
	}

	ReformItemRestaure(pItem);  //¾ÆÀÌÅÛ ÀÎÁõ ¹Þ±â 
	return TRUE;
}




//³»±¸·ÂÀ» ³»¸°´Ù
int sinDownDurabilityAging(sITEMINFO *pItem)
{
	int Temp = 0;
	Temp = pItem->Durability[1]/100;
	Temp += 1;
	pItem->Durability[1] += Temp*DownNum;
	if(pItem->Durability[1] < 0 ) pItem->Durability[1] = 0;
	if(pItem->Durability[1] < pItem->Durability[0] ) pItem->Durability[0] = pItem->Durability[1]; //ÇöÁ¦ ³»±¸·Â º¸Á¤ 

	return TRUE;
}	
																																																																																									
// ¿¡ÀÌÂ¡ °ø°Ý·Â
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
//¹æ¾î·Â
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

//¸íÁß·Â
int sinDownAttackRateAging(sITEMINFO *pItem , int AddNum)
{

	pItem->Attack_Rating -= AddNum*DownNum;
	return TRUE;

}
//Èí¼öÀ²
int sinDownAbsorbAging(sITEMINFO *pItem , float Percent , int Level)
{

	pItem->fAbsorb -= Percent*(float)DownNum; 

	int Temp = Level-9; //·¹º§ 10ÀÌ»óÀº Áõ°¡ÇÑ °ª¸¸Å­À» ´õ»©ÁØ´Ù
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

//Å©¸®Æ¼ÄÃ
int sinDownCriticalAging(sITEMINFO *pItem)
{
	pItem->Critical_Hit -=1; //ÀÏ´Ü ÇÏ³ª³»·ÁÁÖ°í
	if(DownNum > 2){
		if(pItem->ItemAgingNum[0] && (pItem->ItemAgingNum[0]%2) == 1){
			pItem->Critical_Hit -= 1;
		}
	}
	return TRUE;

}

//ºí·°À²
int sinDownBlockRateAging(sITEMINFO *pItem)
{
	pItem->fBlock_Rating -=1; //ÀÏ´Ü ÇÏ³ª³»·ÁÁÖ°í
	if(DownNum > 2){
		if(pItem->ItemAgingNum[0] && (pItem->ItemAgingNum[0]%2) == 1){
			pItem->fBlock_Rating -= 1;

		}
	}
	return TRUE;

}

//¿¡ÀÌÂ¡ ·¹º§ÃÊ±âÈ­
int sinAgingItemInit(sITEMINFO *pItem , int Down)
{

	float TempDefense[2] = {0,0}; 
	DownNum = Down + 1;	
	int AgingLevelTemp = 0;
	AgingLevelTemp = pItem->ItemAgingNum[0];

	pItem->ItemAgingNum[0] -= DownNum;	//¸ÕÀú ·¹º§À» ³»·ÁÁØ´Ù (Å©¸®Æ¼ÄÃ °è»ê¹®Á¦)
/*
	if((pItem->CODE & sinITEM_MASK2) == sinMA1){
	}
	else{
	
*/	
	//¿¡ÀÌÂ¡ ·¹º§´Ù¿î --
	switch(pItem->CODE & sinITEM_MASK2){
		case sinWA1: //µµ³¢ 
			//°ø°Ý·Â 
			sinDownDamageAging(pItem,AgingLevelTemp);
			//¸íÁß·Â
			sinDownAttackRateAging(pItem , 10);
			//³»±¸·Â
			sinDownDurabilityAging(pItem); 

		break;
		case sinWC1: //Å¬·¯
			//°ø°Ý·Â 
			sinDownDamageAging(pItem,AgingLevelTemp);
			//¸íÁß·Â
			sinDownAttackRateAging(pItem , 5);
			//Å©¸®Æ¼ÄÃ  
			sinDownCriticalAging(pItem);

		break;

		case sinWH1: //ÇØ¸Ó 
			//°ø°Ý·Â 
			sinDownDamageAging(pItem,AgingLevelTemp);

			//¸íÁß·Â
			sinDownAttackRateAging(pItem , 10);
			//³»±¸·Â
			sinDownDurabilityAging(pItem); 

		break;
		case sinWM1: //¸ÞÁöÄÃ ½ºÅ×ÇÁ 
			//°ø°Ý·Â 
			sinDownDamageAging(pItem,AgingLevelTemp);

			//¸íÁß·Â
			sinDownAttackRateAging(pItem , 10);

			//±â·Â  
			pItem->fIncrease_Mana -= 10*DownNum;

		break;
		case sinWP1: //Ã¢ 
			//°ø°Ý·Â 
			sinDownDamageAging(pItem,AgingLevelTemp);

			//¸íÁß·Â
			sinDownAttackRateAging(pItem , 5);

			//Å©¸®Æ¼ÄÃ  
			sinDownCriticalAging(pItem);

		break;
		case sinWS1: //È° 
			//°ø°Ý·Â 
			sinDownDamageAging(pItem,AgingLevelTemp);

			//Å©¸®Æ¼ÄÃ  
			sinDownCriticalAging(pItem);

			//³»±¸·Â
			sinDownDurabilityAging(pItem); 
		break;

		case sinWS2: //Ä®  
			//°ø°Ý·Â 
			sinDownDamageAging(pItem,AgingLevelTemp);

			//¸íÁß·Â
			sinDownAttackRateAging(pItem , 5);
			
			//Å©¸®Æ¼ÄÃ  
			sinDownCriticalAging(pItem);

		break;

		case sinWT1: //ÀÚº§¸° 
			//°ø°Ý·Â 
			sinDownDamageAging(pItem,AgingLevelTemp);

			//Å©¸®Æ¼ÄÃ  
			sinDownCriticalAging(pItem);

			//³»±¸·Â
			//sinSetDurabilityAging(pItem); 
		break;
			
		case sinDS1: //¹æÆÐ 
			//ºí·°À² 
			sinDownBlockRateAging(pItem);
			//Èí¼öÀ²
			sinDownAbsorbAging(pItem , 0.2f ,AgingLevelTemp );
			//³»±¸·Â
			sinDownDurabilityAging(pItem); 
		break;

		case sinOM1: //¸ÅÁöÄÃ °¨ÀÚ 
			//¹æ¾î·Â 
			sinDownDefenseAging(pItem,10);

			//Èí¼öÀ²
			sinDownAbsorbAging(pItem , 0.5f,AgingLevelTemp);

			//³»±¸·Â
			sinDownDurabilityAging(pItem); 

		break;
		case sinDA1: case sinDA2://°©¿Ê 
			//¹æ¾î·Â 
			sinDownDefenseAging(pItem,5);

			//Èí¼öÀ²
			sinDownAbsorbAging(pItem , 0.5f,AgingLevelTemp);

			//³»±¸·Â
			sinDownDurabilityAging(pItem); 

		break; 
		case sinDB1: // ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ Ãß°¡(ºÎÃ÷)
			//¹æ¾î·Â 
			sinDownDefenseAging(pItem,10);
			//Èí¼öÀ²
			sinDownAbsorbAging(pItem , 0.5f, AgingLevelTemp);
			//³»±¸·Â
			sinDownDurabilityAging(pItem); 
		break;
		case sinDG1: // ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ Ãß°¡(Àå°©)
			//¹æ¾î·Â 
			sinDownDefenseAging(pItem,10);
			//Èí¼öÀ²
			sinDownAbsorbAging(pItem , 0.5f, AgingLevelTemp);
			//³»±¸·Â
			sinDownDurabilityAging(pItem); 
		break;
		case sinOA2: // ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ Ãß°¡(¾Ï¸´)
			//¹æ¾î·Â 
			sinDownDefenseAging(pItem,10);
			//¸íÁß·Â
			sinDownAttackRateAging(pItem , 5);
			//³»±¸·Â
			sinDownDurabilityAging(pItem); 
		break;
		}

		pItem->ItemAgingNum[1] = 0; //ÃÊ±âÈ­ 
		pItem->ItemAgingCount[0] = 0;
		pItem->ItemAgingCount[1] = 0;
	
		// pluto ¿¡ÀÌÂ¡
		if( pItem->Level >= 100 ){
			pItem->Level -= 0 ;
		}
		else

			pItem->Level -= 1; //·¹º§À» »©ÁÖ°í
			if(DownNum > 2){
				if((pItem->ItemAgingNum[0] % 2 ) == 1){
					pItem->Level -=1; //¿¡ÀÌÂ¡·¹º§ÀÌ È¦¼öÀÏ°æ¿ì ·¹º§À» ´õ ³»·ÁÁØ´Ù 
			}
	}


	ReformItem(pItem);  //¾ÆÀÌÅÛ ÀÎÁõ ¹Þ±â 
//	ReformMixItem( pItem ); //¿¡ÀÌÂ¡ ÀçÀÎÁõ 
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
			//////////// ¿Àºê , ºñÁî  (µÎ¹ø Ã¼Å©¸¦ ÇØ¾ßÇÏ±â¶§¹®¿¡ ÀÌ·¸°ÔÇØ³õ´Â´Ù)
			if(cInvenTory.InvenItem[sInven[1].ItemIndex-1].Flag ||
				cInvenTory.InvenItem[sInven[1].ItemIndex-1].sItemInfo.ItemAgingNum[1]){
					if((cInvenTory.InvenItem[sInven[1].ItemIndex-1].CODE &sinITEM_MASK2) == sinOM1){
						pItem = &cInvenTory.InvenItem[sInven[1].ItemIndex-1];
						if( pItem && pItem->sItemInfo.ItemKindCode == ITEM_KIND_AGING) {
							///////////È£ÃâµÉ¶§¸¶´Ù ¿Ã·ÁÁØ´Ù  
							if(smConfig.DebugMode){
								pItem->sItemInfo.ItemAgingCount[0] +=200;
							}
							else{
								pItem->sItemInfo.ItemAgingCount[0]++;
							}
							if(pItem->sItemInfo.ItemAgingCount[1] &&  pItem->sItemInfo.ItemAgingCount[0] >= pItem->sItemInfo.ItemAgingCount[1] ){
								//¼­¹ö·Î ¾ÆÀÌÅÛÀ» º¸³½´Ù 
								SendAgingUpgradeItemToServer(&pItem->sItemInfo); 
							}
						}
						pItem = 0;
					}
				}

			// °©¿Ê , ·Îºê 	
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

		// ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¸¶½ºÅÍ ¾ÆÀÌÅÛ
		case SIN_AGING_DEFENSE_ARMOR: // °©¿Ê, ·Îºê
			// °©¿Ê , ·Îºê 	
			if(cInvenTory.InvenItem[sInven[2].ItemIndex-1].Flag ||
				cInvenTory.InvenItem[sInven[2].ItemIndex-1].sItemInfo.ItemAgingNum[1]){
					if((cInvenTory.InvenItem[sInven[2].ItemIndex-1].CODE &sinITEM_MASK2) == sinDA1 ||
						(cInvenTory.InvenItem[sInven[2].ItemIndex-1].CODE &sinITEM_MASK2) == sinDA2 ){
							pItem = &cInvenTory.InvenItem[sInven[2].ItemIndex-1];
						}
				}
		break;
		
		// ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¸¶½ºÅÍ ¾ÆÀÌÅÛ
		case SIN_AGING_DEFENSE_ORB: // ¿Àºê ºñÁî
			if(cInvenTory.InvenItem[sInven[1].ItemIndex-1].Flag ||
				cInvenTory.InvenItem[sInven[1].ItemIndex-1].sItemInfo.ItemAgingNum[1]){
					if((cInvenTory.InvenItem[sInven[1].ItemIndex-1].CODE &sinITEM_MASK2) == sinOM1){
						pItem = &cInvenTory.InvenItem[sInven[1].ItemIndex-1];
					}
				}
		break;

		// ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ Ãß°¡(ºÎÃ÷)
		case SIN_AGING_DEFENSE_BOOTS: // ºÎÃ÷
			if(	!cInvenTory.InvenItem[sInven[9].ItemIndex-1].Flag ||
				!cInvenTory.InvenItem[sInven[9].ItemIndex-1].sItemInfo.ItemAgingNum[1])return FALSE;

			if((cInvenTory.InvenItem[sInven[9].ItemIndex-1].CODE &sinITEM_MASK2) == sinDB1)
				pItem = &cInvenTory.InvenItem[sInven[9].ItemIndex-1];
			break;

			// ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ Ãß°¡(Àå°©)
		case SIN_AGING_DEFENSE_GLOVES: // Àå°©
			if(	!cInvenTory.InvenItem[sInven[8].ItemIndex-1].Flag ||
				!cInvenTory.InvenItem[sInven[8].ItemIndex-1].sItemInfo.ItemAgingNum[1])return FALSE;

			if((cInvenTory.InvenItem[sInven[8].ItemIndex-1].CODE &sinITEM_MASK2) == sinDG1)
				pItem = &cInvenTory.InvenItem[sInven[8].ItemIndex-1];
			break;

			// ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ Ãß°¡(¾Ï¸´)
		case SIN_AGING_DEFENSE_ARMLETS: // ¾Ï¸´
			if(	!cInvenTory.InvenItem[sInven[7].ItemIndex-1].Flag ||
				!cInvenTory.InvenItem[sInven[7].ItemIndex-1].sItemInfo.ItemAgingNum[1])return FALSE;

			if((cInvenTory.InvenItem[sInven[7].ItemIndex-1].CODE &sinITEM_MASK2) == sinOA2)
				pItem = &cInvenTory.InvenItem[sInven[7].ItemIndex-1];
			break;
	}

	if(!pItem || pItem->sItemInfo.ItemKindCode != ITEM_KIND_AGING)return FALSE;

	///////////È£ÃâµÉ¶§¸¶´Ù ¿Ã·ÁÁØ´Ù  
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
		//¼­¹ö·Î ¾ÆÀÌÅÛÀ» º¸³½´Ù 
		SendAgingUpgradeItemToServer(&pItem->sItemInfo);
	}



	/*

	//¿¡ÀÌÂ¡ ¾ÆÀÌÅÛÀÌ ¾Æ´Ï°Å³ª ¿¡ÀÌÂ¡ÀÌ ²ËÂù ¾ÆÀÌÅÛÀº ¸®ÅÏÇÑ´Ù 
	if(pItem->sItemInfo.ItemKindCode != ITEM_KIND_AGING ||
		(pItem->sItemInfo.ItemAgingCount[0] >= pItem->sItemInfo.ItemAgingCount[1]) )
		return FALSE;
		

	//////////////ÃÊ ³ë°¡´Ù ÀÛ¾÷ 
	if(!CheckItemForm(&pItem->sItemInfo)){ //¾ÆÀÌÅÛ ÀÎÁõ¹Þ±â 
		SendSetHackUser(12); //ÇØÅ·À» ÇÏ·Á°íÇß´ø ¾¾¹Ù!! À¯Àú¸¦ °í¹ß TRUE Á¢¼Ó Á¾·á 
		return FALSE;

	}

	//¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ ÀÎÁõÈ®ÀÎ 
	if(!CheckMixItem( &pItem->sItemInfo )){
		SendSetHackUser(52); //ÇØÅ·À» ÇÏ·Á°íÇß´ø ¸øµÈ À¯Àú¸¦ °í¹ß TRUE Á¢¼Ó Á¾·á 
		return FALSE;
	}
	*/

	return TRUE;	
}

//´É·ÂÄ¡°¡ Çâ»óµÈ ¾ÆÀÌÅÛÀ» ¹Þ´Â´Ù 
int sinRecvAgingIncreStateItem(sITEMINFO *pItem)
{
	for(int i = 0; i  < INVENTORY_MAXITEM ; i++){ 
		if(cInvenTory.InvenItem[i].sItemInfo.BackUpChkSum  == pItem->BackUpChkSum &&
			cInvenTory.InvenItem[i].sItemInfo.BackUpKey == pItem->BackUpKey &&
			cInvenTory.InvenItem[i].sItemInfo.CODE == pItem->CODE){
				memcpy(&cInvenTory.InvenItem[i].sItemInfo,pItem,sizeof(sITEMINFO));
				cInvenTory.ReFormInvenItem();   //ÀÎº¥Åä¸® ¾ÆÀÌÅÛ ÀÎÁõ 
				cInvenTory.CheckRequireItemToSet(&cInvenTory.InvenItem[i]); 
				cInvenTory.SetItemToChar(); //´É·ÂÄ¡ ÀçÁ¶Á¤
				break;

		}
	}

	return TRUE;
}

//¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ¿¡ ´ëÇÑ ÇØÅ·À» ¸·´Â´Ù 
int sinCheckAgingItemHack(sITEM *pItem)
{ 
	if(	pItem->sItemInfo.ItemKindCode == ITEM_KIND_CRAFT){
		return FALSE;

	}
	return TRUE;
}

///////////////ÇØÅ·¹æÁö¸¦ À§ÇØ µ·À» ÇÑ°÷¿¡¼­ °ü¸®ÇÑ´Ù 
int sinMinusMoney(int Money,int Kind)
{
	//°ø¼ºÀü ¼¼À²ÀÇ ¿µÇâ¹Þ´Â´Ù.
	if(Kind){
		//--------------------------------------------------------------------------//
		#ifdef HASIEGE_MODE
		    //°ø¼ºÀü ¼¼À²Àû¿ë ¸¶ÀÌ³Ê½º ¸Ó´Ï Àû¿ë
			
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

	ReformCharForm();//ÀçÀÎÁõ 
	
	SendSaveMoney(); //±Ý¾× Á¶ÀÛÀ» ¸øÇÏ°ÔÇÏ±âÀ§ÇØ È£ÃâÇÑ´Ù 

	return TRUE	;		
}

int sinPlusMoney(int Money)
{
	sinChar->Money += Money;

	ReformCharForm();//ÀçÀÎÁõ 
	SetTotalAddMoney(Money);
	SendSaveMoney(); //±Ý¾× Á¶ÀÛÀ» ¸øÇÏ°ÔÇÏ±âÀ§ÇØ È£ÃâÇÑ´Ù 

	return TRUE;
}

///////////////ÇØÅ·¹æÁö¸¦ À§ÇØ µ·À» ÇÑ°÷¿¡¼­ °ü¸®ÇÑ´Ù (Ã¢°í¸¸ µû·Î °ü¸® )
int sinMinusMoney2(int Money)
{
	sinChar->Money -= Money;

	ReformCharForm();//ÀçÀÎÁõ 
	SendSaveMoney(); //±Ý¾× Á¶ÀÛÀ» ¸øÇÏ°ÔÇÏ±âÀ§ÇØ È£ÃâÇÑ´Ù 

	return TRUE;
}

int sinPlusMoney2(int Money)
{
	sinChar->Money += Money;

	ReformCharForm();//ÀçÀÎÁõ 
	SendSaveMoney(); //±Ý¾× Á¶ÀÛÀ» ¸øÇÏ°ÔÇÏ±âÀ§ÇØ È£ÃâÇÑ´Ù 

	return TRUE;
}

//¿ø¼Ò¼Ó¼ºÀ» ±¸ÇÑ´Ù 
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

// Premiação evento quebra-cabeça aqui
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

//¹æ¾î±¸
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


// Àåº° - Äµµðµ¥ÀÌÁî º¸»ó ¾ÆÀÌÅÛ
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


// Àåº° - ¸ÅÁöÄÃ±×¸° ¿¡¸Þ¶öµå º¸»ó ¾ÆÀÌÅÛ
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


// Àåº° - ¸ÅÁöÄÃ±×¸° ºñÃë º¸»ó ¾ÆÀÌÅÛ
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


// Àåº° - Ä«¶óÀÇ ´«¹° º¸»ó ¾ÆÀÌÅÛ
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

// Correção quebra cabeça, estava pegando premiação aqui
char  *PresentFindinvestigatorNineWeaponName3[1][9] = {"gf107",0,0,0,0,0,0,0,0 };
char  *PresentFindinvestigatorNineArmorName3[1][9] = {"gf107",0,0,0,0,0,0,0,0 };
int PresentFindinvestigatorNinePercentIndex3[1] = {10000};

// Àåº° - Á¶»ç¿øÀ» Ã£¾Æ¶ó Å×ÀÏ¾Æ¹Ä·¿ ¹èÆ÷
char  *PresentFindinvestigatorNineTaleWeaponName3[1][9] = {"gf108",0,0,0,0,0,0,0,0 };
char  *PresentFindinvestigatorNineTaleArmorName3[1][9] = {"gf108",0,0,0,0,0,0,0,0 };
int PresentFindinvestigatorNineTalePercentIndex3[1] = {10000};

// Àåº° - Á¶»ç¿øÀ» Ã£¾Æ¶ó ¿¡Åä º¸»ó ¾ÆÀÌÅÛ
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


// Premiação Evento Melancia
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


// ¹ÚÀç¿ø - ¾ËÆÄºª Á¶ÇÕ ÀÌº¥Æ®
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


DWORD sinForceOrbCode[] = {(sinFO1|sin01),(sinFO1|sin02),(sinFO1|sin03),(sinFO1|sin04),(sinFO1|sin05),(sinFO1|sin06),(sinFO1|sin07),(sinFO1|sin08),(sinFO1|sin09),(sinFO1|sin10),(sinFO1|sin11),(sinFO1|sin12),(sinFO1|sin13),(sinFO1|sin14),(sinFO1|sin15)}; // ¹ÚÀç¿ø - º§·ë, ¿À¸£µµ Æ÷½º Ãß°¡

// ¹ÚÀç¿ø - ¸ÅÁ÷ Æ÷½º Ãß°¡
DWORD sinMagincForceOrbCode[] = {(sinFO1|sin21),(sinFO1|sin22),(sinFO1|sin23),(sinFO1|sin24),(sinFO1|sin25),(sinFO1|sin26),(sinFO1|sin27),(sinFO1|sin28),(sinFO1|sin29),(sinFO1|sin30),(sinFO1|sin31),(sinFO1|sin32),(sinFO1|sin33),(sinFO1|sin34)};
// ¹ÚÀç¿ø - ºô¸µ ¸ÅÁ÷ Æ÷½º Ãß°¡
DWORD sinBillingMagicForceOrbCode[] = {(sinFO1|sin35),(sinFO1|sin36),(sinFO1|sin37)};

DWORD sinWingItemQuestServer(sCRAFTITEM_SERVER *pWingItem , smCHAR_INFO *pChar_Info)
{
	//3Â÷ Àü¾÷Äù½ºÆ®
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
	//ÀÏ°ö°¡Áö Å©¸®½ºÅ»À» ´Ù½ÃÃ¼Å©ÇÑ´Ù.
	for( i = 0 ; i < 7 ; i++ ){
		for( j = 0 ; j < 12 ; j++ ){
			if( pWingItem->SheltomCode[i]==CristalEventCODE[j] ){
				CristalCount = i+1;
			}
		}
	}
	
	int WatermelonCount=0;
	int WatermelonFlag =0;
	//¹ÚÀç¿ø - ¼ö¹Ú ¸ð¾Æ¿À±â(7°³ÀÇ ¼ö¹ÚÀ» ´Ù½ÃÃ¼Å©ÇÑ´Ù.)
	for(int n = 0 ; n < 7 ; n++ )
	{
		if( pWingItem->SheltomCode[n]==WatermelonEventCODE )
		{
			WatermelonCount = n+1;
		}
	}

	int ValentineCount=0;
	int ValentineFlag =0;
	//Àåº° - ¹ß·»Å¸ÀÎ ÃÊÄÝ¸´ ¸ð¾Æ¿À±â(7°³ÀÇ ÃÊÄÝ¸´À» ´Ù½ÃÃ¼Å©ÇÑ´Ù.)
	for(int n = 0 ; n < 7 ; n++ )
	{
		if( pWingItem->SheltomCode[n]==ValentineEventCODE )
		{
			ValentineCount = n+1;
		}
	}


	int CandydaysCount=0;
	int CandydaysFlag =0;
	// Àåº° - Äµµðµ¥ÀÌÁî (7°³ÀÇ Äµµð ´Ù½ÃÃ¼Å©ÇÑ´Ù.)
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
	// Àåº° - ¸ÅÁöÄÃ±×¸° (7°³ÀÇ ¿¡¸Þ¶öµå ´Ù½ÃÃ¼Å©ÇÑ´Ù.)
	for(int a = 0 ; a < 7 ; a++ )
	{
		if( pWingItem->SheltomCode[a]==MagicalGreenEventCODE[1] )
		{
			MagicalGreenEmeraldCount = a+1;
		}
	}

	// Àåº° - ¸ÅÁöÄÃ±×¸° (7°³ÀÇ ºñÃë ´Ù½ÃÃ¼Å©ÇÑ´Ù.)
	for(int b = 0 ; b < 7 ; b++ )
	{
		if( pWingItem->SheltomCode[b]==MagicalGreenEventCODE[0] )
		{
			MagicalGreenJadeCount = b+1;
		}
	}

	int TearOfKaraCount=0;
	int TearOfKaraFlag =0;
	// Àåº° - Ä«¶óÀÇ ´«¹° (7°³ÀÇ ´«¹° ´Ù½ÃÃ¼Å©ÇÑ´Ù.)
	for(int n = 0 ; n < 7 ; n++ )
	{
		if( pWingItem->SheltomCode[n]==TeatOfKaraEventCODE )
		{
			TearOfKaraCount = n+1;
		}
	}


	// Àåº° - Á¶»ç¿øÀ» Ã£¾Æ¶ó
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


	// ¹ÚÀç¿ø - ¾ËÆÄºª Á¶ÇÕ ÀÌº¥Æ®
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

	//¹Ùº§¾ÆÀÌÅÛ 
	if( pWingItem->SheltomCode[0] == (sinGF1 | sin02) ){
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 5;
		pPresentWeaponName = PresentWeaponName; //Æ÷ÀÎÅÍ ¿¬°á
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
	// ±¸¹ÌÈ£¾ÆÀÌÅÛ
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

	// ºû³ª´Â °¡·ç
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
	//ÀÏ°ö°¡Áö Å©¸®½ºÅ»ÀÇ º¸Àº ¾ÆÀÌÅÛ ÁÖ±â
	else if(CristalCount==7){
		CristalFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 5;
		//ÀÓ½Ã·Î
		pPresentWeaponName   = PresentWeaponName3; //Æ÷ÀÎÅÍ ¿¬°á
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
	//¹ÚÀç¿ø - ¼ö¹Ú ¸ð¾Æ¿À±â
	else if(WatermelonCount==7)
	{
		WatermelonFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 9; // ¹ÚÀç¿ø - ¼ö¹Ú ÀÌº¥Æ® 12°¡Áö Áß ÇÑ°¡Áö ¾ÆÀÌÅÛÀ» º¸»óÇÑ´Ù. // È£¹Ú ÀÌº¥Æ® 9°¡Áö Áß ÇÑ°¡Áö¸¦ º¸»óÇÑ´Ù. // ¹ãÇÏ´ÃÀÇ ¼Ò¿ø ÀÌº¥Æ® 9°¡ÁöÁß ÇÑ°¡Áö¸¦ º¸»óÇÑ´Ù.
		//ÀÓ½Ã·Î
		pPresentWeaponName   = PresentWeaponName3; //Æ÷ÀÎÅÍ ¿¬°á
		pPresentArmorName    = PresentArmorName3;
		pPresentPercentIndex = PresentPercentIndex3;
		PotionNum = 5; // ¹ÚÀç¿ø - ¼ö¹Ú ÀÌº¥Æ® º¸»ó ¾ÆÀÌÅÛÀÌ ¹°¾àÀÏ °æ¿ì ¹°¾à °³¼ö¸¦ ¼ÂÆÃÇÑ´Ù. //¹ÚÀç¿ø - ¹ãÇÏ´ÃÀÇ ¼Ò¿ø ÀÌº¥Æ®(¹°¾à º¸»ó 5°³)
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}

	//Àåº° - ¹ß·»Å¸ÀÎ ÃÊÄÝ¸´ ¸ð¾Æ¿À±â
	else if(ValentineCount==7)
	{
		ValentineFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 17; // Àåº° - ¹ß·»Å¸ÀÎ ÃÊÄÝ¸´ ÀÌº¥Æ® 17°¡Áö Áß ÇÑ°¡Áö ¾ÆÀÌÅÛÀ» º¸»óÇÑ´Ù. 
		//ÀÓ½Ã·Î
		pPresentWeaponName   = PresentChocoWeaponName3; //Æ÷ÀÎÅÍ ¿¬°á
		pPresentArmorName    = PresentChocoArmorName3;
		pPresentPercentIndex = PresentChocoPercentIndex3;
		PotionNum = 5; // Àåº° - ¹ß·»Å¸ÀÎ ÀÌº¥Æ® º¸»ó ¾ÆÀÌÅÛÀÌ ¹°¾àÀÏ °æ¿ì ¹°¾à °³¼ö¸¦ ¼ÂÆÃÇÑ´Ù.
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}
	// ¹ÚÀç¿ø - ¾ËÆÄºª Á¶ÇÕ ÀÌº¥Æ®
	else if(PristonAlphabetCount==7){
		PristonAlphabetFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 11;
		//ÀÓ½Ã·Î
		pPresentWeaponName   = PresentWeaponName5; //Æ÷ÀÎÅÍ ¿¬°á
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


	// Àåº° - Äµµðµ¥ÀÌÁî Äµµð ¸ð¾Æ¿À±â
	else if(CandydaysCount==7)
	{
		CandydaysFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 17; // Àåº° - Äµµðµ¥ÀÌÁî ÀÌº¥Æ® 17°¡Áö Áß ÇÑ°¡Áö ¾ÆÀÌÅÛÀ» º¸»óÇÑ´Ù. 
		//ÀÓ½Ã·Î
		pPresentWeaponName   = PresentCandyWeaponName3; //Æ÷ÀÎÅÍ ¿¬°á
		pPresentArmorName    = PresentCandyArmorName3;
		pPresentPercentIndex = PresentCandyPercentIndex3;
		PotionNum = 5; // Àåº° - Äµµðµ¥ÀÌÁî ÀÌº¥Æ® º¸»ó ¾ÆÀÌÅÛÀÌ ¹°¾àÀÏ °æ¿ì ¹°¾à °³¼ö¸¦ ¼ÂÆÃÇÑ´Ù.
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}

	// Àåº° - ¸ÅÁöÄÃ±×¸° -  ºñÃë ¸ð¾Æ¿À±â
	else if(MagicalGreenJadeCount==7)
	{
		MagicalGreenJadeFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 15; // Àåº° - ¸ÅÁöÄÃ±×¸° ÀÌº¥Æ® 15°¡Áö Áß ÇÑ°¡Áö ¾ÆÀÌÅÛÀ» º¸»óÇÑ´Ù. 
		//ÀÓ½Ã·Î
		pPresentWeaponName    = PresentMagicalGreenJadeWeaponName3; //Æ÷ÀÎÅÍ ¿¬°á
		pPresentArmorName	 = PresentMagicalGreedJadeArmorName3;
		pPresentPercentIndex = PresentMagicalGreedJadePercentIndex3;
		PotionNum = 10; // Àåº° - ¸ÅÁöÄÃ±×¸° ÀÌº¥Æ® º¸»ó ¾ÆÀÌÅÛÀÌ ¹°¾àÀÏ °æ¿ì ¹°¾à °³¼ö¸¦ ¼ÂÆÃÇÑ´Ù.
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}


	// Àåº° - ¸ÅÁöÄÃ±×¸° -  ¿¡¸Þ¶öµå ¸ð¾Æ¿À±â
	else if(MagicalGreenEmeraldCount==7)
	{
		MagicalGreenEmeraldFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 18; // Àåº° - ¸ÅÁöÄÃ±×¸° ÀÌº¥Æ® 18°¡Áö Áß ÇÑ°¡Áö ¾ÆÀÌÅÛÀ» º¸»óÇÑ´Ù. 
		//ÀÓ½Ã·Î
		pPresentWeaponName    = PresentMagicalGreenEmeraldWeaponName3; //Æ÷ÀÎÅÍ ¿¬°á
		pPresentArmorName	 = PresentMagicalGreenEmeraldArmorName3;
		pPresentPercentIndex = PresentMagicalGreenEmeraldPercentIndex3;
		PotionNum = 20; // Àåº° - ¸ÅÁöÄÃ±×¸° ÀÌº¥Æ® º¸»ó ¾ÆÀÌÅÛÀÌ ¹°¾àÀÏ °æ¿ì ¹°¾à °³¼ö¸¦ ¼ÂÆÃÇÑ´Ù.
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}

	// Àåº° - Ä«¶óÀÇ ´«¹°  ´«¹° ¸ð¾Æ¿À±â
	else if(TearOfKaraCount==7)
	{
		TearOfKaraFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 18; // Ä«¶óÀÇ ´«¹° ÀÌº¥Æ® 18°¡Áö Áß ÇÑ°¡Áö ¾ÆÀÌÅÛÀ» º¸»óÇÑ´Ù. 
		//ÀÓ½Ã·Î
		pPresentWeaponName   = PresentTearOfKaraWeaponName3; //Æ÷ÀÎÅÍ ¿¬°á
		pPresentArmorName    = PresentTearOfKaraArmorName3;
		pPresentPercentIndex = PresentTearOfKaraPercentIndex3;
		PotionNum = 10; // Àåº° - Äµµðµ¥ÀÌÁî ÀÌº¥Æ® º¸»ó ¾ÆÀÌÅÛÀÌ ¹°¾àÀÏ °æ¿ì ¹°¾à °³¼ö¸¦ ¼ÂÆÃÇÑ´Ù.
		if(RandomTemp < 50){
			ItemCountPuzzle = 8;
		}
		else{
			ItemCountPuzzle = 16;
		}
	}


	// Correção quebra cabeça
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
					ItemIndex = 1; // Á¶»ç¿øÀ» Ã£¾Æ¶ó ³ªÀÎ¾Æ¹Ä·¿ ¹èÆ÷
					//ÀÓ½Ã·Î
					pPresentWeaponName   = PresentFindinvestigatorNineWeaponName3; //Æ÷ÀÎÅÍ ¿¬°á
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

	// Àåº° - Á¶»ç¿øÀ» Ã£¾Æ¶ó( ³ªÀÎ¾Æ¹Ä·¿À» ¼ÒÁöÇÏ°í ÀÖÀ»¶§)
	else if( FindinvestigatorNineCount == 1 )
	{
		FindinvestigatorNineFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 1; // Á¶»ç¿øÀ» Ã£¾Æ¶ó Å×ÀÏ¾Æ¹Ä·¿ ¹èÆ÷
		//ÀÓ½Ã·Î
		pPresentWeaponName   = PresentFindinvestigatorNineTaleWeaponName3; //Æ÷ÀÎÅÍ ¿¬°á
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

	// Àåº° - Á¶»ç¿øÀ» Ã£¾Æ¶ó( Å×ÀÏ¾Æ¹Ä·¿À» ¼ÒÁöÇÏ°í ÀÖÀ»¶§)
	else if( FindinvestigatorTaleCount == 1 ) 
	{
		FindinvestigatorTaleFlag = 1;
		RandomTemp = GetRandomPos(0,100);
		ItemIndex = 12; 
		//ÀÓ½Ã·Î
		pPresentWeaponName   = PresentFindinvestigatorWeaponName3; //Æ÷ÀÎÅÍ ¿¬°á
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

		//ÆÛÁñ
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
	// Premiacao evento quebra cabeça
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
						if(PresentItemIndex < 0 )break; //¹«ÇÑ·çÇÁ ¹æÁö
					}
				}
			}
			else PresentPercentSum += pPresentPercentIndex[i];
		}
	}
	
	//80_2 LvÄù½ºÆ®
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
			case 1:		//ÆÄÀÌÅÍ
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWA1 | sin08);
			break;
			case 2:		//¸ÞÄ«´Ï¼Ç
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWC1 | sin08);
			break;
			case 3:		//¾ÆÃÄ
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWS1 | sin10);
			break;
			case 4:		//ÆÄÀÌÅ©¸Ç
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWP1 | sin09);
			break;
			case 5:		//¾ÆÅ»¶õÅ¸
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWT1 | sin09);
			break;
			case 6:		//³ªÀÌÆ®
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWS2 | sin10);
			break;
			case 7:		//¸ÅÁö¼Ç
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWM1 | sin09);
			break;
			case 8:		//ÇÁ¸®½ºÆ¼½º
				pWingItem->DesCraftItem.sItemInfo.CODE = (sinWM1 | sin09);
			break;
		}
		//¼­¹ö¿¡¼­ ¼ÂÆÃÇØÁØ´Ù
		pWingItem->DesCraftItem.sItemInfo.ItemKindCode = ITEM_KIND_QUEST_WEAPON;
		//SetChangeJob3QuestItem(&pWingItem->DesCraftItem.sItemInfo); //¾ÆÀÌÅÛ ÃÊ±â¼ÂÆÃ
		return TRUE;

	}
	//Æ÷½º ¿Àºê
	if(pWingItem->DesCraftItem.CODE == 1000){
		for( i = 0 ; i < 12 ; i++){
			for(j = 0 ; j < 16 ; j++){ // ¹ÚÀç¿ø - º§·ë, ¿À¸£µµ Æ÷½º Ãß°¡(12 -> 14))
				if((pWingItem->SheltomCode[i] & sinITEM_MASK3) == SheltomCode2[j]){
					pWingItem->Head[i] = 0;
					pWingItem->CheckSum[i] = 0;
					pWingItem->SheltomCode[i] = sinForceOrbCode[j];
					break;
				}
				// ¹ÚÀç¿ø - ¸ÅÁ÷ Æ÷½º Ãß°¡
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

//¼­¹ö¿¡ À®¾ÆÀÌÅÛÀ» º¸³½´Ù
int SendWingQuestItem() //À®¾ÆÀÌÅÛ Äù½ºÆ® 
{
	SendWingItemToServer( &sWingItem_Send );   
	return TRUE;
}

//¼­¹ö¿¡¼­ À®¾ÆÀÌÅÛÀ» ¹Þ´Â´Ù
int RecvWingItem(sCRAFTITEM_SERVER *pWingItem)
{
 
	sITEM *pItem=0; 
	int   Index = 0; 
	int   i = 0; 
	sITEM sinTempItem;  //¾ÆÀÌÅÛ¿¡ °ü·ÃµÈ »çÇ×À» Àá½Ã ³Ö¾îµÎ´Â Temp

	//if(pWingItem->Result != TRUE)return FALSE;

	//ÆÛÁñÀÏ°æ¿ì´Â ¾îÄÉÇÏ³ª -0-

	for( i = 0; i < INVENTORY_MAXITEM*2 ; i++){
		if(i<100){
			if(!cInvenTory.InvenItem[i].Flag)continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else{
			if(!cInvenTory.InvenItemTemp[i-100].Flag)continue;
			pItem = &cInvenTory.InvenItemTemp[i-100];
		}

		//°á°ú°¡ FALSEÀÏ°æ¿ì¿¡´Â À® ¾ÆÀÌÅÛµµ »èÁ¦ÇÑ´Ù
		if(pWingItem->Result == FALSE){
			cInvenTory.DeleteInvenItemToServer(pWingItem->DesCraftItem.sItemInfo.CODE , pWingItem->DesCraftItem.sItemInfo.ItemHeader.Head ,
			 pWingItem->DesCraftItem.sItemInfo.ItemHeader.dwChkSum);

		}

		//ÀÎÁõÄÚµå°¡ ¾ø´Â ÅõÇÚµå ¹«±â´Â Ã¼Å©ÇÏÁö¾Ê´Â´Ù 
		if(pItem->ItemPosition == 2){  
			if(pItem->Class == ITEM_CLASS_WEAPON_TWO)
				continue; 
		}

		for(int j = 0 ; j < 8 ; j++){
			if(pItem->sItemInfo.CODE == pWingItem->SheltomCode[j] &&
				pItem->sItemInfo.ItemHeader.Head == pWingItem->Head[j] &&
				pItem->sItemInfo.ItemHeader.dwChkSum == pWingItem->CheckSum[j]){
					pItem->Flag = 0; //¾ÆÀÌÅÛÀ» Áö¿öÁØ´Ù
					cInvenTory.ReFormInvenItem();
					cInvenTory.CheckWeight();
				}
				
		}
	}	
	
	//¼º°øÇÏ¿´À»°æ¿ì¿¡ µ·À»»©°í ¾ÆÀÌÅÛÀ» ¼ÂÆÃÇÑ´Ù
	if(pWingItem->Result == TRUE){
		sinMinusMoney(pWingItem->Money);//µ·À» »«´Ù
		SendSaveMoney(); //±Ý¾× Á¶ÀÛÀ» ¸øÇÏ°ÔÇÏ±âÀ§ÇØ È£ÃâÇÑ´Ù 

		//¾ÆÀÌÅÛÀ» ÀÎº¥Åä¸®¿¡ ¼ÂÆÃÇÑ´Ù
		if(pWingItem->DesCraftItem.sItemInfo.CODE){
			if(LoadItemImage(&pWingItem->DesCraftItem.sItemInfo,&sinTempItem)){
				//Äù½ºÆ® ¾ÆÀÌÅÛÀ» ¹Þ°í ·¹º§À» ¼ÂÆÃ
				if(sinTempItem.sItemInfo.ItemKindCode ==ITEM_KIND_QUEST_WEAPON){
					sinQuest_ChangeJob3.StartLevel = sinChar->Level;

				}
				sinSetSpecialItemCode(&sinTempItem.sItemInfo); //½ºÆä¼È¾ÆÀÌÅÛÀ» ±¸ºÐÇÑ´Ù
				cInvenTory.AutoSetInvenItem(&sinTempItem,1+pWingItem->DocIndex); //ÀÎµ¦½º¿¡ 1ÀÌÀÖÀ»°æ¿ì ÁÂÇ¥¸¦ °íÁ¤ÇÑ´Ù
				cInvenTory.ReFormInvenItem();
				ResetPotion();
				cInvenTory.ReFormPotionNum();	//Æ÷¼Ç °¹¼ö¸¦ Ã¼Å©ÇÑ´Ù
			}
		}
	}

	ReformCharForm();//ÀçÀÎÁõ 
	cInvenTory.SetItemToChar();
	cInvenTory.CheckWeight();
	
	sinbaram_Stop = 0; //ÀÌº¥Æ®°¡ Á¤»óÀÛµ¿µÇ°ÔÇÑ´Ù
	cInvenTory.CheckPuzzle();

	return TRUE;	
}

//¸µÀ» ¿¡ÀÌÂ¡ ÇÑ´Ù
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

//¼ýÀÚ¿¡ ÄÞ¸¶¸¦Âï¾î¼­ ³Ñ±ä´Ù
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

//¹°¾àÀ» ¹ö·ÈÀ» °æ¿ì °ÔÀÓÀ» ÀúÀåÇÑ´Ù (ÇöÀç·Î¼±)
int sinSaveGame(DWORD CODE , int Count)
{
	DWORD MASK_CODE = (CODE & sinITEM_MASK2);

	//±â¾àÀÏ°æ¿ì 
	if(MASK_CODE == sinPM1 && Count >= 4 ){
		SaveGameData();

	}
	if((  MASK_CODE == sinPL1 || MASK_CODE == sinPS1 ) && Count >= 10){
		SaveGameData();
	}
	return TRUE;
}

//³¯Â¥°¡ Áö³­¾ÆÀÌÅÛÀÌ »ç¶óÁø°É º¸¿©ÁØ´Ù
int OverDay_Item_Flag = 0;
int OverDay_Item_Delete(sITEM *pItem)
{ 
	return TRUE;
}


//¸ðµç ÀÎÅÍÆäÀÌ½º¸¦ ´Ý´Â´Ù
int sinCloseInterFace() { return TRUE; }

int sinCheck_ShowHelpMap() { return TRUE; }

//Æ÷½º ¾ÆÀÌÅÛÀ» ¹Þ´Â´Ù
int sinRecvForceOrb(sITEMINFO *pItemInfo , int Count) { return TRUE; }

DWORD SummonSkillCode[] = {
	SKILL_METAL_GOLEM,
	SKILL_FIRE_ELEMENTAL,
	SKILL_RECALL_WOLVERIN,
	0,

};
int SummonSkillCodeIndex[10] = {0,};

//´õºíÅ¬¸¯ÀÌº¥Æ®
int sinDoubleClick() { return TRUE; }

