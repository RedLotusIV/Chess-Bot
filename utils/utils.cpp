#include "../includes/Chess.hpp"

int file_to_int(char file)
{
	switch (file)
	{
		case 'a':
			return (0);
		case 'b':
			return (1);
		case 'c':
			return (2);
		case 'd':
			return (3);
		case 'e':
			return (4);
		case 'f':
			return (5);
		case 'g':
			return (6);
		case 'h':
			return (7);
		default:
			return (-1);
	}
}

void Board::set_piece_from_fen(char ch, int square)
{
	bool is_white = isupper(ch);
	switch (tolower(ch))
	{
		case 'p':
			SetPiece(is_white ? BoardMap["WhitePawns"].Type : BoardMap["BlackPawns"].Type, -1, square);
			break;
		case 'n':
			SetPiece(is_white ? BoardMap["WhiteKnights"].Type : BoardMap["BlackKnights"].Type, -1, square);
			break;
		case 'b':
			SetPiece(is_white ? BoardMap["WhiteBishops"].Type : BoardMap["BlackBishops"].Type, -1, square);
			break;
		case 'r':
			SetPiece(is_white ? BoardMap["WhiteRooks"].Type : BoardMap["BlackRooks"].Type, -1, square);
			break;
		case 'q':
			SetPiece(is_white ? BoardMap["WhiteQueens"].Type : BoardMap["BlackQueens"].Type, -1, square);
			break;
		case 'k':
			SetPiece(is_white ? BoardMap["WhiteKing"].Type : BoardMap["BlackKing"].Type, -1, square);
			break;
	}
}

void Board::set_from_fen(const string& fen)
{
	Board_init();
	int square = 56;
	for (char ch: fen)
	{
		if (ch == ' ')
			break;
		if (ch == '/')
			square -= 16;
		else if (isdigit(ch))
			square += ch - '0';
		else
		{
			set_piece_from_fen(ch, square);
			square++;
		}
	}
	BoardMap["White"].Type =
		BoardMap["WhitePawns"].Type | 
		BoardMap["WhiteKnights"].Type | 
		BoardMap["WhiteBishops"].Type | 
		BoardMap["WhiteRooks"].Type | 
		BoardMap["WhiteQueens"].Type | 
		BoardMap["WhiteKing"].Type;
	BoardMap["Black"].Type =
		BoardMap["BlackPawns"].Type | 
		BoardMap["BlackKnights"].Type | 
		BoardMap["BlackBishops"].Type | 
		BoardMap["BlackRooks"].Type | 
		BoardMap["BlackQueens"].Type |
		BoardMap["BlackKing"].Type;
	
	BoardMap["Occupied"].Type = BoardMap["Black"].Type | BoardMap["White"].Type;
	BoardMap["Empty"].Type = ~BoardMap["Occupied"].Type;
}

bool Board::isSquareAttacked(int square, bool is_white)
{
	for (int from = 0; from < 64; from++)
	{
		t_piece* piece = this->Check_Piece(from);
		if (piece && piece->is_white != is_white)
		{
			if (IsValidMove(from, square, *this, *piece))
				return (true);
		}
	}
	return (false);
}

bool	file_exists(const char *path)
{
	struct stat buffer;
	return (stat(path, &buffer) == 0);
}

vector<pair<int, int>> PieceMoves(Board &board, t_piece piece, int square)
{
	vector<pair<int, int>> moves;
	for (int to = 0; to < 64; ++to)
	{
		if (IsLegalMove(square, to, board, piece))
			moves.push_back({square, to});
	}
	return (moves);
}
