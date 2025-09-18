#define _SINBARAM
#include <fstream>
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <ZMOUSE.H>
#include <process.h>
#include "Database/SQLConnection.h"
#include "GM\\GM.h"
#include "WinDump.h"
#include "fileread.h"
#include "smLib3d/smSin.h"
#include "AreaServer.h"
#include "..//Database.h"
#define WM_CALLMEMMAP				WM_USER+3 


HWND hwnd;

int quit = 0;
int QuitSave = 0;
extern int TJwheel;
int angX = 0;
int angY = 0;
int	LastAttackDamage = 0;

int pX;
int pY;
int pZ;
int	dpX=0;
int dpY=0;
int dpZ=0;

int whAnx = 64;
int anx = 64;
int	ViewAnx = 64;
int	ViewDist = 100;
int	PlayFloor = 0;
int any = 0;
int anz = 0;
int dist = 100;
int tX = 0;
int tY = 0;
int tZ = 0;
int GameMode = 0;
BYTE VRKeyBuff[256];
HFONT	hFont = 0;
CRITICAL_SECTION	cSection;
HIMC hImc;
HIMC hImcEdit;

extern rsRECORD_DBASE	rsRecorder;
extern int ServerWinMain();

BOOL HookAPI(char* moduleName, char* apiName, void* callBack, void* backup = NULL)
{
	DWORD old = 0;

	void* pAPIHandle = GetProcAddress(GetModuleHandleA(moduleName), apiName);

	if (pAPIHandle == NULL)
		return FALSE;

	if (backup != NULL)
		MoveMemory(backup, pAPIHandle, 5);

	VirtualProtect(pAPIHandle, 5, PAGE_EXECUTE_READWRITE, &old);
	*(BYTE*)((DWORD)pAPIHandle) = 0xE9;
	*(DWORD*)((DWORD)pAPIHandle + 1) = (DWORD)callBack - (DWORD)pAPIHandle - 5;
	VirtualProtect(pAPIHandle, 5, old, &old);

	return TRUE;
}

LONG WINAPI RedirectedSetUnhandledExceptionFilter(EXCEPTION_POINTERS* p)
{
	return NULL;
}

extern std::vector<std::shared_ptr<Database>> vSQLConnection;

void CreateSQLConnection(EDatabaseIDX eDatabaseIDx)
{
	std::shared_ptr<Database> pcSQL = std::make_shared<Database>();

	if (pcSQL->Init(eDatabaseIDx))
	{
		vSQLConnection.push_back(pcSQL);
	}
	else
	{
		cerr << "Falha ao conectar-se ao banco de dados! Log: SQL.txt" << endl;
		Sleep(5000);
		exit(0);
	}
}

// Entry Point
int main(int argv, char* argc[])
{
	SetUnhandledExceptionFilter(unhandled_handler);
	HookAPI("kernel32.dll", "SetUnhandledExceptionFilter", RedirectedSetUnhandledExceptionFilter);

	SetConsoleTitle("Server");
	smConfigDecode("Server\\Config\\Devices.ini");

	initSinCos();
	srand(GetCurrentTime());


	initializeSQL();
	
	cout << "Conectando-se ao Banco de Dados: ServerDB" << endl;
	CreateSQLConnection(DATABASEID_ServerDBX);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: CoinShopDB" << endl;
	CreateSQLConnection(DATABASEID_CoinShopDBX);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: CoinShopDB" << endl;
	CreateSQLConnection(DATABASEID_ShopCoinX);
	cout << "Conectado com sucesso" << endl;

	cout << "Conectando-se ao Banco de Dados: BattleEvents" << endl;
	CreateSQLConnection(DATABASEID_BattleEvents);
	cout << "Conectado com sucesso" << endl;

	InitializeCriticalSection(&cSection);
	InitializeCriticalSection(&cSection_Main);



	return ServerWinMain();
}
