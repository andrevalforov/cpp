#include "Headers.h"
#include "variables.h"

using namespace std;
char tmp_map[18][32];

char map[18][32] = {
	"+#############################+",
	"|                             |",
	"|                             |",
	"|## ########### ##   #########|",
	"|   |                         |",
	"| | |### |  |           |     |",
	"| |      |  | |###  |   |  |  |",
	"| | #####|  | |      ## |     |",
	"| |           |###  |      |  |",
	"| |##### ###         ##       |",
	"|          ######  ####### ###|",
	"|                             |",
	"|# ### ####      ###   #######|",
	"|                             |",
	"|                             |",
	"|                             |",
	"|                             |",
	"+#############################+"
};

void ShowMap()
{
	for (int i = 0; i < 18; i++) {
		printf("%s\n", map[i]);
	}
}

void gotoXY(short x, short y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y }; //структура з полями Х і У

	SetConsoleCursorPosition(hStdout, position);
}



vector<target> walk_queue;

vector<walk> BFSArray;

void AddArray(int x, int y, int wc, int back) {
	if (tmp_map[y][x] == ' ' || tmp_map[y][x] == '.') {
		tmp_map[y][x] = '#';
		walk tmp;
		tmp.x = x;
		tmp.y = y;
		tmp.walk_count = wc;
		tmp.back = back;
		BFSArray.push_back(tmp);
	}
}

void FindPath(int sx, int sy, int x, int y) {  //пошук шляху
	memcpy(tmp_map, map, sizeof(map));
	BFSArray.clear();
	walk tmp;
	tmp.x = sx;
	tmp.y = sy;
	tmp.walk_count = 0;
	tmp.back = -1;
	BFSArray.push_back(tmp);

	int i = 0;
	while (i < BFSArray.size()) {
		if (BFSArray[i].x == x && BFSArray[i].y == y) {
			walk_queue.clear();
			target tmp2;
			while (BFSArray[i].walk_count != 0) {
				tmp2.x = BFSArray[i].x;
				tmp2.y = BFSArray[i].y;
				walk_queue.push_back(tmp2);

				i = BFSArray[i].back;
			}

			break;
		}

		AddArray(BFSArray[i].x + 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
		AddArray(BFSArray[i].x - 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
		AddArray(BFSArray[i].x, BFSArray[i].y + 1, BFSArray[i].walk_count + 1, i);
		AddArray(BFSArray[i].x, BFSArray[i].y - 1, BFSArray[i].walk_count + 1, i);

		
		i++;
	}

	BFSArray.clear();
}


int main()
{
	bool running = true;
	int x = 15; // hero x
	int y = 16; // hero y
	int old_x;
	int old_y;

	int ex = 1;
	int ey = 1;


	int score = 0;
	cout << "      ||==       //\\\\       ====  ||\\\\    //||     //\\\\     ||\\\\    ||\n" << 
		    "      ||   \\\\   //  \\\\    ||      || \\\\  // ||    //  \\\\    || \\\\   ||\n" << 
		    "      ||   //  //====\\\\   ||      ||  \\\\//  ||   //====\\\\   ||  \\\\  ||\n" << 
		    "      ||==    //      \\\\  ||      ||        ||  //      \\\\  ||   \\\\ ||\n" << 
	    	"      ||     //        \\\\   ====  ||        || //        \\\\ ||    \\\\||\n\n";
	cout << "\t\t\t   ..::GAME PACMAN::..\n\t\t\tPowered by Andrii Alforov\n";
	cout << "Instruction:\n1. Arrow Keys to move your hero\n2. Eat the dots produced by the Eater to gain poins\n3. Don't get caught by the Eater\n\n";
	cout << "H -> Hard\nN -> Normal\nE -> Easy\n\nInput : ";

	char diffi;
	int speedmod = 3;

	cin >> diffi;

	if (diffi == 'N') {
		speedmod = 2;
	}
	else if (diffi == 'H') {
		speedmod = 1;
	}

	system("cls");
	ShowMap();

	gotoXY(x, y); cout << "H";

	int frame = 0;

	FindPath(ex, ey, x, y);

	while (running) {
		gotoXY(x, y); cout << " ";

		old_x = x;
		old_y = y;

		if (GetAsyncKeyState(VK_UP)) {                 //зчитування стрілок
			if (map[y - 1][x] == '.') { y--; score++; }
			else
				if (map[y - 1][x] == ' ') y--;
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			if (map[y + 1][x] == '.') { y++; score++; }
			else
				if (map[y + 1][x] == ' ') y++;
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			if (map[y][x - 1] == '.') { x--; score++; }
			else
				if (map[y][x - 1] == ' ') x--;
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			if (map[y][x + 1] == '.') { x++; score++; }
			else
				if (map[y][x + 1] == ' ') x++;
		}

		if (old_x != x || old_y != y) {
			FindPath(ex, ey, x, y);
		}

		gotoXY(x, y); cout << "H";

		map[ey][ex] = '.';
		gotoXY(ex, ey); cout << ".";

		if (frame%speedmod == 0 && walk_queue.size() != 0) {
			ex = walk_queue.back().x;
			ey = walk_queue.back().y;
			walk_queue.pop_back();
		}

		gotoXY(ex, ey); cout << "E";

		if (ex == x && ey == y) {
			break;
		}


		gotoXY(32, 18);
		gotoXY(32, 1); cout << score;
		Sleep(100);
		frame++;
	}

	system("cls");
	printf("You Lose and your score is : %i", score);
	cin.get();
	

	return 0;
}
