enum chess_piece {empty = 0, pawn = 1, bishop = 2, knight = 3, rook = 4, queen = 5, king = 6};
enum chess_team {none = 0, black = 1, white = 2};

#define BOARD_LENGTH 8

struct square {
	chess_piece piece;
	chess_team team;
};

struct pos {
	char row;
	char col;
};


void print_board ();
