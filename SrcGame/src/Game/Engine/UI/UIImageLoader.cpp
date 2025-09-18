
#include <memory>
#include "UIImageLoader.h"
#include "UIImage.h"
#include "..\\Directx\\DXGraphicEngine.h"
#include "Utils\\_common.h"
#include "Utils\\Macros.h"

typedef std::shared_ptr<stImageStructure> pImageSt_ptr;

std::vector<UI::Image*> vImageResource;

namespace UI
{

	BOOL DecryptBMP(char* pBuffer, unsigned int uBufferSize)
	{
		if (uBufferSize < 14)
			return FALSE;

		if ((pBuffer[0] != 'B') || (pBuffer[1] != 'M'))
		{
			pBuffer[0] = 'B';
			pBuffer[1] = 'M';

			for (unsigned char c = 2; c < 14; c++)
				pBuffer[c] -= (c * c);
		}

		pBuffer[2] = 0;
		pBuffer[3] = 0;
		pBuffer[4] = 0;
		pBuffer[5] = 0;

		return TRUE;
	}

	BOOL DecryptTGA(char* pBuffer, unsigned int uBufferSize)
	{
		if (uBufferSize < 18)
			return FALSE;

		if ((pBuffer[0] == 'G') && (pBuffer[1] == '8'))
		{
			pBuffer[0] = 0;
			pBuffer[1] = 0;

			for (unsigned char c = 2; c < 18; c++)
				pBuffer[c] -= (c * c);
		}

		return TRUE;
	}

	void* ImageLoader::GetDataFromFile(const char* FilePath, size_t& FileSize) const
	{
		FileSize = 0;

		if (FilePath == nullptr || strlen(FilePath) == 0)
			return nullptr;

		FILE* fp = nullptr;

		if (fopen_s(&fp, FilePath, "rb") == 0)
		{
			// Get File Size
			fseek(fp, 0, SEEK_END);
			FileSize = ftell(fp);
			rewind(fp);

			// Buffer Read
			char* FileData = new char[FileSize]();

			// Read Buffer
			fread_s(FileData, FileSize, sizeof(char), FileSize, fp);
			fclose(fp);

			return static_cast<void*>(FileData);
		}

		return nullptr;
	}

	ImageLoader::ImageLoader()
	{
	}

	ImageLoader::~ImageLoader()
	{
	}

	void* ImageLoader::readData(const char* filepath, size_t& filesize, bool& free) const
	{
		auto data = GetDataFromFile(filepath, filesize);

		if (data)
		{
			free = true;
		}

		return data;
	}

	void ImageLoader::SetScale(UI::Image* pImage, int iW, int iH, D3DXVECTOR2* pVector)
	{
		if (pImage->GetWidth() > iW)
			pVector->x = (float)pImage->GetWidth() / (float)iW;
		else
			pVector->x = (float)iW / (float)pImage->GetWidth();

		if (pImage->GetHeight() > iH)
			pVector->y = (float)pImage->GetHeight() / (float)iH;
		else
			pVector->y = (float)iH / (float)pImage->GetHeight();
	}

	class Image* ImageLoader::Swap(Image* ptr)
	{
		for (UINT u = 0; u < vImageResource.size(); u++)
		{
			if (vImageResource[u]->GetPointer() == ptr)
			{
				char szFileName[256];
				STRINGCOPY(szFileName, vImageResource[u]->GetFileName());
				vImageResource[u]->SetFile("t");
				delete vImageResource[u];
				vImageResource[u] = LoadImage_(szFileName);
				return vImageResource[u];
				break;
			}
		}
		return NULL;
	}

	UI::Image* ImageLoader::LoadImage_(const char* pszFile, ...)
	{
		char szBuf[1024];
		ZeroMemory(szBuf, 1024);
		va_list ap;
		va_start(ap, pszFile);
		_vsnprintf_s(szBuf, 1024, 1023, pszFile, ap);
		va_end(ap);

		// Get the size of string
		int iStrNameSize = lstrlenA(szBuf);
		if (iStrNameSize <= 4)
		{
			return NULL;
		}

		for (UINT u = 0; u < vImageResource.size(); u++)
		{
			if (STRINGCOMPARE(vImageResource[u]->GetFileName(), szBuf))
			{
				vImageResource[u]->AddRef();
				return vImageResource[u];
			}
		}

		D3DXIMAGE_INFO SrcInfo;

		// Define temp Alloc
		UI::Image* pImage = new UI::Image();

		// Use a magenta colourkey
		D3DCOLOR colorkey = 0xFFFF00FF;

		// Open File Memory
		size_t fileSize = 0;
		bool free = false;
		auto pBuffer = IMAGELOADER->readData(szBuf, fileSize, free);

		if (pBuffer)
		{
			// Check Decrypt
			std::string strFileExtension = GetFileExtension(szBuf);

			if (strFileExtension.compare("bmp") == 0)
			{
				if (!DecryptBMP(static_cast<char*>(pBuffer), fileSize))
				{
					if (free)
						delete[] pBuffer;
					return NULL;
				}
			}
			if (strFileExtension.compare("tga") == 0)
			{
				if (!DecryptTGA(static_cast<char*>(pBuffer), fileSize))
				{
					if (free)
						delete[] pBuffer;

					return NULL;
				}
			}

			// Get Image Info
			D3DXGetImageInfoFromFileInMemory(pBuffer, fileSize, &SrcInfo);

			if (SrcInfo.ImageFileFormat == D3DXIFF_BMP)
				colorkey = 0xFF000000;

			IDirect3DTexture9* hTexture;


			// Load image from file.
			if (FAILED(D3DXCreateTextureFromFileInMemoryEx(GRAPHICENGINE->GetDevice(), pBuffer, fileSize, SrcInfo.Width, SrcInfo.Height, 1, 0, (D3DFORMAT)D3DX_FROM_FILE, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, SrcInfo.ImageFileFormat == D3DXIFF_BMP ? D3DCOLOR_ARGB(255, 0, 0, 0) : 0, &SrcInfo, NULL, &hTexture)))
			{
				if (FILEEXIST(szBuf) == false)
				{
					char szTextureError[512] = { 0 };
					STRINGFORMAT(szTextureError, "Could not find file %s\n", szBuf);
					MessageBoxA(0, szTextureError, "Error", MB_ICONERROR | MB_OK);
					ExitProcess(0);
				}
			}
			pImage->SetWidth(SrcInfo.Width);
			pImage->SetHeight(SrcInfo.Height);
			pImage->SetFormat(SrcInfo.ImageFileFormat);
			pImage->SetFile(szBuf);
			pImage->SetID(vImageResource.size(), hTexture);

			vImageResource.push_back(pImage);

			if (free)
				delete[] pBuffer;

			pImage->AddRef();

			return pImage;
		}

		return NULL;
	}

	std::pair<UI::Image*, UI::Image*> ImageLoader::LoadActiveImage(char* pszFile1, char* pszFile2)
	{
		UI::Image* f = ImageLoader::LoadImage_(pszFile1);
		UI::Image* s = ImageLoader::LoadImage_(pszFile2);
		return std::pair<UI::Image*, UI::Image*>(f, s);
	}

	void ImageLoader::DeleteImage(Image* ptr)
	{
		if (ptr)
		{
			ptr->DecRef();

			if (ptr->GetRef() == 0)
			{
				for (std::vector<UI::Image*>::iterator it = vImageResource.begin(); it != vImageResource.end(); it++)
				{
					UI::Image* pc = (*it);

					if (pc == ptr)
					{
						LPDIRECT3DTEXTURE9 lp = pc->GetTexture();
						RELEASE(lp);
						DELET(pc);

						it = vImageResource.erase(it);
						break;
					}
				}
			}
		}
	}


}