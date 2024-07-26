#include "../includes/Chess.hpp"

Board::Board()
{
	Board_init();
}

Board::~Board()
{
}

void Board::Board_init()
{
	/*
	board example:
	   a b c d e f g h

	8  r n b q k b n r
	7  p p p p p p p p
	6  . . . . . . . .
	5  . . . . . . . .
	4  . . . . . . . .
	3  . . . . . . . .
	2  P P P P P P P P
	1  r n b q k b n r
	*/
	BoardMap["Black"] = 0xFFFF000000000000;
	BoardMap["White"] = 0x000000000000FFFF;
	BoardMap["WhitePawns"] = 0x000000000000FF00;
	BoardMap["WhiteKnights"] = 0x0000000000000042;
	BoardMap["WhiteBishops"] = 0x0000000000000024;
	BoardMap["WhiteRooks"] = 0x0000000000000081;
	BoardMap["WhiteQueens"] = 0x0000000000000008;
	BoardMap["WhiteKing"] = 0x0000000000000010;
	BoardMap["BlackPawns"] = 0x00FF000000000000;
	BoardMap["BlackKnights"] = 0x4200000000000000;
	BoardMap["BlackBishops"] = 0x2400000000000000;
	BoardMap["BlackRooks"] = 0x8100000000000000;
	BoardMap["BlackQueens"] = 0x0800000000000000;
	BoardMap["BlackKing"] = 0x1000000000000000;
	BoardMap["Occupied"] = BoardMap["Black"] | BoardMap["White"];
	BoardMap["Empty"] = ~BoardMap["Occupied"];
}

void Board::SetPiece(U64 &bitboard, int FromSquare, int ToSquare)

{
	U64 tmp = bitboard;
	if (tmp &= (1ULL << FromSquare))
	{
		bitboard &= ~(1ULL << FromSquare);
		bitboard |= (1ULL << ToSquare);
	}
	else
	{
		cout << "Wrong Move!" << endl;
		exit(1);
	}
}

U64 &Board::Check_Piece(Board &board, int square) {
    if (board.get_white_pawns() & (1ULL << square))
        return board.get_white_pawns();
    else if (board.get_white_knights() & (1ULL << square))
        return board.get_white_knights();
    else if (board.get_white_bishops() & (1ULL << square))
        return board.get_white_bishops();
    else if (board.get_white_rooks() & (1ULL << square))
        return board.get_white_rooks();
    else if (board.get_white_queen() & (1ULL << square))
        return board.get_white_queen();
    else if (board.get_white_king() & (1ULL << square))
        return board.get_white_king();
    else if (board.get_black_pawns() & (1ULL << square))
        return board.get_black_pawns();
    else if (board.get_black_knights() & (1ULL << square))
        return board.get_black_knights();
    else if (board.get_black_bishops() & (1ULL << square))
        return board.get_black_bishops();
    else if (board.get_black_rooks() & (1ULL << square))
        return board.get_black_rooks();
    else if (board.get_black_queen() & (1ULL << square))
        return board.get_black_queen();
    else if (board.get_black_king() & (1ULL << square))
        return board.get_black_king();
    else
    {
		cout << "No piece on this square!" << endl;
		exit(1);
    }
}

void Board::MovePiece(int from[2], int to[2])
{
	int fromSquare = from[0] * 8 + from[1];
	int toSquare = to[0] * 8 + to[1];
	U64 &pieceBitboard = Check_Piece(*this, fromSquare);
	UnsetOthers(*this, toSquare);
	SetPiece(pieceBitboard, fromSquare, toSquare);
	BoardMap["Occupied"] |= (1ULL << toSquare);
    BoardMap["Occupied"] &= ~(1ULL << fromSquare);
    BoardMap["Empty"] = ~BoardMap["Occupied"];
}

void	Board::UnsetOthers(Board &board, int Square)
{
	if (board.get_white_pawns() & (1ULL << Square))
		board.BoardMap["WhitePawns"] &= ~(1ULL << Square);
    else if (board.get_white_knights() & (1ULL << Square))
		board.BoardMap["WhiteKnights"] &= ~(1ULL << Square);
    else if (board.get_white_bishops() & (1ULL << Square))
		board.BoardMap["WhiteBishops"] &= ~(1ULL << Square);
    else if (board.get_white_rooks() & (1ULL << Square))
		board.BoardMap["WhiteRooks"] &= ~(1ULL << Square);
    else if (board.get_white_queen() & (1ULL << Square))
		board.BoardMap["WhiteQueens"] &= ~(1ULL << Square);
    else if (board.get_white_king() & (1ULL << Square))
		board.BoardMap["WhiteKing"] &= ~(1ULL << Square);
    else if (board.get_black_pawns() & (1ULL << Square))
		board.BoardMap["BlackPawns"] &= ~(1ULL << Square);
    else if (board.get_black_knights() & (1ULL << Square))
		board.BoardMap["BlackKnights"] &= ~(1ULL << Square);
    else if (board.get_black_bishops() & (1ULL << Square))
		board.BoardMap["BlackBishops"] &= ~(1ULL << Square);
    else if (board.get_black_rooks() & (1ULL << Square))
		board.BoardMap["BlackRooks"] &= ~(1ULL << Square);
    else if (board.get_black_queen() & (1ULL << Square))
		board.BoardMap["BlackQueens"] &= ~(1ULL << Square);
    else if (board.get_black_king() & (1ULL << Square))
		board.BoardMap["BlackKing"] &= ~(1ULL << Square);
	return ;
}

void Board::PrintBoard()
{
	cout << "  a b c d e f g h" << endl;
    for (int i = 7; i >= 0; i--)  // Start from the top row (rank 8) and go down to the bottom row (rank 1)
    {
        cout << i + 1 << " ";
        for (int j = 0; j <= 7; j++) // Start from the leftmost file (file a) and go right to the rightmost file (file h)
        {
            int square = i * 8 + j; // 0 to 63
            if (BoardMap["WhitePawns"] & (1ULL << square)) // If there is a white pawn on this square
                cout << "P ";
            else if (BoardMap["WhiteKnights"] & (1ULL << square))
                cout << "N ";
            else if (BoardMap["WhiteBishops"] & (1ULL << square))
                cout << "B ";
            else if (BoardMap["WhiteRooks"] & (1ULL << square))
                cout << "R ";
            else if (BoardMap["WhiteQueens"] & (1ULL << square))
                cout << "Q ";
            else if (BoardMap["WhiteKing"] & (1ULL << square))
                cout << "K ";
            else if (BoardMap["BlackPawns"] & (1ULL << square))
                cout << "p ";
            else if (BoardMap["BlackKnights"] & (1ULL << square))
                cout << "n ";
            else if (BoardMap["BlackBishops"] & (1ULL << square))
                cout << "b ";
            else if (BoardMap["BlackRooks"] & (1ULL << square))
                cout << "r ";
            else if (BoardMap["BlackQueens"] & (1ULL << square))
                cout << "q ";
            else if (BoardMap["BlackKing"] & (1ULL << square))
                cout << "k ";
            else
                cout << ". "; // Empty square
        }
        cout << endl;
	}
}

