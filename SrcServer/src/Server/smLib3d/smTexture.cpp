
#include "smd3d.h"



//######################################################################################
//�� �� �� : �� �� ��
int		g_IsReadTextures = 1;

BYTE	g_DibImageDateBuff[ (1024*768)*4 ];
int		g_DibLastReadWidth;
int		g_DibLastReadHeight;
int		g_TgaLastBitCnt;
int		g_TgaLastSwapHeight;

int						new_smCreateTexture( smTEXTUREHANDLE *lpTexHandle, int MipMap = 0 );

int						new_LoadDib( char *Filename );
int						new_LoadTga( char *Filename );
int						New_DrawSurfaceFromTga( void* lpDDSurface );

void*	new_LoadBmpCreateTexSurface( char *Filename, int MipMap, int &rTexHalf );
void*	new_LoadTgaCreateTexSurface( char *Filename, int MipMap, int &rTexHalf );
void*	new_LoadBmpSurfaceOffscreen( char *Filename );
//######################################################################################




#define ERROR_LIST_MAX		32
#define ERROR_LIST_MASK		(ERROR_LIST_MAX-1)

char szErrorList[ERROR_LIST_MAX][64];
int ErrorListCnt  = 0;


int AddErrorList( char *szErrMsg )
{
	/*
	int cnt;

	cnt = ErrorListCnt & ERROR_LIST_MASK;

	lstrcpy( szErrorList[cnt] , szErrMsg );

	ErrorListCnt++;
	*/
	return ErrorListCnt;
}

int DisplayError( HDC hdc , int x, int y )
{
	int cnt,mcnt;
	int len;
	int dy;

	dy = y;

	for(cnt=ErrorListCnt-ERROR_LIST_MASK;cnt<ErrorListCnt;cnt++) {
		if ( cnt>=0 ) {
			mcnt = cnt & ERROR_LIST_MASK;
			len = lstrlen( szErrorList[mcnt] );
			//dsTextLineOut( hdc , x,dy ,szErrorList[mcnt] , len );
			dy+=14;
		}
	}

	return TRUE;
}


//���� ��� �޸� ����ġ
DWORD	VramTotal = 0;


//######################################################################################
//�� �� �� : �� �� ��
#define	MAX_MAP_BLINK_COLOR_TIME				8

const char *szBlinkTimeScript[ MAX_MAP_BLINK_COLOR_TIME ] =
{
	"BLINK_TIME1:",
	"BLINK_TIME2:",
	"BLINK_TIME3:",
	"BLINK_TIME4:",
	"BLINK_TIME5:",
	"BLINK_TIME6:",
	"BLINK_TIME7:",
	"BLINK_TIME8:",
};

const DWORD dwBlinkTimeCode[ MAX_MAP_BLINK_COLOR_TIME ] =
{
    9, 10, 11, 12, 13, 14, 15, 16,
};
//######################################################################################


//######################################################################################
//�� �� �� : �� �� ��
int MipMapModeCreate;						// �Ӹ� ��� ���� ����.
int TextureSwapMode	= TRUE;					// �׷��� ����Ƽ�� ���ؼ� �Ӹ� ��� ���� �˱�����. ��������.
static int TexturHalfSize = FALSE;			// �ؽ��� �������� ũ�� ����

// 6.0 ������ �Ӹ� ������ ���� �ܰ� 256��256, 128��128, 64��64, 32��32, 16��16
// ���� 256��128 �� ���� �Ҽ��� ������. ī�庰�� �ȵǴ� �͵� �ִٰ� �մϴ�.
// ���� ������ �ִ� 3�ܰ� ������ ��� �ϱ�� ����.
static char MipMapFileListBuff[ MIPMAP_FILELIST ][16] = { "", "_mm1", "_mm2", "_mm3", "_mm4", };

static int  MipMapCount = 0;
static char MipMapFileBuff[ MIPMAP_FILELIST ][126] = { 0,};
static int  MipMapCountA = 0;
static char MipMapFileABuff[ MIPMAP_FILELIST ][126] = { 0,};
static char FileTypeBuff[16] = { 0,};
//######################################################################################


int		   MaterialFrame;

//�ؽ��� �޸� ���� ��� ����
int SetTextureSwapMode( int mode )
{
	int OldValue;

	OldValue = TextureSwapMode;

	TextureSwapMode = mode;

	return OldValue;
}

//�ؽ����� ���� ���� ( 0-��ȭ�� 1-���� 2-��ȭ�� )
int smSetTextureLevel( int Level )
{
	switch( Level ) {
	case 0:	//( ���� �޸𸮰� ū �ý��ۿ��� ���� )
		//��� �ؽ��ĸ� ���� �޸𸮷� �ø���
		TextureSwapMode = FALSE;
		TexturHalfSize = 0;
		break;

	case 1: //( �޸𸮰� ū �ý��ۿ��� ���� )
		//�ؽ��ĸ� ������ �ý��� �޸𸮿� ����
		TextureSwapMode = TRUE;
		TexturHalfSize = 0;
		break;

	case 2: //( ��� ���� �ý��ۿ��� ��� )
		//��� �ؽ��ĸ� ����ũ��� �ٿ��� ���� �޸𸮿� �ø�
		TextureSwapMode = TRUE;
		TexturHalfSize = 1;
		break;

	case 3: //( VRAM 8�ް� ���� ���� ���� �ý��ۿ��� ��� )
		//��� �ؽ��ĸ� 1/4ũ��� �ٿ��� ���� �޸𸮿� �ø�
		TextureSwapMode = TRUE;
		TexturHalfSize = 2;
		break;
	}

	return TRUE;
}



smTEXTURE::smTEXTURE()
{
	Init();
}

smTEXTURE::~smTEXTURE()
{
//	Remove();
}

void smTEXTURE::Init()
{
	//######################################################################################
	//�� �� �� : �� �� ��
	ZeroMemory( TexSpeedSum, sizeof(TexSpeedSum) );
	//######################################################################################

	ZeroMemory( Texture , sizeof( smTEXTUREHANDLE ) * MAX_TEXTURE ); 
	ZeroMemory( SwapTexture , sizeof( smSWAPTEXTURE ) * SWAPTEXTURE_MAX ); 
	TextureCnt	= 0;
	SwapCount	= 0;

	//ũ��Ƽ�� ���� �ʱ�ȭ
	InitializeCriticalSection( &cTextureSection );

}

int smTEXTURE::Remove()
{
	return TRUE;
}


//######################################################################################
//�� �� �� : �� �� ��
//int smTEXTURE::Find( char *name )
int smTEXTURE::Find( DWORD dwCode, char *Name )
{
	int cnt;
	for( cnt=0; cnt < MAX_TEXTURE; cnt++ )
	{
		if( TexSpeedSum[cnt] == dwCode )
		{
			if( Texture[cnt].UseCounter && _stricmp( Texture[cnt].Name, Name ) == 0 )
				return cnt;
		}
	}

	return -1;
}
//######################################################################################


//�ؽ��� ����� �߰�
smTEXTUREHANDLE *smTEXTURE::Add( char *name , char *nameA )
{
	int TexNum;
	int cnt;

	//######################################################################################
	//�� �� �� : �� �� ��	
	extern DWORD GetSpeedSum( char *szName );

	DWORD dwCode = GetSpeedSum(name);
	TexNum = Find( dwCode, name );
	//TexNum = Find( name );
	//######################################################################################

	if ( TexNum>=0 ) {
		LastTextureCnt = TexNum;
		Texture[ TexNum ].UseCounter++;
		return &Texture[ TexNum ];
	}

	for( cnt=0;cnt<MAX_TEXTURE;cnt++) {
		if ( Texture[ cnt ].UseCounter==0 ) break;
	}
	if ( cnt==MAX_TEXTURE ) return NULL;
	TextureCnt = cnt;

	lpLastTextureSurface = &Texture[ TextureCnt ].lpDDSurface;
	lpLastTexture = &Texture[ TextureCnt ].lpD3DTexture;

	//�ʱ� �ڵ� ���� 0 �̴�
	Texture[TextureCnt].lpDDSurface = NULL;
	Texture[TextureCnt].lpD3DTexture = NULL;

	lstrcpy( Texture[ TextureCnt ].Name , name );
	if ( nameA )
		lstrcpy( Texture[ TextureCnt ].NameA , nameA );
	else 
		Texture[ TextureCnt ].NameA[0] = 0;

	Texture[ TextureCnt ].TexSwapMode = TextureSwapMode;			// �⺻������ ���Ҹ�� �㰡
	Texture[ TextureCnt ].UseCounter++;
	Texture[ TextureCnt ].lpD3DTextureLarge = NULL;

	//######################################################################################
	//�� �� �� : �� �� ��	
	TexSpeedSum[ TextureCnt ] = dwCode;
	//######################################################################################

	return &Texture[ TextureCnt ];
}

//�ؽ��ĸ� �����Ѵ� ( 1�ܰ�� �����Ͽ� ��Ʈ������� ��ũ�� ���� ��� ���� ���� )
int smTEXTURE::Delete( smTEXTUREHANDLE *lpTex )
{
	int cnt;

	if ( lpTex->UseCounter<=0 ) return FALSE;

	lpTex->UseCounter--;

	if ( lpTex->UseCounter<=0 ) {
		//���� �ؽ��Ŀ��� ������̸� �����ؽ��ĸ� ã�Ƴ��� ����
		if ( lpTex->lpD3DTextureLarge ) {
			for( cnt=0; cnt<SWAPTEXTURE_MAX ; cnt++ ) {
				if ( SwapTexture[cnt].SwapState && SwapTexture[cnt].smTextureMaster==lpTex ) {
					DeleteSwapTexture( cnt );
					break;
				}
			}
		}

		lpTex->lpD3DTexture = 0;
		lpTex->lpDDSurface = 0;
		lpTex->lpDDSSysMemory = 0;

		VramTotal -= lpTex->Width * lpTex->Height  * 2 ;

	}

	return lpTex->UseCounter;
}

/*
LPDIRECT3DTEXTURE2 *smTEXTURE::AddName( char *name )
{
	int TexNum;

	TexNum = Find( name );
	if ( TexNum>=0 ) {
		LastTextureCnt = TexNum;
		return &Texture[ TexNum ].lpD3DTexture;
	}

	lpLastTextureSurface = &Texture[ TextureCnt ].lpDDSurface;
	lpLastTexture = &Texture[ TextureCnt ].lpD3DTexture;

	lstrcpy( Texture[ TextureCnt ].Name , name );
	Texture[ TextureCnt ].NameA[0] = 0;
	TextureCnt++;

	return &Texture[ TextureCnt-1 ].lpD3DTexture;
}

LPDIRECT3DTEXTURE2 *smTEXTURE::AddName( char *name , char *nameA )
{
	int TexNum;
	char szBuff[64];
	LPDIRECT3DTEXTURE2 *lpTexture;
	FILE *fp;

	TexNum = Find( name );
	if ( TexNum>=0 ) {
		LastTextureCnt = TexNum;
		return &Texture[ TexNum ].lpD3DTexture;
	}

	lpTexture = &Texture[ TextureCnt ].lpD3DTexture ;

	lpLastTextureSurface = &Texture[ TextureCnt ].lpDDSurface;
	lpLastTexture = &Texture[ TextureCnt ].lpD3DTexture;
	LastTextureCnt = TextureCnt;

	lstrcpy( Texture[ TextureCnt ].Name , name );
	lstrcpy( Texture[ TextureCnt ].NameA , nameA );
	TextureCnt++;

	return lpTexture;
}
*/


//SWAP �ؽ��ĸ� ����
int smTEXTURE::DeleteSwapTexture( int TexNum )
{
	return TRUE;
}

//ū�ؽ��ĸ� SWAP �Ͽ� ����� 
int smTEXTURE::SetLargeTexture( smTEXTUREHANDLE *TexHandle )
{
	return TRUE;
}

//�ؽ��� 
int smTEXTURE::ReadTexture()
{
	//######################################################################################
	//�� �� �� : �� �� ��
	if( g_IsReadTextures == 0 )
		return 0;
	//######################################################################################

	int cnt;
	char szErrMsg[128];
	int	Result;
	int ReadCount = 0;

	for( cnt=0;cnt<MAX_TEXTURE;cnt++ ) {
		if ( Texture[cnt].UseCounter && !Texture[cnt].lpD3DTexture ) {

			EnterCriticalSection( &cTextureSection );			//ũ��ƼĮ ���� ����

			//######################################################################################
			//�� �� �� : �� �� ��
			//Result = smCreateTexture( &Texture[cnt] );
			Result = new_smCreateTexture( &Texture[cnt] );
			//######################################################################################

			if ( Result<=0 ) {
				switch( Result ) {
				case 0:
					wsprintf( szErrMsg , "TEX_D3D ���� [%s]" , Texture[cnt].Name );
					break;
				case -1:
					wsprintf( szErrMsg , "TEX_FILE ���� [%s]" , Texture[cnt].Name );
					break;
				case -2:
					wsprintf( szErrMsg , "TEX_ALPHA ���� [%s]" , Texture[cnt].Name );
					break;
				}
				//���� ��� ����
				AddErrorList( szErrMsg );
			}
			ReadCount++;

			LeaveCriticalSection( &cTextureSection );		//ũ��ƼĮ ���� ����

			if ( (ReadCount&0x7)==0 )	smPlayWindowMessage();	//�޼��� ó��
		}
	}

	return TRUE;
}

//�Ҿ� ���� �ؽ��ĸ� ����� �ٽ� �ҷ� ���δ�
int smTEXTURE::Restore()
{
	return TRUE;
}


smTEXTURE smTexture;

////////////////////// smMATERIAL_GROUP ////////////////////////


smMATERIAL_GROUP::smMATERIAL_GROUP()
{

}

smMATERIAL_GROUP::smMATERIAL_GROUP( int MaterialMax )
{
	Init( MaterialMax );
}

smMATERIAL_GROUP::~smMATERIAL_GROUP()
{
	Close();
}

// ��Ʈ���� �ʱ�ȭ
void smMATERIAL_GROUP::Init( int MaterialMax )
{

	MaterialCount = 0;
	MaxMaterial = MaterialMax;
	ReformTexture = 0;

	smMaterial = new smMATERIAL[ MaterialMax ];
	ZeroMemory( smMaterial , sizeof( smMATERIAL )*MaterialMax );

}

// ��Ʈ���� ����ȭ
int smMATERIAL_GROUP::Close()
{
	DWORD cnt , tcnt;

	for( cnt=0;cnt<MaterialCount;cnt++ ) {
		if ( smMaterial[cnt].InUse ) {
			//�ؽ��ĸ� �����Ѵ�
			for( tcnt=0; tcnt<smMaterial[cnt].TextureCounter; tcnt++ ) 
				if ( smMaterial[cnt].smTexture[tcnt] )
					smTexture.Delete (  smMaterial[cnt].smTexture[tcnt]  );

			for( tcnt=0; tcnt<smMaterial[cnt].AnimTexCounter; tcnt++ ) 
				if ( smMaterial[cnt].smAnimTexture[tcnt] )
					smTexture.Delete (  smMaterial[cnt].smAnimTexture[tcnt]  );

		}
	}

	delete smMaterial;

	return TRUE;
}

#define TEXFILENAME_SIZE	64

//������ ����Ÿ�� ũ�⸦ �̸� �˷���
int smMATERIAL_GROUP::GetSaveSize()
{
	int size;
	DWORD cnt ,tcnt;
	int	len,alen;

	size	 = sizeof( smMATERIAL_GROUP );

	for(cnt=0;cnt<MaterialCount;cnt++) {
		size+= sizeof( smMATERIAL );
		if ( smMaterial[cnt].InUse ) {
			size += sizeof(int);					//�ؽ��� �̸� ���̰� �� int��
			for( tcnt=0; tcnt<smMaterial[cnt].TextureCounter ; tcnt++) {
				len = lstrlen( smMaterial[cnt].smTexture[tcnt]->Name )+1;
				alen = lstrlen( smMaterial[cnt].smTexture[tcnt]->NameA )+1;
				size += len;
				size += alen;
			}

			for( tcnt=0; tcnt<smMaterial[cnt].AnimTexCounter ; tcnt++) {
				len = lstrlen( smMaterial[cnt].smAnimTexture[tcnt]->Name )+1;
				alen = lstrlen( smMaterial[cnt].smAnimTexture[tcnt]->NameA )+1;
				size += len;
				size += alen;
			}

		}
	}
	return size;
}

//����Ÿ�� ���Ϸ� ���� 
int smMATERIAL_GROUP::SaveFile( HANDLE hFile )
{
	DWORD	dwAcess;
	DWORD cnt ,tcnt;
	int	len;
	int size;

	size =	WriteFile( hFile , &Head	, sizeof( smMATERIAL_GROUP )	, &dwAcess , NULL );

	for(cnt=0;cnt<MaterialCount;cnt++) {
		//��Ʈ���� ����
		size+= WriteFile( hFile , &smMaterial[cnt] , sizeof( smMATERIAL )	, &dwAcess , NULL );

		if ( smMaterial[cnt].InUse ) {

			//�ؽ��� ���� ��Ͽ� ���� �̸� ���� ���
			len = 0;
			for( tcnt=0; tcnt<smMaterial[cnt].TextureCounter ; tcnt++) {
				len += lstrlen( smMaterial[cnt].smTexture[tcnt]->Name )+1;
				len += lstrlen( smMaterial[cnt].smTexture[tcnt]->NameA )+1;
			}
			for( tcnt=0; tcnt<smMaterial[cnt].AnimTexCounter ; tcnt++) {
				len += lstrlen( smMaterial[cnt].smAnimTexture[tcnt]->Name )+1;
				len += lstrlen( smMaterial[cnt].smAnimTexture[tcnt]->NameA )+1;
			}
			//���ڿ� ���� �̸� ���
			size+= WriteFile( hFile , &len , sizeof(int) , &dwAcess , NULL );

			//�ؽ��� ���� �̸��� ���������� ����
			for( tcnt=0; tcnt<smMaterial[cnt].TextureCounter ; tcnt++) {
				len = lstrlen( smMaterial[cnt].smTexture[tcnt]->Name )+1;
				size+= WriteFile( hFile , smMaterial[cnt].smTexture[tcnt]->Name , len , &dwAcess , NULL );
				len = lstrlen( smMaterial[cnt].smTexture[tcnt]->NameA )+1;
				size+= WriteFile( hFile , smMaterial[cnt].smTexture[tcnt]->NameA , len , &dwAcess , NULL );
			}

			for( tcnt=0; tcnt<smMaterial[cnt].AnimTexCounter ; tcnt++) {
				len = lstrlen( smMaterial[cnt].smAnimTexture[tcnt]->Name )+1;
				size+= WriteFile( hFile , smMaterial[cnt].smAnimTexture[tcnt]->Name , len , &dwAcess , NULL );
				len = lstrlen( smMaterial[cnt].smAnimTexture[tcnt]->NameA )+1;
				size+= WriteFile( hFile , smMaterial[cnt].smAnimTexture[tcnt]->NameA , len , &dwAcess , NULL );
			}

		}
	}

	return size;
}

//���Ͽ��� ����Ÿ�� �ε� 
int smMATERIAL_GROUP::LoadFile( HANDLE hFile )
{
	DWORD	dwAcess;
	DWORD	cnt ,tcnt;
	int		StrLen;
	int		size;
	char	szNameBuff[4096];
	char	*lpNameBuff;
	char	*szName , *szNameA;

	//�׷��� ������ �о��
	size=ReadFile( hFile , &Head , sizeof( smMATERIAL_GROUP ) , &dwAcess , NULL );

	//��Ʈ���� �޸� ����
	smMaterial = new smMATERIAL[ MaterialCount ];

	for(cnt=0;cnt<MaterialCount;cnt++) {
		//��Ʈ���� ����Ÿ �о��
		size+=	ReadFile( hFile , &smMaterial[cnt] , sizeof( smMATERIAL ) , &dwAcess , NULL );

		if ( smMaterial[cnt].InUse ) {
			//�ؽ��� ���� ���� ũ�� ����
			size+=	ReadFile( hFile , &StrLen , sizeof( int ) , &dwAcess , NULL );
			//�ؽ��� ���� ���� ũ�⸸ŭ ����Ÿ ���� 
			size+=	ReadFile( hFile , szNameBuff , StrLen, &dwAcess , NULL );

			lpNameBuff = szNameBuff;

			//�ؽ��� ����
			for( tcnt=0; tcnt<smMaterial[cnt].TextureCounter ; tcnt++) {
				szName = lpNameBuff;
				lpNameBuff += lstrlen( szName )+1;
				szNameA = lpNameBuff;
				lpNameBuff += lstrlen( szNameA )+1;

				if ( szNameA[0] )
					smMaterial[cnt].smTexture[tcnt] = smTexture.Add( szName , szNameA );
				else
					smMaterial[cnt].smTexture[tcnt] = smTexture.Add( szName );
			}

			//���ϸ��̼� �ؽ��� ����
			for( tcnt=0; tcnt<smMaterial[cnt].AnimTexCounter ; tcnt++) {
				szName = lpNameBuff;
				lpNameBuff += lstrlen( szName )+1;
				szNameA = lpNameBuff;
				lpNameBuff += lstrlen( szNameA )+1;

				if ( szNameA[0] )
					smMaterial[cnt].smAnimTexture[tcnt] = smTexture.Add( szName , szNameA );
				else
					smMaterial[cnt].smAnimTexture[tcnt] = smTexture.Add( szName );
			}
		}

	}

	return size;
}

//������ �ʴ� ��Ʈ���� ����
int smMATERIAL_GROUP::DeleteUnuseMaterial()
{
	DWORD cnt , dcnt , tcnt;

	dcnt = 0;
	for( cnt=0;cnt<MaterialCount;cnt++ ) {
		if ( smMaterial[cnt].InUse==TRUE ) {
			//�ؽ��ĸ� �����Ѵ�
			for( tcnt=0; tcnt<smMaterial[cnt].TextureCounter; tcnt++ ) 
				smTexture.Delete (  smMaterial[cnt].smTexture[tcnt]  );

			for( tcnt=0; tcnt<smMaterial[cnt].AnimTexCounter; tcnt++ ) 
				smTexture.Delete (  smMaterial[cnt].smAnimTexture[tcnt]  );

			ZeroMemory( &smMaterial[cnt] , sizeof( smMATERIAL ) );
			//smMaterial[cnt].InUse = FALSE;
			dcnt++;
		}
	}

	return dcnt;
}


//��Ʈ������ ���
int smMATERIAL_GROUP::AddMaterial( ASE_MATERIAL *aseMaterial , char *szScript )
{
	int cnt,len;
	int	AnimCount,FrameSpeed;
	int MatNum;
	char	*lpAnimFileList[16];
	char	*szDirectory;
	char	*lpScript;
	char	szTemp[64];

	MatNum = MaterialCount;
	MaterialCount++;

	smMaterial[MatNum].InUse  = TRUE;
	smMaterial[MatNum].Shade  = TRUE;
	smMaterial[MatNum].BlendType = SMMAT_BLEND_ALPHA;
	smMaterial[MatNum].TwoSide = aseMaterial->TwoSide;
	smMaterial[MatNum].ReformTexture = 0;

	// ���� �ؽ��Ŀ� ���
	if ( !aseMaterial->MAP_OPACITY[0] ) {
		for( cnt=0;cnt<aseMaterial->TextureCounter;cnt++) {
			smMaterial[MatNum].smTexture[cnt] = smTexture.Add( aseMaterial->BITMAP[cnt] );
			smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
			smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
			smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
		}
		smMaterial[MatNum].MapOpacity = FALSE;
	}
	else {
		//######################################################################################
		//�� �� �� : �� �� ��
		if( aseMaterial->TextureCounter > 1 )
		{
			for( cnt=0; cnt < aseMaterial->TextureCounter-1; cnt++ )
			{
				smMaterial[MatNum].smTexture[cnt] = smTexture.Add( aseMaterial->BITMAP[cnt], aseMaterial->MAP_OPACITY );
				smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
				smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
				smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
			}

			smMaterial[MatNum].smTexture[cnt] = smTexture.Add( aseMaterial->BITMAP[cnt] );
			smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
			smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
			smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
		}
		else
		{
			for( cnt=0; cnt < aseMaterial->TextureCounter; cnt++ )
			{
				smMaterial[MatNum].smTexture[cnt] = smTexture.Add( aseMaterial->BITMAP[cnt] , aseMaterial->MAP_OPACITY );
				smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
				smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
				smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
			}
		}

		smMaterial[MatNum].MapOpacity = TRUE;
		//######################################################################################
	}

	//��ǥ ���� �ؽ��� ���� ýũ�Ͽ� ����
	if ( smMaterial[MatNum].ReformTexture )	ReformTexture ++;

	smMaterial[MatNum].TextureCounter = aseMaterial->TextureCounter;	//�ؽ��ĸ��� ��
	smMaterial[MatNum].Transparency   = aseMaterial->Transparency ;		//������
	smMaterial[MatNum].SelfIllum	  = aseMaterial->SelfIllum ;		//��ü�߱�
	smMaterial[MatNum].Diffuse        = aseMaterial->Diffuse;			//�⺻����

	smMaterial[MatNum].UseState			= aseMaterial->ScriptState;
	smMaterial[MatNum].TextureType		= SMTEX_TYPE_MULTIMIX;

	if( aseMaterial->BlendType )
		smMaterial[MatNum].BlendType = aseMaterial->BlendType;

	//�ٴ� �浹 üũ
	if ( smMaterial[MatNum].Transparency==0 ) 
		smMaterial[MatNum].MeshState		= SMMAT_STAT_CHECK_FACE;

	//���� ��鸮��
	if ( (aseMaterial->ScriptState&sMATS_SCRIPT_WIND) ) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ1;
		smMaterial[MatNum].MeshState		= 0;
	}
	if ( (aseMaterial->ScriptState&sMATS_SCRIPT_WINDX1) ) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDX1;
		smMaterial[MatNum].MeshState		= 0;
	}
	if ( (aseMaterial->ScriptState&sMATS_SCRIPT_WINDX2) ) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDX2;
		smMaterial[MatNum].MeshState		= 0;
	}
	if ( (aseMaterial->ScriptState&sMATS_SCRIPT_WINDZ1) ) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ1;
		smMaterial[MatNum].MeshState		= 0;
	}
	if ( (aseMaterial->ScriptState&sMATS_SCRIPT_WINDZ2) ) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ2;
		smMaterial[MatNum].MeshState		= 0;
	}

	if ( (aseMaterial->ScriptState&sMATS_SCRIPT_WINDZ2) ) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ2;
		smMaterial[MatNum].MeshState		= 0;
	}

	if ( (aseMaterial->ScriptState&sMATS_SCRIPT_WATER) ) {
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WATER;
		smMaterial[MatNum].MeshState		= 0;
	}

	//��Ʈ���� �浹 üũ �㰡
	if ( (aseMaterial->ScriptState&sMATS_SCRIPT_NOTPASS) ) {
		smMaterial[MatNum].MeshState		= SMMAT_STAT_CHECK_FACE;	//�㰡
	}
	else {
		if ( (aseMaterial->ScriptState&sMATS_SCRIPT_PASS) ) {
			smMaterial[MatNum].MeshState		= 0;					//�Ұ�
		}
	}
	//������ ���߿� �׸���
	if ( (aseMaterial->ScriptState&sMATS_SCRIPT_RENDLATTER) ) {
		smMaterial[MatNum].MeshState |= sMATS_SCRIPT_RENDLATTER;
	}

	//######################################################################################
	//�� �� �� : �� �� ��
	if( (aseMaterial->ScriptState & sMATS_SCRIPT_CHECK_ICE) )
		smMaterial[MatNum].MeshState |= sMATS_SCRIPT_CHECK_ICE;
	//######################################################################################

	//######################################################################################
	//�� �� �� : �� �� ��
	if( (aseMaterial->ScriptState & sMATS_SCRIPT_ORG_WATER) )
		smMaterial[MatNum].MeshState = sMATS_SCRIPT_ORG_WATER;
	//######################################################################################

	//�ڵ� ���ϸ��̼�
	AnimCount = 0;
	if ( szScript ) {
		if ( aseMaterial->ScriptState&sMATS_SCRIPT_ANIM2 ) AnimCount=2;
		if ( aseMaterial->ScriptState&sMATS_SCRIPT_ANIM4 ) AnimCount=4;
		if ( aseMaterial->ScriptState&sMATS_SCRIPT_ANIM8 ) AnimCount=8;
		if ( aseMaterial->ScriptState&sMATS_SCRIPT_ANIM16 ) AnimCount=16;
	}

	if ( AnimCount ) {
		len = lstrlen(szScript);

		for( cnt=0;cnt<len;cnt++) {
			if ( szScript[cnt]=='a' && szScript[cnt+1]=='n' && 
				szScript[cnt+2]=='i' && szScript[cnt+3]=='m' ) {
					for( cnt=cnt;cnt<len;cnt++) {
						if ( szScript[cnt]==':' ) break;
					}
					break;
			}
		}

		if ( cnt<len ) {
			cnt++;
			lpScript = &szScript[cnt];
			FrameSpeed = 0;

			for(cnt=cnt;cnt<len;cnt++) {
				if ( szScript[cnt]==':' ) {
					FrameSpeed = atoi( &szScript[cnt+1] );
					szScript[cnt] = 0;
					break;
				}
			}

			szDirectory = SetDirectoryFromFile( aseMaterial->BITMAP[0] );

			if ( szDirectory ) {
				for(cnt=0;cnt<AnimCount;cnt++) {
					lpAnimFileList[cnt] = new char[64];
					lstrcpy( szTemp , szDirectory );
					lstrcat( szTemp , lpScript );
					wsprintf( lpAnimFileList[cnt] , szTemp , cnt );
				}
			
				ChangeMaterialToAnimation( &smMaterial[MatNum] , lpAnimFileList , AnimCount , smMaterial[MatNum].BlendType , TRUE );
				if ( FrameSpeed ) smMaterial[MatNum].Shift_FrameSpeed = FrameSpeed;			//���ϸ��̼� Ÿ�̸� ����Ʈ

				smMaterial[MatNum].Transparency   = aseMaterial->Transparency ;		//������

				for(cnt=AnimCount-1;cnt>=0;cnt--) delete lpAnimFileList[cnt];
			}
		}
	}

	//######################################################################################
	// �� �� �� : �� �� ��
	if( (aseMaterial->ScriptState & sMATS_SCRIPT_BLINK_COLOR) && smMaterial[MatNum].WindMeshBottom == 0 )
	{
		for( cnt=0; cnt < MAX_MAP_BLINK_COLOR_TIME; cnt++ )
		{
			if( strstr( szScript, szBlinkTimeScript[cnt] ) != 0 )
				break;
		}

		if( cnt >= MAX_MAP_BLINK_COLOR_TIME )
			smMaterial[MatNum].WindMeshBottom = dwBlinkTimeCode[0];
		else
			smMaterial[MatNum].WindMeshBottom = dwBlinkTimeCode[cnt];
	}
	//######################################################################################

	aseMaterial->Regist ++;												//��Ʈ���� ��Ͽ� ���
	aseMaterial->RegistNum = MatNum;

	return MatNum;
}

//�ؽ��� ��Ʈ���� ����
int smMATERIAL_GROUP::CreateTextureMaterial( char *szBitmap , char *szOpacity , int TwoSide ,int Shade , DWORD TexSwap , DWORD BlendType )
{
	int MatNum;


	MatNum = MaterialCount;
	MaterialCount++;

	smMaterial[MatNum].InUse  = TRUE;
	smMaterial[MatNum].Shade  = Shade;
	smMaterial[MatNum].TwoSide = TwoSide;

	if ( szOpacity ) 
		smMaterial[MatNum].smTexture[0] = smTexture.Add( szBitmap , szOpacity );
	else 
		smMaterial[MatNum].smTexture[0] = smTexture.Add( szBitmap );


	smMaterial[MatNum].ReformTexture = 0;

	smMaterial[MatNum].TextureStageState[0] = 0;
	smMaterial[MatNum].TextureFormState[0] = 0;

	smMaterial[MatNum].smTexture[0]->TexSwapMode = TexSwap;
	smMaterial[MatNum].MapOpacity = FALSE;

	smMaterial[MatNum].TextureCounter = 1;			//�ؽ��ĸ��� ��
	smMaterial[MatNum].Transparency   = 0;			//������
//	smMaterial[MatNum].Diffuse        = 0;			//�⺻����

	smMaterial[MatNum].UseState			= 0;
	smMaterial[MatNum].TextureType		= SMTEX_TYPE_MULTIMIX;
	smMaterial[MatNum].BlendType		= BlendType;


	smMaterial[MatNum].InUse++;

	return MatNum;
}

//��Ʈ���� �ؽ��ĸ� �߰��Ѵ�
int	smMATERIAL_GROUP::AddTexture( int MatNum , char *szBitmap , char *szOpacity )
{
	int cnt;

	cnt = smMaterial[MatNum].TextureCounter;			//�ؽ��ĸ��� ��

	if ( szOpacity ) 
		smMaterial[MatNum].smTexture[cnt] = smTexture.Add( szBitmap , szOpacity );
	else 
		smMaterial[MatNum].smTexture[cnt] = smTexture.Add( szBitmap );

	if ( smMaterial[MatNum].smTexture[cnt] )
		smMaterial[MatNum].TextureCounter++;

	return TRUE;
}

//�ؽ��� �̸����� ���� ��Ʈ������ ã�´�
smMATERIAL *smMATERIAL_GROUP::FindNextMaterialFromTextureName()
{
	DWORD cnt,cnt2;

	char *szName;

	szName = szLastSearchName;


	//�� ��Ʈ���� ã��
	for( cnt=LastSearchMaterial;cnt<MaterialCount;cnt++) {
		if ( smMaterial[cnt].InUse ) {

			for(cnt2=0;cnt2<smMaterial[cnt].TextureCounter;cnt2++) {
				if ( lstrcmpi( smMaterial[cnt].smTexture[cnt2]->Name , szName )==0 ) {
					return	&smMaterial[cnt];
				}
			}

			for(cnt2=0;cnt2<smMaterial[cnt].AnimTexCounter;cnt2++) {
				if ( lstrcmpi( smMaterial[cnt].smAnimTexture[cnt2]->Name , szName )==0 ) {
					return	&smMaterial[cnt];
				}
			}

		}
	}

	return NULL;
}

//�ؽ��� �̸����� ��Ʈ������ ã�´�
smMATERIAL *smMATERIAL_GROUP::FindMaterialFromTextureName( char *szName )
{
	LastSearchMaterial = 0;

	lstrcpy( szLastSearchName, szName );

	return FindNextMaterialFromTextureName();
}

//��Ʈ������ ���ϸ��̼� �������� ����
int smMATERIAL_GROUP::SetMaterialAnimFrame( smMATERIAL *lpMaterial , int frame )
{
	int OldFrame;

	OldFrame = lpMaterial->AnimationFrame;
	lpMaterial->AnimationFrame = frame;

	return OldFrame;
}



//��Ʈ������ ���ϸ��̼� �����ϰ� ����
int smMATERIAL_GROUP::ChangeMaterialToAnimation( smMATERIAL *lpMaterial , char **szBitmap , int NumTex , DWORD BlendType , int AutoAnimMode )
{
	int cnt;

	for( cnt=0;cnt<NumTex;cnt++) {
		lpMaterial->smAnimTexture[cnt] = smTexture.Add( szBitmap[cnt] );
		lpMaterial->smAnimTexture[cnt]->TexSwapMode = FALSE;
	}


	lpMaterial->MapOpacity = FALSE;
	lpMaterial->TextureCounter = 1;//NumTex;		//�ؽ��ĸ��� ��
	lpMaterial->Transparency   = 0;			//������

	lpMaterial->AnimTexCounter	= NumTex;		//���ϸ��̼� �ؽ��� ī����
	lpMaterial->FrameMask		= NumTex -1;	//���ϸ��̼� ������ ����ũ
	lpMaterial->Shift_FrameSpeed = 6;			//���ϸ��̼� Ÿ�̸� ����Ʈ

	lpMaterial->UseState			= 0;
	lpMaterial->TextureType		= SMTEX_TYPE_ANIMATION;
	lpMaterial->BlendType		= BlendType;

	//���ϸ��̼� �ڵ�
	if ( AutoAnimMode )	
		lpMaterial->AnimationFrame	= SMTEX_AUTOANIMATION;
	else
		lpMaterial->AnimationFrame	= 0;

	lpMaterial->InUse++;

	return TRUE;
}


//�ִϸ��̼� ��Ʈ���� ����
int smMATERIAL_GROUP::CreateAnimationMaterial( char **szBitmap , int NumTex , DWORD BlendType , int AutoAnimMode )
{
	int cnt;

	smMATERIAL *lpMaterial;

	cnt = MaterialCount;
	MaterialCount++;

	lpMaterial = &smMaterial[cnt];

	lpMaterial->InUse  = TRUE;
	lpMaterial->Shade  = FALSE;
	lpMaterial->TwoSide = TRUE;

	ChangeMaterialToAnimation( lpMaterial , szBitmap , NumTex , BlendType , AutoAnimMode );

	return cnt;
}



//�ؽ��� ���ſ� ������
int smMATERIAL_GROUP::IncTextureFrame()
{
	return TRUE;
}



//��Ʈ������ �ؽ��� �����ΰ��� ������ �����Ѵ� ( �ε� �Ϸ��� ���� )
int smMATERIAL_GROUP::CheckMatreialTextureSwap()
{
	//######################################################################################
	//�� �� �� : �� �� ��
    return TRUE;
	//######################################################################################

	DWORD cnt , cnt2;

	//�� ��Ʈ���� ã��
	for( cnt=0;cnt<MaterialCount;cnt++) 
		if ( smMaterial[cnt].InUse ) {
			if ( smMaterial[cnt].TextureType==SMTEX_TYPE_MULTIMIX ) {
				for( cnt2=0; cnt2<smMaterial[cnt].TextureCounter; cnt2++ ) {
					if ( smMaterial[cnt].smTexture[cnt2] && smMaterial[cnt].smTexture[cnt2]->lpDDSSysMemory ) {
						smMaterial[cnt].TextureSwap = TRUE;
						break;
					}
				}
			}

			if ( smMaterial[cnt].TextureType==SMTEX_TYPE_ANIMATION ) {
				for( cnt2=0; cnt2<smMaterial[cnt].AnimTexCounter; cnt2++ ) {
					if ( smMaterial[cnt].smAnimTexture[cnt2] && smMaterial[cnt].smAnimTexture[cnt2]->lpDDSSysMemory ) {
						smMaterial[cnt].TextureSwap = TRUE;
						break;
					}
				}
			}

		}

	return TRUE;
}


//��Ʈ������ ������ �ؽ��ĸ� ã�� �����Ѵ�
int smMATERIAL_GROUP::ReSwapMaterial( smMATERIAL *lpMaterial )
{
	//######################################################################################
	//�� �� �� : �� �� ��
    return TRUE;
	//######################################################################################

	DWORD cnt;
	int result;

	lpMaterial->MatFrame = MaterialFrame;

	lpMaterial->TextureClip = FALSE;

	if ( lpMaterial->TextureSwap ) {
		result = 0;
		for( cnt=0;cnt<lpMaterial->TextureCounter;cnt++) {
			result |= smTexture.SetLargeTexture( lpMaterial->smTexture[cnt] );
		}

		if ( result ) {
			lpMaterial->TextureClip = TRUE;
			return TRUE;
		}
	}

	return FALSE;
}

//######################################################################################
//�� �� �� : �� �� ��
//�ش� ��Ʈ������ ��� �ؽ��ĸ� �ε�
int smMATERIAL_GROUP::ReadTextures( int MipMap )
//######################################################################################
{
	//######################################################################################
	//�� �� �� : �� �� ��
	if( g_IsReadTextures == 0 )
		return 0;
	//######################################################################################

	DWORD cnt;
	DWORD tcnt;
	int	Result;
	int	ReadCount;
	smTEXTUREHANDLE	*lpTexture;

	//�ؽ��� ���� ũ��ƼĮ ���� ����
	smEnterTextureCriticalSection();

	ReadCount = 0;

	for( cnt=0;cnt<MaterialCount;cnt++ ) {
		if ( smMaterial[cnt].InUse ) {
			for( tcnt=0; tcnt<smMaterial[cnt].TextureCounter; tcnt++ ) {
				if ( smMaterial[cnt].smTexture[tcnt] ) {
					lpTexture = smMaterial[cnt].smTexture[tcnt];

					if ( lpTexture->UseCounter && !lpTexture->lpD3DTexture )
					{
						//######################################################################################
						//�� �� �� : �� �� ��
						//Result = smCreateTexture( lpTexture, MipMap );
						Result = new_smCreateTexture( lpTexture, MipMap );
						//######################################################################################

						ReadCount++;
					}
				}
			}

			for( tcnt=0; tcnt<smMaterial[cnt].AnimTexCounter; tcnt++ ) {
				if ( smMaterial[cnt].smAnimTexture[tcnt] ) {
					lpTexture = smMaterial[cnt].smAnimTexture[tcnt];
					if ( lpTexture->UseCounter && !lpTexture->lpD3DTexture )
					{
						//######################################################################################
						//�� �� �� : �� �� ��
						//Result = smCreateTexture( lpTexture, MipMap );
						Result = new_smCreateTexture( lpTexture, MipMap );
						//######################################################################################

						ReadCount++;
					}
				}
			}
		}
	}

	//�ؽ��� ���� ũ��ƼĮ ���� ����
	smLeaveTextureCriticalSection();

	return ReadCount;
}































////////////////////////////////////////////////////////////////////////////////////////////////


//smMATERIAL smMaterial[ MATRIAL_MAX ];
smMATERIAL *smMaterial;

smMATERIAL_GROUP	*smMaterialGroup;

// ��Ʈ���� �ʱ�ȭ
int InitMaterial()
{
//	smMaterialGroup.Init( MATRIAL_MAX );
	smMaterialGroup = new smMATERIAL_GROUP( MATRIAL_MAX );
	smMaterial = smMaterialGroup->smMaterial;

	MaterialFrame = 0;

	return TRUE;
}

//��Ʈ���� ����
int CloseMaterial()
{
//	smMaterialGroup.Close();
	delete smMaterialGroup;
	return TRUE;
}

//������ �ʴ� ��Ʈ���� ����
int DeleteUnuseMaterial()
{
	return smMaterialGroup->DeleteUnuseMaterial();
}

//��Ʈ������ ���
int AddMaterial( ASE_MATERIAL *aseMaterial )
{
	return smMaterialGroup->AddMaterial( aseMaterial );
}

//��Ʈ���� �ؽ��ĸ� �߰��Ѵ�
int	AddTexture( int MatNum , char *szBitmap , char *szOpacity )
{
	return smMaterialGroup->AddTexture( MatNum , szBitmap , szOpacity );
}

//�ؽ��� �̸����� ���� ��Ʈ������ ã�´�
smMATERIAL *FindNextMaterialFromTextureName()
{
	return smMaterialGroup->FindNextMaterialFromTextureName();
}

//�ؽ��� �̸����� ��Ʈ������ ã�´�
smMATERIAL *FindMaterialFromTextureName( char *szName )
{
	return smMaterialGroup->FindMaterialFromTextureName( szName );
}

//��Ʈ������ ���ϸ��̼� �������� ����
int SetMaterialAnimFrame( smMATERIAL *lpMaterial , int frame )
{
	return smMaterialGroup->SetMaterialAnimFrame( lpMaterial , frame );
}


//��Ʈ������ ���ϸ��̼� �����ϰ� ����
int ChangeMaterialToAnimation( smMATERIAL *lpMaterial , char **szBitmap , int NumTex , DWORD BlendType , int AutoAnimMode )
{
	return smMaterialGroup->ChangeMaterialToAnimation( lpMaterial, szBitmap, NumTex, BlendType, AutoAnimMode );
}


//�ִϸ��̼� ��Ʈ���� ����
int CreateAnimationMaterial( char **szBitmap , int NumTex , DWORD BlendType , int AutoAnimMode )
{
	return smMaterialGroup->CreateAnimationMaterial( szBitmap, NumTex, BlendType, AutoAnimMode );
}


//�ؽ��� ���ſ� ������
int IncTextureFrame()
{
	MaterialFrame++;
	return smTexture.SwapCount ++;
}

//��Ʈ������ �ؽ��� �����ΰ��� ������ �����Ѵ� ( �ε� �Ϸ��� ���� )
int CheckMatreialTextureSwap()
{
	return smMaterialGroup->CheckMatreialTextureSwap();
}


//��Ʈ������ ������ �ؽ��ĸ� ã�� �����Ѵ�
int ReSwapMaterial( smMATERIAL *lpMaterial )
{
	return smMaterialGroup->ReSwapMaterial( lpMaterial );
}




int InitTexture()
{
	return TRUE;
}

int CloseTexture()
{
	smTexture.Remove();

	return TRUE;
}

int ReadTextures()
{
	//######################################################################################
	//�� �� �� : �� �� ��
	if( g_IsReadTextures == 0 )
		return 0;
	//######################################################################################

	int val;

	val = smTexture.ReadTexture();
	CheckMatreialTextureSwap();

	return val;
}

//�ؽ��ĸ� ýũ�Ͽ� �Ҿ���� �ؽ��ĸ� �ٽ� �����
int RestoreTextures()
{
	return smTexture.Restore();
}

/*
int LoadDibTextureNum( char *Filename )
{

	if ( smTexture.AddName( Filename ) )
		return smTexture.TextureCnt;
	else 
		return -1;
}
*/





void* *GetLastTextureSurface()
{
	return smTexture.lpLastTextureSurface;
}



//�ؽ��� ���� ũ��ƼĮ ���� ����
void smEnterTextureCriticalSection()
{
	EnterCriticalSection( &smTexture.cTextureSection );
}

//�ؽ��� ���� ũ��ƼĮ ���� ����
void smLeaveTextureCriticalSection()
{
	LeaveCriticalSection( &smTexture.cTextureSection );
}

int hresult;


////////////////// BMP FILE READ ///////////////////
DWORD GetDibInfoHeaderSize(BYTE  *lpDib)
{
	return ((BITMAPINFOHEADER  *)lpDib)->biSize;
}
WORD GetDibWidth(BYTE  *lpDib)
{
	if (GetDibInfoHeaderSize(lpDib)+sizeof(BITMAPCOREHEADER))
		return (WORD) (((BITMAPCOREHEADER  *)lpDib)->bcWidth);
	else
		return (WORD) (((BITMAPINFOHEADER  *)lpDib)->biWidth);
}
WORD GetDibHeight (BYTE  *lpDib)
{
	if (GetDibInfoHeaderSize(lpDib)==sizeof(BITMAPCOREHEADER))
		return (WORD) (((BITMAPCOREHEADER  *) lpDib)->bcHeight);
	else
		return (WORD) (((BITMAPINFOHEADER  *) lpDib)->biHeight);
}

WORD GetDibBitCount(BYTE  *lpDib)
{
	return ((BITMAPINFOHEADER  *)lpDib)->biBitCount;
}

BYTE  *GetDibBitsAddr(BYTE  *lpDib)
{
	DWORD dwNumColors, dwColorTableSize;
	WORD  wBitCount;

	if (GetDibInfoHeaderSize(lpDib)==sizeof(BITMAPCOREHEADER))
	{
		wBitCount=((BITMAPCOREHEADER  *) lpDib)->bcBitCount;
		if(wBitCount!=24)
			dwNumColors=1L<<wBitCount;
		else dwNumColors=0;
		dwColorTableSize=dwNumColors*sizeof(RGBTRIPLE);
	}
	else
	{
		wBitCount=((BITMAPINFOHEADER  *)lpDib)->biBitCount;
		if(GetDibInfoHeaderSize(lpDib)>=36)
			dwNumColors=((BITMAPINFOHEADER  *)lpDib)->biClrUsed;
		else
			dwNumColors=0;
		if(dwNumColors==0)
		{
			if(wBitCount!=24)
				dwNumColors=1L<<wBitCount;
			else
				dwNumColors=0;
		}
		dwColorTableSize=dwNumColors*sizeof(RGBQUAD);
	}
	return lpDib+GetDibInfoHeaderSize(lpDib)+dwColorTableSize;
}



/////////////////////////[ BMP ���� �ε� ]///////////////////////////////
BYTE *LoadDib( char *Filename )
{
	BITMAPFILEHEADER	bmfh;
	BYTE 				*lpDib;
	DWORD				dwDibSize,dwHeaderSize;
	HANDLE	hFile;
	DWORD	dwAcess;


	//������ ����
	hFile = CreateFile( Filename , GENERIC_READ , FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , NULL );
	if ( hFile == INVALID_HANDLE_VALUE ) return NULL;
	//��Ʈ�� ��� ����
	ReadFile( hFile , &bmfh , sizeof( BITMAPFILEHEADER ) , &dwAcess , NULL );
	if (bmfh.bfType != *(WORD *)"BM" && bmfh.bfType != *(WORD *)"C8" && bmfh.bfType != *(WORD *)"A8" ) 
	{ CloseHandle( hFile ); return NULL; }

	//��� ��ȣȭ ����
	if ( bmfh.bfType == *(WORD *)"A8" ) {
		BYTE	ch;
		BYTE	*lpHeader;
		int		cnt;

		//����� ��ȣȭ
		lpHeader = (BYTE *)&bmfh;
		for( cnt=0;cnt<sizeof(bmfh);cnt++) {
			ch = (BYTE)( lpHeader[cnt]-(cnt*cnt) );
			lpHeader[cnt] = ch;
		}
	}

	dwDibSize=bmfh.bfSize - sizeof(BITMAPFILEHEADER);
	lpDib = new BYTE [dwDibSize];
	if(lpDib==NULL)	{ CloseHandle( hFile );	return NULL; }
	//��Ʈ�� ����
	ReadFile( hFile , lpDib , dwDibSize , &dwAcess , NULL );
	CloseHandle( hFile );
	dwHeaderSize=GetDibInfoHeaderSize(lpDib);
	if (dwHeaderSize<12||(dwHeaderSize>12 && dwHeaderSize < 16) ) 
	{	delete lpDib; return NULL; }

	return lpDib;
}

//////////////////// TGA ���� �о���̴� ũ���� //////////////////
class cTGA	{
public:
	BYTE	*m_pBuff;
	BYTE	*m_pData;
	int		Width , Height;
	int		SwapHeight;
	int		BitCount;

	cTGA();
	~cTGA();

	int LoadTga( char *Filename );
	int GetWidth();
	int GetHeight();
	int GetBitCount();

};

cTGA::cTGA()
{
	m_pBuff = 0;
	m_pData = 0;
	Width = 0;
	Height = 0;
	BitCount = 0;
}

cTGA::~cTGA()
{
	if ( m_pBuff ) delete m_pData;
}

// TGA���� �ε�
int cTGA::LoadTga( char *Filename )
{
	int len;
	BYTE TGAHeader[0x12];
	WORD *Bit16Buff;
	WORD r,g,b;

	int DestCnt;
	int SrcCnt;

	HANDLE	hFile;
	DWORD	dwAcess;

	//������ ����
	hFile = CreateFile( Filename , GENERIC_READ , FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , NULL );
	if ( hFile == INVALID_HANDLE_VALUE ) return FALSE;

	//TGA ��� ����
	ReadFile( hFile , TGAHeader , 0x12 , &dwAcess , NULL );

	//��� ��ȣȭ ����
	if ( TGAHeader[0]=='G' && TGAHeader[1]=='8' ) {
		BYTE	ch;
		BYTE	*lpHeader;
		int		cnt;

		//����� ��ȣȭ
		lpHeader = (BYTE *)&TGAHeader;
		for( cnt=0;cnt<sizeof(TGAHeader);cnt++) {
			ch = (BYTE)( lpHeader[cnt]-(cnt*cnt) );
			lpHeader[cnt] = ch;
		}
	}

	Width = *((WORD *)(&TGAHeader[0xC]));
	Height = *((WORD *)(&TGAHeader[0xE]));

	if ( (TGAHeader[0x11]&0x20) ) {
		SwapHeight = FALSE;
	}
	else
		SwapHeight = TRUE;

	switch( TGAHeader[0x10] ) {
	case 16:		//555 �� RGB 888 �� ��ȯ
		m_pBuff = new BYTE [Width*Height*3];
		len = Width*Height;
		Bit16Buff = new WORD [ len ];
		ReadFile( hFile , Bit16Buff , len*2 , &dwAcess , NULL );
		//fread( Bit16Buff , len*2 , 1, fp );
		DestCnt = 0;
		for( SrcCnt=0;SrcCnt<len;SrcCnt++ ) {
			r = ( Bit16Buff[SrcCnt]>>10 ) & 0x1F;
			g = ( Bit16Buff[SrcCnt]>>5 ) & 0x1F;
			b = ( Bit16Buff[SrcCnt] ) & 0x1F;

			m_pBuff[ DestCnt   ] = (r<<3) | (r>>2);
			m_pBuff[ DestCnt+1 ] = (g<<3) | (g>>2);
			m_pBuff[ DestCnt+2 ] = (b<<3) | (b>>2);
			DestCnt+=3;
		}
		delete Bit16Buff;
		BitCount = 24;
		break;
	case 24:
		m_pBuff = new BYTE [Width*Height*3];
		ReadFile( hFile , m_pBuff , Width*Height*3 , &dwAcess , NULL );
		//fread( m_pBuff , Width*Height*3 , 1, fp );
		BitCount = 24;
		break;
	case 32:
		m_pBuff = new BYTE [Width*Height*4];
		ReadFile( hFile , m_pBuff , Width*Height*4 , &dwAcess , NULL );
		//fread( m_pBuff , Width*Height*4 , 1, fp );
		BitCount = 32;
		break;
	}
	CloseHandle( hFile );

	m_pData = m_pBuff;

	return TRUE;
}

int cTGA::GetWidth()
{
	return Width;
}

int cTGA::GetHeight()
{
	return Height;
}

int cTGA::GetBitCount()
{
	return BitCount;
}

#define smTEXFILETYPE_BMP		0
#define smTEXFILETYPE_JPG		1
#define smTEXFILETYPE_TGA		2

//������ Ȯ���ڸ� �˻��Ͽ� ���� ������ ã�´�
int GetTextureFileType( char *Filename ) 
{
	int len;
	int cnt;
	char *szFileExt = 0;

	len = lstrlen( Filename );

	for(cnt=len-1;cnt>=0;cnt--) {
		if ( Filename[cnt]=='.' ) {
			szFileExt = Filename+cnt+1;
			break;
		}
	}

	if ( !szFileExt ) 
		return -1;

	if ( ( szFileExt[0]=='j' || szFileExt[0]=='J') && 
		 ( szFileExt[1]=='p' || szFileExt[1]=='P') &&
		 ( szFileExt[2]=='g' || szFileExt[2]=='G') ) 
		 return smTEXFILETYPE_JPG;

	if ( ( szFileExt[0]=='b' || szFileExt[0]=='B') && 
		 ( szFileExt[1]=='m' || szFileExt[1]=='M') &&
		 ( szFileExt[2]=='p' || szFileExt[2]=='P') ) 
		 return smTEXFILETYPE_BMP;

	if ( ( szFileExt[0]=='t' || szFileExt[0]=='T') && 
		 ( szFileExt[1]=='g' || szFileExt[1]=='G') &&
		 ( szFileExt[2]=='a' || szFileExt[2]=='A') ) 
		 return smTEXFILETYPE_TGA;


	if ( ( szFileExt[0]=='s' || szFileExt[0]=='S') && 
		 ( szFileExt[1]=='t' || szFileExt[1]=='T') &&
		 ( szFileExt[2]=='g' || szFileExt[2]=='G') ) 
		 return smTEXFILETYPE_JPG;

	if ( ( szFileExt[0]=='s' || szFileExt[0]=='S') && 
		 ( szFileExt[1]=='t' || szFileExt[1]=='T') &&
		 ( szFileExt[2]=='a' || szFileExt[2]=='A') ) 
		 return smTEXFILETYPE_TGA;

	return -1;
}



int LoadDibSurfaceAlphaMipMap( void* lpDDSurface, char *Filename, char *FileAlpha, int CheckWidth, int CheckHeight )
{
	return TRUE;
}


/////////[ BMP������ �ؽ��� �����̽��� ����� ( ����ä�� ��� ) ] ///////////
void* LoadDibSurfaceAlpha( char *Filename , char *FileAlpha , int SysMem )
{

	return nullptr;

}


//////////////// [ BMP������ �ؽ��� �����̽��� ����� ] ///////////////
void* LoadDibSurface( char *Filename , int SysMem )
{
	return nullptr;
}

// Dib�� �����̽��� �׸���
int DrawSurfaceFromDib(void* lpDDSurface, BYTE* lpDib) { return TRUE; }






int MipMapCreateTextureCheck( int width, int height, int MipMapCount )
{
	if( width > 256 || height > 256 )
		return 0;

	switch( MipMapCount )
	{
	case 5:
		if( width == 256 && height == 256 )
			return 1;
		break;

	case 4:
		if( width >= 128 && height >= 128 )
			return 1;
		break;

	case 3:
		if( width >= 64 && height >= 64 )
			return 1;
		break;

	case 2:
		if( width >= 32 && height >= 32 )
			return 1;
		break;

	case 1:
		return 0;

	default:
		return 0;
	}

	return 0;
}
//######################################################################################





//######################################################################################
//�� �� �� : �� �� ��
//////////////// [ BMP������ �ؽ��� �����̽��� ����� (�ڵ� ����) ] ///////////////
int smCreateTexture(smTEXTUREHANDLE* lpTexHandle, int MipMap) { return TRUE; }












extern HWND hwnd;


void*	lpDDSMapTexture[256];
void*	lpDDSMapTextureVideo[8*8];
void*	lpD3DMapTexture[8*8];

int MapTexCode[8][8];

int MapTextureSize;

int LoadDibMapTexture( char *Filename, int tSize ) { return TRUE; }

int RemoveMapTexture() { return TRUE; }



int SetMapTextureMem( int x, int y ) { return TRUE; }

int SetMapTextureWidth( int x, int y )
{
	int cnt;

	for( cnt=0;cnt<8;cnt++ ) {
		SetMapTextureMem( x+cnt, y );
	}

	return TRUE;
}

int SetMapTextureHeight( int x, int y )
{
	int cnt;

	for( cnt=0;cnt<8;cnt++ ) {
		SetMapTextureMem( x, y+cnt );
	}


	return TRUE;
}

int SetMapImage( int x , int y )
{
	int sx,sy;
	int cntX,cntY;

	sx = x>>(ShiftMAPCELL_DIV+3);
	sy = y>>(ShiftMAPCELL_DIV+3);


	for( cntX=sx-3;cntX<sx+4;cntX++) {
		for( cntY=sy-3;cntY<sy+4;cntY++) {
			SetMapTextureMem( cntX, cntY );
		}
	}


/*
	SetMapTextureWidth( sx-3 , sy+3 );
	SetMapTextureWidth( sx-3 , sy-3 );

	SetMapTextureWidth( sx+3 , sy-3 );
	SetMapTextureWidth( sx-3 , sy-3 );
*/
	return TRUE;

}








void* LoadDibBGTexture(char* Filename) { return nullptr; }



void*	lpDDSAnimBG[32];

int DrawAnimBG(void* lpDDSSrc, int frame) { return TRUE; }

int LoadAnimBG() { return TRUE; }

int ClearBG( void* lpDDSSrc, DWORD color ) { return TRUE; }

int CloseAnimBG() { return TRUE; }


//######################################################################################
//�� �� �� : �� �� ��
int new_smCreateTexture( smTEXTUREHANDLE *lpTexHandle, int MipMap ) { return TRUE; }


/////////////////////////////////////////////////////////////////////////////////////////
//
int new_LoadDib( char *Filename )
{
	HANDLE				hFile;
	DWORD				dwAcess;
	BITMAPFILEHEADER	bmfh;

	//������ ����
	hFile = CreateFile( Filename , GENERIC_READ , FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , NULL );
	if( hFile == INVALID_HANDLE_VALUE )
		return NULL;

	//��Ʈ�� ��� ����
	ReadFile( hFile , &bmfh , sizeof( BITMAPFILEHEADER ) , &dwAcess , NULL );
	if( bmfh.bfType != *(WORD *)"BM" && bmfh.bfType != *(WORD *)"C8" && bmfh.bfType != *(WORD *)"A8" ) 
	{
		CloseHandle( hFile );
		return NULL;
	}

	//��� ��ȣȭ ����
	if( bmfh.bfType == *(WORD *)"A8" )
	{
		BYTE	ch;
		BYTE	*lpHeader;
		int		cnt;

		//����� ��ȣȭ
		lpHeader = (BYTE *)&bmfh;
		for( cnt=0;cnt<sizeof(bmfh);cnt++)
		{
			ch = (BYTE)( lpHeader[cnt]-(cnt*cnt) );
			lpHeader[cnt] = ch;
		}
	}

	DWORD dwDibSize = bmfh.bfSize - sizeof(BITMAPFILEHEADER);
	BYTE *lpDib     = g_DibImageDateBuff;
	
	//��Ʈ�� ����
	ReadFile( hFile , lpDib , dwDibSize , &dwAcess , NULL );
	CloseHandle( hFile );

	DWORD dwHeaderSize = GetDibInfoHeaderSize(lpDib);
	if( dwHeaderSize < 12 || (dwHeaderSize>12 && dwHeaderSize < 16) ) 
		return NULL;

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////
//
int new_LoadTga( char *Filename )
{
    BYTE	TGAHeader[0x12];
	HANDLE	hFile;
	DWORD	dwAcess;

	//������ ����
	hFile = CreateFile( Filename , GENERIC_READ , FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , NULL );
	if( hFile == INVALID_HANDLE_VALUE )
		return NULL;

	//TGA ��� ����
	ReadFile( hFile , TGAHeader , 0x12 , &dwAcess , NULL );

	//��� ��ȣȭ ����
	if ( TGAHeader[0]=='G' && TGAHeader[1]=='8' ) {
		BYTE	ch;
		BYTE	*lpHeader;
		int		cnt;

		//����� ��ȣȭ
		lpHeader = (BYTE *)&TGAHeader;
		for( cnt=0;cnt<sizeof(TGAHeader);cnt++) {
			ch = (BYTE)( lpHeader[cnt]-(cnt*cnt) );
			lpHeader[cnt] = ch;
		}
	}

	g_DibLastReadWidth  = *((WORD *)(&TGAHeader[0xC]));
	g_DibLastReadHeight = *((WORD *)(&TGAHeader[0xE]));

	if ( (TGAHeader[0x11]&0x20) )
		g_TgaLastSwapHeight = FALSE;
	else
		g_TgaLastSwapHeight = TRUE;

	switch( TGAHeader[0x10] )
	{
	//case 16:
	case 24:
		g_TgaLastBitCnt = 24;
		ReadFile( hFile, g_DibImageDateBuff, g_DibLastReadWidth*g_DibLastReadHeight*3, &dwAcess, NULL );
		break;

	case 32:
		g_TgaLastBitCnt = 32;
		ReadFile( hFile, g_DibImageDateBuff, g_DibLastReadWidth*g_DibLastReadHeight*4, &dwAcess, NULL );
		break;

	default:
		CloseHandle( hFile );
		return NULL;
	}

	CloseHandle( hFile );
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////
//
int New_DrawSurfaceFromTga( void* lpDDSurface ) { return TRUE; }


/////////////////////////////////////////////////////////////////////////////////////////
//
void* new_LoadBmpCreateTexSurface( char *Filename, int MipMap, int &rTexHalf ) { return nullptr; }


/////////////////////////////////////////////////////////////////////////////////////////
//
void* new_LoadTgaCreateTexSurface( char *Filename, int MipMap, int &rTexHalf ) { return nullptr; }


/////////////////////////////////////////////////////////////////////////////////////////
//
void* new_LoadBmpSurfaceOffscreen( char *Filename ) { return nullptr; }
//######################################################################################


