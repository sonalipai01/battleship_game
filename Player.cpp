/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Player.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Sonali Pai and Raffy Millado
 * sonpai and rmillado
 *
 * Project 4: Battleship
 *
 * Player class that adds each players ships to grids and implements functions for attacking in the game
 */

#include <fstream>

#include "Player.h"


// default constructor
Player::Player() {
    name = "";
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

// non default constructor
Player::Player(string name_val) {
    name = name_val;
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
    
}

void Player::init_grid() {
    
// constructs a grid filled with '-' in each element
    for (int i = 0; i < MAX_GRID_SIZE; i++)
    {
        for (int j = 0; j < MAX_GRID_SIZE; j++)
        {
            grid[i][j] = EMPTY_LETTER;
            guess_grid[i][j] = EMPTY_LETTER;
        }
    }
    return;
}

string Player::get_name() {
    
    return name;
}

int Player::get_num_ships() {

    return num_ships;
}

int Player::get_remaining_ships() {
   
    return remaining_ships;
}

// returns the character in a specific position on grid
char Player::get_grid_at(int row, int col) {
    
    return grid[row][col];
}

// returns the character in a specific position on guess grid
char Player::get_guess_grid_at(int row, int col) {

    return guess_grid[row][col];
}

void Player::add_ship(Ship ship) {
    
// returns if the max number of ships has been added
   if (num_ships == MAX_NUM_SHIPS)
   {
       return;
   }
    
// adds the ship to the player's ship array
   ships[num_ships] = ship;
   num_ships++;
   remaining_ships++;


// adds a ship to the grid if it is horizontal
    if (ship.is_horizontal())
    {
        if (ship.get_start().get_col() < ship.get_end().get_col())
        {
            // adds '*' from start column to end column
            for (int i = ship.get_start().get_col();
                 i <= ship.get_end().get_col(); i++)
            {
                grid[ship.get_start().get_row()][i] = SHIP_LETTER;
            }
        }
    else
    {
        // adds '*' from end column to start column
        for (int i = ship.get_end().get_col(); i <= ship.get_start().get_col();
             i++)
        {
            grid[ship.get_start().get_row()][i] = SHIP_LETTER;
 
        }
    }
}
    
// adds a ship to the grid if it is vertical
    else
    {
        if (ship.get_start().get_row() < ship.get_end().get_row())
        {
            // adds '*' from start column to end column
            for (int i = ship.get_start().get_row(); i
                 <= ship.get_end().get_row(); i++)
            {
                grid[i][ship.get_start().get_col()] = SHIP_LETTER;
            }
        }
        else
        {
            // adds '*' from end column to start column
            for (int i = ship.get_end().get_row();
                 i <= ship.get_start().get_row(); i++)
            {
                grid[i][ship.get_start().get_col()] = SHIP_LETTER;
            }
        }
    }
    
    return;
}

bool Player::position_not_hit(Position pos) {
/* grid will have an empty letter or ship letter if the position
    has not been hit yet */
    if ((grid[pos.get_row()][pos.get_col()] == EMPTY_LETTER) ||
        (grid[pos.get_row()][pos.get_col()] == SHIP_LETTER))
    {
        return true;
    }

    return false;
}

void Player::attack(Player &opponent, Position pos) {
   Player attacker = Player(name);
     int hits = 0;
     
    // iterates through the opponent's ships array
         for (int i = 0; i < MAX_NUM_SHIPS; i++)
         {
             if(opponent.ships[i].has_sunk())
             {
                 
             }
             else
             {
                 /* ensures that the position has not been hit,
                  the opponent has a ship in that position,
                  and the position in that grid is not an empty letter*/
                 if (opponent.position_not_hit(pos) &&
                    opponent.ships[i].has_position(pos) &&
                     (opponent.grid[pos.get_row()][pos.get_col()]
                      != EMPTY_LETTER))
                             {
                                 /* hits the ship and marks the grids at that
                                  position as O */
                                 opponent.ships[i].hit();
                                 
                                 opponent.grid[pos.get_row()][pos.get_col()]
                                 = HIT_LETTER;
                                 
                                 attacker.grid[pos.get_row()][pos.get_col()]
                                 = HIT_LETTER;
                                 
                                 guess_grid[pos.get_row()][pos.get_col()]
                                 = HIT_LETTER;
                                 
                                 cout << attacker.name << " " << pos << " hit"
                                 << endl;
                                 
                                 if(opponent.ships[i].has_sunk())
                                 {
                                      if(opponent.ships[i].get_size() == 2)
                                      {
                                          announce_ship_sunk(2);
                                      }
                                      else if(opponent.ships[i].get_size() == 3)
                                      {
                                          announce_ship_sunk(3);
                                      }
                                      else if(opponent.ships[i].get_size() == 4)
                                      {
                                          announce_ship_sunk(4);
                                      }
                                      else
                                      {
                                          announce_ship_sunk(5);
                                      }
                                                
                                            opponent.remaining_ships--;
                                 }
                                 
                                 hits++;
                                 
                             }
             }
           

         }
   
    // marks the position as a 'X' to represent a miss
    if(hits == 0)
        {
           opponent.grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
           attacker.grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
               
           guess_grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
               
           cout << attacker.name << " " << pos << " miss" << endl;
        }
       else
       {
           return;
       }
     
     return;

}

// announces what kind of ship has sunk based on the size of the ship
  void Player::announce_ship_sunk(int size) {
     
          
          if (size == 2)
          {
              cout << "Congratulations " << name << "!"
                   << " You sunk a Destroyer" << endl;
          }
          if (size == 3)
              {
              cout << "Congratulations " << name << "!"
                   << " You sunk a Submarine" << endl;
          }
          if (size == 4)
          {
              cout << "Congratulations " << name << "!"
                   << " You sunk a Battleship" << endl;
          
          }
          if (size == 5)
          {
              cout << "Congratulations " << name << "!"
                   << " You sunk a Carrier" << endl;

          }
      
      return;
  }


bool Player::load_grid_file(string filename) {
    ifstream input;
    Position start;
    Position end;
    Player pp1;
    Ship battleship;
    
    // opens up a file
    input.open(filename);
    
    if (input.fail())
    {
        return false;
    }
   
    while (input.good() && pp1.num_ships < MAX_NUM_SHIPS)
    {
        // reads in a start position and an end position of a ship
            input >> start >> end;
        // constructs a ship based on positions and adds ship to player's grid
            battleship = {start, end};
            add_ship(battleship);
    }
    
    input.close();
    return true;
}

// player is destroyed if they have no more ships
bool Player::destroyed() {
   if (remaining_ships == 0)
   {
       return true;
   }
    return false;
}

// Your code goes above this line.
// Don't change the implementations below!

void Player::print_grid() {
    ::print_grid(grid);
}

void Player::print_guess_grid() {
    ::print_grid(guess_grid);
}


