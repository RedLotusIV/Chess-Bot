#include <bits/stdc++.h>

#include "../includes/Chess.hpp"

int main()
{
	Board board;
	board.PrintBoard();
	int from[2];
	int to[2];
	from[0] = 1;
	from[1] = 0;
	to[0] = 3;
	to[1] = 0;
	board.MovePiece(from, to);
	from[0] = 0;
	from[1] = 0;
	board.MovePiece(from, to);
	board.PrintBoard();
	return (0);
}