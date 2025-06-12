#include "main.hpp"
#include <array>
#include <vector>
#include <iostream>

std::array<std::array<square, 8>, 8> board;

char piece_sprites[7] = {']', 'p', 'b', 'k', 'r', 'q', 'K'};
char team_names[3] = {'[', 'B', 'W'};

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

std::vector<square> get_RowCol_moves(pos src, square src_square, std::vector<square> all_moves);

// calculate all valid moves for a piece then see if dst is one of them
bool validate_move(pos dst, pos src) {

    square dst_square = board[dst.row][dst.col];
    square src_square = board[src.row][src.col];

    bool valid_move = true;

    std::vector<square> all_moves;
    switch (src_square.piece)
    {
    case pawn: //TODO: add en passant, promoting, this only works for one side
        {
            if (board[src.row+1][src.col].piece == empty)
                all_moves.push_back(board[src.row+1][src.col]);

            if (src_square.team  == black) {
                if (board[src.row + 1][src.col + 1].team != src_square.team ) {
                    all_moves.push_back(board[src.row+1][src.col+1]); 
                }
                
                if (board[src.row + 1][src.col - 1].team != src_square.team ) {
                    all_moves.push_back(board[src.row + 1][src.col - 1]); 
                }
            } else if (src_square.team == white) {
                if (board[src.row - 1][src.col + 1].team != src_square.team ) {
                    all_moves.push_back(board[src.row - 1][src.col + 1]); 
                }
                
                if (board[src.row - 1][src.col - 1].team != src_square.team ) {
                    all_moves.push_back(board[src.row - 1][src.col - 1]); 
                }
            }
        }
        break;
    
    case bishop:
        {
            int col = src.col - 1;
            int row = src.row - 1;
            while(row > 0 && col > 0) { // left upper
                if (board[row][col].team != none) {
                    if (board[row][col].team != src_square.team) {
                        all_moves.push_back(board[row][col]);
                    }

                    break;
                }

                all_moves.push_back(board[row][col]);
                row--;
                col--;
            }

            col = src.col + 1;
            row = src.row - 1;
            while(row > 0 && col < BOARD_LENGTH) { // right upper
                if (board[row][col].team != none) {
                    if (board[row][col].team != src_square.team) {
                        all_moves.push_back(board[row][col]);
                    }

                    break;
                }

                all_moves.push_back(board[row][col]);
                row--;
                col++;
            }

            col = src.col - 1;
            row = src.row + 1;
            while(row > 0 && col < BOARD_LENGTH) { //left lower
                if (board[row][col].team != none) {
                    if (board[row][col].team != src_square.team) {
                        all_moves.push_back(board[row][col]);
                    }

                    break;
                }

                all_moves.push_back(board[row][col]);
                row++;
                col--;
            }

            col = src.col + 1;
            row = src.row + 1;
            while(row > 0 && col < BOARD_LENGTH) { //right lower
                if (board[row][col].team != none) {
                    if (board[row][col].team != src_square.team) {
                        all_moves.push_back(board[row][col]);
                    }

                    break;
                }

                all_moves.push_back(board[row][col]);
                row++;
                col++;
            }
        }
        
        break;

    case knight: // theres probably a smarter way to do this
        {
        if (board[src.row + 1][src.col + 2].team != src_square.team) 
            all_moves.push_back(board[src.row + 1][src.col + 2]);
        
        if (board[src.row + 2][src.col + 1].team != src_square.team) 
            all_moves.push_back(board[src.row + 2][src.col + 1]);
        
        if (board[src.row - 1][src.col + 2].team != src_square.team) 
            all_moves.push_back(board[src.row - 1][src.col + 2]);
        
        if (board[src.row - 2][src.col + 1].team != src_square.team) 
            all_moves.push_back(board[src.row - 2][src.col + 1]);
        
        if (board[src.row + 1][src.col - 2].team != src_square.team) 
            all_moves.push_back(board[src.row + 1][src.col - 2]);
        
        if (board[src.row + 2][src.col - 1].team != src_square.team) 
            all_moves.push_back(board[src.row + 2][src.col - 1]);
        
        if (board[src.row - 1][src.col - 2].team != src_square.team) 
            all_moves.push_back(board[src.row - 1][src.col - 2]);
        
        if (board[src.row - 2][src.col - 1].team != src_square.team) 
            all_moves.push_back(board[src.row - 2][src.col - 1]);

        }
        break;

    case rook:
        {
            all_moves = get_RowCol_moves(src, src_square, all_moves);
        }
        break;
    case queen:
        

    
        break;
    
    case king:
        /* code */
        break;
    
    default:
        break;
    }

    return valid_move;


}

std::vector<square> get_RowCol_moves(pos src, square src_square, std::vector<square> all_moves) {

        int col = src.col + 1;
        int row = src.row;
       while(col < BOARD_LENGTH) { // row right
            if (board[row][col].team != none) {
                if (board[row][col].team != src_square.team) {
                    all_moves.push_back(board[row][col]);
                }

                break;
            }

            all_moves.push_back(board[row][col]);
            col++;
        }

        col = src.col - 1;
        row = src.row;
       while(col > 0) { // row left
            if (board[row][col].team != none) {
                if (board[row][col].team != src_square.team) {
                    all_moves.push_back(board[row][col]);
                }

                break;
            }

            all_moves.push_back(board[row][col]);
            col--;
        }

        col = src.col;
        row = src.row - 1;
       while(row > 0) { //col upper
            if (board[row][col].team != none) {
                if (board[row][col].team != src_square.team) {
                    all_moves.push_back(board[row][col]);
                }

                break;
            }

            all_moves.push_back(board[row][col]);
            row--;
        }

        col = src.col;
        row = src.row + 1;
       while(row < BOARD_LENGTH) { // col lower
            if (board[row][col].team != none) {
                if (board[row][col].team != src_square.team) {
                    all_moves.push_back(board[row][col]);
                }

                break;
            }

            all_moves.push_back(board[row][col]);
            row++;
        }

    return all_moves;

}



// Print the current board
void print_board () {
	for (int column = 7; column >= 0; column--) {
		for (int row = 0; row < 8; row++) {
			std::cout << team_names[board[column][row].team] << piece_sprites[board[column][row].piece];
		}
		std::cout << "\n";
	}
}
