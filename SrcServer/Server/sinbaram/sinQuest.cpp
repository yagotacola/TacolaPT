/*----------------------------------------------------------------------------*
*	���ϸ� :  sinHelp.cpp	
*	�ϴ��� :  �Źٶ� �����
*	�ۼ��� :  ����������Ʈ 2002�� 7��
*	������ :  �ڻ� 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"
#include "..\\field.h"
#include "Character/playmain.h"
#include "Character/playsub.h"
#include "..\\netplay.h"
#include "Character/character.h"
#include "..\\fileread.h"

/*----------------------------------------------------------------------------*
*							���� ���� 						
*-----------------------------------------------------------------------------*/	
sQUEST_CHANGEJOB	sinQuest_ChangeJob;	//����Ʈ�� �������� ������ �ٷ�� (�۽�ũ��)
sQUEST_CHANGEJOB	sinQuest_ChangeJob2;//����Ʈ�� �������� ������ �ٷ�� (����̿�)
sQUEST_CHANGEJOB3   sinQuest_ChangeJob3;//�۽�ũ�� ����̿� 3�� ��������Ʈ 
sQUEST_CHANGEJOB3   sinQuest_ChangeJob4;//�۽�ũ�� ����̿� 3�� ��������Ʈ 

//��������Ʈ
sQUEST_CHANGEJOB3   sinQuest_Level30;
sQUEST_CHANGEJOB3   sinQuest_Level55;
sQUEST_CHANGEJOB3   sinQuest_Level55_2;
sQUEST_CHANGEJOB3   sinQuest_Level70;
sQUEST_CHANGEJOB3   sinQuest_Level80;
sQUEST_CHANGEJOB3   sinQuest_Level85;
sQUEST_CHANGEJOB3   sinQuest_Level90;

sQUEST_CHANGEJOB3   sinQuest_Level80_2; //�����߰��� ���� +7����Ʈ
sQUEST_CHANGEJOB3   sinQuest_Level90_2; //�����߰��� ���� +10����Ʈ

DWORD sinQuest_levelLog = 0; //����Ʈ�� �����߳� �α�

sITEM TempQuestItem;

int sinChangeJobButtonShow  = 0; //�۽�ũ�� ���� 2������
int sinChangeJobButtonShow2 = 0; //����̿� ���� 2������
int sinChangeJobButtonShow3 = 0; //�۽�ũ�� ����̿� 3������
int sinChangeJobButtonShow4 = 0; //�۽�ũ�� ����̿� 4������

int CheckQuestComplete = 0;		 //������ �������
int CheckQuestButtonShow1 = 0;
int CheckQuestButtonShow2 = 0;
int CheckQuestButtonShow3 = 0;

POINT QuestMessageBoxPosi2 = {50,45};
POINT QuestMessageBoxSize2 = {9,10};

//����Ʈ ������ ��� 
char *QuestFilePath[] ={
	"image\\Sinimage\\Quest\\ChangeJob1.sin",
	"image\\Sinimage\\Quest\\ChangeJob2.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_M1.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_M2.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_M3.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_D1.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_D2.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_D3.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_Success.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_M0.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_D0.sin",
	"image\\Sinimage\\Quest\\ChangeJob1.sin",
};

char *QuestFilePath3[] ={
	"image\\Sinimage\\Quest\\ChangeJob3_0.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_1.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_2.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_3.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_4.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_5.sin",
};


char *WingQuestFilePath_a[] = {
	"image\\Sinimage\\Quest\\M_Wing_a.sin",
	"image\\Sinimage\\Quest\\S_Wing_a.sin",
	"image\\Sinimage\\Quest\\G_Wing_a.sin",
	"image\\Sinimage\\Quest\\D_Wing_a.sin",
	"image\\Sinimage\\Quest\\K_wing_a.sin", //���̾ƽ���
	"image\\Sinimage\\Quest\\E_wing_a.sin", //�ͽ�Ʈ���� �ν�Ʈ ���Ϸ��� (�����߰�)
	"image\\Sinimage\\Quest\\Puzzle.sin",   //��� ���� ~~~ �ǵ��� ������ -0-

};

char *WingQuestFilePath_b[] = {
	"image\\Sinimage\\Quest\\M_Wing_b.sin",
	"image\\Sinimage\\Quest\\S_Wing_b.sin",
	"image\\Sinimage\\Quest\\G_Wing_b.sin",
	"image\\Sinimage\\Quest\\D_Wing_b.sin",
	"image\\Sinimage\\Quest\\K_wing_b.sin", //���̾ƽ���
	"image\\Sinimage\\Quest\\E_wing_b.sin", //�ͽ�Ʈ���� �ν�Ʈ ���Ϸ��� (�����߰�)
	"image\\Sinimage\\Quest\\Wing_End.sin",

};

char *WarpGateDoc[] = {
	"image\\Sinimage\\WarpGateDoc\\Default.sin",
	"image\\Sinimage\\WarpGateDoc\\Ricarten.sin",
	"image\\Sinimage\\WarpGateDoc\\Pilai.sin",
	"image\\Sinimage\\WarpGateDoc\\Forest2.sin",
	"image\\Sinimage\\WarpGateDoc\\Forest3.sin",
	"image\\Sinimage\\WarpGateDoc\\Ruinen.sin",
	"image\\Sinimage\\WarpGateDoc\\Nevisco.sin",
	"image\\Sinimage\\WarpGateDoc\\Desert4.sin",
	"image\\Sinimage\\WarpGateDoc\\yura.sin",
	"image\\Sinimage\\WarpGateDoc\\chaoticpost.sin",	//�ν�Ʈ ���Ϸ��� (�����߰�)

};
char *HaWarpGateDoc[] = {
	"image\\Sinimage\\WarpGateDoc\\B_Castle.sin"
};

char *WarningInitPoint[] = {
	"image\\Sinimage\\Help\\WarnigWeight.sin",

};
char *BabelEventDoc = "image\\Sinimage\\Quest\\BaBelEvent.sin";
char *NineTailFoxDoc = "image\\Sinimage\\Quest\\NineTailFoxEvent.sin";
char *StarDustDoc = "image\\Sinimage\\Quest\\StarDust.sin";		//ũ������������
char *CristalEventDoc= "image\\Sinimage\\Quest\\CristalEvent.sin";//�ϰ����� ũ����Ż�� ����

//����� - ���� ��ƿ���
char *WatermelonDoc = "image\\Sinimage\\Quest\\WatermelonEvent.sin";//���� ��ƿ��� �̺�Ʈ
//����� - ȣ�� ��ƿ���
char *PumpkinDoc = "image\\Sinimage\\Quest\\PumpkinEvent.sin";//ȣ�� ��ƿ��� �̺�Ʈ
//����� - ������ ��ƿ���
char *StarDoc = "image\\Sinimage\\Quest\\StarEvent.sin";//����� - ���ϴ��� �ҿ� �̺�Ʈ
//�庰 - �߷�Ÿ�� ���ݸ� ��ƿ���
char *ValentineDoc = "image\\Sinimage\\Quest\\ChocolateEvent.sin"; //�߷�Ÿ�� ���ݸ� ��ƿ��� �̺�Ʈ
// ����� - ���ĺ� ���� �̺�Ʈ
char *PristonAlphabetDoc = "image\\Sinimage\\Quest\\Priston.sin"; // ����� - ���ĺ� ���� �̺�Ʈ
// �庰 - ĵ������
char *CandydaysDoc = "image\\Sinimage\\Quest\\CandydaysEvent.sin"; // ĵ�� ��ƿ��� �̺�Ʈ
// �庰 - �����ñ׸�
char *MagicalGreenDoc = "image\\Sinimage\\Quest\\MagicalGreenEvent.sin"; 
// �庰 - ī���� ����
char *TearOfKaraDoc = "image\\Sinimage\\Quest\\KarasTears.sin"; 

// �庰 - ������� ã�ƶ�
char *Findinvestigator1_1Doc = "image\\Sinimage\\Quest\\Resercher_Start.sin"; 
char *Findinvestigator1_2Doc = "image\\Sinimage\\Quest\\Resercher_Pass1.sin"; 
char *Findinvestigator1_3Doc = "image\\Sinimage\\Quest\\Resercher_Pass2.sin"; 
char *Findinvestigator2_1Doc = "image\\Sinimage\\Quest\\Kamiyu_Start.sin"; 
char *Findinvestigator2_2Doc = "image\\Sinimage\\Quest\\Kamiyu_Pass.sin"; 
char *Findinvestigator3_1Doc = "image\\Sinimage\\Quest\\Eto_Start.sin"; 
char *Findinvestigator3_2Doc = "image\\Sinimage\\Quest\\Eto_Pass.sin"; 

char *LevelQuest30Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest30start.sin",
	"image\\Sinimage\\Quest\\LevelQuest30Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest30end.sin",

};
char *LevelQuest55Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest55start.sin",
	"image\\Sinimage\\Quest\\LevelQuest55Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest55end.sin",

};

char *LevelQuest55_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest55-2start.sin",
	"image\\Sinimage\\Quest\\LevelQuest55-2Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest55-2end.sin",

};

char *LevelQuest70Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest70start.sin",
	"image\\Sinimage\\Quest\\LevelQuest70Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest70end.sin",

};
char *LevelQuest80Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest80start.sin",
	"image\\Sinimage\\Quest\\LevelQuest80Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest80end.sin",

};
char *LevelQuest85Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest85start.sin",
	"image\\Sinimage\\Quest\\LevelQuest85Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest85Path2.sin",
	"image\\Sinimage\\Quest\\LevelQuest85end.sin",

};
char *LevelQuest90Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest90start.sin",
	"image\\Sinimage\\Quest\\LevelQuest90Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest90end.sin",

};

char *LevelQuest80_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest80_2start.sin",
	"image\\Sinimage\\Quest\\LevelQuest80_2start2.sin",
	"image\\Sinimage\\Quest\\LevelQuest80_2Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest80_2Path2.sin",
	"image\\Sinimage\\Quest\\LevelQuest80_2end.sin",

};

char *LevelQuest90_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest90_2start.sin",
	"image\\Sinimage\\Quest\\LevelQuest90_2start2.sin",
	"image\\Sinimage\\Quest\\LevelQuest90_2Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest90_2Path2.sin",
	"image\\Sinimage\\Quest\\LevelQuest90_2end.sin",

};

char *QuestFilePath4[] ={
	"image\\Sinimage\\Quest\\ChangeJob4_1Start.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_1Path.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_2Start.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_2Path.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_3Start.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_3Path.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_4Start.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_4End.sin",

};


/*----------------------------------------------------------------------------*
*					������ �Ҽ��ִ����� üũ�Ѵ�
*-----------------------------------------------------------------------------*/	
int sinCheckChageJob() { return TRUE; }

/*----------------------------------------------------------------------------*
*					����Ʈ ����Ÿ�� �ε��Ѵ� 
*-----------------------------------------------------------------------------*/	
int sinLoadQuest(int CODE ,void *Buff ) { return TRUE; }

/*----------------------------------------------------------------------------*
*					����Ʈ ����Ÿ�� �����Ѵ� 
*-----------------------------------------------------------------------------*/	
int sinSaveQuest(void *Buff ) { return TRUE; }

/*----------------------------------------------------------------------------*
*					����Ʈ�� NPC�� ��縦 �����ش� 
*-----------------------------------------------------------------------------*/	
int sinMorayionNpcChangeJob_Two() { return TRUE; }
/*----------------------------------------------------------------------------*
*				����Ʈ�� NPC�� ��縦 �����ְ� �������� ó���Ѵ� (3������)
*-----------------------------------------------------------------------------*/	
int sinNpcChangeJob3() { return TRUE; }


//�ڵ�� �������� �����Ѵ�(����Ʈ�����۸� ����� �ٸ��� ����� �ȵ�)
int DeleteQuestItem(DWORD CODE)
{
	sITEM *pItem=0;
	int i = 0;
	for( i = 0; i < INVENTORY_MAXITEM*2 ; i++){
		if(i<100){
			if(!cInvenTory.InvenItem[i].Flag)continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else{
			if(!cInvenTory.InvenItemTemp[i-100].Flag)continue;
			pItem = &cInvenTory.InvenItemTemp[i-100];
		}
		
		if(pItem->sItemInfo.CODE == CODE){
			pItem->Flag = 0;
			if(i<100){
				if(pItem->ItemPosition){
					sInven[pItem->ItemPosition-1].ItemIndex = 0;
					if(pItem->SetModelPosi)
						sinSetCharItem(pItem->CODE , pItem->SetModelPosi, FALSE); 

				}
			}
		}
	}
	cInvenTory.ReFormInvenItem();
	ReformCharForm();//������ 
	cInvenTory.ReFormPotionNum();
	cInvenTory.SetItemToChar();
	cInvenTory.CheckWeight();
	return TRUE;
}
/*----------------------------------------------------------------------------*
*					3�� ���� ������ üũ & ����
*-----------------------------------------------------------------------------*/	
int  QuestMonsterCount[] = {30,40,50,25,35,45,50,70,100};
int CheckChangeJob3QuestItem(DWORD Monster_CODE) { return TRUE; }
int SetChangeJob3QuestItem(sITEMINFO *pItem,int Down)
{

	int Temp =0;
	float fTemp = 0;
	if(pItem->ItemAgingNum[0] > 3)return FALSE; //3�������� �Ҽ��ִ�

	switch(pItem->CODE&sinITEM_MASK2){
		case sinWA1: 
		case sinWC1:
		case sinWP1:
		case sinWS2:
			if(Down){
				//pItem->Attack_Speed -=2;
				/*
				Temp = GetRandomPos(2,4);
				pItem->Damage[0] -=Temp;
				pItem->Damage[1] -=Temp;
				Temp = GetRandomPos(15,20);
				pItem->Attack_Rating -=Temp;
				*/

			}
			else{
				if(pItem->ItemAgingNum[0]){
					pItem->fIncrease_Life += 4;
					Temp = GetRandomPos(1,2);
					pItem->Damage[0] +=Temp;
					pItem->Damage[1] +=Temp;
					Temp = GetRandomPos(10,15);
					pItem->Attack_Rating +=Temp;
					pItem->ItemKindMask = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX |SIN_ADD_ATTACK_RATE |SIN_ADD_LIFE;
				}
				pItem->ItemAgingNum[1] = pItem->ItemAgingNum[0];
				pItem->ItemAgingCount[1] = QuestMonsterCount[pItem->ItemAgingNum[1]]; //�ִ�ġ ����
				pItem->ItemAgingNum[0]++; //������
				
			}
		break;
		case sinWS1:
		case sinWT1:
			if(Down){
				//pItem->Attack_Speed -=2;
				/*
				Temp = GetRandomPos(2,4);
				pItem->Damage[0] -=Temp;
				pItem->Damage[1] -=Temp;
				Temp = GetRandomPos(15,20);
				pItem->Attack_Rating -=Temp;
				*/

			}
			else{
				if(pItem->ItemAgingNum[0]){
					pItem->fIncrease_Life += 4;
					Temp = GetRandomPos(1,2);
					pItem->Damage[0] +=Temp;
					pItem->Damage[1] +=Temp;
					Temp = GetRandomPos(10,15);
					pItem->Attack_Rating +=Temp;
					pItem->ItemKindMask = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX |SIN_ADD_ATTACK_RATE |SIN_ADD_LIFE;
				}

				pItem->ItemAgingNum[1] = 3+pItem->ItemAgingNum[0];
				pItem->ItemAgingCount[1] = QuestMonsterCount[pItem->ItemAgingNum[1]]; //�ִ�ġ ����
				pItem->ItemAgingNum[0]++; //������
				
			}
		break;
		case sinWM1:
			if(Down){
				//pItem->Attack_Speed -=2;
				/*
				Temp = GetRandomPos(2,4);
				pItem->Damage[0] -=Temp;
				pItem->Damage[1] -=Temp;
				Temp = GetRandomPos(4,8);
				fTemp = (float)Temp/10.0f;
				pItem->fMana_Regen -= fTemp;
				*/

			}
			else{
				if(pItem->ItemAgingNum[0]){
					pItem->fIncrease_Life += 4;
					Temp = GetRandomPos(1,2);
					pItem->Damage[0] +=Temp;
					pItem->Damage[1] +=Temp;
					Temp = GetRandomPos(3,6);
					fTemp = (float)Temp/10.0f;
					pItem->fMana_Regen += fTemp;
					pItem->ItemKindMask = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX |SIN_ADD_MANAREGEN |SIN_ADD_LIFE;

				}
				pItem->ItemAgingNum[1] = 6+pItem->ItemAgingNum[0];
				pItem->ItemAgingCount[1] = QuestMonsterCount[pItem->ItemAgingNum[1]]; //�ִ�ġ ����
				pItem->ItemAgingNum[0]++; //������
				
			}
		break;
	}
	//�ѹ��� �����̵ǰ� (����¡ ������� �ö󰣰� �������� ����������Ѵ�)
	pItem->ItemAgingCount[0] = pItem->ItemAgingCount[1]; //0���� ��ĥ���ִ�
	ReformItem(pItem);  //������ ���� �ޱ� 
	return TRUE;
}

int CheckQuestItemDownFlag = 0;
//3�������� ���������� üũ�Ѵ�
int CheckChangeJob_QuestItem()
{

	int ItemIndex = 0;
	sITEM *pTempItem = 0; 
	///////////�ð��� üũ�ؼ� �������� ���ش�
	if(sinQuest_ChangeJob3.CODE && sinQuest_ChangeJob3.State == 5 && sinChar->ChangeJob ==2){ 
		while(1){
			ItemIndex = cInvenTory.SearchItemIndex(0,ITEM_KIND_QUEST_WEAPON);
			if(ItemIndex){
				if(ItemIndex < 100) //5�ϰ���� �����
					pTempItem = &cInvenTory.InvenItem[ItemIndex-1];
				else pTempItem = &cInvenTory.InvenItemTemp[(ItemIndex-100)-1];

				if(sinItemTime > pTempItem->sItemInfo.dwCreateTime +(60*60*24*5) ){
				//if(sinItemTime > pTempItem->sItemInfo.dwCreateTime +(60*3) ){ //�׽�Ʈ�� ���� 30��
					//���� ���⸦ ���� ���ش�
					cInvenTory.DeleteInvenItemToServer(pTempItem->sItemInfo.CODE,
						pTempItem->sItemInfo.ItemHeader.Head,pTempItem->sItemInfo.ItemHeader.dwChkSum);
					DeleteQuestItem(sinOR2|sin02);
					DeleteQuestItem(sinOR2|sin03);
					DeleteQuestItem(sinOR2|sin04);

					//���콺 �����۵� üũ�Ѵ�
					if(MouseItem.Flag && MouseItem.sItemInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON){
							cInvenTory.DeleteInvenItemToServer(MouseItem.sItemInfo.CODE,
								MouseItem.sItemInfo.ItemHeader.Head,MouseItem.sItemInfo.ItemHeader.dwChkSum);
					}
				}
				else break;
			}
			else break;
			
		}
	}


	ItemIndex = 0;
	////////��⼭�� �̳��� ����Ʈ�� ���ϰ� �������ߴ��� Ȯ���Ѵ�
	if(sinQuest_ChangeJob3.CODE && !CheckQuestItemDownFlag){
		ItemIndex = cInvenTory.SearchItemIndex(0,ITEM_KIND_QUEST_WEAPON);
		if(ItemIndex){
			if(sinChar->Level > sinQuest_ChangeJob3.StartLevel+2){
				sinQuest_ChangeJob3.StartLevel  = sinChar->Level;
				CheckQuestItemDownFlag = 1;
			}
		}
	}

	if(sinChar->ChangeJob >= 1 ){
		DeleteQuestItem((sinQT1|sin01)); //���ʿ��� ����Ʈ �������� �����ش�
		DeleteQuestItem((sinQT1|sin02));
		DeleteQuestItem((sinQT1|sin03));
		DeleteQuestItem((sinQT1|sin04));
		DeleteQuestItem((sinQT1|sin05));
	}
	if(sinChar->ChangeJob >= 2 && !sinQuest_ChangeJob3.CODE){ //���� ������ ������� �����ش�
		DeleteQuestItem((sinQT1|sin06));
		DeleteQuestItem(sinOR2|sin02);
		DeleteQuestItem(sinOR2|sin03);
		DeleteQuestItem(sinOR2|sin04);

	}
	return TRUE;
}



/*----------------------------------------------------------------------------*
*					���� ����Ʈ
*-----------------------------------------------------------------------------*/	
/*
#define SIN_QUEST_CODE_LEVEL30			0x0005
#define SIN_QUEST_CODE_LEVEL55			0x0006
#define SIN_QUEST_CODE_LEVEL70			0x0007
#define SIN_QUEST_CODE_LEVEL80			0x0008

sQUEST_CHANGEJOB3   sinQuest_Level30;
sQUEST_CHANGEJOB3   sinQuest_Level55;
sQUEST_CHANGEJOB3   sinQuest_Level55_2;
sQUEST_CHANGEJOB3   sinQuest_Level70;
sQUEST_CHANGEJOB3   sinQuest_Level80;
*/

//����Ʈ�� �������ִ��� üũ�Ѵ�
int sinCheckLevelQuest30() { return TRUE; }

//����Ʈ�� �������ִ��� üũ�Ѵ�
int sinCheckLevelQuest55() { return TRUE; }

//����Ʈ�� �������ִ��� üũ�Ѵ�
int sinCheckLevelQuest55_2() { return TRUE; }


//����Ʈ�� �������ִ��� üũ�Ѵ�
int sinCheckLevelQuest70() { return TRUE; }

//����Ʈ�� �������ִ��� üũ�Ѵ�
int sinCheckLevelQuest80() { return TRUE; }

//����Ʈ�� �������ִ��� üũ�Ѵ�
int sinCheckLevelQuest85() { return TRUE; }

int sinCheckQuest85Die() { return TRUE; }

//����Ʈ�� �������ִ��� üũ�Ѵ�
int sinCheckLevelQuest90() { return TRUE; }

//����Ʈ�� �������ִ��� üũ�Ѵ�
int sinCheckLevelQuest80_2(int NpcNum) { return TRUE; }

int sinCheckLevelQuest80_2Item()
{
	if(cInvenTory.SearchItemCode(sinQT1|sin09) &&
		cInvenTory.SearchItemCode(sinQT1|sin10) &&
		cInvenTory.SearchItemCode(sinQT1|sin11))
		return TRUE;
	return FALSE;
}
//������ �����ڵ带 ������
int sinSetSendItem80_2()	
{
	sITEM *pItem=0;  
	int   Count = 0;
	int   i = 0;
	int   TempItemIndex[3] = {0,0,0};
	short TempItemIndex2[4] = {0,};
	memset(&sWingItem_Send,0,sizeof(sCRAFTITEM_SERVER)); //�ʱ�ȭ
	for( i = 0; i < INVENTORY_MAXITEM*2 ; i++){
		if(i<100){
			if(!cInvenTory.InvenItem[i].Flag)continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else{
			if(!cInvenTory.InvenItemTemp[i-100].Flag)continue;
			pItem = &cInvenTory.InvenItemTemp[i-100];
		}
		//���⼭�� �ϴ� ���Ҹ��� üũ�Ѵ�
		switch(pItem->sItemInfo.CODE){
			case (sinQT1|sin09):
				if(sWingItem_Send.SheltomCode[0])break;
				sWingItem_Send.SheltomCode[0] =  pItem->sItemInfo.CODE;
				sWingItem_Send.Head[0] =  pItem->sItemInfo.ItemHeader.Head;
				sWingItem_Send.CheckSum[0] =  pItem->sItemInfo.ItemHeader.dwChkSum;
			break;
			case (sinQT1|sin10):
				if(sWingItem_Send.SheltomCode[1])break;
				sWingItem_Send.SheltomCode[1] =  pItem->sItemInfo.CODE;
				sWingItem_Send.Head[1] =  pItem->sItemInfo.ItemHeader.Head;
				sWingItem_Send.CheckSum[1] =  pItem->sItemInfo.ItemHeader.dwChkSum;

			break;
			case (sinQT1|sin11):
				if(sWingItem_Send.SheltomCode[2])break;
				sWingItem_Send.SheltomCode[2] =  pItem->sItemInfo.CODE;
				sWingItem_Send.Head[2] =  pItem->sItemInfo.ItemHeader.Head;
				sWingItem_Send.CheckSum[2] =  pItem->sItemInfo.ItemHeader.dwChkSum;

			break;

		}
	}
	return TRUE;
}

//���� +10 90����Ʈ
int sinCheckLevelQuest90_2(int NpcNum) { return TRUE; }

void *pQuestCode[] = { //void�� �����ͷ� �迭�� ��´� 
  &sinQuest_ChangeJob,
  &sinQuest_ChangeJob2,
  &sinQuest_ChangeJob3,
  &sinQuest_Level30,
  &sinQuest_Level55,
  &sinQuest_Level55_2,
  &sinQuest_Level70,
  &sinQuest_Level80,
  &sinQuest_Level85,
  &sinQuest_Level90,
  &sinQuest_Level80_2,
  &sinQuest_Level90_2,
  &sinQuest_ChangeJob4,
  0,
};

struct QuestCodeFlag{
	DWORD	CODE;
};

//���� �������� ����Ʈ�� �ֳ��� Ȯ���Ѵ�
int CheckNowQuestState(DWORD CODE) { return TRUE; }

//���� �������� ����Ʈ�� �ʱ�ȭ�Ѵ� (������)
int ClearNowQuest()
{
	int cnt = 0;
	while(1){
		if(pQuestCode[cnt] == 0)break;
		if(((QuestCodeFlag *)pQuestCode[cnt])->CODE){
			((QuestCodeFlag *)pQuestCode[cnt])->CODE = 0;
			return FALSE;

		}
		cnt++;
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*					4����ų ��������Ʈ
*-----------------------------------------------------------------------------*/	

int sinChangeJob4MonCode[][2] ={
	{MONSTER_MURPIN,MONSTER_SKELETON_KNIGHT },
	{MONSTER_HEAD_CUTTER,MONSTER_SOLID_SNAIL},
	{MONSTER_THORN_CROWLER,MONSTER_MUMMY},
	{MONSTER_DOOM_GUARD ,MONSTER_FIGON},
	{MONSTER_STONE_GIANT,MONSTER_STONE_COLEM},
	{MONSTER_IRON_GUARD,MONSTER_AVELLRIN},
};
int sinChangeJob4MonCode2[][2] = {
	{MONSTER_AVELRISK_L,MONSTER_BEEBUL},
	{MONSTER_ILLUSION_KNIGHT,MONSTER_NIGHT_MARE },
	{MONSTER_WITCH,MONSTER_HEAVY_GOBLIN},
	{MONSTER_DAWLIN ,MONSTER_STYGIAN},
	{MONSTER_INCUBUS,MONSTER_CHAIN_GOLEM},
	{MONSTER_DARK_SPECTOR,MONSTER_METRON},
};
int sinChangeJob4MonCode3[] = {
	MONSTER_SOLID_SNAIL,
	MONSTER_ILLUSION_KNIGHT,
	MONSTER_AVELRISK_LOAD,
	MONSTER_DUSK,
	MONSTER_CHAIN_GOLEM ,
	MONSTER_SADNESS
};



int QuestLevelTable[7] = {60,65,70,75,80,85,200};
char szQuestMonsterName[64];
int sinChangeJob4MonSet(sQUEST_CHANGEJOB3 *pQuset) { return TRUE; }
int sinCheckChangeJobQuest4() { return TRUE; }

//����Ʈ Ÿ�̸Ӹ� ǥ���Ѵ�
int sinSetQuestTimer(sQUEST_CHANGEJOB3 *pQuset , int UseTime , int CheckTime) { return TRUE; }

//npc���� ���������� �ºΰ���� �޴´�
int sinBattleNpcResult(int WinFlag) { return TRUE; }

//4����ų�� ����Key�� �����Ѵ�
int sinCompleteChangeJob4(int Index) { return TRUE; }


