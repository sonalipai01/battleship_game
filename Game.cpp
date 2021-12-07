/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Game.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Sonali Pai and Raffy Millado
 * sonpai and rmillado
 *
 * Project 4: Battleship
 *
 * Game class that sets the players and the moves to execute the game of battleship
 */

#include <fstream>

#include "Game.h"

// default constructor
Game::Game() {
    p1 = Player();
    p2 = Player();
}

// non-default constructor
Game::Game(Player player1, string grid1, Player player2, string grid2) {
    p1 = player1;
    p2 = player2;
    
    if (grid1 != "")
    {
        // adds ships from file onto p1's grid
        p1.load_grid_file(grid1);
        
        // if it fails, generate a random grid for p1
        if (!p1.load_grid_file(grid1))
        {
            generate_random_grid(p1);
            cout << "Generating random grid for" << p1.get_name() << endl;
        }
    }
    if (grid1 == "")
    {
        generate_random_grid(p1);
         cout << "Generating random grid for" << p1.get_name() << endl;
    }
    
    // adds ships from file onto p2's grid
    if (grid2 != "")
       {
           p2.load_grid_file(grid2);
           
        // if it fails, generate a random grid for p2
           if (!p1.load_grid_file(grid2))
           {
               generate_random_grid(p2);
               cout << "Generating random grid for" << p2.get_name() << endl;
           }
       }
       if (grid2 == "")
       {
           generate_random_grid(p2);
           cout << "Generating random grid for" << p2.get_name() << endl;

       }
}

Player Game::get_p1() {
    
    return p1;
}

Player Game::get_p2() {
    return p2;
}

string Game::get_move(string player_name) {
    
    string playerMove;
    cout << player_name << " enter your move:" << endl;
    cin >> playerMove;
     
    return playerMove;
     
}

bool Game::check_valid_move(string move) {
    // ensures that move consists of only one row and one col
    if(move.size() != 2)
    {
        cout << p1.get_name() << " you entered an invalid input" << endl;
        return false;
    }
    // ensures that row is between 1 and 8
    else if(move.at(0) > '8' || move.at(0) < '1')
    {
        cout << p1.get_name() << " you entered an invalid position" << endl;
        return false;
    }
    
    // ensures that col is between A and H or a and h
    else if(!((move.at(1) <= 'H' && move.at(1) >= 'A') ||
              (move.at(1) <= 'h' && move.at(1) >= 'a')))
    {
        cout << p1.get_name() << " you entered an invalid position" << endl;
        return false;
    }
    else
    {
        return true;
    }

   
}

void Game::start(char difficulty, int max_num_rounds) {
    
    int numRounds = 0;
    string move;
    bool goodMove;
    
    /* executes while neither ship is destroyed and max rounds
    hasn't been reached */
    while ((!(p1.destroyed() || p2.destroyed())) && (numRounds < max_num_rounds))
    {
        move = get_move(p1.get_name());
        goodMove = check_valid_move(move);
        
        while (!(goodMove))
        {
            move = get_move(p1.get_name());
            check_valid_move(move);
        }
        
        // calls attack function from player one using the move input from user
        p1.attack(p2, Position(move.at(0), move.at(1)));
        
        // ends game if player 2 is destroyed and prints grid of both players
        if(p2.destroyed())
        {
            cout << "Your grid" << endl;
            p1.print_grid();
            cout << p2.get_name() << "'s grid" << endl;
            p1.print_guess_grid();
            numRounds++;
            cout << "Game over, winner is " << p1.get_name() << " in "
            << numRounds << " rounds" << endl;
            return;
        }
        
        opponent_make_move(difficulty);
        
        // ends game if player 1 is destroyed and prints grid of both players
        if(p1.destroyed())
        {
            cout << "Your grid" << endl;
            p1.print_grid();
            cout << p2.get_name() << "'s grid" << endl;
            p1.print_guess_grid();
            numRounds++;
            cout << "Game over, winner is " << p2.get_name() << " in "
            << numRounds << " rounds" << endl;
            return;
        }
        
        // prints the grid of each player at the end of each round
        cout << "Your grid" << endl;
        p1.print_grid();
        cout << p2.get_name() << "'s grid" << endl;
        p1.print_guess_grid();
        
        // increments the number of rounds after each round
        numRounds++;
    }
    
    /* after the while loop ends this checks to see if either player is
     destroyed and if neither one is then then there is no winner */
    if(p1.destroyed())
    {
        cout << "Game over, winner is " << p2.get_name() << " in "
        << numRounds << " rounds" << endl;
    }
    else if(p2.destroyed())
    {
        cout << "Game over, winner is " << p1.get_name() << " in "
        << numRounds << " rounds" << endl;
    }
    else
    {
        cout << "Game over, winner is no one in " << numRounds << " rounds"
        << endl;
    }
    
    
    
    
}

// Your code goes above this line.
// Don't change the implementations below!

void Game::generate_random_grid(Player &p) {
    // grid to check which position has been taken
    bool grid[MAX_GRID_SIZE][MAX_GRID_SIZE] = {{false}};

    for (int k = 0; k < 10 && p.get_num_ships() < 5; k++) {
        // i is the length of the ship to be made
        // decrementing i to create 2 ships of size 3
        int i = p.get_num_ships() + 1;
        if (i > 2) {
            i--;
        }

        // generate random position 1
        int row = get_random_number() % MAX_GRID_SIZE;
        int col = get_random_number() % MAX_GRID_SIZE;
        Position pos1(row, col);

        if (!grid[row][col]) {
            Position pos2;
            // Check if creating position two is not off the grid relative to
            // position 1 inthe order of bottom, right, left, top
            if (row + i < MAX_GRID_SIZE) {
                pos2 = Position(row + i, col);
            } else if (col + i < MAX_GRID_SIZE) {
                pos2 = Position(row, col + i);
            } else if (col - i >= 0) {
                pos2 = Position(row, col - i);
            } else if (row - i >= 0) {
                pos2 = Position(row - i, col);
            } else {
                continue;
            }

            Ship s(pos1, pos2);

            bool pos2_taken = false;
            if (s.is_horizontal()) {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_col() < pos2.get_col() ?
                            pos1.get_col() : pos2.get_col();
                int end = pos1.get_col() < pos2.get_col() ?
                          pos2.get_col() : pos1.get_col();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[pos1.get_row()][j]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[pos1.get_row()][j] = true;
                }
            } else {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_row() < pos2.get_row() ?
                            pos1.get_row() : pos2.get_row();
                int end = pos1.get_row() < pos2.get_row() ?
                          pos2.get_row() : pos1.get_row();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[j][pos1.get_col()]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[j][pos1.get_col()] = true;
                }
            }

            // Restart from beginning
            if (pos2_taken) {
                continue;
            }

            // Add the ship to p2's ships
            p.add_ship(s);
        }
    }
}

void Game::opponent_make_move(char difficulty) {
    if (difficulty == EMULATE) {
        Position next;
        cout << "Enter CPU emulation move: ";
        cin >> next;
        cout << endl;
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
    } else if (difficulty == EASY) {
#ifndef NOCPU
        int randRow = get_random_number() % MAX_GRID_SIZE;
        int randCol = get_random_number() % MAX_GRID_SIZE;
        Position randCoord(randRow, randCol);
        p2.attack(p1, randCoord);
        cout << "You received an attack at " << randCoord << endl << endl;
#else
        Position next;
        cin >> next;
        if (cin.fail()) {
            cin.clear();
            next = Position(7, 4);
        }
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
#endif
    } else if (difficulty == MEDIUM) {
        // Simple AI that checks right, bottom, left, top of hit position
        // TODO: implement for S'more version
    }
}

