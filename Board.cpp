#include "Board.h"

static void initRandomSeed() {
	static bool _initialized = false;
	if (!_initialized) {
		srand(int(time(nullptr)));
		rand();   // BUGFIX: throwaway call to get randomness going
		_initialized = true;
	}
}


double randomReal(double low, double high) {
	initRandomSeed();
	double d = rand() / (double(RAND_MAX) + 1);
	double s = d * (high - low);
	return low + s;
}


bool randomChance(double p) {
	initRandomSeed();
	return randomReal(0, 1) < p;
}


Board::Board()
{
	rows = 20;
	cols = 20;

	for (int i = 0; i < rows + 2; i++) {
		std::vector <char> vect;
		for (int j = 0; j < cols + 2; j++) {
			vect.push_back(empty);
		}
		grid.push_back(vect);
	}
	
	for (int i = 1; i < rows + 1; i++) {
		for (int j = 1; j < cols + 1; j++) {
			if (randomChance(0.5)) {
				continue;
			}
			else if (randomChance(0.2)) {
				grid[i][j] = playerA;
				continue;
			}
			else {
				grid[i][j] = playerB;
				continue;
			}
		}
	}
}

Board::~Board()
{
}

int Board::count_neighbours(char player, int i, int j) {
	int counter = 0;

	for (int m = -1; m < 2; m++) {
		for (int n = -1; n < 2; n++) {
			if ((m == 0) && (n == 0)) {
				continue;
			}
			if (grid[i + m][j + n] == player){
				counter++;
			}
		}
	}

	return counter;
}

void Board::birth_rules(char first, char second, int i, int j) {

	int first_neighbours = count_neighbours(first, i, j);
	int second_neighbours = count_neighbours(second, i, j);

	//Rule #1
	if ((first_neighbours == 3) && (second_neighbours != 3)){
		grid[i][j] = first;			//cell is born
		return;
	}

	//Rule #2
	if ((first_neighbours == 3) && (second_neighbours == 3)) {
		if (randomChance(0.5)) {
			grid[i][j] = first;		//cell is born
			return;
		}
		else {
			grid[i][j] = second;		//cell is born
			return;
		}
	}
}


void Board::survival_rules(char first, char second, int i, int j) {
	int first_neighbours = count_neighbours(first, i, j);
	int second_neighbours = count_neighbours(second, i, j);
	
	//Rule #1
	if ((abs(first_neighbours - second_neighbours) == 3) ||
		(abs(first_neighbours - second_neighbours) == 2)) {
		return;
	}
	else if ((abs(first_neighbours - second_neighbours) == 1) &&
		(first_neighbours >= 2)) {
		return;
	}
	else {
		grid[i][j] = empty;		//cell dies
		return;
	}
}


void Board::update() {
	for (int i = 1; i < rows + 1; i++) {
		for (int j = 1; j < cols + 1; j++) {
			if (grid[i][j] == empty) {
				birth_rules(playerA, playerA, i, j);
				continue;
			}
			else if (grid[i][j] == playerA) {
				survival_rules(playerA, playerB, i, j);
				continue;
			}
			else if (grid[i][j] == playerB) {
				survival_rules(playerB, playerA, i, j);
				continue;
			}
		}
	}
}

void Board::print() {
	for (int i = 1; i < rows + 1; i++) {
		for (int j = 1; j < cols + 1; j++) {
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	Sleep(1000);
	system("CLS");
}