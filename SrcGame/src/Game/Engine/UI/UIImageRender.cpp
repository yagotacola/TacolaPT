
#include <vector>
#include <memory>
#include "UIImageRender.h"
#include "UIImageLoader.h"
#include "..\\Directx\\DXEffect.h"
#include "..\\Directx\\DXGraphicEngine.h"
#include "Utils\\Geometry.h"
#include "Utils\EXEVertex.h"
#include "Def.h"

typedef std::shared_ptr<stImageStructure> pImageSt_ptr;

extern std::vector<pImageSt_ptr> vImageResource;

LPD3DXSPRITE lpSpriteUIImage = NULL;
LPD3DXSPRITE lpSpriteUIImageNormal = NULL;
ID3DXEffect* lpEffectImage = NULL;
LPD3DXBUFFER lpD3DErrorBuffer = NULL;
HRESULT hr;

namespace UI
{

	DX::Effect_ptr ImageRender::pEffect;

	ImageRender::ImageRender()
	{
	}

	ImageRender::~ImageRender()
	{
	}

	DX::Effect_ptr ImageRender::GetEffect()
	{
		return ImageRender::pEffect;
	}

	void ImageRender::SetEffect(DX::Effect_ptr p)
	{
		ImageRender::pEffect = p;
	}

	void ImageRender::Render(LPDIRECT3DTEXTURE9 lpTexture, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY, DWORD dwColor, float fScaleX, float fScaleY, float fRotation)
	{
		if (!lpTexture)
			return;

		//Create Sprite
		if (lpSpriteUIImage == NULL)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(), &lpSpriteUIImage);

		//Sprite Transformation
		D3DXVECTOR2 scale(fScaleX, fScaleY);
		D3DXVECTOR2 trans((float)iX, (float)iY);
		D3DXVECTOR2 center((float)(iWidth >> 1) * fScaleX, (float)(iHeight >> 1) * fScaleY);
		// D3DXVECTOR2 center( (float)((iWidth / 2)) - (float)(iX / 2), (float)((iHeight / 2)) - (float)(iY / 2) );

		fRotation = D3DXToRadian(fRotation);

		D3DXMATRIX matrix;
		D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &scale, &center, fRotation, &trans);

		//Sprite Rectangle
		RECT rSourceRect;
		rSourceRect.left = iSourceX;
		rSourceRect.top = iSourceY;
		rSourceRect.right = rSourceRect.left + iWidth;
		rSourceRect.bottom = rSourceRect.top + iHeight;

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		for (UINT u = 0; u < uPasses; u++)
		{
			lpSpriteUIImage->Begin(D3DXSPRITE_ALPHABLEND);
			{
				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->BeginPass(u);

				LPDIRECT3DBASETEXTURE9 lpOld;
				GRAPHICDEVICE->GetTexture(0, &lpOld);
				GRAPHICDEVICE->SetTexture(0, lpTexture);
				lpSpriteUIImage->SetTransform(&matrix);
				lpSpriteUIImage->Draw(lpTexture, &rSourceRect, NULL, NULL, dwColor);

				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->EndPass();

				lpSpriteUIImage->End();

				GRAPHICDEVICE->SetTexture(0, lpOld);
			}
		}
	}

	void ImageRender::Render(LPDIRECT3DTEXTURE9 lpTexture, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY, DWORD dwColor, float fScale, float fRotation)
	{
		if (!lpTexture)
			return;

		//Create Sprite
		if (lpSpriteUIImage == NULL)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(), &lpSpriteUIImage);

		//Sprite Transformation
		D3DXVECTOR2 scale(fScale, fScale);
		D3DXVECTOR2 trans((float)iX, (float)iY);
		D3DXVECTOR2 center((float)(iWidth >> 1) * fScale, (float)(iHeight >> 1) * fScale);
		// D3DXVECTOR2 center( (float)((iWidth / 2)) - (float)(iX / 2), (float)((iHeight / 2)) - (float)(iY / 2) );

		fRotation = D3DXToRadian(fRotation);

		D3DXMATRIX matrix;
		D3DXMatrixTransformation2D(&matrix, NULL, fScale, &scale, &center, fRotation, &trans);

		//Sprite Rectangle
		RECT rSourceRect;
		rSourceRect.left = iSourceX;
		rSourceRect.top = iSourceY;
		rSourceRect.right = rSourceRect.left + iWidth;
		rSourceRect.bottom = rSourceRect.top + iHeight;

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		for (UINT u = 0; u < uPasses; u++)
		{
			lpSpriteUIImage->Begin(D3DXSPRITE_ALPHABLEND);
			{
				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->BeginPass(u);

				//LPDIRECT3DBASETEXTURE9 lpOld;
				GRAPHICDEVICE->SetTexture(0, lpTexture);
				lpSpriteUIImage->SetTransform(&matrix);
				lpSpriteUIImage->Draw(lpTexture, &rSourceRect, NULL, NULL, dwColor);

				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->EndPass();

				lpSpriteUIImage->End();
			}
		}
	}

	void ImageRender::Render(LPDIRECT3DTEXTURE9 lpTexture, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY, DWORD dwColor, float fScale, float fRotation, Point2D sRotationPoint, DWORD dwFlags)
	{
		if (!lpTexture)
			return;

		//Create Sprite
		if (lpSpriteUIImage == NULL)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(), &lpSpriteUIImage);

		//Sprite Transformation
		D3DXVECTOR2 scale(fScale, fScale);
		D3DXVECTOR2 trans((float)iX, (float)iY);
		D3DXVECTOR2 center((float)abs(iX - sRotationPoint.iX), (float)abs(iY - sRotationPoint.iY));

		fRotation = D3DXToRadian(fRotation);

		D3DXMATRIX matrix;
		D3DXMatrixTransformation2D(&matrix, NULL, fScale, &scale, &center, fRotation, &trans);

		//Sprite Rectangle
		RECT rSourceRect;
		rSourceRect.left = iSourceX;
		rSourceRect.top = iSourceY;
		rSourceRect.right = rSourceRect.left + iWidth;
		rSourceRect.bottom = rSourceRect.top + iHeight;

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		for (UINT u = 0; u < uPasses; u++)
		{
			lpSpriteUIImage->Begin(dwFlags);
			{
				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->BeginPass(u);

				LPDIRECT3DBASETEXTURE9 lpOld;
				GRAPHICDEVICE->GetTexture(0, &lpOld);
				GRAPHICDEVICE->SetTexture(0, lpTexture);
				lpSpriteUIImage->SetTransform(&matrix);
				lpSpriteUIImage->Draw(lpTexture, &rSourceRect, NULL, NULL, dwColor);

				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->EndPass();

				lpSpriteUIImage->End();

				GRAPHICDEVICE->SetTexture(0, lpOld);
			}
		}
	}

	void ImageRender::Render(LPDIRECT3DTEXTURE9 lpTexture, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY, DWORD dwColor, BOOL bScaleResolution)
	{
		if (!lpTexture)
			return;

		//Create Sprite
		if (lpSpriteUIImage == NULL)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(), &lpSpriteUIImage);

		//Sprite Transformation
		D3DXVECTOR2 scale(1.0f, 1.0f);

		if (bScaleResolution)
		{
			scale.x = (float)RESOLUTION_WIDTH / (float)iWidth;
			scale.y = (float)RESOLUTION_HEIGHT / (float)iHeight;
		}

		D3DXVECTOR2 trans((float)iX, (float)iY);
		D3DXVECTOR2 center((float)((iWidth / 2)), (float)((iHeight / 2)));

		float fRotation = D3DXToRadian(0.0f);

		D3DXMATRIX matrix;
		D3DXMatrixTransformation2D(&matrix, NULL, 0.0, &scale, &center, fRotation, &trans);

		//Sprite Rectangle
		RECT rSourceRect;
		rSourceRect.left = iSourceX;
		rSourceRect.top = iSourceY;
		rSourceRect.right = rSourceRect.left + iWidth;
		rSourceRect.bottom = rSourceRect.top + iHeight;

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		for (UINT u = 0; u < uPasses; u++)
		{
			lpSpriteUIImage->Begin(D3DXSPRITE_ALPHABLEND);
			{
				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->BeginPass(u);

				LPDIRECT3DBASETEXTURE9 lpOld;
				GRAPHICDEVICE->GetTexture(0, &lpOld);
				GRAPHICDEVICE->SetTexture(0, lpTexture);
				lpSpriteUIImage->SetTransform(&matrix);
				lpSpriteUIImage->Draw(lpTexture, &rSourceRect, NULL, NULL, dwColor);

				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->EndPass();

				lpSpriteUIImage->End();

				GRAPHICDEVICE->SetTexture(0, lpOld);
			}
		}
	}

	void ImageRender::Render(UI::Image* pImage, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY, DWORD dwColor, float fScale, float fRotation, DWORD dwFlags)
	{
		if (!pImage)
			return;

		//Create Sprite
		if (lpSpriteUIImage == NULL)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(), &lpSpriteUIImage);


		//Sprite Transformation
		D3DXVECTOR2 scale(fScale, fScale);
		D3DXVECTOR2 trans((float)iX, (float)iY);
		D3DXVECTOR2 center((float)(iWidth >> 1) * fScale, (float)(iHeight >> 1) * fScale);

		fRotation = D3DXToRadian(fRotation);

		D3DXMATRIX matrix;
		D3DXMatrixTransformation2D(&matrix, NULL, 0.0, &scale, &center, fRotation, &trans);

		//Sprite Rectangle
		RECT rSourceRect;
		rSourceRect.left = iSourceX;
		rSourceRect.top = iSourceY;
		rSourceRect.right = rSourceRect.left + iWidth;
		rSourceRect.bottom = rSourceRect.top + iHeight;

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		for (UINT u = 0; u < uPasses; u++)
		{
			lpSpriteUIImage->Begin(dwFlags);

			if (ImageRender::GetEffect())
				ImageRender::GetEffect()->BeginPass(u);

			LPDIRECT3DBASETEXTURE9 lpOld;
			GRAPHICDEVICE->GetTexture(0, &lpOld);
			GRAPHICDEVICE->SetTexture(0, pImage->GetTexture());

			lpSpriteUIImage->SetTransform(&matrix);

			lpSpriteUIImage->Draw(pImage->GetTexture(), &rSourceRect, NULL, NULL, dwColor);

			if (ImageRender::GetEffect())
				ImageRender::GetEffect()->EndPass();

			lpSpriteUIImage->End();

			GRAPHICDEVICE->SetTexture(0, lpOld);


		}
	}

	void ImageRender::Render(Image* pImage, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY, DWORD dwColor, float fScale, float fRotation, Point2D sRotationPoint)
	{
		if (!pImage)
			return;

		//Create Sprite
		if (lpSpriteUIImage == NULL)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(), &lpSpriteUIImage);

		//Sprite Transformation
		D3DXVECTOR2 scale(fScale, fScale);
		D3DXVECTOR2 trans((float)iX, (float)iY);
		D3DXVECTOR2 center((float)((iWidth / 2)), (float)((iHeight / 2)));

		fRotation = D3DXToRadian(fRotation);

		D3DXMATRIX matrix;
		D3DXMatrixTransformation2D(&matrix, NULL, 0.0, &scale, &center, fRotation, &trans);

		//Sprite Rectangle
		RECT rSourceRect;
		rSourceRect.left = iSourceX;
		rSourceRect.top = iSourceY;
		rSourceRect.right = rSourceRect.left + iWidth;
		rSourceRect.bottom = rSourceRect.top + iHeight;

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		for (UINT u = 0; u < uPasses; u++)
		{
			lpSpriteUIImage->Begin(D3DXSPRITE_ALPHABLEND);
			{
				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->BeginPass(u);

				LPDIRECT3DBASETEXTURE9 lpOld;
				GRAPHICDEVICE->GetTexture(0, &lpOld);
				GRAPHICDEVICE->SetTexture(0, pImage->GetTexture());
				lpSpriteUIImage->SetTransform(&matrix);
				lpSpriteUIImage->Draw(pImage->GetTexture(), &rSourceRect, NULL, NULL, dwColor);

				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->EndPass();

				lpSpriteUIImage->End();

				GRAPHICDEVICE->SetTexture(0, lpOld);
			}
		}
	}

	void ImageRender::Render(UI::Image* pImage, int iX, int iY, int iWidth, int iHeight, DWORD dwColor)
	{
		if (!pImage)
			return;

		//Create Sprite
		if (lpSpriteUIImage == NULL)
			D3DXCreateSprite(GRAPHICENGINE->GetDevice(), &lpSpriteUIImage);

		//Viewport
		D3DVIEWPORT9 sViewPort;
		GRAPHICDEVICE->GetViewport(&sViewPort);
		D3DXVECTOR3 pos = { (float)iX + sViewPort.X, (float)iY + sViewPort.Y, 0.0f };

		//Scale Vetor
		D3DXVECTOR2 scale(1.0f, 1.0f);
		UI::ImageLoader::SetScale(pImage, iWidth, iHeight, &scale);
		D3DXVECTOR2 trans((float)iX, (float)iY);
		D3DXVECTOR2 center((float)((iWidth) / 2), (float)((iHeight) / 2));
		D3DXMATRIX matrix;
		D3DXMatrixTransformation2D(&matrix, NULL, 0, &scale, &center, 0.0f, &trans);

		//Draw Sprite
		UINT uPasses = ImageRender::GetEffect() ? ImageRender::GetEffect()->GetPasses() : 1;

		for (UINT u = 0; u < uPasses; u++)
		{
			lpSpriteUIImage->Begin(D3DXSPRITE_ALPHABLEND);
			{
				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->BeginPass(u);

				LPDIRECT3DBASETEXTURE9 lpOld;
				GRAPHICDEVICE->GetTexture(0, &lpOld);
				GRAPHICDEVICE->SetTexture(0, pImage->GetTexture());
				lpSpriteUIImage->SetTransform(&matrix);
				lpSpriteUIImage->Draw(pImage->GetTexture(), NULL, NULL, NULL, dwColor);

				if (ImageRender::GetEffect())
					ImageRender::GetEffect()->EndPass();

				lpSpriteUIImage->End();

				GRAPHICDEVICE->SetTexture(0, lpOld);
			}
		}
	}

	void ImageRender::RenderQuad(class Image* pImage, int iX, int iY, int iWidth, int iHeight, Rectangle2DF fRect, DWORD dwColor)
	{
		float u1, v1, u2, v2;

		//Compute texture coordinates .it ' easy
		u1 = fRect.fX;
		v1 = fRect.fY;
		u2 = fRect.fWidth;
		v2 = fRect.fHeight;

		EXEDrawVertex rVertex[4];

		float fRenderX = float(iX) - 0.5f;
		float fRenderY = float(iY) - 0.5f;
		float fRenderWidth = fRenderX + float(iWidth);
		float fRenderHeight = fRenderY + float(iHeight);

		rVertex[0] = { fRenderX		,fRenderY		,0,1,D3DCOLOR_XRGB(255,255,255),0,u1,v1 };
		rVertex[1] = { fRenderWidth	,fRenderY		,0,1,D3DCOLOR_XRGB(255,255,255),0,u2,v1 };
		rVertex[2] = { fRenderX		,fRenderHeight	,0,1,D3DCOLOR_XRGB(255,255,255),0,u1,v2 };
		rVertex[3] = { fRenderWidth	,fRenderHeight	,0,1,D3DCOLOR_XRGB(255,255,255),0,u2,v2 };

		GRAPHICDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		//GRAPHICDEVICE->SetRenderState( D3DTEXTUREADDRESS, D3DTADDRESS_WRAP );

		GRAPHICDEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);
		GRAPHICDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		GRAPHICDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
		GRAPHICDEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		GRAPHICDEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		GRAPHICDEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		GRAPHICDEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

		//Texture Stage States
		GRAPHICDEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		GRAPHICDEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		GRAPHICDEVICE->SetTexture(0, pImage->GetTexture());

		GRAPHICDEVICE->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1);
		GRAPHICDEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, (LPVOID)rVertex, sizeof(EXEDrawVertex));
	}

	void ImageRender::OnResetDevice()
	{
		if (lpSpriteUIImage)
			lpSpriteUIImage->OnResetDevice();
		if (lpSpriteUIImageNormal)
			lpSpriteUIImageNormal->OnResetDevice();

		if (lpEffectImage)
			lpEffectImage->OnResetDevice();
	}

	void ImageRender::OnLostDevice()
	{
		if (lpSpriteUIImage)
			lpSpriteUIImage->OnLostDevice();
		if (lpSpriteUIImageNormal)
			lpSpriteUIImageNormal->OnLostDevice();

		if (lpEffectImage)
			lpEffectImage->OnLostDevice();
	}
}
