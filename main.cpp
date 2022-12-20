// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <bits/stdc++.h>
#undef _MBCS
#define _UNICODE
#define UNICODE
// Global variables

// The main window class name.
static wchar_t szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static wchar_t szTitle[] = _T("Attention");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

const int fheight = 30;

// Forward declarations of functions included in this code module:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
   WNDCLASSEXW wcex;

   wcex.cbSize = sizeof(WNDCLASSEX);
   wcex.style = CS_HREDRAW | CS_VREDRAW;
   wcex.lpfnWndProc = WndProc;
   wcex.cbClsExtra = 0;
   wcex.cbWndExtra = 0;
   wcex.hInstance = hInstance;
   wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
   wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
   wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
   wcex.lpszMenuName = NULL;
   wcex.lpszClassName = szWindowClass;
   wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

   if (!RegisterClassExW(&wcex))
   {
      MessageBoxW(NULL,
                  _T("Call to RegisterClassEx failed!"),
                  _T("Windows Desktop Guided Tour"),
                  NULL);

      return 1;
   }

   // Store instance handle in our global variable
   hInst = hInstance;

   // The parameters to CreateWindowEx explained:
   // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
   // szWindowClass: the name of the application
   // szTitle: the text that appears in the title bar
   // WS_OVERLAPPEDWINDOW: the type of window to create
   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
   // 500, 100: initial size (width, length)
   // NULL: the parent of this window
   // NULL: this application does not have a menu bar
   // hInstance: the first parameter from WinMain
   // NULL: not used in this application
   HWND hWnd = CreateWindowExW(
       WS_EX_OVERLAPPEDWINDOW,
       szWindowClass,
       szTitle,
       WS_BORDER,
       CW_USEDEFAULT, CW_USEDEFAULT,
       150, fheight * 10,
       NULL,
       NULL,
       hInstance,
       NULL);
   HWND Button1 = CreateWindow(
       L"BUTTON",
       L"关闭窗口",
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
       5, fheight * 8,
       130, fheight,
       hWnd,
       NULL,
       hInstance,
       NULL);

   CreateText();
   if (!hWnd)
   {
      MessageBoxW(NULL,
                  _T("Call to CreateWindow failed!"),
                  _T("Windows Desktop Guided Tour"),
                  NULL);

      return 1;
   }

   // The parameters to ShowWindow explained:
   // hWnd: the value returned from CreateWindow
   // nCmdShow: the fourth parameter from WinMain
   ShowWindow(hWnd,
              nCmdShow);
   UpdateWindow(hWnd);
   ShowWindow(Button1,
              nCmdShow);
   UpdateWindow(Button1);

   // Main message loop:
   MSG msg;
   while (GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }

   return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   PAINTSTRUCT ps;
   HDC hdc;
   wchar_t greeting[] = _T("Task List");
   wchar_t tasks[5][10] = {_T("Task1"), _T("Task1"), _T("Task1"), _T("Task1"), _T("Task1")};
   HFONT hFontOriginal, hFont1, hFont2;
   switch (message)
   {
   case WM_PAINT:
      SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
      hdc = BeginPaint(hWnd, &ps);
      // Here your application is laid out.
      // For this introduction, we just print out "Hello, Windows desktop!"
      // in the top left corner. _tcslen(greeting)
      hFont1 = CreateFont(fheight, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                          CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("等线"));
      hFont2 = CreateFont(fheight, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                          CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("等线"));
      hFontOriginal = (HFONT)SelectObject(hdc, hFont1);
      // Sets the coordinates for the rectangle in which the text is to be formatted.
      //  SetRect(&rect, 100,100,700,200);
      //  SetTextColor(hdc, RGB(255,0,0));
      TextOutW(hdc, 5, 5, greeting, _tcslen(greeting));
      SelectObject(hdc, hFont2);
      for (int i = 0; i < 5; i++)
      {
         TextOutW(hdc, 5, 5 + fheight * (i + 1), tasks[i], _tcslen(tasks[i]));
      }
      // End application-specific layout section.
      EndPaint(hWnd, &ps);
      break;
   case WM_DESTROY:
      PostQuitMessage(0);
      break;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
      break;
   }

   return 0;
}
