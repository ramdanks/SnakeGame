#include <curses.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

int main ()
{
    //Menjalankan Ncurses
    initscr();
    cbreak();

    WINDOW *in;
    in = newwin(1, 1, 0, -1);
    refresh();

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(7, COLOR_WHITE, COLOR_RED);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);

    char* choices[] = {"Accept and Continue", "Exit"};
    // Length of Array, bukan Size of Array
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight = 0;

    //Mengambil informasi ukuran layar komputer
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //Watermark
    char mesg[] = {"Password Manager 1.0 Alpha Release"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    //Window Konten
    WINDOW * content_win = newwin(yMax-8, xMax-10, 3, 5);
    box(content_win, 0, 0);
    refresh();


    //Disclaimer
    int clock;
    char* disc[] = {"[Disclaimer]", "Program ini tidak ditujukan untuk disebarluaskan.", "Melainkan sebagai proyek untuk tugas di mata kuliah Pemrograman Lanjutan.",
                    "Program ini akan terus mendapatkan pembaruan sampai 13 Oktober 2019.", "Program yang kami buat masih banyak terdapat kekurangan.", "Mohon untuk tidak menginput data asli anda ataupun orang lain.",
                    "Kami tidak bertanggung-jawab atas bocornya data yang anda input ke dalam", "program kami. Mohon gunakan dengan bijak, Terimakasih."};

    int s = sizeof(disc) / sizeof(disc[0]);
    for (clock=0; clock < s; clock++)
    {
        mvwprintw(content_win, (yMax/2)-s+clock,(xMax-strlen(disc[clock])-11)/2,"%s", disc[clock]);
    }
    wrefresh(content_win);

    //Buat window khusus untuk input
    WINDOW * menuwin = newwin(3, xMax/2-5, yMax-4, 5);
    mvwprintw(menuwin, 1, 18, choices[0]);
    refresh();
    wrefresh(menuwin);

    WINDOW * menuwin1 = newwin(3, xMax/2-5, yMax-4, 60);
    mvwprintw(menuwin1, 1, 25, choices[1]);
    refresh();
    wrefresh(menuwin);

    //Fungsi untuk mengambil input arrow key
    keypad(in, true);

    while(1)
    {
            if(highlight==0)
            {
                wbkgd(menuwin1, COLOR_PAIR(2));
                wbkgd(menuwin, COLOR_PAIR(7));
            }
            else if(highlight==1)
            {
                wbkgd(menuwin, COLOR_PAIR(2));
                wbkgd(menuwin1, COLOR_PAIR(7));
            }

            wrefresh(menuwin);
            wrefresh(menuwin1);

                choice = wgetch(in);

        switch(choice)
        {
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == n);
                    highlight = n-1;
                break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;
    }
    if(highlight == 0)
        {
            erase();
            menu_utama(xMax, yMax);
        }

    //Ncurses Selesai
    else if(highlight == 1)
    exit(0);

    return 0;
}

int menu_utama(int xMax, int yMax)
{
    WINDOW * menuwin;
    WINDOW * menuwin1;
    WINDOW * menuwin2;
    WINDOW * menuwin3;
    WINDOW * menuwin4;
    WINDOW * win;
    WINDOW *in;
    in = newwin(1, 1, 0, -1);
    refresh();

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(3));

    //Watermark
    char mesg[] = {"Password Manager 1.0 Alpha Release"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    //Buat window khusus untuk Konten
    win = newwin(30, xMax, 4, 10);
    refresh();

    wrefresh(win);

    char* choices[] = {"Encrypt", "Decrypt", "Manage", "About", "Exit"};
    // Length of Array, bukan Size of Array
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight=0;

    //Buat window khusus untuk input
    menuwin = newwin(7, 22, yMax-8, 5);
    mvwprintw(menuwin, 3, 7, choices[0]);
    refresh();

    menuwin1 = newwin(7, 22, yMax-8, 27);
    mvwprintw(menuwin1, 3, 7, choices[1]);
    refresh();

    menuwin2 = newwin(7, 22, yMax-8, 49);
    mvwprintw(menuwin2, 3, 8, choices[2]);
    refresh();

    menuwin3 = newwin(7, 22, yMax-8, 71);
    mvwprintw(menuwin3, 3, 8, choices[3]);
    refresh();

    menuwin4 = newwin(7, 22, yMax-8, 93);
    mvwprintw(menuwin4, 3, 9, choices[4]);
    refresh();

    //Fungsi untuk mengambil input arrow key
    keypad(in, true);

while(1)
    {
            if(highlight==0)
            {
                wbkgd(menuwin4, COLOR_PAIR(2));
                wbkgd(menuwin3, COLOR_PAIR(2));
                wbkgd(menuwin2, COLOR_PAIR(2));
                wbkgd(menuwin1, COLOR_PAIR(2));
                wbkgd(menuwin, COLOR_PAIR(1));
            }
            else if(highlight==1)
            {
                wbkgd(menuwin, COLOR_PAIR(2));
                wbkgd(menuwin4, COLOR_PAIR(2));
                wbkgd(menuwin3, COLOR_PAIR(2));
                wbkgd(menuwin2, COLOR_PAIR(2));
                wbkgd(menuwin1, COLOR_PAIR(1));
            }
            else if(highlight==2)
            {
                wbkgd(menuwin1, COLOR_PAIR(2));
                wbkgd(menuwin, COLOR_PAIR(2));
                wbkgd(menuwin4, COLOR_PAIR(2));
                wbkgd(menuwin3, COLOR_PAIR(2));
                wbkgd(menuwin2, COLOR_PAIR(1));
            }
            else if(highlight==3)
            {
                wbkgd(menuwin2, COLOR_PAIR(2));
                wbkgd(menuwin1, COLOR_PAIR(2));
                wbkgd(menuwin, COLOR_PAIR(2));
                wbkgd(menuwin4, COLOR_PAIR(2));
                wbkgd(menuwin3, COLOR_PAIR(1));
            }
            else if(highlight==4)
            {
                wbkgd(menuwin3, COLOR_PAIR(2));
                wbkgd(menuwin2, COLOR_PAIR(2));
                wbkgd(menuwin1, COLOR_PAIR(2));
                wbkgd(menuwin, COLOR_PAIR(2));
                wbkgd(menuwin4, COLOR_PAIR(1));
            }

        wrefresh(menuwin);
        wrefresh(menuwin1);
        wrefresh(menuwin2);
        wrefresh(menuwin3);
        wrefresh(menuwin4);


        choice = wgetch(in);

        switch(choice)
        {
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == n)
                    highlight = n-1;
                break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;
    }

    if(highlight == 3)
    {
        erase();
        bkgd(COLOR_PAIR(9));
        about(xMax, yMax);
    }

    else if(highlight == 2)
      {
        erase();
        bkgd(COLOR_PAIR(9));
        manager(xMax, yMax);
      }

    else if(highlight == 1)
    {
        erase();
        bkgd(COLOR_PAIR(9));
        de_menu(xMax, yMax);
    }


    else if(highlight == 0)
    {
        erase();
        bkgd(COLOR_PAIR(9));
        encrypt(xMax, yMax);
    }

    //Ncurses Selesai
    else if(highlight == n-1)
    exit(0);
}

int about (int xMax, int yMax)
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(4));

    WINDOW *judul;
    WINDOW *in;
    in = newwin(1, 1, 0, -1);
    refresh();

    //Watermark
    char mesg[] = {"Password Manager 1.0 Alpha Release"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    //Window Konten
    WINDOW * content_win = newwin(yMax-15, xMax-10, 8, 5);
    refresh();
    wrefresh(content_win);

    char* string[] = {"Password manager adalah program yang digunakan", "user untuk menyimpan dan mengelola password", "akun online, pin kartu kredit, nomor identitas, dan",
     "fitur keamanan lainnya. Password tersimpan dalam", "format terenkripsi yang bertujuan untuk", "memberikan security terhadap semua informasi",
     "password yang tersimpan. Program ini akan", "mendekripsi password saat user ingin menggunakan","atau melihat password, hingga memberikan akses","yang aman dan mudah bagi user", "Pengarang :", "Diaz Ilyasa Azrurrafi Saiful (1806200154)", "Ramadhan Kalih Sewu (1806148826)"};

    int s = sizeof(string) / sizeof(string[0]);
    int clock=0;

    for (clock=0; clock < s; clock++)
    {
        mvwprintw(content_win, 1+clock, (xMax-strlen(string[clock])-11)/2,"%s", string[clock]);
    }
    wrefresh(content_win);

    char* choices[] = {"Back", "Exit"};
    // Length of Array, bukan Size of Array
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight = 0;

    //Buat window khusus untuk input
    WINDOW * win = newwin(5, xMax/2-5, yMax-6, 5);
    mvwprintw(win, 2, xMax/4-6, choices[0]);
    refresh();
    wrefresh(win);

    WINDOW * win1 = newwin(5, xMax/2-5, yMax-6, 60);
    mvwprintw(win1, 2, xMax/4-6, choices[1]);
    refresh();
    wrefresh(win1);

    //Window Judul
    judul = newwin(3, xMax-10, 4, 5);
    mvwprintw(judul, 1, 52, "ABOUT");
    wbkgd(judul, COLOR_PAIR(5));
    refresh();
    wrefresh(judul);

    //Fungsi untuk mengambil input arrow key
    keypad(in, true);

    while(1)
    {
            if(highlight==0)
            {
                wbkgd(win1, COLOR_PAIR(2));
                wbkgd(win, COLOR_PAIR(1));
            }
            else if(highlight==1)
            {
                wbkgd(win, COLOR_PAIR(2));
                wbkgd(win1, COLOR_PAIR(1));
            }

            wrefresh(win);
            wrefresh(win1);

        choice = wgetch(in);

        switch(choice)
        {
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == n);
                    highlight = n-1;
                break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;
    }
    if(highlight == 0)
    {
        erase();
        menu_utama(xMax, yMax);
    }

    //Ncurses Selesai
    else if(highlight == n-1)
    exit(0);
}

int encrypt(int xMax, int yMax, int loop)
{
    int i, x;
    char str[64], filename[64], type[16]={"Encryption"};
    WINDOW * win;
    WINDOW * content_win;
    WINDOW * ghost_win;
    mvprintw(7, 6, "Encryption, Inf Box :");

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(4));

    //Watermark
    char mesg[] = {"Password Manager 1.0 Alpha Release"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    char *dirname;

    if (loop != 1)
    {
        //Buat folder khusus
        dirname = malloc(25*sizeof(char));
        char *dirname = "savepass";
        mkdir(dirname);
    }

    //Window Konten
    content_win = newwin(yMax-13, xMax-10, 8, 5);
    wbkgd(content_win, COLOR_PAIR(9));
    refresh();
    wrefresh(content_win);

    //Buat window baru khusus untuk input
    win = newwin(3, xMax-10, yMax-5, 5);
    wbkgd(win, COLOR_PAIR(2));
    refresh();

    char string[]={"Please enter a string: "};
    mvwprintw(win, 1,1,"%s", string);
    wrefresh(win);
    wgetstr(win, str);

    int sz = sizeof(str) / sizeof(str[0]);

    mvwprintw(win, 1, 1, "                       ");
    mvwprintw(content_win, 1, 1, "Input string: %s", str);

      for(i = 0; (i < sz && str[i] != '\0'); i++)
      {
        if (i<2)
            str[i] = str[i] + 3;
        else if (i<4)
            str[i] = str[i] + 5;
        else if (i<6)
            str[i] = str[i] + 11;
        else if (i<8)
            str[i] = str[i] - 7;
        else if (i<10)
            str[i] = str[i] - 10;
        else if (i>=10)
            str[i] = str[i] + 1 + i;
      }

    mvwprintw(content_win, 3, 1, "Encryption Successful");
    mvwprintw(content_win, 5, 1, "Encrypted string: %s", str);
    wrefresh(content_win);

    //manggil Save WIndow
    int save = ask_save(xMax, yMax, type);

    ghost_win = newwin(5, xMax/2.5, 3, xMax/3.3);
    wbkgd(ghost_win, COLOR_PAIR(4));
    refresh();
    wrefresh(ghost_win);

    //Save
    if (save == 1)
    {

        wclear(win);
        //Ambil nama File
        mvwprintw(win, 1, 1, "Save with Filename: ");
        wrefresh(win);
        wgetstr(win, filename);

        //Specify path
        char filepath[64];
        char cwd[PATH_MAX];
        dirname = "savepass";
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        sprintf(filepath, "%s\\%s\\%s.proglan", cwd, dirname, filename);

        //Exporting File
        FILE* fptr;
        fptr = fopen(filepath, "w");

        //Could not Create File
        if(fptr == NULL)
        {
            mvwprintw(content_win, 7, 1, "Could not create file");
            mvwprintw(content_win, 9, 1, " -Please avoid using symbols");
            mvwprintw(content_win, 11, 1, " -Maybe locked or being used by another application");
            wrefresh(content_win);

            werase(win);
            mvwprintw(win, 1, xMax/2-9, "FAILED");
            wrefresh(win);

            //Wait Initialize
            mvwprintw(content_win, 13, 1, "Please Wait (2s)");
            wrefresh(content_win);
            sleep(1);
            mvwprintw(content_win, 13, 1, "Please Wait (1s)");
            wrefresh(content_win);
            sleep(1);
            mvwprintw(content_win, 13, 1, "                ");
            wrefresh(content_win);

            ask(xMax, yMax, type);

            wgetch(content_win);
            erase();
            menu_utama(xMax, yMax);
        }
        else
        {
            fprintf(fptr, "%s", str);
            fclose(fptr);
        }

        //Sampai sini kondisi save ^

        werase(win);
        mvwprintw(win, 1, xMax/2-9, "COMPLETE");
        wrefresh(win);

        mvwprintw(content_win, 7, 1, "Save File as : <%s.proglan>", filename);
        mvwprintw(content_win, 9, 1, "Your file has been saved to :");
        mvwprintw(content_win, 11, 1, " -(%s)", filepath);
        wrefresh(content_win);

        //Wait Initialize
        mvwprintw(content_win, 13, 1, "Please Wait (2s)");
        wrefresh(content_win);
        sleep(1);
        mvwprintw(content_win, 13, 1, "Please Wait (1s)");
        wrefresh(content_win);
        sleep(1);
        mvwprintw(content_win, 13, 1, "                ");
        wrefresh(content_win);

    ask(xMax, yMax, type);
    }

    else
    {

    werase(win);
    mvwprintw(win, 1, xMax/2-9, "COMPLETE");
    wrefresh(win);

    //Wait Initialize
        mvwprintw(content_win, 7, 1, "Please Wait (2s)");
        wrefresh(content_win);
        sleep(1);
        mvwprintw(content_win, 7, 1, "Please Wait (1s)");
        wrefresh(content_win);
        sleep(1);
        mvwprintw(content_win, 7, 1, "                ");
        wrefresh(content_win);

    ask(xMax, yMax, type);
    }
}

int decrypt(int xMax, int yMax, int import)
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(4));

    //Watermark
    char mesg[] = {"Password Manager 1.0 Alpha Release"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    int i, x, fi=0;
    char str[64], filename[64];
    char type[]={"Decryption"};
    int sz = sizeof(str) / sizeof(str[0]);
    mvprintw(7, 6, "Decryption, Inf Box :");

    //Window Konten
    WINDOW * content_win = newwin(yMax-13, xMax-10, 8, 5);
    wbkgd(content_win, COLOR_PAIR(9));
    refresh();
    wrefresh(content_win);

    //Buat window khusus untuk input
    WINDOW * win = newwin(3, xMax-10, yMax-5, 5);
    wbkgd(win, COLOR_PAIR(2));
    refresh();

    if (import == 1)
    {
        //Import File
        mvwprintw(win, 1, 1,"Upload with a Filename: ");
        wgetstr(win, filename);

        //Specify path
        char* dirname = "savepass";
        char filepath[64];
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        sprintf(filepath, "%s\\%s\\%s.proglan", cwd, dirname, filename);

        //Load File
        FILE* fptr = fopen(filepath, "r");

        //Could not Load File
        if(fptr == NULL)
        {
            mvwprintw(content_win, 1, 1, "Could not load file");
            mvwprintw(content_win, 3, 1, " -Please check your filename again");
            mvwprintw(content_win, 5, 1, " -Maybe locked or being used by another application");


            werase(win);
            mvwprintw(win, 1, xMax/2-9, "FAILED");
            wrefresh(win);

            //Wait Initialize
            mvwprintw(content_win, 7, 1, "Please Wait (2s)");
            wrefresh(content_win);
            sleep(1);
            mvwprintw(content_win, 7, 1, "Please Wait (1s)");
            wrefresh(content_win);
            sleep(1);
            mvwprintw(content_win, 7, 1, "                ");
            wrefresh(content_win);

            ask(xMax, yMax, "F.Decryption");

            wgetch(win);

            erase();
            menu_utama(xMax, yMax);
        }

        mvwprintw(content_win, 1, 1,"Imported file from: <%s>", filepath);
        fi = 2;
        fscanf(fptr, "%s", &str);
    }

    else if (import != 1)
    {
        mvwprintw(win, 1, 1, "Please enter a string: %s", str);
        wrefresh(win);
        wgetstr(win, str);
    }


    mvwprintw(content_win, 1+fi, 1, "Input string: %s", str);


      for(i = 0; (i < sz && str[i] != '\0'); i++)
      {
        if (i<2)
            str[i] = str[i] - 3;
        else if (i<4)
            str[i] = str[i] - 5;
        else if (i<6)
            str[i] = str[i] - 11;
        else if (i<8)
            str[i] = str[i] + 7;
        else if (i<10)
            str[i] = str[i] + 10;
        else if (i>=10)
            str[i] = str[i] - 1 - i;
      }

    mvwprintw(content_win, 3+fi, 1, "Decryption Successful");
    mvwprintw(content_win, 5+fi, 1, "Decrypted string: %s", str);
    wrefresh(content_win);

    werase(win);
    mvwprintw(win, 1, xMax/2-9, "COMPLETE");
    wrefresh(win);

        //Wait Initialize
        mvwprintw(content_win, 7+fi, 1, "Please Wait (2s)");
        wrefresh(content_win);
        sleep(1);
        mvwprintw(content_win, 7+fi, 1, "Please Wait (1s)");
        wrefresh(content_win);
        sleep(1);
        mvwprintw(content_win, 7+fi, 1, "                ");
        wrefresh(content_win);

        if (import == 1)
            ask(xMax, yMax, "F.Decryption");
        else
            ask(xMax, yMax, type);

    erase();
    menu_utama(xMax, yMax);

   return 0;

}

int manager(xMax, yMax)
{
    WINDOW * judul;
    WINDOW * content_win;
    WINDOW * win;
    WINDOW * win1;
    WINDOW * win2;
    WINDOW *in;
    in = newwin(1, 1, 0, -1);
    refresh();

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(4));

    //Watermark
    char mesg[] = {"Password Manager 1.0 Alpha Release"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    //Window Judul
    judul = newwin(3, xMax/2+10, 4, 45);
    mvwprintw(judul, 1, 30, "MANAGER");
    wbkgd(judul, COLOR_PAIR(5));
    refresh();
    wrefresh(judul);

    //Window Konten
    content_win = newwin(yMax-9, xMax/2+10, 8, 45);
    refresh();
    wrefresh(content_win);

    char* choices[] = {"Create Bank Password", "Manage Bank Password", "Back"};

    //Buat window khusus untuk input
    win = newwin(8, xMax/3-2, 4, 5);
    mvwprintw(win, 3, 9, choices[0]);
    refresh();
    win1 = newwin(8, xMax/3-2, 13, 5);
    mvwprintw(win1, 3, 9, choices[1]);
    refresh();
    win2 = newwin(7, xMax/3-2, 22, 5);
    mvwprintw(win2, 3, 17, choices[2]);
    refresh();

    //Fungsi untuk mengambil input arrow key
    keypad(in, true);

    // Length of Array, bukan Size of Array
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight=0;

    while(1)
    {
            if(highlight==0)
            {
                wbkgd(win2, COLOR_PAIR(2));
                wbkgd(win1, COLOR_PAIR(2));
                wbkgd(win, COLOR_PAIR(1));
            }
            else if(highlight==1)
            {
                wbkgd(win, COLOR_PAIR(2));
                wbkgd(win2, COLOR_PAIR(2));
                wbkgd(win1, COLOR_PAIR(1));
            }
            else if(highlight==2)
            {
                wbkgd(win1, COLOR_PAIR(2));
                wbkgd(win, COLOR_PAIR(2));
                wbkgd(win2, COLOR_PAIR(1));
            }

        wrefresh(win);
        wrefresh(win1);
        wrefresh(win2);

        choice = wgetch(in);

        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 3)
                    highlight = 2;
                    break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;
    }
    if(highlight == 0)
    {
        clear();
        bankpass(xMax, yMax);
    }

      else if(highlight == 1)
    {
        clear();
        editbank(xMax, yMax);
    }

    else if(highlight == n-1)
    {
        clear();
        menu_utama(xMax, yMax);
    }

}

int ask(int xMax, int yMax, char type[32])
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);

    //Looping Program
    //Window Pop-Up pemberitahuan
        WINDOW * ask_win = newwin(5, xMax/2.5, 3, xMax/3.3);
        wbkgd(ask_win, COLOR_PAIR(2));
        refresh();
        mvwprintw(ask_win, 1, (xMax-strlen(type))/16, "Want to perform another %s?", type);
        wrefresh(ask_win);

    //Window Pop-Up waiting request

        //Fungsi untuk mengambil input arrow key
    keypad(ask_win, true);

    char *choices[]={"Yes", "No"};
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight = 0;

    while(1)
    {
        for(int i = 0; i < n; i++)
        {
            if(i==highlight)
                wattron(ask_win, A_REVERSE);
                mvwprintw(ask_win, 3, 19+6*i, choices[i]);
                wattroff(ask_win, A_REVERSE);
        }
        choice = wgetch(ask_win);

        switch(choice)
        {
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == n)
                    highlight = n-1;
                break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;
    }

    if(highlight == 0)
    {
        clear();
        if(type[0] == 'E')
        {
            int loop = 1;
            encrypt(xMax, yMax, loop);
        }
        else if (type[0] == 'D')
            decrypt(xMax, yMax, 0);
        else if (type[0] == 'F')
            decrypt(xMax, yMax, 1);
        else
        {
            int loop = 1;
            muldecrypt(xMax, yMax);
        }

    }

    else if(highlight == n-1)
    {
        clear();
        menu_utama(xMax, yMax);
    }
}

int ask_save (xMax, yMax)
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);

       int save;
       //Window Pop-Up pemberitahuan
        WINDOW * ask_win = newwin(5, xMax/2.5, 3, xMax/3.3);
        wbkgd(ask_win, COLOR_PAIR(2));
        refresh();
        mvwprintw(ask_win, 1, xMax/15, "Do you want to Save it to File?");
        wrefresh(ask_win);

    //Window Pop-Up waiting request

        //Fungsi untuk mengambil input arrow key
    keypad(ask_win, true);

    char *choices[]={"Yes", "No"};
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight = 0;

    while(1)
    {
        for(int i = 0; i < n; i++)
        {
            if(i==highlight)
                wattron(ask_win, A_REVERSE);
                mvwprintw(ask_win, 3, 19+6*i, choices[i]);
                wattroff(ask_win, A_REVERSE);
        }
        choice = wgetch(ask_win);

        switch(choice)
        {
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == n)
                    highlight = n-1;
                break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;
    }

    if(highlight == 0)
    {
        wclear(ask_win);
        save = 1;
    }

    else if(highlight == 1)
    {
        wclear(ask_win);
        save = -1;
    }

return save;
}

int de_menu(int xMax, int yMax)
{
    WINDOW * judul;
    WINDOW * content_win;
    WINDOW * win;
    WINDOW * win1;
    WINDOW * win2;
    WINDOW * win3;
    WINDOW *in;
    in = newwin(1, 1, 0, -1);
    refresh();

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(4));

    //Watermark
    char mesg[] = {"Password Manager 1.0 Alpha Release"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    //Window Judul
    judul = newwin(3, xMax/2+10, 4, 45);
    mvwprintw(judul, 1, 26, "DECRYPTION TOOLS");
    wbkgd(judul, COLOR_PAIR(5));
    refresh();
    wrefresh(judul);

    //Window Konten
    content_win = newwin(yMax-9, xMax/2+10, 8, 45);
    refresh();
    wrefresh(content_win);

    char* choices[] = {"Decrypt a String", "Decryption with Files", "Decrypt Multiple Files", "Back"};

    //Buat window khusus untuk input
    win = newwin(5, xMax/3-2, 4, 5);
    mvwprintw(win, 2, 11, choices[0]);
    refresh();
    win1 = newwin(6, xMax/3-2, 10, 5);
    mvwprintw(win1, 2, 9, choices[1]);
    refresh();
    win2 = newwin(6, xMax/3-2, 17, 5);
    mvwprintw(win2, 2, 8, choices[2]);
    refresh();
    win3 = newwin(5, xMax/3-2, 24, 5);
    mvwprintw(win3, 2, 17, choices[3]);
    refresh();

    //Fungsi untuk mengambil input arrow key
    keypad(in, true);

    // Length of Array, bukan Size of Array
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight=0;

    while(1)
    {
            if(highlight==0)
            {
                wbkgd(win3, COLOR_PAIR(2));
                wbkgd(win2, COLOR_PAIR(2));
                wbkgd(win1, COLOR_PAIR(2));
                wbkgd(win, COLOR_PAIR(1));
            }
            else if(highlight==1)
            {
                wbkgd(win3, COLOR_PAIR(2));
                wbkgd(win, COLOR_PAIR(2));
                wbkgd(win2, COLOR_PAIR(2));
                wbkgd(win1, COLOR_PAIR(1));
            }
            else if(highlight==2)
            {
                wbkgd(win3, COLOR_PAIR(2));
                wbkgd(win1, COLOR_PAIR(2));
                wbkgd(win, COLOR_PAIR(2));
                wbkgd(win2, COLOR_PAIR(1));
            }
            else if(highlight==3)
            {
                wbkgd(win2, COLOR_PAIR(2));
                wbkgd(win1, COLOR_PAIR(2));
                wbkgd(win, COLOR_PAIR(2));
                wbkgd(win3, COLOR_PAIR(1));
            }

        wrefresh(win);
        wrefresh(win1);
        wrefresh(win2);
        wrefresh(win3);

        choice = wgetch(in);

        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == n)
                    highlight = n-1;
                break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;
    }
    if(highlight == 0)
    {
        clear();
        erase();
        decrypt(xMax, yMax, 0);
    }

    else if(highlight == 1)
      {
        clear();
        erase();
        decrypt(xMax, yMax, 1);
      }

    else if(highlight == 2)
    {
        clear();
        muldecrypt(xMax, yMax);
    }

    erase();
    menu_utama(xMax, yMax);
}

int muldecrypt(int xMax, int yMax, int loop)
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(4));

    //Watermark
    char mesg[] = {"Password Manager 1.0 Alpha Release"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    char arr_file[16][64];
    char arr_str[16][64];
    int i, x, fi=0, lup=0;
    char str[64], filename[64], filepath[64];
    char type[]={"M.Decryption"};
    char *dirname;
    int sz = sizeof(str) / sizeof(str[0]);
    WINDOW * content_win;
    WINDOW * content_win2;
    WINDOW * win;
    WINDOW * ask_win;
    WINDOW * ghost_win;

    ghost_win = newwin(5, xMax/2.5, 3, xMax/3.3);
    wbkgd(ghost_win, COLOR_PAIR(4));
    refresh();

    ask_win = newwin(5, xMax/2.5, 3, xMax/3.3);
    wbkgd(ask_win, COLOR_PAIR(2));
    refresh();

    mvprintw(7, 6, "Decryption, Inf Box :");
    mvprintw(5, 6, "Input <end> to Stop");

    //Window Konten1
    content_win = newwin(yMax-13, (xMax-11)/2, 8, 5);
    wbkgd(content_win, COLOR_PAIR(9));
    refresh();
    wrefresh(content_win);

    //Window Konten2
    content_win2 = newwin(yMax-13, (xMax-11)/2, 8, 61);
    wbkgd(content_win2, COLOR_PAIR(9));
    refresh();
    wrefresh(content_win2);

    //Buat window khusus untuk input
    win = newwin(3, xMax-10, yMax-5, 5);
    wbkgd(win, COLOR_PAIR(2));
    refresh();

    while (1)
    {
        wclear(win);
        //Import File
        mvwprintw(win, 1, 1,"Upload with a Filename: ");
        wgetstr(win, filename);

        if (filename[0] == 'e' && filename[1] == 'n' && filename[2] == 'd')
            break;

        //Specify path
        char* dirname = "savepass";
        char filepath[64];
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        sprintf(filepath, "%s\\%s\\%s.proglan", cwd, dirname, filename);

        //Load File
        FILE* fptr = fopen(filepath, "r");

        //Could not Load File
        if(fptr == NULL)
        {
            if (lup <= 7)
            {
                mvwprintw(content_win, 1+2*lup, 1, "Could not load file" );
                wrefresh(content_win);
            }
            else if (lup > 7)
            {
                mvwprintw(content_win2, 2*lup-15, 1, "Could not load file" );
                wrefresh(content_win2);
            }
        }
        else
        {
            //scan string file dan simpan ke variable untuk di shift
            fscanf(fptr, "%s", &str);
            //Simpan filename ke array baru untuk menyimpan banyak filename
            strcpy(arr_file[lup], filename);
            if (lup <= 7)
            {
                mvwprintw(content_win, 1+2*lup, 1, "Import from: <%s.proglan>", arr_file[lup]);
                wrefresh(content_win);
            }

            else if (lup <= 15)
            {
                mvwprintw(content_win2, 1+2*lup-16, 1, "Import from: <%s.proglan>", arr_file[lup]);
                wrefresh(content_win2);
            }

            for(i = 0; (i < sz && str[i] != '\0'); i++)
            {
                if (i<2)
                    str[i] = str[i] - 3;
                else if (i<4)
                    str[i] = str[i] - 5;
                else if (i<6)
                    str[i] = str[i] - 11;
                else if (i<8)
                    str[i] = str[i] + 7;
                else if (i<10)
                    str[i] = str[i] + 10;
                else if (i>=10)
                    str[i] = str[i] - 1 - i;
            }
            strcpy(arr_str[lup], str);
            lup ++;
        }
    }

    //Hapus window konten
    wclear(content_win);
    wclear(content_win2);

    //buat baru untuk menyesuaikan dengan input
    content_win = newwin(yMax-13, (xMax-11)/2, 8, 5);
    wbkgd(content_win, COLOR_PAIR(9));

    content_win2 = newwin(yMax-13, (xMax-11)/2, 8, 61);
    wbkgd(content_win2, COLOR_PAIR(9));


    for (i = 0; i <= lup-1; i++)
    {

        if (i <= 7)
        {
            mvwprintw(content_win, 1+2*i, 1, "<%s.proglan>:%s", arr_file[i], arr_str[i]);
        }

        else if (i <= 15)
        {
            mvwprintw(content_win2, 1+2*i-16, 1, "<%s.proglan>:%s", arr_file[i], arr_str[i]);
        }
    }
        wrefresh(content_win);
        wrefresh(content_win2);

        werase(win);
        mvwprintw(win, 1, xMax/2-9, "COMPLETE");
        wrefresh(win);

        //Tanya untuk save
        int save = ask_save(xMax, yMax);
        wrefresh(ghost_win);
        FILE* fptr;

    if (loop != 1)
    {
        //Buat folder khusus
        dirname = malloc(25*sizeof(char));
        char *dirname = "depass";
        mkdir(dirname);
    }

    //Save
    if (save == 1)
    {
checkpoint :
        // Buat Box baru karena user mau masukin input lagi
        win = newwin(3, xMax-10, yMax-5, 5);
        wbkgd(win, COLOR_PAIR(2));
        ask_win = newwin(5, xMax/2.5, 3, xMax/3.3);
        wbkgd(ask_win, COLOR_PAIR(4));
        refresh();
        wrefresh(win);

        //Ambil nama File
        mvwprintw(win, 1, 1, "Simpan dengan nama file: ");
        wrefresh(win);
        wgetstr(win, filename);

        //Specify path
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));
        dirname = "depass";
        sprintf(filepath, "%s\\%s\\%s.txt", cwd, dirname, filename);

        //Exporting File
        fptr = fopen(filepath, "w");

        //Print string to Text File
         for (i = 0; i <= lup-1; i++)
        {
            fprintf(fptr, "<%s.proglan>:", arr_file[i]);
            fprintf(fptr, "%s\n", arr_str[i]);
        }

        //Could not Create File
        if(fptr == NULL)
        {
            mvwprintw(ask_win, 1, 7, "Could not create file, Try Again?");

    //Window Pop-Up waiting request
        //Fungsi untuk mengambil input arrow key
        keypad(ask_win, true);

        char *choices[]={"Yes", "No"};
        int n = sizeof(choices) / sizeof(choices[0]);
        int choice;
        int highlight = 0;

        while(1)
        {
            for(int i = 0; i < n; i++)
            {
                if(i==highlight)
                    wattron(ask_win, A_REVERSE);
                    mvwprintw(ask_win, 3, 19+6*i, choices[i]);
                    wattroff(ask_win, A_REVERSE);
            }
            choice = wgetch(ask_win);

            switch(choice)
            {
                case KEY_LEFT:
                    highlight--;
                if(highlight == -1)
                    highlight = 0;
                    break;
                case KEY_RIGHT:
                    highlight++;
                if(highlight == n)
                    highlight = n-1;
                    break;
                default:
                    break;
            }
            if(choice==10 || choice==13)
                break;
        }

        if(highlight == 0)
        {
            werase(ghost_win);
            wclear(ask_win);
            wrefresh(ghost_win);
            goto checkpoint;
        }

        else if(highlight == 1)
        {
            werase(ask_win);
            ask(xMax, yMax, type);
        }
    }
}
    else
        fclose(fptr);

    // Berhasil Save
    werase(win);
    if (save == 1)
        mvwprintw(win, 1, 1, "File Saved to:%s", filepath);
    else
        mvwprintw(win, 1, xMax/2-9, "COMPLETE");
    wrefresh(win);

    //Tanya untuk perform ulang
    ask(xMax, yMax, type);
}

int bankpass (int xMax, int yMax)
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(4));

    char arr_usr[64][64];
    char arr_pass[64][64];
    char arr_acc[64][64];

    //Encrypted String
    char arren_usr[64][64];
    char arren_pass[64][64];
    char arren_acc[64][64];

    int i, x, lup=0, page=1;
    char acc[64], filename[64], filepath[64], usr[64], pass[64];
    char *dirname;
    int sz = sizeof(acc) / sizeof(acc[0]);
    WINDOW * passwin;
    WINDOW * accountwin;
    WINDOW * userwin;
    WINDOW * inputwin;
    WINDOW * ghost_win;
    WINDOW * ask_win;
    WINDOW * top;
    WINDOW * sec1;
    WINDOW * sec2;
    WINDOW * sec3;
    WINDOW * sec4;
    WINDOW * sec5;
    WINDOW * sec6;
    WINDOW * sec7;
    WINDOW * sec8;
    WINDOW * sec9;
    WINDOW * sec10;
    WINDOW * sec11;
    WINDOW * sec12;
    WINDOW * seq1;
    WINDOW * seq2;
    WINDOW * seq3;
    WINDOW * seq4;
    WINDOW * answer;
    WINDOW *in;
    in = newwin(1, 1, 0, -1);
    refresh();

    //window apabila could not create file
    ask_win = newwin(5, xMax/2.5, 3, xMax/3.3);
    wbkgd(ask_win, COLOR_PAIR(2));
    refresh();

    int fi=0;

    while (x != -1)
    {
    if (fi==0 || fi >= 3)
    {
        mvprintw(6, 6, "Account Created : %d", fi);
    }

    WINDOW *jdl = newwin(1, 14, 5, 5);
    mvwprintw(jdl, 0, 1, "Bank Creator");
    wbkgd(jdl, COLOR_PAIR(2));
    refresh();
    wrefresh(jdl);

    //Watermark
    char mesg[] = {"Password Manager 1.0 Alpha Release"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    //Buat window baru khusus untuk input
    inputwin = newwin(3, xMax-10, yMax-5, 5);
    wbkgd(inputwin, COLOR_PAIR(2));
    refresh();

    //window Konten
    ghost_win = newwin(5, xMax/2.5, 3, xMax/3.3);
    wbkgd(ghost_win, COLOR_PAIR(4));
    refresh();

    accountwin = newwin(2, xMax-20, 8+5*lup, 5);
    wbkgd(accountwin, COLOR_PAIR(1));
    refresh();

    userwin = newwin(2,xMax/2-10, 10+5*lup, 5);
    wbkgd(userwin, COLOR_PAIR(5));
    refresh();

    passwin = newwin(2,xMax/2-10, 10+5*lup, 55);
    wbkgd(passwin, COLOR_PAIR(9));
    refresh();

    editer(xMax, yMax, lup);
    if(fi<1)
        bankpage(xMax, yMax, page, page);

      char *string[]=
    {"Enter type of Account: ",
     "Enter a Username: ",
     "Enter a Password: "};

    wrefresh(userwin); wrefresh(passwin); wrefresh(accountwin);

    mvwprintw(inputwin, 1, 1, string[0]);
    wrefresh(inputwin);
    wgetstr(inputwin, acc);

    mvwprintw(accountwin, 0, xMax/2-10-(strlen(acc)/2), acc); wrefresh(accountwin);

    wclear(inputwin);
    mvwprintw(inputwin, 1, 1, string[1]);
    wgetstr(inputwin, usr);

    mvwprintw(userwin, 0, xMax/4-3-(strlen(usr)/2), usr); wrefresh(userwin);

    wclear(inputwin);
    mvwprintw(inputwin, 1, 1, string[2]);
    wgetstr(inputwin, pass);

    mvwprintw(passwin, 0, xMax/4-3-(strlen(pass)/2), pass); wrefresh(passwin);

    //Menyimpan data sementara ke array
    strcpy(arr_acc[fi], acc);
    strcpy(arr_usr[fi], usr);
    strcpy(arr_pass[fi], pass);

    fi++;
    mvprintw(6, 6, "Account Created : %d", fi);

    x = askbank(xMax, yMax);
    wrefresh(ghost_win);

    if (lup < 1)
    {
        //Buat folder khusus
        dirname = malloc(25*sizeof(char));
        char *dirname = "myaccount";
        mkdir(dirname);
    }
        lup++;
        if (lup == 3)
        {
            clear();
            page++;
            bankpage(xMax, yMax, page, page);
            lup=0;
        }
    }


    FILE* fptr;
    //Save
    if (x == -1)
    {
    clear();
    //Watermark
    char mesg[] = {"Password Manager 1.0 Alpha Release"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    top = newwin(3,xMax-10, 4, 5);
    mvwprintw(top, 1, 38, "Please Choose a Security Question!");
    wbkgd(top, COLOR_PAIR(5));
    refresh();

    char security[12][64]=
    {
        "Favorite movie",
        "Childhood nickname",
        "Favorite food as a child",
        "Your first job",
        "What time were you born",
        "When is your anniversary",
        "What street did you grow up on",
        "Favorite color",
        "Name of your favorite pet",
        "Primary school you attend",
        "First best friends",
        "Dream job as a child"
    };

    answer = newwin(1, xMax-10, 7, 5);
    mvwprintw(answer, 0, 22, "Info : Input <end> after chosing security question to CANCEL operation");
    wbkgd(answer, COLOR_PAIR(9));
    refresh();

    seq1 = newwin(3,2, 9, 5);
    wbkgd(seq1, COLOR_PAIR(2));
    refresh();

    sec1 = newwin(3,xMax/3-6, 9, 9);
    mvwprintw(sec1, 1, 1, security[0]);
    wbkgd(sec1, COLOR_PAIR(2));
    refresh();

    sec2 = newwin(3,xMax/3-6, 9, 45);
        mvwprintw(sec2, 1, 1, security[1]);
    wbkgd(sec2, COLOR_PAIR(2));
    refresh();

    sec3 = newwin(3,xMax/3-6, 9, 81);
        mvwprintw(sec3, 1, 1, security[2]);
    wbkgd(sec3, COLOR_PAIR(2));
    refresh();

    seq2 = newwin(3,2, 13, 5);
    wbkgd(seq2, COLOR_PAIR(2));
    refresh();

    sec4 = newwin(3,xMax/3-6, 13, 9);
        mvwprintw(sec4, 1, 1, security[3]);
    wbkgd(sec4, COLOR_PAIR(2));
    refresh();

    sec5 = newwin(3,xMax/3-6, 13, 45);
        mvwprintw(sec5, 1, 1, security[4]);
    wbkgd(sec5, COLOR_PAIR(2));
    refresh();

    sec6 = newwin(3,xMax/3-6, 13, 81);
        mvwprintw(sec6, 1, 1, security[5]);
    wbkgd(sec6, COLOR_PAIR(2));
    refresh();

    seq3 = newwin(3,2, 17, 5);
    wbkgd(seq3, COLOR_PAIR(2));
    refresh();

    sec7 = newwin(3,xMax/3-6, 17, 9);
        mvwprintw(sec7, 1, 1, security[6]);
    wbkgd(sec7, COLOR_PAIR(2));
    refresh();

    sec8 = newwin(3,xMax/3-6, 17, 45);
        mvwprintw(sec8, 1, 1, security[7]);
    wbkgd(sec8, COLOR_PAIR(2));
    refresh();

    sec9 = newwin(3,xMax/3-6, 17, 81);
        mvwprintw(sec9, 1, 1, security[8]);
    wbkgd(sec9, COLOR_PAIR(2));
    refresh();

    seq4 = newwin(3,2, 21, 5);
    wbkgd(seq4, COLOR_PAIR(2));
    refresh();

    sec10 = newwin(3,xMax/3-6, 21, 9);
        mvwprintw(sec10, 1, 1, security[9]);
    wbkgd(sec10, COLOR_PAIR(2));
    refresh();

    sec11 = newwin(3,xMax/3-6, 21, 45);
        mvwprintw(sec11, 1, 1, security[10]);
    wbkgd(sec11, COLOR_PAIR(2));
    refresh();

    sec12 = newwin(3,xMax/3-6, 21, 81);
        mvwprintw(sec12, 1, 1, security[11]);
    wbkgd(sec12, COLOR_PAIR(2));
    refresh();

    wrefresh(top);
    wrefresh(answer);
    wrefresh(seq1);    wrefresh(sec1);    wrefresh(sec2);    wrefresh(sec3);
    wrefresh(seq2);    wrefresh(sec4);    wrefresh(sec5);    wrefresh(sec6);
    wrefresh(seq3);    wrefresh(sec7);    wrefresh(sec8);    wrefresh(sec9);
    wrefresh(seq4);    wrefresh(sec10);    wrefresh(sec11);    wrefresh(sec12);

    int scroll = 0, highlight=0;
    keypad(in, true);

    inputwin = newwin(3, xMax-10, yMax-5, 5);
    wbkgd(inputwin, COLOR_PAIR(2));
    wrefresh(inputwin);

    while(1)
    {
            if (scroll == 0)
            {
                wbkgd(seq1, COLOR_PAIR(1));
                wbkgd(seq2, COLOR_PAIR(2));
                wbkgd(seq3, COLOR_PAIR(2));
                wbkgd(seq4, COLOR_PAIR(2));

                if(highlight==0)
                {
                wbkgd(sec3, COLOR_PAIR(2));
                wbkgd(sec2, COLOR_PAIR(2));
                wbkgd(sec1, COLOR_PAIR(1));

                wbkgd(sec4, COLOR_PAIR(2));
                wbkgd(sec5, COLOR_PAIR(2));
                wbkgd(sec6, COLOR_PAIR(2));
                wbkgd(sec7, COLOR_PAIR(2));
                wbkgd(sec8, COLOR_PAIR(2));
                wbkgd(sec9, COLOR_PAIR(2));
                wbkgd(sec10, COLOR_PAIR(2));
                wbkgd(sec11, COLOR_PAIR(2));
                wbkgd(sec12, COLOR_PAIR(2));
                }
                else if(highlight==1)
                {
                wbkgd(sec3, COLOR_PAIR(2));
                wbkgd(sec1, COLOR_PAIR(2));
                wbkgd(sec2, COLOR_PAIR(1));

                wbkgd(sec4, COLOR_PAIR(2));
                wbkgd(sec5, COLOR_PAIR(2));
                wbkgd(sec6, COLOR_PAIR(2));
                wbkgd(sec7, COLOR_PAIR(2));
                wbkgd(sec8, COLOR_PAIR(2));
                wbkgd(sec9, COLOR_PAIR(2));
                wbkgd(sec10, COLOR_PAIR(2));
                wbkgd(sec11, COLOR_PAIR(2));
                wbkgd(sec12, COLOR_PAIR(2));
                }
                else if(highlight==2)
                {
                wbkgd(sec1, COLOR_PAIR(2));
                wbkgd(sec2, COLOR_PAIR(2));
                wbkgd(sec3, COLOR_PAIR(1));

                wbkgd(sec4, COLOR_PAIR(2));
                wbkgd(sec5, COLOR_PAIR(2));
                wbkgd(sec6, COLOR_PAIR(2));
                wbkgd(sec7, COLOR_PAIR(2));
                wbkgd(sec8, COLOR_PAIR(2));
                wbkgd(sec9, COLOR_PAIR(2));
                wbkgd(sec10, COLOR_PAIR(2));
                wbkgd(sec11, COLOR_PAIR(2));
                wbkgd(sec12, COLOR_PAIR(2));
                }
            }

            else if (scroll == 1)
            {
                wbkgd(seq1, COLOR_PAIR(2));
                wbkgd(seq2, COLOR_PAIR(1));
                wbkgd(seq3, COLOR_PAIR(2));
                wbkgd(seq4, COLOR_PAIR(2));

                if(highlight==0)
                {
                wbkgd(sec6, COLOR_PAIR(2));
                wbkgd(sec5, COLOR_PAIR(2));
                wbkgd(sec4, COLOR_PAIR(1));

                wbkgd(sec1, COLOR_PAIR(2));
                wbkgd(sec2, COLOR_PAIR(2));
                wbkgd(sec3, COLOR_PAIR(2));
                wbkgd(sec7, COLOR_PAIR(2));
                wbkgd(sec8, COLOR_PAIR(2));
                wbkgd(sec9, COLOR_PAIR(2));
                wbkgd(sec10, COLOR_PAIR(2));
                wbkgd(sec11, COLOR_PAIR(2));
                wbkgd(sec12, COLOR_PAIR(2));
                }
                else if(highlight==1)
                {
                wbkgd(sec4, COLOR_PAIR(2));
                wbkgd(sec6, COLOR_PAIR(2));
                wbkgd(sec5, COLOR_PAIR(1));

                wbkgd(sec1, COLOR_PAIR(2));
                wbkgd(sec2, COLOR_PAIR(2));
                wbkgd(sec3, COLOR_PAIR(2));
                wbkgd(sec7, COLOR_PAIR(2));
                wbkgd(sec8, COLOR_PAIR(2));
                wbkgd(sec9, COLOR_PAIR(2));
                wbkgd(sec10, COLOR_PAIR(2));
                wbkgd(sec11, COLOR_PAIR(2));
                wbkgd(sec12, COLOR_PAIR(2));
                }
                else if(highlight==2)
                {
                wbkgd(sec5, COLOR_PAIR(2));
                wbkgd(sec4, COLOR_PAIR(2));
                wbkgd(sec6, COLOR_PAIR(1));

                wbkgd(sec1, COLOR_PAIR(2));
                wbkgd(sec2, COLOR_PAIR(2));
                wbkgd(sec3, COLOR_PAIR(2));
                wbkgd(sec7, COLOR_PAIR(2));
                wbkgd(sec8, COLOR_PAIR(2));
                wbkgd(sec9, COLOR_PAIR(2));
                wbkgd(sec10, COLOR_PAIR(2));
                wbkgd(sec11, COLOR_PAIR(2));
                wbkgd(sec12, COLOR_PAIR(2));
                }
            }

            else if (scroll == 2)
            {
                wbkgd(seq1, COLOR_PAIR(2));
                wbkgd(seq2, COLOR_PAIR(2));
                wbkgd(seq3, COLOR_PAIR(1));
                wbkgd(seq4, COLOR_PAIR(2));

                if(highlight==0)
                {
                wbkgd(sec9, COLOR_PAIR(2));
                wbkgd(sec8, COLOR_PAIR(2));
                wbkgd(sec7, COLOR_PAIR(1));

                wbkgd(sec1, COLOR_PAIR(2));
                wbkgd(sec2, COLOR_PAIR(2));
                wbkgd(sec3, COLOR_PAIR(2));
                wbkgd(sec4, COLOR_PAIR(2));
                wbkgd(sec5, COLOR_PAIR(2));
                wbkgd(sec6, COLOR_PAIR(2));
                wbkgd(sec10, COLOR_PAIR(2));
                wbkgd(sec11, COLOR_PAIR(2));
                wbkgd(sec12, COLOR_PAIR(2));
                }
                else if(highlight==1)
                {
                wbkgd(sec7, COLOR_PAIR(2));
                wbkgd(sec9, COLOR_PAIR(2));
                wbkgd(sec8, COLOR_PAIR(1));

                wbkgd(sec1, COLOR_PAIR(2));
                wbkgd(sec2, COLOR_PAIR(2));
                wbkgd(sec3, COLOR_PAIR(2));
                wbkgd(sec4, COLOR_PAIR(2));
                wbkgd(sec5, COLOR_PAIR(2));
                wbkgd(sec6, COLOR_PAIR(2));
                wbkgd(sec10, COLOR_PAIR(2));
                wbkgd(sec11, COLOR_PAIR(2));
                wbkgd(sec12, COLOR_PAIR(2));
                }
                else if(highlight==2)
                {
                wbkgd(sec7, COLOR_PAIR(2));
                wbkgd(sec8, COLOR_PAIR(2));
                wbkgd(sec9, COLOR_PAIR(1));

                wbkgd(sec1, COLOR_PAIR(2));
                wbkgd(sec2, COLOR_PAIR(2));
                wbkgd(sec3, COLOR_PAIR(2));
                wbkgd(sec4, COLOR_PAIR(2));
                wbkgd(sec5, COLOR_PAIR(2));
                wbkgd(sec6, COLOR_PAIR(2));
                wbkgd(sec10, COLOR_PAIR(2));
                wbkgd(sec11, COLOR_PAIR(2));
                wbkgd(sec12, COLOR_PAIR(2));
                }
            }

            else if (scroll == 3)
            {
                wbkgd(seq1, COLOR_PAIR(2));
                wbkgd(seq2, COLOR_PAIR(2));
                wbkgd(seq3, COLOR_PAIR(2));
                wbkgd(seq4, COLOR_PAIR(1));

                if(highlight==0)
                {
                wbkgd(sec12, COLOR_PAIR(2));
                wbkgd(sec11, COLOR_PAIR(2));
                wbkgd(sec10, COLOR_PAIR(1));

                wbkgd(sec1, COLOR_PAIR(2));
                wbkgd(sec2, COLOR_PAIR(2));
                wbkgd(sec3, COLOR_PAIR(2));
                wbkgd(sec4, COLOR_PAIR(2));
                wbkgd(sec5, COLOR_PAIR(2));
                wbkgd(sec6, COLOR_PAIR(2));
                wbkgd(sec7, COLOR_PAIR(2));
                wbkgd(sec8, COLOR_PAIR(2));
                wbkgd(sec9, COLOR_PAIR(2));
                }
                else if(highlight==1)
                {
                wbkgd(sec10, COLOR_PAIR(2));
                wbkgd(sec12, COLOR_PAIR(2));
                wbkgd(sec11, COLOR_PAIR(1));

                wbkgd(sec1, COLOR_PAIR(2));
                wbkgd(sec2, COLOR_PAIR(2));
                wbkgd(sec3, COLOR_PAIR(2));
                wbkgd(sec4, COLOR_PAIR(2));
                wbkgd(sec5, COLOR_PAIR(2));
                wbkgd(sec6, COLOR_PAIR(2));
                wbkgd(sec7, COLOR_PAIR(2));
                wbkgd(sec8, COLOR_PAIR(2));
                wbkgd(sec9, COLOR_PAIR(2));
                }
                else if(highlight==2)
                {
                wbkgd(sec10, COLOR_PAIR(2));
                wbkgd(sec11, COLOR_PAIR(2));
                wbkgd(sec12, COLOR_PAIR(1));

                wbkgd(sec1, COLOR_PAIR(2));
                wbkgd(sec2, COLOR_PAIR(2));
                wbkgd(sec3, COLOR_PAIR(2));
                wbkgd(sec4, COLOR_PAIR(2));
                wbkgd(sec5, COLOR_PAIR(2));
                wbkgd(sec6, COLOR_PAIR(2));
                wbkgd(sec7, COLOR_PAIR(2));
                wbkgd(sec8, COLOR_PAIR(2));
                wbkgd(sec9, COLOR_PAIR(2));
                }
            }

        wrefresh(seq1);wrefresh(sec1);wrefresh(sec2);wrefresh(sec3);
        wrefresh(seq2);wrefresh(sec4);wrefresh(sec5);wrefresh(sec6);
        wrefresh(seq3);wrefresh(sec7);wrefresh(sec8);wrefresh(sec9);
        wrefresh(seq4);wrefresh(sec10);wrefresh(sec11);wrefresh(sec12);

        int choice = wgetch(in);

        switch(choice)
        {
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == 3)
                    highlight = 2;
                break;
            case KEY_UP:
                scroll--;
                if(scroll == -1)
                    scroll = 0;
                break;
            case KEY_DOWN:
                scroll++;
                if(scroll == 4)
                    scroll = 3;
                break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;
    }

    int os=0;

    if (scroll==0)
    {
        if (highlight==0)
        os = 0;
        else if (highlight==1)
        os = 1;
        else if (highlight==2)
        os = 2;
    }

    else if (scroll==1)
    {
        if (highlight==0)
        os = 3;
        else if (highlight==1)
        os = 4;
        else if (highlight==2)
        os = 5;
    }

    else if (scroll==2)
    {
        if (highlight==0)
        os = 6;
        else if (highlight==1)
        os = 7;
        else if (highlight==2)
        os = 8;
    }

    else
    {
        if (highlight==0)
        os = 9;
        else if (highlight==1)
        os = 10;
        else if (highlight==2)
        os = 11;
    }

    char ans[64];

    wclear(top);
    mvwprintw(top, 1, 40, "Answer the Security Question");
    wrefresh(top);
    mvwprintw(inputwin, 1, 1, "%s: ", security[os]);
    wgetstr(inputwin, ans);

    char fls[]={"end"};

    if (strcmp(ans, fls)==0)
    {
        erase();
        clear();
        menu_utama(xMax, yMax);
    }

    clear();

    //Watermark
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    seq4 = newwin(13, 55, 11, 5);
    refresh();

    sec1 = newwin(3, 53, 11, 62);
    mvwprintw(sec1, 1, 16, "File Security Question");
    wbkgd(sec1, COLOR_PAIR(1));
    refresh();
    wrefresh(sec1);

    seq1 = newwin(3, 53, 14, 62);
    wbkgd(seq1, COLOR_PAIR(9));
    refresh();

    sec2 = newwin(3, 53, 18, 62);
    mvwprintw(sec2, 1, 17, "File Authentication");
    wbkgd(sec2, COLOR_PAIR(1));
    refresh();
    wrefresh(sec2);

    answer = newwin(3, 53, 21, 62);
    wbkgd(answer, COLOR_PAIR(9));
    refresh();

    top = newwin(3,xMax-10,8,5);
    wbkgd(top, COLOR_PAIR(5));
    refresh();

    mvwprintw(answer, 1, 26-strlen(ans)/2, "%s", ans);
    mvwprintw(seq1, 1, 26-strlen(security[os])/2, "%s", security[os]);

    wrefresh(answer);
    wrefresh(seq1);
    wrefresh(seq4);

    wclear(top);
    mvwprintw(top, 1, 41, "Insert the desired Filename");
    wrefresh(top);

checkpoint :
        // Buat Box baru karena user mau masukin input lagi
        inputwin = newwin(3, xMax-10, yMax-5, 5);
        wbkgd(inputwin, COLOR_PAIR(2));
        ask_win = newwin(5, xMax/2.5, 3, xMax/3.3);
        wbkgd(ask_win, COLOR_PAIR(2));
        refresh();
        wrefresh(inputwin);

        //Ambil nama File
        mvwprintw(inputwin, 1, 1, "Simpan dengan nama file: ");
        wrefresh(inputwin);
        wgetstr(inputwin, filename);

        //Specify path
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));
        dirname = "myaccount";
        sprintf(filepath, "%s\\%s\\%s.mya", cwd, dirname, filename);

        //Exporting File
        fptr = fopen(filepath, "w");

        //Could not Create File
        if(fptr == NULL)
        {
            mvwprintw(ask_win, 1, 7, "Could not create file, Try Again?");

            mvwprintw(seq4, 1, 1, "Could not create file");
            mvwprintw(seq4, 3, 1, " -Please avoid using symbols");
            mvwprintw(seq4, 5, 1, " -Maybe locked or being used by another application");
            wrefresh(seq4);

    //Window Pop-Up waiting request
        //Fungsi untuk mengambil input arrow key
        keypad(ask_win, true);

        char *choices[]={"Yes", "No"};
        int n = sizeof(choices) / sizeof(choices[0]);
        int choice;
        int highlight = 0;

        while(1)
        {
            for(int i = 0; i < n; i++)
            {
                if(i==highlight)
                    wattron(ask_win, A_REVERSE);
                    mvwprintw(ask_win, 3, 19+6*i, choices[i]);
                    wattroff(ask_win, A_REVERSE);
            }
            choice = wgetch(ask_win);

            switch(choice)
            {
                case KEY_LEFT:
                    highlight--;
                if(highlight == -1)
                    highlight = 0;
                    break;
                case KEY_RIGHT:
                    highlight++;
                if(highlight == n)
                    highlight = n-1;
                    break;
                default:
                    break;
            }
            if(choice==10 || choice==13)
                break;
        }

        if(highlight == 0)
        {
            werase(ghost_win);
            wclear(ask_win);
            wrefresh(ghost_win);
            goto checkpoint;
        }

        else if(highlight == 1)
        {
            werase(ask_win);
            wrefresh(ghost_win);
            menu_utama(xMax, yMax);
        }
    }

        lup=0;
        //ENCRYPT STARTS
        while (1)
        {
            char str[64];
            strcpy(str, arr_usr[lup]);
            int sz = strlen(str);

            //ENCRYPT USERNAME
            for(i = 0; (i < sz && str[i] != '\0'); i++)
            {
                if (i<2)
                    str[i] = str[i] + 3;
                else if (i<4)
                    str[i] = str[i] + 5;
                else if (i<6)
                    str[i] = str[i] + 11;
                else if (i<8)
                    str[i] = str[i] - 7;
                else if (i<10)
                    str[i] = str[i] - 10;
                else if (i>=10)
                    str[i] = str[i] + 1 + i;
            }
            strcpy(arren_usr[lup], str);

            memset(str, 0, sizeof(str));
            strcpy(str, arr_pass[lup]);
            sz = strlen(str);

            //ENCRYPT PASS
            for(i = 0; (i < sz && str[i] != '\0'); i++)
            {
                if (i<2)
                    str[i] = str[i] + 3;
                else if (i<4)
                    str[i] = str[i] + 5;
                else if (i<6)
                    str[i] = str[i] + 11;
                else if (i<8)
                    str[i] = str[i] - 7;
                else if (i<10)
                    str[i] = str[i] - 10;
                else if (i>=10)
                    str[i] = str[i] + 1 + i;
            }
            strcpy(arren_pass[lup], str);

            memset(str, 0, sizeof(str));
            strcpy(str, arr_acc[lup]);
            sz = strlen(str);

            //ENCRYPT ACC
            for(i = 0; (i < sz && str[i] != '\0'); i++)
            {
                if (i<2)
                    str[i] = str[i] + 3;
                else if (i<4)
                    str[i] = str[i] + 5;
                else if (i<6)
                    str[i] = str[i] + 11;
                else if (i<8)
                    str[i] = str[i] - 7;
                else if (i<10)
                    str[i] = str[i] - 10;
                else if (i>=10)
                    str[i] = str[i] + 1 + i;
            }
            strcpy(arren_acc[lup], str);

            lup++;
            if(lup == fi)
                break;
        }

        //Print string to Text File
            fprintf(fptr, "\n%s", security[os]);
            fprintf(fptr, "\n%s", ans);

         for (i = 0; i < fi; i++)
        {
            fprintf(fptr, "\n%s", arren_acc[i]);
            fprintf(fptr, "\n%s", arren_usr[i]);
            fprintf(fptr, "\n%s", arren_pass[i]);
        }
}
        fclose(fptr);

    if (x == -1)
    {
    // Berhasil Save
    werase(inputwin);
    wclear(seq4);
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    mvwprintw(inputwin, 1, xMax/2-9, "COMPLETE");
    mvwprintw(seq4, 1, 1, "File Saved to:");
    mvwprintw(seq4, 2, 1, " <%s.mya>", filename);
    mvwprintw(seq4, 4, 1, "Folder Directory:");
    mvwprintw(seq4, 5, 1, " <%s>", dirname);
    mvwprintw(seq4, 7, 1, "Folder Path:");
    mvwprintw(seq4, 8, 1, " <%s>", cwd);
    wrefresh(seq4);
    wrefresh(inputwin);

        mvwprintw(top, 1, 36, "Press any key to Redirect back to Menu");
        wrefresh(top);
        getch();
        erase();
        clear();
        menu_utama(xMax, yMax);
    }
}

int askbank(int xMax, int yMax)
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);

    //Looping Program
    //Window Pop-Up pemberitahuan
        WINDOW * ask_win = newwin(5, xMax/2.5, 3, xMax/3.3);
        wbkgd(ask_win, COLOR_PAIR(2));
        refresh();
        mvwprintw(ask_win, 1, 10, "Want to add another Account?");
        wrefresh(ask_win);

    //Window Pop-Up waiting request

        //Fungsi untuk mengambil input arrow key
    keypad(ask_win, true);

    char *choices[]={"Yes", "No"};
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight = 0;

    while(1)
    {
        for(int i = 0; i < n; i++)
        {
            if(i==highlight)
                wattron(ask_win, A_REVERSE);
                mvwprintw(ask_win, 3, 19+6*i, choices[i]);
                wattroff(ask_win, A_REVERSE);
        }
        choice = wgetch(ask_win);

        switch(choice)
        {
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == n)
                    highlight = n-1;
                break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;
    }

    if(highlight == 0)
    {
        wclear(ask_win);
        return 1;
    }

    else if(highlight == n-1)
    {
        return -1;
    }
}

int editbank(int xMax, int yMax)
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_RED);
    bkgd(COLOR_PAIR(4));

    char arr_usr[64][64];
    char arr_pass[64][64];
    char arr_acc[64][64];

    //Encrypted String
    char arren_usr[64][64];
    char arren_pass[64][64];
    char arren_acc[64][64];
    char security[64];
    char secans[64];

    int i, x, lup=0, addlup=0;
    char acc[64], filename[64], filepath[64], usr[64], pass[64];
    char *dirname;
    int sz = sizeof(acc) / sizeof(acc[0]);
    WINDOW * passwin;
    WINDOW * accountwin;
    WINDOW * userwin;
    WINDOW * inputwin;
    WINDOW * ghost_win;
    WINDOW * ask_win;
    WINDOW * winwait;
    WINDOW * judul;
    WINDOW * sec;
    WINDOW * secbar;
    WINDOW * pin;
    WINDOW * pinbar;

    //window apabila could not create file
    ask_win = newwin(5, xMax/2.5, 3, xMax/3.3);
    wbkgd(ask_win, COLOR_PAIR(2));
    refresh();

    int fi=0;

        //Watermark
    char mesg[] = {"Password Manager 1.0 Alpha Release"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    //Buat window baru khusus untuk input
    inputwin = newwin(3, xMax-10, yMax-5, 5);
    wbkgd(inputwin, COLOR_PAIR(2));
    refresh();

    //window Konten
    ghost_win = newwin(5, 40, 3, 75);
    wbkgd(ghost_win, COLOR_PAIR(4));
    refresh();

    accountwin = newwin(2, xMax-10, 8+4*lup, 5);
    wbkgd(accountwin, COLOR_PAIR(1));
    refresh();

    userwin = newwin(2,xMax/2-5, 10+4*lup, 5);
    wbkgd(userwin, COLOR_PAIR(5));
    refresh();

    passwin = newwin(2,xMax/2-5, 10+4*lup, 60);
    wbkgd(passwin, COLOR_PAIR(9));
    refresh();

    winwait = newwin(20 ,xMax/2-5, 4, 5);
    mvwprintw(winwait, 1, 1, "Input <end> to Exit");
    wbkgd(passwin, COLOR_PAIR(9));
    refresh();

    judul = newwin(3, 53, 4, 62);
    mvwprintw(judul, 1, 18, "Password Manager");
    wbkgd(judul, COLOR_PAIR(5));
    refresh();
    wrefresh(judul);

    sec = newwin(3, 53, 8, 62);
    mvwprintw(sec, 1, 15, "File Security Question");
    wbkgd(sec, COLOR_PAIR(1));
    refresh();
    wrefresh(sec);

    secbar = newwin(3, 53, 11, 62);
    wbkgd(secbar, COLOR_PAIR(9));
    refresh();
    wrefresh(secbar);

    pin = newwin(3, 53, 15, 62);
    mvwprintw(pin, 1, 14, "Prove File Authentication");
    wbkgd(pin, COLOR_PAIR(1));
    refresh();
    wrefresh(pin);

    pinbar = newwin(3, 53, 18, 62);
    wbkgd(pinbar, COLOR_PAIR(9));
    refresh();
    wrefresh(pinbar);

    int line=1;

     while (1)
    {
        char str[64];
        wclear(inputwin);
        //Import File
        mvwprintw(inputwin, 1, 1,"Upload with a Filename: ");
        wrefresh(winwait);
        wgetstr(inputwin, filename);

        if (filename[0] == 'e' && filename[1] == 'n' && filename[2] == 'd')
            menu_utama(xMax, yMax);

        //Specify path
        char* dirname = "myaccount";
        char filepath[64];
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        sprintf(filepath, "%s\\%s\\%s.mya", cwd, dirname, filename);

        //Load File
        FILE* file = fopen(filepath, "r");

        //Could not Load File
        if(file == NULL)
        {
            mvwprintw(winwait, 3, 1, "Could Not Load File");
            mvwprintw(winwait, 5, 1, " -Please check your filename again");
            mvwprintw(winwait, 7, 1, " -Maybe locked or being used by another application");
        }
        else
        {
            char c;
            for (c = getc(file); c != EOF; c = getc(file))
                if (c == '\n') // Increment count if this character is newline
                    line = line + 1;
            fclose(file);
            break;
        }
    }

    wclear(winwait);
    char cwd[PATH_MAX];

        dirname = "myaccount";
        filepath[64];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        sprintf(filepath, "%s\\%s\\%s.mya", cwd, dirname, filename);

    mvwprintw(winwait, 1, 1, "Filename:");
    mvwprintw(winwait, 2, 1, " <%s.mya>", filename);
    mvwprintw(winwait, 4, 1, "Imported from:");
    mvwprintw(winwait, 5, 1, " <%s>", cwd);
    mvwprintw(winwait, 7, 1, "Waiting for File Authentication...");
    wrefresh(winwait);

        dirname = "myaccount";
        filepath[64];

        //Load File
        FILE* file = fopen(filepath, "r");

        int lineNumber = 1;
        char code[64];
        int count = 0;
        while (fgets(code, sizeof(code), file))
        {

        if (count == lineNumber)
        {
            strcpy(code, strtok(code, "\n"));
            mvwprintw(secbar, 1, 26-strlen(code)/2, "%s", code);
            wrefresh(secbar);
            strcpy(security, code);
            break;
        }
        else
            count++;
        }

    wclear(inputwin);
    mvwprintw(inputwin, 1, 1, "Answer to the Security Question: ");
    char ans[64];
    wrefresh(inputwin);
    wgetstr(inputwin, ans);

    mvwprintw(pinbar, 1, 23, "PENDING");
    mvwprintw(winwait, 7, 1, "                                   ");
    mvwprintw(winwait, 7, 1, "Attempting code...");
    wclear(inputwin);
    mvwprintw(inputwin, 1, 50, "PLEASE WAIT");

    wrefresh(pinbar); wrefresh(winwait); wrefresh(inputwin);

    lineNumber = 0;
    char code2[64];
    count = 0;

    while (fgets(code2, sizeof(code2), file))
    {

        if (count == lineNumber)
        {
             strcpy(code2, strtok(code2, "\n"));
             break;
        }
        else
            count++;
    }

        if(strcmp(ans, code2) == 0)
        {
            sleep(2);
            wclear(pinbar);
            mvwprintw(pinbar, 1, 23, "SUCCESS");
            wbkgd(pinbar, COLOR_PAIR(3));
            wrefresh(pinbar);
            strcpy(secans, code2);
        }

        else
        {
            sleep(2);
            wclear(pinbar);
            mvwprintw(pinbar, 1, 24, "FAILED");
            wbkgd(pinbar, COLOR_PAIR(7));
            wrefresh(pinbar);
            mvwprintw(winwait, 9, 1, "Security Answer's not Match!");
            mvwprintw(winwait, 11, 1, "Redirecting Back to Menu...(3)");
            wrefresh(winwait);
            sleep(1);
            mvwprintw(winwait, 11, 1, "Redirecting Back to Menu...(2)");
            wrefresh(winwait);
            sleep(1);
            mvwprintw(winwait, 11, 1, "Redirecting Back to Menu...(1)");
            wrefresh(winwait);
            sleep(1);
            clear();
            menu_utama(xMax, yMax);
        }

        lup = 0;
        int cla=1;

        while (1)
        {
            mvwprintw(winwait, 7, 1, "Security Answer's Match!");
            mvwprintw(winwait, 9, 1, "Decrypting...(%d)", cla);
            wrefresh(winwait);

            lineNumber = 0;
            char str[64];
            count = 0;

            while (fgets(str, sizeof(str), file))
            {
            if (count == lineNumber)
            {
                strcpy(str, strtok(str, "\n"));
                break;
            }
            else
                count++;
            }

            sz = sizeof(str)/sizeof(str[0]);
            for(i = 0; (i < sz && str[i] != '\0'); i++)
            {
                if (i<2)
                    str[i] = str[i] - 3;
                else if (i<4)
                    str[i] = str[i] - 5;
                else if (i<6)
                    str[i] = str[i] - 11;
                else if (i<8)
                    str[i] = str[i] + 7;
                else if (i<10)
                    str[i] = str[i] + 10;
                else if (i>=10)
                    str[i] = str[i] - 1 - i;
            }

            if (lup == -3+3*cla)
                strcpy(arr_acc[cla-1], str);
            else if (lup == -2+3*cla)
                strcpy(arr_usr[cla-1], str);
            else if (lup == -1+3*cla)
                strcpy(arr_pass[cla-1], str);

            lup++;

            if (3+lup == line)
                break;

            else if (lup == 3*cla)
            {
                cla++;
                sleep(1);
            }
        }

        wclear(inputwin);
        mvwprintw(inputwin, 1, xMax/2-9, "COMPLETE");
        mvwprintw(winwait, 11, 1, "File has been Decrypted Succesfully");
        mvwprintw(winwait, 13, 1, "Press any key to Continue...");
        wrefresh(inputwin);
        wrefresh(winwait);
        getch();

        // SELESAI WINDOW AUTHENTICATION
print :
    clear();
    int page=1;
    int clock=0;
    int gopage=0;

test:
    lup = 0;
    int num;
    while (1)
    {
        accountwin = newwin(2, xMax-20, 8+5*lup, 5);
        wbkgd(accountwin, COLOR_PAIR(1));
        refresh();

        userwin = newwin(2,xMax/2-10, 10+5*lup, 5);
        wbkgd(userwin, COLOR_PAIR(5));
        refresh();

        passwin = newwin(2,xMax/2-10, 10+5*lup, 55);
        wbkgd(passwin, COLOR_PAIR(9));
        refresh();

        if (gopage == 1)
        {
            mvwprintw(accountwin, 0, xMax/2-10-(strlen(arr_acc[3*num-3+lup])/2), arr_acc[3*num-3+lup]); wrefresh(accountwin);
            mvwprintw(userwin, 0, xMax/4-3-(strlen(arr_usr[3*num-3+lup])/2), arr_usr[3*num-3+lup]); wrefresh(userwin);
            mvwprintw(passwin, 0, xMax/4-3-(strlen(arr_pass[3*num-3+lup])/2), arr_pass[3*num-3+lup]); wrefresh(passwin);
            editer(xMax, yMax, lup);

            if (lup+3*num-2 == cla)
            break;

            lup++;

            if (lup == 3)
                break;
        }

        else if (gopage == 0)
        {
            mvwprintw(accountwin, 0, xMax/2-10-(strlen(arr_acc[3*page-3+lup])/2), arr_acc[3*page-3+lup]); wrefresh(accountwin);
            mvwprintw(userwin, 0, xMax/4-3-(strlen(arr_usr[3*page-3+lup])/2), arr_usr[3*page-3+lup]); wrefresh(userwin);
            mvwprintw(passwin, 0, xMax/4-3-(strlen(arr_pass[3*page-3+lup])/2), arr_pass[3*page-3+lup]); wrefresh(passwin);
            editer(xMax, yMax, lup);

            if (lup+1+3*clock == cla)
            break;

            lup++;

            if (lup == 3)
            {
                page++;
                clock++;
                lup=0;
                clear();
            }
        }
    }

    //Watermark
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);
    if (gopage==0)
        bankpage(xMax, yMax, page, page);
    else
        bankpage(xMax, yMax, page, num);

    WINDOW *top = newwin(1, 14, 5, 5);
    mvwprintw(top, 0, 1, "Bank Manager");
    wbkgd(top, COLOR_PAIR(2));
    refresh();
    wrefresh(top);

    mvprintw(6, 5, "Available Command : ");

    WINDOW *c = newwin(1, 6, 6, 25);
    mvwprintw(c, 0, 1, "edit");
    wbkgd(c, COLOR_PAIR(2));
    refresh();
    wrefresh(c);

    WINDOW *c1 = newwin(1, 6, 6, 32);
    mvwprintw(c1, 0, 1, "goto");
    wbkgd(c1, COLOR_PAIR(2));
    refresh();
    wrefresh(c1);

    WINDOW *c2 = newwin(1, 6, 6, 39);
    mvwprintw(c2, 0, 1, "save");
    wbkgd(c2, COLOR_PAIR(2));
    refresh();
    wrefresh(c2);

    WINDOW *c3 = newwin(1, 5, 6, 46);
    mvwprintw(c3, 0, 1, "end");
    wbkgd(c3, COLOR_PAIR(2));
    refresh();
    wrefresh(c3);

        WINDOW *c4 = newwin(1, 5, 6, 52);
    mvwprintw(c4, 0, 1, "add");
    wbkgd(c4, COLOR_PAIR(2));
    refresh();
    wrefresh(c4);

    char *string[]=
    {"Enter a Command: ",
     "Enter Page Number to View: ",
     "PLEASE SELECT TO EDIT"};

     if (addlup == 1)
        goto add;

getstr :
    //Buat window baru khusus untuk input
    inputwin = newwin(3, xMax-10, yMax-5, 5);
    wbkgd(inputwin, COLOR_PAIR(2));
    mvwprintw(inputwin, 1, 1, string[0]);
    refresh();
    wrefresh(inputwin);
    wgetnstr(inputwin, ans, 4);

    //COMMAND LINE
    char end[]={"end"};
    char go[]={"goto"};
    char edit[]={"edit"};
    char save[]={"save"};
    char add[]={"add"};
    int turn;

    // USER EXIT WINDOW
    if (strcmp(ans, end)== 0)
    {
        clear();
        fclose(file);
        menu_utama(xMax, yMax);
    }

    // USER PINDAH PAGE
    if (strcmp(ans, go)==0)
    {
        char str[16];
        num=0;
        while (num > page || num < 1)
        {
            wclear(inputwin);
            mvwprintw(inputwin, 1, 1, string[1]);
            wgetnstr(inputwin, str, 2);
            sscanf(str, "%d", &num);
        }
        clear();
        gopage=1;
        goto test;
    }

    if (gopage==0 || page ==1)
        num = page;

    // USER EDIT DATA
    if (strcmp(ans, edit)==0)
    {
        int askdel=0;
        wclear(inputwin);
        mvwprintw(inputwin, 1, 45, string[2]);
        wbkgd(inputwin, COLOR_PAIR(5));
        wrefresh(inputwin);
        turn = editmg(xMax, yMax, num, cla);
editlup:
        clear();
        //WATERMARK
        mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

       char *string[]=
    {"Enter type of Account: ",
     "Enter a Username: ",
     "Enter a Password: "};

    //Buat window baru khusus untuk input
    inputwin = newwin(3, xMax-10, yMax-5, 5);
    wbkgd(inputwin, COLOR_PAIR(2));
    mvwprintw(inputwin, 1, 1, string[0]);
    refresh();

    WINDOW *top = newwin(1, 11, 5, 5);
    mvwprintw(top, 0, 1, "Edit Pass");
    wbkgd(top, COLOR_PAIR(2));
    refresh();
    wrefresh(top);

    mvprintw(6, 5, "Available Command : ");

    WINDOW *c = newwin(1, 8, 6, 25);
    mvwprintw(c, 0, 1, "cancel");
    wbkgd(c, COLOR_PAIR(2));
    refresh();
    wrefresh(c);

    //NON-AKTIFKAN DELETE APABILA JUMLAH AKUN HANYA 1
    if (cla>1)
    {
        WINDOW *c1 = newwin(1, 8, 6, 34);
        mvwprintw(c1, 0, 1, "delete");
        wbkgd(c1, COLOR_PAIR(2));
        refresh();
        wrefresh(c1);
    }

    char del[]={"delete"};
    char fls[]={"cancel"};


        lup = 0;

        while (lup != 2)
        {
            accountwin = newwin(3, xMax-20, 8+7*lup, 15);
            wbkgd(accountwin, COLOR_PAIR(1));
            refresh();

            userwin = newwin(3,xMax/2-10, 11+7*lup, 15);
            wbkgd(userwin, COLOR_PAIR(5));
            refresh();

            passwin = newwin(3,xMax/2-10, 11+7*lup, 65);
            wbkgd(passwin, COLOR_PAIR(9));
            refresh();

            WINDOW *winb = newwin(6, 8, 8+7*lup, 5);
            wbkgd(winb, COLOR_PAIR(6));
            if (lup == 0)
                mvwprintw(winb, 2, 1, "BEFORE");
            else if (lup == 1)
                mvwprintw(winb, 2, 1, "AFTER");
            refresh();
            wrefresh(winb);

            if (lup == 0)
            {
                mvwprintw(accountwin, 1, xMax/2-10-(strlen(arr_acc[3*num-3+turn])/2), "%s", arr_acc[3*num-3+turn]);
                mvwprintw(userwin, 1, xMax/4-3-(strlen(arr_usr[3*num-3+turn])/2), "%s", arr_usr[3*num-3+turn]);
                mvwprintw(passwin, 1, xMax/4-3-(strlen(arr_pass[3*num-3+turn])/2), "%s", arr_pass[3*num-3+turn]);
            }

            wrefresh(passwin); wrefresh(userwin); wrefresh(accountwin);
            lup++;
        }

checkpoint :
            wclear(inputwin);
            mvwprintw(inputwin, 1, 1, string[0]);
            wgetstr(inputwin, acc);
            if (strcmp(acc, fls)==0)
                goto print;
            if (cla > 1)
            {
                if (strcmp(acc, del)==0)
                {
                    askdel = delcon(xMax, yMax);
                    if (askdel == 1)
                        goto delanyway;
                    else
                    {
                        wrefresh(ghost_win);
                        goto editlup;
                    }

                }
            }


            mvwprintw(accountwin, 1, xMax/2-10-(strlen(acc)/2), "%s", acc);
            wrefresh(accountwin);

            wclear(inputwin);
            mvwprintw(inputwin, 1, 1, string[1]);
            wgetstr(inputwin, usr);
            if (strcmp(usr, fls)==0)
                goto print;
            if (cla > 1)
            {
                if (strcmp(usr, del)==0)
                {
                    askdel = delcon(xMax, yMax);
                    if (askdel == 1)
                        goto delanyway;
                    else
                    {
                        wrefresh(ghost_win);
                        goto editlup;
                    }

                }
            }
            mvwprintw(userwin, 1, xMax/4-3-(strlen(usr)/2), "%s", usr);
            wrefresh(userwin);

            wclear(inputwin);
            mvwprintw(inputwin, 1, 1, string[2]);
            wgetstr(inputwin, pass);
            if (strcmp(pass, fls)==0)
                goto print;
            if (cla > 1)
            {
                if (strcmp(pass, del)==0)
                {
                    askdel = delcon(xMax, yMax);
                    if (askdel == 1)
                        goto delanyway;
                    else
                    {
                        wrefresh(ghost_win);
                        goto editlup;
                    }

                }
            }

            mvwprintw(passwin, 1, xMax/4-3-(strlen(pass)/2), "%s", pass);
            wrefresh(passwin);
delanyway:
            //ERASE
            if (askdel==1)
            {
                if (turn == 0)
                {
                    memset(arr_acc[3*num-3], 0, sizeof(arr_acc[3*num-3]));
                    memset(arr_usr[3*num-3], 0, sizeof(arr_usr[3*num-3]));
                    memset(arr_pass[3*num-3], 0, sizeof(arr_pass[3*num-3]));
                }
                else if (turn == 1)
                {
                    memset(arr_acc[3*num-2], 0, sizeof(arr_acc[3*num-2]));
                    memset(arr_usr[3*num-2], 0, sizeof(arr_usr[3*num-2]));
                    memset(arr_pass[3*num-2], 0, sizeof(arr_pass[3*num-2]));
                }
                else if (turn == 2)
                {
                    memset(arr_acc[3*num-1], 0, sizeof(arr_acc[3*num-1]));
                    memset(arr_usr[3*num-1], 0, sizeof(arr_usr[3*num-1]));
                    memset(arr_pass[3*num-1], 0, sizeof(arr_pass[3*num-1]));
                }

            }

            if (askdel==1)
            {
                if (turn == 0)
                {
                    strcpy(arr_acc[3*num-3], arr_acc[cla-1]);
                    strcpy(arr_usr[3*num-3], arr_usr[cla-1]);
                    strcpy(arr_pass[3*num-3], arr_pass[cla-1]);
                }
                else if (turn == 1)
                {
                    strcpy(arr_acc[3*num-2], arr_acc[cla-1]);
                    strcpy(arr_usr[3*num-2], arr_usr[cla-1]);
                    strcpy(arr_pass[3*num-2], arr_pass[cla-1]);
                }
                else if (turn == 2)
                {
                    strcpy(arr_acc[3*num-1], arr_acc[cla-1]);
                    strcpy(arr_usr[3*num-1], arr_usr[cla-1]);
                    strcpy(arr_pass[3*num-1], arr_pass[cla-1]);
                }
                cla--;
                goto print;
            }

            int jawab = askedit(xMax, yMax);

            if (jawab == 1)
            {
              //ERASE
                if (turn == 0)
                {
                    memset(arr_acc[3*num-3], 0, sizeof(arr_acc[3*num-3]));
                    memset(arr_usr[3*num-3], 0, sizeof(arr_usr[3*num-3]));
                    memset(arr_pass[3*num-3], 0, sizeof(arr_pass[3*num-3]));
                }
                else if (turn == 1)
                {
                    memset(arr_acc[3*num-2], 0, sizeof(arr_acc[3*num-2]));
                    memset(arr_usr[3*num-2], 0, sizeof(arr_usr[3*num-2]));
                    memset(arr_pass[3*num-2], 0, sizeof(arr_pass[3*num-2]));
                }
                else if (turn == 2)
                {
                    memset(arr_acc[3*num-1], 0, sizeof(arr_acc[3*num-1]));
                    memset(arr_usr[3*num-1], 0, sizeof(arr_usr[3*num-1]));
                    memset(arr_pass[3*num-1], 0, sizeof(arr_pass[3*num-1]));
                }
                strcpy(arr_acc[3*num-3+turn], acc); strcpy(arr_usr[3*num-3+turn], usr); strcpy(arr_pass[3*num-3+turn], pass);
            }

            else if (jawab == -1)
            {
                wclear(accountwin); wclear(userwin); wclear(passwin);
                wrefresh(accountwin); wrefresh(userwin); wrefresh(passwin);
                wclear(ghost_win);
                wrefresh(ghost_win);
                goto checkpoint;
            }
        goto print;
    }


    // USER SAVE
    if (strcmp(ans, save)==0)
    {
        fclose(file);
        sprintf(filepath, "%s\\%s\\%s.mya", cwd, dirname, filename);
        //Exporting File
        file = fopen(filepath, "r");
        FILE *temp = fopen("delete.tmp", "w");

        lup=0;
        //ENCRYPT STARTS
        while (1)
        {
            char str[64];
            strcpy(str, arr_usr[lup]);
            int sz = strlen(str);

            //ENCRYPT USERNAME
            for(i = 0; (i < sz && str[i] != '\0'); i++)
            {
                if (i<2)
                    str[i] = str[i] + 3;
                else if (i<4)
                    str[i] = str[i] + 5;
                else if (i<6)
                    str[i] = str[i] + 11;
                else if (i<8)
                    str[i] = str[i] - 7;
                else if (i<10)
                    str[i] = str[i] - 10;
                else if (i>=10)
                    str[i] = str[i] + 1 + i;
            }
            strcpy(arren_usr[lup], str);

            memset(str, 0, sizeof(str));
            strcpy(str, arr_pass[lup]);
            sz = strlen(str);

            //ENCRYPT PASS
            for(i = 0; (i < sz && str[i] != '\0'); i++)
            {
                if (i<2)
                    str[i] = str[i] + 3;
                else if (i<4)
                    str[i] = str[i] + 5;
                else if (i<6)
                    str[i] = str[i] + 11;
                else if (i<8)
                    str[i] = str[i] - 7;
                else if (i<10)
                    str[i] = str[i] - 10;
                else if (i>=10)
                    str[i] = str[i] + 1 + i;
            }
            strcpy(arren_pass[lup], str);

            memset(str, 0, sizeof(str));
            strcpy(str, arr_acc[lup]);
            sz = strlen(str);

            //ENCRYPT ACC
            for(i = 0; (i < sz && str[i] != '\0'); i++)
            {
                if (i<2)
                    str[i] = str[i] + 3;
                else if (i<4)
                    str[i] = str[i] + 5;
                else if (i<6)
                    str[i] = str[i] + 11;
                else if (i<8)
                    str[i] = str[i] - 7;
                else if (i<10)
                    str[i] = str[i] - 10;
                else if (i>=10)
                    str[i] = str[i] + 1 + i;
            }
            strcpy(arren_acc[lup], str);

            lup++;
            if(lup == cla)
                break;
        }

        //Print string to Text File
            fprintf(temp, "\n%s", security);
            fprintf(temp, "\n%s", secans);

         for (i = 0; i < cla; i++)
        {
            fprintf(temp, "\n%s", arren_acc[i]);
            fprintf(temp, "\n%s", arren_usr[i]);
            fprintf(temp, "\n%s", arren_pass[i]);
        }
        fclose(temp);
        fclose(file);

        remove(filepath);
        rename("delete.tmp", filepath);
        mvwprintw(inputwin, 1, 1, "File Saved: <%s>",filepath);

        top=newwin(3, xMax-10, 4, 5);
        wbkgd(top, COLOR_PAIR(3));
        mvwprintw(top, 1, 36, "Press Any Key to Redirect Back to Menu");
        refresh();
        wrefresh(top);
        wrefresh(inputwin);

        getch();
        clear();
        menu_utama(xMax, yMax);
    }

    if (strcmp(ans, add)==0)
    {
        char *string[]=
        {"Enter type of Account: ",
        "Enter a Username: ",
        "Enter a Password: "};
add :
        if (cla%3 == 0)
        {
            clear();

            //Watermark
            mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

            top = newwin(1, 14, 5, 5);
            mvwprintw(top, 0, 1, "Bank Manager");
            wbkgd(top, COLOR_PAIR(2));
            refresh();
            wrefresh(top);

            mvprintw(6, 5, "Available Command : ");

            c = newwin(1, 6, 6, 25);
            mvwprintw(c, 0, 1, "edit");
            wbkgd(c, COLOR_PAIR(2));
            refresh();
            wrefresh(c);

            c1 = newwin(1, 6, 6, 32);
            mvwprintw(c1, 0, 1, "goto");
            wbkgd(c1, COLOR_PAIR(2));
            refresh();
            wrefresh(c1);

            c2 = newwin(1, 6, 6, 39);
            mvwprintw(c2, 0, 1, "save");
            wbkgd(c2, COLOR_PAIR(2));
            refresh();
            wrefresh(c2);

            c3 = newwin(1, 5, 6, 46);
            mvwprintw(c3, 0, 1, "end");
            wbkgd(c3, COLOR_PAIR(2));
            refresh();
            wrefresh(c3);

            c4 = newwin(1, 5, 6, 52);
            mvwprintw(c4, 0, 1, "add");
            wbkgd(c4, COLOR_PAIR(2));
            refresh();
            wrefresh(c4);

            page++;
            num = page;
            lup=0;
            bankpage(xMax, yMax, page, page);
            editer(xMax, yMax, lup);
            accountwin = newwin(2, xMax-20, 8, 5);
            wbkgd(accountwin, COLOR_PAIR(1));
            refresh();

            userwin = newwin(2,xMax/2-10, 10, 5);
            wbkgd(userwin, COLOR_PAIR(5));
            refresh();

            passwin = newwin(2,xMax/2-10, 10, 55);
            wbkgd(passwin, COLOR_PAIR(9));
            refresh();

            wrefresh(accountwin); wrefresh(userwin); wrefresh(passwin);
            wclear(inputwin); mvwprintw(inputwin, 1, 1, string[0]); wgetstr(inputwin, acc); mvwprintw(accountwin, 0, xMax/2-10-(strlen(acc)/2), acc); wrefresh(accountwin);
            wclear(inputwin); mvwprintw(inputwin, 1, 1, string[1]); wgetstr(inputwin, usr); mvwprintw(userwin, 0, xMax/4-3-(strlen(usr)/2), usr); wrefresh(userwin);
            wclear(inputwin); mvwprintw(inputwin, 1, 1, string[2]); wgetstr(inputwin, pass); mvwprintw(passwin, 0, xMax/4-3-(strlen(pass)/2), pass); wrefresh(passwin);

            strcpy(arr_pass[3*num-3+lup], pass); strcpy(arr_usr[3*num-3+lup], usr); strcpy(arr_acc[3*num-3+lup], acc);
        }

        else
        {
            addlup++;
            if (addlup == 1)
                goto print;
            num = page;
            lup++;
            editer(xMax, yMax, lup);
            accountwin = newwin(2, xMax-20, 8+5*lup, 5);
            wbkgd(accountwin, COLOR_PAIR(1));
            refresh();

            userwin = newwin(2,xMax/2-10, 10+5*lup, 5);
            wbkgd(userwin, COLOR_PAIR(5));
            refresh();

            passwin = newwin(2,xMax/2-10, 10+5*lup, 55);
            wbkgd(passwin, COLOR_PAIR(9));
            refresh();

            wrefresh(accountwin); wrefresh(userwin); wrefresh(passwin);

            wclear(inputwin); mvwprintw(inputwin, 1, 1, string[0]); wgetstr(inputwin, acc);
            mvwprintw(accountwin, 0, xMax/2-10-(strlen(acc)/2), acc); wrefresh(accountwin);

            wclear(inputwin); mvwprintw(inputwin, 1, 1, string[1]); wgetstr(inputwin, usr);
            mvwprintw(userwin, 0, xMax/4-3-(strlen(usr)/2), usr); wrefresh(userwin);

            wclear(inputwin); mvwprintw(inputwin, 1, 1, string[2]); wgetstr(inputwin, pass);
            mvwprintw(passwin, 0, xMax/4-3-(strlen(pass)/2), pass); wrefresh(passwin);

            strcpy(arr_pass[3*num-3+lup], pass); strcpy(arr_usr[3*num-3+lup], usr); strcpy(arr_acc[3*num-3+lup], acc);
        }
        cla++;
        addlup=0;
        goto getstr;
    }

    else
    {
        wclear(inputwin);
        goto getstr;
    }


}

int editer(int xMax, int yMax, int lup)
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);

    WINDOW *win;

    win = newwin(4, 8, 8+5*lup, xMax-13);
    mvwprintw(win, 1, 2, "Edit");
    wbkgd(win, COLOR_PAIR(2));
    refresh();
    wrefresh(win);
}

int bankpage(int xMax, int yMax, int page, int num)
{
      start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);

    WINDOW *indiwin;
    WINDOW *win2;
    WINDOW *win3;
    WINDOW *win4;
    WINDOW *win5;
    WINDOW *win6;
    WINDOW *win7;
    WINDOW *win8;
    WINDOW *win9;
    WINDOW *win10;
    WINDOW *win11;
    WINDOW *win12;
    WINDOW *win13;
    WINDOW *win14;
    WINDOW *win15;
    WINDOW *win16;


    if (page>0)
    {
    indiwin = newwin(1, 5, yMax-7, 5);
    mvwprintw(indiwin, 0, 2, "P");
    wbkgd(indiwin, COLOR_PAIR(2));
    refresh();
    wrefresh(indiwin);

    win2 = newwin(1, 6, yMax-7, 11);
    mvwprintw(win2, 0, 2, "1");

    if (num==1)
        wbkgd(win2, COLOR_PAIR(1));
    else
        wbkgd(win2, COLOR_PAIR(2));

        refresh();
        wrefresh(win2);

    }

    if (page>1)
    {
    win3 = newwin(1, 6, yMax-7, 18);
    mvwprintw(win3, 0, 2, "2");

    if (num==2)
        wbkgd(win3, COLOR_PAIR(1));
    else
        wbkgd(win3, COLOR_PAIR(2));

    refresh();
    wrefresh(win3);
    }

    if (page>2)
    {
    win4 = newwin(1, 6, yMax-7, 25);
    mvwprintw(win4, 0, 2, "3");

    if (num==3)
        wbkgd(win4, COLOR_PAIR(1));
    else
        wbkgd(win4, COLOR_PAIR(2));

    refresh();
    wrefresh(win4);
    }

    if (page>3)
    {
    win5 = newwin(1, 6, yMax-7, 32);
    mvwprintw(win5, 0, 2, "4");

    if (num==4)
        wbkgd(win5, COLOR_PAIR(1));
    else
        wbkgd(win5, COLOR_PAIR(2));

    refresh();
    wrefresh(win5);
    }

    if (page>4)
    {
    win6 = newwin(1, 6, yMax-7, 39);
    mvwprintw(win6, 0, 2, "5");

    if (num==5)
        wbkgd(win6, COLOR_PAIR(1));
    else
        wbkgd(win6, COLOR_PAIR(2));

    refresh();
    wrefresh(win6);
    }

    if (page>5)
    {
    win7 = newwin(1, 6, yMax-7, 46);
    mvwprintw(win7, 0, 2, "6");

    if (num==6)
        wbkgd(win7, COLOR_PAIR(1));
    else
        wbkgd(win7, COLOR_PAIR(2));

    refresh();
    wrefresh(win7);
    }

    if (page>6)
    {
    win8 = newwin(1, 6, yMax-7, 53);
    mvwprintw(win8, 0, 2, "7");

    if (num==7)
        wbkgd(win8, COLOR_PAIR(1));
    else
        wbkgd(win8, COLOR_PAIR(2));

    refresh();
    wrefresh(win8);
    }

    if (page>7)
    {
    win9 = newwin(1, 6, yMax-7, 60);
    mvwprintw(win9, 0, 2, "8");

    if (num==8)
        wbkgd(win9, COLOR_PAIR(1));
    else
        wbkgd(win9, COLOR_PAIR(2));

    refresh();
    wrefresh(win9);
    }

    if (page>8)
    {
    win10 = newwin(1, 6, yMax-7, 67);
    mvwprintw(win10, 0, 2, "9");

    if (num==9)
        wbkgd(win10, COLOR_PAIR(1));
    else
        wbkgd(win10, COLOR_PAIR(2));

    refresh();
    wrefresh(win10);
    }

    if (page>9)
    {
    win11 = newwin(1, 6, yMax-7, 74);
    mvwprintw(win11, 0, 2, "10");

    if (num==10)
        wbkgd(win11, COLOR_PAIR(1));
    else
        wbkgd(win11, COLOR_PAIR(2));

    refresh();
    wrefresh(win11);
    }

    if (page>10)
    {
    win12 = newwin(1, 6, yMax-7, 81);
    mvwprintw(win12, 0, 2, "11");

    if (num==11)
        wbkgd(win12, COLOR_PAIR(1));
    else
        wbkgd(win12, COLOR_PAIR(2));

    refresh();
    wrefresh(win12);
    }

    if (page>11)
    {
    win13 = newwin(1, 6, yMax-7, 88);
    mvwprintw(win13, 0, 2, "12");

    if (num==12)
        wbkgd(win13, COLOR_PAIR(1));
    else
        wbkgd(win13, COLOR_PAIR(2));

    refresh();
    wrefresh(win13);
    }

    if (page>12)
    {
    win14 = newwin(1, 6, yMax-7, 95);
    mvwprintw(win14, 0, 2, "13");

    if (num==13)
        wbkgd(win14, COLOR_PAIR(1));
    else
        wbkgd(win14, COLOR_PAIR(2));

    refresh();
    wrefresh(win14);
    }

    if (page>13)
    {
    win15 = newwin(1, 6, yMax-7, 102);
    mvwprintw(win15, 0, 2, "14");

    if (num==14)
        wbkgd(win15, COLOR_PAIR(1));
    else
        wbkgd(win15, COLOR_PAIR(2));

    refresh();
    wrefresh(win15);
    }

    if (page>14)
    {
    win16 = newwin(1, 6, yMax-7, 109);
    mvwprintw(win16, 0, 2, "15");

    if (num==15)
        wbkgd(win16, COLOR_PAIR(1));
    else
        wbkgd(win16, COLOR_PAIR(2));

    refresh();
    wrefresh(win16);
    }
}

int editmg(int xMax, int yMax, int num, int cla)
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);

    WINDOW *win;
    WINDOW *win1;
    WINDOW *win2;
    WINDOW *in;

    in = newwin(1, 1, 0, -1);
    refresh();
    int n;
    int x = cla - 3 * num + 3;

        win = newwin(4, 8, 8, xMax-13);
        mvwprintw(win, 1, 2, "Edit");
        refresh();

        win1 = newwin(4, 8, 8+5*1, xMax-13);
        mvwprintw(win1, 1, 2, "Edit");
        refresh();

        win2 = newwin(4, 8, 8+5*2, xMax-13);
        mvwprintw(win2, 1, 2, "Edit");
        refresh();

    keypad(in, true);

    int choice;
    int highlight=0;

    while(1)
    {
            if(highlight==0)
            {
                wbkgd(win2, COLOR_PAIR(2));
                wbkgd(win1, COLOR_PAIR(2));
                wbkgd(win, COLOR_PAIR(1));
            }
            else if(highlight==1)
            {
                wbkgd(win, COLOR_PAIR(2));
                wbkgd(win2, COLOR_PAIR(2));
                wbkgd(win1, COLOR_PAIR(1));
            }
            else if(highlight==2)
            {
                wbkgd(win1, COLOR_PAIR(2));
                wbkgd(win, COLOR_PAIR(2));
                wbkgd(win2, COLOR_PAIR(1));
            }

            if (x>0)
            {
                n=1;
                wrefresh(win);
                if (x>1)
                {
                    n=2;
                    wrefresh(win1);
                    if (x>2)
                    {
                        n=3;
                        wrefresh(win2);
                    }
                }
            }

        choice = wgetch(in);

        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == n)
                    highlight = n-1;
                    break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;
    }
    if (highlight == 0)
    {
        wclear(win);
        return 0;
    }
    if (highlight == 1)
    {
        wclear(win1);
        return 1;
    }
    if (highlight == 2)
    {
        wclear(win2);
        return 2;
    }
}

int askedit(int xMax, int yMax)
{
        start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);

    //Looping Program
    //Window Pop-Up pemberitahuan
        WINDOW * ask_win = newwin(5, 40, 3, 75);
        wbkgd(ask_win, COLOR_PAIR(2));
        refresh();
        mvwprintw(ask_win, 1, 5, "Apply Changes to the Account?");
        wrefresh(ask_win);

    //Window Pop-Up waiting request

        //Fungsi untuk mengambil input arrow key
    keypad(ask_win, true);

    char *choices[]={"Yes", "No"};
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight = 0;

    while(1)
    {
        for(int i = 0; i < n; i++)
        {
            if(i==highlight)
                wattron(ask_win, A_REVERSE);
                mvwprintw(ask_win, 3, 15+6*i, choices[i]);
                wattroff(ask_win, A_REVERSE);
        }
        choice = wgetch(ask_win);

        switch(choice)
        {
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == n)
                    highlight = n-1;
                break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;
    }

    if(highlight == 0)
    {
        wclear(ask_win);
        return 1;
    }

    else if(highlight == n-1)
    {
        return -1;
    }
}

int delcon(int xMax, int yMax)
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_RED);

    WINDOW *ask_win;

    //Buat window baru khusus untuk input
    ask_win = newwin(5, 40, 3, 75);
    wbkgd(ask_win, COLOR_PAIR(7));
    refresh();

     mvwprintw(ask_win, 1, 3, "Sure want to Delete this Account?");
        wrefresh(ask_win);

    //Window Pop-Up waiting request

        //Fungsi untuk mengambil input arrow key
    keypad(ask_win, true);

    char *choices[]={"Yes", "No"};
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight = 0;

    while(1)
    {
        for(int i = 0; i < n; i++)
        {
            if(i==highlight)
                wattron(ask_win, A_REVERSE);
                mvwprintw(ask_win, 3, 15+6*i, choices[i]);
                wattroff(ask_win, A_REVERSE);
        }
        choice = wgetch(ask_win);

        switch(choice)
        {
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == n)
                    highlight = n-1;
                break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;
    }

    if(highlight == 0)
    {
        wclear(ask_win);
        return 1;
    }

    else if(highlight == n-1)
    {
        return 0;
    }

}

