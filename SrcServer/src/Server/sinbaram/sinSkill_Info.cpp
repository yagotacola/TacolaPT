﻿// *************************************************************************** //
//
//									MECÂNICO
//
// *************************************************************************** //
#include <Skills/Skills.h>
#include "sinSkill_InfoIni.h"
short E_Shield_BlockRate[10] = { 12,14,16,18,20,22,24,26,28,30 };
short E_Shield_UseTime[10] = { 30,50,70,90,110,130,150,170,190,210 };
short E_Shield_UseMana[10] = { 12,14,17,20,23,26,30,34,39,44 };

short Mechanic_Bomb_Damage[10][2] = { { 5,29 },{ 6,33 },{ 7,37 },{ 8,42 },{ 9,47 },{ 10,53 },{ 11,60 },{ 12,68 },{ 13,77 },{ 14,87 } };
short Mechanic_Bomb_Attack_Range[10] = { 50,53,56,59,62,64,66,68,70,72 };
short Mechanic_Bomb_UseMana[10] = { 8,10,12,14,17,20,23,26,29,33 };

short P_Absorb[10][2] = { { 5,10 },{ 8,16 },{ 12,24 },{ 16,32 },{ 20,40 },{ 25,50 },{ 29,54 },{ 34,58 },{ 39,72 },{ 40,80 } };
short P_Absorb_UseTime[10] = { 30,50,70,90,110,130,150,170,190,210 };
short P_Absor_bUseMana[10] = { 20,24,28,32,36,40,44,48,52,56 };

short PlusPoison[10] = { 9,17,24,30,35,39,42,44,45,46 };

short G_Smash_Attack_Rate[10] = { 60,70,80,90,100,120,140,160,180,200 };
short G_Smash_Attack_Rage[10] = { 8,16,24,32,40,48,56,64,72,80 };
short G_Smash_UseMana[10] = { 22,25,28,31,34,38,42,46,50,54 };

short Maximize_Damage[10] = { 15,20,25,30,35,40,45,50,55,60 };
short Maximize_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
short Maximize_UseMana[10] = { 26,28,30,33,36,39,43,47,51,56 };

short Automation_Damage[10] = { 30,35,40,44,48,52,55,58,63,66 };
short Automation_Speed[10] = { 1,1,1,1,1,2,2,2,2,2 };
short Automation_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
short Automation_UseMana[10] = { 24,27,30,33,36,39,42,45,48,51 };

short Spark_Damage[10][2] = { { 30,82 },{ 33,89 },{ 36,96 },{ 38,103 },{ 40,110 },{ 42,117 },{ 44,123 },{ 46,129 },{ 48,135 },{ 50,141 } };
short Spark_Area[10] = { 50,54,58,62,66,70,74,78,82,86 };
short Spark_UseMana[10] = { 26,28,31,34,37,40,44,46,50,55 };

short Metal_Armor_Defense[10] = { 6,11,16,20,24,28,31,34,36,38 };
short Metal_Armor_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
short Metal_Armor_UseMana[10] = { 32,35,38,41,44,48,52,56,60,64 };

short Grand_Smash_AttackRate[10] = { 60,80,100,120,140,160,180,200,220,240 };
short Grand_Smash_Damage[10] = { 43,49,55,61,67,73,79,85,91,97 };
short Grand_Smash_UseMana[10] = { 26,29,32,35,38,41,44,47,50,53 };

short M_Weapon_Mastey[10] = { 5,9,13,17,21,25,29,33,37,41 };

short Spark_Shield_Damage[10] = { 30,42,54,66,78,90,102,114,126,138 };
short Spark_Shield_Defense[10] = { 8,16,24,32,40,48,56,64,72,80 };
short Spark_Shield_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
short Spark_Shield_UseMana[10] = { 34,36,38,41,44,47,51,55,59,64 };

short Impulsion_LightingDamage[10][2] = { { 140,180 },{ 150,190 },{ 160,200 },{ 170,210 },{ 180,220 },{ 190,230 },{ 200,240 },{ 210,250 },{ 220,260 },{ 230,270 } };
short Impulsion_Range[10] = { 130,135,140,145,150,155,160,165,170,175 };
short Impulsion_LightingNum[10] = { 3,3,4,4,5,5,6,6,7,7 };
short Impulsion_UseMana[10] = { 35,38,40,43,46,49,53,57,61,65 };

short Compulsion_AddAbsorb[10] = { 5,7,9,11,13,15,17,19,21,23 };
short Compulsion_Area[10] = { 150,160,170,180,190,200,210,220,230,240 };
short Compulsion_Time[10] = { 16,24,32,40,48,57,66,75,84,93 };
short Compulsion_UseMana[10] = { 50,54,58,62,66,70,74,78,82,86 };

short Magnetic_Sphere_AddDamage[10][2] = { { 30,40 },{ 40,50 },{ 50,60 },{ 60,70 },{ 70,80 },{ 80,90 },{ 90,100 },{ 100,110 },{ 110,120 },{ 120,130 } };
short Magnetic_Sphere_Area[10] = { 80,80,85,85,90,90,95,95,100,100 };
short Magnetic_Sphere_AttackDelay[10] = { 6,6,6,5,5,5,4,4,4,3 };
short Magnetic_Sphere_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
short Magnetic_Sphere_UseMana[10] = { 60,65,70,75,80,85,90,95,100,105 };

short Metal_Golem_Damage[10][2] = { { 95,115 },{ 100,120 },{ 105,125 },{ 110,130 },{ 115,135 },{ 120,140 },{ 125,145 },{ 130,150 },{ 135,155 },{ 140,160 } };
short Metal_Golem_Hit[10] = { 660,680,700,720,740,760,780,800,820,840 };
short Metal_Golem_Defense[10] = { 355,400,445,490,535,580,625,670,715,760 };
short Metal_Golem_Life[10] = { 4100,4300,4500,4700,4900,5100,5300,5500,5700,5900 };
short Metal_Golem_UseMana[10] = { 60,64,68,72,76,80,84,88,92,96 };


// assassina
int Stinger_Damage[10] = { 33, 36, 39, 42, 45, 48, 51, 54, 57, 60 };
int Stinger_UseMana[10] = { 8, 10,12, 15,18, 21,25, 29, 33, 38 };
int D_Mastery_DamagePercent[10] = { 4,8,12,16,20,24,28,32,36,40 };
int Double_Blow_Damage[10] = { 52, 55, 58, 61, 64, 67, 70, 73, 76, 79 };
int DoubleBlow_UseMana[10] = { 14,16,18,20,23,26,29,32,35,39 };
int Wisp_UseTime[10] = { 10, 10, 10, 12, 12, 12, 14, 14, 14, 16 };
int Wisp_Reduction[10] = { 6, 8, 10, 12, 14, 16, 18, 20, 22, 24 };
int Wisp_UseMana[10] = { 18,20,22,24,26,29,33,37,41,45 };
int VenomThorn_Time[10] = { 6, 6, 7, 7, 8, 8, 9, 10, 11, 12 };
int VenomThorn_Chance[10] = { 40, 45, 50, 55, 60, 65, 70, 75, 80, 85 };
int VenomThorn_Damage[10] = { 50,54,58,62,66,70,74,78,82,86 };
int VenomThorn_UseMana[10] = { 22,25,28, 31, 34, 38, 42, 46, 50, 54 };
int Alas_Time[10] = { 120, 140, 160, 180, 200, 220, 240, 260, 280, 300 };
int Alas_EvasionPercent[10] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 12 };
int Alas_UseMana[10] = { 26, 28, 30, 33, 36, 39, 43, 47, 51, 56 };
int SoulChock_Range[10] = { 70, 75, 80, 85, 90, 95, 100, 105, 110, 115 };
int SoulChock_Time[10] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 12 };
int SoulChock_UseMana[10] = { 26, 28, 30, 33, 36, 39, 42, 45, 49, 53 };
int A_Mastery_AddPercent[10] = { 11,13,15,17,19,21,23,24,25,26 };
int A_Mastery_AddPercent2[10] = { 11,13,15,17,19,21,23,24,25,26 };
int SoreSword_Damage[10] = { 84, 88, 92, 96, 100, 104, 108, 112, 116, 120 };
int SoreSword_UseMana[10] = { 28, 31, 34, 37, 40, 43, 46, 49, 52, 55 };
int BeatUp_Damage[10] = { 55, 60, 65, 70, 75, 80, 85, 90, 95, 100 };
int BeatUp_Area[10] = { 80, 80, 80, 80, 80, 80, 80, 80, 80, 80 };
int BeatUp_UseMana[10] = { 32, 34, 36, 38, 41, 44, 47, 50, 53, 56 };
int Inpes_Time[10] = { 90, 110, 130, 150, 170, 190, 210, 230, 250, 270 };
int Inpes_Speed[10] = { 2,4,6,8,10,11,12,13,14,15 };
int Inpes_UseMana[10] = { 32, 35, 38, 41, 44, 48, 52, 56, 60, 64 };
int Blind_Time[10] = { 90, 110, 130, 150, 170, 190, 210, 230, 250, 270 };
int Blind_Damage[10] = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };
int Blind_Range[10] = { -25,-30,-35,-40,-45,-50,55 };
int Blind_UseMana[10] = { 40, 43, 46, 49, 52, 55, 58, 62, 66, 70 };
int Polluted_Damage2[10][2] = { { 43,47 },{ 46,51 } ,{ 49,55 } ,{ 52,59 } ,{ 55,62 } ,{ 58,65 } ,{ 61,68 } ,{ 64,72 } ,{ 67,76 } ,{ 70,80 } };
int Polluted_Area[10] = { 90, 94, 98, 102, 106, 110, 114, 118, 112, 116 };
int Polluted_Time[10] = { 5, 6, 6, 7, 7, 8, 8, 9, 9, 10 };
int Polluted_AttackNum[10] = { 3,3,4,4,5,5,6,6,7,7 };
int Polluted_UseMana[10] = { 50, 53, 56, 59, 62, 65, 68, 71, 74, 77 };
int FrostWind_Damage[10] = { 49, 53, 57, 61, 65, 69, 73, 77, 81, 85 };
int FrostWind_UseMana[10] = { 50, 53, 56, 59, 62, 65, 68, 71, 74, 77 };
int F_Mastery_Critical[10] = { 9,11,12,13,14,15,16,17,18,19 };
int PastingShadow_Damage[10] = { 47, 52, 57, 62, 67, 72, 77, 82, 87, 92 };
int PastingShadow_UseMana[10] = { 52, 55, 58, 61, 64, 67, 70, 73, 76, 79 };
int ShadowBomb_Damage2[10][2] = { { 300,350 },{ 320,380 } ,{ 340,410 } ,{ 360,440 } ,{ 380,470 } ,{ 400,500 } ,{ 420,530 } ,{ 440,560 } ,{ 460,590 } ,{ 480,620 } };
int ShadowBomb_AttackNum[10] = { 5, 5, 6, 6, 7, 7, 8, 8, 9, 9 };
int ShadowBomb_Area[10] = { 80, 90, 100, 110, 120, 130, 140, 150, 160, 170 };
int ShadowBomb_UseMana[10] = { 55, 58, 61, 64, 67, 70, 73, 76, 79, 82 };
int RisingSlash_Damage[10] = { 120, 160, 200, 240, 280, 320, 360, 400, 440, 480 };
int RisingSlash_UseMana[10] = { 60, 63, 66, 69, 72, 75, 78, 81, 84, 87 };
int ViolenceStab_Damage[10] = { 40, 80, 120, 160, 200, 240, 280, 320, 360, 400 };
int ViolenceStab_UseMana[10] = { 60, 63, 66, 69, 72, 75, 78, 81, 84, 87 };
int Storm_Damage[10] = { 100, 130, 160, 190, 220, 260, 300, 340, 380, 420 };
int Storm_UseMana[10] = { 83, 85, 87, 89, 91, 93, 95, 97, 99, 101 };

// assassina
// *************************************************************************** //
//
//									LUTADOR
//
// *************************************************************************** //

short Melee_Mastery_DamagePercent[10] = { 6,10,14,18,21,24,26,28,30,32 };

short PlusFire[10] = { 9,17,24,30,35,39,42,44,45,46 };

short Raving_Damage[10] = { 13,16,19,22,25,28,31,34,37,40 };
short Ravind_Speed[10] = { 2,2,2,3,3,3,4,4,4,4 };
float Raving_UseLife[10] = { 1.f,1.3f,1.6f,1.9f,2.2f,2.5f,2.8f,3.1f,3.4f,3.7f };
short Raving_UseMana[10] = { 14,16,18,20,22,24,26,29,32,35 };

short Impact_Attack_Rating[10] = { 20,40,60,80,100,120,140,160,180,200 };
short Impact_Damage[10] = { 20,25,29,33,37,41,45,49,52,55 };
short Impact_UseMana[10] = { 18,20,22,24,26,29,33,37,41,45 };

short T_Impact_Damage[10] = { 35,40,25,30,35,25,30,35,40,45 };
short T_Impact_Hit[10] = { 1,1,2,2,2,3,3,3,3,3 };
short T_Impact_UseMana[10] = { 22,24,26,29,32,35,38,41,44,47 };

short B_Swing_Damage[10] = { 10,16,22,28,34,40,45,50,55,60 };
short B_Swing_Critical[10] = { 3,7,10,13,16,19,21,24,27,30 };
short B_Swing_UseMana[10] = { 24,26,28,31,34,38,42,47,52,58 };

short Roar_Range[10] = { 50,60,70,80,90,100,108,116,124,130 };
short Roar_Time[10] = { 4,6,8,10,12,14,16,18,20,22 };
short Roar_UseMana[10] = { 26,28,30,33,36,39,42,45,49,53 };

short R_Zecram_Damage[10] = { 14,28,42,56,70,84,98,112,126,140 };
short R_Zecram_UseMana[10] = { 29,31,33,36,39,42,45,49,53,58 };

short Concentration_AttackRate[10] = { 16,32,48,64,80,96,112,128,144,160 };
short Concentration_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
short Concentration_UseMana[10] = { 35,38,41,44,47,50,53,56,59,62 };

short A_Crash_Damage[10] = { 50,55,60,65,70,75,80,85,90,95 };
short A_Crash_AttackRate[10] = { 5,10,15,20,25,30,35,40,45,50 };
short A_Crash_UseMana[10] = { 32,34,36,38,41,44,47,50,53,56 };

short Swift_Axe_Speed[10] = { 2,4,6,8,10,11,12,13,14,15 };
short Swift_Axe_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
short Swift_Axe_UseMana[10] = { 40,44,48,52,56,60,64,68,72,76 };

short B_Crash_Damage[10] = { 50,55,60,65,70,75,80,85,90,95 };
short B_Crash_DemonDamage[10] = { 20,25,30,35,40,45,50,55,60,65 };
short B_Crash_UseMana[10] = { 34,36,38,41,44,47,50,53,56,59 };

short Destoryer_DamagePercent[10] = { 15,30,45,60,75,90,105,120,135,150 };
short Destoryer_AddCritical[10] = { 10,12,14,16,18,20,22,24,26,28 };
short Destoryer_UseMana[10] = { 46,48,50,52,54,56,58,60,62,64 };

short Berserker_AddAttack[10] = { 20,24,28,32,36,40,44,48,52,56 };
short Berserker_SubAbsorb[10] = { -2,-4,-6,-8,-10,-12,-14,-16,-18,-20 };
short Berserker_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
short Berserker_UseMana[10] = { 52,55,58,61,64,67,70,73,76,79 };

short Cyclone_Strike_DamagePercent[10] = { 15,22,29,36,43,50,57,64,71,78 };
short Cyclone_Strike_AreaDamage[10][2] = { { 120,150 },{ 135,165 },{ 150,180 },{ 165,195 },{ 180,210 },{ 195,225 },{ 210,240 },{ 225,255 },{ 240,270 },{ 255,285 } };
short Cyclone_Strike_AttackNum[10] = { 5,5,6,6,7,7,8,8,9,9 };
short Cyclone_Strike_Area[10] = { 100,105,110,115,120,125,130,135,140,145 };
short Cyclone_Strike_UseMana[10] = { 50,53,56,59,62,65,68,71,74,77 };

short Boost_Health_Life[10] = { 10,20,30,40,50,70,90,110,130,150 };

// *************************************************************************** //
//
//									PIKE
//
// *************************************************************************** //

short Pike_Wind_Damage[10][2] = { { 3,20 },{ 5,27 },{ 7,34 },{ 9,41 },{ 11,48 },{ 13,52 },{ 15,59 },{ 17,66 },{ 19,73 },{ 21,80 } };
short Pike_Wind_Push_Lenght[10] = { 70,75,80,85,90,95,100,105,110,120 };
short Pike_Wind_UseMana[10] = { 14,16,18,20,23,26,29,32,35,39 };

short PlusIce[10] = { 8,15,21,26,30,33,36,39,42,45 };

short Critical_Hit_Critical[10] = { 15,19,23,26,29,32,34,36,38,40 };
short Critical_Hit_UseMana[10] = { 14,16,18,20,23,26,29,33,37,41 };

short Jumping_Crash_UseMana[10] = { 16,18,20,23,26,29,32,35,39,43 };
short Jumping_Crash_Attack_Rating[10] = { 10,20,30,40,50,55,60,65,70,75 };
short Jumping_Crash_Damage[10] = { 40,50,60,70,80,90,100,110,120,130 };

short G_Pike_Damage[10][2] = { { 10,40 },{ 13,45 },{ 16,50 },{ 19,55 },{ 22,60 },{ 25,65 },{ 28,70 },{ 31,75 },{ 34,80 },{ 37,85 } };
short G_Pike_Range[10] = { 80,82,84,86,88,90,92,94,96,98 };
short G_Pike_UseMana[10] = { 19,21,23,25,28,31,34,38,42,46 };
short G_Pike_Time[10] = { 1,1,2,2,2,3,3,4,4,5 };

short Tornado_Damage[10] = { 20,29,37,44,50,55,59,62,64,65 };
short Tornado_Stun[10] = { 8,16,24,32,40,48,56,64,72,80 };
short Tornado_Range[10] = { 50,53,56,59,62,65,68,71,74,77 };
short Tornado_UseMana[10] = { 23,25,27,29,32,35,38,42,46,51 };

short W_D_Mastery_Block[10] = { 2,4,6,8,10,11,12,13,14,15 };

short Expansion_Size[10] = { 30,38,46,54,62,70,78,86,94,102 };
short Expansion_Damage[10] = { 30,35,40,45,50,55,60,65,70,75 };
short Expansion_UseMana[10] = { 26,28,30,33,36,39,43,47,50,53 };

short VenomSpear_Damage[10][2] = { { 17,20 },{ 19,22 },{ 21,24 },{ 23,26 },{ 25,28 },{ 27,30 },{ 29,32 },{ 31,34 },{ 33,36 },{ 35,38 } };
short VenomSpear_Num[10] = { 3,3,3,4,4,4,5,5,5,5 };
short VenomSpear_Time[10] = { 5,5,5,5,6,6,6,6,7,7 };
short VenomSpear_Range[10] = { 90,94,98,102,106,110,114,118,122,126 };
short VenomSpear_UseMana[10] = { 30,33,36,39,42,45,48,51,54,57 };

short Vanish_Damage[10] = { 10,20,30,40,50,60,70,80,90,100 };
short Vanish_Range[10] = { -40,-46,-52,-58,-64,-70,-75,-80,-85,-90 };
short Vanish_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
short Vanish_UseMana[10] = { 40,43,46,49,52,55,58,62,66,70 };

short Critical_Mastery_Critical[10] = { 9,11,12,13,14,15,16,17,18,19 };

short Chain_Lance_Damage[10] = { 10,15,20,25,30,35,40,45,50,55 };
short Chain_Lance_UseMana[10] = { 32,35,38,41,44,47,50,53,56,59 };

short Assassin_Eye_AddCritical[10] = { 10,14,18,22,26,30,34,38,42,46 };
short Assassin_Eye_M_SubCritical[10] = { -4,-5,-6,-7,-8,-9,-10,-11,-12,-13 };
short Assassin_Eye_Time[10] = { 12,13,14,15,16,17,18,19,20,21 };
short Assassin_Eye_UseMana[10] = { 47,49,51,53,55,57,59,61,63,65 };

short Charging_Strike_DamagePercent[10] = { 10,15,20,25,30,35,40,45,50,55 };
short Charging_Strike_CharingDamagePercent[10] = { 30,45,60,75,90,105,120,135,150,165 };
short Charging_Strike_Time[10] = { 9,18,27,36,45,54,63,72,81,90 };
short Charging_Strike_UseMana[10] = { 48,51,54,57,60,63,66,69,72,75 };

short Vague_EvasionPercent[10] = { 3,6,9,11,13,15,17,19,21,22 };
short Vague_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
short Vague_UseMana[10] = { 55,58,61,64,67,70,73,76,79,82 };

short Shadow_Master_DamagePercent[10] = { 10,15,20,25,25,30,35,40,40,45 };
short Shadow_Master_ShadowNum[10] = { 3,3,4,4,5,5,6,6,7,7 };
short Shadow_Master_UseMana[10] = { 52,55,58,61,64,67,70,73,76,79 };

// *************************************************************************** //
//
//									ARQUEIRA
//
// *************************************************************************** //

short Scout_Hawk_Attack_Rate[10] = { 10,20,30,40,50,60,70,80,90,100 };
short Scout_Hawk_UseTime[10] = { 5,6,7,8,9,10,11,12,13,14 };
short Scout_Hawk_UseMana[10] = { 14,16,18,20,23,26,30,34,39,44 };

short S_Mastery_DamagePercent[10] = { 6,12,18,24,30,36,42,48,54,60 };

short Wind_Arrow_Speed[10] = { 2,2,2,3,3,3,4,4,4,5 };
short Wind_Arrow_Damage[10] = { 15,24,32,39,45,50,54,57,59,60 };
short Wind_Arrow_UseMana[10] = { 12,14,16,18,20,23,26,29,32,35 };

short Perfect_Aim_Attack_Rate[10] = { 26,27,29,32,36,41,47,54,62,71 };
short Perfect_Aim_Damage[10] = { 4,6,8,10,12,14,16,18,19,20 };
short Perfect_Aim_Damage_LV[10] = { 8,8,8,8,7,7,7,6,6,6 };
short Perfect_Aim_UseMana[10] = { 14,16,18,20,22,25,28,31,35,39 };

short D_Eye_Attack_Rate[10] = { 10,20,30,40,50,60,70,80,90,100 };

short Falcon_Damage[10][2] = { { 10,36 },{ 12,40 },{ 14,44 },{ 16,48 },{ 18,52 },{ 20,56 },{ 22,60 },{ 24,64 },{ 26,68 },{ 28,72 } };
short Falcon_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
short Falcon_UseMana[10] = { 24,26,28,30,33,36,39,43,47,52 };

short A_Rage_ArrowNum[10] = { 2,3,4,5,6,7,8,9,10,11 };
short A_Rage_Damage[10] = { 6,6,6,6,5,5,5,5,4,4 };
short A_Rage_Area[10] = { 55,59,63,67,70,73,76,79,82,85 };
short A_Rage_UseMana[10] = { 24,26,28,31,34,37,40,44,48,53 };

short Avalanche_Speed[10] = { 1,1,1,2,2,2,3,3,3,4 };
short Avalanche_Damage[10] = { 15,19,23,27,31,35,39,43,47,51 };
short Avalanche_ArrowNum[10] = { 3,3,3,4,4,4,5,5,5,6 };
short Avalanche_UseMana[10] = { 25,28,31,34,38,42,46,51,56,61 };

short Elemental_Shot_Fire[10][2] = { { 12,22 },{ 17,27 },{ 22,32 },{ 27,37 },{ 32,42 },{ 37,47 },{ 42,52 },{ 47,57 },{ 52,62 },{ 57,67 } };
short Elemental_Shot_Lightning[10][2] = { { 5,17 },{ 9,22 },{ 13,27 },{ 17,32 },{ 21,37 },{ 25,42 },{ 29,47 },{ 33,52 },{ 37,57 },{ 41,62 } };
short Elemental_Shot_UseMana[10] = { 27,29,31,33,36,39,42,45,48,51 };

short Golden_Falcon_Damage[10] = { 120,125,130,135,140,145,150,155,160,165 };
float Golden_Falcon_LifeRegen[10] = { 1.0f,1.3f,1.6f,1.9f,2.2f,2.5f,2.8f,3.1f,3.4f,3.7f };
short Golden_Falcon_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
short Golden_Falcon_UseMana[10] = { 33,36,39,42,46,50,54,59,64,70 };

short BombShot_Damage[10] = { 5,10,15,20,25,30,35,40,45,50 };
short BombShot_DemonDamage[10] = { 5,10,15,20,25,30,35,40,45,50 };
short BombShot_AddDamage[10][2] = { { 15,27 },{ 18,31 },{ 21,35 },{ 24,39 },{ 27,43 },{ 30,47 },{ 33,51 },{ 36,55 },{ 39,59 },{ 42,63 } };
short BombShot_Area[10] = { 82,84,86,88,90,92,94,96,98,100 };
short BombShot_UseMana[10] = { 28,31,34,37,40,43,46,49,52,53 };

short Perforation_Damage[10] = { 10,16,22,28,34,40,46,52,58,64 };
short Perforation_Critical[10] = { 3,6,9,12,15,18,21,24,27,30 };
short Perforation_UseMana[10] = { 28,31,34,37,40,43,46,49,52,53 };
short Perforation_Attack_Range[10] = { 30,34,38,42,46,50,54,58,62,66 };

short Recall_Wolverin_Damage[10][2] = { { 50,75 },{ 55,80 },{ 60,85 },{ 65,90 },{ 70,95 },{ 75,100 },{ 80,105 },{ 85,110 },{ 90,115 },{ 95,120 } };
short Recall_Wolverin_Hit[10] = { 900,1000,1100,1200,1300,1400,1500,1600,1700,1800 };
short Recall_Wolverin_Defense[10] = { 1000,1050,1100,1150,1200,1250,1300,1350,1400,1450 };
short Recall_Wolverin_Life[10] = { 2000,2200,2400,2600,2800,3000,3200,3400,3600,3800 };
short Recall_Wolverin_UseMana[10] = { 52,56,60,64,68,72,76,80,84,88 };

//short Evasion_Mastery_AddPercent[10] = { 10,14,18,22,26,30,34,38,40,43 };
short Evasion_Mastery_AddPercent[10] = { 7,9,11,13,15,17,19,21,23,25 };
float Evasion_Mastery_AddSpeed[10] = { 1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f };
short Evasion_Mastery_AddReduce[10] = { 7,14,21,28,35,42,49,56,63,70 };
short Evasion_Mastery_Time[10] = { 300,300,300,300,300,300,300,300,300,300 };
short Evasion_Mastery_UseMana[10] = { 43,46,49,52,55,58,61,64,67,70 };

short Phoenix_Shot_DamagePercent[10] = { 50,62,74,86,98,110,122,134,146,158 };
short Phoenix_Shot_Time[10] = { 9,18,27,36,45,54,63,72,81,90 };
short Phoenix_Shot_UseMana[10] = { 33,35,37,40,43,46,50,54,58,62 };

short Force_Of_Nature_AddDamage[10] = { 12,15,18,21,24,27,30,33,36,39 };
short Force_Of_Nature_AddHit[10] = { 20,30,40,50,60,70,80,90,100,110 };
short Force_Of_Nature_FalconAddDamage[10] = { 22,26,30,34,38,42,46,50,54,58 };
short Force_Of_Nature_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
short Force_Of_Nature_UseMana[10] = { 51,54,57,60,63,66,69,72,75,78 };

// *************************************************************************** //
//
//									CAVALEIRO
//
// *************************************************************************** //

short Sword_Blast_UseMana[10] = { 8,10,12,15,18,21,25,29,33,38 };
short Sword_Blast_Damage[10][2] = { { 12,16 },{ 15,20 },{ 18,24 },{ 21,28 },{ 24,32 },{ 27,36 },{ 30,40 },{ 33,44 },{ 36,48 },{ 39,52 } };
short Sword_Blast_ShootingRange[10] = { 80,84,88,92,96,100,104,108,112,116 };

short HolyBody_UseMana[10] = { 18,21,24,27,30,34,38,42,46,50 };
short HolyBody_Absorb[10] = { 8,12,16,19,22,25,27,29,31,33 };
short HolyBody_Time[10] = { 30,50,70,90,110,130,150,170,190,210 };

short P_Traning_Stamina[10] = { 5,8,11,14,17,20,23,26,28,30 };

short D_Crash_UseMana[10] = { 18,20,22,24,27,30,33,36,39,42 };
short D_Crash_Damage[10] = { 10,14,18,22,25,28,31,34,37,40 };
short D_Crash_Critical[10] = { 3,3,4,4,5,5,6,6,7,7 };

short Holy_Valor_Damage[10] = { 18,22,26,30,34,38,42,46,50,54 };
short Holy_Valor_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
short Holy_Valor_Mana[10] = { 23,26,29,32,35,38,41,44,47,50 };

short Brandish_Range[10] = { 70,72,74,76,78,80,82,84,86,88 };
short Brandish_Damage[10] = { 10,16,22,28,34,40,46,52,58,64 };
short Brandish_Mana[10] = { 22,24,26,28,30,33,36,39,42,45 };

short Piercing_Damage[10] = { 10,17,24,31,38,45,52,59,66,73 };
short Piercing_Attack_Rating[10] = { 40,50,60,70,80,90,100,110,120,130 };
short Piercing_Mana[10] = { 24,26,28,30,32,34,36,38,40,42 };

short Drastic_Spirit_Defense[10] = { 6,9,12,15,18,20,22,23,24,25 };
short Drastic_Spirit_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
short Drastic_Spirit_Mana[10] = { 25,27,29,32,35,38,41,45,49,54 };

short Sword_Mastery_DamagePercent[10] = { 11,14,17,20,23,26,29,32,35,38 };

short D_Inhalation_Life[10] = { 9,18,27,36,45,54,63,72,81,90 };
short D_Inhalation_Block[10] = { 2,2,3,3,4,4,5,5,6,6 };
short D_Inhalation_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
short D_Inhalation_UseMana[10] = { 30,33,36,39,43,47,51,55,60,65 };

short H_Incantation_Success[10] = { 45,54,62,69,75,80,84,88,92,96 };
short H_Incantation_AddLife[10] = { 100,120,140,160,180,200,220,240,260,280 };
short H_Incantation_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
short H_Incantation_UseMana[10] = { 36,39,42,45,48,52,56,60,65,70 };

short Grand_Cross_Damage[10] = { 35,40,45,50,55,60,65,70,75,80 };
short Grand_Cross_AttackRate[10] = { 35,40,45,50,55,60,65,70,75,80 };
short Grand_Cross_UndeadDamage[10] = { 5,10,15,20,25,30,35,40,45,50 };
short Grand_Cross_UseMana[10] = { 28,31,34,37,40,43,46,49,52,55 };

short Sword_Of_Justice_DamagePercent[10] = { 100,110,120,130,140,150,160,170,180,190 };
short Sword_Of_Justice_Area[10] = { 130,135,140,145,150,155,160,165,170,175 };
short Sword_Of_Justice_UseMana[10] = { 50,53,56,59,62,65,68,71,74,77 };

short Godly_Shield_AbsorbPercent[10] = { 2,4,6,8,10,12,14,16,18,20 };
short Godly_Shield_Time[10] = { 100,110,120,130,140,150,160,170,180,190 };
short Godly_Shield_UseMana[10] = { 47,50,53,56,59,62,65,68,71,74 };

short God_Bless_AddDamage[10] = { 40,50,60,70,80,90,100,110,120,130 };
short God_Bless_Time[10] = { 120,130,140,150,160,170,180,190,200,210 };
short God_Bless_UseMana[10] = { 57,60,63,66,69,72,75,78,81,84 };

short Divine_Piercing_DamagePercent[10] = { 10,14,18,22,20,25,30,35,30,35 };
short Divine_Piercing_AddHit[10] = { 20,30,40,50,50,60,70,80,80,90 };
short Divine_Piercing_AttackNum[10] = { 3,3,3,3,5,5,5,5,7,7 };
short Divine_Piercing_UseMana[10] = { 45,47,49,51,53,55,57,59,61,63 };

// *************************************************************************** //
//
//									ATALANTA
//
// *************************************************************************** //

short S_Strike_UseMana[10] = { 16,18,20,22,24,27,30,33,36,40 };
short S_Strike_Damage[10][2] = { { 4,20 },{ 5,25 },{ 6,30 },{ 8,35 },{ 10,40 },{ 12,45 },{ 14,50 },{ 16,55 },{ 18,60 },{ 20,65 } };

short Farina_UseMana[10] = { 17,19,21,23,26,29,32,35,38,41 };
short Farina_Speed[10] = { 1,1,1,1,2,2,2,2,2,2 };
short Farina_AttackRate[10] = { 30,40,50,60,70,80,90,100,110,120 };

short T_Mastery_Damage[10] = { 18,22,26,30,34,38,41,44,47,50 };

short V_Spear_UseMana[10] = { 19,21,23,25,28,31,34,37,40,43 };
short V_Spear_Damage[10][2] = { { 4,10 },{ 6,15 },{ 8,20 },{ 10,25 },{ 11,30 },{ 12,35 },{ 13,40 },{ 14,45 },{ 15,50 },{ 16,55 } };

short Windy_Attack_Rating[10] = { 10,20,30,40,50,60,70,80,90,100 };
short Windy_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
short Windy_Mana[10] = { 24,26,28,30,32,34,37,40,44,48 };

short Twist_Javelin_Damage[10] = { 10,22,34,46,58,70,82,94,106,118 };
short Twist_Javelin_Attack_Rating[10] = { 10,22,34,46,58,70,82,94,106,118 };
short Twist_Javelin_Mana[10] = { 20,22,24,27,30,33,36,40,44,48 };

short Soul_Sucker_Absorb[10] = { 10,13,16,19,22,25,28,31,34,37 };
short Soul_Sucker_Mana[10] = { 25,28,31,34,38,42,46,50,55,60 };

short Fire_Javelin_Damage[10][2] = { { 20,30 },{ 25,35 },{ 30,40 },{ 35,45 },{ 40,50 },{ 45,55 },{ 50,60 },{ 55,65 },{ 60,70 },{ 65,75 } };
short Fire_Javelin_Mana[10] = { 25,27,29,32,35,38,41,44,47,50 };

short Split_Javelin_AttackNum[10] = { 3,3,3,3,3,3,3,3,3,3 };
short Split_Javelin_Damage[10] = { 8,14,20,26,32,38,44,50,56,62 };
short Split_Javelin_AttackRate[10] = { -10,-7,-4,-1,2,5,8,12,16,20 };
short Split_Javelin_UseMana[10] = { 30,33,36,39,42,45,48,51,54,57 };

short T_Of_Valhalla_Damage[10] = { 5,10,15,20,25,30,35,40,45,50 };
short T_Of_Valhalla_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
short T_Of_Valhalla_UseMana[10] = { 32,34,36,39,42,45,49,54,59,65 };

short Lightning_Javelin_Damage[10][2] = { { 20,40 },{ 23,46 },{ 26,52 },{ 29,58 },{ 32,64 },{ 35,70 },{ 38,76 },{ 41,82 },{ 44,88 },{ 47,96 } };
short Lightning_Javelin_UseMana[10] = { 30,32,34,37,40,43,47,50,53,56 };

short Storm_Javelin_Damage[10] = { 22,28,34,40,46,52,58,64,70,76 };
short Storm_Javelin_UseMana[10] = { 34,36,38,41,44,47,50,53,56,59 };

short Hall_Of_Valhalla_AddEvation[10] = { 5,7,9,11,13,15,17,19,21,23 };
short Hall_Of_Valhalla_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
short Hall_Of_Valhalla_UseMana[10] = { 36,39,42,45,48,52,56,60,65,70 };

short X_Rage_DamagePercent[10] = { 70,80,90,100,110,120,130,140,150,160 };
short X_Rage_Area[10] = { 100,105,110,115,120,125,130,135,140,145 };
short X_Rage_UseMana[10] = { 34,36,38,41,44,47,50,54,58,62 };

short Frost_Javelin_IceAddDamage[10][2] = { { 40,50 },{ 42,54 },{ 44,58 },{ 46,62 },{ 48,66 },{ 50,70 },{ 52,74 },{ 54,78 },{ 56,82 },{ 58,86 } };
short Frost_Javelin_SpeedSubPercent[10] = { 7,8,9,10,11,12,13,14,15,16 };
short Frost_Javelin_IceTime[10] = { 2,2,2,3,3,3,4,4,4,5 };
short Frost_Javelin_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
short Frost_Javelin_UseMana[10] = { 33,36,39,42,44,48,52,56,60,65 };

short Vengeance_DamagePercent[10] = { 10,20,30,40,50,60,70,80,90,100 };
short Vengeance_Range[10] = { 10,15,20,25,30,35,40,45,50,55 };
short Vengeance_UseMana[10] = { 33,35,37,39,41,43,45,47,49,51 };
short Vengeance_AddCritical[10] = { 2,4,6,8,10,13,16,19,22,25 };

// *************************************************************************** //
//
//									SACERDOTISA
//
// *************************************************************************** //


short Healing_UseMana[10] = { 11,14,17,20,24,28,32,37,42,47 };
short Healing_Heal[10][2] = { {64,86},{72,98},{80,110},{88,122},{96,134},{104,146},{112,158},{120,170},{128,182},{136,194} };


short HolyBolt_UseMana[10] = { 14,17,20,23,27,31,35,40,45,50 };
short HolyBolt_Damage[10] = { 14,17,20,23,27,31,35,40,45,50 };


short M_Spark_UseMana[10] = { 11,14,17,20,24,28,32,37,42,47 };



short M_Spark_Damage[10] = { 16,19,22,25,29,33,37,42,47,52 };
short M_Spark_Num[10] = { 4,4,4,5,5,5,6,6,7,7 };


short HolyMind_UseMana[10] = { 22,25,28,32,36,40,45,50,55,60 };
short HolyMind_DecDamage[10] = { 10,13,16,19,22,25,28,30,32,34 };
short HolyMind_Time[10] = { 15,15,15,15,15,15,15,15,15,15 };


float Meditation_Regen[10] = { 0.6f,1.0f,1.4f,1.8f,2.2f,2.6f,3.0f,3.4f,3.8f,4.2f };


short Divine_Lightning_Damage[10] = { 24,26,28,31,34,37,40,44,48,53 };
short Divine_Lightning_Num[10] = { 3,3,3,4,4,4,5,5,5,6 };
short Divine_Lightning_Mana[10] = { 24,26,28,31,34,37,40,44,48,53 };


short Holy_Reflection_Return_Damage[10] = { 20,30,40,50,60,70,80,90,100,110 };
short Holy_Reflection_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
short Holy_Reflection_Mana[10] = { 24,27,30,33,36,40,44,48,52,57 };


short Grand_Healing[10][2] = { {40,50},{50,60},{60,70},{70,80},{80,90},{90,100},{100,110},{110,120},{120,130},{130,140} };
short Grand_Healing_Range[10] = { 300,310,320,330,340,350,360,370,380,390 };
short Grand_Healing_Mana[10] = { 24,26,29,32,36,40,44,49,54,59 };


short Vigor_Ball_Damage[10] = { 26,28,30,33,36,39,42,45,48,51 };
short Vigor_Ball_UseMana[10] = { 26,28,30,33,36,39,42,45,48,51 };


short Resurrection_Percent[10] = { 40,47,54,61,67,73,79,84,89,94 };
short Resurrection_Exp[10] = { 100,150,200,250,300,350,400,450,500,550 };
short Resurrection_UseMana[10] = { 70,66,62,58,54,50,46,42,38,34 };


short Extinction_Percent[10] = { 60,64,68,72,76,80,84,88,92,100 };
short Extinction_Amount[10] = { 20,25,30,34,38,41,44,47,50,52 };
short Extinction_UseMana[10] = { 30,32,34,37,40,43,47,51,55,60 };


short Virtual_Life_Percent[10] = { 2,3,4,5,6,7,8,9,11,13 };
short Virtual_Life_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
short Virtual_Life_UseMana[10] = { 60,63,66,69,73,77,81,86,91,97 };


short Glacial_Spike_Damage[10] = { 150,155,160,165,170,175,180,185,190,195 };
short Glacial_Spike_Area[10] = { 150,155,160,165,170,175,180,185,190,195 };
short Glacial_Spike_UseMana[10] = { 65,68,71,74,77,80,83,86,89,92 };


float Regeneration_Field_LifeRegen[10] = { 1.2f,2.4f,3.6f,4.8f,6.0f,7.2f,8.4f,9.6f,10.8f,12.0f };
float Regeneration_Field_ManaRegen[10] = { 1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f };
short   Regeneration_Field_Time[10] = { 35,40,45,50,55,60,65,70,75,80 };
short   Regeneration_Field_Area[10] = { 250,260,270,280,290,300,310,320,330,340 };
short   Regeneration_Field_UseMana[10] = { 100,104,108,112,116,120,124,128,132,136 };


short Chain_Lightning_Damage[10] = { 140,145,150,155,160,165,170,175,180,185 };
short Chain_Lightning_Num[10] = { 5,5,6,6,7,7,8,8,9,9 };
short Chain_Lightning_Range[10] = { 100, 105, 110, 115, 120, 125, 130, 135, 140, 145 };
short Chain_Lightning_UseMana[10] = { 76,79,82,85,88,91,94,97,100,103 };


short Summon_Muspell_Damage[10][2] = { {70,95},{76,100},{82,105},{88,110},{94,115},
									{100,120},{106,125},{112,130},{118,135},{124,140} };
short Summon_Muspell_Attack_Delay[10] = { 7,7,7,6,6,6,5,5,5,4 };
short Summon_Muspell_UndeadAbsorbPercent[10] = { 10,14,18,22,26,30,34,38,42,46 };
short Summon_Muspell_BlockPercent[10] = { 5,6,7,8,9,10,11,12,13,14 };
short Summon_Muspell_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
short Summon_Muspell_UseMana[10] = { 110,114,118,122,126,130,134,138,140,146 };


// *************************************************************************** //
//
//									MAGO
//
// *************************************************************************** //

short Agony_UseMana[10] = { 5,6,7,8,9,10,11,12,13,14 };
short Agony_ConvLife[10] = { 4,8,12,16,20,24,28,32,36,40 };


short FireBolt_UseMana[10] = { 16,18,20,22,25,28,31,34,38,42 };
short FireBolt_Damage[10] = { 16,18,20,22,25,28,31,34,38,42 };


short Zenith_UseMana[10] = { 18,20,22,25,28,31,35,39,43,48 };
short Zenith_Element[10] = { 2,3,4,5,6,7,8,9,10,11 };
short Zenith_Time[10] = { 30,50,70,90,110,130,150,170,190,210 };


short FireBall_UseMana[10] = { 22,24,26,28,31,34,38,42,46,50 };
short FireBall_Damage[10] = { 22,24,26,28,31,34,38,42,46,50 };
short FireBall_Area[10] = { 70,72,74,76,78,80,82,84,86,88 };
short FireBall_Range[10] = { 163,166,169,172,175,178,181,184,187,190 };


short Mental_Mastery_Mana[10] = { 5,8,11,14,17,20,23,26,29,32 };


short Watornado_Damage[10] = { 70,72,74,76,78,80,82,84,86,88 };
short Watornado_Area[10] = { 70,72,74,76,78,80,82,84,86,88 };
short Watornado_Range[10] = { 170,174,178,182,186,190,194,198,202,206 };
short Watornado_Mana[10] = { 25,27,29,32,35,38,42,46,50,55 };


short Enchant_Weapon_Damage_Ice[10][2] = { {3,8},{6,12},{9,16},{12,20},{15,24},{18,28},{21,32},{24,36},{27,40},{30,44} };
short Enchant_Weapon_Damage_Fire[10][2] = { {4,10},{8,16},{12,22},{16,28},{20,34},{24,40},{28,46},{32,52},{36,58},{40,64} };
short Enchant_Weapon_Damage_Lightning[10][2] = { {4,8},{6,13},{8,18},{10,23},{12,28},{14,33},{16,38},{18,43},{20,48},{22,53} };
short Enchant_Weapon_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
short Enchant_Weapon_Mana[10] = { 30,32,34,37,40,44,48,53,58,64 };


short Dead_Ray_Damage[10] = { 185,190,195,200,205,210,215,220,225,230 };
short Dead_Ray_Range[10] = { 185,190,195,200,205,210,215,220,225,230 };
short Dead_Ray_Mana[10] = { 26,29,32,35,39,43,47,51,55,59 };


short Energy_Shield_DecDamage[10] = { 10,13,16,19,21,24,26,28,29,33 };
short Energy_Shield_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
short Energy_Shield_UseMana[10] = { 34,37,40,43,47,51,55,60,66,72 };


short Diastrophism_Damage[10] = { 100,105,110,115,120,125,130,135,140,145 };
short Diastrophism_Area[10] = { 100,105,110,115,120,125,130,135,140,145 };
short Diastrophism_UseMana[10] = { 30,33,36,39,43,47,51,56,61,67 };


float Spirit_Elemental_RegenMana[10] = { 0.2f,0.4f,0.6f,0.8f,1.0f,1.2f,1.4f,1.6f,1.8f,2.0f };
short Spirit_Elemental_Damage[10] = { 310,320,330,340,350,360,370,380,390,400 };

short Spirit_Elemental_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
short Spirit_Elemental_UseMana[10] = { 36,39,42,45,48,51,54,57,60,63 };


short Dancing_Sword_IceDamage[10][2] = { {20,26},{22,29},{24,32},{26,35},{28,38},{30,41},{32,44},{34,47},{36,50},{38,53} };
short Dancing_Sword_FireDamage[10][2] = { {20,26},{23,30},{26,34},{29,38},{32,42},{35,46},{38,50},{41,54},{44,58},{47,62} };
short Dancing_Sword_AttackDelay[10] = { 5,5,5,5,4,4,4,4,3,3 };
short Dancing_Sword_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
short Dancing_Sword_UseMana[10] = { 35,37,39,42,45,48,52,56,61,66 };


short Fire_Elemental_Damage[10][2] = { {80,95},{85,100},{90,105},{95,110},{100,115},
									  {105,120},{110,125},{115,130},{120,135},{125,140} };
short Fire_Elemental_Hit[10] = { 500,550,600,650,700,750,800,850,900,950 };
short Fire_Elemental_Life[10] = { 2000,2200,2400,2600,2800,3000,3200,3400,3600,3800 };
short Fire_Elemental_UseMana[10] = { 52,56,60,64,68,72,76,80,84,88 };


short Flame_Wave_FireDamage[10] = { 110,120,130,140,150,160,170,180,190,200 };
short Flame_Wave_Area[10] = { 110,120,130,140,150,160,170,180,190,200 };
short Flame_Wave_UseMana[10] = { 75,79,83,87,91,95,99,103,107,111 };


short Distortion_SpeedSubPercent[10] = { 4,6,8,10,12,14,16,18,20,22 };
short Distortion_DamageSubPercent[10] = { 15,16,17,18,19,20,21,22,23,24 };
short Distortion_Area[10] = { 120,125,130,135,140,145,150,155,160,165 };
short Distortion_Time[10] = { 4,6,8,10,12,14,16,18,20,22 };
short Distortion_UseMana[10] = { 105,110,115,120,125,130,135,140,145,150 };


short Meteo_Damage[10] = { 100,105,110,115,120,125,130,135,140,145 };
short Meteo_Area[10] = { 100,105,110,115,120,125,130,135,140,145 };
short Meteo_UseMana[10] = { 100,104,108,112,116,120,124,128,132,136 };


ASSASSIN_INFO AssassinSkills;
char* GetWords(char* q, char* p)
{

	//	while ( *p != '\n' ) {
	if (*p == 0) { *q = 0; return p; }

	while ((*p == 32) || (*p == 9) || (*p == 58)) // SPACE or TAB or ':'는 제외 시킴
	{
		p++;
	}

	while ((*p != 32) && (*p != 9) && (*p != 58) && (*p != 0)) // SPACE or TAB
	{
		if (*p == '\n' || *p == '\r') break;
		*q++ = *p++;
	}
	*q++ = 0;	// end of one string, put Null character
	//	}
	//	*q = '\n';

	return p;
}



#include <string>
#include <sstream>

int ReadSkillFloat(float* Skill, char* szFileName, char* szSkillName)
{
#ifdef _W_SERVER
	int i;
	char Path[255], decode[255], line[255];
	FILE* file;
	char* skill;

	GetCurrentDirectoryA(sizeof(Path), Path);
	wsprintf(Path, "%s\\Server\\Skill\\%s", Path, szFileName);

	file = fopen(Path, "rb");

	//fopen(&file, Path, "rb");

	if (file == NULL)
		return FALSE;

	while (!feof(file)) {

		if (fgets(line, 255, file) == NULL) break;

		skill = GetWords(decode, line);
		if (lstrcmpi(decode, szSkillName) == 0) {
			for (i = 0; i < 10; i++)
			{

				while (*skill == ',' || *skill == ' ' || *skill == '=' || *skill == '.')
					if (*skill == '.')
						skill += 2;
					else
						skill++;

				if (*skill == ';') break;

				/*	std::istringstream in(skill);

					std::string type;
					in >> type;*/

				Skill[i] = (float)atof(skill);
				//	Skill[i] = std::stof(type, &sz);

				while (*skill != ',')
				{
					skill++;
					if (*skill == ';') break;
				}
			}
		}
	}
	fclose(file);
#endif
	return TRUE;
}

int ReadSkillInt(int* Skill, char* szFileName, char* szSkillName)
{
	int i;
	char Path[255], decode[255], line[255];
	FILE* file;
	char* skill;

	GetCurrentDirectoryA(sizeof(Path), Path);
	wsprintf(Path, "%s\\Server\\Skill\\%s", Path, szFileName);

	file = fopen(Path, "rb");


	if (file == NULL)
		return FALSE;

	while (!feof(file)) {

		if (fgets(line, 255, file) == NULL) break;

		skill = GetWords(decode, line);
		if (lstrcmpi(decode, szSkillName) == 0) {
			for (i = 0; i < 10; i++) {
				while (*skill == ',' || *skill == ' ' || *skill == '=')
					skill++;

				if (*skill == ';') break;

				Skill[i] = atoi(skill);

				while (*skill != ',')
				{
					skill++;
					if (*skill == ';') break;
				}
			}
			break;
		}
	}
	fclose(file);
	return TRUE;
}

int ReadSkillInt2(int Skill[][2], char* szFileName, char* szSkillName)
{
	int i;
	char Path[255], decode[255], line[255];
	FILE* file;
	char* skill;

	GetCurrentDirectoryA(sizeof(Path), Path);
	wsprintf(Path, "%s\\Server\\Skill\\%s", Path, szFileName);

	file = fopen(Path, "rb");
	//fopen_s(&file, Path, "rb");

	if (file == NULL)
		return FALSE;

	while (!feof(file)) {

		if (fgets(line, 255, file) == NULL) break;

		skill = GetWords(decode, line);
		if (lstrcmpi(decode, szSkillName) == 0) {
			for (i = 0; i < 10; i++) {
				for (int j = 0; j < 2; j++) {

					while (*skill == ',' || *skill == ' ' || *skill == '=' || *skill == '(' || *skill == ')')
						skill++;

					if (*skill == ';') break;

					Skill[i][j] = atoi(skill);

					while (*skill != ',')
					{
						skill++;
						if (*skill == ';') break; // testar.
					}
				}
			}
			break;
		}
	}
	fclose(file);
	return TRUE;
}
int LoadSkillInfo()
{
    ReadSkillInt(&Stinger_Damage[0], "Assassin.ini", "Stingger_Damage");
    ReadSkillInt(&Stinger_UseMana[0], "Assassin.ini", "Stingger_UseMana");

    ReadSkillInt(&Double_Blow_Damage[0], "Assassin.ini", "Double_Blow_Damage");
    ReadSkillInt(&DoubleBlow_UseMana[0], "Assassin.ini", "DoubleBlow_UseMana");

    ReadSkillInt(&D_Mastery_DamagePercent[0], "Assassin.ini", "D_Mastery_DamagePercent");

    ReadSkillInt(&Wisp_UseTime[0], "Assassin.ini", "Wisp_UseTime");
    ReadSkillInt(&Wisp_Reduction[0], "Assassin.ini", "Wisp_Reduction");
    ReadSkillInt(&Wisp_UseMana[0], "Assassin.ini", "Wisp_UseMana");

    ReadSkillInt(&VenomThorn_Time[0], "Assassin.ini", "VenomThorn_Time");
    ReadSkillInt(&VenomThorn_Chance[0], "Assassin.ini", "VenomThorn_Chance");
    ReadSkillInt(&VenomThorn_Damage[0], "Assassin.ini", "VenomThorn_Damage");
    ReadSkillInt(&VenomThorn_UseMana[0], "Assassin.ini", "VenomThorn_UseMana");

    ReadSkillInt(&Alas_Time[0], "Assassin.ini", "Alas_Time");
    ReadSkillInt(&Alas_UseMana[0], "Assassin.ini", "Alas_UseMana");
    ReadSkillInt(&Alas_EvasionPercent[0], "Assassin.ini", "Alas_EvasionPercent");

    ReadSkillInt(&SoulChock_Range[0], "Assassin.ini", "SoulChock_Range");
    ReadSkillInt(&SoulChock_Time[0], "Assassin.ini", "SoulChock_Time");
    ReadSkillInt(&SoulChock_UseMana[0], "Assassin.ini", "SoulChock_UseMana");

    ReadSkillInt(&A_Mastery_AddPercent[0], "Assassin.ini", "A_Mastery_AddPercent");
    ReadSkillInt(&A_Mastery_AddPercent2[0], "Assassin.ini", "A_Mastery_AddPercent2");

    ReadSkillInt(&SoreSword_Damage[0], "Assassin.ini", "SoreSword_Damage");
    ReadSkillInt(&SoreSword_UseMana[0], "Assassin.ini", "SoreSword_UseMana");

    ReadSkillInt(&BeatUp_Damage[0], "Assassin.ini", "BeatUp_Damage");
    ReadSkillInt(&BeatUp_Area[0], "Assassin.ini", "BeatUp_Area");
    ReadSkillInt(&BeatUp_UseMana[0], "Assassin.ini", "BeatUp_UseMana");

    ReadSkillInt(&Inpes_Time[0], "Assassin.ini", "Inpes_Time");
    ReadSkillInt(&Inpes_Speed[0], "Assassin.ini", "Inpes_Speed");
    ReadSkillInt(&Inpes_UseMana[0], "Assassin.ini", "Inpes_UseMana");

    ReadSkillInt(&Blind_Time[0], "Assassin.ini", "Blind_Time");
    ReadSkillInt(&Blind_Damage[0], "Assassin.ini", "Blind_Damage");
    ReadSkillInt(&Blind_Range[0], "Assassin.ini", "Blind_Range");
    ReadSkillInt(&Blind_UseMana[0], "Assassin.ini", "Blind_UseMana");

    ReadSkillInt(&FrostWind_Damage[0], "Assassin.ini", "FrostWind_Damage");
    ReadSkillInt(&FrostWind_UseMana[0], "Assassin.ini", "FrostWind_UseMana");

    ReadSkillInt(&F_Mastery_Critical[0], "Assassin.ini", "F_Mastery_Critical");


    ReadSkillInt2(Polluted_Damage2, "Assassin.ini", "Polluted_Damage2");
    ReadSkillInt(&Polluted_Area[0], "Assassin.ini", "Polluted_Area");
    ReadSkillInt(&Polluted_Time[0], "Assassin.ini", "Polluted_Time");
    ReadSkillInt(&Polluted_AttackNum[0], "Assassin.ini", "Polluted_AttackNum");
    ReadSkillInt(&Polluted_UseMana[0], "Assassin.ini", "Polluted_UseMana");

    ReadSkillInt(&PastingShadow_Damage[0], "Assassin.ini", "PastingShadow_Damage");
    ReadSkillInt(&PastingShadow_UseMana[0], "Assassin.ini", "PastingShadow_UseMana");


    ZeroMemory(&AssassinSkills, sizeof(ASSASSIN_INFO));


	ReadSkillInt(&AssassinSkills.Stinger_Damage[0], "Assassin.ini", "Stingger_Damage");
	ReadSkillInt(&AssassinSkills.Stinger_UseMana[0], "Assassin.ini", "Stingger_UseMana");

	ReadSkillInt(&AssassinSkills.Double_Blow_Damage[0], "Assassin.ini", "Double_Blow_Damage");
	ReadSkillInt(&AssassinSkills.DoubleBlow_UseMana[0], "Assassin.ini", "DoubleBlow_UseMana");

	ReadSkillInt(&AssassinSkills.D_Mastery_DamagePercent[0], "Assassin.ini", "D_Mastery_DamagePercent");

	ReadSkillInt(&AssassinSkills.Wisp_UseTime[0], "Assassin.ini", "Wisp_UseTime");
	ReadSkillInt(&AssassinSkills.Wisp_Reduction[0], "Assassin.ini", "Wisp_Reduction");
	ReadSkillInt(&AssassinSkills.Wisp_UseMana[0], "Assassin.ini", "Wisp_UseMana");

	ReadSkillInt(&AssassinSkills.VenomThorn_Time[0], "Assassin.ini", "VenomThorn_Time");
	ReadSkillInt(&AssassinSkills.VenomThorn_Chance[0], "Assassin.ini", "VenomThorn_Chance");
	ReadSkillInt(&AssassinSkills.VenomThorn_Damage[0], "Assassin.ini", "VenomThorn_Damage");
	ReadSkillInt(&AssassinSkills.VenomThorn_UseMana[0], "Assassin.ini", "VenomThorn_UseMana");

	ReadSkillInt(&AssassinSkills.Alas_Time[0], "Assassin.ini", "Alas_Time");
	ReadSkillInt(&AssassinSkills.Alas_UseMana[0], "Assassin.ini", "Alas_UseMana");
	ReadSkillInt(&AssassinSkills.Alas_EvasionPercent[0], "Assassin.ini", "Alas_EvasionPercent");

	ReadSkillInt(&AssassinSkills.SoulChock_Range[0], "Assassin.ini", "SoulChock_Range");
	ReadSkillInt(&AssassinSkills.SoulChock_Time[0], "Assassin.ini", "SoulChock_Time");
	ReadSkillInt(&AssassinSkills.SoulChock_UseMana[0], "Assassin.ini", "SoulChock_UseMana");

	ReadSkillInt(&AssassinSkills.A_Mastery_AddPercent[0], "Assassin.ini", "A_Mastery_AddPercent");
	ReadSkillInt(&AssassinSkills.A_Mastery_AddPercent2[0], "Assassin.ini", "A_Mastery_AddPercent2");

	ReadSkillInt(&AssassinSkills.SoreSword_Damage[0], "Assassin.ini", "SoreSword_Damage");
	ReadSkillInt(&AssassinSkills.SoreSword_UseMana[0], "Assassin.ini", "SoreSword_UseMana");

	ReadSkillInt(&AssassinSkills.BeatUp_Damage[0], "Assassin.ini", "BeatUp_Damage");
	ReadSkillInt(&AssassinSkills.BeatUp_Area[0], "Assassin.ini", "BeatUp_Area");
	ReadSkillInt(&AssassinSkills.BeatUp_UseMana[0], "Assassin.ini", "BeatUp_UseMana");

	ReadSkillInt(&AssassinSkills.Inpes_Time[0], "Assassin.ini", "Inpes_Time");
	ReadSkillInt(&AssassinSkills.Inpes_Speed[0], "Assassin.ini", "Inpes_Speed");
	ReadSkillInt(&AssassinSkills.Inpes_UseMana[0], "Assassin.ini", "Inpes_UseMana");

	ReadSkillInt(&AssassinSkills.Blind_Time[0], "Assassin.ini", "Blind_Time");
	ReadSkillInt(&AssassinSkills.Blind_Damage[0], "Assassin.ini", "Blind_Damage");
	ReadSkillInt(&AssassinSkills.Blind_Range[0], "Assassin.ini", "Blind_Range");
	ReadSkillInt(&AssassinSkills.Blind_UseMana[0], "Assassin.ini", "Blind_UseMana");

	ReadSkillInt(&AssassinSkills.FrostWind_Damage[0], "Assassin.ini", "FrostWind_Damage");
	ReadSkillInt(&AssassinSkills.FrostWind_UseMana[0], "Assassin.ini", "FrostWind_UseMana");

	ReadSkillInt(&AssassinSkills.F_Mastery_Critical[0], "Assassin.ini", "F_Mastery_Critical");


	ReadSkillInt2(AssassinSkills.Polluted_Damage2, "Assassin.ini", "Polluted_Damage2");
	ReadSkillInt(&AssassinSkills.Polluted_Area[0], "Assassin.ini", "Polluted_Area");
	ReadSkillInt(&AssassinSkills.Polluted_Time[0], "Assassin.ini", "Polluted_Time");
	ReadSkillInt(&AssassinSkills.Polluted_AttackNum[0], "Assassin.ini", "Polluted_AttackNum");
	ReadSkillInt(&AssassinSkills.Polluted_UseMana[0], "Assassin.ini", "Polluted_UseMana");

	ReadSkillInt(&AssassinSkills.PastingShadow_Damage[0], "Assassin.ini", "PastingShadow_Damage");
	ReadSkillInt(&AssassinSkills.PastingShadow_UseMana[0], "Assassin.ini", "PastingShadow_UseMana");


		return TRUE;
}

int ReLoadSkillInfo(rsPLAYINFO* lpPlayInfo)
{
    AssassinSkills.size = sizeof(ASSASSIN_INFO);
    AssassinSkills.code = smTRANSCODE_ASSASSIN_INFO;

    if (lpPlayInfo->lpsmSock)
        lpPlayInfo->lpsmSock->Send((char*)&AssassinSkills, AssassinSkills.size, TRUE);

    return TRUE;
}
