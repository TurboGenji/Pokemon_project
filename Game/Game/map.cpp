#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <locale>
using namespace std;

void future() { //использовать для всего, что я говорю "Потом будет вставляться мной или кем-либо другим"
	cout << "Undone*";
	_getch();
}

const int n = 20, k = 42;
char bigmap[n][k];
char character = 'O';
void main()
{
	srand(time(NULL));
	int characterLocY = 10;
	int characterLocX = 21;
	char bush = '#';
	char block = char(219);
	char space = char(32);
	int count = 4;
	int bushX = 5;
	int bushY = 3;

	while (true)
	{
		int chois = 1;
		bool choose = false;
		bool transition = false;
		bool purchasing = false;
		int x = rand() % 100;
		int c = rand() % 5;
		if ((characterLocX >= 6 && characterLocX <= 10) && (characterLocY >= 4 && characterLocY <= 7)) //Приоритет отдаётся электрическому покемону
		{

			if (x <= 20 && x >= 0)
			{

				if (c == 0)
				{
					system("cls");
					cout << "Fire pokemon has appeared\n";
					_getch();

				}
				else if (c == 1)
				{
					system("cls");
					cout << "Water pokemon has appeared\n";
					_getch();

				}
				else if (c == 4)
				{
					system("cls");
					cout << "Earth pokemon has appeared\n";
					_getch();

				}
				else if (c == 2 || c == 3)
				{
					system("cls");
					cout << "Lightning pokemon has appeared\n";
					_getch();
				}

			}

			system("cls");
		}
		if ((characterLocX >= 6 && characterLocX <= 10) && (characterLocY >= 13 && characterLocY <= 17)) //Приоритет отдаётся огненному покемону
		{


			if (x <= 20 && x >= 0)
			{


				if (c == 0)
				{
					system("cls");
					cout << "Water pokemon has appeared\n";
					_getch();

				}
				else if (c == 1)
				{
					system("cls");
					cout << "Earth pokemon has appeared\n";
					_getch();

				}
				else if (c == 4)
				{
					system("cls");
					cout << "Lightning pokemon has appeared\n";
					_getch();

				}
				else if (c == 2 || c == 3)
				{
					system("cls");
					cout << "Fire pokemon has appeared\n";
					_getch();
				}

			}

			system("cls");
		}
		if ((characterLocX >= 30 && characterLocX <= 35) && (characterLocY >= 13 && characterLocY <= 17)) //Приоритет отдаётся водному покемону
		{
			if (x <= 20 && x >= 0)
			{

				if (c == 0)
				{
					system("cls");
					cout << "Earth pokemon has appeared\n";
					_getch();

				}
				else if (c == 1)
				{
					system("cls");
					cout << "Lightning pokemon has appeared\n";
					_getch();

				}
				else if (c == 4)
				{
					system("cls");
					cout << "Fire pokemon has appeared\n";
					_getch();

				}
				else if (c == 2 || c == 3)
				{
					system("cls");
					cout << "Water pokemon has appeared\n";
					_getch();
				}

			}

			system("cls");
		}
		if ((characterLocX >= 30 && characterLocX <= 35) && (characterLocY >= 4 && characterLocY <= 7)) //Приоритет отдаётся земляному покемону
		{
			if (x <= 20 && x >= 0)
			{

				if (c == 0)
				{
					system("cls");
					cout << "Fire pokemon has appeared\n";
					_getch();

				}
				else if (c == 1)
				{
					system("cls");
					cout << "Water pokemon has appeared\n";
					_getch();

				}
				else if (c == 4)
				{
					system("cls");
					cout << "Lightning pokemon has appeared\n";
					_getch();

				}
				else if (c == 2 || c == 3)
				{
					system("cls");
					cout << "Earth pokemon has appeared\n";
					_getch();
				}

			}

			system("cls");
		}



		if (characterLocY == 2 && ((characterLocX == 18 || characterLocX == 19 || characterLocX == 20 || characterLocX == 21 || characterLocX == 22)))
		{
			char hello[] = "Welcome to Jumshut's shop!\n";
			char would[] = "What would you like?\n";
			for (int i = 0; hello[i - 1] != '\n'; i++) {
				cout << hello[i];
				Sleep(20);
			}
			for (int i = 0; would[i - 1]; i++) {
				cout << would[i];
				Sleep(20);
			}
			future();
			characterLocY++;

		}
		system("cls");
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < k; j++)
			{
				bigmap[i][0] = bigmap[i][1] = bigmap[i][k - 1] = bigmap[i][k - 2] = bigmap[0][j] = bigmap[n - 1][j] = block;
				bigmap[i][j + 1] = space;
				if (i == 2 && ((j == 18) || (j == 19) || (j == 20) || (j == 21) || (j == 22)))
					bigmap[i][j] = block;
			}
		}

		char* adress;
		adress = &bush;
		for (int bushY1 = bushY + 4; bushY1 > bushY; bushY1--) //Куст сверху слева
		{
			for (int bushX1 = bushX + 5; bushX1 > bushX; bushX1--)
			{
				bigmap[bushY1][bushX1] = bush;

			}

		}

		for (int bushY1 = 4 * bushY + 4; bushY1 > 4 * bushY; bushY1--)	//Куст снизу слева
		{
			for (int bushX1 = bushX + 5; bushX1 > bushX; bushX1--)
			{
				bigmap[bushY1][bushX1] = bush;

			}
		}
		for (int bushY1 = n - 7; bushY1 < n - 3; bushY1++)	//Куст спарва снизу
		{
			for (int bushX1 = k - 11; bushX1 < k - 6; bushX1++)
			{
				bigmap[bushY1][bushX1] = bush;


			}
		}
		for (int bushY1 = n - 16; bushY1 < n - 12; bushY1++)	 //Куст сверху справа
		{
			for (int bushX1 = k - 11; bushX1 < k - 6; bushX1++)
			{
				bigmap[bushY1][bushX1] = bush;

			}

		}
		bigmap[characterLocY][characterLocX] = character;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < k; j++)
			{
				cout << bigmap[i][j];
			}
			cout << endl;
		}

		while (transition == false)
		{
			char keyboard = _getch();

			switch (keyboard) {
			case 'w':
			{
				characterLocY--;
				if (characterLocY == 0)
					characterLocY = 1;
				transition = true;
				break;
			}
			case 's':
			{
				characterLocY++;
				if (characterLocY == 19)
					characterLocY = 18;
				transition = true;
				break;
			}
			case 'a':
			{
				characterLocX--;

				if (characterLocX == 1 || characterLocX == 0)
					characterLocX = 2;
				transition = true;
				break;
			}
			case 'd':
			{
				characterLocX++;
				if (characterLocX == 40 || characterLocX == 41)
					characterLocX = 39;
				transition = true;

				break;
			}
			case 9: {
				future();
				break;
			}
			case 27:
			{
				exit(0);
			}
			}
		}

		system("cls");
	}
}