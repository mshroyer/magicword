#pragma once

namespace Hyperlink
{
    ATOM Register(HINSTANCE hInst, LPCTSTR szClassName);
    LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
}
