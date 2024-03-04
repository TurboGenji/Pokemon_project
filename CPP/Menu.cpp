#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <locale>
#include "unite.h"
using namespace std;

void gotoxy(int x, int y);
int showoptions(int x, int y, int);
void showabout();

void gotoxy(int x, int y)
{   //Перейти по координатам x,y
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void info() {
	system("cls");
	gotoxy(2, 2);
	cout << "On map controls\n";
	cout << "W - move up\nS - move down\nA - move left\nD - move left\n";
	cout << "Tab - open inventory\nBy clicking Q in inventory you will\n open your pokemon inventory\n";
	gotoxy(2, 11);
	cout << "In combat and menu controls\n";
	cout << "A, D - choose horizontally\nW, S - choose vertically\n";
	cout << "X - choose point\nEsc - cancel choosing\nH - get description of item or attack";
	gotoxy(50, 2);
	cout << "Short info about game mechanics";
	gotoxy(40, 4);
	cout << "Pokemons are of 4 types: Electricity, Fire, Water, Earth";
	gotoxy(40, 6);
	cout << "Some types has advantages over another and dissadvatages against others";
	gotoxy(40, 8);
	cout << "Some attacks might have different type of damage from pokemon's type";
	gotoxy(40, 10);
	cout << "You will engage into fight by walking over bushes (#)";
	gotoxy(40, 12);
	cout << "After fight you will gain money to spend in shop";
	_getch();
}




int showoptions(int x, int y, int opt)
{
	int equip = opt / 10, set = 0, sound = opt % 10;
	char input = '0';
	while (true) {
		system("cls");
		gotoxy(3, 2);
		cout << "Starting equipment";
		gotoxy(1, 3);
		for (int i = 0; i < 20; i++) {
			cout << ' ';
		}
		gotoxy(1, 3);
		switch (equip) {
		case 1: {cout << "1. Water newbie"; break; }
		case 2: {cout << "2. Fire newbie"; break;
		}
		case 3: {cout << "3. Earth newbie"; break; }
		case 4: {cout << "4. Electric newbie"; break; }
		}
		gotoxy(3, 5);
		cout << "Controls and about";
		gotoxy(3, 8);
		cout << "Exit";
		gotoxy(1, (2 + set * 3));
		cout << '>';
		input = _getch();
		input = tolower(input);
		switch (input) {
		case 'w': {
			gotoxy(1, (2 + set * 3));
			cout << ' ';
			set--;
			if (set < 0) set = 2;
			break;
		}
		case 's': {
			gotoxy(1, (2 + set * 3));
			cout << ' ';
			set++;
			if (set > 2) set = 0;
			break;
		}
		case 'd': {
			switch (set) {
			case 0: {
				equip++;
				if (equip > 4) equip = 1;
				break;
			}
			}
			break;

		}
		case 'a': {
			switch (set) {
			case 0: {
				equip--;
				if (equip < 1) equip = 4;
				break;
			}

			}
			break;
		}
		case 'x': {
			switch (set) {
			case 1: {
				info();
				break;
			}
			case 2: {
				return equip;
			}
			}
			break;
		}
		}
	}

}

void showabout()
{
	system("CLS");

	gotoxy(8, 8);
	printf("Pokemon Demo\n");
	gotoxy(8, 10);
	printf("Goal: recreate basic mechanics from Pokemon game\n");
	gotoxy(8, 12);
	printf("Made by 5 students, who wish to stay anonymus\n");

	_getch();
}




int showmenu(int x, int y)
{
	int options = 1;
	int choic = 2;
	// int ch = 2;
	char ch_1;
	system("CLS");

	while (true)
	{
		system("cls");
		//Отображаем пункты меню
		gotoxy(x, y);
		printf("GAME MENU");

		gotoxy(x, y + 2);
		printf("1. Start GAME");  //cout << "1. Start GAME";  

		gotoxy(x, y + 4);
		printf("2. For game");

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
		gotoxy(x - 2, y + choic);
		printf(">");

		ch_1 = _getch();        //получаем нажатую клавишу
		//ch_1 = toupper(ch_1); //преобразовываем в заглавные

		//выбор пунктов меню кнопками цифр 1-4
		switch (ch_1)
		{
		case '1':  choic = 2; break;
		case '2':  choic = 4; break;
		case '3':  choic = 6; break;
		case '4':  choic = 8; break;
		}

		/*Коды клавиш "стрелки"    0x4B: Left, 0x48: Up, 0x4D: Right, 0x50: Down */
		if ((tolower(ch_1) == 's') && (choic < 8))    //была кнопка 'S', теперь стрелка вниз
		{
			choic = choic + 2; //следующий пункт меню
		}
		else if ((tolower(ch_1) == 'w') && (choic > 2)) //была кнопка 'W', теперь стрелка вверх
		{
			choic = choic - 2; //предыдующий пункт меню
		}

		if ((tolower(ch_1) == 'x')) //при нажатии Enter выполнить выбранный пункт меню
		{
			switch (choic)
			{
			case 2: map(options); break;     //запуск игры, значение 200 для выхода из цикла
			case 4: options = showoptions(10, 10, options); system("CLS"); break;     //вызов меню настройки
			case 6: showabout(); system("CLS"); break;//вызов окна о программе
			case 8: system("cls"); gotoxy(8, 4); cout << "Goodbye!"; gotoxy(1, 8); return 0; //вызов окна выход, значение 100 для выхода из цикла
			}
		}
	};

	switch (choic)
	{
	case 200: return options; break;    //запуск игры - функция вернет значение 1
	case 100: return 0; break;    //выход  - функция вернет значение 2
	}
};


int main()
{
	CONSOLE_CURSOR_INFO curs = { 0 };
	curs.dwSize = sizeof(curs);
	curs.bVisible = FALSE;
	::SetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &curs);
	int menustart = 0;

	/* Отобразить меню */
	menustart = showmenu(10, 10);  // Функция возвращает значения:
	//1 -запуск игры
	return 0;
}