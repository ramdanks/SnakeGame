#include "prototyping.h"
#include "datastructure.h"

RECT rect;
HINSTANCE hInst;
PAINTSTRUCT     ps;
HDC             hdc;
BITMAP          bitmap;
HDC             hdcMem;
HGDIOBJ         oldBitmap;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
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
    if (!SettingInstance(hInstance, nCmdShow))
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
            update_position = TRUE;
            if (point != 0 && facing==B_UP && wParam==40)
                update_position = FALSE;
            else if (point != 0 && facing==B_DOWN && wParam==38)
                update_position = FALSE;
            else if (point != 0 && facing==B_LEFT && wParam==39)
                update_position = FALSE;
            else if (point != 0 && facing==B_RIGHT && wParam==37)
                update_position = FALSE;

            if (update_position == TRUE)
            {
                nowKeyNumber = wParam;
                switch(wParam)
                {
                    case VK_UP:
                        wsprintf(szCharKey,"Facing : UP");
                        facing = B_UP;
                    break;
                    case VK_DOWN:
                        wsprintf(szCharKey,"Facing : DOWN");
                        facing = B_DOWN;
                    break;
                    case VK_LEFT:
                        wsprintf(szCharKey,"Facing : LEFT");
                        facing = B_LEFT;
                    break;
                    case VK_RIGHT:
                        wsprintf(szCharKey,"Facing : RIGHT");
                        facing = B_RIGHT;
                    break;
                    case VK_SPACE:
                        turbo = TRUE;
                    break;
                }
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
            check_background(bkgchoice);
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

LRESULT CALLBACK ContentProc (HWND _hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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
                    return DefWindowProc(_hWnd, Msg, wParam, lParam);
            }
        break;

        default:
            return DefWindowProc(_hWnd, Msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK LeaderboardProc (HWND _hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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
                    DestroyWindow(leaderboard_hWnd);
                    LeaderboardInstance(hInst);
                break;
                default:
                    return DefWindowProc(_hWnd, Msg, wParam, lParam);
            }
        break;

        default:
            return DefWindowProc(_hWnd, Msg, wParam, lParam);
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

            //PlaySound("1.wav",NULL,SND_FILENAME | SND_ASYNC);

        	hMyDC=BeginPaint(hwnd, &ps);
            randStar();
            speed();
            starAndSnakeHand(hwnd,hMyDC);
            walked();
        	show_debug(hwnd, hMyDC);
            keyClicked();
            PrintTail(hwnd, hMyDC);
            outLine(hwnd);

            EndPaint(hwnd, &ps);

        break;

        default:
            return DefWindowProc(hwnd, Msg, wParam, lParam);
    }
        return 0;
}

LRESULT CALLBACK SettingProc (HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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
                case APPLY_BUTTON:
                    destroy_setting();
                    GetWindowText(hUser, user, 16);
                    update_welcome(hWnd);
                    puts("Applying Changes");
                break;
                default:
                    return DefWindowProc(hwnd, Msg, wParam, lParam);
            }
            break;

        default:
            return DefWindowProc(hwnd, Msg, wParam, lParam);
    }
    return 0;
}

ATOM RegisterMain(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = 0;
    wcex.lpfnWndProc    = MainProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = MainClass;
    wcex.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

ATOM RegisterContent(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = 0;
    wcex.lpfnWndProc    = ContentProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+6);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = ContentClass;
    wcex.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

ATOM RegisterGame(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = 0;
    wcex.lpfnWndProc    = GameProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
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
    wcex.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

ATOM RegisterSetting(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = 0;
    wcex.lpfnWndProc    = SettingProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
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
    wcex.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

ATOM RegisterLeaderboard(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = 0;
    wcex.lpfnWndProc    = LeaderboardProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);

    LOGBRUSH background;
    background.lbStyle     = BS_PATTERN;
    background.lbHatch     = (long) LoadImage(hInstance,
                            "assets\\background\\lead.bmp",
                            IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    //Set Background
    if(background.lbHatch != 0)
        wcex.hbrBackground = CreateBrushIndirect(&background);
    else
        wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = GameClass;
    wcex.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = LeaderboardClass;
    wcex.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

BOOL LeaderboardInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    center_window(GetDesktopWindow(), 960, 600);
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

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

BOOL ContentInstance(HINSTANCE hInstance, int nCmdShow)
{
    con_hWnd = CreateWindowW   (ContentClass, "Content", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                20, 15, 300, 540,
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
                                335, 15,
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

BOOL SettingInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    center_window(GetDesktopWindow(), 960, 600);
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
    ShowWindow(con_hWnd, SW_HIDE);
    ShowWindow(game_hWnd, SW_HIDE);
    Pressed = TRUE;
}

void destroy_setting()
{
        ShowWindow(setting_hWnd, SW_HIDE);
        Pressed = TRUE;
}

void content()
{
    hBack = CreateWindowW(L"Button", L"Back", WS_VISIBLE | WS_CHILD, 50, 500, 200, 30, con_hWnd, (HMENU)BACK_BUTTON, NULL, NULL);
}

void setting()
{
        CreateWindowW(L"Button", L"Player Name", WS_VISIBLE | WS_CHILD, 240, 20, 100, 30, setting_hWnd, NULL, NULL, NULL);
        hUser = CreateWindowW(L"Edit", L"Default", WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | WS_BORDER, 350, 20, 300, 30, setting_hWnd, NULL, NULL, NULL);
        hBackground1 = CreateWindowW(L"Button", L"1", WS_VISIBLE | WS_CHILD | BS_BITMAP, 75, 70, 192, 120, setting_hWnd, (HMENU)BKG1_BUTTON, NULL, NULL);
        hBackground2 = CreateWindowW(L"Button", L"2", WS_VISIBLE | WS_CHILD | BS_BITMAP, 277, 70, 192, 120, setting_hWnd, (HMENU)BKG2_BUTTON, NULL, NULL);
        hBackground3 = CreateWindowW(L"Button", L"3", WS_VISIBLE | WS_CHILD | BS_BITMAP, 479, 70, 192, 120, setting_hWnd, (HMENU)BKG3_BUTTON, NULL, NULL);
        hBackground4 = CreateWindowW(L"Button", L"4", WS_VISIBLE | WS_CHILD | BS_BITMAP, 681, 70, 192, 120, setting_hWnd, (HMENU)BKG4_BUTTON, NULL, NULL);
        hApply = CreateWindowW(L"Button", L"Apply", WS_VISIBLE | WS_CHILD , 230, 510, 500, 40, setting_hWnd, (HMENU)APPLY_BUTTON, NULL, NULL);
        update_setting();
}

void leaderboard()
{
    //Sort Data Structure
    sorting();
    hReset = CreateWindowW(L"Button", L"Reset", WS_VISIBLE | WS_CHILD , 839, 11, 94, 88, leaderboard_hWnd, (HMENU)RESET_BUTTON, NULL, NULL);
    hBackLead = CreateWindowW(L"Button", L"Back", WS_VISIBLE | WS_CHILD , 15, 11, 94, 88, leaderboard_hWnd, (HMENU)BACK_BUTTON, NULL, NULL);
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
