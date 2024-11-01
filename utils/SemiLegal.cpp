#include "../includes/Chess.hpp"

typedef bool (*MoveValidator)(int, int, Board&, t_piece&);

bool IsValidPawnMove(int from, int to, Board &board, t_piece &piece);
bool IsValidKnightMove(int from, int to, Board &board, t_piece &piece);
bool IsValidBishopMove(int from, int to, Board &board, t_piece &piece);
bool IsValidRookMove(int from, int to, Board &board, t_piece &piece);
bool IsValidQueenMove(int from, int to, Board &board, t_piece &piece);
bool IsValidKingMove(int from, int to, Board &board, t_piece &piece);

MoveValidator moveValidators[] = {
    IsValidPawnMove,
    IsValidKnightMove,
    IsValidBishopMove,
    IsValidRookMove,
    IsValidQueenMove,
    IsValidKingMove
};

bool IsValidMove(int from, int to, Board &board, t_piece &piece)
{
    if (piece.piece_type >= PAWN && piece.piece_type <= KING)
    {
        return moveValidators[piece.piece_type](from, to, board, piece);
    }
    return false;
}

bool IsValidPawnMove(int from, int to, Board &board, t_piece &piece)
{
    int direction = piece.is_white ? 8 : -8;
    if (to == from + direction && !((board.Check_Piece(to))))
        return (true);
    if ((from / 8 == 1 && piece.is_white) || (from / 8 == 6 && !piece.is_white))
    {
        if (to == from + 2 * direction && !(board.Check_Piece(to)) && !(board.Check_Piece(to - direction)))
            return (true);
    }
    if (to == from + direction + 1 || ((from % 8) && (to == from + direction - 1)))
    {
        if ((board.Check_Piece(to) && board.Check_Piece(to)->is_white != piece.is_white))
            return (true);
    }
    // should add en passant
    return (false);
}

bool IsValidKnightMove(int from, int to, Board &board, t_piece &piece)
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

bool IsValidBishopMove(int from, int to, Board &board, t_piece &piece)
{
    int step = 0;
    int fromRow = from / 8;
    int toRow = to / 8;
    int fromCol = from % 8;
    int toCol = to % 8;
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
            if (board.Check_Piece(current))
                return (false);
            current += step;
        }
        if (board.Check_Piece(to) && board.Check_Piece(to)->is_white == piece.is_white)
            return (false);
        return (true);
    }
    return (false);
}

bool IsValidKingMove(int from, int to, Board &board, t_piece &piece)
{
    int FromArr[2] = {from / 8, from % 8};
    int ToArr[2] = {to / 8, to % 8};
    int moves[] = {1, 9, 8, 7, -1, -9, -8, -7};
    for (int move : moves)
    {
        if (to == from + move && ((board.Check_Piece(to) == nullptr
            || (board.Check_Piece(to) && board.Check_Piece(to)->is_white != piece.is_white)))
            && abs(FromArr[0] - ToArr[0]) <= 1 && abs(FromArr[1] - ToArr[1]) <= 1)
            return (true);
    }
    return (false);
}

bool IsValidRookMove(int from, int to, Board &board, t_piece &piece)
{
    int step;
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
        if (board.Check_Piece(current))
            return false;
        current += step;
    }
    if (board.Check_Piece(to) && board.Check_Piece(to)->is_white == piece.is_white)
        return (false);
    return (true);
}

bool IsValidQueenMove(int from, int to, Board &board, t_piece &piece)
{
    return (IsValidRookMove(from, to, board, piece) || IsValidBishopMove(from, to, board, piece));
}

bool IsLegalMove(int from, int to, Board &board, t_piece &piece)
{
    int FromArr[2] = {from / 8, from % 8};
    int ToArr[2] = {to / 8, to % 8};
    if (IsValidMove(from, to, board, piece))
    {
        Board temp = board;
        temp.MovePiece(FromArr, ToArr);
        for (int i = 0; i < 64; i++)
        {
            t_piece *king_piece = temp.Check_Piece(i);
            if (king_piece && king_piece->piece_type == KING && king_piece->is_white == piece.is_white)
            {
                if (temp.isSquareAttacked(i, king_piece->is_white))
                    return (false);
                else
                    break;
            }
        }
        return (true);
    }
    return (false);
}