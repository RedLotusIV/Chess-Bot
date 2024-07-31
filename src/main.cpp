#include <bits/stdc++.h>

#include "../includes/Chess.hpp"

int main()
{
	Board board;
	board.PrintBoard();
	while (true) {
		vector<pair<int, int>> MovesWhite = board.GenerateMoves(true);
		if (MovesWhite.empty()) {
			std::cout << "Checkmate! Black wins!" << std::endl;
			break;
		}
		int randomIndex = rand() % MovesWhite.size();
		pair<int, int> randomMove = MovesWhite[randomIndex];
		int from[2] = {randomMove.first / 8, randomMove.first % 8};
		int to[2] = {randomMove.second / 8, randomMove.second % 8};
		cout << "White moves from " << from[0] + 1 << " " << from[1]+ 1  << " to " << to[0] + 1 << " " << to[1] + 1 << endl;
		board.MovePiece(from, to);
		board.PrintBoard();
		vector<pair<int, int>> MovesBlack = board.GenerateMoves(false);
		if (MovesBlack.empty()) {
			std::cout << "Checkmate! White wins!" << std::endl;
			break;
		}
		randomIndex = rand() % MovesBlack.size();
		randomMove = MovesBlack[randomIndex];
		from[0] = randomMove.first / 8;
		from[1] = randomMove.first % 8;
		to[0] = randomMove.second / 8;
		to[1] = randomMove.second % 8;
		cout << "Black moves from " << from[0] + 1 << " " << from[1] + 1 << " to " << to[0] + 1 << " " << to[1] + 1 << endl;
		board.MovePiece(from, to);
		board.PrintBoard();
    }
}
