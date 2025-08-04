#include "chess.hpp"

chess::chess(int row, int col)
{
    this->col = col;
    this->row = row;
}

void chess::move(int target_row, int target_col)
{
    this->col = target_col;
    this->row = target_row;
}

int *chess::get_coord() const
{
    int *coord = new int[2];
    coord[0] = this->row;
    coord[1] = this->col;
    return coord;
}

chess::~chess()
{
}

