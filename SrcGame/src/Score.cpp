#include "Score.h"
#include <string>
#include "smLib3d\smDsx.h"
#include "playmain.h"
#include "character.h"
#include "field.h"
#include "hobaram\\holinkheader.h"
#include "sinbaram\\sinlinkheader.h"
#include <HoBaram/hoAssaParticleEffect.h>
#include "TitleBox/TitleBox.h"

extern int haSiegeBoardFlag;

Score::Score()
{
}

Score::~Score()
{

}



bool Score::drawModoBot()
{
	if (Settings::GetInstance()->bStatusBot)
	{
		//TitleBox::GetInstance()->SetText("Modo Automatico", 3);
	}

	return true;
}

bool Score::draw()
{
	unsigned int stage = StageField[lpCurPlayer->OnStageField]->FieldCode;
	bool result = false;
	extern bool ativarImgPVP;

	if (stage == 33 || stage == 21 || stage == 3)
	{
		//bloquear ativação de modo automático em BC
		if (Settings::GetInstance()->bStatusBot)
		{
			Settings::GetInstance()->bStatusBot = false;
		}

		result = true;
	}



	
	drawModoBot();
	




	return result;
}
