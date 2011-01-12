#include "stdafx.h"

#include "Hyperlink.h"
#include "LogString.h"

ATOM Hyperlink::Register(HINSTANCE hInst, LPCTSTR szClassName)
{
    WNDCLASSEX wcex;

    wcex.cbSize         = sizeof(wcex);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = Hyperlink::WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInst;
    wcex.hIcon          = NULL;
    wcex.hCursor        = LoadCursor(NULL, IDC_HAND);
    wcex.hbrBackground  = (HBRUSH) GetSysColorBrush(COLOR_3DFACE);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szClassName;
    wcex.hIconSm        = NULL;

    return RegisterClassEx(&wcex);
}


LRESULT CALLBACK Hyperlink::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    COLORREF clrLink = RGB(0x00, 0x66, 0xcc);
    COLORREF clrActive = RGB(0xc8, 0x00, 0x00);
    LOGFONT lfn;
    HFONT hPrevFont;
    TRACKMOUSEEVENT tme;
    static TCHAR szLink[100];
    static HFONT hFont;
    static bool active = false;

    switch ( message )
    {
    case WM_CREATE:
        GetWindowText(hwnd, szLink, sizeof(szLink) / sizeof(TCHAR));
        return 0;

    case WM_SETFONT:
        GetObject((HFONT) wParam, sizeof(lfn), &lfn);
        lfn.lfUnderline = TRUE;
        hFont = CreateFontIndirect(&lfn);
        return 0;

    case WM_PAINT:
        GetClientRect(hwnd, &rect);

        hdc = BeginPaint(hwnd, &ps);

        hPrevFont = (HFONT) SelectObject(hdc, hFont);
        SetBkColor(hdc, GetSysColor(COLOR_3DFACE));
        SetTextColor(hdc, active ? clrActive : clrLink);
        DrawText(hdc, szLink, -1, &rect, DT_SINGLELINE | DT_VCENTER);
        SelectObject(hdc, hPrevFont);

        EndPaint(hwnd, &ps);
        return 0;

    case WM_LBUTTONDOWN:
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.hwndTrack = hwnd;
        TrackMouseEvent(&tme);
        active = true;
        InvalidateRgn(hwnd, NULL, FALSE);
        UpdateWindow(hwnd);
        return 0;

    case WM_LBUTTONUP:
        if ( active )
            ShellExecute(NULL, _T("open"), szLink, NULL, NULL, SW_SHOWNORMAL);
    case WM_MOUSELEAVE:
        if ( active ) {
            active = false;
            InvalidateRgn(hwnd, NULL, FALSE);
            UpdateWindow(hwnd);
        }
        return 0;

    case WM_DESTROY:
        DeleteObject(hFont);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}
