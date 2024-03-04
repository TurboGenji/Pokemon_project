#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <locale>
#include "unite.h"
using namespace std;
struct MosterInfo {
	string name;
	int type;
	int HP;
	int DEF;
	int ATK;
	int A1;
	int A2;
	int Ult;
};

struct AttackInfo {
	string name;
	string description;
	int type;
	int effect;
	int EffectChance;
	int effectStacks;
	int manaCost;
	int damage;
};

struct AEffectInfo {
	string name;
	int type; //1 - bleed, 2 - DMG down, 3 - stun, 4 - burn, 5 - mana lost, 6 - blind
	int damage;
};

struct ItemsInfo {
	string name;
	string desc;
	int effect; //1 - защита, 2 - увеличение урона, 3 - восстановление (моментальное), 4 - регенерация, 5 - неуязвимость, 6 - слепота, 7 - очищение, 8 - опустошение маны, 9 - моментальный ход
	int stacks;
	int cost;
};

struct InventPoke {
	int index;
	int ATK;
	int DEF;
	int HP;
	int Buff;
	int BuffTurns;
	int Debuff;
	int DebuffTurns;
};



MosterInfo monsters[] = {
		{"Smuchi", 1, 250, 10, 75, 0, 3, -1},
		{"Ibas", 1, 250, 10, 75, 0, 2, 4},

		{"Limidrak", 2, 200, 5, 50, 1, 6, -1},
		{"Dainblade", 2, 200, 5, 50, 0, 5, 7},

		{"Sudoecho", 3, 300, 15, 60, 1, 9, -1},
		{"Likikan", 3, 300, 15, 60, 1, 8, 10},

		{"Spinling", 4, 150, 0, 80, 0, 12, -1},
		{"Pikachu", 4, 150, 0, 80, 1, 11, 13}
};
AttackInfo attacks[] = {
	{"Cut", "Cut your enemy and apply bleed", 9, 0, 100, 2, -2, 75},
	{"Heavy punch", "Hit your enemy and have chance to stun enemy", 9, 2, 50, 1, -2, 40},

	{"Flood", "Hit your enemy and decrease enemy's ATK", 1, 1, 100, 2, 2, 60},
	{"Hidro Sniper", "Pierce enemy with pressured water", 1, -1, 0, 0, 2, 160},
	{"Geiser", "Shoot enemy with hot water and weaken his ATK for long time", 1, 1, 100, 5, 5, 240},

	{"Fire breath","Burn enemy and apply burn", 2, 3, 100, 2, 2, 80},
	{"Fire charge","Throw fireball at enemy and sligthly burn enemy", 2, 3, 100, 1, 1, 60},
	{"Sunfire", "Burn enemy with blue fire, leaving big fire on enemy", 2, 3, 100, 4, 5, 300},

	{"Sand spit", "Spit sand into enemy's eyes and blind him for next attack", 3, 5, 100, 1, 1, 40},
	{"Petrification", "Create pillar under enemy that will hit enemy in head and stun it", 3, 2, 100, 1, 2, 50},
	{"Rage", "Hit enemy with two stone fists, leaving enemy unconsious", 3, 2, 100, 3, 5, 300},

	{"Electro-furr", "Shock enemy with electrified furr and paralyze", 4, 4, 100, 1, 2, 80},
	{"Electrifying sight", "Shoot enemy with electricity", 4, -1, 0, 0, 1, 120},
	{"Lightning strike", "Hit enemy with lightning, leaving him paralyzed for some time", 4, 4, 100, 3, 5, 350}
};
AEffectInfo effects[] = {
	{"Bleeding", 1, 20},
	{"Weakened", 2, 20},
	{"Stunned", 3, 0},
	{"Burning", 4, 25},
	{"Paralyzed", 5, 0},
	{"Blinded", 6, 70}

};
ItemsInfo items[] = {
	{"Defense potion", "Increases DEF of standing pokemon for 2 turns", 1, 2, 7},
	{"Blood potion", "Increases ATK of your standing pokemon for 2 turns",2, 3, 5},
	{"Tear of Immortal", "Your standing pokemon doesn't recieve any damage but still can get effects",5, 1, 50},
	{"Flask", "Your standing pokemon will restore health at the beginning of its next 3 turns",4, 3, 10},
	{"Red berry", "Nullifies all effects", 7, 1, 15},
	{"Mana drainer", "Sets mana point of opponent to 0",8, 1, 50},
	{"Sand", "Your opponent may not hit you in next attack", 6, 1, 3},
	{"Tear of Goddess", "Restores half of HP to your standing pokemon", 3, 1, 50},
	{"Favorite snack", "You will gain extra turn", 9, 1, 30},
	{"Pokeball", "Gain opportunity to catch low HP pokemon", 10, 0, 5}
};


void pokInv(int* ipok) {
	system("cls");
	int check = 0;
	int choicing = 0, choicingmax = 3;
	char input;
	for (int i = 0; i < 2; i++) {
		for (int d = 0; d < 2; d++) {
			if (ipok[check] != -1) {
				set(2 + 15 * i, 2 + 2 * d);
				cout << monsters[ipok[check]].name;
				check++;
			}
			else {
				choicingmax--;
				check++;
			}
		}
	}
	do {
		check = 0;
		for (int i = 0; i < 2; i++) {
			for (int d = 0; d < 2; d++) {
				if (ipok[check] != -1) {
					set(2 + 15 * i, 2 + 2 * d);
					cout << monsters[ipok[check]].name;
				}
				check++;
			}
		}
		set(choicing % 2 * 15, 2 + 2 * (choicing / 2));
		cout << char(4);
		input = _getch();
		switch (input)
		{
		case 'w': {
			if (choicingmax > 1)
			{
				set(choicing % 2 * 15, 2 + 2 * (choicing / 2));
				cout << ' ';
				choicing -= 2;
				if (choicing < 0) choicing = choicingmax + choicing + 1;
			}
			break;
		}
		case 's': {
			if (choicingmax > 1)
			{
				set(choicing % 2 * 15, 2 + 2 * (choicing / 2));
				cout << ' ';
				choicing += 2;
				if (choicing > choicingmax) choicing = choicingmax - choicing + 1;
				if (choicing < 0) choicing = 1;
			}
			break;
		}
		case 'd': {
			set(choicing % 2 * 15, 2 + 2 * (choicing / 2));
			cout << ' ';
			choicing++;
			if (choicing > choicingmax) choicing = 0;
			break;
		}
		case 'a': {
			set(choicing % 2 * 15, 2 + 2 * (choicing / 2));
			cout << ' ';
			choicing--;
			if (choicing < 0) choicing = choicingmax;
			break;
		}
		case 'x': {
			if (choicingmax != 0)
			{
				if (ipok[choicing] != -1) {
					char input;
					set(35, 15);
					cout << "Are you sure you want to delete it? (Y/N)";
					input = _getch();
					if (tolower(input) == 'y') {
						for (int i = choicing; i < 9; i++) {
							ipok[i] = ipok[i + 1];
						}
						set((choicing % 3) * 20, 4 + (choicing / 3) * 2);
						for (int i = 0; i < 20; i++) cout << ' ';
						choicingmax--;
						if (choicing > choicingmax) choicing = choicingmax;
					}
					set(35, 15);
					for (int i = 0; i < 50; i++) cout << ' ';
				}
				else {
					set(35, 15);
					cout << "There is nothing";
					Sleep(1000);
					set(35, 15);
					for (int i = 0; i < 20; i++) cout << ' ';
				}
			}
			else {
				set(35, 15);
				cout << "You cannot do that when you have only one pokemon";
				Sleep(2000);
				set(35, 15);
				for (int i = 0; i < 100; i++) cout << ' ';
			}
			break;

		}
		}
	} while (input != char(27));
	system("cls");
}

void invMap(int* inv, int* ipok) {
	system("cls");
	int choice = 0, choicemax = 8;
	char input;

	int get = 0;
	for (int i = 0; i < 3; i++) {
		for (int d = 0; d < 3; d++) {
			if (inv[get] != -1) {
				set(2 + d * 20, 4 + 2 * i);
				cout << items[inv[get]].name;
				get++;
			}
			else choicemax--;
		}
	}
	do {
		get = 0;

		for (int i = 0; i < 3; i++) {
			for (int d = 0; d < 3; d++) {
				if (inv[get] != -1) {
					set(2 + d * 20, 4 + 2 * i);
					cout << items[inv[get]].name;
					get++;
				}
			}
		}
		set(2, 12);
		for (int i = 0; i < 15; i++) {
			cout << ' ';
		}
		set((choice % 3) * 20, 4 + (choice / 3) * 2);
		cout << '>';
		input = _getch();
		switch (tolower(input)) {
		case 'w':
			if (choicemax > 2) {
				set((choice % 3) * 20, 4 + (choice / 3) * 2);
				cout << ' ';
				choice -= 3;
				if (choice < 0) choice = choicemax + choice + 1;
			}
			break;
		case 's':
			if (choicemax > 2) {
				set((choice % 3) * 20, 4 + (choice / 3) * 2);
				cout << ' ';
				choice += 3;
				if (choice > choicemax) choice = abs(choicemax - choice + 1);

			}
			break;
		case 'a': {
			set((choice % 3) * 20, 4 + (choice / 3) * 2);
			cout << ' ';
			choice--;
			if (choice < 0) choice = choicemax;
			break;
		}
		case 'd':
			set((choice % 3) * 20, 4 + (choice / 3) * 2);
			cout << ' ';
			choice++;
			if (choice > choicemax) choice = 0;
			break;
		case 'h':
			set(35, 15);
			for (int i = 0; i < 100; i++) {
				cout << ' ';
			}
			set(35, 15);
			cout << items[inv[choice]].desc;
			break;
		case 'q': pokInv(ipok); break;
		case 'x': {
			char input;
			set(35, 15);
			cout << "Are you sure you want to delete it? (Y/N)";
			input = _getch();
			if (tolower(input) == 'y') {
				for (int i = choice; i < 9; i++) {
					inv[i] = inv[i + 1];
				}
				set((choice % 3) * 20, 4 + (choice / 3) * 2);
				for (int i = 0; i < 20; i++) cout << ' ';
				choicemax--;
				if (choice > choicemax) choice = choicemax;
			}
			set(35, 15);
			for (int i = 0; i < 50; i++) cout << ' ';
			break;
		}
		}
	} while (input != char(27) && input != char(9));
}

const int n = 20, k = 42;
char bigmap[n][k];
char character = 'O';
void map(int start)
{
	srand(time(NULL));
	int characterLocY = 10;
	int characterLocX = 21;
	char bush = '#';
	char block = char(219);
	char space = char(32);
	int count = 4;
	int bushX = 5;
	int bushY = 3, inv[9] = { 0, 3, 9, -1, -1, -1, -1, -1, -1 };
	int ipok[4] = { 2 * start - 2, -1, -1, -1 };
	int stpok = 0;
	int* inventory = inv;
	int chois = 1;
	bool purchasing = false;
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
	while (true) {
		system("cls");
		bool transition = false;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < k; j++)
			{
				cout << bigmap[i][j];
			}
			cout << endl;
		}
		set(characterLocX, characterLocY);
		cout << character;
		while (transition == false)
		{
			int enemyt;
			bool choose = false;
			int shop[9];
			int x = rand() % 100;
			int c = rand() % 5;
			int money = 10;
			if (purchasing == false) {
				for (int i = 0; i < 9; i++) {
					shop[i] = rand() % 10;
				}
			}
			if ((characterLocX >= 6 && characterLocX <= 10) && (characterLocY >= 4 && characterLocY <= 7)) //Приоритет отдаётся электрическому покемону
			{

				if (x <= 20 && x >= 0)
				{

					if (c == 0)
					{
						system("cls");
						cout << "Fire pokemon has appeared\n";
						enemyt = 2;

					}
					else if (c == 1)
					{
						system("cls");
						cout << "Water pokemon has appeared\n";
						enemyt = 1;
					}
					else if (c == 4)
					{
						system("cls");
						cout << "Earth pokemon has appeared\n";
						enemyt = 3;
					}
					else if (c == 2 || c == 3)
					{
						system("cls");
						cout << "Lightning pokemon has appeared\n";
						enemyt = 4;
					}
					_getch();
					system("cls");
					int random = rand() % 2 + (enemyt - 1) * 2;
					int enemy[] = { monsters[random].type, monsters[random].ATK, monsters[random].DEF, monsters[random].HP, random/*index*/, -1/*bad effects*/, /*stacks of effect*/ };
					money += fight(inventory, ipok, enemy, stpok);
					purchasing = false;
					transition = true;
				}
			}
			else if ((characterLocX >= 6 && characterLocX <= 10) && (characterLocY >= 13 && characterLocY <= 17)) //Приоритет отдаётся огненному покемону
			{


				if (x <= 20 && x >= 0)
				{

					if (c == 0)
					{
						system("cls");
						cout << "Water pokemon has appeared\n";
						enemyt = 1;

					}
					else if (c == 1)
					{
						system("cls");
						cout << "Earth pokemon has appeared\n";
						enemyt = 3;
					}
					else if (c == 4)
					{
						system("cls");
						cout << "Lightning pokemon has appeared\n";
						enemyt = 4;

					}
					else if (c == 2 || c == 3)
					{
						system("cls");
						cout << "Fire pokemon has appeared\n";
						enemyt = 2;
					}
					_getch();
					system("cls");
					int random = rand() % 2 + (enemyt - 1) * 2;
					int enemy[] = { monsters[random].type, monsters[random].ATK, monsters[random].DEF, monsters[random].HP, random/*index*/, -1/*bad effects*/, /*stacks of effect*/ };
					money += fight(inventory, ipok, enemy, stpok);
					purchasing = false;
					transition = true;
				}
			}
			else if ((characterLocX >= 30 && characterLocX <= 35) && (characterLocY >= 13 && characterLocY <= 17)) //Приоритет отдаётся водному покемону
			{
				if (x <= 20 && x >= 0)
				{
					if (c == 0)
					{
						system("cls");
						cout << "Earth pokemon has appeared\n";
						enemyt = 3;

					}
					else if (c == 1)
					{
						system("cls");
						cout << "Lightning pokemon has appeared\n";
						enemyt = 4;

					}
					else if (c == 4)
					{
						system("cls");
						cout << "Fire pokemon has appeared\n";
						enemyt = 2;

					}
					else if (c == 2 || c == 3)
					{
						system("cls");
						cout << "Water pokemon has appeared\n";
						enemyt = 1;
					}
					_getch();
					system("cls");
					int random = rand() % 2 + (enemyt - 1) * 2;
					int enemy[] = { monsters[random].type, monsters[random].ATK, monsters[random].DEF, monsters[random].HP, random/*index*/, -1/*bad effects*/, /*stacks of effect*/ };

					money += fight(inventory, ipok, enemy, stpok);
					purchasing = false;
					transition = true;
				}
			}
			else if ((characterLocX >= 30 && characterLocX <= 35) && (characterLocY >= 4 && characterLocY <= 7)) //Приоритет отдаётся земляному покемону
			{
				if (x <= 20 && x >= 0)
				{
					if (c == 0)
					{
						system("cls");
						cout << "Fire pokemon has appeared\n";
						enemyt = 2;

					}
					else if (c == 1)
					{
						system("cls");
						cout << "Water pokemon has appeared\n";
						enemyt = 1;

					}
					else if (c == 4)
					{
						system("cls");
						cout << "Lightning pokemon has appeared\n";
						enemyt = 4;

					}
					else if (c == 2 || c == 3)
					{
						system("cls");
						cout << "Earth pokemon has appeared\n";
						enemyt = 3;
					}
					int random = rand() % 2 + (enemyt - 1) * 2;
					int enemy[] = { monsters[random].type, monsters[random].ATK, monsters[random].DEF, monsters[random].HP, random/*index*/, -1/*bad effects*/, /*stacks of effect*/ };

					_getch();
					system("cls");
					money += fight(inventory, ipok, enemy, stpok);
					purchasing = false;
					transition = true;
				}
			}



			if (characterLocY == 2 && characterLocX >= 18 && characterLocX <= 22)
			{
				transition = true;
				system("cls");
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
				Sleep(100);
				int shopp = 0;
				for (int i = 0; i < 3; i++) {
					for (int d = 0; d < 3; d++) {
						set(2 + d * 20, 4 + 2 * i);
						cout << items[shop[shopp]].name;
						shopp++;
					}
				}
				char input;
				int choice = 0, choicemax = 8;
				do {
					set(2, 12);
					for (int i = 0; i < 15; i++) {
						cout << ' ';
					}
					set(2, 12);
					cout << "You have: " << money;
					set((choice % 3) * 20, 4 + (choice / 3) * 2);
					cout << '>';
					input = _getch();
					switch (tolower(input)) {
					case 'w':
						if (choicemax > 2) {
							set((choice % 3) * 20, 4 + (choice / 3) * 2);
							cout << ' ';
							choice -= 3;
							if (choice < 0) choice = choicemax + choice + 1;
						}
						break;
					case 's':
						if (choicemax > 2) {
							set((choice % 3) * 20, 4 + (choice / 3) * 2);
							cout << ' ';
							choice += 3;
							if (choice > choicemax) choice = abs(choicemax - choice + 1);

						}
						break;
					case 'a': {
						set((choice % 3) * 20, 4 + (choice / 3) * 2);
						cout << ' ';
						choice--;
						if (choice < 0) choice = choicemax;
						break;
					}
					case 'd':
						set((choice % 3) * 20, 4 + (choice / 3) * 2);
						cout << ' ';
						choice++;
						if (choice > choicemax) choice = 0;
						break;
					case 'h':
						set(35, 17);
						for (int i = 0; i < 10; i++) {
							cout << ' ';
						}
						set(35, 17);
						cout << "Cost: " << items[shop[choice]].cost;
						set(35, 15);
						for (int i = 0; i < 100; i++) {
							cout << ' ';
						}
						set(35, 15);
						cout << items[shop[choice]].desc;
						break;
					case 'x': {
						bool space = false;
						for (int i = 0; i < 9; i++) {
							if (inv[i] == -1) {
								space = true;
							}
						}
						if (space == true) {
							if (shop[choice] != -1)
							{
								if (money >= items[shop[choice]].cost) {
									set(35, 10);
									cout << "Purchased";
									money -= items[shop[choice]].cost;
									shop[choice] = -1;
									Sleep(1000);
									set(35, 10);
									for (int i = 0; i < 15; i++) {
										cout << ' ';
									}
								}
								else {
									set(35, 10);
									cout << "Not enough";
									Sleep(1000);
									set(35, 10);
									for (int i = 0; i < 15; i++) {
										cout << ' ';
									}
								}
							}
							else {
								set(35, 10);
								cout << "Already purchased";
								Sleep(1000);
								set(35, 10);
								for (int i = 0; i < 20; i++) {
									cout << ' ';
								}

							}
						}
					}
					}
				} while (input != char(27));
				characterLocY++;

			}


			if (transition != true) {
				char keyboard = _getch();

				switch (keyboard) {

				case 'w':
				{
					set(characterLocX, characterLocY);
					cout << bigmap[characterLocY][characterLocX];
					characterLocY--;
					if (characterLocY == 0)
						characterLocY = 1;
					set(characterLocX, characterLocY);
					cout << character;
					break;
				}
				case 's':
				{
					set(characterLocX, characterLocY);
					cout << bigmap[characterLocY][characterLocX];
					characterLocY++;
					if (characterLocY == 19)
						characterLocY = 18;
					set(characterLocX, characterLocY);
					cout << character;
					break;
				}
				case 'a':
				{
					set(characterLocX, characterLocY);
					cout << bigmap[characterLocY][characterLocX];
					characterLocX--;
					if (characterLocX == 1 || characterLocX == 0)
						characterLocX = 2;
					set(characterLocX, characterLocY);
					cout << character;
					break;
				}
				case 'd':
				{
					set(characterLocX, characterLocY);
					cout << bigmap[characterLocY][characterLocX];
					characterLocX++;
					if (characterLocX == 40 || characterLocX == 41)
						characterLocX = 39;
					set(characterLocX, characterLocY);
					cout << character;
					break;
				}
				case 9: {
					invMap(inv, ipok);
					transition = true;
					break;
				}
				case 27:
				{
					exit(0);
				}
				}
			}


		}
	}
}