#pragma once

#include <d3d9.h>

#define MAX_ITEM					1900	 //071203 (700->720 ) pluto  
//ÀÛ¼ºÀÚ : ¹ÚÀç¿ø,  ÀÛ¼ºÀÏ : 08.04.07
//³»  ¿ë : Å¬·£Ä¡ÇÁ ¸µ 20°³ Ãß°¡(720->740)					
// ¹ÚÀç¿ø - ¼öÇ¥ »èÁ¦ ÈÄ 746 ºÎÅÍ ½ÃÀÛ
// ¹ÚÀç¿ø - ½´ÆÛ¾Ï¸´(2), ½ºÇÇµåºÎÃ÷(2), ½ºÅ³¸¶½ºÅÍ(3), ¿¡ÀÌÂ¡¸¶½ºÅÍ(3)
// ÀÌµ¿»óÁ¡(1), °æÇèÄ¡Áõ°¡Æ÷¼Ç(3), ½ºÅÈÃÊ±â ½ºÅæ(5)   746 -> 765
// ¹ÚÀç¿ø - ÇÇ´Ð½º Æê(30ÀÏ) Ãß°¡ 765 -> 766
// ¹ÚÀç¿ø - ÀÌº¥Æ® ¸µ, ÀÌº¥Æ® ¾Æ¹Â·¿ Ãß°¡ 766 -> 768
// ¹ÚÀç¿ø - ¿¤´õ ÄÚÆÛ ¿À¾î, ½´ÆÛ ¿¡ÀÌÂ¡ ½ºÅæ, Å×ÀÌ¿ÍÁî Ãß°¡ 768 -> 771
// ¹ÚÀç¿ø 09.10.13 ºÎ½ºÅÍ ¾ÆÀÌÅÛ(»ý¸í·Â, ±â·Â, ±Ù·Â) 9Á¾ Ãß°¡(771->780)
// ¹ÚÀç¿ø 09.12.04 ºô¸µ ¸ÅÁ÷ Æ÷½º Ãß°¡(780->783)
// ¹ÚÀç¿ø 09.11.04 ¸ÅÁ÷ ½©ÅÒ(14Á¾), ¸ÅÁ÷ Æ÷½º(14Á¾), ÀÏ¹Ý Æ÷½º(2Á¾ º§·ë, ¿À¸£µµ) Ãß°¡(783->813) ¸ÅÁ÷ Æ÷½º Ãß°¡
// ¹ÚÀç¿ø 09.12.01 ºô¸µ µµ¿ì¹Ì Æê Ãß°¡(813->817)
// ¹ÚÀç¿ø 09.12.08 »êÅ¸¸µ, »êÅ¸¾Æ¹Ä·¿ Ãß°¡(817->819)
// ¹ÚÀç¿ø 09.12.17 ÀÌº¥Æ®¸µ(1½Ã°£, 1ÀÏ), ÀÌº¥Æ®¾Æ¹Ä·¿(1½Ã°£, 1ÀÏ), ¹ãÇÏ´ÃÀÇ º°(1Á¾) Ãß°¡(819->824)
// ¹ÚÀç¿ø 10.02.02 º¸½º ¸ó½ºÅÍ ¸µ(Ç»¸®¸µ, ¹Ùº§¸µ) Ãß°¡(824->826)
// Àåº° 10.02.01 ¹ß·»Å¸ÀÎ ÃÊÄÝ¸´ Ãß°¡(826->827)
// Àåº° 10.02.02 Heart Ring(7ÀÏ) Ãß°¡(827->828)
// ¹ÚÀç¿ø 10.02.12 ¿À¸£µµ ½©ÅÒ(os114) Ãß°¡ (828->829) 
// ¹ÚÀç¿ø 10.02.12 ¾ËÆÄºª Ãß°¡ (829->836) 
// Àåº° 10.02.16 È­ÀÌÆ®ÄÜÅä¶ó½ºÆ® ÀÌº¥Æ® ¼öÁ¤, ·é, Á¦ÀÛ¼­, ´«²É ¸ñ°ÉÀÌ  Ãß°¡(836->847)
// Àåº° 10.02.16 ºô¸µ µµ¿ì¹Ì Æê 1ÀÏ Ãß°¡(4¸¶¸®)(847->851)
// Àåº° 10.03.01 ÇÏÆ®¾Æ¹Ä·¿(7ÀÏ) Ãß°¡, Äµµðµ¥ÀÌÁî Äµµð(851->853)
// Àåº° 10.03.01 ÇÇ´Ð½º(1½Ã°£), °æÇèÄ¡ 2¹è Áõ°¡¾à(1½Ã°£), ½ºÇÇµåºÎÃ÷1ÀÏ, ½´ÆÛ¾Ï¸´1ÀÏ Ãß°¡ (853->857)
// Àåº° 10.03.01 ºô¸µµµ¿ì¹Ì 4¸¶¸® Ãß°¡ // Àåº° - ºô¸µ µµ¿ì¹Ì Æê Ãß°¡(7ÀÏ) (857->861)
// ¹ÚÀç¿ø 10.03.08 ¿¡ÀÌÂ¡ ¸¶½ºÅÍ(2Â÷) ¾ÆÀÌÅÛ Ãß°¡ 3Á¾(D,E,F) (864->865)
// ¹ÚÀç¿ø 10.03.26 È£¶ûÀÌ Ä¸½¶ Ãß°¡(864->865)	
// Àåº° 10.03.29 ´ëÀåÀåÀÌÀÇ È¥ ¾ÆÀÌÅÛ(865->875)
// Àåº° 10.04.01 ´ëÀåÀåÀÌÀÇ È¥ º¸»ó ¿Ê ¾ÆÀÌÅÛ(875->879)
// Àåº° 10.04.13 ±×¶óºñÆ¼ ½ºÅ©·Ñ, ¸ÅÁöÄÃ±×¸°(¿¡¸Þ¶öµå, ºñÃë), ¸Þ¸ð¸®¾ó ºí·¹ÀÌµå, ±â°£Á¦ 4Á¾(879->890)
// Àåº° 10.05.04 ½´ÆÛ ¿¡ÀÌÁö¾î ½ºÅæ 1.5, ±â°£Á¦ 4Á¾(890->895)
// Àåº° 10.06.10 ¹ìÇÇ¸¯Ä¿½ºÇÍEX, Ä«¶óÀÇ ´«¹°(894->898) 
// ¹ÚÀç¿ø 10.06.10 2010 ¿ùµåÄÅ ÀÌº¥Æ® (Ãà±¸°ø Æ÷¼Ç Ãß°¡) (898->899)
// ¹ÚÀç¿ø 10.07.13 ¹Í½ºÃÄ ¸®¼Â ½ºÅæ, ¸®½ºÆå ½ºÅæ, ±Ù·Â ¸®µà½º Æ÷¼Ç(1ÀÏ,7ÀÏ), ÇÊµå ÄÚ¾î(1ÀÏ, 7ÀÏ)¼ö¿µº¹ Ãß°¡ (899 -> 909)
// Àåº° 10.07.15  ½Å±Ô¾ÆÀÌÅÛ 17Á¾, ¼ö¹Ú(909->927) 
// Àåº° 10.08.10 ¼Ò¿ï½ºÅæ 9°³, ¸µ°ú ¾Æ¹Ä·¿ 9°³ Ãß°¡( 927->945 )
// Àåº° 10.09.03 º¹³¯ ÀÌº¥Æ® ¸µ, ¾Æ¹Ä 3°³ Ãß°¡(945 -> 948 )

#define ITEMSIZE					22   //¾ÆÀÌÅÛ ÀÌ¹ÌÁöÀÇ Å©±â¸¦ ³ª´©´Â °ª 

#define CHECK_COPY_ITEM				1	//º¹»ç¾ÆÀÌÅÛ
#define CHECK_GIVE_ITEM				2	//ÁõÁ¤¿ë¾ÆÀÌÅÛ 


/*---------------------------------------------*
*			¾ÆÀÌÅÛÀÌ ³õ¿©Áú À§Ä¡¸¦ Á¤ÀÇÇÑ´Ù '
*----------------------------------------------*/
#define INVENTORY_POS_BOX			    0x00000001  
#define INVENTORY_POS_LHAND				0x00000002 
#define INVENTORY_POS_RHAND				0x00000004 
#define INVENTORY_POS_ARMOR				0x00000008 
#define INVENTORY_POS_BOOTS				0x00000010 
#define INVENTORY_POS_GLOVES			0x00000020 
#define INVENTORY_POS_LRING				0x00000040 
#define INVENTORY_POS_RRING				0x00000080 
#define INVENTORY_POS_SHELTOM			0x00000100 
#define INVENTORY_POS_AMULET			0x00000200 
#define INVENTORY_POS_ARMLET			0x00000800
#define INVENTORY_POS_TWO_HAND			0x00001000
#define INVENTORY_POS_POTION			0x00002000
#define INVENTORY_POS_COSTUME			0x00004000 // costume xxstr
#define INVENTORY_POS_RELICS			0x00020000
#define INVENTORY_POS_RELICS2			0x00040000
#define INVENTORY_POS_RELICS3			0x00080000

/*---------------------------------------------*
*			¾ÆÀÌÅÛÀÇ Å¬·¡½º¸¦  Á¤ÀÇÇÑ´Ù
*----------------------------------------------*/

#define ITEM_CLASS_WEAPON_ONE			INVENTORY_POS_RHAND 
#define ITEM_CLASS_WEAPON_TWO			(INVENTORY_POS_RHAND |INVENTORY_POS_LHAND) //ÅõÇÚµå´Â ¾îµð¿¡³ª µé¾î°¥¼öÀÖ´Ù 
#define ITEM_CLASS_ARMOR				INVENTORY_POS_ARMOR 
#define ITEM_CLASS_BOOTS				INVENTORY_POS_BOOTS 
#define ITEM_CLASS_GLOVES				INVENTORY_POS_GLOVES 
#define ITEM_CLASS_SHIELDS				INVENTORY_POS_LHAND
#define ITEM_CLASS_RING					(INVENTORY_POS_LRING | INVENTORY_POS_RRING)
#define ITEM_CLASS_SHELTOM				INVENTORY_POS_SHELTOM 
#define ITEM_CLASS_AMULET				INVENTORY_POS_AMULET 
#define ITEM_CLASS_ARMLET				INVENTORY_POS_ARMLET 
#define ITEM_CLASS_MAGICIAL_STUFFS		INVENTORY_POS_LHAND
#define ITEM_CLASS_POTION				INVENTORY_POS_POTION
#define ITEM_CLASS_COSTUME              INVENTORY_POS_COSTUME // costume xxstr
#define ITEM_CLASS_ECORE				INVENTORY_POS_BOX
#define ITEM_CLASS_QUEST				INVENTORY_POS_BOX
#define ITEM_CLASS_FORCEORB				INVENTORY_POS_BOX
#define ITEM_CLASS_SEEL					INVENTORY_POS_BOX

#define INVENTORY_POS_EARRINGSL			0x00008000
#define INVENTORY_POS_EARRINGSR			0x00010000
#define ITEM_CLASS_EARRRINGS			(INVENTORY_POS_EARRINGSL | INVENTORY_POS_EARRINGSR)
#define ITEM_CLASS_RELIC				INVENTORY_POS_RELICS
#define ITEM_CLASS_RELIC2				INVENTORY_POS_RELICS2
#define ITEM_CLASS_RELIC3				INVENTORY_POS_RELICS3



//¹ß»çÇüÀÎÁö ±ÙÁ¢ÇüÀÎÁö 
#define ITEM_WEAPONCLASS_NOT_SHOOTING	1 //±ÙÁ¢Çü 
#define ITEM_WEAPONCLASS_SHOOTING		2 //¹ß»çÇü 
#define ITEM_WEAPONCLASS_CASTING		3 //¹ý»çÇü

//¹«±âÀÇ Å¬·¡½º¸¦ Á¤ÀÇÇÑ´Ù 
/*---------------------------------------------*
*			(¹«±â)1Â÷ Ä«Å×°í¸®
*----------------------------------------------*/
#define sinWA1			0x01010000	//Axes
#define sinWC1			0x01020000	//Claws
#define sinWH1			0x01030000	//Hammer & So On
#define sinWM1			0x01040000	//Magicial Stuffs
#define sinWP1			0x01050000	//Poles & Spears
#define sinWS1			0x01060000	//Shooters
#define sinWS2			0x01070000	//Swords
#define sinWT1			0x01080000	//Throwing Arms
#define sinSA1			0x0D010000
#define sinWD1			0x010A0000
/*---------------------------------------------*
*			(¹æ¾î±¸)1Â÷ Ä«Å×°í¸®
*----------------------------------------------*/

#define sinDA1			0x02010000	//Armor
#define sinDB1			0x02020000	//Boots
#define sinDG1			0x02030000	//Gloves
#define sinDS1			0x02040000	//Shields
#define sinDA2			0x02050000	//Armor

#define sinOE1			0x030A0000

#define sinCA1			0x02100000  //Trajes masculinos
#define sinCA2			0x02200000	//Trajes femininos

#define sinRR1			0x0A040000

/*---------------------------------------------*
*			(Àå½Å±¸·ù)1Â÷ Ä«Å×°í¸®
*----------------------------------------------*/

#define sinOA1			0x03010000	//Amulet
#define sinOA2			0x03020000	//Armlet
#define sinOM1			0x03030000	//Magicial Stuffs
#define sinOR1			0x03040000	//Ring
#define sinOR2			0x03050000	//Ring2
#define sinOS1			0x02350000	//Sheltom
#define sinFO1			0x03060000  //Force Orb
#define sinSE1			0x03070000  //Seel
#define sinPR1			0x03080000  // ±¤¼® pluto
#define sinPR2			0x03090000  // ¼öÁ¤ pluto
#define sinPR3			0x03100000  // ·é(A) pluto
#define sinPR4			0x03110000  // ·é(B) pluto
/*---------------------------------------------*
*			(¹°¾à)1Â÷ Ä«Å×°í¸®
*----------------------------------------------*/
#define sinPM1			0x04010000  //Mana
#define sinPL1			0x04020000  //Life
#define sinPS1			0x04030000  //Stamina

/*---------------------------------------------*
*			(µ·)1Â÷ Ä«Å×°í¸®
*----------------------------------------------*/
#define sinGG1			0x05010000 //Gold
#define sinBS1			0x05020000 //º§¶óÅä½ºÅæ

/*---------------------------------------------*
*			(±ÍÈ¯)1Â÷ Ä«Å×°í¸®
*----------------------------------------------*/
#define sinEC1			0x06010000

/*---------------------------------------------*
*			  Äù½ºÆ® ¾ÆÀÌÅÛ
*----------------------------------------------*/

#define sinQT1			0x07010000


/*---------------------------------------------*
*			  ÀÌº¥Æ® ¾ÆÀÌÅÛ
*----------------------------------------------*/
#define sinSP1			0x08010000 
#define sinGP1			0x08020000		//0x09010000 À¸·ÎÇÏ´Ï ¹®Á¦ÀÌ³× ±×·Á.. (& sinITEM_MASK2 °¡ ¾È¸ÔÀ½)
#define sinQW1			0x08030000		//¿öÇÁ°ÔÀÌÆ® À®
#define sinGF1			0x08040000		//º°»óÇ°±Ç
#define sinPZ1			0x08060000		//¾ÆÃ³ ÆÛÁñ
#define sinPZ2			0x08070000		//Å·È£ÇÇ ÆÛÁñ
#define sinCH1			0x08080000		//¹ß·»Å¸ÀÎµ¥ÀÌ ÃÊÄÝ·¿
#define sinSD2			0x08090000		//Sod2 ¹ß»ý ¾ÆÀÌÅÛ
#define sinBC1          0x080A0000      //°ø¼ºÀü ¹ß»ý ¾ÆÀÌÅÛ
#define sinBI1          0x080B0000      //À¯·á±¸¸Å ¾ÆÀÌÅÛ  
#define sinBI2          0x080C0000      //À¯·á±¸¸Å ¾ÆÀÌÅÛ(ÆÐÅ°Áö Ä³½¬ ¾ÆÀÌÅÛ )  
#define sinGP2			0x080D0000		// Àåº° - ¼Ò¿ï½ºÅæ
#define sinSC1			0x080E0000
#define sinSC2			0x080F0000	// 장별 - 소울스톤
#define sinSC3			0x08100000 // 장별 - 소울스톤
#define sinSC4			0x08200000
#define sinSC5			0x08400000
#define sinSK1 0x081C0000
#define sinSK2 0x081C0001
#define sinSK3 0x081C0002

/*---------------------------------------------*
*			  Make Item
*----------------------------------------------*/
#define sinMA1			0x09010000 
#define sinMA2			0x09020000

#define sinRL1			0x03130000
#define sinRL2			0x03140000
#define sinRL3			0x03150000

#define sinSS1			0x09030000
#define sinES1			0x09040000
#define sinSR1			0x09050000
#define sinSR2			0x09060000
/*---------------------------------------------*
*			  Á¦ÀÛ Àç·á ¾ÆÀÌÅÛ
*----------------------------------------------*/
// pluto Á¦ÀÛ
#define sinWR1			0x0A010000 // ¹«±¸ ·¹½ÃÇÇ
#define sinDR1			0x0A020000 // °©ÁÖ ·¹½ÃÇÇ

#define EXTREME_RECIPE		1		// ÀØÇôÁø ·¹½ÃÇÇ
#define ANCIENT_RECIPE		2		// °í´ëÀÇ ·¹½ÃÇÇ
#define	MINOTAUR_RECIPE		3		// ´ëÁöÀÇ ·¹½ÃÇÇ
#define DOOM_RECIPE			4		// ¾îµÒÀÇ ·¹½ÃÇÇ
#define SALAMANDER_RECIPE	5		// È­¸íÀÇ ·¹½ÃÇÇ
#define WYVERN_RECIPE		6		// ¹Ù¶÷ÀÇ ·¹½ÃÇÇ
#define PHOENIX_RECIPE		7		// ÅÂ¾çÀÇ ·¹½ÃÇÇ
#define FRENZY_RECIPE		8		// ±¤Æ÷ÇÑ ·¹½ÃÇÇ
#define HEAVENS_RECIPE		9		// Ãµ»óÀÇ ·¹½ÃÇÇ 
#define SNOW_RECIPE			10		// Æ÷¼³ÀÇ ·¹½ÃÇÇ
#define MEMORY_RECIPE		11		// ±â¾ïÀÇ ·¹½ÃÇÇ // Àåº° - ´ëÀåÀåÀÌÀÇ È¥

/*---------------------------------------------*
*			¾ÆÀÌÅÛ 2Â÷ Ä«Å×°í¸®(¾ÆÀÌÅÛº°·Î ¼¼ºÐÈ­µÇ ±¸ºÐ )
*----------------------------------------------*/
#define sin00			0x00000000	
#define sin01			0x00000100	
#define sin02			0x00000200
#define sin03			0x00000300
#define sin04			0x00000400
#define sin05			0x00000500
#define sin06			0x00000600
#define sin07			0x00000700
#define sin08			0x00000800
#define sin09			0x00000900
#define sin10			0x00000A00
#define sin11			0x00000B00
#define sin12			0x00000C00
#define sin13			0x00000D00
#define sin14			0x00000E00
#define sin15			0x00000F00
#define sin16			0x00001000
#define sin17			0x00001100
#define sin18			0x00001200
#define sin19			0x00001300
#define sin20			0x00001400
#define sin21			0x00001500
#define sin22			0x00001600
#define sin23			0x00001700
#define sin24			0x00001800
#define sin25			0x00001900 //16
#define sin26			0x00002A00
#define sin27			0x00002B00
#define sin28			0x00002C00
#define sin29			0x00002D00
#define sin30			0x00002E00
#define sin31			0x00002F00
#define sin32			0x00003000
#define sin33			0x00003100
#define sin34			0x00003200
#define sin35			0x00003300
#define sin36			0x00003400
#define sin37			0x00003500
#define sin38			0x00003600
#define sin39			0x00003700
#define sin40			0x00003800
#define sin41			0x00003900
#define sin42			0x00003A00
#define sin43			0x00003B00
#define sin44			0x00003C00
#define sin45			0x00003D00
#define sin46			0x00003E00
#define sin47			0x00003F00
#define sin48			0x00004000	// pluto Ãß°¡
#define sin49			0x00004100	// pluto Ãß°¡
#define sin50			0x00004200	// pluto Ãß°¡
#define sin51			0x00004300	// ¹ÚÀç¿ø - ÇÇ´Ð½º Æê(30ÀÏ) Ãß°¡ 
#define sin52			0x00004400
#define sin53			0x00004500
#define sin54			0x00004600
#define sin55			0x00004700
#define sin56			0x00004800
#define sin57			0x00004900
#define sin58			0x00004A00
#define sin59			0x00004B00
#define sin60			0x00004C00  // ¹ÚÀç¿ø - ¿¤´õ ÄÚÆÛ ¿À¾î Ãß°¡
#define sin61			0x00004D00  // ¹ÚÀç¿ø - ½´ÆÛ ¿¡ÀÌÂ¡ ½ºÅæ Ãß°¡
#define sin62			0x00004E00
#define sin63			0x00004F00
#define sin64			0x00005000
#define sin65			0x00005100
#define sin66			0x00005200
#define sin67			0x00005300
#define sin68			0x00005400
#define sin69			0x00005500
#define sin70			0x00005600
#define sin71			0x00005700
#define sin72			0x00005800
#define sin73			0x00005900 
#define sin74			0x00005A00 
#define sin75			0x00005B00 
#define sin76			0x00005C00 
#define sin77			0x00005D00 
#define sin78			0x00005E00 
#define sin79			0x00005F00 
#define sin80			0x00006000 
#define sin81			0x00006100 // ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¸¶½ºÅÍ(2Â÷) ¾ÆÀÌÅÛ Ãß°¡
#define sin82			0x00006200 // ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¸¶½ºÅÍ(2Â÷) ¾ÆÀÌÅÛ Ãß°¡
#define sin83			0x00006300 // ¹ÚÀç¿ø - ¿¡ÀÌÂ¡ ¸¶½ºÅÍ(2Â÷) ¾ÆÀÌÅÛ Ãß°¡
#define sin84			0x00006400 // Àåº° - ±×¸®¹ÙÆ¼ ½ºÅ©·Ñ
#define sin85			0x00006500
#define sin86			0x00006600 
#define sin87			0x00006700 
#define sin88			0x00006800 
#define sin89			0x00006900 
#define sin90			0x00006A00 
#define sin91			0x00006B00 
#define sin92			0x00006C00 
#define sin93			0x00006D00 
#define sin94			0x00006E00 
#define sin95			0x00006F00 
#define sin96			0x00007000 
#define sin97			0x00007100 
#define sin98			0x00007200 









/*---------------------------------------------*
*			¾ÆÀÌÅÛ »ç¿îµå
*----------------------------------------------*/

#define		SIN_SOUND_AXES				1
#define		SIN_SOUND_CLAWS				2
#define		SIN_SOUND_HAMMER			3
#define		SIN_SOUND_MAGICIAL		 	4
#define		SIN_SOUND_POLES				5
#define		SIN_SOUND_SHOOTERS			6
#define		SIN_SOUND_SWORDS			7
#define		SIN_SOUND_THROWING			8
#define		SIN_SOUND_ARMOR				9
#define		SIN_SOUND_BOOTS				10
#define		SIN_SOUND_GLOVES			11
#define		SIN_SOUND_SHIELDS			12
#define		SIN_SOUND_AMULET			13
#define		SIN_SOUND_Armlet			14
#define		SIN_SOUND_RING				15
#define     SIN_SOUND_SHELTOM			16
#define     SIN_SOUND_POTION			17
#define     SIN_SOUND_COIN				18
#define     SIN_SOUND_STAFF				19
#define		SIN_SOUND_EAT_POTION		20
#define		SIN_SOUND_SHOW_INTER		21
#define		SIN_SOUND_REPAIR_ITEM		22
#define		SIN_SOUND_FAILD_MIXITEM		23
#define		SIN_SOUND_ARMOR2			24
#define		SIN_SOUND_EAT_POTION2		25


/** ¿ø¼Ò ÀúÇ×·Â **/
#define   sITEMINFO_BIONIC			0	//»ýÃ¼ 
#define   sITEMINFO_EARTH			1	//´ëÀÚ¿¬ 
#define   sITEMINFO_FIRE			2	//ºÒ 
#define	  sITEMINFO_ICE				3	//³Ã±â 
#define   sITEMINFO_LIGHTING		4	//¹ø°³ 
#define   sITEMINFO_POISON			5	//µ¶ 
#define   sITEMINFO_WATER			6	//¹° 
#define   sITEMINFO_WIND			7	//¹Ù¶÷ 
#define	  sITEMINFO_NONE			15	//¼Ó¼º ¹«½Ã

//////////* ¾ÆÀÌÅÛ Á¾·ù *////////
#define ITEM_KIND_NORMAL			0   //±âº» ¾ÆÀÌÅÛ 
#define ITEM_KIND_CRAFT				1   //Á¶ÇÕ ¾ÆÀÌÅÛ 
#define ITEM_KIND_AGING				2   //¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ 
#define ITEM_KIND_QUEST				3	//Äù½ºÆ®¿ë ¾ÆÀÌÅÛ 
#define ITEM_KIND_EVENT				4	//ÀÌº¥Æ® ¾ÆÀÌÅÛ 
#define ITEM_KIND_MAKE_MAIN			5	//ÀÌº¥Æ® ¾ÆÀÌÅÛ 
#define ITEM_KIND_MAKE_ELEMENT		6	//ÀÌº¥Æ® ¾ÆÀÌÅÛ 
#define ITEM_KIND_QUEST_WEAPON		7	//ÀÌº¥Æ® ¾ÆÀÌÅÛ 
#define ITEM_KIND_SPECIAL			8	//SpecialItemFlag[1] ¿¡ ÇÃ·¢µî·Ï½Ã ½ºÆä¼È¾ÆÀÌÅÛÀ¸·Î ±¸ºÐ

/////////////////////////////////


#define   SIN_ADD_FIRE				0x00000001	//ºÒ
#define   SIN_ADD_ICE				0x00000002	//¾óÀ½
#define   SIN_ADD_LIGHTNING			0x00000004	//¹ø°³
#define   SIN_ADD_POISON			0x00000008	//µ¶
#define   SIN_ADD_BIO				0x00000010	//¹°
#define   SIN_ADD_CRITICAL			0x00000020	//Å©¸®Æ¼ÄÃ
#define   SIN_ADD_ATTACK_RATE		0x00000040	//¸íÁß·Â
#define   SIN_ADD_DAMAGE_MIN		0x00000080	//ÃÖ¼Ò°ø°Ý·Â
#define   SIN_ADD_DAMAGE_MAX		0x00000100	//ÃÖ´ë°ø°Ý·Â
#define   SIN_ADD_ATTACK_SPEED		0x00000200	//°ø°Ý¼Óµµ
#define   SIN_ADD_ABSORB			0x00000400	//Èí¼ö·Â
#define   SIN_ADD_DEFENCE			0x00000800	//¹æ¾î·Â
#define   SIN_ADD_BLOCK_RATE		0x00001000	//ºí·°À²
#define   SIN_ADD_MOVE_SPEED		0x00002000	//ÀÌµ¿¼Óµµ
#define   SIN_ADD_LIFE				0x00004000	//ÃÖ´ë»ý¸í·Â
#define   SIN_ADD_MANA				0x00008000	//ÃÖ´ë±â·Â
#define   SIN_ADD_STAMINA			0x00010000	//ÃÖ´ë±Ù·Â
#define   SIN_ADD_LIFEREGEN			0x00020000  //»ý¸í·ÂÀç»ý
#define   SIN_ADD_MANAREGEN			0x00040000  //±â·Â·ÂÀç»ý
#define   SIN_ADD_STAMINAREGEN		0x00080000  //±Ù·Â·ÂÀç»ý


/*----------------------------------------------------------------------------*
*						 ¾ÆÀÌÅÛ ¼Ó¼º
*-----------------------------------------------------------------------------*/
struct	sITEM_CREATE {
	DWORD	Head;			//Çì´õ
	DWORD	dwVersion;		//»ý¼º ¹öÀü
	DWORD	dwTime;			//»ý¼º½Ã°£
	DWORD	dwChkSum;		//¾ÆÀÌÅÛ Ã¼Å©¼¶
};

struct sITEM_SPECIAL {

	float	Add_fAbsorb;			//Èí¼ö·Â 
	int     Add_Defence;			//¹æ¾î·Â 
	float   Add_fSpeed;				//ÀÌµ¿ ¼Óµµ 
	float   Add_fBlock_Rating;		//(¹æÆÐ)ºí·°À² 
	int     Add_Attack_Speed;		//°ø°Ý¼Óµµ
	int     Add_Critical_Hit;		//1.5¹è µ¥¹ÌÁöÈ®À²
	int     Add_Shooting_Range;		//»çÁ¤°Å¸® 
	float   Add_fMagic_Mastery;     //¸¶¹ý¼÷·Ãµµ 
	short	Add_Resistance[8];		//¿ø¼Ò¿¡´ëÇÑ ÀúÇ×·Â 

	////////////////////////////////////////////////

	short	Lev_Attack_Resistance[8];	//¿ø¼Ò¿¡´ëÇÑ °ø°Ý·Â
	int		Lev_Mana;				//¸¶³ªÈ¸º¹(ÃÖ¼Ò)(ÃÖ´ë)
	int		Lev_Life;				//¶óÀÌÇÁÈ¸º¹(ÃÖ¼Ò)(ÃÖ´ë) 
	int     Lev_Attack_Rating;		//¸íÁß·Â 
	short	Lev_Damage[2];			//°ø°Ý·Â

	float	Per_Mana_Regen;			//¸¶³ª Àç»ý 6
	float	Per_Life_Regen;			//¶óÀÌÇÁ Àç»ý 
	float	Per_Stamina_Regen;		//½ºÅ×¹Ì³ª Àç»ý

	//////////////////////////////////////////////////

	DWORD	dwTemp[32];
};

enum ESocketType : unsigned char
{
	SOCKETTYPE_None,

	SOCKETTYPE_Prismatic,
	SOCKETTYPE_Emerald,
	SOCKETTYPE_Ruby,
	SOCKETTYPE_Aquamarine,
	SOCKETTYPE_Amethyst,
	SOCKETTYPE_Topaz,

	SOCKETTYPE_Count = 7,
};
enum EGemType : unsigned char
{
	GEMTYPE_None,

	GEMTYPE_Triangular,
	GEMTYPE_Square,
	GEMTYPE_Marquise,
};
enum EGemItem : unsigned char
{
	GEMITEM_None,

	/*Normal Gems*/
	GEMITEM_Emerald,
	GEMITEM_Ruby,
	GEMITEM_Aquamarine,
	GEMITEM_Amethyst,
	GEMITEM_Topaz,

	/*Special Gems*/
	GEMITEM_RainbowOpal,
	GEMITEM_DemonSlayer,
	GEMITEM_BloodyPerl,
	GEMITEM_NavyPerl,
	GEMITEM_TempskronMartyr,
	GEMITEM_MorionMartyr,
	GEMITEM_RoyalDiamond,
	GEMITEM_PolishedCitrine,
	GEMITEM_ElementalTourmaline,
	GEMITEM_DivineHeart,
	GEMITEM_LuckyCirclet,
};


struct SocketItem
{
	ESocketType 	eSocketType;
	EGemType		eGemType;
	EGemItem		eGemItem;
};

struct sITEMINFO {

	DWORD	dwSize;						//¾ÆÀÌÅÛ ±¸Á¶ Å©±â

	sITEM_CREATE	ItemHeader;			//¾ÆÀÌÅÛ »ý¼º Á¤º¸

	short	Durability[2];				//³»±¸·Â

	//////// ½ÇÁ¦ ¾ÆÀÌÅÛ µ¥ÀÌÅ¸Á¤º¸°¡ µé¾î°©´Ï´Ù /////////

	/*-------------------------*
	*		 ¾ÆÀÌÅÛ Á¤º¸
	*--------------------------*/
	DWORD	CODE;				//¾ÆÀÌÅÛ ÄÚµå 	
	char	ItemName[32];		//¾ÆÀÌÅÛ ÀÌ¸§ 	

	/*-------------------------*
	*		°øÅë »çÇ×
	*--------------------------*/
	int     Weight;				//¹«°Ô 		
	int     Price;				//°¡°Ý

	/////////////////////////////////////////
	int		Index;				//ÀÎµ¦½º
	int		PotionCount;		//Æ÷¼ÇÄ«¿îÅÍ
	////////////////////////////////////////

	/**¿ø¼Ò**/
	short	Resistance[8];		//¿ø¼Ò¿¡´ëÇÑ ÀúÇ×·Â 
	/********/

	int		Sight;				//½Ã¾ß

	DWORD	Temp0;

	/*-------------------------*
	*		 °ø°Ý¼º´É
	*--------------------------*/
	short	Damage[2];			//°ø°Ý·Â 
	int     Shooting_Range;		//»çÁ¤°Å¸® 
	int     Attack_Speed;		//°ø°Ý¼Óµµ 
	int     Attack_Rating;		//¸íÁß·Â 
	int     Critical_Hit;		//1.5¹è µ¥¹ÌÁöÈ®À²  

	/*-------------------------*
	*		 ¹æ¾î¼º´É
	*--------------------------*/

	float	fAbsorb;			//Èí¼ö·Â 
	int     Defence;			//¹æ¾î·Â 
	float   fBlock_Rating;		//(¹æÆÐ)ºí·°À² 

	/*-------------------------*
	*		 ÀÌµ¿¼º´É
	*--------------------------*/
	float     fSpeed;				//ÀÌµ¿ ¼Óµµ 

	/*-------------------------*
	*		 ÆÈÂî ¼º´É
	*--------------------------*/

	int		Potion_Space;		//¼ÒÄÏ °ø°£ ÇÒ´ç 

	/**Æ¯¼ö´É·Â**/
	float   fMagic_Mastery;     //¸¶¹ý¼÷·Ãµµ 
	float   fMana_Regen;		//¸¶³ª Àç»ý 
	float   fLife_Regen;		//¶óÀÌÇÁ Àç»ý 
	float   fStamina_Regen;	    //½ºÅ×¹Ì³ª Àç»ý 
	float   fIncrease_Life;     //¶óÀÌÇÁ ÃÖ´ëÄ¡»ó½Â 
	float   fIncrease_Mana;     //¸¶³ª ÃÖ´ëÄ¡»ó½Â
	float   fIncrease_Stamina;  //½ºÅ×¹Ì³ª ÃÖ´ëÄ¡»ó½Â

	/************/

	/*-------------------------*
	*		¿ä±¸Æ¯¼º
	*--------------------------*/
	int     Level;				//·¹º§ 
	int     Strength;			//Èû 	
	int     Spirit;				//Á¤½Å·Â 
	int     Talent;				//Àç´É 
	int     Dexterity;			//¹ÎÃ¸¼º 
	int     Health;				//°Ç°­ 

	/*-------------------------*
	*		 È¸º¹¾à
	*--------------------------*/
	short   Mana[2];            //¸¶³ªÈ¸º¹(ÃÖ¼Ò)(ÃÖ´ë)
	short   Life[2];            //¶óÀÌÇÁÈ¸º¹(ÃÖ¼Ò)(ÃÖ´ë) 
	short   Stamina[2];         //½ºÅ×¹Ì³ÊÈ¸º¹(ÃÖ¼Ò)(ÃÖ´ë)

	/*-------------------------*
	*		 .....
	*--------------------------*/
	int		Money;				//º¸À¯ÇÑ µ·
	int     NotUseFlag;         //»ç¿ëºÒ°¡´É ÇÃ·¢

	DWORD	BackUpKey;			//¹é¾÷Çì´õ
	DWORD	BackUpChkSum;		//¹é¾÷ ¾ÆÀÌÅÛ Ã¼Å©¼¶

	short   ScaleBlink[2];		//½ºÄÉÀÏ º¯°æ 
	DWORD	UniqueItem;			//À¯´ÏÅ©
	short	EffectBlink[2];		//»ö»óÇ¥½Ã ÁÖ±â (0) ÀÌÆåÆ® Ã½Å©¼¶(1)
	short	EffectColor[4];		//»ö»óÇ¥½Ã¸ðµå

	DWORD	DispEffect;			//¾ÆÀÌÅÛ Ç¥½Ã ÀÌÆåÆ® (¿¹Á¤)


	/*-------------------------*
	*		Ä³¸¯ÅÍ Æ¯È­¾ÆÀÌÅÛ    (ÇöÀç ¹Ì¼³Á¤)
	*--------------------------*/

	DWORD			JobCodeMask;		//Æ¯È­ Á÷¾÷	(Á÷¾÷º° ºñÆ® ¸¶½ºÅ©)
	sITEM_SPECIAL	JobItem;			//Æ¯È­ ¾ÆÀÌÅÛ ¼º´É

	DWORD   ItemKindCode;		//¾ÆÀÌÅÛ Á¾·ù 0ÀÌ¸é ³ë¸Ö ¾ÆÀÌÅÛ 
	DWORD   ItemKindMask;

	short   ItemAgingNum[2];	//0Àº ¿¡ÀÌÂ¡+¸î 1Àº ¿¡ÀÌÂ¡ÀÌ µÇ°íÀÖ³ª ¾Æ´Ñ°¡?
	short   ItemAgingCount[2];	//0¾ÆÀÌÅÛ ¼÷·Ã Ä«¿îÆ® 1¼÷·ÃÄ¡ ÃÖ´ë 
	short   ItemAgingProtect[2];//¿¡ÀÌÂ¡ º¸È£ 

	short   SpecialItemFlag[2];   //0Àº ÀúÁÖ¾ÆÀÌÅÛ ÇÃ·º 1 Àº Äù½ºÆ®°°Àº °÷¿¡ »ç¿ëµÇ´Â Æ¯¼ö¾ÆÀÌÅÛ

	DWORD	dwCreateTime;		//»ý¼º ½Ã°£

	DWORD	dwTemp[8];			//¿¹ºñ

	BOOL    bUpgraded;
	int	iMixType = 0;
	int	expireTime = 0;
	int	itemType = 0;

	WORD					ItemCraftCode;
	WORD					ItemElement;
	BYTE					ItemSocket[4];
	SocketItem				sSocketData[2];

	int		Param1;
	int		Param2;
	int		Param3;
	int		Param4;
	int		Param5;
	int		Param6;
	int		Param7;
	int		Param8;
	int		Param9;
	int		Param10;
	int		Param11;
	int		Param12;
	int		Param13;
	int		Param14;
	int		Param15;
	int		Param16;
	int		Param17;
	int		Param18;
	int		Param19;
	int		Param20;
	int		Param21;
	int		Param22;
	int		Param23;
	int		Param24;
	int		Param25;
	int		Param26;
	int		Param27;
	int		Param28;
	int		Param29;
	int		Param30;
};

/*----------------------------------------------------------------------------*
*						    struct  ¾ÆÀÌÅÛ
*-----------------------------------------------------------------------------*/
struct sITEM {

	DWORD	CODE;
	char	ItemNameIndex[32];	//¾ÆÀÌÅÛ ÀÌ¸§ 	

	/*-------------------------*
	*	ÃÊ±âÈ­½Ã ¼ÂÆÃÇÑ´Ù
	*--------------------------*/
	char	LastCategory[16];   //ÃÖÁ¾ Ä«Å×°í¸® 		
	int		w;
	int     h;			        //¾ÆÀÌÅÛ »çÀÌÁî 
	char	ItemFilePath[64];   //¾ÆÀÌÅÛ ·Îµå½Ã ÆÄÀÏ °æ·Î 
	DWORD	Class;		        //¾ÆÀÌÅÛÀÇ Á¾·ù
	char    DorpItem[64];       //¶³¾îÁ³À»¶§ ¾ÆÀÌÅÛ 
	DWORD   SetModelPosi;		//¾ÆÀÌÅÛÀÌ ¼ÂÆÃµÉ À§Ä¡ 
	int		SoundIndex;			//¾ÆÀÌÅÛÀÇ »ç¿îµå 
	int     WeaponClass;		//¹ß»çÇüÀÎÁö ±ÙÁ¢ÇüÀÎÁö 


	//--------------------------

	int Flag;			        //¾ÆÀÌÅÛ ÇÃ·¢ 
	int x, y;			        //¾ÆÀÌÅÛÀÌ ±×·ÁÁú ÁÂÇ¥ 
	int SetX, SetY;				//¾ÆÀÌÅÛÀÌ ¼¼ÆÃµÉ °÷ÀÇ ³Ö¾îÁØ´Ù 

	LPDIRECT3DTEXTURE9 lpItem;
	int		ItemPosition;       //¾ÆÀÌÅÛÀÌ ÀÎº¥Åä¸®»ó¿¡ Á¸ÀçÇÒ¶§ Æ÷Áö¼ÇÀ» ÁØ´Ù (¿À¸¥¼Õ , ¿Þ¼Õ ,¾ç¼Õ ,°ª¿Ê ..)

	int     PotionCount;		//¹°¾àÀÏ¶§¸¸ Ä«¿îÆ®ÇÑ´Ù 
	int     NotUseFlag;			//¿ä±¸Ä¡°¡ ÃæÁ·µÇÁö ¾ÊÀ»¶§ ÇÃ·¢À» ÁØ´Ù 
	int     SellPrice;			//¾ÆÀÌÅÛÀÌ ÆÈ¸± °¡°Ý

	int     OldX, OldY;          //¾ÆÀÌÅÛÀÌ ¿¹Àü¿¡ ¼¼ÆÃ‰ç´ø ÁÂÇ¥  
	LPDIRECT3DTEXTURE9	lpTempItem;
	//int		LimitTimeFlag;		    //À¯Åë±âÇÑ 

	sITEMINFO sItemInfo;

};

struct sITEMPRICE {
	int PureSellPrice;
	int SellPrice;
	int RepairCost;

};

//¾ÆÀÌÅÛ ¿ä±¸Ä¡ ÇÃ·¢ 
struct sITEMREQUIRE {

	int     rLevel;				//·¹º§ 
	int     rStrength;			//Èû 	
	int     rSpirit;			//Á¤½Å·Â 
	int     rTalent;			//Àç´É 
	int     rDexterity;			//¹ÎÃ¸¼º 
	int     rHealth;			//°Ç°­ 

};
/*----------------------------------------------------------------------------*
*						    class   ¾ÆÀÌÅÛ
*-----------------------------------------------------------------------------*/
class cITEM
{

public:

	char* DropItemPath;
	char* CharSetItemPath;

	int MatItemInfoBox;

	int MatItemInfoBox_TopLeft;
	int MatItemInfoBox_TopRight;
	int MatItemInfoBox_TopCenter;

	int MatItemInfoBox_BottomLeft;
	int MatItemInfoBox_BottomRight;
	int MatItemInfoBox_BottomCenter;

	int MatItemInfoBox_Left;
	int MatItemInfoBox_Right;
	int MatItemInfoBox_Center;


	LPDIRECT3DTEXTURE9	AgingBar;
	LPDIRECT3DTEXTURE9	AgingGage;
	LPDIRECT3DTEXTURE9	AgingBar2;

public:
	cITEM();
	~cITEM();

	void Init();
	void Load();
	void Release();
	void Close();
	void Draw();
	void Main();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	void RButtonDown(int x, int y);
	void RButtonUp(int x, int y);
	void KeyDown();


	int ShowItemInfo(sITEM* pItem, int Flag, int Index = 0); //Á¤º¸¸¦ Ã£´Â´Ù  1Àº »óÁ¡ ¾ÆÀÌÅÛ 2´Â ÀÎº¥ ¾ÆÀÌÅÛ 

	int ShowItemInfo2(sITEM* pItem, int Flag, int Index = 0); //Á¤º¸¸¦ Ã£´Â´Ù  1Àº »óÁ¡ ¾ÆÀÌÅÛ 2´Â ÀÎº¥ ¾ÆÀÌÅÛ (µÎ°³·Î ³ª´³´Ù)

	int DrawItemText(); //¾ÆÀÌÅÛ Á¤º¸ ÅØ½ºÆ® 

	POINT SetTextXY(int x, int y, int len); //ÅØ½ºÆ®°¡ ³õÀÏ À§Ä¡¸¦ º¸Á¤ÇÑ´Ù  

	int SearchSpecialItemJob(DWORD SpecialJob_CODE); //Æ¯È­ Ä³¸¯ÅÍ Àü¿ë ¾ÆÀÌÅÛ  

	int GetInfoBoxSize(sITEM* pItem, int Col);
	int GetInfoBoxSize2(sITEM* pItem, int Col);

	/////////////////// ¾ÆÀÌÅÛ Å×ÀÌºíÀÇ Á¶ÀÛÀ» ¹æÁöÇÑ´Ù 
	int CheckItemTable();

	int GetJobCode(DWORD SpecialJob_CODE);


	/////// ¾ÆÀÌÅÛ À¯Åë±âÇÑ 
	int GetItemLimitTime(sITEM* pItem);

	//¾ÆÀÌÅÛÀÇ ÁÂÇ¥¸¦ ¾ò¾î¿Â´Ù
	void GetMousePos(int* MouseX, int* MouseY);

	//°¡Á¦ Å×½ºÆ®
	void SetItemInfo(char* Buff);
};

extern cITEM cItem;
extern sITEM sItem[MAX_ITEM];

extern sITEM TempItem;      //Àá½Ã ÀúÀåµÉ ¾ÆÀÌÅÛ ±¸Á¶Ã¼ º¯¼ö 
extern sITEM MouseItem;	    //¸¶¿ì½º¿¡ ¿Å°ÜÁú ¾ÆÀÌÅÛ 

extern int sinShowItemInfoFlag;  //¾ÆÀÌÅÛ Á¤º¸¸¦ º¸¿©ÁØ´Ù 
extern DWORD sinItemTime;   //¾ÆÀÌÅÛ À¯Åë±â°£ 

extern int NotSell_Item_CODECnt;
extern int NotSell_Item_MASKCnt;
extern int NotSell_Item_KINDCnt;

extern int NotDrow_Item_CODECnt;
extern int NotDrow_Item_MASKCnt;
extern int NotDrow_Item_KINDCnt;

extern int NotSet_Item_CODECnt;
extern int NotSet_Item_MASKCnt;
extern int NotSet_Item_KINDCnt;

extern DWORD NotSell_Item_CODE[];
extern DWORD NotSell_Item_MASK[];
extern DWORD NotSell_Item_KIND[];

extern DWORD NotDrow_Item_CODE[];
extern DWORD NotDrow_Item_MASK[];
extern DWORD NotDrow_Item_KIND[];

extern DWORD NotSet_Item_CODE[];
extern DWORD NotSet_Item_MASK[];
extern DWORD NotSet_Item_KIND[];