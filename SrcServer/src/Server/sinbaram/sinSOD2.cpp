/*----------------------------------------------------------------------------*
*	���ϸ� :  sinSOD2.cpp
*	�ϴ��� :  ���� Test ������ ���̰� �ֵ�
*	�ۼ��� :  ����������Ʈ 4�� 
*	������ :  �ڻ� 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\clan_Enti.h"
#include "tjboy\\isaocheck\\auth.h"
#include "Character/playmain.h"
#include "Character/playsub.h"
#include "netplay.h"
#include "Character/character.h"
#include "fileread.h"
#include "field.h"
#include "SrcServer\\onserver.h"


cSINSOD2 cSinSod2;
cSINSIEGE cSinSiege;
sinMESSAGEBOX_NEW sinMessageBox_New;

void*	lpbltr_clanN;
void*	lpbltr_clanB;
int Matbltr_Paper291;
int Matbltr_Paper291_Text;

void*	lpbltr_ButtonBox;
void*	lpbltr_Button_Clan;
void*	lpbltr_Button_Clan_G;
void*	lpbltr_Button_Prize;
void*	lpbltr_Button_Prize_G;
void*	lpbltr_Button_OK;
void*	lpbltr_Button_OK_G;

int Matbltr_Logo;
void*    lpbltr_ClanRank_Title;
int Matbltr_ClanRank_KindBar;
void*    Matbltr_ClanRank_ListLine;


RECT SodButtonRect[3] = {
	{111,393,111+68,393+23},
	{189,393,189+68,393+23},
	{267,393,267+68,393+23},

};

int MatSod2Box[10]; //�ڽ� Mat

/*----------------------------------------------------------------------------*
*						 Init
*-----------------------------------------------------------------------------*/	
void cSINSOD2::Init() {}
/*----------------------------------------------------------------------------*
*						 Load
*-----------------------------------------------------------------------------*/	
void cSINSOD2::Load() {}
/*----------------------------------------------------------------------------*
*						Release
*-----------------------------------------------------------------------------*/	
void cSINSOD2::Release()
{

}
/*----------------------------------------------------------------------------*
*						Draw
*-----------------------------------------------------------------------------*/	
void cSINSOD2::Draw() {}
/*----------------------------------------------------------------------------*
*						DrawText
*-----------------------------------------------------------------------------*/	
void cSINSOD2::DrawText() {}
/*----------------------------------------------------------------------------*
*						Main
*-----------------------------------------------------------------------------*/	
DWORD ClanRankFlagTime = 0;
void cSINSOD2::Main() {}
/*----------------------------------------------------------------------------*
*						Close
*-----------------------------------------------------------------------------*/	
void cSINSOD2::Close()
{

}
/*----------------------------------------------------------------------------*
*						LbuttonDown
*-----------------------------------------------------------------------------*/	
void cSINSOD2::LButtonDown(int x, int y) {}
/*----------------------------------------------------------------------------*
*						LbuttonUp
*-----------------------------------------------------------------------------*/	
void cSINSOD2::LButtonUp(int x , int y)
{


}
/*----------------------------------------------------------------------------*
*						RbuttonDown
*-----------------------------------------------------------------------------*/	
void cSINSOD2::RButtonDown(int x , int y)
{

}
/*----------------------------------------------------------------------------*
*						RbuttonUp
*-----------------------------------------------------------------------------*/	
void cSINSOD2::RButtonUp(int x, int y)
{

}
/*----------------------------------------------------------------------------*
*						KeyDown
*-----------------------------------------------------------------------------*/	
void cSINSOD2::KeyDown()
{

}
/*----------------------------------------------------------------------------*
*						Sod2�ڽ��� �ݴ´�
*-----------------------------------------------------------------------------*/	
void cSINSOD2::CloseSod2MessageBox() {}
/*----------------------------------------------------------------------------*
*						Sod2�ڽ��� �����ش�
*-----------------------------------------------------------------------------*/	
void cSINSOD2::ShowSod2MessageBox() {}

//���ο� �޼��� �ڽ��� ����
int ShowSinMessageBox_New(int PosiX, int PosiY, int SizeW, int SizeH, RECT* rect, int ButtonNum) { return TRUE; }

/*----------------------------------------------------------------------------*
*						Web Data Ŭ���̾�Ʈ�� �Ľ�
*-----------------------------------------------------------------------------*/	
void cSINSOD2::RecvWebDaTa() //����� �׽�Ʈ�� ����
{
	

}
void cSINSOD2::RecvClanRank(char *szBuff)
{
	//115001132 -�Ƹ��Ե�- 1329660 2004-05-07
	//string Test ="1 ȣ��������Ŭ�� 10010020 2004/05/05 2 �Źٶ�Ŭ�� 553340 2004/2332/1 3 ���Ŭ�� 12131001 2003/05/23";
	//string Test = "Code=2 CIMG=121000196 CName=BS-ClaN_���� CPoint=591260 CRegistDay=2004/05/04 CIMG=103001219 CName=�����´� CPoint=546943 CRegistDay=2004/05/04 CIMG=104000979 CName=[NEO]���ް� CPoint=479030 CRegistDay=2004/05/05 CIMG=112000075 CName=������ CPoint=454562 CRegistDay=2004/05/04 CIMG=115001132 CName=-�Ƹ��Ե�- CPoint=451679 CRegistDay=2004/05/04 CIMG=102001120 CName=[�������] CPoint=438589 CRegistDay=2004/05/05 CIMG=109000660 CName=GladiaTor CPoint=364726 CRegistDay=2004/05/04 CIMG=118000957 CName=pUrplEviShop CPoint=357253 CRegistDay=2004/05/04 CIMG=111001179 CName=����ȣ������ CPoint=302324 CRegistDay=2004/05/04";
	//sinClanRank = Split_ClanRankDaTa(Test);

}

// Space�� Ű������ ��Ʈ���� �и��Ѵ�
vector<string> cSINSOD2::Split_ClanRankDaTa(const string& s)
{

	vector<string> ret; 
	typedef string::size_type string_size;
	string_size i = 0;
	while(i != s.size()){ 
		while(i != s.size()){
			if(s[i] & 0x80)break; //�ѱ��̸� �ǳʶ���
			if(isspace(s[i])){
				++i;
			}
			else break;
		}
		string_size j =i;
		while(j != s.size()){
			if((j-i) > 200 ){
				i = s.size();
				j = i;
				break;
			}
			if(s[j] & 0x80){ //�ѱ��̸� �ε��� 2ĭ������ �ٽ�üũ (0x80�� ���������ϸ� 128 ) 
				j +=2;       // 0000 0000 �߿� �޺κ��� ��ä��� ������ �Ѿ�ԵǸ� 2Byte�� ����ϴ� �ѱ��̶�����
				continue;
			}
			if(!isspace(s[j])){
				++j;
			}
			else break;
		}
		if(i != j ){
			ret.push_back(s.substr(i,j-i));
			i = j;
		}
	}

	//Code���� �ٽ� �Ľ��Ѵ�
	vector<string> ret2;
	string_size k = 0;
	string_size e = 0;
	string STempNum;
	string CodeTemp;
	int TempNumCnt = 0;

	//��⼭ �ʱ�ȭ
	for(int p = 0; p < 10 ; p++){
		ClanMarkNum[p] = -1;
	}

	i = 0; //�պκп��� CODE�� �ִ�
	while(i < ret.size()){ 
		while(k != ret[i].size()){
			if(ret[i][k] == '='){ 
				CodeTemp.clear();
				CodeTemp = ret[i].substr(0,k);
				if( i ==0 && CodeTemp == "Code"){
					STempNum.clear(); //�̰ž����ְ� atoi�ϴٰ� �������ִ� ��� ��ٷο� string����
					STempNum = ret[i].substr(k+1,ret[i].size()-(k+1));
					if(atoi(STempNum.c_str()) == 2){
						ret2.clear();
						return ret2;
					}
					else break;
				}
				
				ret2.push_back(ret[i].substr(k+1,ret[i].size()-(k+1)));
				if(CodeTemp == "CIMG"){
					STempNum.clear(); //�̰ž����ְ� atoi�ϴٰ� �������ִ� ��� ��ٷο� string����
					STempNum = ret[i].substr(k+1,ret[i].size()-(k+1));
					ClanMarkNum[TempNumCnt] = atoi(STempNum.c_str());
					ClanMarkIndex[TempNumCnt] = ReadClanInfo( ClanMarkNum[TempNumCnt] );
					TempNumCnt++;
				}
				k = 0;
				break;
			}
			k++;
		}
		i++;
	}

	//Ŭ����ũ�� �ε��Ѵ�
	for(int t = 0 ;t < TempNumCnt ; t++){ 
		if(ClanMarkIndex[t] >= 0){
			if(ClanInfo[ClanMarkIndex[t]].hClanMark){ //TempNumCnt�� �Ѱ��� �־�� �ε����̹������ִ°Ŵ�
				ClanMark[t] = ClanInfo[ClanMarkIndex[t]].hClanMark;
			}
		}
	}
	return ret2;		
}
// ���ҵ� ��Ʈ���� ���̸� �������� �����Ѵ�
vector<string> cSINSOD2::Split_ClanMessage(const string& s , const int Len[])
{

	vector<string> ret;  
	typedef string::size_type string_size; 
	string_size i = 0;
	string_size j = 0;
	int LenCnt = 0;
	while(i < s.size()){
		if(s[i] & 0x80)i += 2;  //�ѱ�
		else i++;
		if( (int)i-(int)j >= Len[LenCnt]){
			if(Len[LenCnt+1] == 0){
				ret.push_back(s.substr(j,i-j));
				break;
			}
			ret.push_back(s.substr(j,i-j));
			j = i;
			LenCnt++;
		}
		if(s[i] == '|'){
			ret.push_back(s.substr(j,i-j));
			break;
		}
	}

	/*
	int LenCnt = 0;  
	vector<string> ret; 
	typedef string::size_type string_size; 
	string_size i = 0;
	string_size j = 0;
	string_size k = 0;
	while(i < s.size()){ 
		if(s[i] & 0x80){
			i +=2;
			if(i == s.size()){
				ret.push_back(s.substr(j,i-j));
				break;
			}
			continue;
		}
		else{
			if( (int)i-(int)j >= Len[LenCnt]){
				if(isspace(s[i])){
					if(Len[LenCnt+1] == 0){
						i = s.size(); //¥���� �۾��� ������ش�
						ret.push_back(s.substr(j,i-j));
						break;
					}
					ret.push_back(s.substr(j,i-j));
					++i; 
					j = i;
					LenCnt++;
				}
			}
			++i;
			if(i == s.size()){
				ret.push_back(s.substr(j,i-j));
				break;
			}

		}
	}
	*/
	return ret;		
}

// �� DB���� ���� ����Ÿ�� �����Ѵ�
vector<string> cSINSOD2::Split_Sod2DaTa(const string& s)
{
	string Temp33;
	vector<string> ret; 
	typedef string::size_type string_size;
	string_size i = 0;
	while(i < s.size()){ 
		while(i < s.size()){
			if(s[i] == '|'){
				++i;
			}
			else break;
		}
		string_size j = i;
		while(j < s.size()){
			if((j - i) > 200){
				i = s.size(); //while������ ������
				j = i; 
				break;
			}
			if(s[j] != '|'){
				++j;
			}
			else break;
		}
		if(i != j ){
			Temp33 = s.substr(i,j-i);
			ret.push_back(s.substr(i,j-i));
			i = j;
		}
	}

	//Code���� �ٽ� �Ľ��Ѵ�
	string Temp;
	string Temp2;
	string_size k = 0;
	string_size e = 0; 
	int NumTemp = 0;
	int TempArray[] = {28,22,26,0}; 
	i = 0; 
	while(i < ret.size()){
		while(k < ret[i].size()){
			if(ret[i][k] == '='){ 
				Temp.clear();
				Temp = ret[i].substr(0,k);

				Temp2.clear();
				Temp2 = ret[i].substr(k+1,ret[i].size()-(k+1));

				/*
				if(k+1 == ret[i].size()){
					if(i+1 != ret.size()){
						if(ret[i+1][0] != 'C'){  //�Ƕ��� -_- �ٻڴٺ��� �Ҽ�����
							Temp2.clear();
							Temp2 = ret[i+1].c_str();
						}
					}
				}
				*/
				
				if(Temp == "Code"){
					NumTemp = atoi(Temp2.c_str());
					switch(NumTemp){
						case 0:
						case 5:
						case 6:
							UserType = 1;
						break;
						case 1:
							UserType = 3;
						break;
						case 2:
						case 3:
							UserType = 2;
						break;
						case 4:
							UserType = 4;
						break;
					}
		
				}
				if(Temp == "CName"){
					lstrcpy(szClanName,Temp2.c_str());
				}
				if(Temp == "CNote"){
					//Temp2 ="�ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ��ѱ�";
					Temp2.push_back('|');
					sinClanMessage = Split_ClanMessage(Temp2 , TempArray);
				}
				if(Temp == "CZang"){
					lstrcpy(szClanMaster,Temp2.c_str());

				}
				if(Temp == "CIMG"){
					ClanImageNum = atoi(Temp2.c_str());
					ClanMark_32Index = ReadClanInfo_32X32(ClanImageNum);
					ClanMark_32 = ClanInfo[ClanMark_32Index].hClanMark32;

				}
				if(Temp == "TotalEMoney"){
					TotalEMoney = atoi(Temp2.c_str());

				}
				if(Temp == "CTax"){
					Tax = atoi(Temp2.c_str());

				}
				if(Temp == "TotalMoney"){
					TotalMoney = atoi(Temp2.c_str());

				}
				if(Temp == "CClanMoney"){
					ClanMoney = atoi(Temp2.c_str());
				}
				k = 0;
				break;
			}
			k++;
		}
		i++;
	}

	return ret;		
}


//�� DB���� �޼����� �޴´�
int cSINSOD2::RecvWebData(int Index , const string& s)
{
	vector<string> Temp_V;   
	if(bip_port_error)return FALSE;   
	if(Index){     
		//Init(); 
		if(Index == 1){     
			Temp_V = Split_Sod2DaTa(s);  
			if(Temp_V.size() <= 0)return FALSE;
			BoxIndex = 1;      
			ShowSinMessageBox_New(62,78,381-62,426-78 ,SodButtonRect );
			//UserType = 2; //1 �Ϲ����� , 2 Ŭ���� ,3 Ŭ�������� ,4 ��ã���� �ִ� Ŭ��������
			//if(UserType == 4 || UserType == 3){
			//	SendClanMoneyToServer(0,0);
			//}
		}
		else if(Index == 3){
			//ClanRankFlag = 1;
			sinClanRank = Split_ClanRankDaTa(s);
			if(sinClanRank.size() <= 0)return FALSE;
			BoxIndex = 2;
			//ShowSinMessageBox_New(62,78,381-62,426-78 ,SodButtonRect );
		}
		//���⼭ Clan ���������� Clan ������ �Ϲ� ���������� ������ �޴��� �����ش�
	}
	return TRUE;
}

//Ŭ��Ĩ�� �ݾ��� ã�´�
int sinRecvClanMoney(int RemainMoney , int GetMoney) { return TRUE; }

/*----------------------------------------------------------------------------*
*	
*							( �� �� �� )
*	
*-----------------------------------------------------------------------------*/	
int sinShowSeigeMessageBox()
{
	//SeigeINFOindex(UserAccount, sinChar->szName,szConnServerName,1);
	return TRUE;
}

int RecvSeigeWebData(int Index , char *string)
{
	//char szTemp[65000];
	//lstrcpy(szTemp,string);

	return TRUE;
}





/*----------------------------------------------------------------------------*
*		 �׽�Ʈ				<ha>������ �޴��ڽ� 
*-----------------------------------------------------------------------------*/	

//�ӽð�ü
cHASIEGE chaSiege;

/*---���Ŵ� ���� �÷���----*/
int haSiegeMenuFlag=0;    //������ �޴��÷�
int haSiegeMenuKind=0;    //������ �޴�����
int ScrollButtonFlag=0;   //��ũ�� ���� �ʿ��� �÷�
int GraphLineFlag=0;    
int haSiegeBoardFlag=0;   //���� Ŭ�� ����â �÷�
int haSiegeMerFlag=0;     //�뺴 ���� �÷�


/*---�����ڽ� ���� ��ġ����---*/
POINT ClanSkillBoxSize={0,0};  //Ŭ����ų ���� �ڽ� ������
POINT ClanSkillBoxPosi={0,0};  //Ŭ����ų ���� �ڽ� ������

/*---�������� ����  �ε�����---*/
int CastleKindIndex  = 0;  //���� ���� ���� �ε���
int TowerIconIndex = 0;  //Ÿ�� ����
int haSendTowerIndex = 0;
int MenuButtonIndex  = 0;  //�޴� ��ư ���� �ε���

/*--����Ű� ���õɶ�  ���� �ӽ��Լ���---*/
int HaTestMoney =0;        //�ӽü���  �ݾ�
int HaTaxRate =0;

/*----Ŭ�� ���� ����-----*/
sHACLANDATA sHaClanData[HACLAN_MAX];  //���� Ŭ�� ����

int  haAlpha   = 0;				//������ ���İ�
int  BoardTime = 0; 
int  haClanSkillTime=0;

int  haTotalDamage =  0;		//��Ż �������� ����ٶ� ����Ѵ�.
int  haPlayTime[3] = {0};		//����Ÿ��

/*---�뺴 ���� ����----*/
//�ӽ�
int haMercenrayMoney[3] = {50000,100000,300000};    //�뺴 ����
int	haMercenrayIndex = 0;                           //�뺴 ���� �ε���
int haTowerMoney =500000;

//ũ����Ż ī��Ʈ�� �޴´�.
short haCrystalTowerCount[4];    //ũ����Ż ī��Ʈ   

char *haC_CastleWinFilePath   = "image\\Sinimage\\help\\CastleWin.sin" ;
char *haC_CastleLoseFilePath  = "image\\Sinimage\\help\\CastleLose.sin";

char *haC_CastleWin_FilePath  = "image\\Sinimage\\help\\CastleWining.sin" ;
char *haC_CastleLose_FilePath  = "image\\Sinimage\\help\\CastleLoseing.sin";


/*---���� Ŭ�� �̸���ġ-----*/
char *ScoreBoardName[] = {
	"Battle Point",    //�÷��̾� ��ų ����          
	"Con Rate",        //�ڽſ� Ŭ�� ���� �⿩��
	"B.P",
	"PlayTime",        //Ÿ��
	"Hit  Rate",	   //�ڱ� Ŭ���� ����
	"BLESS CASTLE",    //����
};

//��ư ��ġ
int SiegeButtonPosi[][4]={
	{70    ,70     ,268,302},    //����
	{29+70 ,269+70 ,68 ,23},     //����/��� ����
	{144+70,269+70 ,48 ,23},     //Ȯ��
	{197+70,269+70 ,48 ,23},     //���
	{270   ,236+70 ,48 ,23},     //��ã�� Ȯ��
	{77+70 ,21+70  ,49 ,11},     //Ÿ�� ������ư
	{179+70-3,21+70,49 ,11},   //�뺴 ������ư
};

//������ ������ ��ġ
int SiegeIconPosi[][4]={
	{26+70,83+70 ,16,16},        //��ũ��
	{36+70,94+70 ,30,30},        //Ÿ���Ӽ�
	{36+70,216+70,30,30},        //Ŭ����ų ��ġ
	{8+70 ,45+70 ,51,22},        //��Ÿ��
	{10+70 ,63+70 ,12,13},       //Ÿ�� �׵θ�
	{26+70,59+70,16,16},         //���� ���� ��ũ��
};  
///������ �÷��̾�
int  haMatPlayMenu[8]={0};
int  haMovieFlag = 0;
int  haMovieKind = 0;
char haMovieName[64];

int haPlayerPosi[4][4] = {
	{64+68+8,359,32,32},//�����Ϲ�ư
	{270    ,363,48,23},//
};

cHASIEGE::cHASIEGE()
{
	int i;
	for(i=0;i<6;i++){
		cSinSiege.TowerTypeDraw[i][1]=0;
	}
	for(i=0;i<4;i++){
		cSinSiege.MercenaryNum[i] =  0;
	}
	
}
cHASIEGE::~cHASIEGE()
{

}

void cHASIEGE::init()
{
	
	
	
}

void cHASIEGE::ImageLoad() {}

/*----------------------------------------------------------------------------*
*		              Release
*-----------------------------------------------------------------------------*/
void cHASIEGE::Release() {}
//��Ʈ x��ǥ


/*----------------------------------------------------------------------------*
*		              ����
*-----------------------------------------------------------------------------*/
void cHASIEGE::Main() {}
/*----------------------------------------------------------------------------*
*		              �׸��� �׸���.
*-----------------------------------------------------------------------------*/
int   haStartTga=0;                //���� �׸��� ���Ŵ� �ӽ� ������
int   haTempScore[2]={0};
int	  haStartPosiX=0,haStartPosiY=100;
void cHASIEGE::Draw() {}

/*----------------------------------------------------------------------------*
*		             �������� ȣ��Ŵ� �Լ�
*-----------------------------------------------------------------------------*/
//<ha>������ �޴��� �����ش�.
int cHASIEGE::ShowSiegeMenu(smTRANS_BLESSCASTLE *pData)
{	

	int i;
	//Ŭ��Ĩ ��Ŭ��Ĩ�� �ƴҰ�� ����
#ifdef _WINMODE_DEBUG
#else
	if(rsBlessCastle.dwMasterClan != GetClanCode(lpCurPlayer->smCharInfo.ClassClan))return TRUE;
#endif
	SendClanMoneyToServer(0,0,1);
	cSinSiege.ClanSkill = pData->ClanSkill;					  //Ŭ�� ��ų
	for(i=0;i<3;i++){
		cSinSiege.MercenaryNum[i] = pData->MercenaryNum[i];   //�뺴Ÿ��
	}
	for(i=0;i<6;i++){
		cSinSiege.TowerTypeDraw[i][0] = 0;
		cSinSiege.TowerTypeDraw[0][0] = 1;					  //���� A�� Ȱ��ȭ ��Ų��.
		cSinSiege.TowerTypeDraw[i][1] = pData->Tower[i];      //��Ÿ���� Ÿ���� ���� 
		
	}
 	ImageLoad();											  //�̹����� �ε�
	
	int Temp=0,Temp2=0;
	Temp  = (pData->TaxRate*22)+96;   
	Temp2 = (cSinSiege.TaxRate*22)+96-8;                      //���� ����Ŵ� ����


	//������ ������ �����Ѵ�.
	SiegeIconPosi[0][0] = Temp-2;
	SiegeIconPosi[5][0] = Temp2-2;
	HaTaxRate = pData->TaxRate;

	
	//������ �޴��� ����.
	haSiegeMenuFlag = 1;
	haSiegeMenuKind = HASIEGE_TAXRATES;//���������� ����.
	
	return TRUE;
}

// MOSTRA PONTUA��O SOD
int cHASIEGE::ShowSiegeScore(rsUSER_LIST_TOP10 *pData)
{
	int i;

	for(i=0;i<HACLAN_MAX ;i++){
		 if(pData->dwUserCode[i] && pData->Damage[i]){
			
			sHaClanData[i].CLANCODE = pData->dwUserCode[i];
			sHaClanData[i].Score    = pData->Damage[i];
			haTotalDamage           = pData->dwTotalDamage;									  
			sHaClanData[i].Flag     = 1; 

			sHaClanData[i].ClanInfoNum = ReadClanInfo(sHaClanData[i].CLANCODE);
			if(sHaClanData[i].ClanInfoNum >=0){
				lstrcpy(sHaClanData[i].ClanName , ClanInfo[sHaClanData[i].ClanInfoNum].ClanInfoHeader.ClanName);
				sHaClanData[i].lpClanMark = ClanInfo[sHaClanData[i].ClanInfoNum].hClanMark;
			}
		 }
	}

	for(i=0;i<4;i++){
		haCrystalTowerCount[i] = pData->bCrystalTowerCount[i];
	}
	
	    
	return TRUE;
}
/*----------------------------------------------------------------------------*
*						 <ha>������ ���� �޼����� �����ش�.
*-----------------------------------------------------------------------------*/
int cHASIEGE::ShowExitMessage() { return TRUE; }
/*----------------------------------------------------------------------------*
*			<ha>������ ����  �ʱ�ȭ �Լ�
*-----------------------------------------------------------------------------*/
int cHASIEGE::SetCastleInit()
{
	for(int i=0;i<3;i++){
		haPlayTime[i]=0;
	}
	for ( int i = 0; i<HACLAN_MAX; i++ )
	{
		sHaClanData[i].CLANCODE=0;
		sHaClanData[i].Flag=0;
		sHaClanData[i].lpClanMark=0;
		sHaClanData[i].Score=0;
		
		if(i<4){
			haCrystalTowerCount[i]=0;
		}
	}
	BoardTime = 60*30;
	
	return TRUE;
}
/*----------------------------------------------------------------------------*
*			       �÷��� Ÿ�� ǥ��
*-----------------------------------------------------------------------------*/
int cHASIEGE::ShowPlayTime(int StartTime)
{
	if(StartTime==0){
		SetCastleInit();
		return TRUE;
	}
	//�÷��� Ÿ���� �����Ѵ�.
	haPlayTime[0] = StartTime%60;     //��
	haPlayTime[1] = StartTime/60;
	haPlayTime[1]-= StartTime/3600*60;
	haPlayTime[2] = StartTime/3600;   //�ð�

	//1�ð� �������� �ʱ�ȭ ���ش�.
	//if(StartTime%60*10 == 0){
	//	SetCastleInit();
	//}

	
	if(rsBlessCastle.TimeSec[1] > 0 ){
		haSiegeBoardFlag = 1;//�ʱ�ȭ ���ش�.
		BoardTime = 0;
	}
	else{
		haSiegeBoardFlag = 0;
		haStartPosiX = 0;
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*			<ha>
*-----------------------------------------------------------------------------*/
int cHASIEGE::ShowPickUserKillPoint(int x,int y,int KillCount)
{	
	return TRUE;
}
/*----------------------------------------------------------------------------*
*						 Ŭ����ų ����
*-----------------------------------------------------------------------------*/
//Ŭ����ų�� ������ �����Ѵ�.
int cHASIEGE::SetClanSkill(int ClanSkill) 
{
	DWORD SkillCode;
	
	haClanSkillTime = 0;
	//�ʱ�ȭ 
	switch(ClanSkill){
		case SIN_CLANSKILL_ABSORB:
			SkillCode = CLANSKILL_ABSORB;
		break;
		case SIN_CLANSKILL_DAMAGE:
			//SkillCode = CLANSKILL_ABSORB;
			SkillCode = CLANSKILL_ATTACK;
		break;
		case SIN_CLANSKILL_EVASION:
			//SkillCode = CLANSKILL_ABSORB;
			SkillCode = CLANSKILL_EVASION;
		break;
	}
    
	if(rsBlessCastle.dwMasterClan == GetClanCode(lpCurPlayer->smCharInfo.ClassClan)){
		if(cSkill.SearchContiueSkillCODE(SkillCode)==SkillCode){
			return TRUE;
		}
		else{
			cSkill.CancelContinueSkill(CLANSKILL_ATTACK);
			cSkill.CancelContinueSkill(CLANSKILL_EVASION);
			cSkill.CancelContinueSkill(CLANSKILL_ABSORB);	
		}
	}
	else{
		cSkill.CancelContinueSkill(CLANSKILL_ATTACK);
		cSkill.CancelContinueSkill(CLANSKILL_EVASION);
		cSkill.CancelContinueSkill(CLANSKILL_ABSORB);
		return TRUE;
	}

	//Ŭ������ ������ Ŭ����ų�� �����Ѵ�.
	sSKILL haClanSkill;
    
	for(int j = 0 ; j < SIN_MAX_SKILL; j++){
		if(sSkill[j].CODE == SkillCode){
			memcpy(&haClanSkill,&sSkill[j],sizeof(sSKILL));
		    haClanSkill.UseTime=60;
			sinContinueSkillSet(&haClanSkill);
			break;
		}
	}
	cInvenTory.SetItemToChar();
	
	return TRUE;
}

int SetSODSkill(int SODSkill)
{
	DWORD SkillCode = 0;

	switch (SODSkill)
	{
	case SIN_SODSKILL_GOLD:
		SkillCode = SOD_SKILL_GOLD;
		break;
	case SIN_SODSKILL_SILVER:
		SkillCode = SOD_SKILL_SILVER;
		break;
	case SIN_SODSKILL_BRONZE:
		SkillCode = SOD_SKILL_BRONZE;
		break;
	}

	if (SODSkill)
	{
		if (cSkill.SearchContiueSkillCODE(SkillCode) == SkillCode)
		{
			return TRUE;
		}
		else
		{
			cSkill.CancelContinueSkill(SOD_SKILL_GOLD);
			cSkill.CancelContinueSkill(SOD_SKILL_SILVER);
			cSkill.CancelContinueSkill(SOD_SKILL_BRONZE);
		}
	}
	else
	{
		cSkill.CancelContinueSkill(SOD_SKILL_GOLD);
		cSkill.CancelContinueSkill(SOD_SKILL_SILVER);
		cSkill.CancelContinueSkill(SOD_SKILL_BRONZE);
		return TRUE;
	}

	sSKILL haClanSkill;

	for (int j = 0; j < SIN_MAX_SKILL; j++)
	{
		if (sSkill[j].CODE == SkillCode)
		{
			memcpy(&haClanSkill, &sSkill[j], sizeof(sSKILL));
			haClanSkill.UseTime = 60;
			sinContinueSkillSet(&haClanSkill);
			break;
		}
	}
	cInvenTory.SetItemToChar();

	return TRUE;
}
/*----------------------------------------------------------------------------*
*				 haGoon ������ ���� �������� ����Ѵ�.
*-----------------------------------------------------------------------------*/	
int haCastleSkillUseFlag =0;
int cHASIEGE::SetCastleItemSkill(int ItemKind)
{
	DWORD CastleSkillCode;
	int   CastleSkillUseTime=0;

	switch(ItemKind){
		case SIN_CASTLEITEMSKILL_S_INVU:
			CastleSkillCode = SCROLL_INVULNERABILITY;
			CastleSkillUseTime = 30;
		break;
		case SIN_CASTLEITEMSKILL_S_CRITICAL:
			CastleSkillCode = SCROLL_CRITICAL;
			CastleSkillUseTime = 30;
		break;
		case SIN_CASTLEITEMSKILL_S_EVASION:
			CastleSkillCode = SCROLL_EVASION;
			CastleSkillUseTime = 30;
		break;
		case SIN_CASTLEITEMSKILL_S_P_LIFE:
			CastleSkillCode = 0;
		break;
		case SIN_CASTLEITEMSKILL_S_RES:
			CastleSkillCode = 0;
		break;
		case SIN_CASTLEITEMSKILL_R_FIRE_C:
			CastleSkillCode = STONE_R_FIRECRYTAL;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_R_ICE_C:
			CastleSkillCode = STONE_R_ICECRYTAL;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_R_LIGHTING_C:
			CastleSkillCode = STONE_R_LINGHTINGCRYTAL;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_FIGHTER:
			CastleSkillCode = STONE_A_FIGHTER;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_MECHANICIAN:
			CastleSkillCode = STONE_A_MECHANICIAN;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_PIKEMAN:
			CastleSkillCode = STONE_A_PIKEMAN;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_ARCHER:
			CastleSkillCode = STONE_A_ARCHER;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_KNIGHT:
			CastleSkillCode = STONE_A_KNIGHT;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_ATALANTA:
			CastleSkillCode = STONE_A_ATALANTA;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_MAGICIAN:
			CastleSkillCode = STONE_A_MAGICIAN;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_PRIESTESS:
			CastleSkillCode = STONE_A_PRIESTESS;
			CastleSkillUseTime = 60;
		break;
	}
	//�ش� �Ŵ� �������� ������ �����۽�ų�� �����Ѵ�.
	sSKILL haCastleSkill;

	haCastleSkillUseFlag =1;
    if(CastleSkillCode==0)return TRUE; //������ �������� ������� �ʴ� ���� ���� �����ش�.  

	for(int j = 0 ; j < SIN_MAX_SKILL; j++){
		if(sSkill[j].CODE == CastleSkillCode){
			memcpy(&haCastleSkill,&sSkill[j],sizeof(sSKILL));
			haCastleSkill.UseTime=CastleSkillUseTime;
			sinContinueSkillSet(&haCastleSkill);
			SwitchSkill(&haCastleSkill);
			break;
		}
	}
	
	return TRUE;
}

/*----------------------------------------------------------------------------*
*						������ �����޴� ����Ÿ�� ������
*-----------------------------------------------------------------------------*/	
int cHASIEGE::SendServerSiegeData()
{
	int i;

	smTRANS_BLESSCASTLE TempBlessCastle;
	//TempBlessCastle ������ ������
	TempBlessCastle.TaxRate        = HaTaxRate;							//����
	TempBlessCastle.ClanSkill      = cSinSiege.ClanSkill;				//Ŭ����ų
	TempBlessCastle.Price          = cSinSiege.Price;
	for(i=0;i<3;i++){
		TempBlessCastle.MercenaryNum[i]  = cSinSiege.MercenaryNum[i];   //�뺴
	}
	for(i=0;i<6;i++){
		TempBlessCastle.Tower[i] = cSinSiege.TowerTypeDraw[i][1];  //��Ÿ���� Ÿ���� ���� 
	}

	SendBlessCastleToServer(&TempBlessCastle,0);//������ ������.
	SaveGameData();
	return TRUE;
}


/*----------------------------------------------------------------------------*
*				�޴� �ʱ�ȭ�� ���ش�.
*-----------------------------------------------------------------------------*/
int cHASIEGE::SetCastleMenuInit()
{
	haSiegeMenuFlag=0;			 //�޴��� �ݾ��ش�.
	haSiegeMenuKind=0;			 //�޴������� �ʱ�ȭ ���ش�.
	haSiegeMerFlag=0;			 //�뺴 �÷��� �ʱ�ȭ ���ش�.
	SiegeIconPosi[0][0]=70+20-7; //��ũ���� �ٽ� ��ġ
    SiegeIconPosi[5][0]=70+20-7; //��ũ���� �ٽ� ��ġ

	return TRUE;	
}
/*----------------------------------------------------------------------------*
*						 Ű�ٿ�
*-----------------------------------------------------------------------------*/
void cHASIEGE::KeyDown()
{
	
}
/*----------------------------------------------------------------------------*
*						 LButtonDown/UP
*-----------------------------------------------------------------------------*/
void cHASIEGE::LButtonDown(int x, int y) {}
void cHASIEGE::LButtonUp(int x, int y) {}
/*----------------------------------------------------------------------------*
*						DrawText
*-----------------------------------------------------------------------------*/
void cHASIEGE::DrawText() {}

/*----------------------------------------------------------------------------*
*						 Class cSINSIEGE
*-----------------------------------------------------------------------------*/	
int cSINSIEGE::GetTaxRate()
{	
	return TaxRate;
}
int cSINSIEGE::SetTaxRate(int TempTaxRate)
{
	TaxRate = TempTaxRate;
	return TRUE;
}

int cSINSIEGE::GetTotalTax()
{
	//������ Ŭ���Ӵϱݾ� ������ �䱸�Ѵ�
	//TotalTax = getSiegeClanMoneyToServer(0,0); �뷫
	return TotalTax;
}
int cSINSIEGE::GetTaxMoney(int Money )
{
	//ã����� ��ŭ�� ���� �䱸�Ѵ�
	return TRUE;
}

/*----------------------------------------------------------------------------*
*					������ ������ �÷��̸� �����ش�.
*-----------------------------------------------------------------------------*/	
int cHASIEGE::ShowCastlePlayMovie(char *szPath,char *TitleName,int Option)
{

	memset(haMovieName ,0,sizeof(haMovieName));
	lstrcpy(haMovieName,TitleName);

	haMovieFlag = 1;  //�÷��� �����ش�.

	if(haMovieFlag){ 
		Play_ParkPlayer( szPath ,42,100, 307,260 ,150);
	}
	return TRUE;
}





