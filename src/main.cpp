#include <bits/stdc++.h>

#include "../includes/Chess.hpp"

int main()
{
	Board board;
	// board.PrintBoard();
	// int from[2];
	// int to[2];
	// from[0] = 1;
	// from[1] = 0;
	// to[0] = 3;
	// to[1] = 0;
	// board.MovePiece(from, to);
	// from[0] = 6;
	// from[1] = 1;
	// to[0] = 4;
	// to[1] = 1;
	// board.MovePiece(from, to);
	// from[0] = 3;
	// from[1] = 0;
	// to[0] = 4;
	// to[1] = 0;
	// board.MovePiece(from, to);
	// from[0] = 0;
	// from[1] = 1;
	// to[0] = 2;
	// to[1] = 2;
	// board.MovePiece(from, to);
	// from[0] = 1;
	// from[1] = 3;
	// to[0] = 3;
	// to[1] = 3;
	// board.MovePiece(from, to);
	// from[0] = 0;
	// from[1] = 2;
	// to[0] = 5;
	// to[1] = 7;
	// board.MovePiece(from, to);
	// from[0] = 5;
	// from[1] = 7;
	// to[0] = 6;
	// to[1] = 6;
	// board.MovePiece(from, to);
	// board.PrintBoard();
	// cout << "----------------" << endl;
	// from[0] = 0;
	// from[1] = 4;
	// to[0] = 1;
	// to[1] = 3;
	// board.MovePiece(from, to);
	// board.PrintBoard();
	// cout << "----------------" << endl;
	// from[0] = 1;
	// from[1] = 3;
	// to[0] = 2;
	// to[1] = 3;
	// board.MovePiece(from, to);
	// board.PrintBoard();
	// cout << "----------------" << endl;
	// from[0] = 2;
	// from[1] = 3;
	// to[0] = 3;
	// to[1] = 3;
	// board.MovePiece(from, to);
	// board.PrintBoard();
	// cout << "----------------" << endl;
	// from[0] = 3;
	// from[1] = 3;
	// to[0] = 4;
	// to[1] = 3;
	// board.MovePiece(from, to);
	// board.PrintBoard();
	// cout << "----------------" << endl;
	// from[0] = 4;
	// from[1] = 3;
	// to[0] = 5;
	// to[1] = 3;
	// board.MovePiece(from, to);
	// board.PrintBoard();
	// cout << "----------------" << endl;
	// from[0] = 5;
	// from[1] = 3;
	// to[0] = 6;
	// to[1] = 3;
	// board.MovePiece(from, to);
	// board.PrintBoard();
	// cout << "----------------" << endl;
	// from[0] = 0;
	// from[1] = 3;
	// to[0] = 0;
	// to[1] = 1;
	// board.MovePiece(from, to);
	// board.PrintBoard();
	// cout << "----------------" << endl;
	// from[0] = 0;
	// from[1] = 1;
	// to[0] = 1;
	// to[1] = 0;
	// board.MovePiece(from, to);
	// board.PrintBoard();
	// cout << "----------------" << endl;
	// from[0] = 1;
	// from[1] = 0;
	// to[0] = 6;
	// to[1] = 5;
	// board.MovePiece(from, to);
	board.PrintBoard();
	// cout << "----------------" << endl;
	vector<pair<int, int>> Moves = board.GenerateMoves(true);
	return (0);
}
