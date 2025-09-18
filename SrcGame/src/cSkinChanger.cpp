#include "sinbaram/sinLinkHeader.h"
#include "cSkinChanger.h"


bool isMousePos(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return true;

	return false;
}

cSKINCHANGER cSkinChanger;

map<DWORD, DWORD> vSkinCodes = {
	//SKINS ITENS PRIMEIRA LINHA
	{ sinSC1 | sin01, sinWA1 | sin40 },
	{ sinSC1 | sin02, sinWA1 | sin05 },
	{ sinSC1 | sin03, sinWC1 | sin40 },
	{ sinSC1 | sin04, sinWH1 | sin40 },
	{ sinSC1 | sin05, sinWM1 | sin40 },
	{ sinSC1 | sin06, sinWP1 | sin40 },
	{ sinSC1 | sin07, sinWS1 | sin40 },
	{ sinSC1 | sin08, sinWS2 | sin40 },

	{ sinSC1 | sin10, sinWT1 | sin40 },


	//SKINS ITENS SEGUNDA LINHA
	{ sinSC1 | sin12, sinWA1 | sin41 },
	{ sinSC1 | sin14, sinWC1 | sin41 },
	{ sinSC1 | sin15, sinWH1 | sin41 },
	{ sinSC1 | sin17, sinWP1 | sin41 },
	{ sinSC1 | sin18, sinWS1 | sin41 },
	{ sinSC1 | sin19, sinWS2 | sin41 },
	{ sinSC1 | sin21, sinWT1 | sin41 },
	{ sinSC1 | sin22, sinDS1 | sin17 },
	{ sinSC1 | sin16, sinWM1 | sin41 },


	//SKINS ITENS TERCEIRA LINHA
	{ sinSC1 | sin23, sinWA1 | sin42 },
	{ sinSC1 | sin24, sinWC1 | sin42 },
	{ sinSC1 | sin25, sinWH1 | sin42 },
	{ sinSC1 | sin26, sinWP1 | sin42 },
	{ sinSC1 | sin27, sinWS1 | sin42 },
	{ sinSC1 | sin28, sinWS2 | sin42 },
	{ sinSC1 | sin29, sinWT1 | sin42 },
	{ sinSC1 | sin30, sinWM1 | sin42 },

	//SKINS ITENS QUARTA LINHA
	{ sinSC1 | sin32, sinWA1 | sin43 },
	{ sinSC1 | sin33, sinWC1 | sin43 },
	{ sinSC1 | sin34, sinWH1 | sin43 },
	{ sinSC1 | sin35, sinWP1 | sin43 },
	{ sinSC1 | sin36, sinWS1 | sin43 },
	{ sinSC1 | sin37, sinWS2 | sin43 },
	{ sinSC1 | sin38, sinWT1 | sin43 },
	{ sinSC1 | sin39, sinWM1 | sin43 },
	
	//SKINS ITENS VIRTUS
	{ sinSC1 | sin41, sinWA1 | sin44 },
	{ sinSC1 | sin42, sinWC1 | sin26 },
	{ sinSC1 | sin43, sinWM1 | sin25 },
	{ sinSC1 | sin44, sinWP1 | sin44 },
	{ sinSC1 | sin45, sinWS1 | sin44 },
	{ sinSC1 | sin46, sinWS2 | sin44 },
	{ sinSC1 | sin47, sinWT1 | sin44 },
	{ sinSC1 | sin48, sinDA1 | sin40 },
	{ sinSC1 | sin49, sinDS1 | sin23 },

	//SKINS UPDATE 05.05.2020
	{ sinSC1 | sin50, sinWA1 | sin45 },
	{ sinSC1 | sin51, sinWA1 | sin46 },
	{ sinSC1 | sin52, sinWC1 | sin41 },
	{ sinSC1 | sin53, sinWC1 | sin42 },
	{ sinSC1 | sin54, sinWH1 | sin44 },
	{ sinSC1 | sin55, sinWH1 | sin43 },
	{ sinSC1 | sin56, sinWM1 | sin42 },
	{ sinSC1 | sin57, sinWM1 | sin43 },
	{ sinSC1 | sin58, sinWP1 | sin45 },
	//{ sinSC1 | sin59, sinWP1 | sin42 },
	{ sinSC1 | sin60, sinWS1 | sin45 },
	{ sinSC1 | sin61, sinWS1 | sin42 },
	{ sinSC1 | sin62, sinWS2 | sin45 },
	{ sinSC1 | sin63, sinWS2 | sin46 },
	{ sinSC1 | sin64, sinWT1 | sin41 },
	{ sinSC1 | sin65, sinWT1 | sin42 },
	{ sinSC1 | sin66, sinDS1 | sin42 },
	{ sinSC1 | sin67, sinDS1 | sin43 },

	//SKINS UPDATE 11.05.2020
	{ sinSC1 | sin68, sinWA1 | sin44 },
	{ sinSC1 | sin69, sinWA1 | sin45 },
	{ sinSC1 | sin70, sinWC1 | sin43 },
	{ sinSC1 | sin71, sinWC1 | sin44 },
	{ sinSC1 | sin72, sinWH1 | sin44 },
	{ sinSC1 | sin73, sinWM1 | sin44 },
	{ sinSC1 | sin74, sinWM1 | sin45 },
	{ sinSC1 | sin75, sinWP1 | sin43 },
	{ sinSC1 | sin76, sinWP1 | sin44 },
	{ sinSC1 | sin77, sinWS1 | sin43 },
	{ sinSC1 | sin78, sinWS1 | sin44 },
	{ sinSC1 | sin79, sinWS2 | sin44 },
	{ sinSC1 | sin80, sinWS2 | sin45 },
	{ sinSC1 | sin81, sinWT1 | sin43 },
	{ sinSC1 | sin82, sinWT1 | sin44 },
	{ sinSC1 | sin83, sinDS1 | sin44 },
	{ sinSC1 | sin84, sinDA1 | sin41 },
	{ sinSC1 | sin85, sinDA2 | sin40 },
	{ sinSC1 | sin86, sinDS1 | sin01 },
	{ sinSC1 | sin87, sinDA1 | sin31 },
	{ sinSC1 | sin88, sinDA2 | sin41 },

	//SKINS UPDATE 21.05.2020
	{ sinSC2 | sin01, sinWA1 | sin46 },
	{ sinSC2 | sin02, sinWA1 | sin47 },
	{ sinSC2 | sin03, sinWA1 | sin48 },
	{ sinSC2 | sin04, sinWA1 | sin49 },
	{ sinSC2 | sin05, sinWA1 | sin50 },
	{ sinSC2 | sin06, sinWC1 | sin45 },
	{ sinSC2 | sin07, sinWC1 | sin46 },
	{ sinSC2 | sin08, sinWC1 | sin47 },
	{ sinSC2 | sin09, sinWC1 | sin48 },
	{ sinSC2 | sin10, sinWC1 | sin49 },
	{ sinSC2 | sin11, sinWC1 | sin50 },
	{ sinSC2 | sin12, sinWH1 | sin45 },
	{ sinSC2 | sin13, sinWH1 | sin46 },
	{ sinSC2 | sin14, sinWH1 | sin47 },
	{ sinSC2 | sin15, sinWH1 | sin48 },
	{ sinSC2 | sin16, sinWH1 | sin49 },
	{ sinSC2 | sin17, sinWM1 | sin46 },
	{ sinSC2 | sin18, sinWM1 | sin47 },
	{ sinSC2 | sin19, sinWM1 | sin48 },
	{ sinSC2 | sin20, sinWM1 | sin49 },
	{ sinSC2 | sin21, sinWM1 | sin50 },
	{ sinSC2 | sin22, sinWM1 | sin51 },
	{ sinSC2 | sin23, sinWP1 | sin45 },
	{ sinSC2 | sin24, sinWP1 | sin46 },
	{ sinSC2 | sin25, sinWP1 | sin47 },
	{ sinSC2 | sin26, sinWP1 | sin48 },
	{ sinSC2 | sin27, sinWP1 | sin49 },
	{ sinSC2 | sin28, sinWP1 | sin50 },
	{ sinSC2 | sin29, sinWS1 | sin45 },
	{ sinSC2 | sin30, sinWS1 | sin46 },
	{ sinSC2 | sin31, sinWS1 | sin47 },
	{ sinSC2 | sin32, sinWS1 | sin48 },
	{ sinSC2 | sin33, sinWS1 | sin49 },
	{ sinSC2 | sin34, sinWS1 | sin50 },
	{ sinSC2 | sin35, sinWS2 | sin46 },
	{ sinSC2 | sin36, sinWS2 | sin47 },
	{ sinSC2 | sin37, sinWS2 | sin48 },
	{ sinSC2 | sin38, sinWS2 | sin49 },
	{ sinSC2 | sin39, sinWS2 | sin50 },
	{ sinSC2 | sin40, sinWS2 | sin51 },
	{ sinSC2 | sin41, sinWT1 | sin45 },
	{ sinSC2 | sin42, sinWT1 | sin46 },
	{ sinSC2 | sin43, sinWT1 | sin47 },
	{ sinSC2 | sin44, sinWT1 | sin48 },
	{ sinSC2 | sin45, sinWT1 | sin49 },
	{ sinSC2 | sin46, sinWT1 | sin50 },
	{ sinSC2 | sin47, sinDA1 | sin42 },
	{ sinSC2 | sin48, sinDA2 | sin42 },
	{ sinSC2 | sin49, sinDS1 | sin45 },
	{ sinSC2 | sin50, sinDS1 | sin46 },
	{ sinSC2 | sin51, sinDS1 | sin47 },
	{ sinSC2 | sin52, sinDS1 | sin48 },
	{ sinSC2 | sin53, sinDS1 | sin49 },
	{ sinSC2 | sin54, sinDS1 | sin50 },
	{ sinSC2 | sin55, sinDA1 | sin03 },

	// update 01.06.2020
//{ sinSC2 | sin56, sinWA1 | sin51 },
{ sinSC2 | sin57, sinWA1 | sin52 },
{ sinSC2 | sin58, sinWA1 | sin53 },
{ sinSC2 | sin59, sinWA1 | sin54 },
{ sinSC2 | sin60, sinWC1 | sin51 },
{ sinSC2 | sin61, sinWC1 | sin52 },
{ sinSC2 | sin62, sinWH1 | sin50 },
{ sinSC2 | sin63, sinWM1 | sin52 },
{ sinSC2 | sin64, sinWP1 | sin51 },
{ sinSC2 | sin65, sinWP1 | sin52 },
{ sinSC2 | sin66, sinWP1 | sin53 },
{ sinSC2 | sin67, sinWS1 | sin51 },
{ sinSC2 | sin68, sinWS1 | sin52 },
{ sinSC2 | sin69, sinWS2 | sin52 },
{ sinSC2 | sin70, sinWS2 | sin53 },
{ sinSC2 | sin71, sinWS2 | sin54 },
{ sinSC2 | sin72, sinWS2 | sin55 },
{ sinSC2 | sin73, sinWT1 | sin51 },
{ sinSC2 | sin74, sinWT1 | sin52 },
{ sinSC2 | sin75, sinDS1 | sin51 },
{ sinSC2 | sin76, sinDS1 | sin52 },

//update 17.06.2020
{ sinSC2 | sin77, sinWA1 | sin60 },
{ sinSC2 | sin78, sinWA1 | sin61 },
{ sinSC2 | sin79, sinWA1 | sin57 },
{ sinSC2 | sin80, sinWA1 | sin58 },
{ sinSC2 | sin81, sinWC1 | sin58 },
{ sinSC2 | sin82, sinWC1 | sin54 },
{ sinSC2 | sin83, sinWC1 | sin55 },
{ sinSC2 | sin84, sinWH1 | sin51 },
{ sinSC2 | sin85, sinWH1 | sin52 },
{ sinSC2 | sin86, sinWH1 | sin53 },
{ sinSC2 | sin87, sinWH1 | sin54 },
{ sinSC2 | sin88, sinWM1 | sin59 },
{ sinSC2 | sin89, sinWM1 | sin54 },
{ sinSC2 | sin90, sinWM1 | sin55 },
{ sinSC2 | sin91, sinWM1 | sin56 },
{ sinSC2 | sin92, sinWP1 | sin60 },
{ sinSC2 | sin93, sinWP1 | sin55 },
{ sinSC2 | sin94, sinWP1 | sin56 },
{ sinSC2 | sin95, sinWP1 | sin57 },
{ sinSC2 | sin96, sinWS1 | sin59 },
{ sinSC2 | sin97, sinWS1 | sin54 },
{ sinSC2 | sin98, sinWS1 | sin55 },
{ sinSC3 | sin01, sinWS1 | sin56 },
{ sinSC3 | sin02, sinWS2 | sin61 },
{ sinSC3 | sin03, sinWS2 | sin62 },
{ sinSC3 | sin04, sinWS2 | sin58 },
{ sinSC3 | sin05, sinWT1 | sin59 },
{ sinSC3 | sin06, sinWT1 | sin54 },
{ sinSC3 | sin07, sinWT1 | sin55 },
{ sinSC3 | sin08, sinWT1 | sin56 },

//SKINS NOVA
{ sinSC3 | sin09, sinWA1 | sin59 },
{ sinSC3 | sin10, sinWC1 | sin56 },
{ sinSC3 | sin11, sinWH1 | sin55 },
{ sinSC3 | sin12, sinWM1 | sin57 },
{ sinSC3 | sin13, sinWP1 | sin58 },
{ sinSC3 | sin14, sinWS1 | sin57 },
{ sinSC3 | sin15, sinWS2 | sin59 },
{ sinSC3 | sin16, sinWT1 | sin57 },
{ sinSC3 | sin17, sinDS1 | sin54 },


{ sinSC3 | sin18, sinWC1 | sin57 },
{ sinSC3 | sin19, sinWH1 | sin56 },
{ sinSC3 | sin20, sinWM1 | sin58 },
{ sinSC3 | sin21, sinWP1 | sin59 },
{ sinSC3 | sin22, sinWS1 | sin58 },
{ sinSC3 | sin23, sinWS2 | sin60 },
{ sinSC3 | sin24, sinWT1 | sin58 },
{ sinSC3 | sin25, sinDA1 | sin08 },

//29.07

{ sinSC3 | sin26, sinWA1 | sin62 },
{ sinSC3 | sin27, sinWA1 | sin63 },
{ sinSC3 | sin28, sinWC1 | sin59 },
{ sinSC3 | sin29, sinWM1 | sin60 },
{ sinSC3 | sin30, sinWP1 | sin61 },
{ sinSC3 | sin31, sinWS1 | sin60 },
{ sinSC3 | sin32, sinWS2 | sin63 },
{ sinSC3 | sin33, sinWS2 | sin64 },
{ sinSC3 | sin34, sinWT1 | sin60 },
{ sinSC3 | sin35, sinDS1 | sin55 },

//11.08
{ sinSC3 | sin36, sinDA1 | sin14 },
{ sinSC3 | sin37, sinDA2 | sin14 },
{ sinSC3 | sin38, sinWA1 | sin21 },
{ sinSC3 | sin39, sinWC1 | sin21 },
{ sinSC3 | sin40, sinWM1 | sin19 },
{ sinSC3 | sin41, sinWP1 | sin16 },
{ sinSC3 | sin42, sinWS1 | sin21 },
{ sinSC3 | sin43, sinWS2 | sin25 },
{ sinSC3 | sin44, sinWT1 | sin15 },

//21.08
{ sinSC3 | sin45, sinWA1 | sin64 },
{ sinSC3 | sin46, sinWC1 | sin60 },
{ sinSC3 | sin47, sinWM1 | sin61 },
{ sinSC3 | sin48, sinWP1 | sin62 },
{ sinSC3 | sin49, sinWS1 | sin61 },
{ sinSC3 | sin50, sinWS2 | sin65 },
{ sinSC3 | sin51, sinWT1 | sin61 },
{ sinSC3 | sin52, sinDS1 | sin56 },
{ sinSC3 | sin53, sinDA1 | sin43 },
{ sinSC3 | sin54, sinDA2 | sin43 },
{ sinSC3 | sin55, sinDA1 | sin19 },
{ sinSC3 | sin56, sinDA2 | sin19 },
{ sinSC3 | sin57, sinWS2 | sin66 },
{ sinSC3 | sin58, sinWP1 | sin63 },
{ sinSC3 | sin59, sinWS1 | sin62 },
{ sinSC3 | sin60, sinWA1 | sin65 },
{ sinSC3 | sin61, sinWC1 | sin61 },
{ sinSC3 | sin62, sinWM1 | sin62 },
{ sinSC3 | sin63, sinWT1 | sin62 },
{ sinSC3 | sin64, sinDS1 | sin57 },

//ITENS ROXOS IMMORTAL
{ sinSC3 | sin65, sinWA1 | sin66 },
{ sinSC3 | sin66, sinWA1 | sin67 },
{ sinSC3 | sin67, sinWC1 | sin62 },
{ sinSC3 | sin68, sinWM1 | sin63 },
{ sinSC3 | sin69, sinWP1 | sin64 },
{ sinSC3 | sin70, sinWS1 | sin63 },
{ sinSC3 | sin71, sinWS2 | sin67 },
{ sinSC3 | sin72, sinWS2 | sin68 },
{ sinSC3 | sin73, sinWT1 | sin63 },
{ sinSC3 | sin74, sinDS1 | sin58 },
{ sinSC3 | sin75, sinDA1 | sin04 },
{ sinSC3 | sin76, sinDA2 | sin04 },

//IMMORTAL.
{ sinSC3 | sin78, sinWS2 | sin70 },
{ sinSC3 | sin79, sinWS2 | sin71 },
{ sinSC3 | sin80, sinWS2 | sin72 },

{ sinSC3 | sin81, sinWS1 | sin65 },
{ sinSC3 | sin82, sinWP1 | sin66 },

//NVOOS
{ sinSC3 | sin83, sinWA1 | sin71 },
{ sinSC3 | sin84, sinWA1 | sin72 },
{ sinSC3 | sin85, sinWA1 | sin73 },
{ sinSC3 | sin86, sinWA1 | sin74 },
{ sinSC3 | sin87, sinWC1 | sin65 },
{ sinSC3 | sin88, sinWC1 | sin66 },
{ sinSC3 | sin89, sinWM1 | sin67 },
{ sinSC3 | sin90, sinWM1 | sin68 },
{ sinSC3 | sin91, sinWP1 | sin67 },
{ sinSC3 | sin92, sinWP1 | sin68 },
{ sinSC3 | sin93, sinWS1 | sin66 },
{ sinSC3 | sin94, sinWS1 | sin67 },
{ sinSC3 | sin95, sinWS1 | sin68 },
{ sinSC3 | sin96, sinWS2 | sin75 },
{ sinSC3 | sin97, sinWS2 | sin76 },
{ sinSC3 | sin98, sinWS2 | sin77 },
{ sinSC4 | sin01, sinWT1 | sin65 },
{ sinSC4 | sin02, sinWT1 | sin66 },
{ sinSC4 | sin03, sinWT1 | sin67 },
{ sinSC4 | sin04, sinDS1 | sin60 },
{ sinSC4 | sin05, sinDS1 | sin61 },
{ sinSC4 | sin06, sinDS1 | sin62 },
{ sinSC4 | sin07, sinDS1 | sin63 },
{ sinSC4 | sin08, sinDA1 | sin15 },
{ sinSC4 | sin09, sinDA1 | sin16 },
{ sinSC4 | sin10, sinDA2 | sin15 },
{ sinSC4 | sin11, sinDA2 | sin16 },

// IMMORTAL 06.12
{ sinSC4 | sin12, sinDS1 | sin64 },
{ sinSC4 | sin13, sinWA1 | sin75 },
{ sinSC4 | sin14, sinWA1 | sin76 },
{ sinSC4 | sin15, sinWC1 | sin67 },
{ sinSC4 | sin16, sinWC1 | sin68 },
{ sinSC4 | sin17, sinWH1 | sin57 },
{ sinSC4 | sin18, sinWM1 | sin69 },
{ sinSC4 | sin19, sinWM1 | sin70 },
{ sinSC4 | sin20, sinWP1 | sin69 },
{ sinSC4 | sin21, sinWP1 | sin70 },
{ sinSC4 | sin22, sinWP1 | sin71 },
{ sinSC4 | sin23, sinWS1 | sin69 },
{ sinSC4 | sin24, sinWS1 | sin70 },
{ sinSC4 | sin25, sinWS2 | sin78 },
{ sinSC4 | sin26, sinWT1 | sin68 },

// ITENS START PT
{ sinSC4 | sin27, sinWA1 | sin79 },
{ sinSC4 | sin28, sinWC1 | sin71 },
{ sinSC4 | sin29, sinWM1 | sin73 },
{ sinSC4 | sin30, sinWP1 | sin74 },
{ sinSC4 | sin31, sinWS1 | sin73 },
{ sinSC4 | sin32, sinWS2 | sin86 },
{ sinSC4 | sin33, sinWS2 | sin87 },
{ sinSC4 | sin34, sinWT1 | sin71 },
{ sinSC4 | sin35, sinDS1 | sin67 },

// ARMADURAS MAGICAS BPT

{ sinSC4 | sin36, sinDA1 | sin20 },
{ sinSC4 | sin37, sinDA2 | sin20 },

// NEW ITENS

{ sinSC4 | sin38, sinWA1 | sin81 },
{ sinSC4 | sin39, sinWC1 | sin73 },
{ sinSC4 | sin40, sinWH1 | sin61 },
{ sinSC4 | sin41, sinWM1 | sin75 },
{ sinSC4 | sin42, sinWP1 | sin76 },
{ sinSC4 | sin43, sinWS1 | sin75 },
{ sinSC4 | sin44, sinWS2 | sin89 },
{ sinSC4 | sin45, sinWT1 | sin73 },
{ sinSC4 | sin46, sinDS1 | sin69 },

// NOVO

{ sinSC4 | sin47, sinDA1 | sin28 },
{ sinSC4 | sin48, sinDA2 | sin28 },
{ sinSC4 | sin49, sinDA1 | sin27 },
{ sinSC4 | sin50, sinDA2 | sin27 },


{ sinSC4 | sin51, sinWA1 | sin82 },
{ sinSC4 | sin52, sinWC1 | sin74 },
{ sinSC4 | sin53, sinWH1 | sin62 },
{ sinSC4 | sin54, sinWM1 | sin76 },
{ sinSC4 | sin55, sinWP1 | sin77 },
{ sinSC4 | sin56, sinWS1 | sin76 },
{ sinSC4 | sin57, sinWS2 | sin90 },
{ sinSC4 | sin58, sinWT1 | sin74 },
{ sinSC4 | sin59, sinDS1 | sin70 },

//ABYSSAL

{ sinSC4 | sin60, sinWA1 | sin31 },
{ sinSC4 | sin61, sinWC1 | sin29 },
{ sinSC4 | sin62, sinWH1 | sin32 },
{ sinSC4 | sin63, sinWM1 | sin31 },
{ sinSC4 | sin64, sinWP1 | sin30 },
{ sinSC4 | sin65, sinWS1 | sin31 },
{ sinSC4 | sin66, sinWS2 | sin34 },
{ sinSC4 | sin67, sinWT1 | sin30 },
{ sinSC4 | sin68, sinDA1 | sin35 },
{ sinSC4 | sin69, sinDA2 | sin35 },
{ sinSC4 | sin70, sinDS1 | sin28 },

//WARTALE
{ sinSC4 | sin71, sinWS2 | sin91 },
{ sinSC4 | sin72, sinDS1 | sin71 },

// NOVAS SKINS 08.10.2021

{ sinSC4 | sin73, sinWA1 | sin83 },
{ sinSC4 | sin74, sinWA1 | sin84 },
{ sinSC4 | sin75, sinWA1 | sin85 },
{ sinSC4 | sin76, sinWA1 | sin86 },
{ sinSC4 | sin77, sinWC1 | sin75 },
{ sinSC4 | sin78, sinWC1 | sin76 },
{ sinSC4 | sin79, sinWC1 | sin77 },
{ sinSC4 | sin80, sinWH1 | sin63 },
{ sinSC4 | sin81, sinWM1 | sin77 },
{ sinSC4 | sin82, sinWM1 | sin78 },
{ sinSC4 | sin83, sinWM1 | sin79 },
{ sinSC4 | sin84, sinWM1 | sin80 },
{ sinSC4 | sin85, sinWP1 | sin78 },
{ sinSC4 | sin86, sinWP1 | sin79 },
{ sinSC4 | sin87, sinWP1 | sin80 },
{ sinSC4 | sin88, sinWS1 | sin77 },
{ sinSC4 | sin89, sinWS1 | sin78 },
{ sinSC4 | sin90, sinWS1 | sin79 },
{ sinSC4 | sin91, sinWS2 | sin92 },
{ sinSC4 | sin92, sinWS2 | sin93 },
{ sinSC4 | sin93, sinWS2 | sin94 },
{ sinSC4 | sin94, sinWS2 | sin95 },
{ sinSC4 | sin95, sinWT1 | sin75 },
{ sinSC4 | sin96, sinWT1 | sin76 },
{ sinSC4 | sin97, sinWT1 | sin77 },
{ sinSC4 | sin98, sinDS1 | sin72 },
{ sinSC5 | sin01, sinDS1 | sin73 },
{ sinSC5 | sin02, sinDS1 | sin74 },

{ sinSC5 | sin03, sinWP1 | sin28 },

{ sinSC5 | sin04, sinWA1 | sin88 },
{ sinSC5 | sin05, sinWA1 | sin89 },
{ sinSC5 | sin06, sinWC1 | sin79 },
{ sinSC5 | sin07, sinWC1 | sin80 },
{ sinSC5 | sin08, sinWM1 | sin82 },
{ sinSC5 | sin09, sinWM1 | sin83 },
{ sinSC5 | sin10, sinWP1 | sin82 },
{ sinSC5 | sin11, sinWP1 | sin83 },
{ sinSC5 | sin12, sinWS1 | sin81 },
{ sinSC5 | sin13, sinWS1 | sin82 },
{ sinSC5 | sin14, sinWS2 | sin97 },
{ sinSC5 | sin15, sinWS2 | sin98 },
{ sinSC5 | sin16, sinWT1 | sin79 },
{ sinSC5 | sin17, sinWT1 | sin80 },
{ sinSC5 | sin18, sinDS1 | sin76 },
{ sinSC5 | sin19, sinDS1 | sin77 },


};

void cSKINCHANGER::Init()
{
	lpBackground = LoadDibSurfaceOffscreen("image\\sinimage\\shopall\\modifyitem\\skinchange.bmp");
	lpButton = LoadDibSurfaceOffscreen("image\\sinimage\\shopall\\modifyitem\\button.bmp");
}

void cSKINCHANGER::Draw()
{
	if (!OpenFlagSkins)
		return;

	BaseX = 50;
	BaseY = 40;

	DrawSprite(BaseX, BaseY, lpBackground, 0, 0, 352, 362);

	if (isMousePos(BaseX + 164, BaseY + 165, 26, 26))
		DrawSprite(BaseX + 164, BaseY + 165, lpButton, 0, 0, 26, 26);

	if (scItem.Flag)
	{
		if (scItem.lpItem)
			DrawSprite(scItem.x, scItem.y, scItem.lpItem, 0, 0, scItem.w, scItem.h);
	}

	if (scStone.Flag)
	{
		if (scStone.lpItem)
			DrawSprite(scStone.x, scStone.y, scStone.lpItem, 0, 0, scStone.w, scStone.h);
	}

	if (isMousePos(BaseX + 62, BaseY + 137, 66, 88))
	{
		if (scItem.Flag)
		{
			cItem.ShowItemInfo(&scItem, 1);
			sinShowItemInfoFlag = 1;
		}

		if (MouseItem.Flag)
		{
			if (!SetSkinChangerItemAreaCheck(&MouseItem, 1))
				dsDrawColorBoxFloat(D3DCOLOR_RGBA(255, 0, 0, 128), BaseX + 62, BaseY + 137, 66, 88);
			else
				dsDrawColorBoxFloat(D3DCOLOR_RGBA(0, 255, 0, 128), BaseX + 62, BaseY + 137, 66, 88);
		}
	}

	if (isMousePos(BaseX + 163, BaseY + 243, 22, 22))
	{
		if (scStone.Flag)
		{
			cItem.ShowItemInfo(&scStone, 1);
			sinShowItemInfoFlag = 1;
		}

		if (MouseItem.Flag)
		{
			if (!SetSkinChangerItemAreaCheck(&MouseItem, 2))
				dsDrawColorBoxFloat(D3DCOLOR_RGBA(255, 0, 0, 128), BaseX + 163, BaseY + 243, 22, 22);
			else
				dsDrawColorBoxFloat(D3DCOLOR_RGBA(0, 255, 0, 128), BaseX + 163, BaseY + 243, 22, 22);
		}
	}

	if (scStone.Flag && scItem.Flag)
	{
		auto it = vSkinCodes.find(scStone.CODE);

		if (it != vSkinCodes.end())
		{
			sITEM* pItem = GetItem(it->second);
			LPDIRECT3DTEXTURE9 lpItem;

			lpItem = GetItemImage(pItem);

			if (lpItem)
			{
				DrawSprite(BaseX + 222 + ((66 - pItem->w) / 2), BaseY + 137 + ((88 - pItem->h) / 2), lpItem, 0, 0, pItem->w, pItem->h);
			}
		}
	}
}

bool cSKINCHANGER::LButtonDown()
{
	if (!OpenFlagSkins)
		return false;

	if (isMousePos(BaseX + 162, BaseY + 166, 26, 26))
	{
		if (scItem.Flag && scStone.Flag)
		{
			SKINCHANGE_INFO sPacket;
			sPacket.size = sizeof(SKINCHANGE_INFO);
			sPacket.code = smTRANSCODE_SKINCHANGE;
			memcpy(&sPacket.scItem, &scItem, sizeof(sITEM));
			memcpy(&sPacket.scStone, &scStone, sizeof(sITEM));

			auto it = vSkinCodes.find(scStone.CODE);
			if (it != vSkinCodes.end())
				sPacket.newCode = it->second;

			smWsockServer->Send((char*)&sPacket, sPacket.size, TRUE);

			scItem.Flag = false;
			scStone.Flag = false;
			Close();
		}
		return true;
	}

	if (isMousePos(BaseX + 62, BaseY + 137, 66, 88))
	{
		if (MouseItem.Flag)
		{
			if (SetSkinChangerItemAreaCheck(&MouseItem, 1))
			{
				if (!scItem.Flag)
				{
					memcpy(&scItem, &MouseItem, sizeof(sITEM));
					ZeroMemory(&MouseItem, sizeof(sITEM));

					scItem.x = scItem.SetX = (BaseX + 62 + ((66 - scItem.w) / 2));
					scItem.y = scItem.SetY = (BaseY + 137 + ((88 - scItem.h) / 2));
				}
				else
				{
					sITEM backup;

					memcpy(&backup, &scItem, sizeof(sITEM));
					memcpy(&scItem, &MouseItem, sizeof(sITEM));
					memcpy(&MouseItem, &backup, sizeof(sITEM));

					scItem.x = scItem.SetX = (BaseX + 62 + ((66 - scItem.w) / 2));
					scItem.y = scItem.SetY = (BaseY + 137 + ((88 - scItem.h) / 2));
				}
			}
		}
		else
		{
			if (scItem.Flag)
			{
				memcpy(&MouseItem, &scItem, sizeof(sITEM));
				ZeroMemory(&scItem, sizeof(sITEM));
			}
		}
		return true;
	}

	if (isMousePos(BaseX + 163, BaseY + 243, 22, 22))
	{
		if (MouseItem.Flag)
		{
			if (SetSkinChangerItemAreaCheck(&MouseItem, 2))
			{
				if (!scStone.Flag)
				{
					memcpy(&scStone, &MouseItem, sizeof(sITEM));
					ZeroMemory(&MouseItem, sizeof(sITEM));

					scStone.x = scStone.SetX = (BaseX + 163 + ((22 - scStone.w) / 2));
					scStone.y = scStone.SetY = (BaseY + 243 + ((22 - scStone.h) / 2));
				}
				else
				{
					sITEM backup;

					memcpy(&backup, &scStone, sizeof(sITEM));
					memcpy(&scStone, &MouseItem, sizeof(sITEM));
					memcpy(&MouseItem, &backup, sizeof(sITEM));

					scStone.x = scStone.SetX = (BaseX + 163 + ((22 - scStone.w) / 2));
					scStone.y = scStone.SetY = (BaseY + 243 + ((22 - scStone.h) / 2));
				}
			}
		}
		else
		{
			if (scStone.Flag)
			{
				memcpy(&MouseItem, &scStone, sizeof(sITEM));
				ZeroMemory(&scStone, sizeof(sITEM));
			}
		}
		return true;
	}

	if (isMousePos(382, 53, 30, 30))
	{
		Close();
		return true;
	}

	if (isMousePos(BaseX, BaseY, 352, 362))
		return true;

	return false;
}

void cSKINCHANGER::Open()
{
	OpenFlagSkins = true;
}

void cSKINCHANGER::Close()
{
	OpenFlagSkins = false;

	if (scItem.Flag)
	{
		scItem.ItemPosition = 0;
		cInvenTory.LastSetInvenItem(&scItem, 1);
	}
	if (scStone.Flag)
	{
		scStone.ItemPosition = 0;
		cInvenTory.LastSetInvenItem(&scStone, 1);
	}
}

bool cSKINCHANGER::SetSkinChangerItemAreaCheck(sITEM* pItem, int Pos)
{
	if (Pos == 1)
	{
		if ((pItem->CODE & sinITEM_MASK2) == sinSC1)
			return false;

		if ((pItem->CODE & sinITEM_MASK2) != sinWA1 && (pItem->CODE & sinITEM_MASK2) != sinWC1 && (pItem->CODE & sinITEM_MASK2) != sinWH1 && (pItem->CODE & sinITEM_MASK2) != sinWM1 && (pItem->CODE & sinITEM_MASK2) != sinWP1 &&
			(pItem->CODE & sinITEM_MASK2) != sinWS1 && (pItem->CODE & sinITEM_MASK2) != sinWS2 && (pItem->CODE & sinITEM_MASK2) != sinWT1 && (pItem->CODE & sinITEM_MASK2) != sinDS1 && (pItem->CODE & sinITEM_MASK2) != sinDA1 && (pItem->CODE & sinITEM_MASK2) != sinDA2)
			return false;

		if (scStone.Flag)
		{
			if (!isCompatible(pItem, &scStone))
				return false;
		}
	}
	else if (Pos == 2)
	{
		if ((pItem->CODE & sinITEM_MASK2) != sinSC1 && (pItem->CODE & sinITEM_MASK2) != sinSC2 && (pItem->CODE & sinITEM_MASK2) != sinSC3 && (pItem->CODE & sinITEM_MASK2) != sinSC4 && (pItem->CODE & sinITEM_MASK2) != sinSC5)
			return false;

		if (scItem.Flag)
		{
			if (!isCompatible(&scItem, pItem))
				return false;
		}
	}

	return true;
}

bool cSKINCHANGER::isCompatible(sITEM* pItem, sITEM* pStone)
{
	auto it = vSkinCodes.find(pStone->CODE);

	if (it != vSkinCodes.end())
	{
		for (int i = 0; i < MAX_ITEM; i++)
		{
			if (sItem[i].CODE == it->second)
			{
				if ((pItem->CODE & sinITEM_MASK2) == (sItem[i].CODE & sinITEM_MASK2) && pItem->Class == sItem[i].Class)
					return true;
			}
		}
	}

	return false;
}

LPDIRECT3DTEXTURE9 cSKINCHANGER::GetItemImage(sITEM* pItem)
{
	char szFilePath[255];

	if (pItem)
	{
		if (pItem->lpTempItem)
			return pItem->lpTempItem;
		wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItem->ItemFilePath, pItem->LastCategory);

		pItem->lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
		return pItem->lpTempItem;
	}

	return nullptr;
}

sITEM* cSKINCHANGER::GetItem(DWORD CODE)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (sItem[i].CODE == CODE)
		{
			return &sItem[i];
		}
	}
	return nullptr;
}
