#ifndef CHESS_H
# define CHESS_H

#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include <map>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cassert>
#include <fstream>
using namespace std;
typedef unsigned long long U64;

class Board
{
	private:
		map<string, U64> BoardMap;
	public:
		Board(void);
		~Board(void);
		void	Board_init(void);
		void	PrintBoard(void);
		void	SetPiece(U64 &bitboard, int FromSquare, int ToSquare);
		void	MovePiece(int from[2], int to[2]);
		void	UnsetOthers(Board &board, int Square);
		U64 	&Check_Piece(Board &board, int square);
		U64		&get_white_pawns(void) { return (BoardMap["WhitePawns"]); }
		U64 	&get_white_rooks(void) { return (BoardMap["WhiteRooks"]); }
		U64 	&get_white_knights(void) { return (BoardMap["WhiteKnights"]); }
		U64 	&get_white_bishops(void) { return (BoardMap["WhiteBishops"]); }
		U64 	&get_white_queen(void) { return (BoardMap["WhiteQueens"]); }
		U64 	&get_white_king(void) { return (BoardMap["WhiteKing"]); }
		U64 	&get_black_pawns(void) { return (BoardMap["BlackPawns"]); }
		U64 	&get_black_rooks(void) { return (BoardMap["BlackRooks"]); }
		U64 	&get_black_knights(void) { return (BoardMap["BlackKnights"]); }
		U64 	&get_black_bishops(void) { return (BoardMap["BlackBishops"]); }
		U64 	&get_black_queen(void) { return (BoardMap["BlackQueens"]); }
		U64 	&get_black_king(void) { return (BoardMap["BlackKing"]); }
};	

int	file_to_int(char file); // a function that converts a file to an integer
U64	&Check_Piece(Board board, int square); // a function that checks the piece on a square
#endif