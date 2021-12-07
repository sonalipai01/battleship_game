/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Position.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Sonali Pai and Raffy Millado
 * sonpai and rmillado
 *
 * Project 4: Battleship
 *
 * Position class that implements functions for finding positions on the generated grids
 */

#include "Position.h"
#include "utility.h"

// default constructor
Position::Position() {
    row = 0;
    col = 0;
   
}

// non-default constructor
// ensures that row and col are valid
Position::Position(int row_in, int col_in) {
    row = check_range(row_in);
    col = check_range(col_in);
    
}

// non-default constructor
Position::Position(char row_in, char col_in) {

    // converts col_in to uppercase
    if (col_in >= 'a' && col_in <= 'z')
    {
        col_in = toupper(col_in);
    }
    
    // converts row_in and col_in to integers
    int rowNumber = row_in - 49;
    int columnNumber = col_in - 65;
    row = check_range(rowNumber);
    col = check_range(columnNumber);
}

int Position::get_row() {
    
    return row;
}

void Position::set_row(int row_in) {
    row = check_range(row_in);
    return;
}

int Position::get_col() {
   
    return col;
}

void Position::set_col(int col_in) {
    col = check_range(col_in);
    return;
}

void Position::read(istream &is) {
    char leftP;
    char comma;
    char rightP;
    char column;

    // tries to read in position from rowcol form
    is >> row;

    // tries to read in postiion from (row,col) form
    if (is.fail())
    {
        is.clear();
        is >> leftP >> row >> comma >> column >> rightP;
        
    }
    // continues reading in from rowcol form
    else
    {
        is >> column;
    }
    
    // stores row and col as integers
    column = toupper(column);
    row = check_range(row - 1);
    col = check_range(column - 65);
 
    return;
}

void Position::write(ostream &os) {
 
    int r1;
    r1 = row + 1;
    
    char c1;
    c1 = col + 65;
    
    // writes out row and col in (row,col) form
    os << "(" << r1 << "," << c1 << ")";
   
 
    
    return;
}

int Position::check_range(int val) {
    
    // checks if the value is in the range
    if (val >= 0 && val < MAX_GRID_SIZE)
    {
        return val;
    }
    
    // modifies and returns value so that it is in the range
    else
    {
        if (val < 0)
        {
            return 0;
        }
        else
        {
            return MAX_GRID_SIZE - 1;
        }
    }
}

// Your code goes above this line.
// Don't change the implementations below!

istream &operator>>(istream &is,  Position &pos) {
    pos.read(is);
    return is;
}

ostream &operator<<(ostream &os, Position pos) {
    pos.write(os);
    return os;
}


