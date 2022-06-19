//Gabriel Mannheimer
//COP 3330
#include <iostream>
#include <cstdlib>      // for srand(), rand()
#include <ctime>   // for time()
#include "grid.h"

using namespace std;


Grid::Grid()
{
    rows = 1;
    cols = 1;
    mrow = 1;
    mcol = 1;
    direc = EAST;
    grid[1][1] = '>';
    path = true;
}


Grid::Grid(int r, int c)                      //grid 2d array goes as grid[cols][rows]
{
    srand(time(0));

//INITIALIZING NUMS*********************************************************************

    rows = r;
    cols = c;
    if (rows < 3)                           //rows and cols oly very from 3-40 max
        rows = 3;

    if (rows > 40)
        rows = 40;

    if (cols < 3)
        cols = 3;

    if (cols > 40)
        cols = 40;


//RANDOM NUM FOR DIRECTION AND PLACEMENT OF MOVER*********************************************************************
    direc = rand() % 3;
    mrow = rand() % (GetNumRows()- 2) + 1;         //this should return a random num from 1 - (rows - 1)
    mcol = rand() % (GetNumCols() - 2) + 1;
    path = true;



    for (int i = 0; i < rows; i++){                                            //i = rows k = cols
        for (int k = 0; k < cols; k++){
            if (mrow == i && mcol == k)
                grid[i][k] = DirecR(direc);
            else
                grid[i][k] = '.';
        }
    }


//BORDER*********************************************************************

    for(int i = 0; i < rows; i++) {
        grid[i][0] = '#';
        grid[i][cols - 1] = '#';
    }
    for (int k = 0; k < cols; k++)
    {
        grid[0][k] = '#';
        grid[rows - 1][k] = '#';
    }

        exitR = rand() % (rows - 2) + 1;                                   //rows - 2 to make sure it never lands on a corner
        exitC = rand() % (cols - 2) + 1;


    int wall = rand() % 3;

    switch(wall)
    {
        case NORTH:
            grid[exitR][0] = ' ';
            break;
        case WEST:
            grid[0][exitC] = ' ';
            break;
        case SOUTH:
            grid[exitR][cols - 1] = ' ';
            break;
        case EAST:
            grid[rows - 1][exitC] = ' ';
            break;
    }



}


Grid::Grid(int r, int c, int mr, int mc, int d)
{
    rows = r;
    cols = c;
    mrow = mr;
    mcol = mc;
    direc = d;
    path = true;




    if (rows < 1)
        rows = 1;

    if (rows > 40)
        rows = 40;

    if (cols < 1)
        cols = 1;


    if (cols > 40)
        cols = 40;

    if (mrow < 1)
        mrow = 1;
    if (mrow > 40)
        mrow = 40;
    if(mcol < 1)
        mcol = 1;
    if (mcol > 40)
        mcol = 40;

    if (direc < 0)
        direc = 0;
    if (direc > 3)
        direc = 3;



    for (int i = 0; i < rows; i++){                                            //i = rows k = cols
        for (int k = 0; k < cols; k++){

            if (mrow == i && mcol == k)
                grid[i][k] = DirecR(direc);
            else
                grid[i][k] = '.';
        }
    }
}


//FUNCTIONS*********************************************************************

void Grid::Display() const
{
    int boi = 0;
    cout << "\nThe Grid:" << endl;
    if(GetNumCols() == 1 && GetNumRows() == 1)              //If the num of rows and cols are 1 then only output >
    {
        cout << '>';
    }

    else {
        for (int i = 0; i < GetNumRows(); i++) {
            for (int k = 0; k < GetNumCols(); k++) {
                if(grid[GetRow()][GetCol()] == '0')
                    cout << '@';
                else {
                    if(path) {
                        if (i == list[boi].x && k == list[boi].y) {
                            cout << ' ';
                        }
                        else
                            cout << grid[i][k];
                    }
                    else
                        cout << grid[i][k];
                }
                cout << ' ';
            }
            cout << "\n";
            boi++;
        }
    }
}

int Grid::GetRow() const
{
    return mrow;
}

int Grid::GetCol() const
{
    return mcol;
}

int Grid::GetNumCols() const {
    return cols;
}


int Grid::GetNumRows() const {
    return rows;
}

char Grid::DirecR(int d)
{
    if (d == NORTH)
        return '^';
    else if (d == WEST)
        return '<';
    else if (d == SOUTH)
        return 'V';
    else if (d == EAST)
        return '>';


    else
        return 'N';
}

bool Grid::Move(int s)                                  // move forward s spaces, if possible
{
        switch(direc) {
            case NORTH:
                if (s > 0) {
                    if (GetRow() - s >= 0){                                         //because it is moving upward
                        for (int i = 0; i < s; i++) {
                            if (FrontIsClear()) {
                                list[listA] = {GetRow(), GetCol()};
                                if(path){
                                    if (grid[GetRow()][GetCol()] != '@')
                                        if(grid[GetRow()][GetCol()] == ' ')
                                            break;
                                        else
                                            grid[GetRow()][GetCol()] = ' ';
                                    else
                                        grid[GetRow()][GetCol()] = '0';
                                }
                                else {
                                    if (grid[GetRow()][GetCol()] != '@')
                                        grid[GetRow()][GetCol()] = '.';
                                    else
                                        grid[GetRow()][GetCol()] = '0';
                                }

                                mrow--;
                                if(grid[GetRow()][GetCol()] == '0')
                                    grid[GetRow()][GetCol()] = '@';
                                else
                                    grid[GetRow()][GetCol()] = DirecR(direc);

                                listA++;
                            }
                        }
                            return true;
                        }
                    }
                else
                    {
                        grid[GetRow()][GetCol()] = DirecR(direc);
                        return false;
                    }


            case WEST:
                if (s > 0){
                    if(GetCol() - s >= 0){
                        for (int i = 0; i < s; i++){
                            if(FrontIsClear()) {
                                list[listA] = {GetRow(),GetCol()};
                                if(path){
                                    if (grid[GetRow()][GetCol()] != '@')
                                        if(grid[GetRow()][GetCol()] == ' ')
                                            break;
                                        else
                                            grid[GetRow()][GetCol()] = ' ';
                                    else
                                        grid[GetRow()][GetCol()] = '0';
                                }
                                else {
                                    if (grid[GetRow()][GetCol()] != '@')
                                        grid[GetRow()][GetCol()] = '.';
                                    else
                                        grid[GetRow()][GetCol()] = '0';
                                }
                                mcol--;

                                if(grid[GetRow()][GetCol()] == '0')
                                    grid[GetRow()][GetCol()] = '@';
                                else
                                    grid[GetRow()][GetCol()] = DirecR(direc);
                                listA++;
                            }
                        }
                        return true;
                    }
                    else                                                                       //else to see if the move is legal
                    {
                        grid[GetRow()][GetCol()] = DirecR(direc);
                        return false;
                    }
                }
            case SOUTH:
                if (s > 0){
                    if(GetRow() + s < GetNumRows()) {
                        for (int i = 0; i < s; i++) {
                            if(FrontIsClear()) {
                                list[listA] = {GetRow(),GetCol()};
                                if(path){
                                    if (grid[GetRow()][GetCol()] != '@')
                                        if(grid[GetRow()][GetCol()] == ' ')
                                            break;
                                        else
                                            grid[GetRow()][GetCol()] = ' ';
                                    else
                                        grid[GetRow()][GetCol()] = '0';
                                }
                                else {
                                    if (grid[GetRow()][GetCol()] != '@')
                                        grid[GetRow()][GetCol()] = '.';
                                    else
                                        grid[GetRow()][GetCol()] = '0';
                                }
                                mrow++;

                                if(grid[GetRow()][GetCol()] == '0')
                                    grid[GetRow()][GetCol()] = '@';
                                else
                                    grid[GetRow()][GetCol()] = DirecR(direc);
                               listA++;
                            }
                        }
                        return true;
                    }
                    else
                    {
                        grid[GetRow()][GetCol()] = DirecR(direc);
                        return false;
                    }

                }
            case EAST:
                if (s > 0){
                    if(GetCol() + s < GetNumCols()){
                        for (int i = 0; i < s; i++) {
                            if (FrontIsClear()) {
                                list[listA] = {GetRow(), GetCol()};

                                if(path){
                                    if (grid[GetRow()][GetCol()] != '@')
                                        if(grid[GetRow()][GetCol()] == ' ')
                                            break;
                                        else
                                            grid[GetRow()][GetCol()] = ' ';
                                    else
                                        grid[GetRow()][GetCol()] = '0';
                                }
                                else {
                                    if (grid[GetRow()][GetCol()] != '@')
                                        grid[GetRow()][GetCol()] = '.';
                                    else
                                        grid[GetRow()][GetCol()] = '0';
                                }
                                mcol++;

                                if(grid[GetRow()][GetCol()] == '0')
                                    grid[GetRow()][GetCol()] = '@';
                                else
                                    grid[GetRow()][GetCol()] = DirecR(direc);
                                listA++;
                            }
                        }
                        return true;
                    }
                    else{
                        grid[GetRow()][GetCol()] = DirecR(direc);
                        return false;
                    }
                }
        }
        return false;


}

bool Grid::PutDown(int r, int c)  // put down an item at (r,c), if possible
{
    if(grid[r][c] == '.' && r < (GetNumRows()) && c < (GetNumCols()) && r >= 0 && c >= 0) {
        grid[r][c] = '0';
        return true;
    }
    else
        return false;
}

void Grid::PutDown()
{
    if(grid[GetRow()][GetCol()] != '@')
    grid[GetRow()][GetCol()] = '@';
}


bool Grid::FrontIsClear() const     // check to see if space in front of mover is clear
{
    switch(direc) {
        case NORTH:
            if (grid[GetRow() - 1][GetCol()] == '#' || GetRow() == 0) {
                for (int i = 0; i < listA; i++) {
                    if (GetRow() - 1 == list[i].x && GetCol() == list[i].y)
                        continue;
                }
                return false;
            }

            else
                return true;


        case WEST:
            if(grid[GetRow()][GetCol() - 1] == '#' || GetCol() == 0){
                for (int i = 0; i < listA; i++) {
                    if (GetRow() == list[i].x && GetCol() - 1 == list[i].y)
                        continue;
                      }
                    return false;
                }
            else
                return true;

        case SOUTH:
            if (grid[GetRow() + 1][GetCol()] == '#' || GetRow() == GetNumRows() - 1) {
                for (int i = 0; i < listA; i++) {
                    if (GetRow() + 1 == list[i].x && GetCol() == list[i].y)
                        continue;
                }
                return false;
            }
            else
                return true;


        case EAST:
            if (grid[GetRow()][GetCol() + 1] == '#' || GetCol() == GetCol() - 1) {
                for (int i = 0; i < listA; i++) {
                    if (GetRow() == list[i].x && GetCol() + 1 == list[i].y)
                        continue;
                }
                return false;
            }
            else
                return true;

    }
    return false;

}
bool Grid::RightIsClear() const     // check to see if space on the right of the mover is clear
{
    switch(direc) {
        case NORTH:
                if (grid[GetRow()][GetCol() + 1] == '#') {
                    for (int i = 0; i < listA; i++) {
                        if (GetRow() == list[i].x && GetCol() + 1 == list[i].y)
                            continue;
                    }
                    return false;
                }

                else
                    return true;


        case WEST:
                if (grid[GetRow() - 1][GetCol()] == '#') {
                    for (int i = 0; i < listA; i++) {
                        if (GetRow() - 1 == list[i].x && GetCol() == list[i].y)
                            continue;
                    }
                    return false;
                }
                else
                    return true;


        case SOUTH:
                if (grid[GetRow()][GetCol() - 1] == '#') {
                    for (int i = 0; i < listA; i++) {
                        if (GetRow() == list[i].x && GetCol() - 1 == list[i].y)
                            continue;
                    }
                    return false;
                }
                else
                    return true;



        case EAST:
                if (grid[GetRow() + 1][GetCol()] == '#') {
                    for(int i = 0; i < listA; i++) {
                        if (GetRow() + 1 == list[i].x && GetCol() == list[i].y)
                            continue;
                    }
                    return false;
                }
                else
                    return true;


    }
    return false;

}


void Grid::TogglePath()
{
    path = !(path);                           // should return the opposite of path

    if(path) {
        for (int i = 0; i < listA; i++) {
            if(grid[list[i].x][list[i].y] != '0' && grid[list[i].x][list[i].y] != DirecR(direc))
            grid[list[i].x][list[i].y] = ' ';
            else if (grid[list[i].x][list[i].y] == DirecR(direc))
                grid[list[i].x][list[i].y] = DirecR(direc);
            else
                grid[list[i].x][list[i].y] = '0';
        }
    }

    else {
        for (int i = 0; i < listA; i++) {
            if(grid[list[i].x][list[i].y] != '0' && grid[list[i].x][list[i].y] != DirecR(direc))
                grid[list[i].x][list[i].y] = '.';
            else if (grid[list[i].x][list[i].y] == DirecR(direc))
                grid[list[i].x][list[i].y] = DirecR(direc);
            else
                grid[list[i].x][list[i].y] = '0';
        }
    }

}

bool Grid::PlaceBlock(int r, int c)          // put a block at (r,c), if possible
{
    if(grid[r][c] == '.' && r < (GetNumRows()) && c < (GetNumCols())) {
        grid[r][c] = '#';
        return true;
    }
    else
        return false;

}



void Grid::TurnLeft()
{
    switch(direc) {
        case NORTH:
            direc = WEST;
            break;
        case WEST:
            direc = SOUTH;
            break;
        case SOUTH:
            direc = EAST;
            break;
        case EAST:
            direc = NORTH;
            break;
    }

    if(grid[GetRow()][GetCol()] != '@')
        grid[mrow][mcol] = DirecR(direc);
    else
        grid[mrow][mcol] = '@';
}

void Grid::Grow(int gr, int gc)
{
    char gridTemp[40][40];
    int tempR,tempC;
    for(int i = 0; i < rows; i ++) {
        for (int k = 0; k < cols; k++) {
            gridTemp[i][k] = grid[i][k];
        }
    }

    tempR = GetNumRows();
    tempC = GetNumCols();


    if (gr + GetNumRows() > 40)
        rows = 40;
    else
        rows = gr + GetNumRows();

    if(gc + GetNumCols() > 40)
        cols = 40;
    else
        cols = gc + GetNumCols();


    for(int i = 0; i < rows; i++){
        for(int k = 0; k < cols; k++) {
            if(i < tempR && k < tempC)
            grid[i][k] = gridTemp[i][k];
            else
                grid[i][k] = '.';
        }
    }
}

bool Grid::PickUp()
{
    if (grid[GetRow()][GetCol()] == '@')
    {
        grid[GetRow()][GetCol()] = DirecR(direc);
        return true;
    }
    else
        return false;
}


