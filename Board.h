#pragma once

#include "Libraries.h"

class Board
{
private:
	std::vector< std::vector<char> > grid;
	int rows{};
	int cols{};
	char playerA = '@';
	char playerB = '#';
	char empty = '_';

	int count_neighbours(char player, int i, int j);
	void birth_rules(char firstp, char secondp, int i, int j);
	void survival_rules(char firstp, char secondp, int i, int j);

public:
	Board();

	void update();

	void print();
	
	virtual ~Board();

};
