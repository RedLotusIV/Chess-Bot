#include "../includes/Chess.hpp"

int main()
{
	Board board;
	bool isWhiteTurn = true;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); // Set to "1" for good quality scaling
	while (!board.quit)
	{
		board.HandleEvents();

		if (isWhiteTurn)
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
			board.MovePiece(from, to);
		}
		else
		{
			vector<pair<int, int>> MovesBlack = board.GenerateMoves(false);
			if (MovesBlack.empty())
			{
				std::cout << "Checkmate! White wins!" << std::endl;
				board.quit = true;
				break;
			}
			int randomIndex = rand() % MovesBlack.size();
			pair<int, int> randomMove = MovesBlack[randomIndex];
			int from[2] = {randomMove.first / 8, randomMove.first % 8};
			int to[2] = {randomMove.second / 8, randomMove.second % 8};
			board.MovePiece(from, to);
		}
		board.RenderBoard();
		SDL_Delay(100);
		isWhiteTurn = !isWhiteTurn;
	}
	SDL_DestroyRenderer(board.renderer);
	SDL_DestroyWindow(board.window);
	SDL_Quit();
	return (0);
}
