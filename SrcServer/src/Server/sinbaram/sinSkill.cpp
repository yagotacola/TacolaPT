/*----------------------------------------------------------------------------*
*	���ϸ� :  sinSkill.cpp
*	�ϴ��� :  ������ ���� 
*	�ۼ��� :  ����������Ʈ 12�� 
*	������ :  �ڻ� 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"
#include "Character/skillsub.h"
#include "field.h"
#include "Character/playmain.h"
#include "Character/playsub.h"
#include "netplay.h"
#include "Character/character.h"
#include "fileread.h"

// ����� - �ν��� ������ �����Ҹ� �����ϱ� ����
/*----------------------------------------------------------------------------*
*								�������� 			
*-----------------------------------------------------------------------------*/	

cSKILL	cSkill;
sUSESKILL sinSkill;
sSKILL  *pUseSkill;			//����ϱ����� ���� �������ش� 
sSKILL  ContinueSkill[20];	//���������� ���Ǵ� ��ų 
sSKILL  TempContinueSkill[20];	//���������� ���Ǵ� ��ų 
int SkillCountTime2[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int ContinueSkillMouseIndex = 0;

JOB_DATA_CODE *sinJobList;

sSKILL *pMasterSkill;  //��ų ���� ������ 

sSKILLPASSIVE sSkillPassive; //ĳ���Ϳ� ����Ǵ� �нú� ��ų 

/////////////
int ShowSkillUpInfo = 0;     //�޼��� �ڽ��� �Բ� ��ų������ �����ش� 
int  SkillMasterOkFlag[2] = {0,0};
int  SkillMasterFlag = 0;    //NPC���� ��ų �� ������ �Ѵ� 

int SkillMasteryShowFlag = 0;		//���õ��� ǥ���Ѵ� 
char szUseSkillMastery[32];			//��ų ���õ� 
POINT UseSkillMasteryPosi = {0,0};	//���õ� ǥ�� ������ 

int MatForceOrb[12] = {0};

// ����� - ���� ���� ����
int MatBillingMagicForceOrb[3] = {0};

// ����� - �ν��� ������
int Mat_BoosterItem[9] = {0};

// �庰 - ��ų ������
int nMat_SkillDelayItem[3] = {0};

int MatQuestTimer = 0;

/////////////��ų ����  �����ֱ� 

POINT SkillUpInfo = { 13,21};       //��ų ���� �����ֱ� 
POINT SkillUpInfoPosi= { 90,100};

////////////
int     SkillInfoLineCnt = 0;

int     SkillInfoShowFlag = 0;
POINT	SkillInfoBoxPosi  = {0,0};
POINT   SkillInfoTextPosi = {0,0};
POINT   SkillBoxSize = {0,0};


char    szSkillInfoBuff[5000];
char    szSkillMasterInfoBuff[5000];

char    szSkillInfoBuff2[5000];
char    szSkillMasterInfoBuff2[5000];


int     SkillDocLineCnt[6] = {0,0,0,0,0,0};
int     SkillUseWeaponClass = 0;
int     NextSkillLevelLine = 0;
/////////////

int ShowSkillClose = 0; //�ݱ� ��ư �÷� 
int SkillButtonIndex = 0;
int Skill4ButtonIndex = 0;

int DownButtonUseShorKey = 0 ; //����Ű�� ������������ ��ų�� �������� �ʴ´� 

int DownButtonIndex  = 0;  //��ư�� ������ ȿ���� �ֱ����� �ε��� 
int LDownButtonIndex = 0;  //���� ��ư 
int RDownButtonIndex = 0;  //������ ��ư 



int ChangeJobSkillPlus = 0;
int UseSkillIndex[2] = {0,0}; //���� ������ 

int SelectInterSkill = 0;

/////////////////�̴� Define
#define	NORMAL_SKILL_INDEX		14
#define MAX_USE_SKILL_POINT		10

#define SIN_MOUSE_POSI_LEFT		1
#define SIN_MOUSE_POSI_RIGHT	2

/////////////////

///////////////// ��ų ������ 
int   SkillIconIndex[10] = {0,0,0,0,0,0,0,0,0,0};
POINT SkillIconPosi = {0,0};
int   SkillInconCnt = 0;


int GageLenght[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

DWORD ClearSkillCODE = 0; //�ʱ�ȭ�� ��ų�� �ֳ����� 
POINT ClearSkillButtonPosi = {0,0}; //��ų �ʱ�ȭ ��ư ��ġ 

int SetT_Of_ValhallaFlag = 0;
int SetT_Of_ValhallaFlag2 = 0; //���������� �÷��ϳ��� ���д�
int SetT_Of_ValhallaLV = 0;    //�������� ����

int SetH_Of_ValhallaLV = 0;    //�������� ����
int SetT_Of_ValhallaPOINT = 0; //�������� Ʈ���̾��� ���� ���Ҷ�����Ʈ
 
int MatCircleIcon = 0;

sSKILL_INFO sSkill_Info[SIN_MAX_SKILL] = {

#include "sinSkill_Info.h"

};

//��ų ���λ��� 
sSKILL sSkill[SIN_MAX_SKILL] = {
	
	//��ų �̸�            ��ų �ڵ�          �䱸����   ��ư ���ϳ��� 
	{"��־��� "		,SKILL_NORMAL_ATTACK	,"Skill_Normal",},	 		

	//////////////��ī�� �迭
	{"�ͽ�Ʈ������"		,SKILL_EXTREME_SHIELD	,"TM10 Ex_shield","Mc1_E_SHIELD.tga"},	 	
	{"��ī�й�"			,SKILL_MECHANIC_BOMB	,"TM12 M_bomb"},
	{"������ ��Ʈ����Ʈ",SKILL_POISON_ATTRIBUTE ,"TM14 P_attribute"},
	{"������ ����"		,SKILL_PHYSICAL_ABSORB	,"TM17 Ph_absorb","Mc1_P_ABSORB.tga"},

	{"���� ����Ʈ"	,SKILL_GREAT_SMASH		,"TM20 G_Smash"},
	{"�ƽø����� "		,SKILL_MAXIMIZE			,"TM23 Maximize","Mc2_MAXIMIZE.tga"},
	{"������̼�"		,SKILL_AUTOMATION		,"TM26 Automation","Mc2_AUTOMATION.tga"},
	{"����ũ"			,SKILL_SPARK			,"TM30 Spark"},

	{"��Ż �Ƹ�"		,SKILL_METAL_ARMOR		,"TM40 M_Armor","Mc3_M_ARMOR.tga"},
	{"�׷��� ���޽�"	,SKILL_GRAND_SMASH		,"TM43 Grand_Smash"},
	{"��ī�� ����"		,SKILL_MECHANIC_WEAPON	,"TM44 M_Weapon"},
	{"����Ʈ ����"		,SKILL_SPARK_SHIELD		,"TM50 S_Shield","Mc3_S_SHIELD.tga"},

	//4�� ��ų
	{"���÷��̼�"		,SKILL_IMPULSION		,"TM60 Impulsion"},
	{"���÷��̼�"		,SKILL_COMPULSION		,"TM63 Compulsion","Mc4_COMPULSION.tga"},
	{"�޳�ƽ �Ǿ�"		,SKILL_MAGNETIC_SPHERE	,"TM66 M_Sphere","Mc4_M_SPHERE.tga"},
	{"��Ż ��"		,SKILL_METAL_GOLEM		,"TM70 M_Golem","Mc4_M_GOLEM.tga"},

	////////////// ������ �迭
	{"��Ʋ �����͸�"	,SKILL_MELEE_MASTERY	,"TF10 M_mastery"},
	{"������ ��Ʈ����Ʈ",SKILL_FIRE_ATTRIBUTE	,"TF12 F_attribute"},
	{"���̺�"			,SKILL_RAVING			,"TF14 raving"},
	{"����Ʈ"			,SKILL_IMPACT			,"TF17 impact"},

	{"Ʈ���� ����Ʈ"	,SKILL_TRIPLE_IMPACT	,"TF20 T_Impact"},
	{"�η�Ʋ ����"		,SKILL_BRUTAL_SWING		,"TF23 B_Swing"},
	{"�ξ�"				,SKILL_ROAR				,"TF26 Roar"},
	{"���������� ��ũ��",SKILL_RAGE_OF_ZECRAM	,"TF30 R_Zecram"},

	{"����Ʈ���̼�"		,SKILL_CONCENTRATION	,"TF40 Concentration","Ft3_CONCENTRATION.tga"},
	{"�¡ ũ����"	,SKILL_AVANGING_CRASH	,"TF43 A_Crash"},
	{"����������"		,SKILL_SWIFT_AXE		,"TF46 S_Axe","Ft3_S_AXE.tga"},
	{"�� ũ����"		,SKILL_BONE_CRASH		,"TF50 B_Crash"},

	//4�� ��ų
	{"���丮��"		,SKILL_DETORYER		    ,"TF60 Destoryer"},
	{"����Ŀ"		    ,SKILL_BERSERKER		,"TF63 Berserker","Ft4_BERSERKER.tga"},
	{"����Ŭ�� ������ũ",SKILL_CYCLONE_STRIKE	,"TF66 C_Strike"},
	{"�ν�Ʈ �ｺ"		,SKILL_BOOST_HEALTH		,"TF70 B_Health"},

	////////////// ����ũ�� �迭 
	{"����ũ����"   	,SKILL_PIKE_WIND		,"TP10 P_wind"},
	{"���̽� ��Ʈ����Ʈ",SKILL_ICE_ATTRIBUTE	,"TP12 I_attribute"},
	{"ũ��Ƽ�� ��"		,SKILL_CRITICAL_HIT		,"TP14 Cri_hit"},
	{"����ũ����"		,SKILL_JUMPING_CRASH	,"TP17 J_Crash"},

	{"�׶�������ũ"	,SKILL_GROUND_PIKE		,"TP20 G_Pike"},
	{"����̵�"			,SKILL_TORNADO			,"TP23 Tornado"},
	{"���ݵ��潺�����͸�",SKILL_WEAPONE_DEFENCE_MASTERY	,"TP26 W_D_Mastery"},
	{"�ͽ����" 		,SKILL_EXPANSION		,"TP30 Expasion"},

	{"���� ���Ǿ�"		,SKILL_VENOM_SPEAR		,"TP40 V_Spear"},
	{"���̵���������",SKILL_VANISH        ,"TP43 Vanish","Pk3_VANISH.tga"},
	{"���������͸�"		,SKILL_CRITICAL_MASTERY	,"TP46 C_Mastery"},
	{"ü�η���" 		,SKILL_CHAIN_LANCE		,"TP50 C_Lance"},

	//4�� ��ų
	{"��ؽ� ����"		,SKILL_ASSASSIN_EYE		,"TP60 A_Eye","Pk4_A_EYE.tga"},
	{"��¡ ��Ʈ����ũ"	,SKILL_CHARGING_STRIKE	,"TP63 C_Strike"},
	{"���̱�"           ,SKILL_VAGUE	        ,"TP66 Vague","Pk4_VAGUE.tga"},
	{"���Ϳ� ������"	,SKILL_SHADOW_MASTER	,"TP70 S_Master"},

	////////////// ��ó �迭 
	{"��ī�� ȣũ"		,SKILL_SCOUT_HAWK		,"TA10 S_hawk","Ac1_S_HAWK.tga"},
	{"���� �����͸�"	,SKILL_SHOOTING_MASTERY	,"TA12 S_mastery"},
	{"���� �ַο�"		,SKILL_WIND_ARROW		,"TA14 W_arrow"},
	{"����Ʈ ����"		,SKILL_PERFECT_AIM		,"TA17 P_aim"},

	{"��½� ����"		,SKILL_DIONS_EYE		,"TA20 D_Eye"},
	{"����"				,SKILL_FALCON			,"TA23 Falcon","Ac2_FALCON.tga"},
	{"�ַο� ���극����",SKILL_ARROW_OF_RAGE	,"TA26 A_Rage"},
	{"�ƹ߶�ü"			,SKILL_AVALANCHE		,"TA30 Avalanchie"},

	{"������Ż��"		,SKILL_ELEMENTAL_SHOT	,"TA40 E_Shot"},
	{"�������"			,SKILL_GOLDEN_FALCON	,"TA43 G_Falcon","Ac3_G_FALCON.tga"},
	{"�� ��"			,SKILL_BOMB_SHOT		,"TA46 B_Shot"},
	{"�������̼�"		,SKILL_PERFORATION		,"TA50 Perforation"},

	//4�� ��ų
	{"���� �����"		  ,SKILL_RECALL_WOLVERIN	,"TA60 R_Wolverin","Ac4_R_WOLVERIN.tga"},
	{"�̺��̼� �����͸�"  ,SKILL_EVASION_MASTERY	,"TA63 E_Mastery","Ac4_E_MASTERY.tga"},
	{"�Ǵн� ��"          ,SKILL_PHOENIX_SHOT	    ,"TA66 P_Shot"},
	{"���� ���� ����"	  ,SKILL_FORCE_OF_NATURE	,"TA70 F_O_Nature","Ac4_F_O_NATURE.tga"},


	///////////////// ����Ʈ
	{"����������Ʈ"	,SKILL_SWORD_BLAST	    ,"MN10 S_Blast"},
	{"Ȧ�� �ٵ�"		,SKILL_HOLY_BODY		,"MN12 H_Body","Kt1_H_BODY.tga"},
	{"������Ʈ���̴�"	,SKILL_PHYSICAL_TRANING ,"MN14 P_Traning"},
	{"���� ũ����"   	,SKILL_DOUBLE_CRASH     ,"MN17 D_Crash"},

	{"Ȧ�� �뷯"	    ,SKILL_HOLY_VALOR       ,"MN20 H_Valor","Kt2_H_VALOR.tga"},
	{"�귣��"	        ,SKILL_BRANDISH         ,"MN23 Brandish"},
	{"�Ǿ��"	        ,SKILL_PIERCING         ,"MN26 Piercing"},
	{"�巹��ƽ ���Ǹ�"	,SKILL_DRASTIC_SPIRIT   ,"MN30 D_Spirit","Kt2_D_SPIRIT.tga"},

	{"������ �귣��"	,SKILL_SWORD_MASTERY   ,"MN40 S_Mastery"},
	{"�������Ȧ���̼�" ,SKILL_DIVINE_INHALATION,"MN43 D_Inhalation","Kt3_D_INHALATION.tga"},
	{"Ȧ����ĵ���̼�"	,SKILL_HOLY_INCANTATION ,"MN46 H_Incantation"},
	{"�׷��� ũ�ν�"	,SKILL_GRAND_CROSS		,"MN50 G_Cross"},

	//4�� ��ų
	{"������ ���� ����ƽ��"	,SKILL_SWORD_OF_JUSTICE	,"MN60 S_O_Justice"},
	{"���鸮 ����"			,SKILL_GODLY_SHIELD		,"MN63 G_Shield","Kt4_G_SHIELD.tga"},
	{"�� ����"            ,SKILL_GOD_BLESS	    ,"MN66 G_Bless","Kt4_G_BLESS.tga"},
	{"����� �Ǿ��"		,SKILL_DIVINE_PIERCING	,"MN70 D_Piercing"},
	


	///////////////// ��Ʋ��Ÿ
	{"���� ��Ʈ����ũ"	,SKILL_SHIELD_STRIKE	,"MA10 S_Strike"},
	{"�ĸ��� "			,SKILL_FARINA			,"MA12 Farina"},
	{"����׸����͸�"	,SKILL_THROWING_MASTERY ,"MA14 T_Mastery"},
	{"��� ���Ǿ�"	    ,SKILL_VIGOR_SPEAR      ,"MA17 V_Spear"},

	{"����"	            ,SKILL_WINDY            ,"MA20 Windy","At2_WINDY.tga"},
	{"Ʈ����Ʈ ���"	,SKILL_TWIST_JAVELIN    ,"MA23 T_Javelin"},
	{"�ҿ� ��Ŀ"	    ,SKILL_SOUL_SUCKER      ,"MA26 S_Sucker"},
	{"���̾� ���"	,SKILL_FIRE_JAVELIN     ,"MA30 F_Javelin"},

	{"���ø� �ں���"	,SKILL_SPLIT_JAVELIN         ,"MA40 Split_Javelin"},
	{"Ʈ���̾���������Ҷ�",SKILL_TRIUMPH_OF_VALHALLA,"MA43 T_Of_Valhalla","At3_T_O_VALHALLA.tga"},
	{"����Ʈ�����"	,SKILL_LIGHTNING_JAVELIN     ,"MA46 L_Javelin"},
	{"���� ���"		,SKILL_STORM_JAVELIN         ,"MA50 Storm_Javelin"},

	//4�� ��ų
	{"�� ���� ���Ҷ�"		,SKILL_HALL_OF_VALHALLA ,"MA60 H_O_Valhalla","At4_H_O_VALHALLA.tga"},
	{"���� ����"			,SKILL_X_RAGE		    ,"MA63 X_Rage"},
	{"���ν�Ʈ ���"      ,SKILL_FROST_JAVELIN	,"MA66 F_Javelin","At4_F_JAVELIN.tga"},
	{"��þ"					,SKILL_VENGEANCE		,"MA70 Vengeance"},


	///////////////// ������Ƽ��
	{"����"				,SKILL_HEALING			,"MP10 Healing"},
	{"Ȧ����Ʈ "		,SKILL_HOLY_BOLT		,"MP12 HolyBolt"},
	{"��Ƽ����ũ"		,SKILL_MULTISPARK		,"MP14 M_Spark"},
	{"Ȧ�����ε�"	    ,SKILL_HOLY_MIND	    ,"MP17 HolyMind"},

	{"�޵����̼�"	    ,SKILL_MEDITATION	    ,"MP20 Meditation"},
	{"����ζ���Ʈ��"	,SKILL_DIVINE_LIGHTNING ,"MP23 D_Lightning"},
	{"Ȧ�� ���÷���"	,SKILL_HOLY_REFLECTION	,"MP26 H_Reflection","Pr2_H_REFLECTION.tga"},
	{"�׷���Ʈ ����"	,SKILL_GRAND_HEALING	,"MP30 G_Healing"},

	{"��� ��"		    ,SKILL_VIGOR_BALL	    ,"MP40 V_Ball"},
	{"��������"			,SKILL_RESURRECTION		,"MP43 Resurrection"},
	{"�ͽ��ü�"			,SKILL_EXTINCTION		,"MP46 Extinction"},
	{"����� ������"	,SKILL_VIRTUAL_LIFE		,"MP50 V_Life","Pr3_V_LIFE.tga"},

	//4�� ��ų
	{"�۷��� ������ũ"	 ,SKILL_GLACIAL_SPIKE	  ,"MP60 G_Spike"},
	{"�����ʷ��̼� �ʵ�" ,SKILL_REGENERATION_FIELD,"MP63 R_Field","Pr4_R_FIELD.tga"},
	{"ü�� ����Ʈ��"     ,SKILL_CHAIN_LIGHTNING	  ,"MP66 C_Lightning"},
	{"���� �½���"		 ,SKILL_SUMMON_MUSPELL	  ,"MP70 S_Muspell","Pr4_S_MUSPELL.tga"},



	///////////////// ������
	{"����"			,SKILL_AGONY			,"MM10 Agony"},
	{"���̾Ʈ "		,SKILL_FIRE_BOLT		,"MM12 FireBolt"},
	{"���Ͼ�"			,SKILL_ZENITH			,"MM14 Zenith","Mg1_ZENITH.tga"},
	{"���̾"			,SKILL_FIRE_BALL	    ,"MM17 FireBall"},

	{"��Ż �����͸�"	,SKILL_MENTAL_MASTERY   ,"MM20 M_Mastery"},
	{"�ݷ�������"		,SKILL_WATORNADO	    ,"MM23 Watornado"},
	{"��æƮ ����"		,SKILL_ENCHANT_WEAPON	,"MM26 E_Weapon","Mg2_E_WEAPON.tga"},
	{"���巹��"			,SKILL_DEAD_RAY  	    ,"MM30 D_Ray"},

	{"������ ����"		,SKILL_ENERGY_SHIELD    ,"MM40 E_Shield","Mg3_E_SHIELD.tga"},
	{"���̾ƽ�Ʈ������"	,SKILL_DIASTROPHISM	    ,"MM43 Diastrophism"},
	{"���Ǹ� ������Ż"	,SKILL_SPIRIT_ELEMENTAL	,"MM46 S_Elemental","Mg3_S_ELEMENTAL.tga"},
	{"��̽�����"		,SKILL_DANCING_SWORD  	,"MM50 D_Sword","Mg3_D_SWORD.tga"},

	//4�� ��ų
	{"���̾� ������Ż"	,SKILL_FIRE_ELEMENTAL	,"MM60 F_Elemental","Mg4_F_ELEMENTAL.tga"},
	{"�ö��� ���̺�"    ,SKILL_FLAME_WAVE		,"MM63 F_Wave"},
	{"��Ʈ�ϼ�"       ,SKILL_DISTORTION	    ,"MM66 Distortion","Mg4_DISTORTION.tga"},
	{"���׿�"		    ,SKILL_M_METEO		    ,"MM70 Meteo"},
		
	//������ Ŭ�� ��ų
	{"����� ���"	    ,CLANSKILL_ABSORB	 ,"","wa1-1.tga"},
	{"���ݷ� ���"      ,CLANSKILL_ATTACK	 ,"","wa1-3.tga"},
	{"ȸ���� ���"      ,CLANSKILL_EVASION	 ,"","wa1-2.tga"},

	//������ ������ ��ų
	{"��Ÿ���þ�"			 ,SCROLL_INVULNERABILITY	 ,"","S_Ath.tga"},
	{"���鸮 ����"			 ,SCROLL_CRITICAL            ,"","S_Dea.tga"},
	{"��� ���� �̺��̵�"	 ,SCROLL_EVASION	         ,"","S_Eva.tga"},
	{"�����̾� ����"		 ,STONE_R_FIRECRYTAL	     ,"","F_C_M.tga"},
	{"�����̾� ����"		 ,STONE_R_ICECRYTAL	         ,"","I_C_M.tga"},
	{"�����̾� ����"	     ,STONE_R_LINGHTINGCRYTAL    ,"","L_C_M.tga"},
	{"����Ʈ ����"			 ,STONE_A_FIGHTER		     ,"","Ft_R.tga"},
	{"����Ʈ ����"			 ,STONE_A_MECHANICIAN	     ,"","Mc_R.tga"},
	{"����Ʈ ����"			 ,STONE_A_PIKEMAN		     ,"","Pk_R.tga"},
	{"����Ʈ ����"	         ,STONE_A_ARCHER			 ,"","Ac_R.tga"},
	{"����Ʈ ����"           ,STONE_A_KNIGHT			 ,"","Kt_R.tga"},
	{"����Ʈ ����"           ,STONE_A_ATALANTA		     ,"","At_R.tga"},
	{"����Ʈ ����"           ,STONE_A_MAGICIAN		     ,"","Mg_R.tga"},
	{"����Ʈ ����"           ,STONE_A_PRIESTESS		     ,"","Pt_R.tga"},

	{"���ͳ� ������"	     ,SCROLL_P_INVULNERABILITY	 ,"","S_Ath.tga"},
	{"����Ʋ ����"			 ,SCROLL_P_CRITICAL          ,"","S_Dea.tga"},
	{"���Ʈ ��ũ��"	     ,SCROLL_P_EVASION	         ,"","S_Eva.tga"},

	// ����� - �ν��� ������(�����, ���, �ٷ�)
	{"����� �ν���",		BOOSTER_ITEM_LIFE,			"",		"Booster_01.tga"},
	{"��� �ν���",			BOOSTER_ITEM_MANA,			"",		"Booster_02.tga"},
	{"�ٷ� �ν���",			BOOSTER_ITEM_STAMINA,		"",		"Booster_03.tga"},

	// �庰 - ��ų ������
	{"��ų ������",			SKILLDELAY_ITEM_LIFE,			"",		"Booster_01.tga"},

};


//��ų â �ڽ� ��ġ ���� 
sSKILLBOX	sSkillBox[SIN_MAX_SKILLBOX] = {
	{{142,537,142+49,537+46}},							//�븻 

	{{27-10,502,27+49-10,502+46},{27+47-10,502+5,27+47+5-10,502+40}},		//1�ܰ�
	{{67-10,546,67+49-10,546+46},{67+47-10,546+5,67+47+5-10,546+40}},
	{{77-10,466,77+49-10,466+46},{77+47-10,466+5,77+47+5-10,466+40}},
	{{137-10,476,137+49-10,476+46},{137+47-10,476+5,137+47+5-10,476+40}},

	{{212-15,466,212+49-15,466+46},{212+47-15,466+5,212+47+5-15,466+40}},	//2�ܰ�
	{{232-15,516,232+49-15,516+46},{232+47-15,516+5,232+47+5-15,516+40}},
	{{272-15,466,272+49-15,466+46},{272+47-15,466+5,272+47+5-15,466+40}},
	{{332,466,332+49,466+46},{332+47,466+5,332+47+5,466+40}},

	{{402,476,402+49, 476+46},{402+47,476+5,402+47+5,476+40}},	//3�ܰ�
	{{472,456,472+49, 456+46},{472+47,456+5,472+47+5,456+40}},
	{{512,506,512+49, 506+46},{512+47,506+5,512+47+5,506+40}},
	{{532,456,532+49, 456+46},{532+47,456+5,532+47+5,456+40}},

	{{602,481,602+49, 481+46},{602+47,481+5,602+47+5,481+40}},	//4�ܰ�
	{{662,511,662+49, 511+46},{662+47,511+5,662+47+5,511+40}},
	{{681,461,681+49, 461+46},{681+47,461+5,681+47+5,461+40}},
	{{722,511,722+49, 511+46},{722+47,511+5,722+47+5,511+40}},


};

sSKILLBOX sLeftRightSkill[2] = {
	{{349,541,349+49,541+46},{349,558,349+5,558+35}},  //��ų ���� 
	{{401+2,541,401+49,541+46},{446,558,446+5,558+35}},  //��ų ������ 

};

int SkillTitle[4][2] = {
	{85,438-4},
	{280,438-4},
	{470,438-9},
	{675,438-4},

};
//��ų ����=======================================
void*	lpSkillMain;
void*	lpSkillMain2; //��ų ����2
//��ų ���ι�ư
void*    lpSkillMainLeftB;
void*    lpSkillMainRightB;

int SkillMain2OpenFlag   = 0;        //��ų ���� flag
int SkillMain2ButtonFlag[2] = {0,0};
//================================================


//4�� ��ų ������flag
int Skill4MasterFlag=0;




int MonsterDamageLine = 0;
int ChainDamageLine   = 0;
int MatSkillIconBackGround   = 0;
/*----------------------------------------------------------------------------*
*							Ŭ���� �ʱ�, ���� 
*-----------------------------------------------------------------------------*/	
cSKILL::cSKILL()
{
	memset(&ContinueSkill,0,sizeof(sSKILL)*10); //���� ��뽺ų �ʱ�ȭ 

}
cSKILL::~cSKILL()
{

}
/*----------------------------------------------------------------------------*
*							     �ʱ�ȭ 
*-----------------------------------------------------------------------------*/	
void cSKILL::Init() {}
/*----------------------------------------------------------------------------*
*						    Bmp������ �ε��Ѵ� 
*-----------------------------------------------------------------------------*/	
void cSKILL::Load() {}

//��ų�̹����� �ε��Ѵ� 
void cSKILL::LoadUseSkillImage() {}

/*----------------------------------------------------------------------------*
*						     Release
*-----------------------------------------------------------------------------*/	
void cSKILL::Release() {}
/*----------------------------------------------------------------------------*
*							     �׸���  
*-----------------------------------------------------------------------------*/	
int CheckVirtualLifeTime = 0;
int CheckBoosterLifeTime = 0; // ����� - �ν��� ������(�����)
int CheckVirtualManaTime = 0; // ����� - �ν��� ������(���)
int CheckVirtualStaminaTime = 0; // ����� - �ν��� ������(�ٷ�)
int CheckSkillDelayTime = 0; // �庰 - ��ų ������
void cSKILL::DrawUp() {}
void cSKILL::Draw() {}
/*----------------------------------------------------------------------------*
*							     ����  
*-----------------------------------------------------------------------------*/	
void cSKILL::Main() {}
/*----------------------------------------------------------------------------*
*							     ���� 
*-----------------------------------------------------------------------------*/	
void cSKILL::Close()
{

}
/*----------------------------------------------------------------------------*
*							   LButtonDown
*-----------------------------------------------------------------------------*/	
void cSKILL::LButtonDown(int x , int y){}
/*----------------------------------------------------------------------------*
*							   LButtonUp
*-----------------------------------------------------------------------------*/	
void cSKILL::LButtonUp(int x, int y) {}
/*----------------------------------------------------------------------------*
*							   RButtonDown
*-----------------------------------------------------------------------------*/	
void cSKILL::RButtonDown(int x, int y) {}
/*----------------------------------------------------------------------------*
*							   RButtonUp
*-----------------------------------------------------------------------------*/	
void cSKILL::RButtonUp(int x, int y) {}
/*----------------------------------------------------------------------------*
*							    KeyDown
*-----------------------------------------------------------------------------*/	
void cSKILL::KeyDown() {}


//����� ��ų�� ã�´� 
int cSKILL::SearchUseSkill()
{

	switch(sinChar->JOB_CODE){  
		case 1:
			UseSkillBox = GROUP_FIGHTER;

		break;
		case 2:
			UseSkillBox = GROUP_MECHANICIAN;

		break;
		case 3:
			UseSkillBox = GROUP_ARCHER;

		break;
		case 4:
			UseSkillBox = GROUP_PIKEMAN;

		break;
		case 5:
			UseSkillBox = GROUP_ATALANTA;
		break;
		case 6:
			UseSkillBox = GROUP_KNIGHT;
		break;
		case 7:
			UseSkillBox = GROUP_MAGICIAN;
		break;
		case 8:
			UseSkillBox = GROUP_PRIESTESS;
		break;

	}
	if(!UseSkillBox)
		return FALSE;

	int Index = 0;
	memcpy(&sinSkill.UseSkill[0],&sSkill[0],sizeof(sSKILL));
	sinSkill.UseSkill[0].Flag = 1; //�븻 ���� default���� 
	sinSkill.UseSkill[0].Use  = 1; //�븻 ���� default���� 
	sinSkill.UseSkill[0].Skill_Info.USECODE = SIN_SKILL_USE_ALL;  //�븻 ���� �������� 
	sinSkill.UseSkill[0].Point = 1;

	for(int i=0;i<SIN_MAX_SKILL;i++){
		if(	(sSkill[i].CODE & sinSKILL_MASK1) == UseSkillBox ){ //�ڽſ� �´� ��ų�� ã�´� 
			for(int j=1;j < SIN_MAX_USE_SKILL; j++){
				if(!sinSkill.UseSkill[j].Flag){
					memcpy(&sinSkill.UseSkill[j],&sSkill[i],sizeof(sSKILL));
					for(int k=0; k < SIN_MAX_SKILL ; k++){
						if(sinSkill.UseSkill[j].CODE == sSkill_Info[k].CODE){
							memcpy(&sinSkill.UseSkill[j].Skill_Info,&sSkill_Info[k],sizeof(sSKILL_INFO));
							sinSkill.UseSkill[j].Skill_Info.SkillNum = j-1;
							break;
						}
					}
					sinSkill.UseSkill[j].Flag = 1;
					
					////////////TEST �� ���ؼ� ����Ʈ1�� �ش� 
					//sinSkill.UseSkill[j].Point = 1;

					break;
				}
			}
		}
	}
	memcpy(&sinSkill.SkillBox,&sSkillBox,sizeof(sSKILLBOX)*SIN_MAX_USE_SKILL); //��ǥ�� �����Ѵ� 

	LoadUseSkillImage(); //��ų�̹����� �ε��Ѵ� (������ �Ҷ��� �ε����ش� )

	sinSkill.UseSkill[0].Use  = 1; //�븻 ���� default���� 
	sinSkill.UseSkill[0].Skill_Info.USECODE = SIN_SKILL_USE_ALL;  //�븻 ���� �������� 
	sinSkill.UseSkill[0].Point = 1;
	ReFormCharSkillInfo(); //��ų������ �����Ѵ� (��ŷ����)
	return FALSE;
}

void cSKILL::DrawSkillText() {}

int JobSkillTemp = 0;
//���� ��ų�� ���¸� �˻��Ѵ� 
void cSKILL::CheckingNowSkillState()
{

	//�븻��ų�� ������ 4,4,4,4
	switch(sinChar->ChangeJob){
	case 0:
		ChangeJobSkillPlus = 5;
	break;
	case 1:
		ChangeJobSkillPlus = 9;
	break;
	case 2:
		ChangeJobSkillPlus = 13;
	break;
	case 3:
		ChangeJobSkillPlus = 17;
	break;

	}
	if(JobSkillTemp != ChangeJobSkillPlus){	//��������Ÿ�� ���߿� ���ͼ� ��ġ�� �������� �����ߴ�  ������ 
		JobSkillTemp = ChangeJobSkillPlus;
		cInvenTory.SetItemToChar();
	}

	for(int j = 0 ; j < ChangeJobSkillPlus ; j ++){  
		if(j>12){
			if(sinSkill.SkillPoint4){ //4����ų ����Ʈ�� ������쿡�� Ȱ��ȭ ��Ų�� 
				sinSkill.UseSkill[j].Flag = 1; //����Ҽ��ִ� ��ų�� �߰��Ѵ� 
				if(sinSkill.UseSkill[j].Point <= MAX_USE_SKILL_POINT){ 
					if(sinSkill.UseSkill[j-1].Point){//Ʈ���� ź�� 
						if(sinSkill.UseSkill[j].Skill_Info.RequireLevel+(sinSkill.UseSkill[j].Point*2) <= sinChar->Level) //��ų�� ����Ҽ��ִ� �������� �Ǵ� 
							sinSkill.UseSkill[j].Use = 1;
						else
							sinSkill.UseSkill[j].Use = 0;
					}
				}
			}
			else{ //�������� �ٽ� ��Ȱ��ȭ 
				sinSkill.UseSkill[j].Use = 0;
			}
			continue;
		}
		if(sinSkill.SkillPoint){ //��ų ����Ʈ�� ������쿡�� Ȱ��ȭ ��Ų�� 
			sinSkill.UseSkill[j].Flag = 1; //����Ҽ��ִ� ��ų�� �߰��Ѵ� 
			if(sinSkill.UseSkill[j].Point <= MAX_USE_SKILL_POINT){
				if(j==0)continue; //�븻 ��ų 
				if(sinSkill.UseSkill[j-1].Point){//Ʈ���� ź�� 
					if(sinSkill.UseSkill[j].Skill_Info.RequireLevel+(sinSkill.UseSkill[j].Point*2) <= sinChar->Level) //��ų�� ����Ҽ��ִ� �������� �Ǵ� 
						sinSkill.UseSkill[j].Use = 1;
					else
						sinSkill.UseSkill[j].Use = 0;
				}
			}
		}
		else{ //�������� �ٽ� ��Ȱ��ȭ 
				sinSkill.UseSkill[j].Use = 0;
		}
	}
}



//�����͸��� �����Ѵ� 
void cSKILL::CheckSkillMastery()
{
	
	int TempLenght = 0; 
	
	int TempTalent = 0;
	

	//���� ��ų���� üũ�Ѵ� 
	if(sinSkill.pLeftSkill){
		if(!sinSkill.pLeftSkill->Point)
			sinSkill.pLeftSkill->UseSkillFlag = 0;
	}
	if(sinSkill.pRightSkill){
		if(!sinSkill.pRightSkill->Point)
			sinSkill.pRightSkill->UseSkillFlag = 0;
	}

	for(int j=1;j < SIN_MAX_USE_SKILL; j++){ 
		if(sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point ){

			CheckSkillMasteryForm(0,j); //��ų �����͸��� üũ�Ѵ�

			if(sinSkill.UseSkill[j].Mastery == 0){
				sinSkill.UseSkill[j].GageLength = 0; //��ų ����
				sinSkill.UseSkill[j].GageLength2 = 0; //��ų ����
				SkillCountTime2[j] = 0;

			}

			//���� �ö󰡴� ���õ� 
			TempTalent = (int)(sinChar->Talent/3)+(int)sinAdd_fMagic_Mastery; 
			if(TempTalent > 50 )TempTalent = 50;
			sinSkill.UseSkill[j].UseSkillMastery =  (int)(TempTalent*100)+sinSkill.UseSkill[j].UseSkillCount;
			if(sinSkill.UseSkill[j].Skill_Info.Element[0]){ //4����ų�� ����ġ�� �����ش�
				sinSkill.UseSkill[j].UseSkillMastery = 10000;

			}

			if(sinSkill.UseSkill[j].UseSkillMastery >= 10000)sinSkill.UseSkill[j].UseSkillMastery = 10000;
			if(sinSkill.UseSkill[j].UseSkillMastery){
				sinSkill.UseSkill[j].UseSkillMasteryGage = (int)((35*((float)sinSkill.UseSkill[j].UseSkillMastery/10000)));
				if(sinSkill.UseSkill[j].UseSkillMasteryGage > 35 )sinSkill.UseSkill[j].UseSkillMasteryGage = 35;
			}
			
			sinSkill.UseSkill[j].Mastery =   (sinSkill.UseSkill[j].Skill_Info.RequireMastery[0]+ (sinSkill.UseSkill[j].Skill_Info.RequireMastery[1]*sinSkill.UseSkill[j].Point) - 
											(sinSkill.UseSkill[j].UseSkillMastery/100));
			if(sinSkill.UseSkill[j].Mastery <= 0) sinSkill.UseSkill[j].Mastery = 1; //�ּҰ� 0.5�� 
			if(sinSkill.UseSkill[j].Mastery > 70)sinSkill.UseSkill[j].Mastery = 70;

			// �庰 - ��ų ������
			if( sinAddSkillDelay )
			{
				sinSkill.UseSkill[j].Mastery = 1;
			}

			else
			{
				sinSkill.UseSkill[j].Mastery =   (sinSkill.UseSkill[j].Skill_Info.RequireMastery[0]+ (sinSkill.UseSkill[j].Skill_Info.RequireMastery[1]*sinSkill.UseSkill[j].Point) - 
											(sinSkill.UseSkill[j].UseSkillMastery/100));

				if(sinSkill.UseSkill[j].Mastery <= 0) sinSkill.UseSkill[j].Mastery = 1; //�ּҰ� 0.5�� 
				if(sinSkill.UseSkill[j].Mastery > 70)sinSkill.UseSkill[j].Mastery = 70;
			}

			//������ �� 
			TempLenght = (int)(35/((float)sinSkill.UseSkill[j].Mastery/2)); 

			sinSkill.UseSkill[j].GageLength2 += TempLenght;

			if(sinSkill.UseSkill[j].GageLength < sinSkill.UseSkill[j].GageLength2){
				SkillCountTime2[j]++;
				if(SkillCountTime2[j] >= (int)(35/(float)TempLenght)){
					sinSkill.UseSkill[j].GageLength++;
					SkillCountTime2[j] = 0;
			
				}

			}

			if(sinSkill.UseSkill[j].GageLength >=35){
				sinSkill.UseSkill[j].GageLength = 35;
				sinSkill.UseSkill[j].GageLength2 = 35;
				sinSkill.UseSkill[j].UseSkillFlag = 1;
				CheckUseSkillState(&sinSkill.UseSkill[j]); //��ų�� ����Ҽ��ִ����� üũ�Ѵ� 
				

			}
			else
				sinSkill.UseSkill[j].UseSkillFlag = 0;

			ReformSkillMasteryForm(0,j); //����Ÿ�� �����Ѵ�
				
		}
	
	}
	
	
}

DWORD UseSkillItemInfo[10] = {0,sinWA1,sinWM1,sinWH1,sinDS1,sinWP1,sinWS2,sinWC1,sinWS1,sinWT1};


int cSKILL::ShowSkillInfo(sSKILL* pSkill, sSKILLBOX* pSkillBox, int Icon) { return TRUE; }
    

int cSKILL::GetInfoBoxSize(sSKILLBOX *pSkillBox, int Col,int Icon) { return TRUE; }


//���õ��� ǥ���Ѵ� 
int cSKILL::GetSkillMastery(sSKILL *pSkill , sSKILLBOX *pSkillBox)
{
	int SkillMasteryTemp = 0;
	SkillMasteryTemp = ((int)pSkill->UseSkillMastery/100);
	wsprintf(szUseSkillMastery , "%d",SkillMasteryTemp);

	UseSkillMasteryPosi.x = pSkillBox->GageRect.left - (34/2);
	UseSkillMasteryPosi.y = pSkillBox->GageRect.top - 29;

	return TRUE;
}

//��ų�� ����Ҽ��ִ����� üũ�Ѵ� // �庰-���� ���ེ ���� ���
int cSKILL::CheckUseSkillState(sSKILL *pSkill)
{
	if(pSkill->Skill_Info.UseMana)
	{
		// �庰 - �׸� �Ӽ�
		// �庰 - �������ེ, �׸�, �ٷ¸��ེ
		if( chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1 && chaPremiumitem.m_StaminaReducePotiontime > 0 )
		{
			if(sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - ((pSkill->Skill_Info.UseMana[pSkill->Point - 1] * 
				chaPremiumitem.m_ManaReducePotionValue / 100) + (pSkill->Skill_Info.UseMana[pSkill->Point-1] * 20 / 100)) && 
				sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1]*(pSkill->Point-1)))-( (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1]*(pSkill->Point-1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
			{
				pSkill->UseSkillFlag = 1;
			}

			else
				pSkill->UseSkillFlag = 0;
		}

		// �庰 - �������ེ, �ٷ¸��ེ
		else if( chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_StaminaReducePotiontime > 0 )
		{
			if(sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * chaPremiumitem.m_ManaReducePotionValue / 100) && 
				sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1]*(pSkill->Point-1)))-( (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1]*(pSkill->Point-1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
			{
				pSkill->UseSkillFlag = 1;
			}
			else
				pSkill->UseSkillFlag = 0;
		}

		// �庰 - �׸�, �ٷ¸��ེ
		else if( chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1 && chaPremiumitem.m_StaminaReducePotiontime > 0 )
		{
			if(sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * 20 / 100) && 
				sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1]*(pSkill->Point-1)))-( (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1]*(pSkill->Point-1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
			{
				pSkill->UseSkillFlag = 1;
			}
			else
				pSkill->UseSkillFlag = 0;
		}

		// �庰 - �������ེ
		else if( chaPremiumitem.m_ManaReducePotiontime > 0)
		{
			if(sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * chaPremiumitem.m_ManaReducePotionValue / 100) && 
				sinGetStamina() >= pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1]*(pSkill->Point-1)))
			{
				pSkill->UseSkillFlag = 1;
			}
			else
				pSkill->UseSkillFlag = 0;
		}

		// �庰 - �׸�
		else if( chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		{
			if(sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * 20 / 100) && 
				sinGetStamina() >= pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1]*(pSkill->Point-1)))
			{
				pSkill->UseSkillFlag = 1;
			}
			else
				pSkill->UseSkillFlag = 0;
		}

		// �庰 - �ٷ¸��ེ
		else if( chaPremiumitem.m_StaminaReducePotiontime > 0)
		{
			if(sinGetMana() >=  pSkill->Skill_Info.UseMana[pSkill->Point - 1] &&
				sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1]*(pSkill->Point-1)))-( (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1]*(pSkill->Point-1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
			{
				pSkill->UseSkillFlag = 1;

			}
			else
				pSkill->UseSkillFlag = 0;
		}

		// ������ ��� ���ߴ�
		else 
		{
			if(sinGetMana() >=  pSkill->Skill_Info.UseMana[pSkill->Point - 1] &&
				sinGetStamina() >= pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1]*(pSkill->Point-1)))
			{
				pSkill->UseSkillFlag = 1;

			}
			else
				pSkill->UseSkillFlag = 0;
		}
	}
	return TRUE;
}


int SkillDataCheckDelayTime = 0;
int SkillDataCheckFlag2 = 0;


int cSKILL::CheckSkillData()
{
	SkillDataCheckDelayTime++;
	if (SkillDataCheckDelayTime < 70 * 10)return FALSE;
	SkillDataCheckDelayTime = 0;


	for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if (sinSkill.UseSkill[j].Flag)
		{

			if (!SkillDataCheckFlag2)
			{
				ReformSkillPointForm(&sinSkill.UseSkill[j]);
			}
			if (!CheckSkillPointForm(&sinSkill.UseSkill[j]))return FALSE;
			if (!CheckSkillMasteryForm(&sinSkill.UseSkill[j]))return FALSE;

		}
	}
	SkillDataCheckFlag2 = 1;


	return TRUE;
}


//��ų����Ʈ �ʱ�ȭ�ϱ� 
int cSKILL::InitSkillPoint(int kind) { return TRUE; }

//DWORD ClearSkillPointCODE[10] = {SKILL_HOLY_BODY , SKILL_HOLY_MIND , 0,0,0,0,0,0,0,0};
DWORD ClearSkillPointCODE[10] = {0,0,0,0,0,0,0,0,0,0}; //�κ� ��ų �ʱ�ȭ 

int cSKILL::SearchClearSkillPoint(DWORD CODE)
{
	
	for(int i = 0 ; i < 10 ; i++){
		if(ClearSkillPointCODE[i] ==CODE){
			ClearSkillCODE = ClearSkillPointCODE[i];
			return TRUE;
		}
		else
			ClearSkillCODE = 0;
	}
	
	return FALSE;
	
}

////////////// �ʱ�ȭ�� ��ų����Ʈ�� �ʱ�ȭ ��ư�� ���� 
int cSKILL::ShowClearSkillPointButton(int x , int y) { return TRUE; }

////////////// Ư�� ��ų����Ʈ�� �ʱ�ȭ�Ѵ� 
int cSKILL::ClearSkillPointSection( )
{

	CheckingNowSkillState(); //��ų����Ʈ�� 
	CheckCharForm();//���� 
	int Count = 0;
	for(int j = 1 ; j < ChangeJobSkillPlus ; j ++){ 
		if(sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point > 1){
			for(int i = 0 ; i < 10 ; i++){
				if(sinSkill.UseSkill[j].CODE== ClearSkillPointCODE[i]){ 
					cSkill.CheckSkillMasteryForm(0,j); // ��ų �����͸��� üũ�Ѵ�
					CheckSkillPointForm(&sinSkill.UseSkill[j]);
					sinSkill.UseSkill[j].Point--; //��ų����Ʈ �ʱ�ȭ 
					sinSkill.UseSkill[j].GageLength   = 0;
					sinSkill.UseSkill[j].GageLength2  = 0;
					sinSkill.UseSkill[j].Mastery      = 0;
					sinSkill.UseSkill[j].UseSKillIncreCount = 0;
					sinSkill.UseSkill[j].UseSkillCount = 0;
					sinSkill.UseSkill[j].UseSkillMastery = 0;
					sinSkill.UseSkill[j].UseSkillMasteryGage = 0;
					sinSkill.UseSkill[j].Use = 0;
					ReformSkillPointForm(&sinSkill.UseSkill[j]);
					ReformSkillMasteryForm(0,j);
					sinSkill.SkillPoint ++;
					ClearSkillCODE = 0;
					LearnSkillEffect(0);
					ReformCharForm();//������ 
					return TRUE;
				}
			}		
		}
	}
	return TRUE;
}


unsigned int CharSkillInfoData[8] = {0,}; //ĳ������ CheckSum�̼��õ� �迭 
int   ChangeJob = -1;
//ĳ���ͺ� SkillInfo�� �����Ѵ� 
int cSKILL::ReFormCharSkillInfo()
{
	int   i = 0 ,j = 0, k = 0;
	int   CharNum = 0;
	
	int   CharCode[9] = {SIN_CHAR_MECANICIAN,SIN_CHAR_FIGHTER,SIN_CHAR_ARCHER,SIN_CHAR_PIKEMAN,SIN_CHAR_KNIGHT,SIN_CHAR_ATALANTA,SIN_CHAR_PRIESTESS,SIN_CHAR_MAGICIAN, JOBCODE_ASSASSIN };
	//�ڽ��� ������ ���Ѵ� 
	for(i = 0 ; i < 9 ; i++){
		if(sinChar->JOB_CODE == CharCode[i] ){
			CharNum = i;
			break;
		}
	}

	if(ChangeJob != sinChar->ChangeJob){
		ChangeJob = sinChar->ChangeJob;
		CharSkillInfoData[CharNum] = 0; //�ʱ�ȭ 
		for(j=1;j < SIN_MAX_USE_SKILL; j++){
			if(sinSkill.UseSkill[j].Flag){
				k = j+1;
				CharSkillInfoData[CharNum] += k*sinSkill.UseSkill[j].Skill_Info.RequireLevel;
				CharSkillInfoData[CharNum] += k*sinSkill.UseSkill[j].Skill_Info.UseStamina[0];
				CharSkillInfoData[CharNum] += k*sinSkill.UseSkill[j].Skill_Info.UseStamina[1];
			}
		}
	}
	return TRUE;
}

//ĳ���ͺ� SkillInfo�� üũ�Ѵ�
int cSKILL::CheckCharSkillInfo()
{
	//DWORD	dwXorKey = lpCurPlayer->dwObjectSerial&0x5F;
	int   i = 0 ,j = 0, k = 0;
	int   CharNum = 0;
	int   CharCode[9] = {SIN_CHAR_MECANICIAN,SIN_CHAR_FIGHTER,SIN_CHAR_ARCHER,SIN_CHAR_PIKEMAN,SIN_CHAR_KNIGHT,SIN_CHAR_ATALANTA,SIN_CHAR_PRIESTESS,SIN_CHAR_MAGICIAN, JOBCODE_ASSASSIN };
	

//	unsigned int CharSkillInfoData[8] = {2549,2597,2246,2230,0,0,0,0};
	
	unsigned int CharSkillInfoDataCheckSum[8] ={0,};

	//�ڽ��� ������ ���Ѵ� 
	for(i = 0 ; i < 9 ; i++){
		if(sinChar->JOB_CODE == CharCode[i] ){
			CharNum = i;
			break;
		}
	}

	// Corre��o Mature

	for (j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if (sinSkill.UseSkill[j].Flag)
		{
			k = j + 1;
			CharSkillInfoDataCheckSum[CharNum] += k * sinSkill.UseSkill[j].Skill_Info.RequireLevel;
			CharSkillInfoDataCheckSum[CharNum] += k * sinSkill.UseSkill[j].Skill_Info.UseStamina[0];
			CharSkillInfoDataCheckSum[CharNum] += k * sinSkill.UseSkill[j].Skill_Info.UseStamina[1];
			if (!sinSkill.UseSkill[j].UseSkillCount)continue;
			if (!CheckSkillMasteyData[j])
			{
				CheckSkillMasteyData[j] = sinSkill.UseSkill[j].UseSkillCount;
			}
			CheckSkillMasteyData[j] = sinSkill.UseSkill[j].UseSkillCount;
		}
	}
	if (CharSkillInfoDataCheckSum[CharNum] != CharSkillInfoData[CharNum])
	{

		SendSetHackUser3(51, CharSkillInfoDataCheckSum[CharNum], CharSkillInfoData[CharNum]);
		return FALSE;
	}


	return TRUE;
}

int cSKILL::CheckSkillMasteryForm( sSKILL *pSkill , int Index)
{
	if(pSkill){
		for(int j=1;j < SIN_MAX_USE_SKILL; j++){
			if(sinSkill.UseSkill[j].Flag){
				if(pSkill->CODE == sinSkill.UseSkill[j].CODE){
					Index = j;
					break;
				}
			}
		}
	}
	//if(!CheckMasteryData[Index])return FALSE; //����Ÿ�� ������쿡�� �Ѿ�� 


	int CheckMasteryDataSum = lpCurPlayer->dwObjectSerial+sinSkill.UseSkill[Index].CODE;

	CheckMasteryDataSum += (sinSkill.UseSkill[Index].GageLength*Index);
	CheckMasteryDataSum += (sinSkill.UseSkill[Index].GageLength2*Index);
	CheckMasteryDataSum += (sinSkill.UseSkill[Index].Mastery*Index);
	
	if(CheckMasteryData[Index] != CheckMasteryDataSum){
		//CheckMasteryDataSum = 0; �׽�Ʈ�� 
		//SendSetHackUser(52); //��ŷ�� �Ϸ����ߴ� ���� ������ ��� TRUE ���� ���� 
		SendSetHackUser3(52,CheckMasteryData[Index],CheckMasteryDataSum);
		return FALSE;

	}

	return TRUE; 
}
int cSKILL::ReformSkillMasteryForm( sSKILL *pSkill ,int Index)
{
	
	if(pSkill){
		for(int j=1;j < SIN_MAX_USE_SKILL; j++){
			if(sinSkill.UseSkill[j].Flag){
				if(pSkill->CODE == sinSkill.UseSkill[j].CODE){
					Index = j;
				}
			}
		}
	}

	CheckMasteryData[Index] = lpCurPlayer->dwObjectSerial+sinSkill.UseSkill[Index].CODE; //�ʱ�ȭ
	CheckMasteryData[Index] += (sinSkill.UseSkill[Index].GageLength*Index);
	CheckMasteryData[Index] += (sinSkill.UseSkill[Index].GageLength2*Index);
	CheckMasteryData[Index] += (sinSkill.UseSkill[Index].Mastery*Index);

	return TRUE;
}

//��ų����Ʈ�� üũ�Ѵ�
int cSKILL::CheckSkillPointForm(sSKILL *pSkill)
{
	DWORD	dwXorKey = lpCurPlayer->dwObjectSerial&0x5F;

	for(int j=1;j < SIN_MAX_USE_SKILL; j++){
		if(sinSkill.UseSkill[j].Flag &&sinSkill.UseSkill[j].Use &&sinSkill.UseSkill[j].Point){
			if(pSkill->CODE == sinSkill.UseSkill[j].CODE){
				//if(CheckSkillPointData[j]){
					if(CheckSkillPointData[j] != (sinSkill.UseSkill[j].Point^dwXorKey) ){
						SendSetHackUser3(54,CheckSkillPointData[j],sinSkill.UseSkill[j].Point);
						return FALSE;
					}
				//}
			}
		}
	}
	
	return TRUE;
}

//��ų����Ʈ�� �����Ѵ�
int cSKILL::ReformSkillPointForm(sSKILL *pSkill)
{
	DWORD	dwXorKey = lpCurPlayer->dwObjectSerial&0x5F;

	for(int j=1;j < SIN_MAX_USE_SKILL; j++){
		if(sinSkill.UseSkill[j].Flag ){
			if(pSkill->CODE == sinSkill.UseSkill[j].CODE){
				CheckSkillPointData[j] = ( sinSkill.UseSkill[j].Point^dwXorKey);
				break;
			}
		}
	}
	return TRUE;
}

//��ų����Ʈ ù����Ʈ�� �����Ѵ� 
int cSKILL::InitReformSkillPointForm()
{
	/*
	DWORD	dwXorKey = lpCurPlayer->dwObjectSerial&0x5F;
	
	for(int j=1;j < SIN_MAX_USE_SKILL; j++){
		if(sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Use && sinSkill.UseSkill[j].Point){
			CheckSkillPointData[j] = ( sinSkill.UseSkill[j].Point^dwXorKey);
		}
	}
	*/
	
	return TRUE;
}

//��ų�� ��ų����Ʈ�� ���´�
int cSKILL::GetSkillPoint(DWORD CODE)
{
	for(int j=1;j < SIN_MAX_USE_SKILL; j++){
		if(sinSkill.UseSkill[j].Flag){
			if(CODE == sinSkill.UseSkill[j].CODE){
				return sinSkill.UseSkill[j].Point;
			}
		}
	}

	return 0;	
}

//���������� ������ ��ų�� ã�Ƽ� ����Ʈ�� �����Ѵ�
int cSKILL::SearchContiueSkill(DWORD CODE)
{
	for(int k = 0; k < 10 ; k++){
		if(ContinueSkill[k].Flag){
			if(ContinueSkill[k].CODE ==CODE){
				return ContinueSkill[k].Point;

			}
		}
	}
	return 0;
}

//���� ������� ��������ų�� �ε����� ã�� �����Ѵ�
int cSKILL::SearchContiueSkillIndex(DWORD CODE)
{
	for(int k = 0; k < 10 ; k++){
		if(ContinueSkill[k].Flag){
			if(ContinueSkill[k].CODE ==CODE){
				return k+1;
			}
		}
	}
	return 0;
}
//���� ������� ��������ų�� �ڵ带 ã�� �����Ѵ�
int cSKILL::SearchContiueSkillCODE(DWORD CODE)
{
	for(int k = 0; k < 10 ; k++){
		if(ContinueSkill[k].Flag){
			if(ContinueSkill[k].CODE ==CODE){
				return ContinueSkill[k].CODE;
			}
		}
	}
	return 0;
}

//���߾�������� �����Ѵ�
int AddVirtualLife[2] = {0,0};
int sinVirtualLifeTime = 0;
int sinVirtualLifePercent = 0;

// ����� - �ν��� ������(�����)
int AddBoosterLife = 0;
int BoosterLifeTime = 0;
int BoosterLifePercent = 0;
int LifeFlag = 0;
short tempLife[2] = {0,0};

// ����� - �ν��� ������(���)
int AddVirtualMana[2] = {0,0};
int sinVirtualManaTime = 0;
int sinVirtualManaPercent = 0;
int ManaFlag = 0;
short tempMana[2] = {0,0};

// ����� - �ν��� ������(�ٷ�)
int AddVirtualStamina[2] = {0,0};
int sinVirtualStaminaTime = 0;
int sinVirtualStaminaPercent = 0;
int StaminaFlag = 0;
short tempStamina[2] = {0,0};

// �庰 - ��ų ������
int sinAddSkillDelay = 0;
int sinSkillDelayTime = 0;
int SkillDelayFlag = 0;

int cSKILL::SetVirtualLife(int Time , int Point)
{

	//Contiue �ʱ�ȭ
	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){
		if(ContinueSkill[i].Flag){
			if(ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE){
				//memset(&ContinueSkill[i],0,sizeof(sSKILL));
				return FALSE; //�ߺ����� �Ұ�
			}
		}
	}

	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){
		if(!ContinueSkill[i].Flag){
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_VIRTUAL_LIFE;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}

	AddVirtualLife[1]  = ((int)sinChar->Life[1] * Virtual_Life_Percent[Point-1])/100;
	sinVirtualLifeTime = Time;
	sinVirtualLifePercent = Virtual_Life_Percent[Point-1];
	CheckVirtualLifeTime = 0; //üũ�ð��ʱ�ȭ
	cInvenTory.SetItemToChar();
	return TRUE;
}

// ����� - �ν��� ������
int cSKILL::UseBoosterItem(sITEM *pItem) { return TRUE; }

// ����� - ������ �ν��͸� �����Ѵ�
int cSKILL::SetBoosterItem(DWORD ItemCODE , int Time)
{
	int UseFlag = 0; 
	sSKILL TempSkill;
	memset(&TempSkill,0,sizeof(sSKILL));
	char *Path;

	DWORD ItemMask;
	int cnt = 0;

	ItemMask = ItemCODE&sinITEM_MASK3;

	if(ItemMask==sin21 || ItemMask==sin24 || ItemMask==sin27) cnt = 0; // 1�ð�
	if(ItemMask==sin22 || ItemMask==sin25 || ItemMask==sin28) cnt = 1; // 3�ð�
    if(ItemMask==sin23 || ItemMask==sin26 || ItemMask==sin29) cnt = 2; // 1��

	switch(ItemMask)
	{
		// ����� �ν���
	case sin21 :  
	case sin22 :
	case sin23 :
		UseFlag = 0;
		Path = "image\\Sinimage\\skill\\keep\\Booster_01.tga";
		TempSkill.CODE = BOOSTER_ITEM_LIFE;
		TempSkill.Point = 0; // �ν��� �������� ������ ����.
		TempSkill.UseTime = BoosterItem_UseTime[cnt];
		TempSkill.CheckTime = (BoosterItem_UseTime[cnt]*70) - (Time*70); 
		TempSkill.MatIcon = Mat_BoosterItem[UseFlag];
		break;

		// ��� �ν���
	case sin24 :  
	case sin25 :
	case sin26 :  
		UseFlag = 1;
		Path = "image\\Sinimage\\skill\\keep\\Booster_02.tga";
		TempSkill.CODE = BOOSTER_ITEM_MANA;
		TempSkill.Point = 0; // �ν��� �������� ������ ����.
		TempSkill.UseTime = BoosterItem_UseTime[cnt];
		TempSkill.CheckTime = (BoosterItem_UseTime[cnt]*70) - (Time*70); 
		TempSkill.MatIcon = Mat_BoosterItem[UseFlag];
		break;

		// �ٷ� �ν���
	case sin27 :  
	case sin28 :
	case sin29 :   
		UseFlag = 2;
		Path = "image\\Sinimage\\skill\\keep\\Booster_03.tga";
		TempSkill.CODE = BOOSTER_ITEM_STAMINA;
		TempSkill.Point = 0; // �ν��� �������� ������ ����.
		TempSkill.UseTime = BoosterItem_UseTime[cnt];
		TempSkill.CheckTime = (BoosterItem_UseTime[cnt]*70) - (Time*70); 
		TempSkill.MatIcon = Mat_BoosterItem[UseFlag];
		break;
	}

	char szBuff[128];
	if(!Mat_BoosterItem[UseFlag]){
		wsprintf(szBuff,Path,UseFlag);
		ReadTextures();	//�ؽ��� �ε�
	}

	sinContinueSkillSet(&TempSkill);

	if(UseFlag == 0)
	{
		// ����� - �ν��� ������(�����)
		AddBoosterLife  = ((int)sinChar->Life[1] * BoosterItem_DataPercent[UseFlag])/100;
		BoosterLifeTime = Time;
		BoosterLifePercent = BoosterItem_DataPercent[UseFlag];
		CheckBoosterLifeTime = 0; //üũ�ð��ʱ�ȭ
	}
	else if(UseFlag == 1)
	{
		// ����� - �ν��� ������(���)
		AddVirtualMana[1]  = ((int)sinChar->Mana[1] * BoosterItem_DataPercent[UseFlag])/100;
		sinVirtualManaTime = Time;
		sinVirtualManaPercent = BoosterItem_DataPercent[UseFlag];
		CheckVirtualManaTime = 0; //üũ�ð��ʱ�ȭ
	}
	else if(UseFlag==2)
	{
		// ����� - �ν��� ������(�ٷ�)
		AddVirtualStamina[1]  = ((int)sinChar->Stamina[1] * BoosterItem_DataPercent[UseFlag])/100;
		sinVirtualStaminaTime = Time;
		sinVirtualStaminaPercent = BoosterItem_DataPercent[UseFlag];
		CheckVirtualStaminaTime = 0; //üũ�ð��ʱ�ȭ
	}

	cInvenTory.SetItemToChar();

	return TRUE;
}

// �庰 - ��ų ������
int cSKILL::SetSkillDelayItem(DWORD ItemCODE , int Time)
{
	int UseFlag = 0; 
	sSKILL TempSkill;
	memset(&TempSkill,0,sizeof(sSKILL));
	char *Path;

	DWORD ItemMask;
	int cnt = 0;

	ItemMask = ItemCODE&sinITEM_MASK3;

	if(ItemMask==sin30 || ItemMask==sin33 || ItemMask==sin36) cnt = 0;
	if(ItemMask==sin31 || ItemMask==sin34 || ItemMask==sin37) cnt = 1;
	if(ItemMask==sin32 || ItemMask==sin35 || ItemMask==sin38) cnt = 2;

	switch(ItemMask)
	{
		// ����� �ν���
	case sin30 :  
	case sin31 :
	case sin32 :
		UseFlag = 0;
		Path = "image\\Sinimage\\skill\\keep\\Booster_01.tga";
		TempSkill.CODE = SKILLDELAY_ITEM_LIFE;
		TempSkill.Point = 0; 
		TempSkill.UseTime = nSkillDelay_UseTime[cnt];
		TempSkill.CheckTime = (nSkillDelay_UseTime[cnt]*70) - (Time*70); 
		TempSkill.MatIcon = nMat_SkillDelayItem[UseFlag];
		break;
	}


	char szBuff[128];
	if(!nMat_SkillDelayItem[UseFlag]){
		wsprintf(szBuff,Path,UseFlag);
		ReadTextures();	//�ؽ��� �ε�
	}

	sinContinueSkillSet(&TempSkill);

	if(UseFlag == 0)
	{
		sinAddSkillDelay  = 10;
		sinSkillDelayTime = Time;
		BoosterLifePercent = BoosterItem_DataPercent[UseFlag];
		CheckSkillDelayTime = 0; //üũ�ð��ʱ�ȭ
	}


	cInvenTory.SetItemToChar();

	return TRUE;
}


// �庰 - ��ų ������
int cSKILL::UseSkillDelayItem(sITEM *pItem) { return TRUE; }


//Ʈ���̾��� ���� ���Ҷ�
int cSKILL::SetT_Of_Valhalla( int Point , int LV)
{

	//Contiue �ʱ�ȭ
	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){
		if(ContinueSkill[i].Flag){
			if(ContinueSkill[i].CODE == SKILL_TRIUMPH_OF_VALHALLA ||ContinueSkill[i].CODE == SKILL_HALL_OF_VALHALLA){
				//memset(&ContinueSkill[i],0,sizeof(sSKILL));
				return FALSE; //�ߺ����� �Ұ�
			}
		}
	}

	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){
		if(!ContinueSkill[i].Flag){
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_TRIUMPH_OF_VALHALLA;
			ContinueSkill[i].UseTime = T_Of_Valhalla_Time[Point-1];
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}

	SetT_Of_ValhallaLV = LV;

	if(SetT_Of_ValhallaFlag2){ //�ڽ��� ����Ѱ��̸�
		SetT_Of_ValhallaFlag2 = 0;
		SetT_Of_ValhallaFlag  = 0;
	}
	else{
		SetT_Of_ValhallaFlag  = 1; //���̻�����ذ��̸�

	}
	cInvenTory.SetItemToChar();
	return TRUE;
}

//��þƮ ����
int cSKILL::SetEnchant_Weapon(int Time , int Point)
{

	//Contiue �ʱ�ȭ
	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){
		if(ContinueSkill[i].Flag){
			if(ContinueSkill[i].CODE == SKILL_ENCHANT_WEAPON){
				//memset(&ContinueSkill[i],0,sizeof(sSKILL));
				return FALSE; //�ߺ����� �Ұ�
			}
		}
	}

	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){
		if(!ContinueSkill[i].Flag){
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_ENCHANT_WEAPON;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}
	cInvenTory.SetItemToChar();
	return TRUE;
}

int cSKILL::Evasion_Mastery(int Time, int Point)
{
	for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			if (ContinueSkill[i].CODE == SKILL_EVASION_MASTERY)
			{
				memset(&ContinueSkill[i], 0, sizeof(sSKILL));
				break;
			}
		}
	}

	for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if (!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_EVASION_MASTERY;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}

	cInvenTory.SetItemToChar();

	return TRUE;
}

//�������������
int cSKILL::ForeceOfNature(int Time , int Point , int Party)
{

	//Contiue �ʱ�ȭ
	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){
		if(ContinueSkill[i].Flag){
			if(ContinueSkill[i].CODE == SKILL_FORCE_OF_NATURE){
				if(ContinueSkill[i].Flag == 2 && !Party ){
					memset(&ContinueSkill[i],0,sizeof(sSKILL));
					break;
				}
				else return FALSE; //�ߺ����� �Ұ�
			}
		}
	}

	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){
		if(!ContinueSkill[i].Flag){
			ContinueSkill[i].Flag = Party+1; //��Ƽ���� 2���Ѵ�
			ContinueSkill[i].CODE = SKILL_FORCE_OF_NATURE;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}
	cInvenTory.SetItemToChar();
	return TRUE;
}

//����� ���Ҷ�
int cSKILL::HellOfValhalla(int Time , int Point,int TVPoint , int LV , int Party)
{

	//Contiue �ʱ�ȭ
	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){
		if(ContinueSkill[i].Flag){
			if(ContinueSkill[i].CODE == SKILL_HALL_OF_VALHALLA){
				if(ContinueSkill[i].Flag == 2 && !Party){
					memset(&ContinueSkill[i],0,sizeof(sSKILL));
					break;
				}
				else return FALSE; //�ߺ����� �Ұ�
			}
		}
	}

	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){
		if(!ContinueSkill[i].Flag){
			ContinueSkill[i].Flag = Party+1; //��Ƽ���� 2���Ѵ�
			ContinueSkill[i].CODE = SKILL_HALL_OF_VALHALLA;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}
	SetT_Of_ValhallaPOINT = TVPoint;
	SetH_Of_ValhallaLV = LV;    //�������� ����
	cInvenTory.SetItemToChar();
	return TRUE;
}


//�����ʷ����� �ʵ�
int cSKILL::Regeneration_Field(int Time , int Point , int Party)
{

	//Contiue �ʱ�ȭ
	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){
		if(ContinueSkill[i].Flag){
			if(ContinueSkill[i].CODE == SKILL_REGENERATION_FIELD){
				if(ContinueSkill[i].UseTime > Time)return FALSE; //���� ĳ������ ����
				ContinueSkill[i].UseTime = Time;
				return TRUE; //�ð�����
			}
		}
	}

	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){
		if(!ContinueSkill[i].Flag){
			ContinueSkill[i].Flag = 1+Party; //��Ƽ���� 2���Ѵ�
			ContinueSkill[i].CODE = SKILL_REGENERATION_FIELD;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}
	cInvenTory.SetItemToChar();
	return TRUE;
}

//��ų ������ ã�´�
int cSKILL::SearchSkillDoc(sSKILL *pSkill) { return TRUE; }

//���׸���
int cSKILL::SkillBarDraw(sSKILL *pSkill , int x , int y, int Alpha) { return TRUE; }



//���� ��ų üũ
int cSKILL::CheckContinueIcon()
{
	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){ 
		if(ContinueSkill[i].Flag){
			if(!ContinueSkill[i].MatIcon){
				for(int j = 0 ; j < SIN_MAX_SKILL; j++){
					if(ContinueSkill[i].CODE == sSkill[j].CODE){
						if(sSkill[j].MatIcon){ 
							ContinueSkill[i].MatIcon = sSkill[j].MatIcon;
							return TRUE;
						}
					}
				}
			}
		}
	}
	return FALSE;
}

//���� ��ų üũ
int cSKILL::CancelContinueSkill(DWORD CODE)
{

	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){ 
		if(ContinueSkill[i].Flag){
			if(ContinueSkill[i].CODE == CODE){
				memset(&ContinueSkill[i],0,sizeof(sSKILL));
				cInvenTory.SetItemToChar(); //������ �ٲ��ش� (������������ ����ġ�� �ٲ��ش�)
				break;
			}
		}
	}
	return FALSE;
}

//��ų����� �ʱ�ȭ
int cSKILL::SkillShortKeyInit()
{
	for(int j=1;j < SIN_MAX_USE_SKILL; j++){
		sinSkill.UseSkill[j].ShortKey = 0;
	}
	return TRUE;
}

// ����� - ��ų ������(�������� ��ų�� ���� ���θ� üũ�Ѵ�.)
int cSKILL::CheckMaturedSkill(int ChangeJob)
{
	int matured_skill_count = 0;

	switch(ChangeJob)
	{
	case 1:
		for(int j=1 ; j<5 ; j++) // 1�� ������ ����� ��ų
		{
			if( sinSkill.UseSkill[j].UseSkillCount<10000 && sinSkill.UseSkill[j].Skill_Info.USECODE != SIN_SKILL_USE_NOT && 
				sinSkill.UseSkill[j].UseSkillMastery)
			{
				matured_skill_count++;
			}
		}
		break;
	case 2:
		for(int j=5 ; j<9 ; j++) // 2�� ������ ����� ��ų
		{
			if( sinSkill.UseSkill[j].UseSkillCount<10000 && sinSkill.UseSkill[j].Skill_Info.USECODE != SIN_SKILL_USE_NOT && 
				sinSkill.UseSkill[j].UseSkillMastery)
			{
				matured_skill_count++;
			}
		}
		break;
	case 3:
		for(int j=9 ; j<13 ; j++) // 3�� ������ ����� ��ų
		{
			if( sinSkill.UseSkill[j].UseSkillCount<10000 && sinSkill.UseSkill[j].Skill_Info.USECODE != SIN_SKILL_USE_NOT && 
				sinSkill.UseSkill[j].UseSkillMastery)
			{
				matured_skill_count++;
			}
		}
		break;
	}

	if(matured_skill_count <= 4 && matured_skill_count>0)
		return TRUE; // ��� ����
	else
		return FALSE;  // ��� �Ұ���
}
/*
//���׸���
int cSKILL::SkillBarDraw(sSKILL *pSkill , int x , int y)
{

	D3DTLVERTEX tlVertex[72][4];  //4���� ������ �밡�� ��ǥ�� ���Ѵ� 

	int Time = 0; 
	float Time2 = 0;

	Time = (int)(((float)pSkill->CheckTime/((float)pSkill->UseTime*70.0f))*72.0f);   
	Time2++;

	float fx , fy =0; 
	
	int i = 0 , j = 0;
	int sinY,cosY;
	for( i = 0 ; i < Time ; i++){  
		for( j = 0 ; j < 4 ; j++){
			tlVertex[i][j].rhw = 1;
			tlVertex[i][j].color	= RGBA_MAKE(255,0,0,255);
			tlVertex[i][j].specular  =  RGBA_MAKE( 0,0,0,0 );
			tlVertex[i][j].sz = 0;
		}


		sinY = GetSin[ (i* 56)&ANGCLIP];      
		cosY = GetCos[ ((i* 56)+ANGLE_180)&ANGCLIP ];

		fx = (float) (( 16*sinY + 16*cosY )>>8); 
		fy = (float) (( 16*cosY - 16*sinY )>>8);
		fx /= 256;
		fy /= 256;

		//dsDrawColorBox( sinInvenColor[0] ,fx+x,fy+y, 16, 16 );

		tlVertex[i][0].sx = (float)(fx+x);  
		tlVertex[i][0].sy = (float)(fy+y);
		tlVertex[i][0].tu = 0;
		tlVertex[i][0].tv = 0;

		tlVertex[i][1].sx = float(x);
		tlVertex[i][1].sy = float(y);
		tlVertex[i][1].tu = 0;
		tlVertex[i][1].tv = 1.0f;


		sinY = GetSin[ ((i+1)* 56)&ANGCLIP];
		cosY = GetCos[ (((i+1)* 56)+ANGLE_180)&ANGCLIP ];

		fx = (float) (( 16*sinY + 16*cosY )>>8);
		fy = (float) (( 16*cosY - 16*sinY )>>8);
		fx /= 256;
		fy /= 256;

		tlVertex[i][2].sx = (float)(fx+x);
		tlVertex[i][2].sy = (float)(fy+y);
		tlVertex[i][2].tu = 1.0f;
		tlVertex[i][2].tv = 0;
		

	}


	lpD3DDevice->SetTexture( 0, 0 );
	for( i = 0 ; i < 72 ; i++){
		lpD3DDevice->DrawPrimitive( D3DPT_TRIANGLEFAN ,
							D3DFVF_TLVERTEX  ,
							tlVertex[i],
							3,
							NULL);
	}
	return TRUE;
}
*/
