#pragma once

#include "smPacket.h"
#include "smLib3d\smObj3d.h"
#include "smLib3d/smStage3d.h"
#include "..//Score.h"

#define PLAYBUFF_SIZE		256
#define PLAYBUFF_MASK		255

#define PLAYCOUNT_PER_SECOND		70

#define DIST_TRANSLEVEL_NEAR	0x12000				//((64*3)^2)*2	
#define DIST_TRANSLEVEL_HIGH	0x48000				//((64*6)^2)*2	
#define DIST_TRANSLEVEL_MHIGH	0xC8000				//((64*10)^2)*2	
#define DIST_TRANSLEVEL_MID		0x120000			//((64*12)^2)*2		
#define DIST_TRANSLEVEL_LOW		0x320000			//((64*20)^2)*2	

#define DIST_TRANSLEVEL_DISCONNECT	0x320000			//((64*20)^2)*2	
#define DIST_TRANSLEVEL_CONNECT		0x120000			//((64*12)^2)*2	

#define	PARTY_GETTING_DIST		(18*64*18*64)
#define	PARTY_GETTING_DIST2		(17*64*17*64)

#define PLAYSERVER_SENDCOUNTER		(70*1)

#define	ICE_FOOT_COUNT_MAX		20
#define	ICE_FOOT_LIFE_TIME		5000
#define	ICE_FOOT_ALPHA_STEP		(200.f / float(ICE_FOOT_LIFE_TIME))

struct SIceFootInfo
{
	int     Life;
	int     TypeNum;
	DWORD   dwPlayTime;
	POINT3D FootPos;
	POINT3D FootAngle;
};

#define DPAT_MAX		2048

#include <list>

namespace Delta3D::Graphics
{
	class Mesh;
};

struct ModelGroup
{
	std::list<Delta3D::Graphics::Mesh*> meshes;
};

struct smDPAT 
{
	smDPAT* lpTalkLink;

	smDPAT* smDinaLink;
	smPAT3D* Pat;

	char	szPatName[64];
	int		UseCount;
	DWORD	dwSpeedFindSum;

	smMODELINFO* lpModelInfo;

	struct ModelsGroup
	{
		ModelGroup sHighModel;
		ModelGroup sDefaultModel;
		ModelGroup sLowModel;
	};
	ModelsGroup* sModelsGroup = nullptr;

	DWORD	LastUsedTime;
};


class smPATTERN 
{
public:

	smPATTERN *BipPattern;

	smDPAT	DinaPat[ DPAT_MAX ];

	smPATTERN(void);
	~smPATTERN(void);

	void Init();
	int	Close();

	int GetNew();
	int FindFromName( char *szName );
	int FindFromCode( DWORD dwCode );
	smDPAT *LoadCharactor( char *szFileName ) ;
	smDPAT *LoadBipPattern( char *szFileName ) ;

};

#define	DISP_MODE_PATMAIN	1
#define	DISP_MODE_PATSUB	2
#define	DISP_MODE_PATTALK	4
#define CHAR_FRAME_MASK		0x00FFFFFF
#define CHAR_FRAME_SELSHIFT	24	

namespace Delta3D::Graphics
{
	class Material;
};

struct smCHARTOOL
{
	smOBJ3D* ObjBip;
	smPAT3D* PatTool;
	DWORD	dwItemCode;

	int	SizeMax, SizeMin;

	int		ColorBlink;
	union
	{
		short	sColors[4];

		struct
		{
			int iAgeLevel;
			int iMixID;
		};
	};
	DWORD	DispEffect;
	int		BlinkScale;
	int		EffectKind;
	DWORD	ElementEffect;

	union
	{
		Delta3D::Graphics::Material* blendingMaterial = nullptr;
		int		TexMixCode;
	};
	int TexScroll;
};



//////////// ��ī�ϼ� ��ų //////////////
#define SKILL_PLAY_EXTREME_SHIELD	0x01
#define SKILL_PLAY_MECHANIC_BOMB	0x02
#define	SKILL_PLAY_PHYSICAL_ABSORB	0x03
#define	SKILL_PLAY_POISON_ATTRIBUTE	0x04

#define	SKILL_PLAY_GREAT_SMASH		0x05
#define	SKILL_PLAY_MAXIMIZE			0x06
#define	SKILL_PLAY_AUTOMATION		0x07
#define	SKILL_PLAY_SPARK			0x08

#define	SKILL_PLAY_METAL_ARMOR		0x09
#define	SKILL_PLAY_GRAND_SMASH		0x0A
#define	SKILL_PLAY_SPARK_SHIELD		0x0B

#define	SKILL_PLAY_IMPULSION		0x0C
#define	SKILL_PLAY_COMPULSION		0x0D
#define	SKILL_PLAY_MAGNETIC_SPHERE	0x0E
#define	SKILL_PLAY_METAL_GOLEM		0x0F


//////////// ����ũ�� ��ų //////////////
#define SKILL_PLAY_PIKEWIND			0x12	// ����� - ���� ���� ���� 1����ų�� �ν� ���Ͽ��� �Ҵ�� �ڵ� ����(0x10 -> 0x12 �� ������)
#define SKILL_PLAY_CRITICAL_HIT		0x13
#define SKILL_PLAY_JUMPING_CRASH	0x14

#define SKILL_PLAY_GROUND_PIKE		0x15
#define SKILL_PLAY_TORNADO			0x16
#define SKILL_PLAY_EXPANSION		0x18

#define SKILL_PLAY_VENOM_SPEAR		0x19

#define SKILL_PLAY_BLADE_OF_BLAZE	0x1A		//(��)
#define SKILL_PLAY_VANISH			0x1A		//SKILL_PLAY_BLADE_OF_BLAZE �� ���� �ڵ�

#define SKILL_PLAY_CHAIN_LANCE		0x1B

#define SKILL_PLAY_ASSASSIN_EYE		0x1C
#define SKILL_PLAY_CHARGING_STRIKE	0x1D
#define SKILL_PLAY_VAGUE			0x1E
#define SKILL_PLAY_SHADOW_MASTER	0x1F


//////////// ������ ��ų //////////////
#define SKILL_PLAY_RAVING			0x23
#define SKILL_PLAY_IMPACT			0x24

#define SKILL_PLAY_TRIPLE_IMPACT	0x25
#define SKILL_PLAY_BRUTAL_SWING		0x26
#define SKILL_PLAY_ROAR				0x27
#define SKILL_PLAY_RAGEOF_ZECRAM	0x28

#define SKILL_PLAY_CONCENTRATION	0x29
#define SKILL_PLAY_AVANGING_CRASH	0x2A
#define SKILL_PLAY_SWIFT_AXE		0x2B
#define SKILL_PLAY_BONE_SMASH		0x2C

#define SKILL_PLAY_DESTROYER		0x2D
#define SKILL_PLAY_BERSERKER		0x2E
#define SKILL_PLAY_CYCLONE_STRIKE	0x2F

//////////// ���� ��ų //////////////

#define SKILL_PLAY_SCOUT_HAWK		0x41
#define SKILL_PLAY_WIND_ARROW		0x43
#define SKILL_PLAY_PERFECT_AIM		0x44

#define SKILL_PLAY_FALCON			0x46
#define SKILL_PLAY_ARROWOF_RAGE		0x47
#define SKILL_PLAY_AVALANCHE		0x48

#define SKILL_PLAY_ELEMENTAL_SHOT	0x49
#define SKILL_PLAY_GOLDEN_FALCON	0x4A
#define SKILL_PLAY_BOMB_SHOT		0x4B
#define SKILL_PLAY_PERFORATION		0x4C

#define SKILL_PLAY_RECALL_WOLVERIN	0x4D
#define SKILL_PLAY_PHOENIX_SHOT		0x4E
#define SKILL_PLAY_FORCE_OF_NATURE	0x4F


////////////// ����Ʈ ��ų //////////////
#define SKILL_PLAY_SWORD_BLAST		0x51
#define SKILL_PLAY_HOLY_BODY		0x52
#define SKILL_PLAY_DOUBLE_CRASH		0x54

#define SKILL_PLAY_HOLY_VALOR		0x55
#define SKILL_PLAY_BRANDISH			0x56
#define SKILL_PLAY_PIERCING			0x57
#define SKILL_PLAY_DRASTIC_SPIRIT	0x58

#define SKILL_PLAY_FLAME_BRANDISH		0x59
#define SKILL_PLAY_DIVINE_INHALATION	0x5A
#define SKILL_PLAY_HOLY_INCANTATION		0x5B
#define SKILL_PLAY_GRAND_CROSS			0x5C

#define SKILL_PLAY_DIVINE_PIERCING		0x5D
#define SKILL_PLAY_GODLY_SHIELD			0x5E
#define SKILL_PLAY_GODS_BLESS			0x5F
#define SKILL_PLAY_SWORD_OF_JUSTICE		0x50


////////////// ��Ż��Ÿ ��ų ///////////////
#define SKILL_PLAY_SHIELD_STRIKE	0x61
#define SKILL_PLAY_FARINA			0x62
#define SKILL_PLAY_VIGOR_SPEAR		0x64

#define SKILL_PLAY_WINDY			0x65
#define SKILL_PLAY_TWIST_JAVELIN	0x66
#define SKILL_PLAY_SOUL_SUCKER		0x67
#define SKILL_PLAY_FIRE_JAVELIN		0x68

#define SKILL_PLAY_SPLIT_JAVELIN		0x69
#define SKILL_PLAY_TRIUMPH_OF_VALHALLA	0x6A
#define SKILL_PLAY_LIGHTNING_JAVELIN	0x6B
#define SKILL_PLAY_STORM_JAVELIN		0x6C

#define SKILL_PLAY_HALL_OF_VALHALLA		0x6D
#define SKILL_PLAY_X_RAGE				0x6E
#define SKILL_PLAY_FROST_JAVELIN		0x6F
#define SKILL_PLAY_VENGEANCE			0x60


////////////// ������Ƽ�� ��ų ///////////////
#define SKILL_PLAY_HEALING			0x71
#define SKILL_PLAY_HOLY_BOLT		0x72
#define SKILL_PLAY_MULTI_SPARK		0x73
#define SKILL_PLAY_HOLY_MIND		0x74

//#define	SKILL_PLAY_MEDITATION		0x75
#define	SKILL_PLAY_DIVINE_LIGHTNING	0x76
#define	SKILL_PLAY_HOLY_REFLECTION	0x77
#define	SKILL_PLAY_GREAT_HEALING	0x78

#define	SKILL_PLAY_VIGOR_BALL		0x79
#define	SKILL_PLAY_RESURRECTION		0x7A
#define	SKILL_PLAY_EXTINCTION		0x7B
#define	SKILL_PLAY_VIRTUAL_LIFE		0x7C

#define	SKILL_PLAY_GLACIAL_SPIKE	0x7D
#define	SKILL_PLAY_REGENERATION_FIELD	0x7E
#define	SKILL_PLAY_CHAIN_LIGHTNING	0x7F
#define	SKILL_PLAY_SUMMON_MUSPELL	0x70


////////////// ������ ��ų ///////////////
#define SKILL_PLAY_AGONY			0x81
#define SKILL_PLAY_FIRE_BOLT		0x82
#define SKILL_PLAY_ZENITH			0x83
#define SKILL_PLAY_FIRE_BALL		0x84

//#define SKILL_PLAY_MENTAL_MASTERY	0x85
#define SKILL_PLAY_COLUMN_OF_WATER	0x86
#define SKILL_PLAY_ENCHANT_WEAPON	0x87
#define SKILL_PLAY_DEAD_RAY			0x88

#define SKILL_PLAY_ENERGY_SHIELD	0x89
#define SKILL_PLAY_DIASTROPHISM		0x8A
#define SKILL_PLAY_SPIRIT_ELEMENTAL	0x8B
#define SKILL_PLAY_DANCING_SWORD	0x8C

#define SKILL_PLAY_FIRE_ELEMENTAL	0x8D
#define SKILL_PLAY_FLAME_WAVE		0x8E
#define SKILL_PLAY_DISTORTION		0x8F
#define SKILL_PLAY_METEO			0x80

///////////// ��� Ȯ�� //////////////////
#define SKILL_PLAY_DIVINE_PIERCING2		0x90
#define SKILL_PLAY_DIVINE_PIERCING3		0x91

#define SKILL_TOPLVL					0x92
#define SKILL_PLAY_EVASION_MASTERY		0x93
////////////////////////////////////////////

#define SKILL_PLAY_BLESS_ABSORB			0xA0
#define SKILL_PLAY_BLESS_DAMAGE			0xA1
#define SKILL_PLAY_BLESS_EVADE			0xA2
#define SKILL_PLAY_BLESS_SIEGE_ITEM		0xA8

#define SKILL_PLAY_FIRE_CRYSTAL			0xB0
#define SKILL_PLAY_LIGHTNING_CRYSTAL	0xB1
#define SKILL_PLAY_ICE_CRYSTAL			0xB2
#define SKILL_PLAY_CHAOSCARA_VAMP		0xB8

#define SKILL_PLAY_PET_ATTACK		0xC0
#define SKILL_PLAY_PET_ATTACK2		0xC1

#define SKILL_PLAY_SOD_ITEM			0xD0
//#define SKILL_PLAY_METEO			0xE0
#define SKILL_PLAY_SPEACIAL			0xF0
#define	SKILL_PLAY_LOVELY_LIFE		0xF1

#define	SKILL_EFFECT_FIREFLOWER		0x12000010


//��ų ���� ����ũ
#define	SKILL_APPMASK_EXTREME_SHIELD		0x0001
#define	SKILL_APPMASK_PHYSICAL_ABSORB		0x0002
#define	SKILL_APPMASK_AUTOMATION			0x0004
#define	SKILL_APPMASK_ANGER					0x0008
#define	SKILL_APPMASK_SPARK_SHIELD			0x0010
#define	SKILL_APPMASK_GODLY_SHIELD			0x0020


#define	SKILL_APPMASK_HOLY_BODY				0x00010000


//��ų ���� ����ũ ( ���� �Ӽ� )
//#define	SKILL_APPMASK_ICE					0x0010


//�������� �� ������ ����Ŵ
struct	ATTACK_DAMAGE_LIST	{
	DWORD	dwUserCode;
	int		DamageCount;
	int		Count;
};

#define	ATTACK_DAMAGE_LIST_MAX			100


class smCHAR {

	DWORD	Head;

public:

	Score score;
	
	int		DisplayFlag;		//ȭ�� ��� ����
	//int		DisplayHead;		//�Ӹ� ���� ����
	int		DisplayTools;		//���� ��� ����

	smSTAGE3D	*lpStage;		//�ش� ��� ����Ʈ
	DWORD		dwObjectSerial;	//��ü ���� ��ȣ
	int			AutoPlayer;		//�ڵ� �÷��̾� ( TRUE �� ��� ������ ���� �������� �޴´� )

	//Equipe na arena
	int nEquipeArena = 0;

	//N�vel do vip
	int vipLevel = 0;

	smPAT3D	*Pattern;			//���� ����
	smPAT3D	*Pattern2;			//�Ӹ� ����
	smPAT3D *AnimPattern;

	//######################################################################################
	//�� �� �� : �� �� ��
	smPAT3D *TalkPattern;		// ǥ�� ����. ( ���̳��� ������ ini �� ���� lpDinaPattern �Ǵ� lpDinaPattern2 )
	//######################################################################################

	smDPAT  *lpDinaPattern;		//���̳��� ���� ������ (������ ������)
	smDPAT  *lpDinaPattern2;	//���̳��� ���� ������ �Ӹ�(������ ������)

	smDPAT  *lpDinaLeftPattern;		//���� ����
	smDPAT  *lpDinaRightPattern;	//������ ����

	smCHARTOOL	HvLeftHand;		//�޼տ� ���� ����
	smCHARTOOL	HvRightHand;	//�����տ� ���� ����

	smMATRIX	HvLeftHand_Matrix;	//�޼� ���� ��� ����
	smMATRIX	HvRightHand_Matrix; //������ ���� ��� ����

	int		Rend_HvLeftHand;		//���� ������ ����
	int		Rend_HvRightHand;		//���� ������ ����


	smOBJ3D	*BackObjBip[3];		//���� ���� ����
	smOBJ3D	*AttackObjBip;		//���� �е� ������Ʈ
	smOBJ3D	*ShieldObjBip;		//���� �е� ������Ʈ

	int		AttackToolRange;	//���� �����Ÿ�
	int		AttackAnger;		//���ݽ� �е�ġ ( �׳� ���� ���� �ϱ� ���� )
	int		AttackIce;			//���� ���� ����

	BOOL	bActive = TRUE;
	BOOL	bPartyLeader = FALSE;
	union
	{
		struct
		{
			int pX;
			int pY;
			int pZ;
		};

		Point3D sPosition;
	};
	
	int		Flag;
	int		AttackX,AttackY,AttackZ;		// ��ǥ
	int		PHeight;		// �ٴ� ���� ��ǥ
	int		FallHeight;		// ������ ���� 
	int		OnStageField;	// ��� ���ִ� �ٴ� �ʵ� ��ȣ
	int		OnStageFieldState;	//�ٴ� �ʵ��� �Ӽ���

	int		PatLoading;		//���� �ε� ������...

	int		PatWidth;		//ĳ���� ����
	int		PatHeight;		//ĳ���� ����

	int		PatSizeLevel;	//ĳ���� ũ�� �ܰ� ( 0 ~ 3 )

	int		OverLapPosi;	//�ٸ� ĳ���Ϳ� ��ġ�� ��ħ
	int		OverLapPosi2;	//�ٸ� ĳ���Ϳ� ��ġ�� ��ħ
	smCHAR	*lpCharOverLap;	//��ģ ĳ������ ����Ʈ

	POINT3D Posi;

	union
	{
		struct
		{
			POINT3D Angle;
		};

		Point3D sAngle;
	};

	int		MoveMode;	//�̵� ��� ( 0 - �ȱ� 1-�޸��� )
	int		MoveFlag;
	int		MoveCnt;	// ��Ž� ���� ����Ÿ�� ������� �ڵ� �̵��Ҷ� �Ÿ� ���� ī����
	int		tx,tz;		// ��ǥ �̵� ��ǥ
	int		TargetMoveCount;	//��ǥ �̵� ��ǥ ī����
	int		WaterHeight;		//�� ����

	DWORD	dwActionItemCode;	//�� �����ӿ� ���õ� �ڵ�
	DWORD	dwItemSetting;		//������ ���� ���( 0-���� ���� 1-�����ʵ� ���� )
	DWORD	dwActionItemTwoHand;	//��� ���� ýũ

	short	wStickItems[4];		//���� ������ ��ȣ

	//ȭ�� �� ������ ���
	int		ShootingMode;	//�߻��� ���� ��� ( TRUE )
	int		ShootingFlag;	//���� �߻����� ����
	int		ShootingKind;	//�߻� ����
	POINT3D	ShootingPosi;	//�߻� ��ġ

	POINT3D	ShootingAngle;	//�߻� ����
	int		ShootingCount;	//�߻� ī����

	smCHAR	*chrAttackTarget;	//���� ��ǥ ĳ����
	int		AttackCritcal;		//ũ��Ƽ�� ���� ����
	int		AttackCriticalCount;//ũ��Ƽ�� ���� ī���� ( ���� ���ݽ� )
	int		AttackExp;			//���ݽ� ����ġ
	int		AttackSkil;			//��ų ���� �ڵ�
	int		AttackEffect;		//���ݽ� Ư�� ����Ʈ ǥ��
	int		LastSkillParam;		//�ֱ� ��ų���� ���� �ڵ� ( ī����ī�� ���� ���������� �߰� ) 

	int		RecvExp;			//����ġ �ο� ����

	POINT3D	ptNextTarget;	//���� �̵� ��ǥ
	POINT3D	PosiAround;		// �ֺ� ��ġ �̰��� �ָ� ����� ���ϰ� �� (��ó������..)
	int		DistAroundDbl;	// �ֺ� ��� �Ÿ� �Ѱ�ġ
	int		TragetTraceMode;	//���� ��� �� (������� )

	POINT3D	PosBeginMove;		//�̵� ���۽��� ��ǥ
	DWORD	PosBeginCount;

	DWORD	dwNextMotionCode;	//���� ���� ����

	int		ChargingFlag;		//��¡ �÷�

	//######################################################################################
	//�� �� �� : �� �� ��
	DWORD	TalkFrame;		// ǥ�� ������
	DWORD	TalkSoundSum;

	SMotionStEndInfo	FrameInfo;
	//######################################################################################

	int		action;
	DWORD	frame;
	int		FrameCnt;
	int		FrameStep;		//������ �ٲ� ��
	int		MoveSpeed;		//�̵� ������ ��
	int		AttackSpeed;	//���� �ӵ�

	int		ActionPattern;	// ������ ����

	DWORD	dwEventFrameExt[4];	//�̺�Ʈ ������ Ȯ��

	int		NearPlayCount;	//��ó�� �ٸ� ������ ���� �ϴ��� Ȯ�� ( NPC/���� )
	int		ReopenCount;	//���� �ð��� ���� ������ ��ų ī����
	int		AutoMoveStep;	//�ڵ� �̵��� ���� ī����
	short	sMoveStepCount[2];		//�̵� ���� ���� ������

	int		Counter;
	int		FrameCounter;			//��� ���ۺ��� ������ ���� ���Ǵ� ī����

	int		RendSucess;				//ȭ����� ������ ���� ����
	RECT	RendRect2D;				//�������� 2D ��ǥ ����
	POINT3D	RendPoint;				//�������� 2D ��ǥ ( x,y,z )
	int		FlagShow;				//ȭ��ǥ�� �÷� ( 0 - ȭ�� ��� ���� )

	//ä��
	char	szChatMessage[256];		//ä�� ���ڿ�
	DWORD	dwChatMessageTimer;		//ä�� ���ڸ� ǥ�� ����ð� ���

	//����
	char	szTradeMessage[128];	//���� �޼��� ���ڿ�
	DWORD	dwTradeMsgCode;			//���� �޼��� �ڵ�


	char	srTransBuff[TRANS_BUFF_SIZE];	//������ ����Ÿ ���� ����
	int		srTransBuffSize;				//������ ����Ÿ ���� ���� ũ��

	//��� ����
	int		ServerCode;				//�ش� ĳ���� ���� �ڵ�

	smWINSOCK *TransSock;

	int		TransSendWait;			//��� ��Ʈ ��ٸ� 
	int		TransLastSendCnt;		//��� ������ ���� �ð�
	int		TransLastSendTime;		//��� ������ ������ �ð��� ( �ӵ� ýũ�� )
	int		TransMinCnt;			//�ּ� ���� ī����
	int		TransLevel;				//����� �߿� �ܰ�
	int		TransDelayMax;			//��� ���� �ִ�ġ ( �̽ð��� ������ ��õ� )

	smPLAYBUFF	PlayBuff[PLAYBUFF_SIZE];	//�÷��� ���� ��Ȳ�� ���ۿ� �����Ͽ� ��Ž� ���۸���
	int		PlayBuffCnt;					//PlayBuff �� ī����
	int		PlayBuffPosi_End;				//PlayBuff ���۸� �� ��ġ

	DWORD	dwLastTransTime;				//������ ���� �ð�
	int		LastPlayDataType;				//������ ������ ����Ÿ Ÿ��

	smCHAR_INFO		smCharInfo;				//���� ����
	smCHAR_MONSTER_INFO	smMonsterInfo;		//���� ���� ����

	int		AnimDispMode;			//���� ǥ�� ��� ( 0-��� ǥ�� 1-�Ѱ��� ǥ��)
	int		PatDispMode;			//���� ǥ�� ��� ( 0-��ǥ�� 1-���� 2-���길 3-��� )

	int		MotionSelectFrame;		//������ �������� ����� ��ȣ ( 0 , 1 ) 

	smMODELINFO		*smMotionInfo;	//���� ���ۺ� �����Ӱ� ����
	smMODELINFO		*smMotionInfo2;	//���� 2���� ��� 1���𵨿��� ����Ÿ�� ���°�� 2������ ����Ÿ�� ��� 
	smMOTIONINFO	*MotionInfo;

	//######################################################################################
	//�� �� �� : �� �� ��
	smMODELINFO		*lpTalkModelParent;
	smMOTIONINFO	*lpTalkMotionInfo;
	//######################################################################################


	DWORD			OldMotionState;			//������ ��� �Ӽ� ����
	DWORD			dwTarget;				//������ ���ΰ��� �ܳ��� �׼��ϰ�� 

	//��ȯ�� ĳ���� ( ������ ������ ���� )
	rsPLAYINFO		*lpMasterPlayInfo;		//���� ĳ���� (������)

	int						nCheckChar;		//���� �ҷ��� ���� ĳ���� ���� (������) // �庰 - �ҿｺ��

	//���� ĳ���� ~~ 
	rsPLAYINFO		*lpTargetPlayInfo;		//��ǥ ĳ���� (������)
	smCHAR			*lpTargetChar;			//��ǥ ĳ���� (Ŭ���̾�Ʈ��)
	int				AttackUserFlag;			//���Ͱ� ������ ������
	DWORD			dwTargetLockTime;		//��ǥ ���� ����

	DWORD			dwLinkObjectCode;		//����� ������Ʈ �ڵ�
	rsPLAYINFO		*lpLinkPlayInfo;		//����� �÷��̾�
	smCHAR			*lpLinkChar;			//����� ĳ����

	//���ݴ��� ĳ���� ���� ( ���� ����ġ ����� ���� - ������ )
	rsPLAYINFO		*lpExpAttackPlayInfo;
	int				ExpAttackLife;
	DWORD			dwExpAttackTime;
	TRANS_ATTACKDATA AttackTrans;			//���� ����Ÿ ����
	DWORD			dwAttackPlayTime;		//���� ���� �ð�

	int				PotionLog;				//���� ��� ���
	int				LevelLog;				//���� ��ȭ ���
	int				CriticalLog;			//ũ��Ƽ�� �α�

	int				EnableStateBar;			//ü�¹� �׸��� �ɼ�
	int				MotionRecordCount;		//��� ���� ��� ī����
	int				OpenStartPostion;		//ĳ������ ���� ��ű�� ��ȣ (������)

	int				DisplayAlpha;			//������ ( �ӽ� ������ ��� )
	int				RendAlpha;				//������ ( ���� ������ ĳ���� )
	int				RenderLatter;			//������ ���߿�

	DWORD			dwDispAppSkill;			//��ų ����ǥ��
	DWORD			dwDispAppSkillMask;		//��ų ����ǥ�� ����ũ ( ���⸦ ���߱� ���� )
	int				HideWeapon;				//���� ����
	int				MotionLoop;				//�ݺ� ��� Ƚ��
	int				MotionLoopSpeed;		//�ݺ� ��ǿ� ������ �ӵ�
	int				MotionEvent;			//��� �̺�Ʈ �÷�
	int				WeaponEffect;			//����� �Ӽ� ����Ʈ
	DWORD			dwWeaponEffectTime;		//����� �Ӽ� ����Ʈ ī����
	int				EnchantEffect_Point;	//��ų EnchantWeapon �� ��ų ����Ʈ

	rsPLAYINFO		*lpCompulsionPlayInfo;	//�ü����� ĳ����
	DWORD			dwCompulsionTime;		//�ü����� �ð�

	DWORD			dwAssassinEyeTime;		//��ž��� ���� ����
	int 			AssassinEyeParam;		//��ž��� ���� ����


	////////////////////// Ŭ�� //////////////////////////
	int				ClanInfoNum;			//Ŭ�� ���� ��ȣ
	DWORD			dwClanInfoTime;			//Ŭ�� ���� ���� �ð�
	DWORD			dwClanManageBit;		//Ŭ�� ���� ǥ��
	int				Clan_CastleMasterFlag;	//���� Ŭ���� �̴�!

	//Ȯ���
	void			*lpExt1;				//(����) �ʵ� ����ü ���� ������ 
	void			*lpExt2;
	void			*lpExt3;
	void			*lpExt4;

	POINT3D			HoSkillPos;				//��ų ���� ��ǥ
	int				HoSkillCode;			//���� ��ų �ڵ�
	int				HoSkillMode;			//��ų ��ȯ�� �ൿ���

	int				PartyFlag;				//��Ƽ �÷�
	int				PartyParam;				//��Ƽ �Ķ����

	int				PlaySlowCount;		//�������� ���� ����
	int				PlaySlowSpeed;		//�������� �ӵ�
	int				PlayStunCount;		//�߸� ���� ī����
	int				PlayStopCount;		//�������� ���� ī����
	short			PlayHolyMind[2];	//������ ��ȭ ��� ( [0] ���ҵ� ������% [1] �����ð� )
	short			PlayHolyPower[2];	//������ ��ȭ ��� ( [0] ��ȭ�� ������% [1] �����ð� )
	short			PlayPoison[2];		//���� ���� ( [0] ���ҵ� ������ [1] �ص��ð� )
	short			PlayHolyIncantation[2];	//���� ��Ȥ ��ų ( [0] �ӽ� [1] �����ð� )
	int				PlayVanish;			//��Ͻ� ��ų����
	int				PlayCurseQuest;		//���� ����Ʈ ���
	int				PlayVague;			//���� ��ų����
	int				PlayDistortion;		//����� (���� �ְ�)
	int				PlayInvincible;		//���� ������
	int				PlayCursePvP;		// reipvp xxstr
	int			    PlayCurseTopLVL;	// toplvl xxstr
	int				PlayEvasionMastery;
	int PlayerGm;
	int				PlayerPvPMode;
	BOOL			CheckFlagIce;
	int iTeam;


	int				DispPoison;

	DWORD			dwForceOfNatureTime;
	DWORD			dwHallOfValhallaTime;


	int				AttackSkillRange;

	int				EventAttackCount;
	DWORD			dwEventAttackParam;

	short			sAddColorEffect[4];
	int				DispLifeBar;

	DWORD			dwUpdateCharInfoTime;
	DWORD			dwLastRecvAttackTime;

	int				TryAttackCount;

	DWORD			dwForceOrbCode;
	DWORD			dwForceOrbTime;

	DWORD			dwLifeBoosterCode;
	DWORD			dwLifeBoosterTime;
	DWORD			dwManaBoosterCode;
	DWORD			dwManaBoosterTime;
	DWORD			dwStaminaBoosterCode;
	DWORD			dwStaminaBoosterTime;

	DWORD			dwSiegeItem_ScrollCode_Eternal;
	DWORD			dwSiegeItem_ScrollTime_Eternal;			
	DWORD			dwSiegeItem_ScrollCode_Fatal;
	DWORD			dwSiegeItem_ScrollTime_Fatal;		
	DWORD			dwSiegeItem_ScrollCode_Avert;
	DWORD			dwSiegeItem_ScrollTime_Avert;	

	DWORD			dwSkillDelayCode;
	DWORD			dwSkillDelayTime;

	int				PkMode_CharState; //(smCHAR_STATE_NPC / ENEMY / USER)
	int				DontMoveFlag;
	DWORD			dwClanCode;

	int				UseObject_VirtualLife;
	short			sObject_VirtualLife[2];
	short			sObject_DisplayLife[2];

	short			sBlessCastle_Damage[2];		//0-Damage 1-Killing Count


	ATTACK_DAMAGE_LIST	*lpAttackDamageList;
	ATTACK_DAMAGE_LIST* lpAttackDamageList_BlessCastle;

	float DissolveAmount = 0.f;
	int iMountID = 0;
	class CMountHandler* pMount = nullptr;

	smCHAR();
	~smCHAR();
	void Init();
	int Close();

	int SetPosi( int x, int y, int z , int angX, int angY, int angZ );

	int SetTargetPosi( int x, int z );
	int SetTargetPosi2( int x, int z );

	int GetAttackPoint( int *nX, int *nY, int *nZ );
	int GetToolBipPoint( smCHARTOOL *ChrTool, int *nX, int *nY, int *nZ );
	int SetNextTarget( int x, int y, int z );

	int MoveAngle( int step );
	int MoveAngle2( int step );

	int ChangeMoveMode();

	int StartHandEffect(int Mode);

	int SetAction( int nAction );
	int ChangeMotion( int Motion , int DpMode=0 );

	int AutoChangeTalkMotion( int TalkModeType );

	int FindActionFromFrame( int sframe );

	int SetDinaPattern( smDPAT	*lpDPat );
	int SetDinaPattern2( smDPAT	*lpDPat );

	int SetTool( DWORD dwItemCode , int hvPosi  );

	int SetPattern( smPAT3D *pat );
	int SetPattern2( smPAT3D *pat );

	int SavePlayBuff();

	int SavePlayBuff2();

	int Main();
	int Draw(bool DrawCharacterTarget = false);
	int DrawLogin();
	int VirtualDraw();

	int ShootingMain();
	
	int	ChargingSkill();
	int EventAttack( int Flag=0 );

	int CheckShootingTest(smCHAR *lpChrTarget);

	int CheckShootingTest_LastAttackTime( smCHAR *lpChar );

	int	SetSmoking( int level );

	SIceFootInfo	m_IceFootInfo[ ICE_FOOT_COUNT_MAX ];

	void SetIceFoot( int TypeNum, DWORD dwPlayTime, int x, int z );
	int  DrawIceFoot(void);	

	int DrawShadow();
	int DrawStateBar(int x, int y);
	int DrawStateBarRenderName(int x, int y);

	int DrawStateBar2( int x, int y );
	int DrawChargingBar( int x, int y , int Charging , int ChargingMax );

	int DrawMotionBlurTool( smCHARTOOL *ChrTool );
	int DrawMotionBlur();

	int SetLoadPattern( char *szName );

	int MakePlayBuffFromPosi( int px, int py, int pz , int anX,int anY, int anZ , int act );
	int MakePlayBuffFromRecvData( smPLAYBUFF *StartBuff , smPLAYBUFF *EndBuff , int len );

	int MakeTransPlayData( char *lpTargetBuff , int SendTime , int pBuffStep=1 );

	int SetTransEffectItems(smEFFECT_ITEM *lpEffectItem);
	int SetTransEffectWeapon(smEFFECT_ITEM *lpEffectItem);

	int TransDelayCheck();
	int SetDistSendCnt( smCHAR *player );

	int SetMotionFromCode( DWORD MotionCode );

	int FindMotionCountFromCode( DWORD MotionCode );

	int FormSetPlayerInfo();

	int SetTransPlayerInfo( smTRNAS_PLAYERINFO *lpTransPlayerInfo );

	int SetTransPlayerInfoQuick( smTRNAS_PLAYERINFO_QUICK *lpTransPlayerInfo );

	DWORD GetAttackTrans_XorCode();
	int ResetAttackTrans();
	int XorAttackTrans();

	int PlayAttack( int EventFlag=0 );

	int RecvPlayData2( char *lpData );
	int RecvPlayData( smTHREADSOCK *RecvData );
	int SendPlayData( smCHAR *player );


	int SendCharInfo( smWINSOCK *lpsmsock );

	int SendPlayDataSock( smWINSOCK *lpsmsock , char *lpTransBuff , int ex, int ey, int ez );

	int SendTransAttack( smCHAR *lpChar , smWINSOCK *lpsmsock , int AttackCode , int Add_Damage=0 , int Resistance=0 );

	int PlayAttackFromPosi( int ex, int ey, int ez, int Dist ,int attack=TRUE );

	int BeginSkill( int SkilCode , int Level , smCHAR *lpTarChar , int x, int y, int z );
	int EventSkill();
	int BeginSkill_Monster();
	int EventSkill_Monster();
	int BeginAttack_Monster();
	int EndSkill();

};

/*
#define CHRMOTION_STAND		0
#define CHRMOTION_WALK		1
#define CHRMOTION_RUN		2
#define CHRMOTION_JUMP		3
#define CHRMOTION_ATTACK	4
*/

#define CHRMOTION_EXT		10

#define hvPOSI_RHAND	0x0001
#define hvPOSI_LHAND	0x0002


#define CHRMOTION_STATE_STAND		0x40
#define CHRMOTION_STATE_WALK		0x50
#define CHRMOTION_STATE_RUN			0x60
#define CHRMOTION_STATE_FALLDOWN	0x80

#define CHRMOTION_STATE_ATTACK		0x100
#define CHRMOTION_STATE_DAMAGE		0x110
#define CHRMOTION_STATE_DEAD		0x120
#define CHRMOTION_STATE_SOMETIME	0x130
#define CHRMOTION_STATE_EAT			0x140
#define CHRMOTION_STATE_SKILL		0x150

#define CHRMOTION_STATE_FALLSTAND	0x170
#define CHRMOTION_STATE_FALLDAMAGE	0x180

#define CHRMOTION_STATE_RESTART		0x200
#define CHRMOTION_STATE_WARP		0x210

#define CHRMOTION_STATE_YAHOO		0x220

#define CHRMOTION_STATE_HAMMER		0x300

#define CHRMOTION_STATE_TALK_AR			0x400
#define CHRMOTION_STATE_TALK_E			0x410
#define CHRMOTION_STATE_TALK_OH			0x420
#define CHRMOTION_STATE_TALK_EYE		0x430
#define CHRMOTION_STATE_TALK_BLANK		0
#define CHRMOTION_STATE_TALK_SMILE		0x440
#define CHRMOTION_STATE_TALK_GRUMBLE	0x450
#define CHRMOTION_STATE_TALK_SORROW		0x460
#define CHRMOTION_STATE_TALK_STARTLED	0x470
#define CHRMOTION_STATE_TALK_NATURE		0x480
#define CHRMOTION_STATE_TALK_SPECIAL	0x490

int smCHAR_SetCameraPosi( int x,int y,int z, int angX,int angY,int angZ );

extern CRITICAL_SECTION	cLoadSection;

int smDPAT_Delete( smDPAT *dPat );
int AnimObjectTree( smOBJ3D *tObj , int frame , int ax, int ay, int az );
int AnimObjectTreexD( smOBJ3D *tObj , int frame , int ax, int ay, int az );

int TestSetNewText( char *str ) ;

int InitMotionBlur();

int GetSinItemNumFromCode( DWORD CODE );

int InitPatterns();
int ClosePatterns();
int SetLoadPattern( smCHAR *smChar , char *szName , POINT3D *Posi , POINT3D *Angle );
int SetLoadPattern( smCHAR *smChar , char *szName , char *szName2 , POINT3D *Posi , POINT3D *Angle );

int	AddLoaderPattern( smCHAR *lpChar , char *szName , char *szName2=0 );
int AddLoaderStage( smSTAGE3D *lpStage , char *szName );
int AnimObjectTree( smOBJ3D *tObj , int frame , int ax, int ay, int az );
int AnimObjectTreexD( smOBJ3D *tObj , int frame , int ax, int ay, int az );

class scITEM {

public:
	DWORD	Head;

	int		DisplayFlag;

	int		Flag;
	int		pX,pY,pZ;

	char	szModelName[64];
	char	szName[64];

	DWORD   iClass;

	void	*lpStgArea;

	smPAT3D	*Pattern;
	smDPAT  *lpDinaPattern;

	int		PatLoading;

	int		ItemCode;

	DWORD	dwLastTransTime;

	int		ServerCode;	

	POINT3D	RendPoint;


	POINT3D Posi;
	POINT3D Angle;


	scITEM();
	~scITEM();

	void Init();
	int Close();

	int SetPosi( int x, int y, int z );
	int SetTransItem( TRANS_ITEM *lpTransItem );

	int SetPattern( smPAT3D *pat );
	int SetPosi( int x, int y, int z , int angX, int angY, int angZ );
	int Draw();

};

int	AddLoaderItem( scITEM *lpItem , char *szName );
DWORD GetSpeedSum( char *szName );

extern smPATTERN smBipPattern;
extern smPATTERN smPattern;


int	Ptect_IncAttackCount( int Flag );
DWORD Ptect_GetAttackCount();

extern int	SkillChargingFlag;

extern TRANS_SKIL_ATTACKDATA	Trans_SplashCharList;

extern BOOL isEnemy;

extern int smCHAR_CameraX;
extern int smCHAR_CameraY;
extern int smCHAR_CameraZ;

extern int CastleBattleZone_LineZ;
extern int CastleBattleZone_DoorLineZ;
extern int CastleBattleZone_DoorLineX[2];
extern int CastleBattleZone_BridgeZ;
extern int CastleSoulFountain_Area[4];

int UpdateCastleMasterClan( DWORD dwMasterClan );
int SetClanMaster_Player( DWORD dwMasterClan );