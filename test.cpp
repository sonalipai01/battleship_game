/**
 * Copyright 2019 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Project 4: Battleship
 *
 * Contains functions for testing classes in the project. 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

#include "Position.h"
#include "Ship.h"
#include "Player.h"
#include "Game.h"
#include "utility.h"

using namespace std;


void test_position();
void test_ship();
void test_player();
void test_game();

void startTests() {
    test_position();
    test_ship();
    test_player();
    test_game();
    
    return;
}

void test_position() {
   // test of default constructor
    Position p1;
    // test of the non-default constructor
    Position p2(3, 9);
   
    Position p4('1','a');

    // test of member function: set_row(int row_in)
    p1.set_row(5);
    
    // test of member function: set_col(int col_in)
    p1.set_col(3);
   
    // test of member functions get_row() and get_col()
    cout << "( " << p1.get_row()
         << ", " << p1.get_col()
         << " )" << endl;
    cout << "( " << p4.get_row()
            << ", " << p4.get_col()
            << " )" << endl;
  
    
    // you can also do cin >> p1;
    
    p1.read(cin);
    cout << p1 << endl;
    
    cout << p2 << endl;
    
    
    // testing read and write functions
    ifstream inFS;
    inFS.open("grid1.txt");
    inFS >> p1;
    cout << "Expected: (8,B), Actual: " << p1 << endl; // testing write function
    inFS.close();

    return;
}

void test_ship() {
    cout << "testing test_ship" << endl;
    Ship s1;
    cout << s1.get_start() << endl;
    cout << s1.get_end() << endl;
    cout << s1.get_size() << endl;
    s1.hit();
    s1.hit();
    s1.hit();
    s1.has_sunk();
    
    
    Position p1('1','H');
    Position p2('1', 'D');
    Ship s2(p1, p2);
    s2.get_start();
    s2.get_end();
    s2.get_size();
    s2.is_horizontal();
    
    s2.hit();
    

    return;
}

void test_player() {
    cout << "Testing test_player" << endl;
    
    cout << "testing add_ship" << endl;
    Player p1;
    Ship s10 (Position('1','H'), Position('1','E'));
    p1.add_ship(s10);
    cout << p1.get_num_ships() << endl;
     cout << p1.get_remaining_ships() << endl;
    p1.add_ship(Ship(Position('2','F'), Position('3','F')));
    cout << p1.get_num_ships() << endl;
    cout << p1.get_remaining_ships() << endl;
    p1.print_grid();
   
   
    p1.add_ship(Ship(Position('4','A'), Position('4','E')));
    cout << p1.get_num_ships() << endl;
    cout << p1.get_remaining_ships() << endl;
    p1.add_ship(Ship(Position('5','E'), Position('5','G')));
    cout << p1.get_num_ships() << endl;
    cout << p1.get_remaining_ships() << endl;
    p1.print_grid();
    
   
    p1.add_ship(Ship(Position('7','A'), Position('7','D')));
    cout << p1.get_num_ships() << endl;
    cout << p1.get_remaining_ships() << endl;
    p1.print_grid();
    
    p1.add_ship(Ship(Position('8','B'), Position('8','D')));
      cout << p1.get_num_ships() << endl;
      cout << p1.get_remaining_ships() << endl;
      p1.print_grid();
    
    p1.add_ship(Ship(Position('5','B'), Position('6','B')));
         cout << p1.get_num_ships() << endl;
         cout << p1.get_remaining_ships() << endl;
         p1.print_grid();
    
    Player p3("Sonali");
     p3.add_ship(Ship(Position('2','F'), Position('2','G')));
     cout << p3.get_num_ships() << endl;
      cout << p3.get_remaining_ships() << endl;
     p3.add_ship(Ship(Position('4','G'), Position('4','H')));
     cout << p3.get_num_ships() << endl;
     cout << p3.get_remaining_ships() << endl;
    cout << p3.get_name();
     p3.print_grid();


    cout << "Testing attack" << endl;
        Player p2;
        p2.attack(p1, Position('1','H'));
        s10.hit();
        s10.has_sunk();
        p2.attack(p1, Position('1','D'));
        p2.attack(p1, Position('1','H'));
        p2.attack(p1, Position('1','E'));
        p2.attack(p1, Position('1','F'));
        s10.hit();
        s10.has_sunk();
        p2.attack(p1, Position('1','G'));
        s10.hit();
        s10.has_sunk();
        cout << p1.get_remaining_ships();
        
    
    
    
        p2.attack(p1, Position('5','B'));
        Ship(Position('5','B'),Position('6','B')).hit();
    Ship(Position('5','B'),Position('6','B')).has_sunk();
    p2.attack(p1, Position('6','B'));
        Ship(Position('5','B'),Position('6','B')).hit();
    Ship(Position('5','B'),Position('6','B')).has_sunk();

    // testing ship_hit
    Ship ship(Position ('2','d'), Position ('2','e'));
    ship.hit();
    ship.hit();
    ship.has_sunk();
    
    Ship shipp(Position ('3','f'), Position ('3','h'));
       ship.hit();
       ship.hit();
       ship.has_sunk();
    
    Ship shippp(Position ('4','H'), Position ('4', 'D'));
    ship.hit();
    ship.hit();
    ship.hit();
    ship.hit();
    ship.hit();
    ship.hit();
    ship.hit();
    ship.has_sunk();
        
    
   
    

    cout << "Testing load_grid_file" << endl;
    Player newPlayer;
    Ship newShip;
    newPlayer.load_grid_file("grid1.txt");
    cout << newShip.get_start() << endl;
    cout << newShip.get_end() << endl;
    newPlayer.print_grid();
    
    return;
  
}


void test_game() {
    cout << "Testing test_game" << endl;
    //Test of the default
    Game g1;
    g1.get_p1();
    g1.get_p2();
    
    //Test of the non-default
    Player p1;
    Player p2;
    
    Game g2 (p1, "grid1.txt", p2, "grid2.txt");
    g2.get_p1();
    g2.get_p2();
    g2.get_p1().load_grid_file("grid1.txt");
    g2.get_p2().load_grid_file("grid2.txt");
    g2.get_move(p1.get_name());
    g2.get_move(p2.get_name());
    
    Game g3 (p1, "slkdjfas", p2, "slkdnftxt" );
    g3.get_p1();
    g3.get_p2();
    g3.get_p1().load_grid_file("slkdjfas");
    g3.get_p2().load_grid_file("slkdnftxt");
    g3.get_move(p1.get_name());
    g3.get_move(p2.get_name());
    g3.get_p1().get_num_ships();
    g3.get_p2().get_num_ships();
    g3.get_p1().get_name();
    g3.get_p2().get_name();
    g3.get_p1().get_grid_at(0, 0);
    g3.get_p2().get_grid_at(0, 0);
    g3.get_p1().get_guess_grid_at(0, 0);
    g3.get_p2().get_guess_grid_at(0, 0);
    g3.get_p1().get_num_ships();
    g3.get_p2().get_num_ships();


    

    
 
    
    //testing check_valid_move
    cout << "Now testing check_valid_move" << endl;
    Game().check_valid_move("1A");
    Game().check_valid_move("1Afsadf");
    Game().check_valid_move("1T");
    Game().check_valid_move("8H");
    Game().check_valid_move("7b");
    Game().check_valid_move("19");
    Game().check_valid_move("fdsa");
    Game().check_valid_move("9A");
    Game().check_valid_move("1t");
    
    
    // testing game getters
    
    
    return;
}

/**
* Requires: size > 0, and size is the number of elements of arr
* Modifies: Nothing.
* Effects:  Returns the index of the first occurrence of value in
*           arr, or -1 if value is not in arr.
*/
int indexOf(int arr[], int size, int value) {

    
    
    return -1;

}

