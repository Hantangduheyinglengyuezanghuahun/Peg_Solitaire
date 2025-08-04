#include "chess_board.hpp"

int main()
{
    chessboard board = chessboard();
    board.print_board();
    board.select(1, 3);
    board.print_board();
    board.move(3, 3);
    board.print_board();
    board.unselect();
    board.print_board();
    board.select(4,3);
    board.print_board();
    board.move(2, 3);
    board.print_board();
}