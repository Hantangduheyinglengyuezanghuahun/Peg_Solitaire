#include "chess_board.hpp"

chessboard::chessboard(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->board = new chess **[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        board[i] = new chess *[this->cols];
        for (int j = 0; j < this->cols; j++)
        {
            if ((i <= 1 && j <= 1) || (i <= 1 && j >= this->cols - 2) || (i >= this->rows - 2 && j <= 1) || (i >= this->rows - 2 && j >= this->cols - 2))
            {
                board[i][j] = nullptr;
            }
            else if ((i == ((rows - 1) / 2)) && j == ((cols - 1) / 2))
            {
                board[i][j] = nullptr;
            }
            else
            {
                board[i][j] = new chess(i, j);
            }
        }
    }
}

bool chessboard::is_inbound(int row, int col) const
{
    int i = row;
    int j = col;
    if ((i <= 1 && j <= 1) || (i <= 1 && j >= this->cols - 2) || (i >= this->rows - 2 && j <= 1) || (i >= this->rows - 2 && j >= this->cols - 2))
    {
        return false;
    }
    if ((i < 0) || (j < 0) || (i >= this->rows) || (j >= this->cols))
    {
        return false;
    }
    return true;
}

chess ***chessboard::get_board() const
{
    return this->board;
}

chess *chessboard::get_chess(int row, int col) const
{
    if (this->is_inbound(row, col) == false)
    {
        cerr << "Invalid coordinate" << endl;
        return nullptr;
    }
    if (this->board[row][col] == nullptr)
    {
        cerr << "There is no such chess!" << endl;
        return nullptr;
    }
    return board[row][col];
}

int **chessboard::get_possible_blocks(int row, int col) const
{
    if (this->get_chess(row, col) == nullptr)
    {
        cerr << "Invalid input!" << endl;
        return nullptr;
    }
    chess *s = get_chess(row, col); // s is not nullptr
    int **possible_block_list;
    int *a, *b, *c, *d;
    // Up direction
    a = nullptr;
    b = nullptr;
    c = nullptr;
    d = nullptr;
    if (this->is_inbound(row - 1, col) && this->board[row - 1][col] != nullptr && this->is_inbound(row - 2, col) && this->board[row - 2][col] == nullptr)
    {
        a = new int[2];
        a[0] = row - 2;
        a[1] = col;
    }
    // Down direction
    if (this->is_inbound(row + 1, col) && this->board[row + 1][col] != nullptr && this->is_inbound(row + 2, col) && this->board[row + 2][col] == nullptr)
    {
        c = new int[2];
        c[0] = row + 2;
        c[1] = col;
    }
    // Left direction
    if (this->is_inbound(row, col - 1) && this->board[row][col - 1] != nullptr && this->is_inbound(row, col - 2) && this->board[row][col - 2] == nullptr)
    {
        d = new int[2];
        d[0] = row;
        d[1] = col - 2;
    }
    // Right direction
    if (this->is_inbound(row, col + 1) && this->board[row][col + 1] != nullptr && this->is_inbound(row, col + 2) && this->board[row][col + 2] == nullptr)
    {
        b = new int[2];
        b[0] = row;
        b[1] = col + 2;
    }
    possible_block_list = new int *[4];
    possible_block_list[0] = a;
    possible_block_list[1] = b;
    possible_block_list[2] = c;
    possible_block_list[3] = d;
    return possible_block_list;
}

bool chessboard::select(int row, int col)
{
    if (this->selected_chess != nullptr)
    {
        cerr << "There is already a selected chess!" << endl;
        return false;
    }
    if (is_inbound(row, col) == false)
    {
        cerr << "The given coordinate is invalid!" << endl;
        return false;
    }
    this->selected_chess = new int[2];
    this->selected_chess[0] = row;
    this->selected_chess[1] = col;
    return true;
}

void chessboard::unselect()
{
    if (this->selected_chess == nullptr)
    {
        cout << "No selected chess!" << endl;
        return;
    }
    else
    {
        delete[] this->selected_chess;
        this->selected_chess = nullptr;
        return;
    }
}

/// @brief This function will take two coordinates of the same dimension as input and determine whether they are the same coordinate. It will return false if any of them is nullptr.
/// @tparam T The type of variables of the coordinate
/// @param a the first coordinate to compare
/// @param b the second coordinate to compare
/// @param N the dimension of the coordinates, the default is 2
/// @return If they are the same coordinate, return true; else return false
template <typename T>
bool is_same_coordinate(const T *a, const T *b, const int N = 2)
{
    if (a == nullptr || b == nullptr)
    {
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        // cout << a[i] << b[i];
        if (a[i] != b[i])
        {
            return false;
        }
    }
    return true;
}

/// @brief This function will take a coordinate and a list of coordinates of the same dimension as input and determine whether the first coordinate is in the coordinate list. If the input coordinate is nullptr, it will return false. But it is OK if there is nullptr in the input coordinate list.
/// @tparam T The type of variables of the coordinate
/// @param a The first input coordinate
/// @param A The given coordinate list
/// @param N The dimension of the input coordinate, the default is 2
/// @param list_length The length of the coordinate list, the default is 4
/// @return
template <typename T>
bool is_in_coord_list(const T *a, T **A, const int N = 2, const int list_length = 4)
{
    if (a == nullptr || A == nullptr)
    {
        cerr << "Error! The input is not allowed to be nullptr!" << endl;
        return false;
    }
    for (int i = 0; i < list_length; i++)
    {
        if (is_same_coordinate(a, A[i], N))
        {
            return true;
        }
    }
    return false;
}

void chessboard::print_board() const
{
    if (this->selected_chess == nullptr)
    {
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                if (this->board[i][j] == nullptr)
                {
                    cout << " ";
                }
                else
                {
                    cout << "#";
                }
                cout << " ";
            }
            cout << "\n"
                 << endl;
        }
    }
    else
    {
        int **possible_list = this->get_possible_blocks(this->selected_chess[0], this->selected_chess[1]);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                int *curr_coord = new int[2];
                curr_coord[0] = i;
                curr_coord[1] = j;
                if (this->board[i][j] == nullptr && !(is_in_coord_list(curr_coord, possible_list)))
                {
                    cout << " ";
                }
                else if (is_same_coordinate(curr_coord, this->selected_chess))
                {
                    cout << "*";
                }
                else if (is_in_coord_list(curr_coord, possible_list))
                {
                    cout << "@";
                }
                else
                {
                    cout << "#";
                }

                cout << " ";
                delete[] curr_coord;
            }
            cout << "\n"
                 << endl;
        }
        for (int i = 0; i < 4; i++)
        {
            delete[] possible_list[i];
        }
        delete[] possible_list;
    }
    cout << "\n";
}

bool chessboard::is_movable(int row, int col) const
{
    if (is_inbound(row, col) == false)
    {
        cerr << "The input coordinate is invalid!";
        return 0;
    }
    else if (this->selected_chess == nullptr)
    {
        cerr << "There is no selected chess!";
        return 0;
    }
    else
    {
        int **possible_list = this->get_possible_blocks(this->selected_chess[0], this->selected_chess[1]);
        if (possible_list == nullptr)
        {

            return false;
        }
        int *target_coord = new int[2];
        target_coord[0] = row;
        target_coord[1] = col;
        if (is_in_coord_list(target_coord, possible_list))
        {
            delete[] target_coord;
            for (int i = 0; i < 4; i++)
            {
                delete[] possible_list[i];
            }
            delete[] possible_list;
            return true;
        }
        else
        {
            delete[] target_coord;
            for (int i = 0; i < 4; i++)
            {
                delete[] possible_list[i];
            }
            delete[] possible_list;
            return false;
        }
    }
}

void chessboard::delete_chess(int row, int col)
{
    if (this->board[row][col] == nullptr)
    {
        cout << "Warning! You are trying to delete a chess that does not exist at all!";
        return;
    }
    delete this->board[row][col];
    this->board[row][col] = nullptr;
    return;
}

bool chessboard::move(int row, int col)
{
    // check whether there is a selected chess
    if (this->selected_chess == nullptr || (this->is_inbound(this->selected_chess[0], this->selected_chess[1]) == false))
    {
        cerr << "Error! There is no selected chess or the selected chess is invalid!";
        return false;
    }
    else if (is_movable(row, col) == false)
    {
        cerr << "Error! This place is not movable!";
        return false;
    }
    // Move the chess
    this->board[this->selected_chess[0]][this->selected_chess[1]]->move(row, col);
    this->board[row][col] = this->board[this->selected_chess[0]][this->selected_chess[1]];
    // Set the original block to nullptr
    this->board[this->selected_chess[0]][this->selected_chess[1]] = nullptr;
    // Delete the block that passes over
    this->delete_chess((this->selected_chess[0] + row) / 2, (this->selected_chess[1] + col) / 2);
    // Set the selected chess to the new coord
    this->selected_chess[0] = row;
    this->selected_chess[1] = col;
    return true;
}

bool chessboard::is_end_game() const
{
    return false;
}