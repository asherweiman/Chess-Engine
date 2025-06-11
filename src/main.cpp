#include "main.hpp"
#include <array>
#include <iostream>

std::array<std::array<square, 8>, 8> board;

char piece_sprites[7] = {' ', 'P', 'B', 'K', 'R', 'Q', '^'};
char team_names[3] = {' ', 'B', 'W'};

int main (int argc, char* argv[]) {

	// Fill the board's default starting position
	board[0][0] = {rook, white};
	board[0][1] = {knight, white};
	board[0][2] = {bishop, white};
	board[0][3] = {queen, white};
	board[0][4] = {king, white};
	board[0][5] = {bishop, white};
	board[0][6] = {knight, white};
	board[0][7] = {rook, white};
	board[1].fill({pawn, white});

	for (int row = 2; row < 6; row++) {
		board[row].fill({empty, none});
	}

	board[6].fill({pawn, black});
	board[7][0] = {rook, black};
	board[7][1] = {knight, black};
	board[7][2] = {bishop, black};
	board[7][3] = {queen, black};
	board[7][4] = {king, black};
	board[7][5] = {bishop, black};
	board[7][6] = {knight, black};
	board[7][7] = {rook, black};
	print_board();
}

// Print the current board
void print_board () {
	for (int column = 7; column >= 0; column--) {
		for (int row = 0; row < 8; row++) {
			std::cout << '['<< team_names[board[column][row].team] << piece_sprites[board[column][row].piece] << ']' << "  ";
		}
		std::cout << "\n\n";
	}
}
