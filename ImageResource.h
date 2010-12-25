#pragma once

// Encapsulate instantiation of GDI+ Images from RCDATA
class ImageResource
{
public:
	ImageResource(LPCTSTR lpName, HMODULE hInst = NULL, LPCTSTR lpType = MAKEINTRESOURCE(RT_RCDATA));
	~ImageResource(void);
	Gdiplus::Image* lpImage;

private:
	HGLOBAL hBuffer;
	void* lpBuffer;
	bool Load(LPCTSTR lpName, HMODULE hInst, LPCTSTR lpType);
};
