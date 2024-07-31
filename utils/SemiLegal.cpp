#include "../includes/Chess.hpp"

bool IsValidMove(int from, int to, Board &board, t_piece &piece)
{
	// for (int i = 0; i < 64 ; i++)
	// {
	// 	t_piece *king_piece = board.Check_Piece(board, i);
	// 	if (king_piece && king_piece->piece_type == KING && king_piece->is_white == piece.is_white)
	// 	{
	// 		if (board.isSquareAttacked(i, !king_piece->is_white))
	// 			return (false);
	// 		else
	// 			break;
	// 	}
	// }
	switch (piece.piece_type)
	{
		case PAWN:
			return (IsValidPawnMove(from, to, board, piece));
		case KNIGHT:
			return (IsValidKnightMove(from, to, board, piece));
		case BISHOP:
			return (IsValidBishopMove(from, to, board, piece));
		case KING:
			return (IsValidKingMove(from, to, board, piece));
		case ROOK:
			return (IsValidRookMove(from, to, board, piece));
		case QUEEN:
			return (IsValidQueenMove(from, to, board, piece));
		default:
			return (false);
	}
}
bool IsValidPawnMove(int from, int to, Board &board, t_piece &piece)
{
	int direction = piece.is_white ? 8 : -8;
	if (to == from + direction && !((board.Check_Piece(board, to))))
		return (true);
	if ((from / 8 == 1 && piece.is_white) || (from / 8 == 6 && !piece.is_white))
	{
		if (to == from + 2 * direction && !(board.Check_Piece(board, to)) && !(board.Check_Piece(board, to - direction)))
			return (true);
	}
	if (to == from + direction + 1 || ((from % 8) && (to == from + direction - 1)))
	{
		if ((board.Check_Piece(board, to) && board.Check_Piece(board, to)->is_white != piece.is_white))
			return (true);
	}
	// should add en passant
	return (false);
}

bool	IsValidKnightMove(int from, int to, Board &board, t_piece &piece)
{
	int moves[] = {17, 15, 10, 6, -17, -15, -10, -6};
	int fromRow = from / 8;
	int fromCol = from % 8;

	for (int move : moves)
	{
		if (to == from + move)
		{
			int newRow = (from + move) / 8;
			int newCol = (from + move) % 8;
			if (abs(newRow - fromRow) <= 2 && abs(newCol - fromCol) <= 2)
			{
				t_piece own_color = piece.is_white ? board.get_white() : board.get_black();
				if (!(own_color.Type & (1ULL << to)))
					return true;
			}
		}
	}
	return (false);
}

bool	IsValidBishopMove(int from, int to, Board &board, t_piece &piece)
{
	int step = 0;
	int fromRow = from / 8;
	int toRow = to / 8;
	int fromCol = from % 8;
	int toCol = to % 8;
	t_piece own_color = piece.is_white ? board.get_white() : board.get_black();
	int diff = to - from;
	if (!(abs(diff) % 9) || !(abs(diff) % 7))
	{
		if (abs(toRow - fromRow) != abs(toCol - fromCol))
			return (false);
		if (!(abs(diff) % 9))
			step = diff > 0 ? 9 : -9;
		else
			step = diff > 0 ? 7 : -7;
		if (!((from + 1) % 8) && step == 9)
			return (false);
		int current = from + step;
		while (current != to)
		{
			if (board.Check_Piece(board, current))
				return (false);
			current += step;
		}
		if (own_color.Type & (1ULL << to))
			return (false);
		return (true);
	}
	return (false);
}

bool	IsValidKingMove(int from, int to, Board &board, t_piece &piece)
{
	t_piece own_color = piece.is_white ? board.get_white() : board.get_black();
	int moves[] = {1, 9, 8, 7, -1, -9, -8, -7};
	for (int move : moves)
	{
		if (to == from + move && !(own_color.Type & (1ULL << to)))
			return (true);
	}
	return (false);
}

bool	IsValidRookMove(int from, int to, Board &board, t_piece &piece)
{
	int step;
	t_piece own_color = piece.is_white ? board.get_white() : board.get_black();
	int fromRow = from / 8;
	int fromCol = from % 8;
	int toRow = to / 8;
	int toCol = to % 8;

	if (fromRow == toRow)
		step = (to > from) ? 1 : -1;
	else if (fromCol == toCol) 
		step = (to > from) ? 8 : -8;
	else
		return (false);
	int current = from + step;
	while (current != to)
	{
		if (board.Check_Piece(board, current))
			return false;
		current += step;
	}
	if (own_color.Type & (1ULL << to))
		return false;
	return (true);
}
bool	IsValidQueenMove(int from, int to, Board &board, t_piece &piece)
{
	return (IsValidRookMove(from, to, board, piece) || IsValidBishopMove(from, to, board, piece));
}