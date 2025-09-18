#include "sinbaram/sinLinkHeader.h"
#include "cSkinChanger.h"
#include "field.h"
#include "SrcServer/onserver.h"

extern int SendQuickMessage2(rsPLAYINFO* lpPlayInfo, char* szMessage);
extern int	rsDeleteInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);
extern int srSetItemFromCode(psITEM* lpsItem, char* szCoed);
extern int	rsRegist_ItemSecCode(rsPLAYINFO* lpPlayInfo, TRANS_ITEMINFO* lpTransItemInfo, int NewItem);
int	rsSaveAgingItemToHDD(sITEMINFO* lpItem);
extern sDEF_ITEMINFO* DefaultItems;
extern int DefaultItemCount;

cSKINCHANGER cSkinChanger;


void cSKINCHANGER::RecvSkinChange(SKINCHANGE_INFO* psPacket, rsPLAYINFO* lpPlayInfo)
{
	TRANS_ITEMINFO	TransItemInfo;



	TransItemInfo.code = smTRANSCODE_PUTITEM;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);

	memcpy(&TransItemInfo.Item, &psPacket->scItem.sItemInfo, sizeof(sITEMINFO));
	TransItemInfo.Item.CODE = psPacket->newCode;




	ReformItem(&TransItemInfo.Item);

	rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
	rsSaveAgingItemToHDD(&TransItemInfo.Item);
	lpPlayInfo->lpsmSock->Send((char*)&TransItemInfo, TransItemInfo.size,TRUE);
}


bool cSKINCHANGER::OpenSkinChange(rsPLAYINFO* lpPlayInfo)
{
	smTRANS_COMMAND sPacket;
	sPacket.code = smTRANSCODE_OPEN_SKINCHANGE;
	sPacket.size = sizeof(smTRANS_COMMAND);
	lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size,TRUE);

	return true;
}
