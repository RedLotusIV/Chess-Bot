#ifndef CHESS_H
# define CHESS_H

#include <sys/stat.h>
#include <bits/stdc++.h>
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
#include <cstddef>
#include <SDL2/SDL.h>

using namespace std;
typedef unsigned long long U64;

typedef enum e_piece
{
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING,
	BLACK,
	WHITE,
	SPECIAL
}				t_piece_type;

typedef struct s_piece
{
	U64				Type;
	t_piece_type	piece_type;
	bool			is_white;
	bool			is_special;
}				t_piece;

class Board
{
	private:
		map<string, t_piece>	BoardMap;
		unsigned int			castlingRights;
		int						enPassantSquare;
	public:
		// variables
		SDL_Window*		window = NULL;
		SDL_Renderer*	renderer = NULL;
		bool			quit = false;
		bool			dragging = false;
		bool 			isWhiteTurn = true;
		bool			PlayerTurn = false;
		e_piece			PlayerColor = WHITE;
		pair<int, int>	PlayerMove = make_pair(-1, -1);
		SDL_Event		e;
		SDL_Point		dragStart;
		SDL_Point		dragEnd;
		// functions
		Board(void);
		~Board(void);
		void					Board_init(void);
		void					PrintBoard(void);
		void					SetPiece(U64 &bitboard, int FromSquare, int ToSquare);
		void					MovePiece(int from[2], int to[2]);
		void					UnsetOthers(Board &board, int Square);
		t_piece 				*Check_Piece(Board &board, int square);
		vector<pair<int, int>>	GenerateMoves(bool isWhite);
		void					set_from_fen(const string& fen);
		bool					isSquareAttacked(int square, bool is_white);
		t_piece					&get_white_pawns(void) { return (BoardMap["WhitePawns"]); }
		t_piece 				&get_white_rooks(void) { return (BoardMap["WhiteRooks"]); }
		t_piece 				&get_white_knights(void) { return (BoardMap["WhiteKnights"]); }
		t_piece 				&get_white_bishops(void) { return (BoardMap["WhiteBishops"]); }
		t_piece 				&get_white_queen(void) { return (BoardMap["WhiteQueens"]); }
		t_piece 				&get_white_king(void) { return (BoardMap["WhiteKing"]); }
		t_piece 				&get_black_pawns(void) { return (BoardMap["BlackPawns"]); }
		t_piece 				&get_black_rooks(void) { return (BoardMap["BlackRooks"]); }
		t_piece 				&get_black_knights(void) { return (BoardMap["BlackKnights"]); }
		t_piece 				&get_black_bishops(void) { return (BoardMap["BlackBishops"]); }
		t_piece 				&get_black_queen(void) { return (BoardMap["BlackQueens"]); }
		t_piece 				&get_black_king(void) { return (BoardMap["BlackKing"]); }
		t_piece 				&get_black(void) { return (BoardMap["Black"]);}
		t_piece 				&get_white(void) { return (BoardMap["White"]);}
		// window management
		void					InitSDL();
		void					HandleEvents();
		void					RenderBoard();
		void					suggestions(SDL_Point dragStart);
};	

int						file_to_int(char file); // a function that converts a file to an integer
bool					IsValidMove(int from, int to, Board &board, t_piece &piece); // a function that checks if a move is valid
bool					IsValidPawnMove(int from, int to, Board &board, t_piece &piece); // a function that checks if a pawn move is valid
bool 					IsValidKnightMove(int from, int to, Board &board, t_piece &piece);
bool 					IsValidBishopMove(int from, int to, Board &board, t_piece &piece);
bool 					IsValidRookMove(int from, int to, Board &board, t_piece &piece);
bool 					IsValidQueenMove(int from, int to, Board &board, t_piece &piece);
bool 					IsValidKingMove(int from, int to, Board &board, t_piece &piece);
bool					IsLegalMove(int from, int to, Board &board, t_piece &piece);
bool					file_exists(const char *path);
vector<pair<int, int>>	PieceMoves(Board &board, t_piece piece, int square);
#endif