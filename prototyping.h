#include <windows.h>
#include <Winuser.h>

#include <stdlib.h>
#include <time.h>

#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )

#define RADIUS 25
#define MOVE_DISTANCE 8
#define SNAKE_SIZE 25
#define STAR_SIZE 25
#define SNAKE_DISTANCE 25

//  OLD

#define EQU ==
#define RIGHT 575
#define LEFT 10
#define UP 10
#define DOWN 515
#define WALKED 15000
#define TAIL_NUM 50
#define SPEED_DEFAULT 36

#define TRUE 1
#define FALSE -1

int facing;
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

const char *MainClass="Snake";
const char *ContentClass="Content";
const char *GameClass="Game";
const char *SettingClass="Setting";
const char *LeaderboardClass="Leaderboard";

const char bkg1[]="assets\\background\\1.bmp";
const char bkg2[]="assets\\background\\2.bmp";
const char bkg3[]="assets\\background\\3.bmp";
const char bkg4[]="assets\\background\\4.bmp";

const char bkg1_battle[]="assets\\background\\battle1.bmp";
const char bkg2_battle[]="assets\\background\\battle2.bmp";
const char bkg3_battle[]="assets\\background\\battle3.bmp";
const char bkg4_battle[]="assets\\background\\battle4.bmp";

ATOM RegisterMain(HINSTANCE hInstance);
ATOM RegisterMenu(HINSTANCE hInstance);
ATOM RegisterContent(HINSTANCE hInstance);
ATOM RegisterGame(HINSTANCE hInstance);
ATOM RegisterSetting(HINSTANCE hInstance);
ATOM RegisterLeaderboard(HINSTANCE hInstance);

LRESULT CALLBACK WndProc (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ContentProc (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

void menu(HWND hWnd);
void Play();
int center_window(HWND parent_window, int width, int height);
void destroy();
void destroy_game();
void content();
void update_welcome(HWND hWnd);
void leaderboard();

int nTopXY(UINT wnd_XY, UINT wnd_Dim);

int cpuTime = SPEED_DEFAULT;

int nowX = 260;
int nowY = 200;

int moveX = 0;
int moveY = 0;

int starX = 0;
int starY = 0;

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

int wnd_W = 600;
int wnd_H = 540;
int bkgchoice = 1;
int uicolor = 1;
char *background, *background_battle;
const char *locate_bg1, *locate_bg2, *locate_bg3, *locate_bg4;
const char *menu_sprites;
int Pressed = FALSE;
char user[16]="Default";
WCHAR welcome_char[24];
char szWelcome[24];
int update_position = TRUE;


//Window
HWND hWnd, con_hWnd, game_hWnd, setting_hWnd, leaderboard_hWnd;
//Menu
HWND hPlay, hLeaderboard, hShops, hAbout, hExit, hBitmap, hSettings, hWelcome;
//Content
HWND hBack;
//Game
HBITMAP hBitmap_battle;
//Settings
HWND hBackground1, hBackground2, hBackground3, hBackground4, hApply, hUser;
//Leaderboard
HWND hBackLead, hReset;

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
    }

    else if (bkgchoice == 2)
    {
        background = bkg2;
        background_battle = bkg2_battle;
    }
    else if (bkgchoice == 3)
    {
        background = bkg3;
        background_battle = bkg3_battle;
    }
    else if (bkgchoice == 4)
    {
        background = bkg4;
        background_battle = bkg4_battle;
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
        starX = rand()%540 + 20;
        starY = rand()%480 + 20;
    }
    else if( ((nowX-starX) <= RADIUS && (nowX-starX) >= -RADIUS) &&
             ((nowY-starY) <= RADIUS && (nowY-starY) >= -RADIUS)    )
    {
       srand(time(NULL));
       starX = rand()%400+rand()%160 + 15 ;
       starY = rand()%400+rand()%55 + 20;
       point += 10;
    }
}

void starAndSnakeHand(HWND hwnd,HDC hMyDC)
{
    HBRUSH hBrush;
    hBrush = CreateSolidBrush(RGB(255,255,48));
        	SelectObject(hMyDC,hBrush);
        	Rectangle(hMyDC,starX,starY,starX+STAR_SIZE,starY+STAR_SIZE);

        	hBrush = CreateSolidBrush(RGB(0,255,0));
        	SelectObject(hMyDC,hBrush);
        	Rectangle(hMyDC,nowX,nowY,nowX+SNAKE_SIZE+3,nowY+SNAKE_SIZE+3);
        	//DeleteObject(hBrush);
}

void keyClicked()
{
    if(nowKeyNumber == 38){
        nowY = nowY - MOVE_DISTANCE ;
        moveX = 0;
        moveY = -MOVE_DISTANCE;
        currentAspect = 0;
    }
    else if(nowKeyNumber == 40){
        nowY = nowY + MOVE_DISTANCE ;
        moveX = 0;
        moveY = MOVE_DISTANCE;
        currentAspect = 1;
    }
    else if(nowKeyNumber == 37){
        nowX = nowX - MOVE_DISTANCE ;
        moveX = -MOVE_DISTANCE;
        moveY = 0;
        currentAspect = 2;
    }
    else if(nowKeyNumber == 39){
        nowX = nowX + MOVE_DISTANCE ;
        moveX = MOVE_DISTANCE;
        moveY = 0;
        currentAspect = 3;
    }
    else{
        nowX = nowX + moveX;
        nowY = nowY + moveY;
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
    int first = 0;
    int id = 0;

    while( tailNumber > 0)
        {
        if(nowXYPlace > 10  ){
            if(distance == 1)
                first = -2;
            else
                first = 0;

            Rectangle   (hMyDC,
                        walkX[nowXYPlace-2*distance+first],
                        walkY[nowXYPlace-2*distance+first],
                        walkX[nowXYPlace-2*distance+first]+SNAKE_SIZE,
                        walkY[nowXYPlace-2*distance+first]+SNAKE_SIZE );


            if  (nowX == walkX[nowXYPlace-2*distance+first] &&
                nowY == walkY[nowXYPlace-2*distance+first]    ||
                nowX == walkX[nowXYPlace-2*distance-1] &&
                nowY == walkY[nowXYPlace-2*distance-1])
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

    nowX = 160;
    nowY = 100;

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

    for(int i = 0 ; i < WALKED ; i++){
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
            InvalidateRect(game_hWnd, NULL, TRUE);
        }
    }
}

void show_debug(HWND hwnd,HDC hMyDC)
{
    int	nLen = sizeof(szText)-1;

    SetTextColor(hMyDC,RGB(110,95,230));
    wsprintf(szPoint,"Point : %d",point);
    TextOut(hMyDC,230,500,szPoint,strlen(szPoint));

    char debug[20];
    SetTextColor(hMyDC,RGB(0,0,0));
    wsprintf(debug, "Position ( %d , %d )",nowX,nowY);
    TextOut(hMyDC,80,500,debug,lstrlen(debug));

    free(debug);
    SetTextColor(hMyDC,RGB(0,0,0));
    wsprintf(debug, "Speed : %d",cpuTime);
    TextOut(hMyDC, 320,500,debug,lstrlen(debug));

    TextOut(hMyDC, 420,500,szCharKey,lstrlen(szCharKey));
    //SetTextColor(hMyDC,RGB(111,0,115));
    //TextOut(hMyDC,260,245,szTextKey,lstrlen(szTextKey));
}

void speed()
{
    if(turbo == TRUE)
        cpuTime = 20;
    else if(point >= 300)
        cpuTime = 30;
    else if(point >= 200)
        cpuTime = 32;
    else if(point >= 100)
        cpuTime = 34;
    else if(point < 100)
        cpuTime = SPEED_DEFAULT;

    SetTimer(hWnd,1,cpuTime,NULL);
}
