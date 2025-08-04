#ifndef CHESS_HPP
#define CHESS_HPP

#include <iostream>
using namespace std;


// This is the class of a single chess, which contains only two integers representing the coordinate of 
// this chess, and some methods to move or delete it. 
class chess
{
    private:
    int row;
    int col;

    public:
    chess(int row = 0, int col = 0);
    /// @brief given a valid coordinate, this function will move this chess to the target place
    /// @param target_col 
    /// @param target_row 
    void move(int target_row, int target_col);
    /// @brief This function returns the address of two containing the address of the chess in the form of [row, col]
    /// @return The address of the first element in the array containing the address of the chess. The array is in heap, so remember to delete it if finishing using.
    int *get_coord() const;
    ~chess();
};


#endif