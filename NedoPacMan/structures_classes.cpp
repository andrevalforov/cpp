class entity { //об*єкт
public:
	entity(int x, int y) {
		this->x = x; //вказує на адресу створеного об*єкта
		this->y = y;
	}

	void move_x(int p) {
		if (map[y][x + p] == ' ') x += p;
	}

	void move_y(int p) {
		if (map[y + p][x] == ' ') y += p;
	}

	void move(int p, int q) {
		x += p;
		y += q;
	}

	int get_x() { return x; }
	int get_y() { return y; }

	void draw(char p) {
		map[x][y] = p;
		gotoXY(x, y); printf("%c", p);
	}

private:
	int x;
	int y;
};

struct walk {
	short walk_count;
	short x;
	short y;
	short back;
};

struct target { //ціль
	short x;
	short y;
};