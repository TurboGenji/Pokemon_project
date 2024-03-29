#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <locale>
#include "unite.h"
using namespace std;
void set(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

bool esc = false;

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
	int effect; //1 - ������, 2 - ���������� �����, 3 - �������������� (������������), 4 - �����������, 5 - ������������, 6 - �������, 7 - ��������, 8 - ����������� ����, 9 - ������������ ���
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


int mana = 0;
int turn = 1;
int chose = 0;

int emana = 0;

void line() {
	for (int i = 0; i < 90; i++) {
		cout << '-';
	}
}




void cleanse() {//������
	set(10, 1);
	for (int i = 0; i < 8; i++) {
		for (int d = 0; d < 100; d++) {
			cout << ' ';
		}
		cout << endl;
	}
}

int ataka(int *enemy, InventPoke* cachedPok) { //������
	char input;
	int choice = 0, choicemax = 2;
	set(10, 1);
	for (int i = 0; i < 8; i++) {
		for (int d = 0; d < 100; d++) {
			cout << ' ';
		}
		cout << endl;
	}
	set(10, 1);
	cout << monsters[cachedPok[chose].index].name;
	cout << " [";
	switch (monsters[cachedPok[chose].index].type) {
	case 1: cout << "Water"; break;
	case 2: cout << "Fire"; break;
	case 3: cout << "Earth"; break;
	case 4: cout << "Lightning"; break;
	}
	cout << ']';
	set(25, 2);
	cout << attacks[monsters[cachedPok[chose].index].A1].name;
	set(50, 2);
	if (-attacks[monsters[cachedPok[chose].index].A1].manaCost > 0) cout << ' ';
	cout << -attacks[monsters[cachedPok[chose].index].A1].manaCost << " Mana";
	set(25, 4);
	for (int i = 0; i < 50; i++) {
		cout << ' ';
	}
	set(25, 4);
	cout << attacks[monsters[cachedPok[chose].index].A2].name;
	set(50, 4);
	if (-attacks[monsters[cachedPok[chose].index].A2].manaCost > 0) cout << ' ';
	cout << -attacks[monsters[cachedPok[chose].index].A2].manaCost << " Mana";
	set(13, 6);
	for (int i = 0; i < 50; i++) {
		cout << ' ';
	}
	set(13, 6);
	if (monsters[cachedPok[chose].index].Ult != -1) {
		cout << "Ultimate:";
		set(25, 6);
		cout << attacks[monsters[cachedPok[chose].index].Ult].name;
		set(50, 6);
		cout << -attacks[monsters[cachedPok[chose].index].Ult].manaCost << " Mana";
	}
	else choicemax--;
	do {
		set(23, choice*2+2);
		cout << char(4);
		input = _getch();
		switch (input) {
		case 'w': {
			set(23, choice * 2 + 2);
			cout << ' ';
			choice--;
			if (choice < 0) choice = choicemax;
			break;
		}
		case 's': {
			set(23, choice * 2 + 2);
			cout << ' ';
			choice++;
			if (choice > choicemax) choice = 0;
			break;
		}
		case 'x': {
			if (choice == 1) {
				if (mana < attacks[monsters[cachedPok[chose].index].A2].manaCost) {
					input = ' ';
					set(20, 8);
					cout << "Not enough mana";
					break;
				}
			}
			if (choice == 2) {
				if (mana < attacks[monsters[cachedPok[chose].index].Ult].manaCost) {
					input = ' ';
					set(20, 8);
					cout << "Not enough mana";
					break;
				}
			}
			break;
		}
		case 'h': {
			switch (choice) {
			case 0: {
				set(35, 15);
				for (int i = 0; i < 100; i++) {
					cout << ' ';
				}
				set(35, 15);
				cout << attacks[monsters[cachedPok[chose].index].A1].description;
				break;
			}
			case 1: {
				set(35, 15);
				for (int i = 0; i < 100; i++) {
					cout << ' ';
				}
				set(23, 15);
				cout << attacks[monsters[cachedPok[chose].index].A2].description;
				break;
			}
			case 2: {
				set(35, 15);
				for (int i = 0; i < 100; i++) {
					cout << ' ';
				}
				set(35, 15);
				cout << attacks[monsters[cachedPok[chose].index].Ult].description;
				break;
			}
			}
			break;
		}
		}
	}while (input != char(27) && tolower(input) != 'x');

	if (input == char(27)) {
		cleanse();
		return 0;
	}
	int damage = 0;
	if (cachedPok[chose].Debuff == 5) {
		if (rand() % 100 < 70) {
			system("cls");
			set(25, 4);
			cout << "You've missed " << monsters[enemy[4]].name;
			set(25, 4);
			Sleep(1000);
			for (int i = 0; i < 40; i++) {
				cout << ' ';
				Sleep(10);
			}
			return -1;
		}
	}	
			switch (choice) {
			case 0: {
				int weak;
				if (abs(enemy[0] - attacks[monsters[cachedPok[chose].index].A1].type) != 1) weak = 0;
				else weak = attacks[monsters[cachedPok[chose].index].A1].type - enemy[0];
				if (enemy[0] - attacks[monsters[cachedPok[chose].index].A1].type == 3) weak = -1;
				if (enemy[0] - attacks[monsters[cachedPok[chose].index].A1].type == -3) weak = 1;
				damage = cachedPok[chose].ATK * (float(attacks[monsters[cachedPok[chose].index].A1].damage) / 100) - ((cachedPok[chose].ATK * (float(attacks[monsters[cachedPok[chose].index].A1].damage) / 100) * (20 * weak + enemy[2])) / 100);
				enemy[3] -= damage;
				mana -= attacks[monsters[cachedPok[chose].index].A1].manaCost;
				if (attacks[monsters[cachedPok[chose].index].A1].effect != -1) {
					if (rand() % 100 < attacks[monsters[cachedPok[chose].index].A1].EffectChance) {
						if (enemy[5] == attacks[monsters[cachedPok[chose].index].A1].effect) {
							enemy[6] += attacks[monsters[cachedPok[chose].index].A1].effectStacks;
						}
						else {
							enemy[5] = attacks[monsters[cachedPok[chose].index].A1].effect;
							enemy[6] = attacks[monsters[cachedPok[chose].index].A1].effectStacks;
						}
					}
				}
				break;
			}
			case 1: {
				int weak;
				if (abs(enemy[0] - attacks[monsters[cachedPok[chose].index].A2].type) != 1) weak = 0;
				else weak = attacks[monsters[cachedPok[chose].index].A2].type - enemy[0];
				if (enemy[0] - attacks[monsters[cachedPok[chose].index].A2].type == 3) weak = 1;
				if (enemy[0] - attacks[monsters[cachedPok[chose].index].A2].type == -3) weak = -1;
				damage = cachedPok[chose].ATK * (float(attacks[monsters[cachedPok[chose].index].A2].damage) / 100) - ((cachedPok[chose].ATK * (float(attacks[monsters[cachedPok[chose].index].A2].damage) / 100) * (20 * weak + enemy[2])) / 100);
				enemy[3] -= damage;
				mana -= attacks[monsters[cachedPok[chose].index].A2].manaCost;
				if (attacks[monsters[cachedPok[chose].index].A1].effect != -1) {
					if (rand() % 100 < attacks[monsters[cachedPok[chose].index].A2].EffectChance) {
						if (enemy[5] == attacks[monsters[cachedPok[chose].index].A2].effect) {
							enemy[6] += attacks[monsters[cachedPok[chose].index].A2].effectStacks;
						}
						else {
							enemy[5] = attacks[monsters[cachedPok[chose].index].A2].effect;
							enemy[6] = attacks[monsters[cachedPok[chose].index].A2].effectStacks;
						}
					}
				}
				break;
			}
			case 2: {
				int weak;
				if (abs(enemy[0] - attacks[monsters[cachedPok[chose].index].Ult].type) != 1) weak = 0;
				else weak = attacks[monsters[cachedPok[chose].index].Ult].type - enemy[0];
				if (enemy[0] - attacks[monsters[cachedPok[chose].index].Ult].type == 3) weak = 1;
				if (enemy[0] - attacks[monsters[cachedPok[chose].index].Ult].type == -3) weak = -1;
				damage = cachedPok[chose].ATK * (float(attacks[monsters[cachedPok[chose].index].Ult].damage) / 100) - ((cachedPok[chose].ATK * (float(attacks[monsters[cachedPok[chose].index].Ult].damage) / 100) * (20 * weak + enemy[2])) / 100);
				enemy[3] -= damage;
				mana -= attacks[monsters[cachedPok[chose].index].Ult].manaCost;
				if (attacks[monsters[cachedPok[chose].index].Ult].effect != -1) {
					if (rand() % 100 < attacks[monsters[cachedPok[chose].index].Ult].EffectChance) {
						if (enemy[5] == attacks[monsters[cachedPok[chose].index].Ult].effect) {
							enemy[6] += attacks[monsters[cachedPok[chose].index].Ult].effectStacks;
						}
						else {
							enemy[5] = attacks[monsters[cachedPok[chose].index].Ult].effect;
							enemy[6] = attacks[monsters[cachedPok[chose].index].Ult].effectStacks;
						}
					}
				}
				break;
			}
			}
	if (mana > 7) mana = 7;
	system("cls");
	set(25, 4);
	cout << "You've dealt " << damage << " damage to " << monsters[enemy[4]].name;
	set(25, 4);
	Sleep(1000);
	for (int i = 0; i < 40; i++) {
		cout << ' ';
		Sleep(10);
	}
	return -1;
}

void posEffects(InventPoke* cachedPok) {//������
	cachedPok[chose].ATK = monsters[cachedPok[chose].index].ATK;
	cachedPok[chose].DEF = monsters[cachedPok[chose].index].DEF;
	if (cachedPok[chose].Buff != 0) {
		switch (cachedPok[chose].Buff) {
		case 1: {
			int def = monsters[cachedPok[chose].index].DEF + (monsters[cachedPok[chose].index].DEF * 20) / 100;
			cachedPok[chose].DEF = def;
			cachedPok[chose].BuffTurns--;
			break;
		}
		case 2: {
			int atk = monsters[cachedPok[chose].index].ATK + (monsters[cachedPok[chose].index].ATK * 20) / 100;
			cachedPok[chose].ATK = atk;
			cachedPok[chose].BuffTurns--;
			break;
		}
		
		
		case 4: {
			cachedPok[chose].HP += cachedPok[chose].HP + monsters[cachedPok[chose].index].HP * 0.15;
			if (cachedPok[chose].HP > monsters[cachedPok[chose].index].HP) cachedPok[chose].HP = monsters[cachedPok[chose].index].HP;
			cachedPok[chose].BuffTurns--;
			break;
		}
		case 5: {
			cachedPok[chose].DEF = 100;
			cachedPok[chose].BuffTurns--;
			break;
		}
		

		}
	}
}

void negEffects(int *enemy, InventPoke* cachedPok) {//������
	if (cachedPok[chose].Debuff != -1) {
		switch (cachedPok[chose].Debuff) {
		case 0: {
			cachedPok[chose].HP -= (enemy[1] * 15) / 100;
			cachedPok[chose].DebuffTurns--;
			break;
		}
		case 1: {
			int atk = monsters[cachedPok[chose].index].ATK - (monsters[cachedPok[chose].index].ATK * 20) / 100;
			cachedPok[chose].ATK = atk;
			cachedPok[chose].DebuffTurns--;
			break;
		}
		case 2: {
			cachedPok[chose].DebuffTurns--;
			break;
		}
		case 3: {
			cachedPok[chose].HP -= double((monsters[cachedPok[chose].index].HP * 25 * cachedPok[chose].DebuffTurns) / 1000);
			cachedPok[chose].DebuffTurns--;
			break;
		}
		case 4: {
			mana = 0;
			cachedPok[chose].DebuffTurns--;
			break;
		}
		case 5: {
			cachedPok[chose].DebuffTurns--;
		}
		}
	}
}

void itemApply(int chosen, int *enemy, InventPoke* cachedPok) {//������
	switch (items[chosen].effect) {
	case 3: {
		cachedPok[chose].HP += cachedPok[chose].HP + 0.5 * monsters[cachedPok[chose].index].HP;
		if (cachedPok[chose].HP > monsters[cachedPok[chose].index].HP) cachedPok[chose].HP = monsters[cachedPok[chose].index].HP;
		turn--;
		return;
	}
	case 7: {
		cachedPok[chose].Debuff = -1;
		turn--;
		return;
	}
	case 6: {
		if (enemy[5] != items[chosen].effect) enemy[6] = 0;
		enemy[5] = 5;
		enemy[6] = items[chosen].stacks;
		turn--;
		return;
	}
	case 8: {
		emana = 0;
		turn--;
		return;
	}
	case 9: {
		turn++;
		return;
	}
	case 10: {
		cleanse();
		set(50, 5);
		cout << "Cannot use that from here";
		Sleep(1000);
		return;
	}
	}
	if (cachedPok[chose].Buff != items[chosen].effect) cachedPok[chose].BuffTurns = 0;
	cachedPok[chose].Buff = items[chosen].effect;
	cachedPok[chose].BuffTurns += items[chosen].stacks;
	turn--;
}


void inventory(int* lol, int *enemy, InventPoke* cachedPok) {//������
	cleanse();
	int choice = 0, choicemax = 8;
	char input;
	for (int i = 0; i < 3; i++) {
		for (int d = 0; d < 3; d++) {
			set(20 + 30 * d, 2 + 2 * i);
			if (lol[choice] == -1) {
				choicemax--;
				continue;
			}
			cout << items[lol[choice]].name;
			choice++;
		}
	}
	choice = 0;
	do {
		set(18 + 30*((choice) % 3), 2 + 2 * ((choice)/3));
		cout << char(4);
		input = _getch();
		switch (tolower(input)) {
		case 'w': 
			if (choicemax > 2) {
				set(18 + 30 * (choice % 3), 2 + 2 * (choice / 3));
				cout << ' ';
				choice -= 3;
				if (choice < 0) choice = choicemax + choice + 1;
			}
			break;
		case 's':
			if (choicemax > 2) {
				set(18 + 30 * ((choice) % 3), 2 + 2 * ((choice) / 3));
				cout << ' ';
				choice += 3;
				if (choice > choicemax) choice = choicemax - choice + 1;
			}
			break;
		case 'a': {
			set(18 + 30 * ((choice) % 3), 2 + 2 * ((choice) / 3));
			cout << ' ';
			choice--;
			if (choice < 0) choice = choicemax;
			break;
		}
		case 'd': 
			set(18 + 30 * ((choice) % 3), 2 + 2 * ((choice) / 3));
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
			cout << items[lol[choice]].desc;
			break;
		}
	} while (input != char(27) && tolower(input) != 'x');
	if (input == char(27)) {
		system("cls");
		return;
	}
	itemApply(lol[choice], enemy, cachedPok);
	if (lol[choice] != 9) {
		for (int i = choice; i < (choicemax + 1); i++) {
			lol[i] = lol[i + 1];
		}
		lol[choicemax] = -1;
	}
	system("cls");
	return;
}

void statusCheck(int* enemy, InventPoke* cachedPok) {
	cleanse();
	set(20, 2);
	cout << monsters[cachedPok[chose].index].name;
	set(50, 2);
	if (cachedPok[chose].Buff != 0) {
		switch (cachedPok[chose].Buff) {
		case 1: {
			cout << "DEFENSE UP";
			break;
		}
		case 2: {
			cout << "ATTACK UP";
			break;
		}


		case 4: {
			cout << "REGENERATES";
			break;
		}
		case 5: {
			cout << "UNSTOPPABLE";
			break;
		}
		}
		cout << " for " << cachedPok[chose].BuffTurns;
	}
	if (cachedPok[chose].Debuff != -1) {
		set(70, 2);
		cout << effects[cachedPok[chose].Debuff].name << " for " << cachedPok[chose].DebuffTurns;
	}
	set(20, 6);
	cout << monsters[enemy[4]].name;
	set(50, 6);
	if (enemy[3] * 100 / monsters[enemy[4]].HP > 90) cout << "Unscratched";
	else if (enemy[3] * 100 / monsters[enemy[4]].HP > 70) cout << "Annoyed";
	else if (enemy[3] * 100 / monsters[enemy[4]].HP > 50) cout << "Angry";
	else if (enemy[3] * 100 / monsters[enemy[4]].HP > 30) cout << "Raging";
	else cout << "Terrified";
	if (enemy[5] != -1) {
		set(70, 6);
		cout << effects[enemy[5]].name << " for " << enemy[6];
	}
}

int changePok(InventPoke* cachedPok) {
	cleanse();
	int choice = 0, choicemax = 3;
	int count = 0;
	char input;
	for (int i = 0; i < 4; i++) {
		if (cachedPok[i].index == -1) count++;
	}
	if (count == 3) {
		set(50, 5);
		cout << "Cannot change";
		Sleep(2000);
		return 0;
	}
	int check = 0;
	for (int i = 0; i < 2; i++) {
		for (int d = 0; d < 2; d++) {
			if (cachedPok[check].index == -1) choicemax--;
		}
	}
	do {
		check = 0;
		for (int i = 0; i < 2; i++) {
			for (int d = 0; d < 2; d++) {
				if (cachedPok[check].index != -1)
				{
					set(40 + d * 30, 2 + 3 * i);
					cout << monsters[cachedPok[check].index].name;
				}
				check++;
			}
		}
		set(38 + choice % 2 * 30, 2 + 3 * (choice / 2));
		cout << char(4);
		input = _getch();
		switch (input)
		{
		case 'w': {
			set(38 + choice % 2 * 30, 2 + 3 * (choice / 2));
			cout << ' ';
			choice -= 2;
			if (choice < 0) choice = choicemax + choice + 1;
			break;
		}
		case 's': {
			set(38 + choice % 2 * 30, 2 + 3 * (choice / 2));
			cout << ' ';
			choice += 2;
			if (choice > choicemax) choice = choicemax - choice + 1;
			if (choice < 0) choice = 1;
			break;
		}
		case 'd': {
			set(38 + choice % 2 * 30, 2 + 3 * (choice / 2));
			cout << ' ';
			choice++;
			if (choice > choicemax) choice = 0;
			break;
		}
		case 'a': {
			set(38 + choice % 2 * 30, 2 + 3 * (choice / 2));
			cout << ' ';
			choice--;
			if (choice < 0) choice = choicemax;
			break;
		}
		case 'x': {
			return choice;
			break;
		}
		}
	} while (input != char(27) && input != 'x');
	return 0;
}

void catchPok(int* enemy, InventPoke* cachedPok, int* inv) {
	int check = 0;
	for (int i = 0, d = 0; i < 0;) {
		if (cachedPok[i].index == -1) {
			break;
		}
		else {
			check++;
		}
	}
	if (check == 4) {
		cleanse();
		set(50, 5);
		cout << "Inventory full";
		return;
	}
	if ((enemy[3] / monsters[enemy[4]].HP) * 100 < 30) {
		if (rand() % 2 == 1) {
			cleanse();
			set(50, 5);
			cout << "Success";
			enemy[3] = 0;
			Sleep(2000);
			for (int i = 0; i < 4; i++) {
				if (cachedPok[i].index == -1) {
					cachedPok[i].index == enemy[4];
				}
			}
		}
		for (int i = 0; i < 9; i++) {
			if (inv[i] == 9) {
				for (int d = i; d < 9; d++) {
					inv[d] = inv[d + 1];
				}
			}
		}
		return;
	}
	else {
		cleanse();
		set(50, 5);
		cout << "Cannot catch";
		Sleep(1000);
	}
}

int actions(int* inv, int *enemy, InventPoke* cachedPok) {
	cleanse();
	int choice = 0, choicemax = 2;
	char input;
	set(60, 2);
	cout << "Escape";
	set(60, 4);
	cout << "Change pokemon";
	set(60, 6);
	cout << "Pass";
	set(60, 8);
	for (int i = 0; i < 9; i++) {
		if (inv[i] == 9) {
			cout << "Catch pokemon";
			choicemax++;
			break;
		}
	}
	do {
		set(58, 2 + 2 * choice);
		cout << char(4);
		input = _getch();
		switch (tolower(input)) {
		case 'w': {
			set(58, 2 + 2 * choice);
			cout << ' ';
			choice--;
			if (choice < 0) choice = choicemax;
			break;
		}
		case 's': {
			set(58, 2 + 2 * choice);
			cout << ' ';
			choice++;
			if (choice > choicemax) choice = 0;
			break;
		}
		case 'x': {
			switch (choice) {
			case 0: {
				esc = true;
				turn = 0;
				system("cls");
				set(50, 5);
				cout << "You fleed";
				Sleep(2000);
				break;
			}
			case 1: {
				int change = changePok(cachedPok);
				cleanse();
				if (chose == change) {
					return chose;
					break;
				}
				if (cachedPok[change].index == -1 || cachedPok[change].HP <= 0) {
					return chose;
					break;
				}
				turn--;
				cleanse();
				set(50, 5);
				cout << "I choose you! " << monsters[cachedPok[change].index].name << "!";
				Sleep(2000);
				cleanse();
				return change;
				break;
			}
			case 2: {
				turn = 0;
				break;
			}
			case 3: {
				catchPok(enemy, cachedPok, inv);
				break;
			}
			}
		}
		}
	} while (input != char(27) && tolower(input) != 'x');
	cleanse();
	return 0;
}


void enemyAttack(int* enemy, InventPoke* cachedPok) {
	cleanse();
	int damage = 0;
	set(50, 5);
	if (enemy[5] == 3) {
		cout << "Enemy can't move";
		return;
	}
	if (enemy[5] == 5 && rand() % 100 < 70) {
		cout << monsters[enemy[4]].name << " missed";	
		return;
	}
	if (cachedPok[chose].Buff == 5) {
		cout << monsters[enemy[4]].name << "'s couldn't harm your pokemon";
	}
	else if (emana == 5) {
		int weak;
		if (abs(monsters[cachedPok[chose].index].type - attacks[monsters[enemy[4]].Ult].type) != 1) weak = 0;
		else weak = attacks[monsters[enemy[4]].Ult].type - monsters[cachedPok[chose].index].type;
		if (monsters[cachedPok[chose].index].type - attacks[monsters[enemy[4]].Ult].type == 3) weak = -1;
		if (monsters[cachedPok[chose].index].type - attacks[monsters[enemy[4]].Ult].type == -3) weak = 1;
		damage = cachedPok[chose].ATK * (float(attacks[monsters[enemy[4]].Ult].damage) / 100) - ((cachedPok[chose].ATK * (float(attacks[monsters[enemy[4]].Ult].damage) / 100) * (20 * weak + cachedPok[chose].DEF)) / 100);
		if (cachedPok[chose].Buff != 5) {
			cachedPok[chose].HP -= damage;
		}
		emana -= attacks[monsters[enemy[4]].Ult].manaCost;
		if (attacks[monsters[enemy[4]].Ult].effect != -1 && cachedPok[chose].Buff != 5) {
			if (rand() % 100 < attacks[monsters[enemy[4]].Ult].EffectChance) {
				if (cachedPok[chose].Debuff == attacks[monsters[enemy[4]].Ult].effect) {
					cachedPok[chose].Debuff += attacks[monsters[enemy[4]].Ult].effectStacks;
				}
				else {
					cachedPok[chose].Debuff = attacks[monsters[enemy[4]].Ult].effect;
					cachedPok[chose].DebuffTurns = attacks[monsters[enemy[4]].Ult].effectStacks;
				}
			}
		}
		if (cachedPok[chose].Buff != 5) {
			cout << monsters[enemy[4]].name << " used " << attacks[monsters[enemy[4]].Ult].name << " for " << damage;
		}
	}
	else if (emana >= attacks[monsters[enemy[4]].A2].manaCost && rand() % 4 < 2) {
		int weak;
		if (abs(monsters[cachedPok[chose].index].type - attacks[monsters[enemy[4]].A2].type) != 1) weak = 0;
		else weak = attacks[monsters[enemy[4]].A2].type - monsters[cachedPok[chose].index].type;
		if (monsters[cachedPok[chose].index].type - attacks[monsters[enemy[4]].A2].type == 3) weak = -1;
		if (monsters[cachedPok[chose].index].type - attacks[monsters[enemy[4]].A2].type == -3) weak = 1;
		damage = cachedPok[chose].ATK * (float(attacks[monsters[enemy[4]].A2].damage) / 100) - ((cachedPok[chose].ATK * (float(attacks[monsters[enemy[4]].A2].damage) / 100) * (20 * weak + cachedPok[chose].DEF)) / 100);
		if (cachedPok[chose].Buff != 5) {
			cachedPok[chose].HP -= damage;
		}
		emana -= attacks[monsters[enemy[4]].A2].manaCost;
		if (attacks[monsters[enemy[4]].A2].effect != -1 && cachedPok[chose].Buff != 5) {
			if (rand() % 100 < attacks[monsters[enemy[4]].A2].EffectChance) {
				if (cachedPok[chose].Debuff == attacks[monsters[enemy[4]].A2].effect) {
					cachedPok[chose].DebuffTurns += attacks[monsters[enemy[4]].A2].effectStacks;
				}
				else {
					cachedPok[chose].Debuff = attacks[monsters[enemy[4]].A2].effect;
					cachedPok[chose].DebuffTurns = attacks[monsters[enemy[4]].A2].effectStacks;
				}
			}
		}
		if (cachedPok[chose].Buff != 5) {
			cout << monsters[enemy[4]].name << " used " << attacks[monsters[enemy[4]].A2].name << " for " << damage;
		}
	}
	else {
		int weak;
		if (abs(monsters[cachedPok[chose].index].type - attacks[monsters[enemy[4]].A1].type) != 1) weak = 0;
		else weak = attacks[monsters[enemy[4]].A1].type - monsters[cachedPok[chose].index].type;
		if (monsters[cachedPok[chose].index].type - attacks[monsters[enemy[4]].A1].type == 3) weak = -1;
		if (monsters[cachedPok[chose].index].type - attacks[monsters[enemy[4]].A1].type == -3) weak = 1;
		damage = cachedPok[chose].ATK * (float(attacks[monsters[enemy[4]].A1].damage) / 100) - ((cachedPok[chose].ATK * (float(attacks[monsters[enemy[4]].A1].damage) / 100) * (20 * weak + cachedPok[chose].DEF)) / 100);
		if (cachedPok[chose].Buff != 5) {
			cachedPok[chose].HP -= damage;
		}
		emana -= attacks[monsters[enemy[4]].A1].manaCost;
		if (attacks[monsters[enemy[4]].A1].effect != -1 && cachedPok[chose].Buff != 5) {
			if (rand() % 100 < attacks[monsters[enemy[4]].A1].EffectChance) {
				if (cachedPok[chose].Debuff == attacks[monsters[enemy[4]].A1].effect) {
					cachedPok[chose].DebuffTurns += attacks[monsters[enemy[4]].A1].effectStacks;
				}
				else {
					cachedPok[chose].Debuff = attacks[monsters[enemy[4]].A1].effect;
					cachedPok[chose].DebuffTurns = attacks[monsters[enemy[4]].A1].effectStacks;
				}
			}
		}
		if (cachedPok[chose].Buff != 5) {
			cout << monsters[enemy[4]].name << " used " << attacks[monsters[enemy[4]].A1].name << " for " << damage;
		}
	}
	if (emana > 7) emana = 7;
	set(50, 5);
	Sleep(2000);
	for (int i = 0; i < 30; i++) {
		cout << ' ';
		Sleep(10);
	}
	enemy[6]--;
	if (enemy[6] == 0) enemy[5] = -1;
	cleanse();
}

void dead(InventPoke* cachedPok) {
	if (cachedPok[chose].HP < 0) {
		cachedPok[chose].index = -1;
		chose++;
		if (chose == 4) chose = 0;
	}
}

int fight(int* item, int* ipok, int* enemy, int stpok) {
	srand(time(NULL));
	esc = false;
	InventPoke cachedPok[] = {
	{ipok[0], monsters[ipok[0]].ATK, monsters[ipok[0]].DEF, monsters[ipok[0]].HP, 0, 0, -1, 0},
	{ipok[1], monsters[ipok[1]].ATK, monsters[ipok[1]].DEF, monsters[ipok[1]].HP, 0, 0, -1, 0},
	{ipok[2], monsters[ipok[2]].ATK, monsters[ipok[2]].DEF, monsters[ipok[2]].HP, 0, 0, -1, 0},
	{ipok[3], monsters[ipok[3]].ATK, monsters[ipok[3]].DEF, monsters[ipok[3]].HP, 0, 0, -1, 0}
	};
	int* pain = enemy;
	
	int command = 0;
	bool died = false;
	while (enemy[3] > 0 && esc == false && died == false) {
		int deads=0;
		for (int i = 0; i < 4; i++) {
			if (cachedPok[i].index == -1) deads++;
		}
		if (deads == 4) return 0;;
		turn = 1;
		while (turn != 0 && died == false) {
			if (cachedPok[chose].DebuffTurns == 0) cachedPok[chose].Debuff = -1;
			if (cachedPok[chose].BuffTurns == 0) cachedPok[chose].Buff = 0;
			set(10, 9);
			line();
		char input;
		set(20, 10);
		cout << "Attack";
		set(40, 10);
		cout << "Items";
		set(60, 10);
		cout << "Status";
		set(80, 10);
		cout << "Actions";
		set(10, 11);
		line();
		set(20, 17);
		cout << "Turns: " << turn;
		
			set(20, 13);
			if (cachedPok[chose].Debuff != 2) {
				cout << "Mana: " << mana;
			}
			else cout << "Stunned";
			if (mana == 7) cout << " (max)";
			set(22, 15);
			cout << "HP: ";
			for (int i = 0; i < 4; i++) {
				cout << ' ';
			}
			set(26, 15);
			cout << cachedPok[chose].HP;
			set(18 + command * 20, 10);
			cout << '>';
			input = _getch();
			switch (tolower(input)) {
			case 'd': {
				set(18 + command * 20, 10);
				cout << ' ';
				command++;
				if (command > 3) command = 0;
				break;
			}
			case 'a': {
				set(18 + command * 20, 10);
				cout << ' ';
				command--;
				if (command < 0) command = 3;
				break;
			}
			case 'x': {
				switch (command) {
				case 0: {
					if (cachedPok[chose].Debuff != 2) {
						set(18 + command * 20, 10);
						cout << ' ';
						turn += ataka(pain, cachedPok);
					}
					else {
						set(10, 8);
						cout << "Cannot use yet";
					}
					break;
				}
				case 1: {
					set(18 + command * 20, 10);
					cout << ' ';
					inventory(item, pain, cachedPok);
					break;
				}
				case 2: {
					statusCheck(pain, cachedPok);
					break;
				}
				case 3: {
					chose = actions(item, enemy, cachedPok);
					break;
				}
				}

				}
			}
		}
		posEffects(cachedPok);
		negEffects(pain, cachedPok);
		if (enemy[3] > 0 && esc == false) {
			enemyAttack(pain, cachedPok);
		}
		dead(cachedPok);
	}
	if (esc == false) {
		return (rand() % 10 + 5);
	}
	else return 0;
}
