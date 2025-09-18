#include "sinLinkHeader.h"
#include "..\\skillsub.h"
#include "..\\field.h"
#include <ConfirmationBox.h>
#include <Utils/Logs/utils.h>

sUSESKILL sinSkill;
sSKILL* pUseSkill;
sSKILL  ContinueSkill[20];
sSKILL  TempContinueSkill[20];
int SkillCountTime2[17] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int ContinueSkillMouseIndex = 0;

JOB_DATA_CODE* sinJobList;

sSKILL* pMasterSkill;  //��ų ���� ������ 

sSKILLPASSIVE sSkillPassive; //ĳ���Ϳ� ����Ǵ� �нú� ��ų 

/////////////
int ShowSkillUpInfo = 0;     //�޼��� �ڽ��� �Բ� ��ų������ �����ش� 
int  SkillMasterOkFlag[2] = { 0,0 };
int  SkillMasterFlag = 0;    //NPC���� ��ų �� ������ �Ѵ� 

int SkillMasteryShowFlag = 0;		//���õ��� ǥ���Ѵ� 
char szUseSkillMastery[32];			//��ų ���õ� 
POINT UseSkillMasteryPosi = { 0,0 };	//���õ� ǥ�� ������ 

int MatForceOrb[12] = { 0 };

// ����� - ���� ���� ����
int MatBillingMagicForceOrb[3] = { 0 };

// ����� - �ν��� ������
int Mat_BoosterItem[9] = { 0 };

// �庰 - ��ų ������
int nMat_SkillDelayItem[3] = { 0 };

int MatQuestTimer = 0;

/////////////��ų ����  �����ֱ� 

POINT SkillUpInfo = { 13,21 };       //��ų ���� �����ֱ� 
POINT SkillUpInfoPosi = { 90,100 };

////////////
int     SkillInfoLineCnt = 0;

int     SkillInfoShowFlag = 0;
POINT	SkillInfoBoxPosi = { 0,0 };
POINT   SkillInfoTextPosi = { 0,0 };
POINT   SkillBoxSize = { 0,0 };


char    szSkillInfoBuff[5000];
char    szSkillMasterInfoBuff[5000];

char    szSkillInfoBuff2[5000];
char    szSkillMasterInfoBuff2[5000];


int     SkillDocLineCnt[6] = { 0,0,0,0,0,0 };
int     SkillUseWeaponClass = 0;
int     NextSkillLevelLine = 0;
/////////////

int ShowSkillClose = 0; //�ݱ� ��ư �÷� 
int SkillButtonIndex = 0;
int Skill4ButtonIndex = 0;

int DownButtonUseShorKey = 0; //����Ű�� ������������ ��ų�� �������� �ʴ´� 

extern sQUEST_CHANGEJOB3	sinQuest_Daily;

int DownButtonIndex = 0;  //��ư�� ������ ȿ���� �ֱ����� �ε��� 
int LDownButtonIndex = 0;  //���� ��ư 
int RDownButtonIndex = 0;  //������ ��ư 

DWORD sinSkillBoxColor = D3DCOLOR_RGBA(0, 0, 132, 128);

int ChangeJobSkillPlus = 0;
int UseSkillIndex[2] = { 0,0 }; //���� ������ 

int SelectInterSkill = 0;

/////////////////�̴� Define
#define	NORMAL_SKILL_INDEX		14
#define MAX_USE_SKILL_POINT		10

#define SIN_MOUSE_POSI_LEFT		1
#define SIN_MOUSE_POSI_RIGHT	2

/////////////////

///////////////// ��ų ������ 
int   SkillIconIndex[10] = { 0,0,0,0,0,0,0,0,0,0 };
POINT SkillIconPosi = { 0,0 };
int   SkillInconCnt = 0;


int GageLenght[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

DWORD ClearSkillCODE = 0; //�ʱ�ȭ�� ��ų�� �ֳ����� 
POINT ClearSkillButtonPosi = { 0,0 }; //��ų �ʱ�ȭ ��ư ��ġ 

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

	{ "Coroa de SOD Gold", SODSKILL_GOLD, "", "bellatracrown_1.tga" },
	{ "Coroa de SOD Prata", SODSKILL_SILVER, "", "bellatracrown_2.tga" },
	{ "Coroa de SOD Bronze", SODSKILL_BRONZE, "", "bellatracrown_3.tga" },

	{ "Chat", CHATGLOBAL, "", "megaphone.tga" },
	{ "Rei PVP", REIPVP, "", "battlepvp.tga" },
	{ "Top LVL", TOPLVL, "", "toplevel.tga" },
	{ "Modo PVP", BUFF_WARMODE, "", "battle.tga" },

	{ "Crystal", 1, 	"", "gp101.tga" },
	{ "Crystal", 1.1, "", "gp101.tga" },
	{ "Crystal", 1.2, "", "gp101.tga" },
	{ "Crystal", 1.3, "", "gp101.tga" },
	{ "Crystal", 1.4, "", "gp101.tga" },

	{ "Crystal", 2, "", "gp102.tga" },
	{ "Crystal", 2.1, "", "gp102.tga" },
	{ "Crystal", 2.2, "", "gp102.tga" },
	{ "Crystal", 2.3, "", "gp102.tga" },
	{ "Crystal", 2.4, "", "gp102.tga" },

	{ "Crystal", 3, "", "gp103.tga" },
	{ "Crystal", 3.1, "", "gp103.tga" },
	{ "Crystal", 3.2, "", "gp103.tga" },
	{ "Crystal", 3.3, "", "gp103.tga" },
	{ "Crystal", 3.4, "", "gp103.tga" },

	{ "Crystal", 4, "", "gp104.tga" },
	{ "Crystal", 4.1, "", "gp104.tga" },
	{ "Crystal", 4.2, "", "gp104.tga" },
	{ "Crystal", 4.3, "", "gp104.tga" },
	{ "Crystal", 4.4, "", "gp104.tga" },

	{ "Crystal", 5, "", "gp105.tga" },
	{ "Crystal", 5.1, "", "gp105.tga" },
	{ "Crystal", 5.2, "", "gp105.tga" },
	{ "Crystal", 5.3, "", "gp105.tga" },
	{ "Crystal", 5.4, "", "gp105.tga" },

	{ "Crystal", 6, "", "gp106.tga" },
	{ "Crystal", 6.1, "", "gp106.tga" },
	{ "Crystal", 6.2, "", "gp106.tga" },
	{ "Crystal", 6.3, "", "gp106.tga" },
	{ "Crystal", 6.4, "", "gp106.tga" },

	{ "Crystal", 7, "", "gp107.tga" },
	{ "Crystal", 7.1, "", "gp107.tga" },
	{ "Crystal", 7.2, "", "gp107.tga" },
	{ "Crystal", 7.3, "", "gp107.tga" },
	{ "Crystal", 7.4, "", "gp107.tga" },

	{ "Crystal", 8, "", "gp108.tga" },
	{ "Crystal", 8.1, "", "gp108.tga" },
	{ "Crystal", 8.2, "", "gp108.tga" },
	{ "Crystal", 8.3, "", "gp108.tga" },
	{ "Crystal", 8.4, "", "gp108.tga" },

	{ "Crystal", 9, "", "gp109.tga" },
	{ "Crystal", 9.1, "", "gp109.tga" },
	{ "Crystal", 9.2, "", "gp109.tga" },
	{ "Crystal", 9.3, "", "gp109.tga" },
	{ "Crystal", 9.4, "", "gp109.tga" },

	{ "Crystal", 10, "", "gp110.tga" },
	{ "Crystal", 10.1, "", "gp110.tga" },
	{ "Crystal", 10.2, "", "gp110.tga" },
	{ "Crystal", 10.3, "", "gp110.tga" },
	{ "Crystal", 10.4, "", "gp110.tga" },

	{ "Crystal", 11, "", "gp111.tga" },
	{ "Crystal", 11.1, "", "gp111.tga" },
	{ "Crystal", 11.2, "", "gp111.tga" },
	{ "Crystal", 11.3, "", "gp111.tga" },
	{ "Crystal", 11.4, "", "gp111.tga" },

	{ "Crystal", 12, "", "gp112.tga" },
	{ "Crystal", 12.1, "", "gp112.tga" },
	{ "Crystal", 12.2, "", "gp112.tga" },
	{ "Crystal", 12.3, "", "gp112.tga" },
	{ "Crystal", 12.4, "", "gp112.tga" },

	{ "Crystal", 13, "", "gp113.tga" },
	{ "Crystal", 13.1, "", "gp113.tga" },
	{ "Crystal", 13.2, "", "gp113.tga" },
	{ "Crystal", 13.3, "", "gp113.tga" },
	{ "Crystal", 13.4, "", "gp113.tga" },

	// Novos Cristais

	{ "Crystal", 23, "", "gp123.tga" },
	{ "Crystal", 23.1, "", "gp123.tga" },
	{ "Crystal", 23.2, "", "gp123.tga" },
	{ "Crystal", 23.3, "", "gp123.tga" },
	{ "Crystal", 23.4, "", "gp123.tga" },

	{ "Crystal", 24, "", "gp124.tga" },
	{ "Crystal", 24.1, "", "gp124.tga" },
	{ "Crystal", 24.2, "", "gp124.tga" },
	{ "Crystal", 24.3, "", "gp124.tga" },
	{ "Crystal", 24.4, "", "gp124.tga" },

	{ "Crystal", 25, "", "gp125.tga" },
	{ "Crystal", 25.1, "", "gp125.tga" },
	{ "Crystal", 25.2, "", "gp125.tga" },
	{ "Crystal", 25.3, "", "gp125.tga" },
	{ "Crystal", 25.4, "", "gp125.tga" },
};


//��ų â �ڽ� ��ġ ���� 
sSKILLBOX	sSkillBox[SIN_MAX_SKILLBOX] = {
	{{142,537,142 + 49,537 + 46}},

	{{27 - 10,502,27 + 49 - 10,502 + 46},{27 + 47 - 10,502 + 5,27 + 47 + 5 - 10,502 + 40}},
	{{67 - 10,546,67 + 49 - 10,546 + 46},{67 + 47 - 10,546 + 5,67 + 47 + 5 - 10,546 + 40}},
	{{77 - 10,466,77 + 49 - 10,466 + 46},{77 + 47 - 10,466 + 5,77 + 47 + 5 - 10,466 + 40}},
	{{137 - 10,476,137 + 49 - 10,476 + 46},{137 + 47 - 10,476 + 5,137 + 47 + 5 - 10,476 + 40}},

	{{212 - 15,466,212 + 49 - 15,466 + 46},{212 + 47 - 15,466 + 5,212 + 47 + 5 - 15,466 + 40}},
	{{232 - 15,516,232 + 49 - 15,516 + 46},{232 + 47 - 15,516 + 5,232 + 47 + 5 - 15,516 + 40}},
	{{272 - 15,466,272 + 49 - 15,466 + 46},{272 + 47 - 15,466 + 5,272 + 47 + 5 - 15,466 + 40}},
	{{332,466,332 + 49,466 + 46},{332 + 47,466 + 5,332 + 47 + 5,466 + 40}},

	{{402,476,402 + 49, 476 + 46},{402 + 47,476 + 5,402 + 47 + 5,476 + 40}},
	{{472,456,472 + 49, 456 + 46},{472 + 47,456 + 5,472 + 47 + 5,456 + 40}},
	{{512,506,512 + 49, 506 + 46},{512 + 47,506 + 5,512 + 47 + 5,506 + 40}},
	{{532,456,532 + 49, 456 + 46},{532 + 47,456 + 5,532 + 47 + 5,456 + 40}},

	{{602,481,602 + 49, 481 + 46},{602 + 47,481 + 5,602 + 47 + 5,481 + 40}},
	{{662,511,662 + 49, 511 + 46},{662 + 47,511 + 5,662 + 47 + 5,511 + 40}},
	{{681,461,681 + 49, 461 + 46},{681 + 47,461 + 5,681 + 47 + 5,461 + 40}},
	{{722,511,722 + 49, 511 + 46},{722 + 47,511 + 5,722 + 47 + 5,511 + 40}},


};

sSKILLBOX sLeftRightSkill[2] = {
	{{349,541,349 + 49,541 + 46},{349,558,349 + 5,558 + 35}},  //��ų ���� 
	{{401 + 2,541,401 + 49,541 + 46},{446,558,446 + 5,558 + 35}},  //��ų ������ 

};

int SkillTitle[4][2] = {
	{85,438 - 4},
	{280,438 - 4},
	{470,438 - 9},
	{675,438 - 4},

};


LPDIRECT3DTEXTURE9	lpSkillMain;
LPDIRECT3DTEXTURE9	lpSkillMain2;
LPDIRECT3DTEXTURE9    lpSkillMainLeftB;
LPDIRECT3DTEXTURE9    lpSkillMainRightB;

int SkillMain2OpenFlag = 0;
int SkillMain2ButtonFlag[2] = { 0,0 };
int Skill4MasterFlag = 0;
int MonsterDamageLine = 0;
int ChainDamageLine = 0;
int MatSkillIconBackGround = 0;

cSKILL::cSKILL()
{
	memset(&ContinueSkill, 0, sizeof(sSKILL) * 10);
}
cSKILL::~cSKILL()
{

}

void cSKILL::Init()
{

	char* FilePath = "Image\\SinImage\\skill\\keep\\";
	char szFilePath[128];
	for (int j = 0; j < SIN_MAX_SKILL; j++) {
		if (sSkill[j].IconName) {
			wsprintf(szFilePath, "%s%s", FilePath, sSkill[j].IconName);
			sSkill[j].MatIcon = CreateTextureMaterial(szFilePath, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

		}
	}


	//MatSkill[0] =  CreateTextureMaterial( "Image\\SinImage\\Skill\\Skill-1.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	//MatSkill[1] =  CreateTextureMaterial( "Image\\SinImage\\Skill\\Skill-2.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	//MatSkill[2] =  CreateTextureMaterial( "Image\\SinImage\\Skill\\Skill-3.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	//MatSkill[3] =  CreateTextureMaterial( "Image\\SinImage\\Skill\\Skill-4.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );

	MatCircleIcon = CreateTextureMaterial("Image\\SinImage\\Skill\\keep\\GA_Mon.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);;
	MatSkillIconBackGround = CreateTextureMaterial("Image\\SinImage\\Skill\\keep\\GA_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);;

	SearchUseSkill(); //���� ����Ҽ� �ִ� ĳ������ ��ų�� ã�´� 
	Load();

	//�⺻������ �����Ѵ� 
	sinSkill.pLeftSkill = &sinSkill.UseSkill[0];
	sinSkill.UseSkill[0].MousePosi = 1;
	sinSkill.pLeftSkill->Position = 1;



}
/*----------------------------------------------------------------------------*
*						    Bmp������ �ε��Ѵ�
*-----------------------------------------------------------------------------*/
void cSKILL::Load()
{
	char ShortKeyDirPath[128];
	char WeaponIconPath[128];

	lpSkillDown = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\skilldown.bmp");

	//��ų ����2=========================================================================== 
	lpSkillMain = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Skil24.bmp");
	//lpSkillMain2   = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Skil25.bmp");

	//��ų ���� ��ư
	lpSkillMainLeftB = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\LeftArrow.bmp");
	lpSkillMainRightB = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\RightArrow.bmp");
	//======================================================================================



	lpSkillGage[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage.bmp");
	lpSkillGage[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage2.bmp");
	lpSkillGage2[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-2.bmp");
	lpSkillGage2[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-22.bmp");
	lpSkillGage3 = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-3.bmp");
	lpSkillGage4 = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-4.bmp");
	lpSkillGage5 = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-5.bmp");

	lpMasteryInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\MasteryInfo.bmp");

	lpSelectSkill = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\SelectSkill.bmp");
	lpSkillBoxBack = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\BOX4040.bmp");

	for (int i = 0; i < 8; i++) {
		wsprintf(ShortKeyDirPath, "Image\\SinImage\\skill\\ShortKey\\f%d.bmp", i + 1);
		lpShortKey[i] = LoadDibSurfaceOffscreen(ShortKeyDirPath);//���Ű 

	}
	for (int i = 0; i < 10; i++)
	{
		wsprintf(WeaponIconPath, "Image\\SinImage\\skill\\WeaponIcon\\%d.bmp", i + 1);
		lpWeaponIcon[i] = LoadDibSurfaceOffscreen(WeaponIconPath);//���� ������ 

	}

}

//��ų�̹����� �ε��Ѵ� 
void cSKILL::LoadUseSkillImage()
{
	int i = 0;
	char TempDirPath[128];
	char TempTitleDirPath[128];
	char ButtonImageDirPath[128];

	TempDirPath[0] = 0;
	switch (UseSkillBox) {
	case GROUP_MECHANICIAN:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Mecha\\");

		break;
	case GROUP_FIGHTER:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Fighter\\");

		break;
	case GROUP_PIKEMAN:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Pikeman\\");

		break;
	case GROUP_ARCHER:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Archer\\");

		break;
	case GROUP_ATALANTA:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Atalanta\\");
		break;
	case GROUP_KNIGHT:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Knight\\");

		break;
	case GROUP_MAGICIAN:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Magician\\");

		break;
	case GROUP_PRIESTESS:
		lstrcpy(TempDirPath, "Image\\SinImage\\Skill\\Priestess\\");

		break;


	}
	if (!TempDirPath[0]) //��θ��� ã�����ϸ� �����Ѵ� 
		return;


	lpSkillButton[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Skill\\Skill_Normal.bmp"); //��� ���� 
	lpSkillButton_Gray[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Skill\\Skill_Normal.bmp"); //��� ���� 
	for (i = 0; i < 4; i++) {
		wsprintf(TempTitleDirPath, "%s%s%d%s", TempDirPath, "JobTitle\\", i + 1, ".bmp");
		lpSkillTitle[i] = LoadDibSurfaceOffscreen(TempTitleDirPath);

	}

	/////////////////��ư �̹��� �ε� 
	for (i = 1; i < 17; i++) { //��� ���� �̹����� �� ������ ��ų �̹��� 
		if (sinSkill.UseSkill[i].Flag) {
			if (sinSkill.UseSkill[i].FileName[0]) {
				wsprintf(ButtonImageDirPath, "%s%s%s%s", TempDirPath, "Button\\", sinSkill.UseSkill[i].FileName, ".bmp");
				lpSkillButton[i] = LoadDibSurfaceOffscreen(ButtonImageDirPath);
				wsprintf(ButtonImageDirPath, "%s%s%s%s%s", TempDirPath, "Button\\", sinSkill.UseSkill[i].FileName, "_", ".bmp");
				lpSkillButton_Gray[i] = LoadDibSurfaceOffscreen(ButtonImageDirPath);
			}
		}
	}

}

/*----------------------------------------------------------------------------*
*						     Release
*-----------------------------------------------------------------------------*/
void cSKILL::Release()
{
	int i = 0;
	if (lpSkillGage[0]) {
		lpSkillGage[0]->Release();
		lpSkillGage[0] = 0;
	}
	if (lpSkillGage[1]) {
		lpSkillGage[1]->Release();
		lpSkillGage[1] = 0;


	}
	if (lpSelectSkill) {
		lpSelectSkill->Release();
		lpSelectSkill = 0;

	}
	for (i = 0; i < 4; i++) {
		if (lpSkillTitle[i]) {
			lpSkillTitle[i]->Release();
			lpSkillTitle[i] = 0;

		}
	}
	for (i = 0; i < 4; i++) {
		if (lpSkillTitle[i]) {
			lpSkillTitle[i]->Release();
			lpSkillTitle[i] = 0;

		}
	}
	for (i = 0; i < 17; i++) {
		if (lpSkillButton[i]) {
			lpSkillButton[i]->Release();
			lpSkillButton[i] = 0;


		}
		if (lpSkillButton_Gray[i]) {
			lpSkillButton_Gray[i]->Release();
			lpSkillButton_Gray[i] = 0;

		}
	}
	for (i = 0; i < 8; i++) {
		if (lpShortKey[i]) {
			lpShortKey[i]->Release();
			lpShortKey[i] = 0;

		}
	}
	for (i = 0; i < 10; i++) {
		if (lpWeaponIcon[i]) {
			lpWeaponIcon[i]->Release();
			lpWeaponIcon[i] = 0;
		}
	}

}
/*----------------------------------------------------------------------------*
*							     �׸���
*-----------------------------------------------------------------------------*/
int CheckVirtualLifeTime = 0;
int CheckBoosterLifeTime = 0; // ����� - �ν��� ������(�����)
int CheckVirtualManaTime = 0; // ����� - �ν��� ������(���)
int CheckVirtualStaminaTime = 0; // ����� - �ν��� ������(�ٷ�)
int CheckSkillDelayTime = 0; // �庰 - ��ų ������
bool bchecked = false;

void cSKILL::DrawUp()
{
	int i = 0;
	//���� ��ų�� �׸���
	for (i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (TempContinueSkill[i].Flag) {
			if (TempContinueSkill[i].MatIcon) {
				if (!TempContinueSkill[i].IconFlag) {
					dsDrawTexImage(MatSkillIconBackGround, 10 + TempContinueSkill[i].IconPosiX, 10, 32, 32, TempContinueSkill[i].IconAlpha);
					SkillBarDraw(&TempContinueSkill[i], 10 + 16 + TempContinueSkill[i].IconPosiX, 10 + 16, TempContinueSkill[i].IconAlpha);

					if (strcmp(TempContinueSkill[i].Skill_Info.SkillName, "Desafio") == 0)
					{
						if (bchecked == false)
						{
							char* Path = "image\\Sinimage\\skill\\keep\\QuestTimer.tga";
							MatQuestTimer = CreateTextureMaterial(Path, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
							ReadTextures();	//�ؽ��� �ε�
							bchecked = true;
						}
						dsDrawTexImage(MatQuestTimer, 10 + TempContinueSkill[i].IconPosiX, 10, 32, 32, TempContinueSkill[i].IconAlpha);
					}
					else
						dsDrawTexImage(TempContinueSkill[i].MatIcon, 10 + TempContinueSkill[i].IconPosiX, 10, 32, 32, TempContinueSkill[i].IconAlpha);
				}
			}
		}
	}

}
void cSKILL::Draw()
{
	int i = 0;

	/*
	//���� ��ų�� �׸���
	for(i = 0 ; i < MAX_CONTINUE_SKILL ; i++){
		if(TempContinueSkill[i].Flag){
			if(TempContinueSkill[i].MatIcon){
				if(!TempContinueSkill[i].IconFlag){
					dsDrawTexImage(MatSkillIconBackGround , 10+TempContinueSkill[i].IconPosiX, 10, 32, 32 , TempContinueSkill[i].IconAlpha );
					SkillBarDraw(&TempContinueSkill[i],10+16+TempContinueSkill[i].IconPosiX,10+16,TempContinueSkill[i].IconAlpha);
					dsDrawTexImage(TempContinueSkill[i].MatIcon , 10+TempContinueSkill[i].IconPosiX, 10, 32, 32 , TempContinueSkill[i].IconAlpha );
				}
			}
		}
	}
	*/

	/////////////�̹��� �׽�Ʈ 
/*
	for(i=0; i <  9 ; i++){
		if(lpWeaponIcon[i]){
			DrawSprite(100+(i*20),100,lpWeaponIcon[i],0,0,18,24);

		}
	}
*/
/////////////////��ų �ڽ� 
//dsDrawTexImage( MatSkill[0] , 0, 600-sinMoveKindInter[SIN_SKILL], 256, 256 , 255 );       
//dsDrawTexImage( MatSkill[1] , 256, 600-sinMoveKindInter[SIN_SKILL], 256, 256 , 255 );   
//dsDrawTexImage( MatSkill[2] , 256+256, 600-sinMoveKindInter[SIN_SKILL], 256, 256 , 255 );       
//dsDrawTexImage( MatSkill[3] , 256+256+256, 600-sinMoveKindInter[SIN_SKILL], 32, 256 , 255 );   

//DrawSprite(0,0,lpSkillMain,0,0,800,200);

//��ų ����2=====================================================================================
	if (SkillMain2OpenFlag) {
		DrawSprite(0, 600 - sinMoveKindInter[SIN_SKILL] + 56, lpSkillMain2, 0, 0, 800, 200);
		//����
		if (SkillMain2ButtonFlag[0]) {
			DrawSprite(13, 600 + 83 - sinMoveKindInter[SIN_SKILL] + 56, lpSkillMainLeftB, 0, 0, 20, 20);
		}
	}

	if (!SkillMain2OpenFlag)
	{
		DrawSprite(0, 600 - sinMoveKindInter[SIN_SKILL] + 56, lpSkillMain, 0, 0, 800, 200);

		if (SkillMain2ButtonFlag[1])
		{
			DrawSprite(766, 600 + 83 - sinMoveKindInter[SIN_SKILL] + 56, lpSkillMainRightB, 0, 0, 20, 20);
		}
	}

	//===========================================================================================
	if (OpenFlag && !SkillMain2OpenFlag)
	{
		for (i = 0; i < (int)sinChar->ChangeJob + 1; i++)
		{
			DrawSprite(SkillTitle[i][0], SkillTitle[i][1] + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillTitle[i], 0, 0, 100, 20);
		}

		for (i = 1; i < ChangeJobSkillPlus; i++)
		{
			if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Use && SkillMasterFlag)
			{
				if (lpSkillButton[i])
				{
					DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]),
						lpSkillButton[i], 0, 0, 49, 46);
				}
			}
			if (sinSkill.UseSkill[i].Flag && !sinSkill.UseSkill[i].Use && SkillMasterFlag)
			{
				if (lpSkillButton_Gray[i])
				{
					DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]),
						lpSkillButton_Gray[i], 0, 0, 49, 46);
				}
			}
			if (sinSkill.UseSkill[i].Flag && SkillMasterFlag && sinSkill.UseSkill[i].Point >= 10)
			{
				if (lpSkillButton_Gray[i])
				{
					DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]),
						lpSkillButton_Gray[i], 0, 0, 49, 46);
				}
			}
			if (!SkillMasterFlag)
			{
				if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Point)
				{
					if (lpSkillButton[i])
					{
						DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]),
							lpSkillButton[i], 0, 0, 49, 46);

					}
				}
				if (sinSkill.UseSkill[i].Flag && !sinSkill.UseSkill[i].Point)
				{
					if (lpSkillButton_Gray[i])
					{
						DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]),
							lpSkillButton_Gray[i], 0, 0, 49, 46);
					}
				}
			}

			if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Skill_Info.USECODE == SIN_SKILL_USE_NOT)
			{
				DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage4, 0, 0, 5, 35);
			}

			if (sinSkill.UseSkill[i].Flag && (sinSkill.UseSkill[i].Skill_Info.USECODE != SIN_SKILL_USE_NOT || sinSkill.UseSkill[i].Skill_Info.Element[0]))
			{
				DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage3, 0, 0, 5, 35);
				DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].UseSkillMasteryGage) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage2[0], 0, 35 - sinSkill.UseSkill[i].UseSkillMasteryGage, 5, 35);
				if (sinSkill.UseSkill[i].UseSkillMasteryGage >= 3)
					DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].UseSkillMasteryGage) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage2[1], 0, 0, 5, 3);

			}
			if (sinSkill.UseSkill[i].Flag)
			{
				DrawSprite(sinSkill.SkillBox[i].GageRect.right + 1, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].GageLength) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage[0], 0, 35 - sinSkill.UseSkill[i].GageLength, 5, 35);
				if (sinSkill.UseSkill[i].GageLength >= 3)
					DrawSprite(sinSkill.SkillBox[i].GageRect.right + 1, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].GageLength) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage[0], 0, 0, 5, 3);

			}

			if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Skill_Info.Element[0])
			{
				DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage5, 0, 0, 5, 35);
			}


		}
		if (DownButtonIndex) {  //��ư �ٿ� �׼�  
			DrawSprite(sinSkill.SkillBox[DownButtonIndex - 1].BoxRect.left + 1, sinSkill.SkillBox[DownButtonIndex - 1].BoxRect.top + 1 + (256 - sinMoveKindInter[SIN_SKILL]),
				lpSkillButton[DownButtonIndex - 1], 0, 0, 49, 46); //�ȼ��� �������̵� 

		}
		if (SkillButtonIndex) {
			if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag) {
				if (DownButtonIndex) {
					DrawSprite(sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.left + 1,
						sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.top + 1 + (256 - sinMoveKindInter[SIN_SKILL]),
						lpSelectSkill, 0, 0, 49, 46);

				}
				else {
					DrawSprite(sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.left,
						sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]),
						lpSelectSkill, 0, 0, 49, 46);
				}
			}

		}

		//////////////////// ShorKey 
		for (i = 0; i < ChangeJobSkillPlus; i++) {
			if (sinSkill.UseSkill[i].Flag) {
				if (sinSkill.UseSkill[i].ShortKey) {
					DrawSprite(sinSkill.SkillBox[i].BoxRect.left + 9, sinSkill.SkillBox[i].BoxRect.top - 6 + (256 - sinMoveKindInter[SIN_SKILL]),
						lpShortKey[sinSkill.UseSkill[i].ShortKey - 1], 0, 0, 16, 16);

				}
			}
		}
	}
	//���õ� ǥ�� 
	if (SkillMasteryShowFlag) {
		DrawSprite(UseSkillMasteryPosi.x, UseSkillMasteryPosi.y + (256 - sinMoveKindInter[SIN_SKILL]), lpMasteryInfo, 0, 0, 39, 27);
	}

	/////��ų �������� �������̽����� �׸��� 
	if (sinSkill.pLeftSkill) {		 //���� ��ų 
		if (sinSkill.pLeftSkill->UseSkillFlag)
			DrawSprite(sLeftRightSkill[0].BoxRect.left, sLeftRightSkill[0].BoxRect.top, //��ư 
				lpSkillButton[sinSkill.pLeftSkill->Position - 1], 0, 0, 49, 46);
		else
			DrawSprite(sLeftRightSkill[0].BoxRect.left, sLeftRightSkill[0].BoxRect.top, //��ư 
				lpSkillButton_Gray[sinSkill.pLeftSkill->Position - 1], 0, 0, 49, 46);


	}
	else { //��ų �߰��� �����ʾ����� �̹��� 
		DrawSprite(sLeftRightSkill[0].BoxRect.left, sLeftRightSkill[0].BoxRect.top, //��ư 
			lpSkillBoxBack, 0, 0, 49, 46);

	}
	if (sinSkill.pRightSkill) {		//������ ��ų  
		if (sinSkill.pRightSkill->UseSkillFlag) //��밡�� 
			DrawSprite(sLeftRightSkill[1].BoxRect.left, sLeftRightSkill[1].BoxRect.top, //��ư 
				lpSkillButton[sinSkill.pRightSkill->Position - 1], 0, 0, 49, 46);
		else	//��� �Ұ��� 
			DrawSprite(sLeftRightSkill[1].BoxRect.left, sLeftRightSkill[1].BoxRect.top, //��ư 
				lpSkillButton_Gray[sinSkill.pRightSkill->Position - 1], 0, 0, 49, 46);


	}
	else { //��ų �߰��������ʾ����� �̹��� 
		DrawSprite(sLeftRightSkill[1].BoxRect.left, sLeftRightSkill[1].BoxRect.top, //��ư 
			lpSkillBoxBack, 0, 0, 49, 46);

	}
}

void cSKILL::Main()
{
	int i = 0, j = 0;
	int k = 0, Num = 0;

	sSKILL  TempSkillData;
	CheckContinueIcon();
	memset(TempContinueSkill, 0, sizeof(sSKILL) * 20);

	for (k = 0; k < MAX_CONTINUE_SKILL; k++) {
		if (ContinueSkill[k].Flag) {
			if (ContinueSkill[k].MatIcon) {
				if (Num * 32 > ContinueSkill[k].IconPosiX) {
					ContinueSkill[k].IconPosiX += 2;
				}
				else if (Num * 32 < ContinueSkill[k].IconPosiX) {
					ContinueSkill[k].IconPosiX -= 2;

				}
				if (ContinueSkill[k].CheckTime < 255) {
					ContinueSkill[k].IconAlpha++;
				}
				if (ContinueSkill[k].CheckTime >= 255) {
					ContinueSkill[k].IconAlpha = 255;

				}
				if (((ContinueSkill[k].UseTime * 70) - ContinueSkill[k].CheckTime) < 180) {
					ContinueSkill[k].IconAlpha--;
				}
				if (ContinueSkill[k].IconAlpha > 255)ContinueSkill[k].IconAlpha = 255;
				if (ContinueSkill[k].IconAlpha < 0)ContinueSkill[k].IconAlpha = 0;

				if (ContinueSkill[k].CheckTime > (ContinueSkill[k].UseTime - 4) * 70) {
					ContinueSkill[k].IconTime++;
					if (ContinueSkill[k].IconTime > 30) {
						ContinueSkill[k].IconTime = 0;
						ContinueSkill[k].IconFlag ^= 1;
					}
				}

				memcpy(&TempContinueSkill[Num], &ContinueSkill[k], sizeof(sSKILL));
				Num++;

			}
		}
	}

	int TempXPosi = 0;
	for (i = Num; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (TempContinueSkill[j].CheckTime < TempContinueSkill[j + 1].CheckTime)
			{
				if (TempContinueSkill[j].CheckTime != 0) {
					TempSkillData = TempContinueSkill[j + 1];
					TempXPosi = TempContinueSkill[j + 1].IconPosiX;
					TempContinueSkill[j + 1] = TempContinueSkill[j];
					TempContinueSkill[j + 1].IconPosiX = TempXPosi;
					TempXPosi = TempContinueSkill[j].IconPosiX;
					TempContinueSkill[j] = TempSkillData;
					TempContinueSkill[j].IconPosiX = TempXPosi;
				}
			}
		}
	}


	if (AddVirtualLife[1]) {
		CheckVirtualLifeTime++;
		if (CheckVirtualLifeTime >= sinVirtualLifeTime * 70) 
		{
			CheckVirtualLifeTime = 0;
			AddVirtualLife[0] = 0;
			AddVirtualLife[1] = 0;
			sinVirtualLifePercent = 0;
		}
	}

	if (AddBoosterLife) {
		CheckBoosterLifeTime++;
		if (CheckBoosterLifeTime >= BoosterLifeTime * 70) {
			CheckBoosterLifeTime = 0;
			AddBoosterLife = 0;
			BoosterLifePercent = 0;
			tempLife[0] = 0;
			LifeFlag = 0;
		}
	}

	if (AddVirtualLife[1] && !AddBoosterLife)
	{
		for (i = 0; i < 10; i++)
		{
			if (ContinueSkill[i].Flag)
			{
				if (ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
				{
					AddVirtualLife[1] = ((int)sinChar->Life[1] * Virtual_Life_Percent[ContinueSkill[i].Point - 1]) / 100;
				}
			}
		}
	}
	if (AddVirtualMana[1]) {
		CheckVirtualManaTime++;
		if (CheckVirtualManaTime >= sinVirtualManaTime * 70) 
		{
			CheckVirtualManaTime = 0;
			AddVirtualMana[0] = 0;
			AddVirtualMana[1] = 0;
			sinVirtualManaPercent = 0;
			tempMana[0] = 0;
			ManaFlag = 0;
		}
	}

	if (AddVirtualStamina[1]) {
		CheckVirtualStaminaTime++;
		if (CheckVirtualStaminaTime >= sinVirtualStaminaTime * 70) 
		{
			CheckVirtualStaminaTime = 0;
			AddVirtualStamina[0] = 0;
			AddVirtualStamina[1] = 0;
			sinVirtualStaminaPercent = 0;
			tempStamina[0] = 0;
			StaminaFlag = 0;
		}
	}

	if (sinAddSkillDelay)
	{
		CheckSkillDelayTime++;
		if (CheckSkillDelayTime >= sinSkillDelayTime * 70)
		{
			CheckSkillDelayTime = 0;
			sinAddSkillDelay = 0;
			sinSkillDelayTime = 0;
			SkillDelayFlag = 0;
		}
	}

	sinCheckContinueSkill();
	CheckSkillData();

	if (!ClearSkillCODE || !CSKILL->OpenFlag || pCursorPos.y < 400) 
	{
		ClearSkillCODE = 0;
		SkillInfoShowFlag = 0;
		GAMECOREHANDLE->pcSkillInfoBox->Invalidate();
	}

	SkillMasteryShowFlag = 0;
	SelectInterSkill = 0;
	CheckingNowSkillState();
	//CheckSkillMastery();

	sinCheckChageJob(); 

	ShowSkillClose = 0; 
	SkillButtonIndex = 0;

	int Space = 0;
	sSKILLBOX TempSkillBox;
	ContinueSkillMouseIndex = 0;

	// Renderiza as skills na nova ui >>>>

	for (i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if (TempContinueSkill[i].Flag) {
			if (TempContinueSkill[i].MatIcon) {
				if (10 + (Space * 32) < pCursorPos.x && 10 + (Space * 32) + 32 > pCursorPos.x &&
					10 < pCursorPos.y && 10 + 32 > pCursorPos.y)
				{
					if (MouseButton[2] && TempContinueSkill[i].CODE == SKILL_FORCE_ORB)
						Beep(300, 300);

					TempSkillBox.BoxRect.left = 10 + (Space * 32);
					TempSkillBox.BoxRect.top = 10 + 32;
					SkillInfoShowFlag = 2;
					ContinueSkillMouseIndex = i + 1;

					GAMECOREHANDLE->pcSkillInfoBox->PrepareShowSkill(&TempContinueSkill[i], TRUE, Rectangle2D(TempSkillBox.BoxRect.left, TempSkillBox.BoxRect.top, TempSkillBox.BoxRect.right, TempSkillBox.BoxRect.bottom));
				}
				Space++;
			}
		}
	}


	if (269 < pCursorPos.x && 287 > pCursorPos.x && 571 < pCursorPos.y && 590 > pCursorPos.y)
		ShowSkillClose = 1;

	if (OpenFlag && !SkillMain2OpenFlag) {
		for (int i = 0; i < ChangeJobSkillPlus; i++) {
			if (sinSkill.UseSkill[i].Flag) {
				if (sinSkill.SkillBox[i].BoxRect.left < pCursorPos.x && sinSkill.SkillBox[i].BoxRect.right > pCursorPos.x &&
					sinSkill.SkillBox[i].BoxRect.top < pCursorPos.y && sinSkill.SkillBox[i].BoxRect.bottom > pCursorPos.y) 
				{
					SkillButtonIndex = i + 1;
					sinSkill.UseSkill[i].Position = i + 1;

					sSKILL* pSkillCopy = new sSKILL();
					CopyMemory(pSkillCopy, &sinSkill.UseSkill[i], sizeof(sSKILL));

					int skillInfoOffset = GAMECOREHANDLE->pcSkillInfoBox->GetSkillInfoLevelOffset();

					if (pSkillCopy->Point == 0 && skillInfoOffset == 0 && SkillButtonIndex != 0)
					{
						skillInfoOffset = 1;
					}

					if (pSkillCopy->Point + skillInfoOffset < 1 ||
						pSkillCopy->Point + skillInfoOffset > 10)
					{
						skillInfoOffset = 0;
						GAMECOREHANDLE->pcSkillInfoBox->Invalidate();
					}

					pSkillCopy->Point = pSkillCopy->Point + skillInfoOffset;

					pSkillCopy->Mastery = pSkillCopy->Skill_Info.RequireMastery[0] + pSkillCopy->Skill_Info.RequireMastery[1] * pSkillCopy->Point - (pSkillCopy->UseSkillMastery / 100);
					if (pSkillCopy->Mastery <= 0) pSkillCopy->Mastery = 1;
					if (pSkillCopy->Mastery > MAX_MASTERY) pSkillCopy->Mastery = MAX_MASTERY;

					if (SkillButtonIndex != 0 && GAMECOREHANDLE->pcSkillInfoBox->IsDifferentSkill(pSkillCopy))
					{
						skillInfoOffset = sinSkill.UseSkill[i].Point == 0 ? 1 : 0;
					}

					GAMECOREHANDLE->pcSkillInfoBox->SetSkillInfoLevelOffset(skillInfoOffset);

					if (GAMECOREHANDLE->pcSkillInfoBox->CanPrepareShowSkill(pSkillCopy, Rectangle2D(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top, sinSkill.SkillBox[i].BoxRect.right, sinSkill.SkillBox[i].BoxRect.bottom)))
					{
						GAMECOREHANDLE->pcSkillInfoBox->PrepareShowSkill(pSkillCopy, FALSE, Rectangle2D(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top, sinSkill.SkillBox[i].BoxRect.right, sinSkill.SkillBox[i].BoxRect.bottom));
					}

					SkillInfoShowFlag = 1;

					if (sinSkill.UseSkill[i].Point && SkillMasterFlag)
						SearchClearSkillPoint(sinSkill.UseSkill[i].CODE);

					SAFE_DELETE(pSkillCopy);

				}
				if (sinSkill.SkillBox[i].GageRect.left < pCursorPos.x && sinSkill.SkillBox[i].GageRect.right > pCursorPos.x &&
					sinSkill.SkillBox[i].GageRect.top < pCursorPos.y && sinSkill.SkillBox[i].GageRect.bottom > pCursorPos.y) {
					if (sinSkill.UseSkill[i].Skill_Info.USECODE != SIN_SKILL_USE_NOT) 
					{
						GetSkillMastery(&sinSkill.UseSkill[i], &sinSkill.SkillBox[i]);
						SkillMasteryShowFlag = 1;
					}
				}
			}
		}
	}
	for (i = 0; i < 2; i++) {
		if (sLeftRightSkill[i].BoxRect.left < pCursorPos.x && sLeftRightSkill[i].BoxRect.right > pCursorPos.x &&
			sLeftRightSkill[i].BoxRect.top < pCursorPos.y && sLeftRightSkill[i].BoxRect.bottom > pCursorPos.y) 
		{
			if (i == 0 && sinSkill.pLeftSkill) {
				cHelpPet.PetMessage("*LeftSkill", 0);

				GAMECOREHANDLE->pcSkillInfoBox->PrepareShowSkill(sinSkill.pLeftSkill, FALSE, Rectangle2D(sLeftRightSkill->BoxRect.left, sLeftRightSkill->BoxRect.top, sLeftRightSkill->BoxRect.right, sLeftRightSkill->BoxRect.bottom));

				SkillInfoShowFlag = 1;
				SelectInterSkill = 1;
			}
			if (i == 1 && sinSkill.pRightSkill) {
				cHelpPet.PetMessage("*RightSkill", 0);

				GAMECOREHANDLE->pcSkillInfoBox->PrepareShowSkill(sinSkill.pRightSkill, FALSE, Rectangle2D(sLeftRightSkill->BoxRect.left, sLeftRightSkill->BoxRect.top, sLeftRightSkill->BoxRect.right, sLeftRightSkill->BoxRect.bottom));

				SkillInfoShowFlag = 1;
				SelectInterSkill = 2;
			}

		}
	}
	if (OpenFlag && SkillMain2OpenFlag) 
	{
		if (12 < pCursorPos.x && 12 + 20 > pCursorPos.x &&
			482 < pCursorPos.y && 482 + 20 > pCursorPos.y) {
			SkillMain2ButtonFlag[0] = 1;
		}
		else {
			SkillMain2ButtonFlag[0] = 0;
		}

	}
	if (OpenFlag && !SkillMain2OpenFlag) 
	{
		if (765 < pCursorPos.x && 765 + 20 > pCursorPos.x &&
			482 < pCursorPos.y && 482 + 20 > pCursorPos.y) {
			SkillMain2ButtonFlag[1] = 1;
		}
		else {
			SkillMain2ButtonFlag[1] = 0;
		}
	}
}
void cSKILL::Close()
{

}
/*----------------------------------------------------------------------------*
*							   LButtonDown
*-----------------------------------------------------------------------------*/
void cSKILL::LButtonDown(int x, int y)
{

	for (int i = 0; i < 2; i++) {
		if (sLeftRightSkill[i].BoxRect.left < pCursorPos.x && sLeftRightSkill[i].BoxRect.right > pCursorPos.x &&
			sLeftRightSkill[i].BoxRect.top < pCursorPos.y && sLeftRightSkill[i].BoxRect.bottom > pCursorPos.y) {
			if (i == 0 && sinSkill.pLeftSkill) {
				cHelpPet.PetMessage("*LeftSkill", 1);
			}
			if (i == 1 && sinSkill.pRightSkill) {
				cHelpPet.PetMessage("*RightSkill", 1);
			}

		}
	}

	if (ClearSkillButtonPosi.x  < pCursorPos.x && ClearSkillButtonPosi.x + 45 > pCursorPos.x &&
		ClearSkillButtonPosi.y <  pCursorPos.y && ClearSkillButtonPosi.y + 45 > pCursorPos.y) {
		ClearSkillPointSection();
	}


	DownButtonUseShorKey = 0;
	LDownButtonIndex = 0;  

	if (ShowSkillClose) 
	{
		OpenFlag = 0;
	}

	if (SkillButtonIndex) 
	{
		if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag) 
		{
			LDownButtonIndex = SkillButtonIndex;
		}
	}

	DownButtonIndex = 0;

	if (ShowSkillClose) 
	{
		OpenFlag = 0;
	}
	if (SkillButtonIndex <= 13 && SkillMasterFlag == 1 && sinSkill.SkillPoint) 
	{
		if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag && sinSkill.UseSkill[SkillButtonIndex - 1].Use && sinSkill.UseSkill[SkillButtonIndex - 1].Point < 10)
		{
			DownButtonIndex = SkillButtonIndex;
			Skill4ButtonIndex = SkillButtonIndex;
		}
	}
	if (SkillButtonIndex > 13 && SkillMasterFlag == 1 && sinSkill.SkillPoint4) 
	{
		if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag && sinSkill.UseSkill[SkillButtonIndex - 1].Use && sinSkill.UseSkill[SkillButtonIndex - 1].Point < 10) {
			DownButtonIndex = SkillButtonIndex;
			Skill4ButtonIndex = SkillButtonIndex;
		}
	}

	if (SelectInterSkill) 
	{
		if (CSKILL->OpenFlag == SIN_CLOSE)CSKILL->OpenFlag = SIN_OPEN;
		else CSKILL->OpenFlag = SIN_CLOSE;
		cInterFace.CheckAllBox(SIN_SKILL);

		if (CSKILL->OpenFlag) 
		{
			if (!sinFireShow) 
			{
				StartMenuFlame(0, 350);
				sinPlaySound(0);
			}
			else
				sinPlaySound(SIN_SOUND_SHOW_INTER);
			sinFireShow = 1;
		}
	}

	if (SkillMain2ButtonFlag[1]) 
	{
		SkillMain2ButtonFlag[1] = 0;
		SkillMain2OpenFlag = 1;
		if (!lpSkillMain2)
			lpSkillMain2 = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Skil25.bmp");
	}

	if (SkillMain2ButtonFlag[0]) 
	{
		SkillMain2ButtonFlag[0] = 0;
		SkillMain2OpenFlag = 0;
	}

}
/*----------------------------------------------------------------------------*
*							   LButtonUp
*-----------------------------------------------------------------------------*/
void cSKILL::LButtonUp(int x, int y)
{

	DownButtonIndex = 0;
	LDownButtonIndex = 0; //��ư �̹��� ����ȭ 
	if (SkillButtonIndex && !DownButtonUseShorKey) {
		if ((sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_LEFT ||
			sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_ALL) && !SkillMasterFlag
			&& sinSkill.UseSkill[SkillButtonIndex - 1].Point)
			sinSkill.pLeftSkill = &sinSkill.UseSkill[SkillButtonIndex - 1];

	}
	//	if(SkillButtonIndex == 1 )  //��� ���� �̸� 
	//		sinSkill.pLeftSkill = &sinSkill.UseSkill[SkillButtonIndex-1];

		//��ų�� �й��Ѵ� 
	if (SkillButtonIndex != 1 && SkillMasterFlag == 1) {
		//4�� ��ų 
		if (SkillButtonIndex > 13 && sinSkill.SkillPoint4 > 0) {
			if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag && sinSkill.UseSkill[SkillButtonIndex - 1].Use) {
				if (sinSkill.UseSkill[SkillButtonIndex - 1].Point < MAX_USE_SKILL_POINT) { //�ִ� ��ų ����Ʈ ġ�� ���Ѵ´� 
					///////////////���⼭ �޼��� �ڽ��� ����ְ� ���� �����ϰ� ��ų�� �÷��ش� 

					pMasterSkill = &sinSkill.UseSkill[SkillButtonIndex - 1];
					cMessageBox.ShowMessage3(MESSAGE_MASTER_SKILL, sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.SkillName);
					ShowSkillUpInfo = 1;

				}
			}
		}
		//1.2.3�� ��ų
		if (SkillButtonIndex <= 13 && sinSkill.SkillPoint > 0) {
			if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag && sinSkill.UseSkill[SkillButtonIndex - 1].Use) {
				if (sinSkill.UseSkill[SkillButtonIndex - 1].Point < MAX_USE_SKILL_POINT) { //�ִ� ��ų ����Ʈ ġ�� ���Ѵ´� 
					///////////////���⼭ �޼��� �ڽ��� ����ְ� ���� �����ϰ� ��ų�� �÷��ش� 

					pMasterSkill = &sinSkill.UseSkill[SkillButtonIndex - 1];
					cMessageBox.ShowMessage3(MESSAGE_MASTER_SKILL, sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.SkillName);
					ShowSkillUpInfo = 1;

				}
			}
		}
	}
}
/*----------------------------------------------------------------------------*
*							   RButtonDown
*-----------------------------------------------------------------------------*/
void cSKILL::RButtonDown(int x, int y)
{
	for (int i = 0; i < 2; i++) {
		if (sLeftRightSkill[i].BoxRect.left < pCursorPos.x && sLeftRightSkill[i].BoxRect.right > pCursorPos.x &&
			sLeftRightSkill[i].BoxRect.top < pCursorPos.y && sLeftRightSkill[i].BoxRect.bottom > pCursorPos.y) {
			if (i == 0 && sinSkill.pLeftSkill) {
				cHelpPet.PetMessage("*LeftSkill", 2);
			}
			if (i == 1 && sinSkill.pRightSkill) {
				cHelpPet.PetMessage("*RightSkill", 2);
			}

		}
	}

	DownButtonUseShorKey = 0;
	if (SkillButtonIndex) {
		if (sinSkill.UseSkill[SkillButtonIndex - 1].Flag) {
			RDownButtonIndex = SkillButtonIndex;
		}
	}
}
/*----------------------------------------------------------------------------*
*							   RButtonUp
*-----------------------------------------------------------------------------*/
void cSKILL::RButtonUp(int x, int y)
{
	RDownButtonIndex = 0;
	LDownButtonIndex = 0; //��ư �̹��� ����ȭ 
	if (SkillButtonIndex && !DownButtonUseShorKey) {
		if ((sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_RIGHT ||
			sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_ALL) && !SkillMasterFlag &&
			sinSkill.UseSkill[SkillButtonIndex - 1].Point)
			sinSkill.pRightSkill = &sinSkill.UseSkill[SkillButtonIndex - 1];
	}

}
/*----------------------------------------------------------------------------*
*							    KeyDown
*-----------------------------------------------------------------------------*/
void cSKILL::KeyDown()
{
	//	sSkill_Info[0].FuncPointer();


	int i = 0;
	char szKeyBuff[8] = { VK_F1,VK_F2,VK_F3,VK_F4,VK_F5,VK_F6,VK_F7,VK_F8 }; //Ű���� 
	for (i = 0; i < 8; i++) {
		if (sinGetKeyClick(szKeyBuff[i])) {
			if (SkillButtonIndex) {
				//if(SkillButtonIndex == 1)break; //�ָ�Ű
				if (LDownButtonIndex) {
					if (sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_LEFT ||
						sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_ALL &&
						sinSkill.UseSkill[SkillButtonIndex - 1].Point && !SkillMasterFlag) {
						sinSkill.UseSkill[SkillButtonIndex - 1].ShortKey = i + 1;
						sinSkill.UseSkill[SkillButtonIndex - 1].MousePosi = SIN_MOUSE_POSI_LEFT;
						DownButtonUseShorKey = 1;
					}
				}
				else {
					if (RDownButtonIndex) {
						if (sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_RIGHT ||
							sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_ALL &&
							sinSkill.UseSkill[SkillButtonIndex - 1].Point && !SkillMasterFlag) {
							sinSkill.UseSkill[SkillButtonIndex - 1].ShortKey = i + 1;
							sinSkill.UseSkill[SkillButtonIndex - 1].MousePosi = SIN_MOUSE_POSI_RIGHT;
							DownButtonUseShorKey = 1;
						}
					}

				}

				for (int j = 0; j < 17; j++) {
					if (j == SkillButtonIndex - 1)continue;
					if (sinSkill.UseSkill[SkillButtonIndex - 1].ShortKey == sinSkill.UseSkill[j].ShortKey) {
						sinSkill.UseSkill[j].ShortKey = 0;
					}
				}
			}
			else {// ����Ű�� ��ų ���
				for (int j = 0; j < SIN_MAX_USE_SKILL; j++) {
					if (i == sinSkill.UseSkill[j].ShortKey - 1) {
						if (sinSkill.UseSkill[j].Point) {
							if (sinSkill.UseSkill[j].MousePosi == SIN_MOUSE_POSI_LEFT) { //����
								sinSkill.pLeftSkill = &sinSkill.UseSkill[j];

							}
							if (sinSkill.UseSkill[j].MousePosi == SIN_MOUSE_POSI_RIGHT) { //������ 
								sinSkill.pRightSkill = &sinSkill.UseSkill[j];
							}
						}
					}
				}
			}
		}
	}
	if (sinGetKeyClick('S')) {
		cHelpPet.PetMessage("*Skill", 3);
		if (CSKILL->OpenFlag)CSKILL->OpenFlag = SIN_CLOSE;
		else CSKILL->OpenFlag = SIN_OPEN;
		cInterFace.CheckAllBox(SIN_SKILL); //â�� �ϳ��� ���� 
		if (CSKILL->OpenFlag) {
			if (!sinFireShow) {
				StartMenuFlame(0, 350);
				sinPlaySound(0);
			}
			else
				sinPlaySound(SIN_SOUND_SHOW_INTER);
			sinFireShow = 1;
		}
	}

}


int cSKILL::SearchUseSkill()
{

	switch (sinChar->JOB_CODE) {
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
	if (!UseSkillBox)
		return FALSE;

	int Index = 0;
	memcpy(&sinSkill.UseSkill[0], &sSkill[0], sizeof(sSKILL));
	sinSkill.UseSkill[0].Flag = 1; //�븻 ���� default���� 
	sinSkill.UseSkill[0].Use = 1; //�븻 ���� default���� 
	sinSkill.UseSkill[0].Skill_Info.USECODE = SIN_SKILL_USE_ALL;  //�븻 ���� �������� 
	sinSkill.UseSkill[0].Point = 1;

	for (int i = 0; i < SIN_MAX_SKILL; i++) {
		if ((sSkill[i].CODE & sinSKILL_MASK1) == UseSkillBox) { //�ڽſ� �´� ��ų�� ã�´� 
			for (int j = 1; j < SIN_MAX_USE_SKILL; j++) {
				if (!sinSkill.UseSkill[j].Flag) {
					memcpy(&sinSkill.UseSkill[j], &sSkill[i], sizeof(sSKILL));
					for (int k = 0; k < SIN_MAX_SKILL; k++) {
						if (sinSkill.UseSkill[j].CODE == sSkill_Info[k].CODE) {
							memcpy(&sinSkill.UseSkill[j].Skill_Info, &sSkill_Info[k], sizeof(sSKILL_INFO));
							sinSkill.UseSkill[j].Skill_Info.SkillNum = j - 1;
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
	memcpy(&sinSkill.SkillBox, &sSkillBox, sizeof(sSKILLBOX) * SIN_MAX_USE_SKILL); //��ǥ�� �����Ѵ� 

	LoadUseSkillImage(); //��ų�̹����� �ε��Ѵ� (������ �Ҷ��� �ε����ش� )

	sinSkill.UseSkill[0].Use = 1; //�븻 ���� default���� 
	sinSkill.UseSkill[0].Skill_Info.USECODE = SIN_SKILL_USE_ALL;  //�븻 ���� �������� 
	sinSkill.UseSkill[0].Point = 1;
	ReFormCharSkillInfo(); //��ų������ �����Ѵ� (��ŷ����)
	return FALSE;
}

int JobSkillTemp = 0;

void cSKILL::CheckingNowSkillState()
{

	//�븻��ų�� ������ 4,4,4,4
	switch (sinChar->ChangeJob) {
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
	if (JobSkillTemp != ChangeJobSkillPlus) {	//��������Ÿ�� ���߿� ���ͼ� ��ġ�� �������� �����ߴ�  ������ 
		JobSkillTemp = ChangeJobSkillPlus;
		cInvenTory.SetItemToChar();
	}

	for (int j = 0; j < ChangeJobSkillPlus; j++) {
		if (j > 12) {
			if (sinSkill.SkillPoint4) { //4����ų ����Ʈ�� ������쿡�� Ȱ��ȭ ��Ų�� 
				sinSkill.UseSkill[j].Flag = 1; //����Ҽ��ִ� ��ų�� �߰��Ѵ� 
				if (sinSkill.UseSkill[j].Point <= MAX_USE_SKILL_POINT) {
					if (sinSkill.UseSkill[j - 1].Point) {//Ʈ���� ź�� 
						if (sinSkill.UseSkill[j].Skill_Info.RequireLevel + (sinSkill.UseSkill[j].Point * 2) <= sinChar->Level) //��ų�� ����Ҽ��ִ� �������� �Ǵ� 
							sinSkill.UseSkill[j].Use = 1;
						else
							sinSkill.UseSkill[j].Use = 0;
					}
				}
			}
			else { //�������� �ٽ� ��Ȱ��ȭ 
				sinSkill.UseSkill[j].Use = 0;
			}
			continue;
		}
		if (sinSkill.SkillPoint) { //��ų ����Ʈ�� ������쿡�� Ȱ��ȭ ��Ų�� 
			sinSkill.UseSkill[j].Flag = 1; //����Ҽ��ִ� ��ų�� �߰��Ѵ� 
			if (sinSkill.UseSkill[j].Point <= MAX_USE_SKILL_POINT) {
				if (j == 0)continue; //�븻 ��ų 
				if (sinSkill.UseSkill[j - 1].Point) {//Ʈ���� ź�� 
					if (sinSkill.UseSkill[j].Skill_Info.RequireLevel + (sinSkill.UseSkill[j].Point * 2) <= sinChar->Level) //��ų�� ����Ҽ��ִ� �������� �Ǵ� 
						sinSkill.UseSkill[j].Use = 1;
					else
						sinSkill.UseSkill[j].Use = 0;
				}
			}
		}
		else 
		{
			sinSkill.UseSkill[j].Use = 0;
		}
	}
}


void cSKILL::CheckSkillMastery()
{
	int TempLenght = 0;
	int TempTalent = 0;

	if (sinSkill.pLeftSkill) {
		if (!sinSkill.pLeftSkill->Point)
			sinSkill.pLeftSkill->UseSkillFlag = 0;
	}
	if (sinSkill.pRightSkill) {
		if (!sinSkill.pRightSkill->Point)
			sinSkill.pRightSkill->UseSkillFlag = 0;
	}

	for (int j = 1; j < SIN_MAX_USE_SKILL; j++) 
	{
		if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point) 
		{
			CheckSkillMasteryForm(0, j);

			if (sinSkill.UseSkill[j].Mastery == 0) {
				sinSkill.UseSkill[j].GageLength = 0;
				sinSkill.UseSkill[j].GageLength2 = 0;
				SkillCountTime2[j] = 0;

			}

			TempTalent = (int)(sinChar->Talent / 3) + (int)sinAdd_fMagic_Mastery;
			if (TempTalent > 50)TempTalent = 50;
			sinSkill.UseSkill[j].UseSkillMastery = (int)(TempTalent * 100) + sinSkill.UseSkill[j].UseSkillCount;
			if (sinSkill.UseSkill[j].Skill_Info.Element[0]) 
			{ 
				sinSkill.UseSkill[j].UseSkillMastery = 10000;

			}

			if (sinSkill.UseSkill[j].UseSkillMastery >= 10000)sinSkill.UseSkill[j].UseSkillMastery = 10000;
			if (sinSkill.UseSkill[j].UseSkillMastery) {
				sinSkill.UseSkill[j].UseSkillMasteryGage = (int)((35 * ((float)sinSkill.UseSkill[j].UseSkillMastery / 10000)));
				if (sinSkill.UseSkill[j].UseSkillMasteryGage > 35)sinSkill.UseSkill[j].UseSkillMasteryGage = 35;
			}

			sinSkill.UseSkill[j].Mastery = (sinSkill.UseSkill[j].Skill_Info.RequireMastery[0] + (sinSkill.UseSkill[j].Skill_Info.RequireMastery[1] * sinSkill.UseSkill[j].Point) -
				(sinSkill.UseSkill[j].UseSkillMastery / 100));
			if (sinSkill.UseSkill[j].Mastery <= 0) sinSkill.UseSkill[j].Mastery = 1;
			if (sinSkill.UseSkill[j].Mastery > 70)sinSkill.UseSkill[j].Mastery = 70;

			if (sinAddSkillDelay)
			{
				sinSkill.UseSkill[j].Mastery = 1;
			}

			else
			{
				sinSkill.UseSkill[j].Mastery = (sinSkill.UseSkill[j].Skill_Info.RequireMastery[0] + (sinSkill.UseSkill[j].Skill_Info.RequireMastery[1] * sinSkill.UseSkill[j].Point) -
					(sinSkill.UseSkill[j].UseSkillMastery / 100));

				if (sinSkill.UseSkill[j].Mastery <= 0) sinSkill.UseSkill[j].Mastery = 1;
				if (sinSkill.UseSkill[j].Mastery > 70)sinSkill.UseSkill[j].Mastery = 70;
			}

			TempLenght = (int)(35 / ((float)sinSkill.UseSkill[j].Mastery / 2));

			sinSkill.UseSkill[j].GageLength2 += TempLenght;

			if (sinSkill.UseSkill[j].GageLength < sinSkill.UseSkill[j].GageLength2) {
				SkillCountTime2[j]++;
				if (SkillCountTime2[j] >= (int)(35 / (float)TempLenght)) {
					sinSkill.UseSkill[j].GageLength++;
					SkillCountTime2[j] = 0;

				}

			}

			if (sinSkill.UseSkill[j].GageLength >= 35) 
			{
				// Skill pronta para o uso
				sinSkill.UseSkill[j].GageLength = 35;
				sinSkill.UseSkill[j].GageLength2 = 35;
				sinSkill.UseSkill[j].UseSkillFlag = 1;
				CheckUseSkillState(&sinSkill.UseSkill[j]);
			}
			else
			{
			//	CHATBOX->AddDebugMessage("Gage: %d - Gage2: %d - Temp: %d", sinSkill.UseSkill[j].GageLength, sinSkill.UseSkill[j].GageLength2, TempLenght);
				sinSkill.UseSkill[j].UseSkillFlag = 0; // Skill em delay
			}

			ReformSkillMasteryForm(0, j);

		}

	}
}

DWORD UseSkillItemInfo[10] = { 0,sinWA1,sinWM1,sinWH1,sinDS1,sinWP1,sinWS2,sinWC1,sinWS1,sinWT1 };

int cSKILL::GetInfoBoxSize(sSKILLBOX* pSkillBox, int Col, int Icon)
{
	int ty, tx;

	SkillBoxSize.x = 16;
	SkillBoxSize.y = Col + 1;

	SkillInfoBoxPosi.x = (pSkillBox->BoxRect.left - 112) + 20;
	SkillInfoBoxPosi.y = pSkillBox->BoxRect.top - (SkillBoxSize.y * 16);

	if (Icon) {
		SkillInfoBoxPosi.x = pSkillBox->BoxRect.left;
		SkillInfoBoxPosi.y = pSkillBox->BoxRect.top;

	}

	ty = SkillInfoBoxPosi.y + (SkillBoxSize.y * 16);
	tx = SkillInfoBoxPosi.x + (SkillBoxSize.x * 16);

	if (SkillInfoBoxPosi.y < 0)
		SkillInfoBoxPosi.y = 0;
	if (SkillInfoBoxPosi.x < 0)
		SkillInfoBoxPosi.x = 0;

	if (ty > 600)
		SkillInfoBoxPosi.y -= (ty - 600);
	if (tx > 800)
		SkillInfoBoxPosi.x -= (tx - 800);

	return TRUE;
}


int cSKILL::GetSkillMastery(sSKILL* pSkill, sSKILLBOX* pSkillBox)
{
	int SkillMasteryTemp = 0;
	SkillMasteryTemp = ((int)pSkill->UseSkillMastery / 100);
	wsprintf(szUseSkillMastery, "%d", SkillMasteryTemp);

	UseSkillMasteryPosi.x = pSkillBox->GageRect.left - (34 / 2);
	UseSkillMasteryPosi.y = pSkillBox->GageRect.top - 29;

	return TRUE;
}


int cSKILL::CheckUseSkillState(sSKILL* pSkill)
{
	if (pSkill->Skill_Info.UseMana)
	{
		if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1 && chaPremiumitem.m_StaminaReducePotiontime > 0)
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - ((pSkill->Skill_Info.UseMana[pSkill->Point - 1] *
				chaPremiumitem.m_ManaReducePotionValue / 100) + (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * 20 / 100)) &&
				sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) - ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
			{
				pSkill->UseSkillFlag = 1;
			}

			else
				pSkill->UseSkillFlag = 0;
		}

		// �庰 - �������ེ, �ٷ¸��ེ
		else if (chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_StaminaReducePotiontime > 0)
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * chaPremiumitem.m_ManaReducePotionValue / 100) &&
				sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) - ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
			{
				pSkill->UseSkillFlag = 1;
			}
			else
				pSkill->UseSkillFlag = 0;
		}

		// �庰 - �׸�, �ٷ¸��ེ
		else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1 && chaPremiumitem.m_StaminaReducePotiontime > 0)
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * 20 / 100) &&
				sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) - ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
			{
				pSkill->UseSkillFlag = 1;
			}
			else
				pSkill->UseSkillFlag = 0;
		}

		// �庰 - �������ེ
		else if (chaPremiumitem.m_ManaReducePotiontime > 0)
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * chaPremiumitem.m_ManaReducePotionValue / 100) &&
				sinGetStamina() >= pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1)))
			{
				pSkill->UseSkillFlag = 1;
			}
			else
				pSkill->UseSkillFlag = 0;
		}

		// �庰 - �׸�
		else if (chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * 20 / 100) &&
				sinGetStamina() >= pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1)))
			{
				pSkill->UseSkillFlag = 1;
			}
			else
				pSkill->UseSkillFlag = 0;
		}

		// �庰 - �ٷ¸��ེ
		else if (chaPremiumitem.m_StaminaReducePotiontime > 0)
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] &&
				sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) - ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
			{
				pSkill->UseSkillFlag = 1;

			}
			else
				pSkill->UseSkillFlag = 0;
		}

		// ������ ��� ���ߴ�
		else
		{
			if (sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] &&
				sinGetStamina() >= pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1)))
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
int cSKILL::InitSkillPoint(int kind)
{
	//kind 0 �̺�Ʈ �ʱ�ȭkind 1���彺�� �ʱ�ȭ
	switch (kind) {
	case 0:
		if (!sinInitPointPassFlag) {
			if (sinChar->wVersion[1] == 1) {
				cMessageBox.ShowMessage(MESSAGE_ALREADY_INITSTATE);
				return FALSE;
			}
		}
		break;
	}
	sinInitPointPassFlag = 0;

	CheckingNowSkillState(); //��ų����Ʈ�� 
	CheckCharForm();//���� 
	int Count = 0;
	int Count2 = 0;

	for (int j = 1; j < ChangeJobSkillPlus; j++) {
		if (j > 12) {
			if (sinSkill.UseSkill[j].Point > 0)
				Count2 += sinSkill.UseSkill[j].Point;
		}
		else {
			if (sinSkill.UseSkill[j].Point > 0)
				Count += sinSkill.UseSkill[j].Point;
		}

		CSKILL->CheckSkillMasteryForm(0, j); // ��ų �����͸��� üũ�Ѵ�
		CheckSkillPointForm(&sinSkill.UseSkill[j]);
		sinSkill.UseSkill[j].Point = 0; //��ų����Ʈ �ʱ�ȭ 
		sinSkill.UseSkill[j].GageLength = 0;
		sinSkill.UseSkill[j].GageLength2 = 0;
		sinSkill.UseSkill[j].Mastery = 0;
		sinSkill.UseSkill[j].UseSKillIncreCount = 0;
		sinSkill.UseSkill[j].UseSkillCount = 0;
		sinSkill.UseSkill[j].UseSkillMastery = 0;
		sinSkill.UseSkill[j].UseSkillMasteryGage = 0;
		sinSkill.UseSkill[j].Use = 0;
		ReformSkillPointForm(&sinSkill.UseSkill[j]);
		ReformSkillMasteryForm(0, j);

	}
	sinSkill.SkillPoint += Count;
	sinSkill.SkillPoint4 += Count2;
	sinChar->wVersion[1] = 1;
	ReformCharForm();//������ 
	cMessageBox.ShowMessage(MESSAGE_GYUNGFUM_OK);
	cInvenTory.SetItemToChar();

	return TRUE;
}

//DWORD ClearSkillPointCODE[10] = {SKILL_HOLY_BODY , SKILL_HOLY_MIND , 0,0,0,0,0,0,0,0};
DWORD ClearSkillPointCODE[10] = { 0,0,0,0,0,0,0,0,0,0 }; //�κ� ��ų �ʱ�ȭ 

int cSKILL::SearchClearSkillPoint(DWORD CODE)
{

	for (int i = 0; i < 10; i++) {
		if (ClearSkillPointCODE[i] == CODE) {
			ClearSkillCODE = ClearSkillPointCODE[i];
			return TRUE;
		}
		else
			ClearSkillCODE = 0;
	}

	return FALSE;

}

////////////// �ʱ�ȭ�� ��ų����Ʈ�� �ʱ�ȭ ��ư�� ���� 
int cSKILL::ShowClearSkillPointButton(int x, int y)
{
	ClearSkillButtonPosi.x = -50;
	ClearSkillButtonPosi.y = -50;

	if (ClearSkillCODE && !sinMessageBoxShowFlag) {
		ClearSkillButtonPosi.x = x - 57;
		ClearSkillButtonPosi.y = y - 51;
		DrawSprite(ClearSkillButtonPosi.x, ClearSkillButtonPosi.y, lpSkillDown, 0, 0, 50, 44);
	}

	return TRUE;
}

////////////// Ư�� ��ų����Ʈ�� �ʱ�ȭ�Ѵ� 
int cSKILL::ClearSkillPointSection()
{

	CheckingNowSkillState(); //��ų����Ʈ�� 
	CheckCharForm();//���� 
	int Count = 0;
	for (int j = 1; j < ChangeJobSkillPlus; j++) {
		if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point > 1) {
			for (int i = 0; i < 10; i++) {
				if (sinSkill.UseSkill[j].CODE == ClearSkillPointCODE[i]) {
					CSKILL->CheckSkillMasteryForm(0, j); // ��ų �����͸��� üũ�Ѵ�
					CheckSkillPointForm(&sinSkill.UseSkill[j]);
					sinSkill.UseSkill[j].Point--; //��ų����Ʈ �ʱ�ȭ 
					sinSkill.UseSkill[j].GageLength = 0;
					sinSkill.UseSkill[j].GageLength2 = 0;
					sinSkill.UseSkill[j].Mastery = 0;
					sinSkill.UseSkill[j].UseSKillIncreCount = 0;
					sinSkill.UseSkill[j].UseSkillCount = 0;
					sinSkill.UseSkill[j].UseSkillMastery = 0;
					sinSkill.UseSkill[j].UseSkillMasteryGage = 0;
					sinSkill.UseSkill[j].Use = 0;
					ReformSkillPointForm(&sinSkill.UseSkill[j]);
					ReformSkillMasteryForm(0, j);
					sinSkill.SkillPoint++;
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


unsigned int CharSkillInfoData[8] = { 0, }; //ĳ������ CheckSum�̼��õ� �迭 
int   ChangeJob = -1;
//ĳ���ͺ� SkillInfo�� �����Ѵ� 
int cSKILL::ReFormCharSkillInfo()
{
	int   i = 0, j = 0, k = 0;
	int   CharNum = 0;

	int   CharCode[8] = { SIN_CHAR_MECANICIAN,SIN_CHAR_FIGHTER,SIN_CHAR_ARCHER,SIN_CHAR_PIKEMAN,SIN_CHAR_KNIGHT,SIN_CHAR_ATALANTA,SIN_CHAR_PRIESTESS,SIN_CHAR_MAGICIAN };
	//�ڽ��� ������ ���Ѵ� 
	for (i = 0; i < 8; i++) {
		if (sinChar->JOB_CODE == CharCode[i]) {
			CharNum = i;
			break;
		}
	}

	if (ChangeJob != sinChar->ChangeJob) {
		ChangeJob = sinChar->ChangeJob;
		CharSkillInfoData[CharNum] = 0; //�ʱ�ȭ 
		for (j = 1; j < SIN_MAX_USE_SKILL; j++) {
			if (sinSkill.UseSkill[j].Flag) {
				k = j + 1;
				CharSkillInfoData[CharNum] += k * sinSkill.UseSkill[j].Skill_Info.RequireLevel;
				CharSkillInfoData[CharNum] += k * sinSkill.UseSkill[j].Skill_Info.UseStamina[0];
				CharSkillInfoData[CharNum] += k * sinSkill.UseSkill[j].Skill_Info.UseStamina[1];
			}
		}
	}
	return TRUE;
}

int cSKILL::CheckCharSkillInfo()
{
	int   i = 0, j = 0, k = 0;
	int   CharNum = 0;
	int   CharCode[8] = { SIN_CHAR_MECANICIAN,SIN_CHAR_FIGHTER,SIN_CHAR_ARCHER,SIN_CHAR_PIKEMAN,SIN_CHAR_KNIGHT,SIN_CHAR_ATALANTA,SIN_CHAR_PRIESTESS,SIN_CHAR_MAGICIAN };

	unsigned int CharSkillInfoDataCheckSum[8] = { 0, };

	for (i = 0; i < 8; i++) 
	{
		if (sinChar->JOB_CODE == CharCode[i]) 
		{
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

int cSKILL::CheckSkillMasteryForm(sSKILL* pSkill, int Index)
{
	if (pSkill) {
		for (int j = 1; j < SIN_MAX_USE_SKILL; j++) {
			if (sinSkill.UseSkill[j].Flag) {
				if (pSkill->CODE == sinSkill.UseSkill[j].CODE) {
					Index = j;
					break;
				}
			}
		}
	}

	int CheckMasteryDataSum = lpCurPlayer->dwObjectSerial + sinSkill.UseSkill[Index].CODE;

	CheckMasteryDataSum += (sinSkill.UseSkill[Index].GageLength * Index);
	CheckMasteryDataSum += (sinSkill.UseSkill[Index].GageLength2 * Index);
	CheckMasteryDataSum += (sinSkill.UseSkill[Index].Mastery * Index);

	if (CheckMasteryData[Index] != CheckMasteryDataSum) 
	{
		SendSetHackUser3(52, CheckMasteryData[Index], CheckMasteryDataSum);
		return FALSE;

	}

	return TRUE;
}
int cSKILL::ReformSkillMasteryForm(sSKILL* pSkill, int Index)
{

	if (pSkill) {
		for (int j = 1; j < SIN_MAX_USE_SKILL; j++) {
			if (sinSkill.UseSkill[j].Flag) {
				if (pSkill->CODE == sinSkill.UseSkill[j].CODE) {
					Index = j;
				}
			}
		}
	}

	CheckMasteryData[Index] = lpCurPlayer->dwObjectSerial + sinSkill.UseSkill[Index].CODE;
	CheckMasteryData[Index] += (sinSkill.UseSkill[Index].GageLength * Index);
	CheckMasteryData[Index] += (sinSkill.UseSkill[Index].GageLength2 * Index);
	CheckMasteryData[Index] += (sinSkill.UseSkill[Index].Mastery * Index);

	return TRUE;
}

int cSKILL::CheckSkillPointForm(sSKILL* pSkill)
{
	DWORD	dwXorKey = lpCurPlayer->dwObjectSerial & 0x5F;

	for (int j = 1; j < SIN_MAX_USE_SKILL; j++) 
	{
		if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Use && sinSkill.UseSkill[j].Point) 
		{
			if (pSkill->CODE == sinSkill.UseSkill[j].CODE) 
			{
				if (CheckSkillPointData[j] != (sinSkill.UseSkill[j].Point ^ dwXorKey)) {
					SendSetHackUser3(54, CheckSkillPointData[j], sinSkill.UseSkill[j].Point);
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}

int cSKILL::ReformSkillPointForm(sSKILL* pSkill)
{
	DWORD	dwXorKey = lpCurPlayer->dwObjectSerial & 0x5F;

	for (int j = 1; j < SIN_MAX_USE_SKILL; j++) {
		if (sinSkill.UseSkill[j].Flag) {
			if (pSkill->CODE == sinSkill.UseSkill[j].CODE) {
				CheckSkillPointData[j] = (sinSkill.UseSkill[j].Point ^ dwXorKey);
				break;
			}
		}
	}
	return TRUE;
}

int cSKILL::InitReformSkillPointForm()
{
	return TRUE;
}

int cSKILL::GetSkillPoint(DWORD CODE)
{
	for (int j = 1; j < SIN_MAX_USE_SKILL; j++) {
		if (sinSkill.UseSkill[j].Flag) {
			if (CODE == sinSkill.UseSkill[j].CODE) {
				return sinSkill.UseSkill[j].Point;
			}
		}
	}

	return 0;
}

int cSKILL::SearchContiueSkill(DWORD CODE)
{
	for (int k = 0; k < 18; k++) {
		if (ContinueSkill[k].Flag) {
			if (ContinueSkill[k].CODE == CODE) {
				return ContinueSkill[k].Point;

			}
		}
	}
	return 0;
}

int cSKILL::SearchContiueSkillIndex(DWORD CODE)
{
	for (int k = 0; k < 18; k++) {
		if (ContinueSkill[k].Flag) {
			if (ContinueSkill[k].CODE == CODE) {
				return k + 1;
			}
		}
	}
	return 0;
}

int cSKILL::SearchContiueSkillCODE(DWORD CODE)
{
	for (int k = 0; k < 18; k++) {
		if (ContinueSkill[k].Flag) {
			if (ContinueSkill[k].CODE == CODE) {
				return ContinueSkill[k].CODE;
			}
		}
	}
	return 0;
}

int AddVirtualLife[2] = { 0,0 };
int sinVirtualLifeTime = 0;
int sinVirtualLifePercent = 0;
int AddBoosterLife = 0;
int BoosterLifeTime = 0;
int BoosterLifePercent = 0;
int LifeFlag = 0;
short tempLife[2] = { 0,0 };
int AddVirtualMana[2] = { 0,0 };
int sinVirtualManaTime = 0;
int sinVirtualManaPercent = 0;
int ManaFlag = 0;
short tempMana[2] = { 0,0 };
int AddVirtualStamina[2] = { 0,0 };
int sinVirtualStaminaTime = 0;
int sinVirtualStaminaPercent = 0;
int StaminaFlag = 0;
short tempStamina[2] = { 0,0 };
int sinAddSkillDelay = 0;
int sinSkillDelayTime = 0;
int SkillDelayFlag = 0;

int cSKILL::SetVirtualLife(int Time, int Point)
{
	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (ContinueSkill[i].Flag) 
		{
			if (ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE) 
			{
				return FALSE;
			}
		}
	}

	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (!ContinueSkill[i].Flag) {
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_VIRTUAL_LIFE;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}

	AddVirtualLife[1] = ((int)sinChar->Life[1] * Virtual_Life_Percent[Point - 1]) / 100;
	sinVirtualLifeTime = Time;
	sinVirtualLifePercent = Virtual_Life_Percent[Point - 1];
	CheckVirtualLifeTime = 0; //üũ�ð��ʱ�ȭ
	cInvenTory.SetItemToChar();
	return TRUE;
}

// ����� - �ν��� ������
int cSKILL::UseBoosterItem(sITEM* pItem)
{
	if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE)
		return FALSE; //���������� ������Ѵ�

	DWORD BoosterCODE;
	DWORD ItemMask;
	int BoosterTime = 0;
	int cnt = 0;

	ItemMask = pItem->CODE & sinITEM_MASK3;
	if (ItemMask == sin21 || ItemMask == sin24 || ItemMask == sin27) cnt = 0;
	if (ItemMask == sin22 || ItemMask == sin25 || ItemMask == sin28) cnt = 1;
	if (ItemMask == sin23 || ItemMask == sin26 || ItemMask == sin29) cnt = 2;

	switch (ItemMask) {
	case sin21: // ����� - 1�ð�
	case sin22: // ����� - 3�ð�
	case sin23: // ����� - 1��
		BoosterCODE = BOOSTER_ITEM_LIFE;
		BoosterTime = BoosterItem_UseTime[cnt];

		AddBoosterLife = ((int)sinChar->Life[1] * BoosterItem_DataPercent[0]) / 100;
		BoosterLifeTime = BoosterTime;
		BoosterLifePercent = BoosterItem_DataPercent[0];
		CheckBoosterLifeTime = 0; //üũ�ð��ʱ�ȭ
		break;
	case sin24: // ��� - 1�ð�
	case sin25: // ��� - 3�ð�
	case sin26: // ��� - 1��
		BoosterCODE = BOOSTER_ITEM_MANA;
		BoosterTime = BoosterItem_UseTime[cnt];

		// ����� - �ν��� ������(���)
		AddVirtualMana[1] = ((int)sinChar->Mana[1] * BoosterItem_DataPercent[1]) / 100;
		sinVirtualManaTime = BoosterTime;
		sinVirtualManaPercent = BoosterItem_DataPercent[1];
		CheckVirtualManaTime = 0; //üũ�ð��ʱ�ȭ
		break;
	case sin27: // �ٷ� - 1�ð�
	case sin28: // �ٷ� - 3�ð�
	case sin29: // �ٷ� - 1��
		BoosterCODE = BOOSTER_ITEM_STAMINA;
		BoosterTime = BoosterItem_UseTime[cnt];

		// ����� - �ν��� ������(�ٷ�)
		AddVirtualStamina[1] = ((int)sinChar->Stamina[1] * BoosterItem_DataPercent[2]) / 100;
		sinVirtualStaminaTime = BoosterTime;
		sinVirtualStaminaPercent = BoosterItem_DataPercent[2];
		CheckVirtualStaminaTime = 0; //üũ�ð��ʱ�ȭ
		break;
	}
	//�ش� �Ŵ� �������� ������ �����۽�ų�� �����Ѵ�.
	sSKILL TempSkill;

	if (CSKILL->SearchContiueSkillCODE(BoosterCODE) == BoosterCODE && BoosterCODE != 0) {
		cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
		haCastleSkillUseFlag = 0;
		return TRUE;
	}
	haCastleSkillUseFlag = 1;

	for (int j = 0; j < SIN_MAX_SKILL; j++) {
		if (sSkill[j].CODE == BoosterCODE) {
			memcpy(&TempSkill, &sSkill[j], sizeof(sSKILL));
			TempSkill.UseTime = BoosterTime;
			sinContinueSkillSet(&TempSkill);
			SwitchSkill(&TempSkill);
			break;
		}
	}

	tempLife[1] = sinChar->Level;
	tempMana[1] = sinChar->Level;
	tempStamina[1] = sinChar->Level;

	sinPlaySound(SIN_SOUND_EAT_POTION2);//��� ����
	cInvenTory.SetItemToChar();
	return TRUE;
}

// ����� - ������ �ν��͸� �����Ѵ�
int cSKILL::SetBoosterItem(DWORD ItemCODE, int Time)
{
	int UseFlag = 0;
	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));
	char* Path;

	DWORD ItemMask;
	int cnt = 0;

	ItemMask = ItemCODE & sinITEM_MASK3;

	if (ItemMask == sin21 || ItemMask == sin24 || ItemMask == sin27) cnt = 0; // 1�ð�
	if (ItemMask == sin22 || ItemMask == sin25 || ItemMask == sin28) cnt = 1; // 3�ð�
	if (ItemMask == sin23 || ItemMask == sin26 || ItemMask == sin29) cnt = 2; // 1��


	switch (ItemMask)
	{
		// ����� �ν���
	case sin21:
	case sin22:
	case sin23:
		UseFlag = 0;
		Path = "image\\Sinimage\\skill\\keep\\Booster_01.tga";
		TempSkill.CODE = BOOSTER_ITEM_LIFE;
		TempSkill.Point = 0; // �ν��� �������� ������ ����.
		TempSkill.UseTime = BoosterItem_UseTime[cnt];
		TempSkill.CheckTime = (BoosterItem_UseTime[cnt] * 70) - (Time * 70);
		TempSkill.MatIcon = Mat_BoosterItem[UseFlag];
		break;

		// ��� �ν���
	case sin24:
	case sin25:
	case sin26:
		UseFlag = 1;
		Path = "image\\Sinimage\\skill\\keep\\Booster_02.tga";
		TempSkill.CODE = BOOSTER_ITEM_MANA;
		TempSkill.Point = 0; // �ν��� �������� ������ ����.
		TempSkill.UseTime = BoosterItem_UseTime[cnt];
		TempSkill.CheckTime = (BoosterItem_UseTime[cnt] * 70) - (Time * 70);
		TempSkill.MatIcon = Mat_BoosterItem[UseFlag];
		break;

		// �ٷ� �ν���
	case sin27:
	case sin28:
	case sin29:
		UseFlag = 2;
		Path = "image\\Sinimage\\skill\\keep\\Booster_03.tga";
		TempSkill.CODE = BOOSTER_ITEM_STAMINA;
		TempSkill.Point = 0; // �ν��� �������� ������ ����.
		TempSkill.UseTime = BoosterItem_UseTime[cnt];
		TempSkill.CheckTime = (BoosterItem_UseTime[cnt] * 70) - (Time * 70);
		TempSkill.MatIcon = Mat_BoosterItem[UseFlag];
		break;
	}

	char szBuff[128];
	if (!Mat_BoosterItem[UseFlag]) {
		wsprintf(szBuff, Path, UseFlag);
		Mat_BoosterItem[UseFlag] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();	//�ؽ��� �ε�
	}

	sinContinueSkillSet(&TempSkill);

	if (UseFlag == 0)
	{
		// ����� - �ν��� ������(�����)
		AddBoosterLife = ((int)sinChar->Life[1] * BoosterItem_DataPercent[UseFlag]) / 100;
		BoosterLifeTime = Time;
		BoosterLifePercent = BoosterItem_DataPercent[UseFlag];
		CheckBoosterLifeTime = 0; //üũ�ð��ʱ�ȭ
	}
	else if (UseFlag == 1)
	{
		// ����� - �ν��� ������(���)
		AddVirtualMana[1] = ((int)sinChar->Mana[1] * BoosterItem_DataPercent[UseFlag]) / 100;
		sinVirtualManaTime = Time;
		sinVirtualManaPercent = BoosterItem_DataPercent[UseFlag];
		CheckVirtualManaTime = 0; //üũ�ð��ʱ�ȭ
	}
	else if (UseFlag == 2)
	{
		// ����� - �ν��� ������(�ٷ�)
		AddVirtualStamina[1] = ((int)sinChar->Stamina[1] * BoosterItem_DataPercent[UseFlag]) / 100;
		sinVirtualStaminaTime = Time;
		sinVirtualStaminaPercent = BoosterItem_DataPercent[UseFlag];
		CheckVirtualStaminaTime = 0; //üũ�ð��ʱ�ȭ
	}

	cInvenTory.SetItemToChar();

	return TRUE;
}

// �庰 - ��ų ������
int cSKILL::SetSkillDelayItem(DWORD ItemCODE, int Time)
{
	int UseFlag = 0;
	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));
	char* Path;

	DWORD ItemMask;
	int cnt = 0;

	ItemMask = ItemCODE & sinITEM_MASK3;

	if (ItemMask == sin30 || ItemMask == sin33 || ItemMask == sin36) cnt = 0;
	if (ItemMask == sin31 || ItemMask == sin34 || ItemMask == sin37) cnt = 1;
	if (ItemMask == sin32 || ItemMask == sin35 || ItemMask == sin38) cnt = 2;

	switch (ItemMask)
	{
		// ����� �ν���
	case sin30:
	case sin31:
	case sin32:
		UseFlag = 0;
		Path = "image\\Sinimage\\skill\\keep\\Booster_01.tga";
		TempSkill.CODE = SKILLDELAY_ITEM_LIFE;
		TempSkill.Point = 0;
		TempSkill.UseTime = nSkillDelay_UseTime[cnt];
		TempSkill.CheckTime = (nSkillDelay_UseTime[cnt] * 70) - (Time * 70);
		TempSkill.MatIcon = nMat_SkillDelayItem[UseFlag];
		break;
	}


	char szBuff[128];
	if (!nMat_SkillDelayItem[UseFlag]) {
		wsprintf(szBuff, Path, UseFlag);
		nMat_SkillDelayItem[UseFlag] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();	//�ؽ��� �ε�
	}

	sinContinueSkillSet(&TempSkill);

	if (UseFlag == 0)
	{
		sinAddSkillDelay = 10;
		sinSkillDelayTime = Time;
		BoosterLifePercent = BoosterItem_DataPercent[UseFlag];
		CheckSkillDelayTime = 0; //üũ�ð��ʱ�ȭ
	}


	cInvenTory.SetItemToChar();

	return TRUE;
}


// �庰 - ��ų ������
int cSKILL::UseSkillDelayItem(sITEM* pItem)
{
	DWORD SkillDelayCODE;
	DWORD ItemMask;
	int SkillDelayTime = 0;
	int cnt = 0;

	ItemMask = pItem->CODE & sinITEM_MASK3;
	if (ItemMask == sin30 || ItemMask == sin33 || ItemMask == sin36) cnt = 0;
	if (ItemMask == sin31 || ItemMask == sin34 || ItemMask == sin37) cnt = 1;
	if (ItemMask == sin32 || ItemMask == sin35 || ItemMask == sin38) cnt = 2;

	switch (ItemMask) {
	case sin30: // 1�ð�
	case sin31: // 3�ð�
	case sin32: // 1��
		SkillDelayCODE = SKILLDELAY_ITEM_LIFE;
		SkillDelayTime = nSkillDelay_UseTime[cnt];

		sinAddSkillDelay = 10;
		sinSkillDelayTime = SkillDelayTime;
		CheckSkillDelayTime = 0; //üũ�ð��ʱ�ȭ
		break;
	}
	//�ش� �Ŵ� �������� ������ �����۽�ų�� �����Ѵ�.
	sSKILL TempSkill;

	if (CSKILL->SearchContiueSkillCODE(SkillDelayCODE) == SkillDelayCODE && SkillDelayCODE != 0) {
		cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
		haCastleSkillUseFlag = 0;
		return TRUE;
	}
	haCastleSkillUseFlag = 1;

	for (int j = 0; j < SIN_MAX_SKILL; j++) {
		if (sSkill[j].CODE == SkillDelayCODE) {
			memcpy(&TempSkill, &sSkill[j], sizeof(sSKILL));
			TempSkill.UseTime = SkillDelayTime;
			sinContinueSkillSet(&TempSkill);
			SwitchSkill(&TempSkill);
			break;
		}
	}

	sinPlaySound(SIN_SOUND_EAT_POTION2);//��� ����
	cInvenTory.SetItemToChar();
	return TRUE;
}


//Ʈ���̾��� ���� ���Ҷ�
int cSKILL::SetT_Of_Valhalla(int Point, int LV)
{

	//Contiue �ʱ�ȭ
	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (ContinueSkill[i].Flag) {
			if (ContinueSkill[i].CODE == SKILL_TRIUMPH_OF_VALHALLA || ContinueSkill[i].CODE == SKILL_HALL_OF_VALHALLA) {
				//memset(&ContinueSkill[i],0,sizeof(sSKILL));
				return FALSE; //�ߺ����� �Ұ�
			}
		}
	}

	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (!ContinueSkill[i].Flag) {
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_TRIUMPH_OF_VALHALLA;
			ContinueSkill[i].UseTime = T_Of_Valhalla_Time[Point - 1];
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}

	SetT_Of_ValhallaLV = LV;

	if (SetT_Of_ValhallaFlag2) { //�ڽ��� ����Ѱ��̸�
		SetT_Of_ValhallaFlag2 = 0;
		SetT_Of_ValhallaFlag = 0;
	}
	else {
		SetT_Of_ValhallaFlag = 1; //���̻�����ذ��̸�

	}
	cInvenTory.SetItemToChar();
	return TRUE;
}

int cSKILL::SetEnchant_Weapon(int Time, int Point)
{

	//Contiue �ʱ�ȭ
	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (ContinueSkill[i].Flag) {
			if (ContinueSkill[i].CODE == SKILL_ENCHANT_WEAPON) {
				memset(&ContinueSkill[i], 0, sizeof(sSKILL));
				//return FALSE; 
			}
		}
	}



	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (!ContinueSkill[i].Flag) {
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
int cSKILL::ForeceOfNature(int Time, int Point, int Party)
{

	//Contiue �ʱ�ȭ
	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (ContinueSkill[i].Flag) {
			if (ContinueSkill[i].CODE == SKILL_FORCE_OF_NATURE) {
				if (ContinueSkill[i].Flag == 2 && !Party) {
					memset(&ContinueSkill[i], 0, sizeof(sSKILL));
					break;
				}
				else return FALSE; //�ߺ����� �Ұ�
			}
		}
	}

	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (!ContinueSkill[i].Flag) {
			ContinueSkill[i].Flag = Party + 1;
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
int cSKILL::HellOfValhalla(int Time, int Point, int TVPoint, int LV, int Party)
{

	//Contiue �ʱ�ȭ
	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (ContinueSkill[i].Flag) {
			if (ContinueSkill[i].CODE == SKILL_HALL_OF_VALHALLA) {
				if (ContinueSkill[i].Flag == 2 && !Party) {
					memset(&ContinueSkill[i], 0, sizeof(sSKILL));
					break;
				}
				else return FALSE; //�ߺ����� �Ұ�
			}
		}
	}

	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (!ContinueSkill[i].Flag) {
			ContinueSkill[i].Flag = Party + 1; //��Ƽ���� 2���Ѵ�
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
int cSKILL::Regeneration_Field(int Time, int Point, int Party)
{

	//Contiue �ʱ�ȭ
	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (ContinueSkill[i].Flag) {
			if (ContinueSkill[i].CODE == SKILL_REGENERATION_FIELD) {
				if (ContinueSkill[i].UseTime > Time)return FALSE; //���� ĳ������ ����
				ContinueSkill[i].UseTime = Time;
				return TRUE; //�ð�����
			}
		}
	}

	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (!ContinueSkill[i].Flag) {
			ContinueSkill[i].Flag = 1 + Party; //��Ƽ���� 2���Ѵ�
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

int cSKILL::SearchSkillDoc(sSKILL* pSkill)
{

	for (int i = 0; i < SIN_MAX_SKILL; i++) {
		if (pSkill->CODE == sSkill_Info[i].CODE) {
			if (pSkill->CODE == SKILL_FORCE_ORB) {
#ifdef _LANGUAGE_CHINESE
				wsprintf(pSkill->Skill_Info.SkillName, "%s%s", SheltomName2[pSkill->Point - 1], sSkill_Info[i].SkillName);
#else
				if (pSkill->ElementIndex == 1000)
				{
					wsprintf(pSkill->Skill_Info.SkillName, "%s %s", BillingMagicForceName, sSkill_Info[i].SkillName);
				}
				else if (pSkill->ElementIndex == 2000)
				{
					wsprintf(pSkill->Skill_Info.SkillName, "%s %s %s", MagicForceName, SheltomName2[pSkill->Point - 1], sSkill_Info[i].SkillName);
				}
				else
					wsprintf(pSkill->Skill_Info.SkillName, "%s %s", SheltomName2[pSkill->Point - 1], sSkill_Info[i].SkillName);
#endif

			}
			else {
				lstrcpy(pSkill->Skill_Info.SkillName, sSkill_Info[i].SkillName);
			}
			lstrcpy(pSkill->Skill_Info.SkillDoc, sSkill_Info[i].SkillDoc);
			break;

		}

	}

	return TRUE;
}

int cSKILL::SkillBarDraw(sSKILL* pSkill, int x, int y, int Alpha)
{

	D3DTLVERTEX tlVertex[73];
	int Time = 0;
	Time = (int)(((float)pSkill->CheckTime / ((float)pSkill->UseTime * 70.0f)) * 72.0f);
	float fx, fy = 0;
	int i = 0, j = 0;
	int sinY, cosY;
	tlVertex[0].rhw = 1;
	tlVertex[0].color = D3DCOLOR_RGBA(0, Alpha, Alpha, Alpha);
	tlVertex[0].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
	tlVertex[0].sz = 0;
	tlVertex[0].sx = float(x);
	tlVertex[0].sy = float(y);
	tlVertex[0].tu = 0.5;
	tlVertex[0].tv = 0.5f;
	for (i = 1; i < Time + 1; i++)
	{
		tlVertex[i].rhw = 1;
		if (pSkill->CODE == SKILL_FORCE_ORB)
		{
			tlVertex[i].color = D3DCOLOR_RGBA(255, 190, 30, Alpha);
		}
		else
			tlVertex[i].color = D3DCOLOR_RGBA(0, 255, 200, Alpha);
		tlVertex[i].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
		tlVertex[i].sz = 0;
		sinY = GetSin[(1024 / 2) + (i * 56) & ANGCLIP];
		cosY = GetCos[(1024 / 2) + ((i * 56) + ANGLE_180) & ANGCLIP];
		fx = (float)((10 * sinY + 10 * cosY) >> 8);
		fy = (float)((10 * cosY - 10 * sinY) >> 8);
		fx /= 256;
		fy /= 256;
		tlVertex[i].sx = (float)(fx + x);
		tlVertex[i].sy = (float)(fy + y);
		tlVertex[i].tu = 0.5f;
		tlVertex[i].tv = 0.5f;
	}
	GRAPHICDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GRAPHICDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	GRAPHICDEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	GRAPHICDEVICE->SetTexture(0, 0);
	GRAPHICDEVICE->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1);
	if (Time - 1 > 0)
		GRAPHICDEVICE->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, Time - 1, tlVertex, sizeof(D3DTLVERTEX));
	GRAPHICDEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	GRAPHICDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	return TRUE;
}



//���� ��ų üũ
int cSKILL::CheckContinueIcon()
{
	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (ContinueSkill[i].Flag) {
			if (!ContinueSkill[i].MatIcon) {
				for (int j = 0; j < SIN_MAX_SKILL; j++) {
					if (ContinueSkill[i].CODE == sSkill[j].CODE) {
						if (sSkill[j].MatIcon) {
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

	for (int i = 0; i < MAX_CONTINUE_SKILL; i++) {
		if (ContinueSkill[i].Flag) {
			if (ContinueSkill[i].CODE == CODE) {
				memset(&ContinueSkill[i], 0, sizeof(sSKILL));
				cInvenTory.SetItemToChar();
				break;
			}
		}
	}
	return FALSE;
}

//��ų����� �ʱ�ȭ
int cSKILL::SkillShortKeyInit()
{
	for (int j = 1; j < SIN_MAX_USE_SKILL; j++) {
		sinSkill.UseSkill[j].ShortKey = 0;
	}
	return TRUE;
}

int cSKILL::CheckMaturedSkill(int ChangeJob)
{
	int matured_skill_count = 0;

	switch (ChangeJob)
	{
	case 1:
		for (int j = 1; j < 5; j++)
		{
			if (sinSkill.UseSkill[j].UseSkillCount < 10000 && sinSkill.UseSkill[j].Skill_Info.USECODE != SIN_SKILL_USE_NOT &&
				sinSkill.UseSkill[j].UseSkillMastery)
			{
				matured_skill_count++;
			}
		}
		break;
	case 2:
		for (int j = 5; j < 9; j++)
		{
			if (sinSkill.UseSkill[j].UseSkillCount < 10000 && sinSkill.UseSkill[j].Skill_Info.USECODE != SIN_SKILL_USE_NOT &&
				sinSkill.UseSkill[j].UseSkillMastery)
			{
				matured_skill_count++;
			}
		}
		break;
	case 3:
		for (int j = 9; j < 13; j++)
		{
			if (sinSkill.UseSkill[j].UseSkillCount < 10000 && sinSkill.UseSkill[j].Skill_Info.USECODE != SIN_SKILL_USE_NOT &&
				sinSkill.UseSkill[j].UseSkillMastery)
			{
				matured_skill_count++;
			}
		}
		break;
	}

	if (matured_skill_count <= 4 && matured_skill_count > 0)
		return TRUE;
	else
		return FALSE;
}