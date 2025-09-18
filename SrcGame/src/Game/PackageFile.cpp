#include "sinbaram/sinLinkHeader.h"
#include "PackageFile.h"

#include <filesystem>
#include "ZipCollections.h"

#include <ctype.h>
#include "ofuscate.h"

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

PackageFile::PackageFile() : strDataFolder{}, bInitialized(false), pFile(nullptr)
{
    std::string path("game\\data\\");
    std::string ext(".pkg");

    for (auto& p : std::filesystem::recursive_directory_iterator(path))
        if (p.path().extension() == ext)
            cachedPackageFiles[p.path().filename().string()] = ReadPackage(p.path().string().c_str());
}

PackageFile::~PackageFile()
{
    for (auto& packageFile : cachedPackageFiles)
    {
        ClosePackage(packageFile.second);
        delete packageFile.second;
    }

    cachedPackageFiles.clear();
}

CZipArchive* PackageFile::ReadPackage(const char* pszFileName)
{
    auto it = cachedPackageFiles.find(pszFileName);

    if (it != cachedPackageFiles.end())
        return it->second;

    try
    {
        CZipArchive* zip = new CZipArchive();

        if (zip->Open(pszFileName, CZipArchive::zipOpenReadOnly))
        {
            for (int i = 0; i < zip->GetCount(); ++i)
            {
                auto file = zip->GetFileInfo(i);

                if (file)
                {
                    std::string strFileName(file->GetFileName());
                    auto fileNamePath = std::filesystem::path{ strFileName };

                    if (fileNamePath.has_extension())
                        cachedFiles[file->GetFileName()] = zip;
                }
            }

            return zip;
        }

        return nullptr;
    }
    catch (...)
    {
        return nullptr;
    }

    return nullptr;
}

std::vector<char> PackageFile::GetFileBufferCached(const char* pszFileName)
{
    std::vector<char> out{};

    std::string fileName = pszFileName;
    std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);
    std::replace(fileName.begin(), fileName.end(), '/', '\\');

    if (auto it = cachedFiles.find(fileName); it != cachedFiles.end())
        out = GetFileBuffer(it->second, fileName.c_str());

    /*Deprecated
    if( auto it = notFoundFiles.find( pszFileName ); it != notFoundFiles.end() )
        return out;

    for( const auto& packageFile : cachedPackageFiles )
    {
        out = GetFileBuffer( packageFile.second, pszFileName );

        if( out.size() )
            break;
    }

    if( out.empty() )
        notFoundFiles[pszFileName] = true;*/

    return out;
}

std::vector<char> PackageFile::GetFileBuffer(CZipArchive* zip, const char* pszFileName)
{
    std::vector<char> out{};

    if (zip)
    {
        std::filesystem::path path{ pszFileName };

        std::string strPassword = std::string(AY_OBFUSCATE("twpguw@")) + path.filename().string();
        zip->SetPassword(strPassword.c_str());
        zip->SetEncryptionMethod(CZipCryptograph::encWinZipAes256);

        ZIP_INDEX_TYPE index = zip->FindFile(pszFileName);

        if (index != ZIP_FILE_INDEX_NOT_FOUND)
        {
            zip->OpenFile(index);

            DWORD uSize = (DWORD)(*zip)[index]->m_uUncomprSize;
            CZipAutoBuffer buffer;
            buffer.Allocate(uSize);
            try
            {
                //Decompress Data
                if (zip->ReadFile(buffer, uSize) != uSize)
                    CZipException::Throw();

                //Check if all the data was decompressed
                char temp;
                if (zip->ReadFile(&temp, 1) != 0)
                    CZipException::Throw();

                //Check the return code to ensure that the extraction was
                if (zip->CloseFile() != 1)
                    CZipException::Throw();

                //Get Keys to Decrypt
                std::vector<int> vKeysToDecrypt = vKeys;

                for (int i = 0; i < path.filename().string().length(); i++)
                    vKeysToDecrypt.push_back(path.filename().string()[i]);

                //Get Keys from Comment
                CZipFileHeader* info = (*zip)[index];
                stdbs comment = info->GetComment();

                auto vCommentKeys = split(comment, ";");
                for (auto& strCommentKey : vCommentKeys)
                    vKeysToDecrypt.push_back(atoi(strCommentKey.c_str()));

                out.insert(out.end(), buffer.GetBuffer(), buffer.GetBuffer() + uSize);

                for (auto i = 0; i < uSize; i++)
                    out[i] ^= vKeysToDecrypt[i % vKeysToDecrypt.size()];
            }
            catch (...)
            {
                zip->Close(CZipArchive::afAfterException);
                throw;
            }
        }
    }

    return out;
}

FILE* PackageFile::GetFileCached(const char* pszFileName, unsigned int& iFileSize)
{
    FILE* file = nullptr;

    std::string fileName = pszFileName;
    std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);
    std::replace(fileName.begin(), fileName.end(), '/', '\\');

    if (auto it = cachedFiles.find(fileName); it != cachedFiles.end())
        file = GetFile(it->second, fileName.c_str(), iFileSize);

    /*Deprecated
    if( auto it = notFoundFiles.find( pszFileName ); it != notFoundFiles.end() )
        return nullptr;

    for( const auto& packageFile : cachedPackageFiles )
    {
        file = GetFile( packageFile.second, pszFileName, iFileSize );

        if( file )
            break;
    }

    if( file == nullptr )
        notFoundFiles[pszFileName] = true;*/

    return file;
}

FILE* PackageFile::GetFile(CZipArchive* zip, const char* pszFileName, unsigned int& iFileSize)
{
    if (pFile)
        fclose(pFile);

    pFile = nullptr;
    if (zip)
    {
        std::filesystem::path path{ pszFileName };

        std::string strPassword = std::string(AY_OBFUSCATE("twpguw@")) + path.filename().string();
        zip->SetPassword(strPassword.c_str());
        zip->SetEncryptionMethod(CZipCryptograph::encWinZipAes256);

        ZIP_INDEX_TYPE index = zip->FindFile(pszFileName);

        if (index != ZIP_FILE_INDEX_NOT_FOUND)
        {
            zip->OpenFile(index);

            DWORD uSize = (DWORD)(*zip)[index]->m_uUncomprSize;
            CZipAutoBuffer buffer;
            buffer.Allocate(uSize);
            try
            {
                //Decompress Data
                if (zip->ReadFile(buffer, uSize) != uSize)
                    CZipException::Throw();

                //Check if all the data was decompressed
                char temp;
                if (zip->ReadFile(&temp, 1) != 0)
                    CZipException::Throw();

                //Check the return code to ensure that the extraction was
                if (zip->CloseFile() != 1)
                    CZipException::Throw();

                //Get Keys to Decrypt
                std::vector<int> vKeysToDecrypt = vKeys;

                for (int i = 0; i < path.filename().string().length(); i++)
                    vKeysToDecrypt.push_back(path.filename().string()[i]);

                //Get Keys from Comment
                CZipFileHeader* info = (*zip)[index];
                stdbs comment = info->GetComment();

                auto vCommentKeys = split(comment, ";");
                for (auto& strCommentKey : vCommentKeys)
                    vKeysToDecrypt.push_back(atoi(strCommentKey.c_str()));

                pFile = tmpfile();

                for (auto i = 0; i < uSize; i++)
                    fputc(buffer[i] ^ (vKeysToDecrypt[i % vKeysToDecrypt.size()]), pFile);

                rewind(pFile);

                iFileSize = uSize;
            }
            catch (...)
            {
                zip->Close(CZipArchive::afAfterException);
                throw;
            }
        }
    }

    return pFile;
}

void PackageFile::CloseFile()
{
    if (pFile)
    {
        fclose(pFile);
        pFile = nullptr;
    }
}

void PackageFile::ClosePackage(CZipArchive* zip)
{
    if (zip)
    {
        zip->Close();

        for (auto it = cachedPackageFiles.begin(); it != cachedPackageFiles.end(); ++it)
        {
            if (it->second == zip)
            {
                cachedPackageFiles.erase(it);
                break;
            }
        }
    }
}