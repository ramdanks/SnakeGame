#include "prototyping.h"
#include "datastructure.h"

RECT rect;
HINSTANCE hInst;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
    FreeConsole();
    initData();
    if (head==NULL)
        puts("null");

    RegisterMain(hInstance);
    if (!MainInstance(hInstance, nCmdShow))
        return FALSE;

    RegisterContent(hInstance);
    if (!ContentInstance(hInstance, nCmdShow))
        return FALSE;

    RegisterGame(hInstance);
    if (!GameInstance(hInstance, nCmdShow))
        return FALSE;

    RegisterSetting(hInstance);
    if (!SettingInstance(hInstance))
        return FALSE;

    RegisterAbout(hInstance);
    if (!AboutInstance(hInstance))
        return FALSE;

    RegisterLeaderboard(hInstance);
    //Buat Window Instance nya pada saat CALLBACK MAIN
    //karena leaderboard instance akan diupdate terus skornya sehingga window diperbaharui terus

    //Message Loop
    MSG Msg;
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK MainProc (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT     ps;
    HDC             hdc;
    BITMAP          bitmap;
    HDC             hdcMem;
    HGDIOBJ         oldBitmap;

    if(Pressed == TRUE)
        update();

    switch(Msg)
    {
        case WM_TIMER:
            if (bFlag == 0 )
            {
                nTick ++;
                if(point == 0)
                    nTick = 0;
                InvalidateRect(game_hWnd, NULL, TRUE);
            }
        break;

        case WM_KEYDOWN:
            if (nowKeyNumber != NULL)
                regKey = wParam;
            else
                nowKeyNumber = wParam;
            switch(wParam)
            {
                case VK_SPACE:
                    turbo = TRUE;
                break;
            }

        break;

        case WM_KEYUP:
            switch(wParam)
            {
            case VK_SPACE:
                turbo = FALSE;
            break;
            }
        break;

        case WM_COMMAND:
            switch(wParam)
            {
                case PLAY_BUTTON:
                    puts("play");
                    update();
                    if (isSound.check == TRUE)
                        PlaySound("assets/sounds/start.wav",NULL,SND_FILENAME | SND_ASYNC );
                    ShowWindow(con_hWnd, SW_SHOW);
                    ShowWindow(game_hWnd, SW_SHOW);
                    SetTimer(hWnd,1,cpuTime,NULL);
                break;

                case LEADERBOARD_BUTTON:
                    puts("leaderboard");
                    update();
                    LeaderboardInstance(hInst);
                break;

                case EXIT_BUTTON:
                    eksportData();
                    PostQuitMessage(0);
                break;

                case ABOUT_BUTTON:
                    puts("leaderboard");
                    update();
                    ShowWindow(about_hWnd, SW_SHOW);
                break;

                case SETTINGS_BUTTON:
                    puts("settings");
                    update();
                    ShowWindow(setting_hWnd, SW_SHOW);
                break;

                default:
                    return DefWindowProc(hWnd, Msg, wParam, lParam);
            }
            break;

        case WM_CREATE:
            update_welcome(hWnd);
            menu(hWnd);
        break;

        case WM_DESTROY:
            eksportData();
            PostQuitMessage(0);
        break;

        case WM_PAINT:
            check_background();
            hBitmap = (HBITMAP)LoadImage(NULL, background, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            hdc = BeginPaint(hWnd, &ps);
            hdcMem = CreateCompatibleDC(hdc);
            oldBitmap = SelectObject(hdcMem, hBitmap);
            GetObject(hBitmap, sizeof(bitmap), &bitmap);
            BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
            SelectObject(hdcMem, oldBitmap);
            DeleteDC(hdcMem);
            EndPaint(hWnd, &ps);
        break;

        default:
            return DefWindowProc(hWnd, Msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ContentProc (HWND con_hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg)
    {
        case WM_COMMAND:
            switch(wParam)
            {
                case BACK_BUTTON:
                    reStart();
                    destroy_game();
                break;
                default:
                    return DefWindowProc(con_hWnd, Msg, wParam, lParam);
            }
        break;

        default:
            return DefWindowProc(con_hWnd, Msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK LeaderboardProc (HWND leaderboard_hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg)
    {
        case WM_COMMAND:
            switch(wParam)
            {
                case BACK_BUTTON:
                    DestroyWindow(leaderboard_hWnd);
                    Pressed=TRUE;
                break;

                case RESET_BUTTON:
                    head = NULL;
                    free(head);
                    DestroyWindow(leaderboard_hWnd);
                    LeaderboardInstance(hInst);
                break;

                default:
                    return DefWindowProc(leaderboard_hWnd, Msg, wParam, lParam);
            }
        break;

        default:
            return DefWindowProc(leaderboard_hWnd, Msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK GameProc (HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HDC	hMyDC;
    PAINTSTRUCT	ps;

    switch(Msg)
    {
       case WM_PAINT:

        	hMyDC=BeginPaint(hwnd, &ps);
            randStar();
            speed();
            starAndSnakeHand(hwnd,hMyDC);
            walked();
            spd = 50 - cpuTime;
        	if (isDebug.check == TRUE)
                show_debug(hwnd, hMyDC);
            if (perform() == 1)
            {
                keyClicked();
            }
            PrintTail(hwnd, hMyDC);
            outLine(hwnd);
            EndPaint(hwnd, &ps);
        break;

        default:
            return DefWindowProc(hwnd, Msg, wParam, lParam);
    }
        return 0;
}

LRESULT CALLBACK SettingProc (HWND setting_hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg)
    {
        case WM_COMMAND:
            switch(wParam)
            {
                case BKG1_BUTTON:
                    if (bkgchoice != 1)
                        {
                            bkgchoice = 1;
                            update_setting();
                        }

                break;
                case BKG2_BUTTON:
                    if (bkgchoice != 2)
                        {
                            bkgchoice = 2;
                            update_setting();
                        }
                break;
                case BKG3_BUTTON:
                    if (bkgchoice != 3)
                        {
                            bkgchoice = 3;
                            update_setting();
                        }
                break;
                case BKG4_BUTTON:
                    if (bkgchoice != 4)
                        {
                            bkgchoice = 4;
                            update_setting();
                        }
                break;
                case ON_BUTTON:
                    isDebug.check = TRUE;
                    update_toggle(isDebug.type);
                break;
                case OFF_BUTTON:
                    isDebug.check = FALSE;
                    update_toggle(isDebug.type);
                break;
                case ONS_BUTTON:
                    isSound.check = TRUE;
                    update_toggle(isSound.type);
                break;
                case OFFS_BUTTON:
                    isSound.check = FALSE;
                    update_toggle(isSound.type);
                break;
                case APPLY_BUTTON:
                    destroy_setting();
                    GetWindowText(hUser, user, 16);
                    update_welcome(hWnd);
                    puts("Applying Changes");
                break;
                default:
                    return DefWindowProc(setting_hWnd, Msg, wParam, lParam);
            }
            break;

        default:
            return DefWindowProc(setting_hWnd, Msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK AboutProc (HWND about_hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT     ps;
    HDC             hdc;
    BITMAP          bitmap;
    HDC             hdcMem;
    HGDIOBJ         oldBitmap;

    switch(Msg)
    {
        case WM_COMMAND:
            switch(wParam)
            {
                case 20:
                    destroy_about();
                break;

                default:
                    return DefWindowProc(about_hWnd, Msg, wParam, lParam);
            }
        break;

        case WM_PAINT:
            check_background();
            hBitmap = (HBITMAP)LoadImage(NULL, background_about, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            hdc = BeginPaint(about_hWnd, &ps);
            hdcMem = CreateCompatibleDC(hdc);
            oldBitmap = SelectObject(hdcMem, hBitmap);
            GetObject(hBitmap, sizeof(bitmap), &bitmap);
            BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
            SelectObject(hdcMem, oldBitmap);
            DeleteDC(hdcMem);
            EndPaint(about_hWnd, &ps);
        break;

        default:
            return DefWindowProc(about_hWnd, Msg, wParam, lParam);
    }
    return 0;
}

ATOM RegisterMain(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = 0;
    wcex.lpfnWndProc    = MainProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = MainClass;
    wcex.hIconSm        = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));

    return RegisterClassExW(&wcex);
}

ATOM RegisterContent(HINSTANCE hInstance)
{
    WNDCLASSW wcex;

    wcex.style          = 0;
    wcex.lpfnWndProc    = ContentProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, NULL);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+6);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = ContentClass;

    return RegisterClassW(&wcex);
}

ATOM RegisterGame(HINSTANCE hInstance)
{
    WNDCLASSW wcex;

    wcex.style          = 0;
    wcex.lpfnWndProc    = GameProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, NULL);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);

    LOGBRUSH background;
    background.lbStyle     = BS_PATTERN;
    background.lbHatch     = (long) LoadImage(hInstance,
                            background_battle,
                            IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    //Set Background
    if(background.lbHatch != 0)
        wcex.hbrBackground = CreateBrushIndirect(&background);
    else
        wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = GameClass;

    free(background.lbHatch);
    return RegisterClassW(&wcex);
}

ATOM RegisterSetting(HINSTANCE hInstance)
{
    WNDCLASSW wcex;

    wcex.style          = 0;
    wcex.lpfnWndProc    = SettingProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, NULL);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);

    LOGBRUSH background;
    background.lbStyle     = BS_PATTERN;
    background.lbHatch     = (long) LoadImage(hInstance,
                            "assets/background/set.bmp",
                            IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    //Set Background
    if(background.lbHatch != 0)
        wcex.hbrBackground = CreateBrushIndirect(&background);
    else
        wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = SettingClass;

    return RegisterClassW(&wcex);
}

ATOM RegisterLeaderboard(HINSTANCE hInstance)
{
    WNDCLASSW wcex;

    wcex.style          = 0;
    wcex.lpfnWndProc    = LeaderboardProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, NULL);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);

    LOGBRUSH background;
    background.lbStyle     = BS_PATTERN;
    background.lbHatch     = (long) LoadImage(hInstance,
                            "assets/background/lead.bmp",
                            IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    //Set Background
    if(background.lbHatch != 0)
        wcex.hbrBackground = CreateBrushIndirect(&background);
    else
        wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = LeaderboardClass;

    return RegisterClassW(&wcex);
}

ATOM RegisterAbout (HINSTANCE hInstance)
{
    WNDCLASSW wc;

    wc.style          = 0;
    wc.lpfnWndProc    = AboutProc;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;
    wc.hInstance      = hInstance;
    wc.hIcon          = LoadIcon(hInstance, NULL);
    wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName   = NULL;
    wc.lpszClassName  = AboutClass;

    return RegisterClassW(&wc);
}

BOOL AboutInstance(HINSTANCE hInstance)
{
    about_hWnd = CreateWindowW   (AboutClass, "About", WS_CHILD | WS_VISIBLE,
                            0, 0, 960, 600,
                            hWnd, NULL, hInstance, NULL);

    if (!about_hWnd)
    {
        return FALSE;
    }

    ShowWindow(about_hWnd, SW_HIDE);
    UpdateWindow(about_hWnd);
    about();
    return TRUE;
}

BOOL LeaderboardInstance(HINSTANCE hInstance)
{
    leaderboard_hWnd = CreateWindowW   (LeaderboardClass, "Leaderboard", WS_CHILD | WS_VISIBLE,
                                    0, 0, 960, 600,
                                    hWnd, NULL, hInstance, NULL);

    if (!leaderboard_hWnd)
    {
        return FALSE;
    }

    ShowWindow(leaderboard_hWnd, SW_HIDE);
    UpdateWindow(leaderboard_hWnd);
    leaderboard();
    ShowWindow(leaderboard_hWnd, SW_SHOW);
    return TRUE;
}

BOOL MainInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    center_window(GetDesktopWindow(), 960, 600);
    hWnd = CreateWindowW   (MainClass, "Snake", WS_SYSMENU | WS_MINIMIZEBOX,
                            rect.left, rect.top, 960, 600,
                            NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    return TRUE;
}

BOOL ContentInstance(HINSTANCE hInstance, int nCmdShow)
{
    con_hWnd = CreateWindowW   (ContentClass, "Content", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                20, 20, wnd_W-290, wnd_H,
                                hWnd, NULL, hInstance, NULL);

    if (!con_hWnd)
    {
        return FALSE;
    }

    ShowWindow(con_hWnd, SW_HIDE);
    UpdateWindow(con_hWnd);
    content();

    return TRUE;
}

BOOL GameInstance(HINSTANCE hInstance, int nCmdShow)
{
    game_hWnd = CreateWindowW   (GameClass, "Game", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                340, 20,
                                wnd_W, wnd_H,
                                hWnd, NULL, hInstance, NULL);
    GetSystemMetrics(SM_CXSCREEN);
    GetSystemMetrics(SM_CYSCREEN);

    if (!game_hWnd)
    {
        return FALSE;
    }

    ShowWindow(game_hWnd, SW_HIDE);
    UpdateWindow(game_hWnd);

    return TRUE;
}

BOOL SettingInstance(HINSTANCE hInstance)
{
    setting_hWnd = CreateWindowW   (SettingClass, "Setting", WS_CHILD | WS_VISIBLE,
                            0, 0, 960, 600,
                            hWnd, NULL, hInstance, NULL);

    if (!setting_hWnd)
    {
        return FALSE;
    }

    ShowWindow(setting_hWnd, SW_HIDE);
    UpdateWindow(setting_hWnd);
    setting();
    return TRUE;
}

void menu(HWND hWnd)
{
    hPlay = CreateWindowW(L"Button", L"Play", WS_VISIBLE | WS_CHILD | BS_BITMAP, 20, 160, 200, 70, hWnd, (HMENU)PLAY_BUTTON, NULL, NULL);
    hLeaderboard = CreateWindowW(L"Button", L"Leaderboard", WS_VISIBLE | WS_CHILD | BS_BITMAP, 20, 240, 200, 70, hWnd, (HMENU)LEADERBOARD_BUTTON, NULL, NULL);
	hShops = CreateWindowW(L"Button", L"Shops", WS_VISIBLE | WS_CHILD | BS_BITMAP, 20, 320, 200, 70, hWnd, (HMENU)SHOPS_BUTTON, NULL, NULL);
	hAbout = CreateWindowW(L"Button", L"About", WS_VISIBLE | WS_CHILD | BS_BITMAP, 20, 400, 200, 70, hWnd, (HMENU)ABOUT_BUTTON, NULL, NULL);
	hExit = CreateWindowW(L"Button", L"Exit", WS_VISIBLE | WS_CHILD | BS_BITMAP, 20, 480, 200, 70, hWnd, (HMENU)EXIT_BUTTON, NULL, NULL);
	hSettings = CreateWindowW(L"Button", L"Settings", WS_VISIBLE | WS_CHILD , 830, 20, 100, 40, hWnd, (HMENU)SETTINGS_BUTTON, NULL, NULL);
	update_menu();
}

int center_window(HWND parent_window, int width, int height)
{
    GetClientRect(parent_window, &rect);
    rect.left = (rect.right/2) - (width/2);
    rect.top = (rect.bottom/2) - (height/2);
    return 0;
}

void destroy_game()
{
    PlaySound(NULL, 0, 0);
    ShowWindow(con_hWnd, SW_HIDE);
    ShowWindow(game_hWnd, SW_HIDE);
    Pressed = TRUE;
}

void destroy_setting()
{
    ShowWindow(setting_hWnd, SW_HIDE);
    Pressed = TRUE;
}

void destroy_about()
{
    ShowWindow(about_hWnd, SW_HIDE);
    Pressed = TRUE;
}

void content()
{
    hBack = CreateWindowW(L"Button", L"Back", WS_VISIBLE | WS_CHILD, 50, 500, 200, 30, con_hWnd, (HMENU)BACK_BUTTON, NULL, NULL);
}

void setting()
{
        //PlayerName Setting
        CreateWindowW(L"Button", L"Player Name", WS_VISIBLE | WS_CHILD, 240, 20, 100, 30, setting_hWnd, NULL, NULL, NULL);
        hUser = CreateWindowW(L"Edit", L"Default", WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | WS_BORDER, 350, 20, 300, 30, setting_hWnd, NULL, NULL, NULL);
        //Background Setting
        hBackground1 = CreateWindowW(L"Button", L"1", WS_VISIBLE | WS_CHILD | BS_BITMAP, 75, 70, 192, 120, setting_hWnd, (HMENU)BKG1_BUTTON, NULL, NULL);
        hBackground2 = CreateWindowW(L"Button", L"2", WS_VISIBLE | WS_CHILD | BS_BITMAP, 277, 70, 192, 120, setting_hWnd, (HMENU)BKG2_BUTTON, NULL, NULL);
        hBackground3 = CreateWindowW(L"Button", L"3", WS_VISIBLE | WS_CHILD | BS_BITMAP, 479, 70, 192, 120, setting_hWnd, (HMENU)BKG3_BUTTON, NULL, NULL);
        hBackground4 = CreateWindowW(L"Button", L"4", WS_VISIBLE | WS_CHILD | BS_BITMAP, 681, 70, 192, 120, setting_hWnd, (HMENU)BKG4_BUTTON, NULL, NULL);
        update_setting();
        //Apply Button
        hApply = CreateWindowW(L"Button", L"APPLY", WS_VISIBLE | WS_CHILD , 230, 510, 500, 40, setting_hWnd, (HMENU)APPLY_BUTTON, NULL, NULL);
        //Debug Setting
        CreateWindowW(L"Button", L"DISPLAY DEBUG", WS_VISIBLE | WS_CHILD , 75, 220, 200, 40, setting_hWnd, NULL, NULL, NULL);
        hOn = CreateWindowW(L"Button", L"ON", WS_VISIBLE | WS_CHILD  | BS_BITMAP, 330, 220, 100, 40, setting_hWnd, (HMENU)ON_BUTTON, NULL, NULL);
        hOff = CreateWindowW(L"Button", L"OFF", WS_VISIBLE | WS_CHILD | BS_BITMAP, 430, 220, 100, 40, setting_hWnd, (HMENU)OFF_BUTTON, NULL, NULL);
        update_toggle(isDebug.type);
        //Sound Setting
        CreateWindowW(L"Button", L"PLAY SOUND", WS_VISIBLE | WS_CHILD , 75, 280, 200, 40, setting_hWnd, NULL, NULL, NULL);
        hOnS = CreateWindowW(L"Button", L"ON", WS_VISIBLE | WS_CHILD | BS_BITMAP, 330, 280, 100, 40, setting_hWnd, (HMENU)ONS_BUTTON, NULL, NULL);
        hOffS = CreateWindowW(L"Button", L"OFF", WS_VISIBLE | WS_CHILD | BS_BITMAP, 430, 280, 100, 40, setting_hWnd, (HMENU)OFFS_BUTTON, NULL, NULL);
        update_toggle(isSound.type);
}

void about()
{
    HWND hImage;
    hReturn = CreateWindowW(L"Button", L"BACK", WS_VISIBLE | WS_CHILD , 230, 510, 500, 40, about_hWnd, (HMENU)20, NULL, NULL);
    hRamdan = CreateWindowW(L"Button", L"Creator", WS_VISIBLE | WS_CHILD | BS_BITMAP , 100, 30, 120, 160, about_hWnd, NULL, NULL, NULL);
    hDiaz = CreateWindowW(L"Button", L"Creator", WS_VISIBLE | WS_CHILD | BS_BITMAP, 730, 30, 120, 160, about_hWnd, NULL, NULL, NULL);
    HWND hBar = CreateWindowW(L"Button", L"NAME", WS_VISIBLE | WS_CHILD | BS_BITMAP, 220, 130, 510, 60, about_hWnd, NULL, NULL, NULL);
    HWND hBar2 = CreateWindowW(L"Button", L"NAME", WS_VISIBLE | WS_CHILD | BS_BITMAP, 220, 70, 510, 60, about_hWnd, NULL, NULL, NULL);

    hImage = (HBITMAP)LoadImageW(NULL, L"assets\\ramdanbar.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessageW(hBar, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
    hImage = (HBITMAP)LoadImageW(NULL, L"assets\\diazbar.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessageW(hBar2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
    hImage = (HBITMAP)LoadImageW(NULL, L"assets\\ramdan.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessageW(hRamdan, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
    hImage = (HBITMAP)LoadImageW(NULL, L"assets\\diaz.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessageW(hDiaz, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
}

void leaderboard()
{
    //Sort Data Structure
    sorting();
    hReset = CreateWindowW(L"Button", L"Reset", WS_VISIBLE | WS_CHILD , 839, 10, 94, 88, leaderboard_hWnd, (HMENU)RESET_BUTTON, NULL, NULL);
    hBackLead = CreateWindowW(L"Button", L"Back", WS_VISIBLE | WS_CHILD , 15, 10, 94, 88, leaderboard_hWnd, (HMENU)BACK_BUTTON, NULL, NULL);
    struct node *ptr = head;
    WCHAR namebar[16];
    WCHAR score[8];
    int loop=0;
    int xAdder = 0, yAdder = 0;

    while (ptr != NULL)
    {
        if(loop > 0 && loop%7==0)
        {
            xAdder = 489;
            yAdder = 0;
        }
        char temp[16];
        //Change int and char array to LPCSTR
        sprintf(temp, "%s", ptr->name);
        swprintf(namebar, L"%S", temp);
        sprintf(temp, "%d", ptr->point);
        swprintf(score, L"%S", temp);
        //Create Window for Player Leaderboard
        CreateWindowW(L"Button", score, WS_VISIBLE | WS_CHILD, 350+xAdder, 176+57*yAdder, 99, 43, leaderboard_hWnd, NULL, NULL, NULL);
        CreateWindowW(L"Button", namebar, WS_VISIBLE | WS_CHILD, 128+xAdder, 176+57*yAdder, 204, 43, leaderboard_hWnd, NULL, NULL, NULL);
        //Next data
        ptr = ptr->next;
        yAdder++;
        loop++;
        //Membatasi Banyaknya Tampilan Window di Leaderboard
        if (loop>=14)
            break;
    }
}

void update_welcome(HWND hWnd)
{
    DestroyWindow(hWelcome);
    sprintf(szWelcome, "Welcome : %s", user);
    swprintf(welcome_char, L"%S", szWelcome);
    hWelcome = CreateWindowW(L"Button", welcome_char, WS_VISIBLE | WS_CHILD, 20, 130, 200, 30, hWnd, NULL, NULL, NULL);
}

int perform()
{
    if ((nowX%30 - 12) == 0)
    {
        if ((nowY%30 - 12) == 0)
        {
            return 1;
        }
        nowX = nowX + moveX;
        nowY = nowY + moveY;
    }
    else
    {
        nowX = nowX + moveX;
        nowY = nowY + moveY;
        return 0;
    }
}
