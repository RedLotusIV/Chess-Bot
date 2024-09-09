#include "../includes/Chess.hpp"

int main()
{
	Board board;
	bool isWhiteTurn = true;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); // Set to "1" for good quality scaling
	while (!board.quit)
	{
		board.HandleEvents();
		if (isWhiteTurn == true && board.PlayerTurn == false)
		{
			vector<pair<int, int>> MovesWhite = board.GenerateMoves(true);
			if (MovesWhite.empty())
			{
				std::cout << "Checkmate! Black wins!" << std::endl;
				board.quit = true;
				break;
			}
			int randomIndex = rand() % MovesWhite.size();
			pair<int, int> randomMove = MovesWhite[randomIndex];
			int from[2] = {randomMove.first / 8, randomMove.first % 8};
			int to[2] = {randomMove.second / 8, randomMove.second % 8};
			if (board.Check_Piece(board, randomMove.first) && IsLegalMove(randomMove.first, randomMove.second, board,
				*board.Check_Piece(board, randomMove.first)))
			{
				board.MovePiece(from, to);
				board.RenderBoard();
				board.PlayerTurn = true;
			}
		}
		else if (isWhiteTurn == false && board.PlayerTurn == true)
		{

			if (board.PlayerMove.first != -1 && board.PlayerMove.second != -1)
			{
				pair<int, int> move = board.PlayerMove;
				int from[2] = {move.first / 8, move.first % 8};
				int to[2] = {move.second / 8, move.second % 8};
				if (board.Check_Piece(board, move.first) && IsLegalMove(move.first, move.second, board, *board.Check_Piece(board, move.first)))
				{
					board.MovePiece(from, to);
					board.RenderBoard();
					board.PlayerTurn = false;
					board.PlayerMove = make_pair(-1, -1);
				}
			}
		}
		isWhiteTurn = !isWhiteTurn;
	}
	SDL_DestroyRenderer(board.renderer);
	SDL_DestroyWindow(board.window);
	SDL_Quit();
	return (0);
}
