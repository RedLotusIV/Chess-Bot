#include "../includes/Chess.hpp"

Board::Board()
{
	// set_from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	set_from_fen("6rk/pp2pp1p/2bb3P/3p2N1/3q3P/8/P1B2P2/7K w - - 0 31");
}

Board::~Board()
{
}

void Board::Board_init()
{
	BoardMap["WhitePawns"] = {0, PAWN, true, false};
	BoardMap["WhiteKnights"] = {0, KNIGHT, true, false};
	BoardMap["WhiteBishops"] = {0, BISHOP, true, false};
	BoardMap["WhiteRooks"] = {0, ROOK, true, false};
	BoardMap["WhiteQueens"] = {0, QUEEN, true, false};
	BoardMap["WhiteKing"] = {0, KING, true, false};
	BoardMap["BlackPawns"] = {0, PAWN, false, false};
	BoardMap["BlackKnights"] = {0, KNIGHT, false, false};
	BoardMap["BlackBishops"] = {0, BISHOP, false, false};
	BoardMap["BlackRooks"] = {0, ROOK, false, false};
	BoardMap["BlackQueens"] = {0, QUEEN, false, false};
	BoardMap["BlackKing"] = {0, KING, false, false};

	BoardMap["White"] = {0, WHITE, true, true};
	BoardMap["Black"] = {0, BLACK, true, true};
	BoardMap["Occupied"] = {0, SPECIAL, false, true};
	BoardMap["Empty"] = {0, SPECIAL, false, true};
}

void Board::SetPiece(U64 &bitboard, int FromSquare, int ToSquare)

{
	U64 tmp = bitboard;
	if ((tmp &= (1ULL << FromSquare)) || (FromSquare == -1))
	{
		if (FromSquare != -1)
			bitboard &= ~(1ULL << FromSquare);
		bitboard |= (1ULL << ToSquare);
	}
	else
	{
		cout << "Wrong Move!" << endl;
		exit(1);
	}
}

t_piece *Board::Check_Piece(Board &board, int square)
{
    if (board.get_white_pawns().Type & (1ULL << square))
        return &board.get_white_pawns();
    else if (board.get_white_knights().Type & (1ULL << square))
        return &board.get_white_knights();
    else if (board.get_white_bishops().Type & (1ULL << square))
        return &board.get_white_bishops();
    else if (board.get_white_rooks().Type & (1ULL << square))
        return &board.get_white_rooks();
    else if (board.get_white_queen().Type & (1ULL << square))
        return &board.get_white_queen();
    else if (board.get_white_king().Type & (1ULL << square))
        return &board.get_white_king();
    else if (board.get_black_pawns().Type & (1ULL << square))
        return &board.get_black_pawns();
    else if (board.get_black_knights().Type & (1ULL << square))
        return &board.get_black_knights();
    else if (board.get_black_bishops().Type & (1ULL << square))
        return &board.get_black_bishops();
    else if (board.get_black_rooks().Type & (1ULL << square))
        return &board.get_black_rooks();
    else if (board.get_black_queen().Type & (1ULL << square))
        return &board.get_black_queen();
    else if (board.get_black_king().Type & (1ULL << square))
        return &board.get_black_king();
    else
		return (nullptr);
}

void Board::MovePiece(int from[2], int to[2])
{
	int	fromSquare = from[0] * 8 + from[1];
	int	toSquare = to[0] * 8 + to[1];
	t_piece &pieceBitboard = *Check_Piece(*this, fromSquare);
	if (IsValidMove(fromSquare, toSquare, *this, pieceBitboard) == false)
		return ;
	// before making the move we need to check if there is a piece on the from square
	// need to check if the piece on the from and after are not the same color
	// if they are the same color then we need to return an error
	// then check the type of the piece and only make the move if its legal aka:
	// the move is in the moveset of the piece and it doesn't go outside the board
	// then we need to check if the move is not blocked by another piece
	// a pawn can only move forward and capture diagonally
	// a knight can move in an L shape
	// a bishop can move diagonally in any direction till it hits another piece
	// a rook can move horizontally or vertically till it hits another piece
	// a queen can move horizontally, vertically, or diagonally till it hits another piece
	// a king can move in any direction but only one square
	// if a king is in check then it can only move to a square that is not under attack
	// if a king is in checkmate then the game is over
	UnsetOthers(*this, toSquare);
	SetPiece(pieceBitboard.Type, fromSquare, toSquare);
	if (pieceBitboard.is_white)
	{
		BoardMap["White"].Type |= (1ULL << toSquare);
		BoardMap["White"].Type &= ~(1ULL << fromSquare);
	}
	else
	{
		BoardMap["Black"].Type |= (1ULL << toSquare);
		BoardMap["Black"].Type &= ~(1ULL << fromSquare);
	}

	BoardMap["Occupied"].Type |= (1ULL << toSquare);
    BoardMap["Occupied"].Type &= ~(1ULL << fromSquare);
    BoardMap["Empty"].Type = ~BoardMap["Occupied"].Type;
}

void	Board::UnsetOthers(Board &board, int Square)
{
	if (board.get_white_pawns().Type & (1ULL << Square))
		board.BoardMap["WhitePawns"].Type &= ~(1ULL << Square);
    else if (board.get_white_knights().Type & (1ULL << Square))
		board.BoardMap["WhiteKnights"].Type &= ~(1ULL << Square);
    else if (board.get_white_bishops().Type & (1ULL << Square))
		board.BoardMap["WhiteBishops"].Type &= ~(1ULL << Square);
    else if (board.get_white_rooks().Type & (1ULL << Square))
		board.BoardMap["WhiteRooks"].Type &= ~(1ULL << Square);
    else if (board.get_white_queen().Type & (1ULL << Square))
		board.BoardMap["WhiteQueens"].Type &= ~(1ULL << Square);
    else if (board.get_white_king().Type & (1ULL << Square))
		board.BoardMap["WhiteKing"].Type &= ~(1ULL << Square);
	else if (board.get_black_pawns().Type & (1ULL << Square))
		board.BoardMap["BlackPawns"].Type &= ~(1ULL << Square);
	else if (board.get_black_knights().Type & (1ULL << Square))
		board.BoardMap["BlackKnights"].Type &= ~(1ULL << Square);
	else if (board.get_black_bishops().Type & (1ULL << Square))
		board.BoardMap["BlackBishops"].Type &= ~(1ULL << Square);
	else if (board.get_black_rooks().Type & (1ULL << Square))
		board.BoardMap["BlackRooks"].Type &= ~(1ULL << Square);
	else if (board.get_black_queen().Type & (1ULL << Square))
		board.BoardMap["BlackQueens"].Type &= ~(1ULL << Square);
	else if (board.get_black_king().Type & (1ULL << Square))
		board.BoardMap["BlackKing"].Type &= ~(1ULL << Square);

	if (board.BoardMap["Black"].Type & (1ULL >> Square))
		board.BoardMap["Black"].Type &= ~(1ULL >> Square);
	else if (board.BoardMap["White"].Type & (1ULL >> Square))
		board.BoardMap["White"].Type &= ~(1ULL >> Square);
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
            if (BoardMap["WhitePawns"].Type & (1ULL << square)) // If there is a white pawn on this square
                cout << "P ";
            else if (BoardMap["WhiteKnights"].Type & (1ULL << square))
                cout << "N ";
            else if (BoardMap["WhiteBishops"].Type & (1ULL << square))
                cout << "B ";
            else if (BoardMap["WhiteRooks"].Type & (1ULL << square))
                cout << "R ";
            else if (BoardMap["WhiteQueens"].Type & (1ULL << square))
                cout << "Q ";
            else if (BoardMap["WhiteKing"].Type & (1ULL << square))
                cout << "K ";
            else if (BoardMap["BlackPawns"].Type & (1ULL << square))
                cout << "p ";
            else if (BoardMap["BlackKnights"].Type & (1ULL << square))
                cout << "n ";
            else if (BoardMap["BlackBishops"].Type & (1ULL << square))
                cout << "b ";
            else if (BoardMap["BlackRooks"].Type & (1ULL << square))
                cout << "r ";
            else if (BoardMap["BlackQueens"].Type & (1ULL << square))
                cout << "q ";
            else if (BoardMap["BlackKing"].Type & (1ULL << square))
                cout << "k ";
            else
                cout << ". "; // Empty square
        }
        cout << endl;
	}
}

vector<pair<int, int>> Board::GenerateMoves(bool isWhite)
{
	vector<pair<int, int>> moves;
	for (int square = 0; square < 64; ++square)
	{
		t_piece* piece = Check_Piece(*this, square);
		if (piece && piece->is_white == isWhite)
		{
			cout << "Piece: ";
			switch (piece->piece_type)
			{
				case PAWN:
					cout << "Pawn";
					break;
				case KNIGHT:
					cout << "Knight";
					break;
				case BISHOP:
					cout << "Bishop";
					break;
				case ROOK:
					cout << "Rook";
					break;
				case QUEEN:
					cout << "Queen";
					break;
				case KING:
					cout << "King";
					break;
				default:
					cout << "Unknown";
					break;
			}
			switch (piece->is_white)
			{
				case true:
					cout << " is White " << endl;
					break;
				case false:
					cout << " is Black " << endl;
					break;
			}
		}
		if (piece && piece->is_white == isWhite)
		{
			for (int to = 0; to < 64; ++to)
			{
				if (IsLegalMove(square, to, *this, *piece))
				{
					moves.push_back({square, to});
					cout << "Move from: " << square << " to: " << to << endl;
				}
			}
		}
	}
	cout << "all moves are "<< moves.size() << endl;
	return (moves);
}