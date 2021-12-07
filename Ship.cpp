/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Ship.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Sonali Pai and Raffy Millado
 * sonpai and rmillado
 *
 * Project 4: Battleship
 *
 * Ship class that implements functions that define the positions of ships
 */

#include <cmath>

#include "Ship.h"

// default constructor
Ship::Ship() {
    start = Position(0,0);
    end = Position(0,0);
    size = 0;
    num_hits = 0;
    
}

// non-default constructor
Ship::Ship(Position start_in, Position end_in) {
    start = start_in;
    end = end_in;
    num_hits = 0;
    
    // counts size horizontally
    if (is_horizontal())
    {
        size = abs(end.get_col() - start.get_col()) + 1;
    }
    
    // counts size vertically
    else
    {
        size = abs(end.get_row() - start.get_row()) + 1;
    }
}

Position Ship::get_start() {
    
    return start;
}

Position Ship::get_end() {
    
    return end;
}

int Ship::get_size() {
    
    return size;
}


bool Ship::is_horizontal() {
    // checks to see if the row stays constant from start to end of ship
    if (start.get_row() == end.get_row())
    {
        return true;
    }
    
    return false;
}

bool Ship::has_position(Position pos) {
    
    // returns true if position exists within the horizontal ship
    if (is_horizontal())
    {
        if ((pos.get_col() >= start.get_col() && pos.get_col() <= end.get_col())
            || (pos.get_col() >= end.get_col() && pos.get_col()
            <= start.get_col()))
        {
            return true;
        }
            
    }
    
    // returns true if position exists within the vertical ship
    else
    {
        if ((pos.get_row() >= start.get_row() && pos.get_row() <= end.get_row())
            || (pos.get_row() >= end.get_row() && pos.get_row()
            <= start.get_row()))
        {
            return true;
        }
    }
    return false;
}

void Ship::hit() {
    if (num_hits < size)
    {
        num_hits++;
    }
    return;
}

bool Ship::has_sunk() {
    if (num_hits == size)
    {
        return true;
    }
    return false;
}

