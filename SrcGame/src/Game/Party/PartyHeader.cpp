#include "PartyHeader.h"

char* GetPartyMode(EPartyMode eMode)
{
	char* pszRet = "Modo Normal";

	if ( eMode == PARTYMODE_EXP )
		pszRet = "Modo Experi�ncia";
	else if( eMode == PARTYMODE_Normal)
		pszRet = "Modo Normal";
	else if (eMode == PARTYMODE_Hunt)
		pszRet = "Modo Ca�a";

	return pszRet;
}