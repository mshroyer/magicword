#include "StdAfx.h"
#include "ImageResource.h"

ImageResource::ImageResource(LPCTSTR lpName, HMODULE hInst, LPCTSTR lpType)
{
    this->hBuffer = NULL;
    this->lpImage = NULL;
    this->Load(lpName, hInst, lpType);
}


ImageResource::~ImageResource(void)
{
    delete this->lpImage;
    this->lpImage = NULL;

    if ( this->hBuffer ) {
        GlobalUnlock(this->hBuffer);
        GlobalFree(this->hBuffer);
        this->hBuffer = NULL;
    }
}


bool ImageResource::Load(LPCTSTR lpName, HMODULE hInst, LPCTSTR lpType)
{
    HRSRC hRes = FindResource(hInst, lpName, lpType);
    if ( ! hRes ) return false;

    DWORD size = SizeofResource(hInst, hRes);
    if ( ! size ) return false;

    // Even though LoadResource() has the return type HGLOBAL, we can't pass
    // its result directly to CreateStreamOnHGlobal() because it expects a
    // global handle allocated by GlobalAlloc with the GMEM_MOVABLE flag.  (MSDN
    // suggests this might work anyway, but the program crashed when I actually
    // tried it.)  So we have to manually create an intermediate buffer here.
    // For more information, see:
    //
    // http://msdn.microsoft.com/en-us/library/aa378980(VS.85).aspx
    // http://www.codeproject.com/KB/GDI-plus/cgdiplusbitmap.aspx?msg=443358
    //
    const void* lpResData = LockResource(LoadResource(hInst, hRes));
    if ( ! lpResData ) return false;

    this->hBuffer = GlobalAlloc(GMEM_MOVEABLE, size);
    if ( ! this->hBuffer ) return false;

    void* lpBuffer = GlobalLock(hBuffer);
    if ( ! lpBuffer ) return false;

    CopyMemory(lpBuffer, lpResData, size);
    IStream* lpStream = NULL;
    HRESULT result = CreateStreamOnHGlobal(hBuffer, FALSE, &lpStream);
    if ( FAILED(result) ) return false;

    this->lpImage = Gdiplus::Image::FromStream(lpStream);
    lpStream->Release();
    if ( this->lpImage->GetLastStatus() != Gdiplus::Ok ) return false;

    return true;
}
