#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include "chess.hpp"
/// @brief This is the class of a chessboard of 7 * 7 with the following shape:
///     1 1 1
///     1 1 1
/// 1 1 1 1 1 1 1
/// 1 1 1 1 1 1 1
/// 1 1 1 1 1 1 1
///     1 1 1
///     1 1 1
/// where 1 represents the valid place and space represents invalid places (i.e. out of the chessboard)
/// each block is a pointer to a chess. It points to a chess if there is a chess and points to nullptr if there is no chess or the place is not valid
class chessboard
{
    private:
    int cols = 7;
    int rows = 7;
    /// @brief A board containing the pointers to all the chesses
    chess ***board;
    /// @brief This variable represents the coordinate of the selected chess. It will be nullptr if no chess is selected
    int *selected_chess = nullptr;
    public:
    chessboard(int rows = 7, int cols = 7);
    /// @brief given a coordinate, it will return true if the coordinate is in the chessboard(i.e. a valid coordinate)
    /// @param row 
    /// @param col 
    /// @return 
    bool is_inbound(int row, int col) const;
    /// @brief Get the board
    /// @return 
    chess ***get_board() const;
    /// @brief Get the pointer to the chess according to the input coord
    /// @param row 
    /// @param col 
    /// @return 
    chess *get_chess(int row, int col) const;
    /// @brief This function will return all the possible blocks that the given chess can go to; Remember to delete after finishing using them!
    /// @return A 2-dimensional array of 4 * 2 containing the coordinates of all the possible possible target blocks in the sequence of north, east, south, west, and the corresponding coordinate will be nullptr if the block is not reachable. nullptr if there isn't any. 
    int **get_possible_blocks(int row, int col) const;
    /// @brief This function will select the chess in the given coordinate
    /// @param row 
    /// @param col 
    /// @return True if successfully selected; false if the given coordinate is invalid or there already exits a selected chess
    bool select(int row, int col);
    /// @brief Set the selected chess to nullptr
    void unselect();
    // /// @brief This function will return the coordinate of the selected chess
    // /// @return A 1-dimensional array in the form of [row, col] of the selected chess, nullptr if no selected chess.
    // int *get_selected_chess() const;

    /// @brief This function will print the board. Empty space represents no chess, # represents chess, * represents selected chess (if any), and @ represents the possible blocks the selected chess can go to (if any) 
    void print_board() const;
    /// @brief This function will check whether the selected chess can move to the target place according to the rule of the game.
    /// @param row 
    /// @param col 
    /// @return Return true if movable; 
    /// @return return false if not movable or the input coordinate is invalid or there is no selected chess
    bool is_movable(int row, int col) const;
    /// @brief This function will delete the chess at the given block, even if it is nullptr.
    /// @param row 
    /// @param col 
    void delete_chess(int row, int col);
    /// @brief This is the key function; It will move the selected chess to the target block and do the following according to the rule:
    /// @brief 1. Set the target block to be the pointer to the selected chess, change the coordinate of the selected chess to the new target
    /// @brief 2. Set the original block to nullptr
    /// @brief 3. Delete the chess that it jumps over and set the corresponding block to nullptr
    /// @param row 
    /// @param col 
    /// @return true if successfully moved and false if fail to move
    bool move(int row, int col);
    /// @brief Determine whether the game is end, i.e. no chess is movable.
    /// @return 
    bool is_end_game() const;



};

#endif