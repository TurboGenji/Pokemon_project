#include <conio.h>
#include <windows.h>
#include <iostream>

void setcolor(int text, int background);
void gotoxy(int x, int y);
void showstart();
void showoptions(int x, int y);
void showabout();
void showexit();

int menucolor = 15; //Первоначальный белый цвет букв меню

void setcolor(int text, int background) //цвет шрифта, фона
{
    /* Чёрный - 0, Синий - 1, Зелёный - 2, Голубой - 3, Красный - 4, Пурпурный - 5,
   Коричневый - 6, Светло - серый - 7, Тёмно - серый - 8, Светло - синий - 9,
   Светло - зелёный - 10, Светло - голубой - 11, Светло - красный - 12,
    Светло - пурпурный - 13, Жёлтый - 14, Белый - 15 */

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void gotoxy(int x, int y)
{   //Перейти по координатам x,y
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void showstart()
{
    int key = 0;
    system("CLS");
    setcolor(10, 0); //цвет текста 10- светло зеленый

    while (key == 0)
    {
        gotoxy(8, 10);
        printf("Press any key to start the game");

        key = _getch();
    }
    setcolor(15, 0); //вернем цвет текста белый на черном фоне
}


void showoptions(int x, int y)
{
    setcolor(11, 0);
    /* Чёрный - 0, Синий - 1, Зелёный - 2, Голубой - 3, Красный - 4, Пурпурный - 5,
       Коричневый - 6, Светло - серый - 7, Тёмно - серый - 8, Светло - синий - 9,
       Светло - зелёный - 10, Светло - голубой - 11, Светло - красный - 12,
        Светло - пурпурный - 13, Жёлтый - 14, Белый - 15
      */
    system("CLS");
    //gotoxy(x, y);
    printf("\n\n\nEnter menu color (1-15):  \n\n");
    printf("0-Black, \n1-Blue, \n2-Green, \n3-Blue, \n4-Red, \n5-Purple, \n6-Brown, \n7-Light Grey, \n8-Dark Grey, \n9-Light Blue,\n10-Light Green, \n11-Light Blue, \n12-Light Red, \n13-Light Purple, \n14-Yellow, \n15-White\n\n");
    std::cin >> menucolor;

    setcolor(15, 0); //вернем цвет текста белый на черном фоне
}

void showabout()
{
    int key = 0;
    system("CLS");
    setcolor(10, 0); //цвет текста 10- светло зеленый

    while (key == 0)
    {
        gotoxy(8, 8);
        printf("Hello.\n");
        gotoxy(8, 10);
        printf("This very interesting game was developed by a group of students.\n");
        gotoxy(8, 12);
        printf("I wish you a fun time.\n");

        key = _getch();
    }
    setcolor(15, 0); //вернем цвет текста белый на черном фоне
}

void showexit()
{
    system("CLS");
    gotoxy(8, 8);
    setcolor(9, 0); //светло-синие буквы
    printf("Goodbye!");
    _getch();
};


int showmenu(int x, int y)
{
    int choice = 2;
    // int ch = 2;
    char ch_1;
    system("CLS");

    while ((choice != (100)) && (choice != (200)))
    {
        setcolor(menucolor, 0);//15
        //Отображаем пункты меню
        gotoxy(x, y);
        printf("GAME MENU");

        gotoxy(x, y + 2);
        printf("1. Start GAME");  //std::cout << "1. Start GAME";  

        gotoxy(x, y + 4);
        printf("2. Options");

        gotoxy(x, y + 6);
        printf("3. About");

        gotoxy(x, y + 8);
        printf("4. EXIT");

        //Стираем указатель пункта меню
        gotoxy(x - 2, y + 2);
        printf(" ");
        gotoxy(x - 2, y + 4);
        printf(" ");
        gotoxy(x - 2, y + 6);
        printf(" ");
        gotoxy(x - 2, y + 8);
        printf(" ");

        //Рисуем указатель пункта меню
        gotoxy(x - 2, y + choice);
        printf(">");

        ch_1 = _getch();        //получаем нажатую клавишу
        //ch_1 = toupper(ch_1); //преобразовываем в заглавные

        //выбор пунктов меню кнопками цифр 1-4
        switch (ch_1)
        {
        case '1':  choice = 2; break;
        case '2':  choice = 4; break;
        case '3':  choice = 6; break;
        case '4':  choice = 8; break;
        }

        /*Коды клавиш "стрелки"    0x4B: Left, 0x48: Up, 0x4D: Right, 0x50: Down */
        if ((ch_1 == 0x50) && (choice < 8))    //была кнопка 'S', теперь стрелка вниз
        {
            choice = choice + 2; //следующий пункт меню
        }
        else if ((ch_1 == 0x48) && (choice > 2)) //была кнопка 'W', теперь стрелка вверх
        {
            choice = choice - 2; //предыдующий пункт меню
        }

        if ((ch_1 == '\r')) //при нажатии Enter выполнить выбранный пункт меню
        {
            switch (choice)
            {
            case 2: showstart(); choice = 200; break;     //запуск игры, значение 200 для выхода из цикла
            case 4: showoptions(10, 10); system("CLS"); break;     //вызов меню настройки
            case 6: showabout(); system("CLS"); break;//вызов окна о программе
            case 8: showexit();  choice = 100; break; //вызов окна выход, значение 100 для выхода из цикла
            }
        }
    };

    switch (choice)
    {
    case 200: return 1; break;    //запуск игры - функция вернет значение 1
    case 100: return 0; break;    //выход  - функция вернет значение 2
    }
};


int main()
{
    int menustart = 0;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    system("CLS");

    /* Отобразить меню */
    menustart = showmenu(10, 10);  // Функция возвращает значения:
                                    //1 -запуск игры

    if (menustart == 1)
    {
        //Здесь должен быть запуск игры...
    }



    return 0;
}
