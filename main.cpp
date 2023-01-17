// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <bits/stdc++.h>
#undef _MBCS
#define _UNICODE
#define UNICODE

#define mainwindow 0x0401
#define BUTTON1_CLICKED 0x0402
#define BUTTON2_CLICKED 0x0403
#define MSGBOX1 0x0404
static wchar_t szWindowClass[] = _T("DesktopApp");
static wchar_t szTitle[] = _T("Attention");
static wchar_t szWindowClass2[] = _T("Msgbox1");
static wchar_t szTitle2[] = _T("Attention");
HINSTANCE hInst;
HWND Main, Msgbox1;
const int fheight = 30;
int ncmds, task_count, Msgbox1_status;
wchar_t greeting[] = _T("Task List");
wchar_t tasks[10][10] = {_T("Task1"), _T("Task1"), _T("Task1"), _T("Task1"), _T("Task1")};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);
int formating();

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    // init data
    // FILE *file=fopen("sfw.cfg","r");
    // char tempchar[100];
    // fgets(tempchar,1,file);
    // task_count=tempchar[0]-48;
    // for(int i=0;i<task_count;i++){
    //     fgets(tempchar,1,file);
    //     tasks[i]=_T(tempchar);
    // }

    WNDCLASSEXW wcex, wcex2;

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

    wcex2 = wcex;
    wcex2.lpfnWndProc = WndProc2;
    wcex2.lpszClassName = szWindowClass2;
    wcex2.hbrBackground = CreateSolidBrush(RGB(1, 36, 86));

    if (!RegisterClassExW(&wcex) || !RegisterClassExW(&wcex2))
    {
        MessageBoxW(NULL,
                    _T("Call to RegisterClassEx failed!"),
                    _T("Windows Desktop Guided Tour"),
                    NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;
    ncmds = nCmdShow;
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
        150, fheight * 12 + 5,
        NULL,
        NULL, // (HMENU)mainwindow,
        hInstance,
        NULL);
    HWND Button1 = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        L"BUTTON",
        L"关闭窗口",
        WS_CHILD, //  WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        5, fheight * 9,
        130, fheight,
        hWnd,
        (HMENU)BUTTON1_CLICKED,
        hInst,
        NULL);
    HWND Button2 = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        L"BUTTON",
        L"***",
        WS_CHILD, //  WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        5, fheight * 10,
        130, fheight,
        hWnd,
        (HMENU)BUTTON2_CLICKED,
        hInst,
        NULL);
    HWND msgbox1 = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass2,
        szTitle2,
        WS_POPUP,
        85, 340,
        1190, 100,
        hWnd,
        NULL, // (HMENU)MSGBOX1,
        hInst,
        NULL);
    Main = hWnd;
    Msgbox1 = msgbox1;
    // CreateText();
    if (!hWnd || !Button1 || !Button2 || !msgbox1)
    {
        MessageBoxW(NULL,
                    _T("Call to CreateWindow failed!"),
                    _T("Windows Desktop Guided Tour"),
                    NULL);

        return 1;
    }

    Msgbox1_status = SW_HIDE;
    HFONT hFont2 = CreateFont(fheight / 2, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                              CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("等线"));
    SendDlgItemMessage(Button1, BUTTON1_CLICKED, WM_SETFONT, (WPARAM)hFont2, TRUE);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    ShowWindow(Button1, nCmdShow);
    UpdateWindow(Button1);
    ShowWindow(Button2, nCmdShow);
    UpdateWindow(Button2);
    SendDlgItemMessage(Button2, BUTTON1_CLICKED, WM_SETFONT, (WPARAM)hFont2, TRUE);

    // FILE* hwndlog=fopen("hwndlog.txt","a+");
    // fprintf(hwndlog, hWnd);
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
//  PURPOSE:  Processes messages for the main window.
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // const int Mainconst=(int)Main, Msgbox1const=(int)Msgbox1;
    PAINTSTRUCT ps;
    HDC hdc;
    wchar_t greeting[] = _T("Task List");
    wchar_t tasks[5][10] = {_T("Task1"), _T("Task1"), _T("Task1"), _T("Task1"), _T("Task1")};
    HFONT hFontOriginal, hFont1, hFont2;
    switch (message)
    {
    case WM_CREATE:
    {
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    case WM_PAINT:
    {
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
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    case WM_COMMAND:
    {
        int iMID = LOWORD(wParam);
        if (((HWND)lParam) && (HIWORD(wParam) == BN_CLICKED))
            switch (iMID)
            {
            case BUTTON1_CLICKED:
            {
                PostQuitMessage(0);
                break;
            }
            case BUTTON2_CLICKED:
            {
                // ShowWindow(Msgbox1, ncmds);
                // UpdateWindow(Msgbox1);
                switch (Msgbox1_status)
                {
                case SW_HIDE:
                {
                    Sleep(150);
                    ShowWindow(Msgbox1, SW_SHOW);
                    UpdateWindow(Msgbox1);
                    Msgbox1_status = SW_SHOW;
                    break;
                }
                case SW_SHOW:
                {
                    ShowWindow(Msgbox1, SW_HIDE);
                    Msgbox1_status = SW_HIDE;
                }
                }
                break;
            }
            default:
                break;
            }
        break;
    }
    default:
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    }

    return 0;
}

LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // const int Mainconst=(int)Main, Msgbox1const=(int)Msgbox1;
    PAINTSTRUCT ps;
    HDC hdc;
    wchar_t greeting[] = _T("Task List");
    wchar_t tasks[5][10] = {_T("Task1"), _T("Task1"), _T("Task1"), _T("Task1"), _T("Task1")};
    HFONT hFontOriginal, hFont1, hFont2;
    switch (message)
    {
    case WM_CREATE:
    {
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        hFont1 = CreateFont(fheight * 1.5, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH , TEXT("等线"));
        hFont2 = CreateFont(fheight * 1.5, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH , TEXT("等线"));
        hFontOriginal = (HFONT)SelectObject(hdc, hFont1);
        // Sets the coordinates for the rectangle in which the text is to be formatted. TEXT("等线") | TEXT("Terminal")
        //  SetRect(&rect, 100,100,700,200);| VTA_CENTER  FW_BOLD  FW_DONTCARE
        SetTextColor(hdc, RGB(255, 255, 255));
        SetBkMode(hdc, TRANSPARENT);
        SetTextAlign(hdc, GetTextAlign(hdc) | TA_CENTER | VTA_CENTER);
        wchar_t warning[] = _T("Warning: Unauthorized Entry");
        wchar_t detail[] = _T("Manual Override Invaild.");
        Sleep(150);
        TextOutW(hdc, 495, 0, warning, _tcslen(warning));
        SetTextColor(hdc, RGB(255, 0, 0));
        SelectObject(hdc, hFont2);
        TextOutW(hdc, 495, fheight * 1.5, detail, _tcslen(detail));
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    default:
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    }
    return 0;
}
