#include "../includes/Chess.hpp"

void Board::HandleEvents()
{
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			quit = true;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
			quit = true;
		else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
		{
			dragging = true;
			dragStart.x = e.button.x;
			dragStart.y = e.button.y;
			// std::cout << "Drag started at (" << dragStart.x << ", " << dragStart.y << ")" << std::endl;
		}
		else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
		{
			dragging = false;
			dragEnd.x = e.button.x;
			dragEnd.y = e.button.y;
			if (dragStart.x == dragEnd.x && dragStart.y == dragEnd.y)
				suggestions(dragStart);
			else
			{
				PlayerMove.first = dragStart.y / 100 * 8 + dragStart.x / 100;
				PlayerMove.second = dragEnd.y / 100 * 8 + dragEnd.x / 100;
				suggestionsOn = false;
			}
		}
	}
}
void Board::RenderBoard()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			SDL_Rect rect = { j * 100, i * 100, 100, 100 };
			if (!((i + j) % 2))
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			else
				SDL_SetRenderDrawColor(renderer, 0x30, 0x30, 0x30, 0xFF);
			SDL_RenderFillRect(renderer, &rect);
		}
	}

	PrintBoard();
	SDL_RenderPresent(renderer);
}
void Board::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		exit(1);
	}
	// Create a window
	window = SDL_CreateWindow("Chess Engine",
											SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											800, 800,
											SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	// Create a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(1);
	}
}
void Board::suggestions(SDL_Point dragStart)
{
	cout << suggestionsOn << endl;
	if (suggestionsOn)
	{
		RenderBoard();
		suggestionsOn = false;
	}
	vector<pair<int, int>> moves;
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
	int from = dragStart.y / 100 * 8 + dragStart.x / 100;
	t_piece *piece = Check_Piece(*this, from);

	if (piece != nullptr && piece->is_white == false)
	{
		moves = PieceMoves(*this, *piece, from);
		if (moves.empty())
			return;
		for (auto move : moves)
		{
			int x = (move.second % 8) * 100;
			int y = (move.second / 8) * 100;
			SDL_Rect rect = {x, y, 100, 100};
			SDL_RenderFillRect(renderer, &rect);
		}
		suggestionsOn = true;
	}

	SDL_RenderPresent(renderer);
}