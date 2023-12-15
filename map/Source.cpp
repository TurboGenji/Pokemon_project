#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>


const int n=20, k = 42;
char bigmap[n][k];
char character = 'O';
using namespace std;
void main()
{
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
		int x = rand() % 40;
		int c = rand() & 50;
		if ((characterLocX >= 6 && characterLocX <= 10) && (characterLocY >= 4 && characterLocY <= 7)) //Приоритет отдаётся электрическому покемону
		{

			if (x <= 20 && x >= 0)
			{

				if (c >= 0 && c <= 10)
				{
					system("cls");
					cout << "Fire pokemon has appeared\n";
					system("PAUSE");

				}
				else if (c >= 11 && c <= 20)
				{
					system("cls");
					cout << "Water pokemon has appeared\n";
					system("PAUSE");

				}
				else if (c >= 21 && c <= 30)
				{
					system("cls");
					cout << "Earth pokemon has appeared\n";
					system("PAUSE");

				}
				else if (c >= 31 && c <= 50)
				{
					system("cls");
					cout << "Lightning pokemon has appeared\n";
					system("PAUSE");
				}

			}

			system("cls");
		}
		if ((characterLocX >= 6 && characterLocX <= 10) && (characterLocY >= 13 && characterLocY <= 17)) //Приоритет отдаётся огненному покемону
		{


			if (x <= 20 && x >= 0)
			{


				if (c >= 0 && c <= 10)
				{
					system("cls");
					cout << "Water pokemon has appeared\n";
					system("PAUSE");

				}
				else if (c >= 11 && c <= 20)
				{
					system("cls");
					cout << "Earth pokemon has appeared\n";
					system("PAUSE");

				}
				else if (c >= 21 && c <= 30)
				{
					system("cls");
					cout << "Lightning pokemon has appeared\n";
					system("PAUSE");

				}
				else if (c >= 7==31 && c <= 50)
				{
					system("cls");
					cout << "Fire pokemon has appeared\n";
					system("PAUSE");
				}

			}

			system("cls");
		}
		if ((characterLocX >= 30 && characterLocX <= 35) && (characterLocY >= 13 && characterLocY <= 17)) //Приоритет отдаётся водному покемону
		{
			if (x <= 20 && x >= 0)
			{

				if (c >= 0 && c <= 10)
				{
					system("cls");
					cout << "Earth pokemon has appeared\n";
					system("PAUSE");

				}
				else if (c >=11 && c <= 20)
				{
					system("cls");
					cout << "Lightning pokemon has appeared\n";
					system("PAUSE");

				}
				else if (c >= 21 && c <= 30)
				{
					system("cls");
					cout << "Fire pokemon has appeared\n";
					system("PAUSE");

				}
				else if (c >= 31 && c <= 50)
				{
					system("cls");
					cout << "Water pokemon has appeared\n";
					system("PAUSE");
				}

			}

			system("cls");
		}
		if ((characterLocX >= 30 && characterLocX <= 35) && (characterLocY >= 4 && characterLocY <= 7)) //Приоритет отдаётся земляному покемону
		{
			if (x <= 20 && x >= 0)
			{

				if (c >= 0 && c <= 10)
				{
					system("cls");
					cout << "Fire pokemon has appeared\n";
					system("PAUSE");

				}
				else if (c >= 11 && c <= 20)
				{
					system("cls");
					cout << "Water pokemon has appeared\n";
					system("PAUSE");

				}
				else if (c >= 21 && c <= 30)
				{
					system("cls");
					cout << "Lightning pokemon has appeared\n";
					system("PAUSE");

				}
				else if (c >= 31 && c <= 50)
				{
					system("cls");
					cout << "Earth pokemon has appeared\n";
					system("PAUSE");
				}

			}

			system("cls");
		}

		

		if (characterLocY == 2 && ((characterLocX == 18 || characterLocX == 19 || characterLocX == 20 || characterLocX == 21 || characterLocX == 22)))
		{
			system("cls");
			cout << "Welcome to Jumshut's shop!\n What would you like? \n\n";
			while (true)
			{	
				
			}
			
		}
		system("cls");
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < k; j++)
			{
				bigmap[i][0] = bigmap[i][1] = bigmap[i][k - 1] = bigmap[i][k - 2] = bigmap[0][j] = bigmap[n-1][j] = block;
				bigmap[i][j + 1] = space;
				if (i == 2 &&(( j == 18) || (j == 19) || (j == 20) || (j == 21) || (j == 22)))
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
		for (int bushY1 = n -16 ; bushY1 < n -12; bushY1++)	 //Куст сверху справа
		{
			for (int bushX1 = k - 11; bushX1 < k-6; bushX1++)
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
		{char keyboard = _getch();

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
		case 27:
		{
			exit(0);
		}
		}
	}

		system("cls");
	}
}