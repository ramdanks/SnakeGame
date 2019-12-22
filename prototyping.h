#include <windows.h>
#include <Winuser.h>
#include <stdlib.h>
#include <time.h>

#pragma comment( lib, "Gdi32.lib" )

#define RADIUS 28
#define MOVE_DISTANCE 6
#define SNAKE_SIZE 30
#define STAR_SIZE 30
#define SNAKE_DISTANCE 30
#define IDI_ICON 101
//  OLD

#define EQU ==
#define RIGHT 575
#define LEFT 10
#define UP 10
#define DOWN 515
#define WALKED 15000
#define TAIL_NUM 50
#define SPEED_DEFAULT 32

#define TRUE 1
#define FALSE 0

#define B_UP 1
#define B_DOWN 2
#define B_LEFT 3
#define B_RIGHT 4

#define PLAY_BUTTON 1
#define LEADERBOARD_BUTTON 2
#define SHOPS_BUTTON 3
#define ABOUT_BUTTON 4
#define EXIT_BUTTON 5
#define BACK_BUTTON 6
#define SETTINGS_BUTTON 7
#define BKG1_BUTTON 8
#define BKG2_BUTTON 9
#define BKG3_BUTTON 10
#define BKG4_BUTTON 11
#define APPLY_BUTTON 12
#define RESET_BUTTON 13
#define ON_BUTTON 14
#define OFF_BUTTON 15
#define ONS_BUTTON 16
#define OFFS_BUTTON 17
#define SOUND 1
#define DEBUG 0

const char *MainClass="Snake";
const char *ContentClass="Content";
const char *GameClass="Game";
const char *SettingClass="Setting";
const char *LeaderboardClass="Leaderboard";
const char *AboutClass="About";

const char bkg1[]="assets\\background\\1.bmp";
const char bkg2[]="assets\\background\\2.bmp";
const char bkg3[]="assets\\background\\3.bmp";
const char bkg4[]="assets\\background\\4.bmp";

const char bkg1_battle[]="assets\\background\\battle1.bmp";
const char bkg2_battle[]="assets\\background\\battle2.bmp";
const char bkg3_battle[]="assets\\background\\battle3.bmp";
const char bkg4_battle[]="assets\\background\\battle4.bmp";

const char *ontoggle_true=L"assets/settings/on.bmp";
const char *ontoggle_false=L"assets/settings/on_dark.bmp";
const char *offtoggle_true=L"assets/settings/off.bmp";
const char *offtoggle_false=L"assets/settings/off_dark.bmp";

ATOM RegisterMain(HINSTANCE hInstance);
ATOM RegisterMenu(HINSTANCE hInstance);
ATOM RegisterContent(HINSTANCE hInstance);
ATOM RegisterGame(HINSTANCE hInstance);
ATOM RegisterSetting(HINSTANCE hInstance);
ATOM RegisterLeaderboard(HINSTANCE hInstance);
ATOM RegisterAbout(hInstance);

BOOL AboutInstance(HINSTANCE hInstance);
BOOL LeaderboardInstance(HINSTANCE hInstance);
BOOL MainInstance(HINSTANCE hInstance, int nCmdShow);
BOOL ContentInstance(HINSTANCE hInstance, int nCmdShow);
BOOL GameInstance(HINSTANCE hInstance, int nCmdShow);
BOOL SettingInstance(HINSTANCE hInstance);


LRESULT CALLBACK WndProc (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ContentProc (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LeaderboardProc (HWND leaderboard_hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AboutProc (HWND about_hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

void menu(HWND hWnd);
void Play();
int center_window(HWND parent_window, int width, int height);
void destroy();
void destroy_game();
void content();
void update_welcome(HWND hWnd);
void leaderboard();
void about();

int nTopXY(UINT wnd_XY, UINT wnd_Dim);

int cpuTime = SPEED_DEFAULT;

//Generating Snake Position
#define xRespawn 282
#define yRespawn 222
int nowX = xRespawn;
int nowY = yRespawn;

int moveX = 0;
int moveY = 0;
int spd;

int starX;
int starY;

int nowKeyNumber = 0;
int beforeKeyNumber = 0;

int nowXYPlace = 0;
int tailNumber = 0;

int walkedNumber = 0;

int aspectX[4] = { 0 ,0  ,SNAKE_DISTANCE,-SNAKE_DISTANCE };
int aspectY[4] = { SNAKE_DISTANCE,-SNAKE_DISTANCE,0 ,0   };


int point = 0;
int currentAspect = 0;
int walkX[WALKED] = {0};
int walkY[WALKED] = {0};

int	nTick = 0;

int nTickX = 1;
int nTickY = 1;

BOOL bFlag =0;
char szText[5] = "";
char szTextKey[10] ="";
char szTick[100] ;
char szCharKey[10];
char szOut[10] = "Out";
char szPoint[100];
char szMenu[30] = "";

int wnd_W = 595;
int wnd_H = 535;
int bkgchoice = 1;
int uicolor = 1;
char *background, *background_battle, *background_about;
const char *locate_bg1, *locate_bg2, *locate_bg3, *locate_bg4;
const char *menu_sprites;
int Pressed = FALSE;
char user[16]="Default";
WCHAR welcome_char[24];
char szWelcome[24];
int update_position = TRUE;
int regKey;

struct setting
{
    BOOL check;
    BOOL type;
};
struct setting isSound = {TRUE, SOUND};
struct setting isDebug = {TRUE, DEBUG};
//Window
HWND hWnd, game_hWnd, setting_hWnd;
//Menu
HWND hPlay, hLeaderboard, hShops, hAbout, hExit, hBitmap, hSettings, hWelcome;
//Content
HWND con_hWnd, hBack;
//Game
HBITMAP hBitmap_battle;
//Settings
HWND hBackground1, hBackground2, hBackground3, hBackground4, hApply, hUser, hOn, hOff, hOnS, hOffS;
//Leaderboard
HWND leaderboard_hWnd, hBackLead, hReset;
//About
HWND about_hWnd, hReturn, hRamdan, hDiaz;

int turbo = FALSE;

void updateStructure()
{
    //Get Username
    GetWindowText(hUser, user, 16);
    //Masukkan ke Data Structure
    insert(user, point);
}

void update()
{
    if(Pressed == FALSE)
    {
        ShowWindow(hSettings, SW_HIDE);
        ShowWindow(hPlay, SW_HIDE);
        ShowWindow(hLeaderboard, SW_HIDE);
        ShowWindow(hShops, SW_HIDE);
        ShowWindow(hAbout, SW_HIDE);
        ShowWindow(hExit, SW_HIDE);
        ShowWindow(hWelcome, SW_HIDE);
    }
    else if(Pressed == TRUE)
    {
        ShowWindow(hLeaderboard, SW_SHOW);
        ShowWindow(hSettings, SW_SHOW);
        ShowWindow(hPlay, SW_SHOW);
        ShowWindow(hShops, SW_SHOW);
        ShowWindow(hAbout, SW_SHOW);
        ShowWindow(hExit, SW_SHOW);
        ShowWindow(hWelcome, SW_SHOW);
    }
    Pressed = FALSE;
}

void check_background()
{
    if (bkgchoice == 1)
    {
        background = bkg1;
        background_battle = bkg1_battle;
        background_about = "assets\\background\\1bg.bmp";
    }

    else if (bkgchoice == 2)
    {
        background = bkg2;
        background_battle = bkg2_battle;
        background_about = "assets\\background\\2bg.bmp";
    }
    else if (bkgchoice == 3)
    {
        background = bkg3;
        background_battle = bkg3_battle;
        background_about = "assets\\background\\3bg.bmp";
    }
    else if (bkgchoice == 4)
    {
        background = bkg4;
        background_battle = bkg4_battle;
        background_about = "assets\\background\\4bg.bmp";
    }
}

void update_setting()
{
    locate_background();

    HWND hBg1I = (HBITMAP)LoadImageW(NULL, locate_bg1, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HWND hBg2I = (HBITMAP)LoadImageW(NULL, locate_bg2, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HWND hBg3I = (HBITMAP)LoadImageW(NULL, locate_bg3, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HWND hBg4I = (HBITMAP)LoadImageW(NULL, locate_bg4, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    SendMessageW(hBackground1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBg1I);
    SendMessageW(hBackground2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBg2I);
    SendMessageW(hBackground3, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBg3I);
    SendMessageW(hBackground4, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBg4I);
}

void update_menu()
{
    //locate_menu();
    HWND hMenu;
    hMenu = (HBITMAP)LoadImageW(NULL, L"assets\\button\\play.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessageW(hPlay, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hMenu);
    hMenu = (HBITMAP)LoadImageW(NULL, L"assets\\button\\lead.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessageW(hLeaderboard, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hMenu);
    hMenu = (HBITMAP)LoadImageW(NULL, L"assets\\button\\exit.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessageW(hExit, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hMenu);
    hMenu = (HBITMAP)LoadImageW(NULL, L"assets\\button\\green.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessageW(hShops, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hMenu);
    hMenu = (HBITMAP)LoadImageW(NULL, L"assets\\button\\about.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessageW(hAbout, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hMenu);

}

void locate_menu()
{
    if (uicolor == 1)
    {
        menu_sprites = L"assets\\button\\green.bmp";
    }
    else if (uicolor == 2)
    {
        menu_sprites = L"assets\\button\\orange.bmp";
    }
    else if (uicolor ==3)
    {
        menu_sprites = L"assets\\button\\red.bmp";
    }
}

void locate_background()
{
    if (bkgchoice == 1)
    {
        locate_bg1 = L"assets\\settings\\check_1.bmp";
        locate_bg2 = L"assets\\settings\\map_2.bmp";
        locate_bg3 = L"assets\\settings\\map_3.bmp";
        locate_bg4 = L"assets\\settings\\map_4.bmp";
    }
    else if (bkgchoice == 2)
    {
        locate_bg1 = L"assets\\settings\\map_1.bmp";
        locate_bg2 = L"assets\\settings\\check_2.bmp";
        locate_bg3 = L"assets\\settings\\map_3.bmp";
        locate_bg4 = L"assets\\settings\\map_4.bmp";
    }
    else if (bkgchoice == 3)
    {
        locate_bg1 = L"assets\\settings\\map_1.bmp";
        locate_bg2 = L"assets\\settings\\map_2.bmp";
        locate_bg3 = L"assets\\settings\\check_3.bmp";
        locate_bg4 = L"assets\\settings\\map_4.bmp";
    }
    else if (bkgchoice == 4)
    {
        locate_bg1 = L"assets\\settings\\map_1.bmp";
        locate_bg2 = L"assets\\settings\\map_2.bmp";
        locate_bg3 = L"assets\\settings\\map_3.bmp";
        locate_bg4 = L"assets\\settings\\check_4.bmp";
    }
}

void randStar()
{
    if(starX == 0 && starY == 0)
    {
        srand(time(NULL));
        while (1)
        {
            starX = 12 + rand()%19 * STAR_SIZE;
            starY = 12 + rand()%17 * STAR_SIZE;
            if (starX != nowX && starY != nowY)
                break;
        }

    }
    else if( ((nowX-starX) <= RADIUS && (nowX-starX) >= -RADIUS) &&
             ((nowY-starY) <= RADIUS && (nowY-starY) >= -RADIUS)    )
    {
        if (isSound.check == TRUE)
            PlaySound("assets/sounds/coinfast.wav",NULL,SND_FILENAME | SND_ASYNC);
        srand(time(NULL));
        while (1)
        {
            starX = 12 + rand()%19 * STAR_SIZE;
            starY = 12 + rand()%17 * STAR_SIZE;
            if (starX != nowX && starY != nowY)
                break;
        }
        point += 10;
    }
}

void starAndSnakeHand(HWND hwnd,HDC hMyDC)
{
    HBRUSH hBrush;
    hBrush = CreateSolidBrush(RGB(255,255,48));
        	SelectObject(hMyDC,hBrush);
        	Rectangle(hMyDC,starX,starY,starX+STAR_SIZE,starY+STAR_SIZE);

            //Draw Head
        	hBrush = CreateSolidBrush(RGB(0,255,0));
        	SelectObject(hMyDC,hBrush);
        	Rectangle(hMyDC,nowX,nowY,nowX+SNAKE_SIZE,nowY+SNAKE_SIZE);
        	//DeleteObject(hBrush);
}

void keyClicked()
{
    update_position = TRUE;
    if (point != 0 && currentAspect==B_UP && nowKeyNumber==40)
        update_position = FALSE;
    else if (point != 0 && currentAspect==B_DOWN && nowKeyNumber==38)
        update_position = FALSE;
    else if (point != 0 && currentAspect==B_LEFT && nowKeyNumber==39)
        update_position = FALSE;
    else if (point != 0 && currentAspect==B_RIGHT && nowKeyNumber==37)
        update_position = FALSE;

    if (update_position == TRUE)
    {
        if(nowKeyNumber == 38)
        {
            nowY = nowY - MOVE_DISTANCE ;
            moveX = 0;
            moveY = -MOVE_DISTANCE;
            currentAspect = B_UP;
        }
        else if(nowKeyNumber == 40)
        {
            nowY = nowY + MOVE_DISTANCE ;
            moveX = 0;
            moveY = MOVE_DISTANCE;
            currentAspect = B_DOWN;
        }
        else if(nowKeyNumber == 37)
        {
            nowX = nowX - MOVE_DISTANCE ;
            moveX = -MOVE_DISTANCE;
            moveY = 0;
            currentAspect = B_LEFT;
        }
        else if(nowKeyNumber == 39)
        {
            nowX = nowX + MOVE_DISTANCE ;
            moveX = MOVE_DISTANCE;
            moveY = 0;
            currentAspect = B_RIGHT;
        }
        else
        {
            nowX = nowX + moveX;
            nowY = nowY + moveY;
        }
    }
    nowKeyNumber = NULL;
    if (regKey != NULL)
    {
        nowKeyNumber = regKey;
        regKey = NULL;
    }
}

void walked()
{
    nowXYPlace = (walkedNumber+WALKED-1) % WALKED;
   	tailNumber = point / 10 ;

    walkedNumber ++;
    int i = nowXYPlace;

    walkX[i] = nowX;
    walkY[i] = nowY;
}

void PrintTail(HWND hwnd,HDC hMyDC )
{
    int distance = 1;
    int handDistance = 3;
    int offset=-1;
    int id = 0;

    while( tailNumber > 0)
        {
        if(nowXYPlace > 10  ){

            Rectangle   (hMyDC,
                        walkX[nowXYPlace-4*distance+offset],
                        walkY[nowXYPlace-4*distance+offset],
                        walkX[nowXYPlace-4*distance+offset]+SNAKE_SIZE,
                        walkY[nowXYPlace-4*distance+offset]+SNAKE_SIZE );


            if  (nowX == walkX[nowXYPlace-4*distance+offset] &&
                nowY == walkY[nowXYPlace-4*distance+offset]    ||
                nowX == walkX[nowXYPlace-4*distance-1] &&
                nowY == walkY[nowXYPlace-4*distance-1])
            {
                KillTimer(hWnd,1);
                char gameOverStr[100];
                wsprintf(gameOverStr,"You Hit Yourself!\nScore:%d\nTry Again?", point);
   	            id = MessageBox(hwnd,gameOverStr,"Game Over", MB_YESNO | MB_ICONINFORMATION);
                if(id == IDNO)
                {
                    updateStructure();
                    reStart();
                    destroy_game();
                }
                else
                {
                    updateStructure();
                    puts("Restarted");
                    reStart();
                    SetTimer(hWnd,1,cpuTime,NULL);
                    PlaySound("assets/sounds/start.wav",NULL,SND_FILENAME | SND_ASYNC );
                    InvalidateRect(game_hWnd, NULL, TRUE);
                }
            }
            tailNumber--;
       	    nowXYPlace--;
       	    distance++;
        }
    }
}

void reStart()
{
    turbo = FALSE;
    nTick = 0;
    nTickX = 1;
    nTickY = 1;

    bFlag =0;

    strcpy(szText,"");
    strcpy(szTextKey,"");
    strcpy(szTick,"");
    strcpy(szCharKey,"");
    strcpy(szOut,"");
    strcpy(szPoint,"");

    nowX = xRespawn;
    nowY = yRespawn;

    moveX = 0;
    moveY = 0;

    starX = 0;
    starY = 0;

    nowKeyNumber = 0;
    beforeKeyNumber = 0;

    nowXYPlace = 0;
    tailNumber = 0;

    walkedNumber = 0;

    point = 0;
    currentAspect = 0;

    for(int i = 0 ; i < WALKED ; i++)
    {
        walkX[i] = 0;
        walkY[i] = 0;
    }
}

void outLine(HWND hwnd)
{
    if( nowX > RIGHT || nowX < LEFT || nowY > DOWN || nowY < UP)
    {
        KillTimer(hWnd,1);
        char gameOverStr[100];
        wsprintf(gameOverStr,"You Hit The Wall!\nScore:%d\nTry Again? ", point);
        int id = MessageBox(hwnd,gameOverStr,"Game Over", MB_YESNO | MB_ICONINFORMATION);
        if(id == IDNO)
        {
            updateStructure();
            reStart();
            destroy_game();
        }
        else
        {
            updateStructure();
            puts("Restarted");
            reStart();
            SetTimer(hWnd,1,cpuTime,NULL);
            PlaySound("assets/sounds/start.wav",NULL,SND_FILENAME | SND_ASYNC );
            InvalidateRect(game_hWnd, NULL, TRUE);
        }
    }
}

void show_debug(HWND hwnd,HDC hMyDC)
{
    SetTextColor(hMyDC,RGB(110,95,230));
    wsprintf(szPoint,"Point : %d",point);
    TextOut(hMyDC,230,500,szPoint,strlen(szPoint));

    char debug[20];
    SetTextColor(hMyDC,RGB(0,0,0));
    wsprintf(debug, "Position ( %d , %d )",nowX,nowY);
    TextOut(hMyDC,78,500,debug,lstrlen(debug));

    free(debug);

    SetTextColor(hMyDC,RGB(0,0,0));
    wsprintf(debug, "Speed : %d",spd);
    TextOut(hMyDC, 320,500,debug,lstrlen(debug));

    if (currentAspect == B_UP)
        wsprintf(szCharKey,"Facing : UP");
    if (currentAspect == B_DOWN)
        wsprintf(szCharKey,"Facing : DOWN");
    if (currentAspect == B_LEFT)
        wsprintf(szCharKey,"Facing : LEFT");
    if (currentAspect == B_RIGHT)
        wsprintf(szCharKey,"Facing : RIGHT");
    TextOut(hMyDC, 420,500,szCharKey,lstrlen(szCharKey));

    //SetTextColor(hMyDC,RGB(111,0,115));
    //TextOut(hMyDC,260,245,szTextKey,lstrlen(szTextKey));
}

void update_toggle(BOOL type)
{
    int data;
    HWND hToggleOn, hToggleOff;

    if (type == SOUND)
        data = isSound.check;
    else if (type == DEBUG)
        data = isDebug.check;

    if (data == TRUE)
    {
        hToggleOn = (HBITMAP)LoadImageW(NULL, ontoggle_true, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hToggleOff = (HBITMAP)LoadImageW(NULL, offtoggle_false, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }
    else if (data == FALSE)
    {
        hToggleOn = (HBITMAP)LoadImageW(NULL, ontoggle_false, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hToggleOff = (HBITMAP)LoadImageW(NULL, offtoggle_true, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }

    if (type == SOUND)
    {
        SendMessageW(hOnS, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hToggleOn);
        SendMessageW(hOffS, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hToggleOff);
    }
    else if (type == DEBUG)
    {
        SendMessageW(hOn, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hToggleOn);
        SendMessageW(hOff, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hToggleOff);
    }
}

void locate_toggle(BOOL data)
{

}
void speed()
{
    if(turbo == TRUE)
        cpuTime = 18;
    else if(point >= 300)
        cpuTime = 28;
    else if(point >= 200)
        cpuTime = 26;
    else if(point >= 100)
        cpuTime = 30;
    else if(point < 100)
        cpuTime = SPEED_DEFAULT;

    SetTimer(hWnd,1,cpuTime,NULL);
}
