#include <conio.h>
#include <windows.h>
#include <iostream>

void setcolor(int text, int background);
void gotoxy(int x, int y);
void showstart();
void showoptions(int x, int y);
void showabout();
void showexit();

int menucolor = 15; //�������������� ����� ���� ���� ����

void setcolor(int text, int background) //���� ������, ����
{
    /* ׸���� - 0, ����� - 1, ������ - 2, ������� - 3, ������� - 4, ��������� - 5,
   ���������� - 6, ������ - ����� - 7, Ҹ��� - ����� - 8, ������ - ����� - 9,
   ������ - ������ - 10, ������ - ������� - 11, ������ - ������� - 12,
    ������ - ��������� - 13, Ƹ���� - 14, ����� - 15 */

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void gotoxy(int x, int y)
{   //������� �� ����������� x,y
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void showstart()
{
    int key = 0;
    system("CLS");
    setcolor(10, 0); //���� ������ 10- ������ �������

    while (key == 0)
    {
        gotoxy(8, 10);
        printf("Press any key to start the game");

        key = _getch();
    }
    setcolor(15, 0); //������ ���� ������ ����� �� ������ ����
}


void showoptions(int x, int y)
{
    setcolor(11, 0);
    /* ׸���� - 0, ����� - 1, ������ - 2, ������� - 3, ������� - 4, ��������� - 5,
       ���������� - 6, ������ - ����� - 7, Ҹ��� - ����� - 8, ������ - ����� - 9,
       ������ - ������ - 10, ������ - ������� - 11, ������ - ������� - 12,
        ������ - ��������� - 13, Ƹ���� - 14, ����� - 15
      */
    system("CLS");
    //gotoxy(x, y);
    printf("\n\n\nEnter menu color (1-15):  \n\n");
    printf("0-Black, \n1-Blue, \n2-Green, \n3-Blue, \n4-Red, \n5-Purple, \n6-Brown, \n7-Light Grey, \n8-Dark Grey, \n9-Light Blue,\n10-Light Green, \n11-Light Blue, \n12-Light Red, \n13-Light Purple, \n14-Yellow, \n15-White\n\n");
    std::cin >> menucolor;

    setcolor(15, 0); //������ ���� ������ ����� �� ������ ����
}

void showabout()
{
    int key = 0;
    system("CLS");
    setcolor(10, 0); //���� ������ 10- ������ �������

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
    setcolor(15, 0); //������ ���� ������ ����� �� ������ ����
}

void showexit()
{
    system("CLS");
    gotoxy(8, 8);
    setcolor(9, 0); //������-����� �����
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
        //���������� ������ ����
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

        //������� ��������� ������ ����
        gotoxy(x - 2, y + 2);
        printf(" ");
        gotoxy(x - 2, y + 4);
        printf(" ");
        gotoxy(x - 2, y + 6);
        printf(" ");
        gotoxy(x - 2, y + 8);
        printf(" ");

        //������ ��������� ������ ����
        gotoxy(x - 2, y + choice);
        printf(">");

        ch_1 = _getch();        //�������� ������� �������
        //ch_1 = toupper(ch_1); //��������������� � ���������

        //����� ������� ���� �������� ���� 1-4
        switch (ch_1)
        {
        case '1':  choice = 2; break;
        case '2':  choice = 4; break;
        case '3':  choice = 6; break;
        case '4':  choice = 8; break;
        }

        /*���� ������ "�������"    0x4B: Left, 0x48: Up, 0x4D: Right, 0x50: Down */
        if ((ch_1 == 0x50) && (choice < 8))    //���� ������ 'S', ������ ������� ����
        {
            choice = choice + 2; //��������� ����� ����
        }
        else if ((ch_1 == 0x48) && (choice > 2)) //���� ������ 'W', ������ ������� �����
        {
            choice = choice - 2; //����������� ����� ����
        }

        if ((ch_1 == '\r')) //��� ������� Enter ��������� ��������� ����� ����
        {
            switch (choice)
            {
            case 2: showstart(); choice = 200; break;     //������ ����, �������� 200 ��� ������ �� �����
            case 4: showoptions(10, 10); system("CLS"); break;     //����� ���� ���������
            case 6: showabout(); system("CLS"); break;//����� ���� � ���������
            case 8: showexit();  choice = 100; break; //����� ���� �����, �������� 100 ��� ������ �� �����
            }
        }
    };

    switch (choice)
    {
    case 200: return 1; break;    //������ ���� - ������� ������ �������� 1
    case 100: return 0; break;    //�����  - ������� ������ �������� 2
    }
};


int main()
{
    int menustart = 0;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    system("CLS");

    /* ���������� ���� */
    menustart = showmenu(10, 10);  // ������� ���������� ��������:
                                    //1 -������ ����

    if (menustart == 1)
    {
        //����� ������ ���� ������ ����...
    }



    return 0;
}
