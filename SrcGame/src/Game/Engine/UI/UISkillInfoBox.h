#pragma once

#include <Windows.h>
#include <Engine/UI/UIList.h>
#include <Engine/UI/UIImageBox.h>
#include <Engine/UI/UIImageLoader.h>
#include "UIElement.h"
#include "UIGroup.h"
#include "UIText.h"
#include <Engine/Directx/DXEffect.h>
#include <Engine/Directx/DXRenderTarget.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <d3d9caps.h>
#include <map>
#include <sinbaram/sinSkill.h>

struct sSKILL;

namespace UI
{
	typedef std::shared_ptr<class SkillInfoBox> SkillInfoBox_ptr;

	class SkillInfoBox : public Element
	{
	public:
		SkillInfoBox();
		virtual								~SkillInfoBox();

		void								Clear() {}
		void								AddSkillElement(int eElementID);

		BOOL								IsDifferentSkill(sSKILL* psSkill);
		BOOL								CanPrepareShowSkill(sSKILL* psSkill, Rectangle2D sBox);
		BOOL								IsViewingSkillTimer() { return bInfoBoxSkillTimer; }


		UI::Text_ptr						AddString(int iSide, const std::string& strString, DWORD dwColor = -1, BOOL bBold = FALSE, EAlign bAlign = EAlign::ALIGN_Left);
		void								SetLineColor(DWORD dwColor, int iSide = -1, int iLineCount = -1);

		BOOL								OnKeyPress(class CKeyboard* pcKeyboard);

		void								Init();

		void								FormatSkillInfo();
		BOOL								PrepareShowSkill(sSKILL* pcSkill, BOOL bSkillTimer, Rectangle2D sBox);

		void								Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

		void								DrawSkillInfoBox(int iX, int iY, int iWidth, int iHeight);

		void								SetExtraWidth(int extra) { iExtraWidth = extra; };

		sSKILL* GetCurrentSkill() { return &cSkillWrapper; }

		int									GetSkillInfoLevelOffset() { return iSkillInfoOffset; };
		void								SetSkillInfoLevelOffset(int iValue) { iSkillInfoOffset = iValue; };
		void								Invalidate() { bInvalidate = TRUE; };


	protected:
		//Images Box
		class Image* pImageMaskLeftTop;
		class Image* pImageMaskRightTop;
		class Image* pImageMaskLeftBottom;
		class Image* pImageMaskRightBottom;

		class Image* pImageBorderLeftTop;
		class Image* pImageBorderRightTop;
		class Image* pImageBorderTop;
		class Image* pImageBorderLeftBottom;
		class Image* pImageBorderRightBottom;
		class Image* pImageBorderBottom;
		class Image* pImageBorderLeft;
		class Image* pImageBorderRight;

		DX::RenderTarget_ptr				pRenderTargetMask;
		DX::Effect_ptr						pEffectMask;

		//Icons
		class Image* pImageIconItems[12];

		class Image* pImageSkillElements[6];

		std::vector<int>				vSkillElements;


		std::vector<Text_ptr>				vLeftText, vRightText, vCompareText;
		Rectangle2D							sSkillBox;
		sSKILL								cSkillWrapper;
		int									iSkillInfoBoxHeight;
		UINT								uSkillStatusPos = 0;
		std::string							strSkillNextLevelCost = "";
		BOOL								bInfoBoxSkillTimer = FALSE;
		UINT								uImageIconsItemsY = 0;

		int									iExtraWidth = 0;
		int									iSkillInfoOffset = 0;
		BOOL								bInvalidate = FALSE;
	};
}
