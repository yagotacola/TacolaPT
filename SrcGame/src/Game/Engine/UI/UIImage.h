#pragma once

#include "Utils/strings.h"
#include <d3d9.h>
#include <Windows.h>

namespace UI
{
	typedef class Image* LPIMAGE;

	class Image
	{
	protected:
		int iID;
		IDirect3DTexture9* hTexture;
		char szFileName[256];
		int iWidth;
		int iHeight;
		UINT uFormat;

		UINT uRef = 0;

	public:

		void AddRef() { uRef++; };
		UINT GetRef() { return uRef; };
		void DecRef() { uRef--; };

		void Clear();

		void SetID(int iImageID, IDirect3DTexture9* hTextureHandler) { iID = iImageID; hTexture = hTextureHandler; }
		void SetFile(const char* pszFile) { StringCbCopyA(szFileName, 256, pszFile); }

		void SetWidth(int iImageWidth) { iWidth = iImageWidth; }
		void SetHeight(int iImageHeight) { iHeight = iImageHeight; }

		void SetFormat(UINT uFormatID) { uFormat = uFormatID; }

		void SetTexture(IDirect3DTexture9* h) { hTexture = h; };

		int GetID() { return iID; }
		int GetWidth() { return iWidth; }
		int GetHeight() { return iHeight; }
		UINT GetFormat() { return uFormat; }
		char* GetFileName() { return szFileName; }
		IDirect3DTexture9* GetTexture() { return hTexture; }

		Image* GetPointer() { return this; };

		void Swap();

	};

};