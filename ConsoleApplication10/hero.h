#ifndef HERO_H
#define HERO_H
#include <string>
#include <iostream>
#include "map.h"
using namespace std;
class Hero			//here our hero starts
{
public:
    bool onexit = 0;
    double health = 100, damage = 5, defense = 1;  //HP, dmg, def
    int heal_ammount = 0, pos_X = 1, pos_Y = 1, bottle_ammount = 0;		//our heals/or food, position X, position Y
    string weapon = "fist", armour = "flesh";		//cosmetic attributes

    Hero(Map& map)		//this is constructor(it will get map object(maybe entrance with appearing hero))
    {
        system("cls");
        for (int j = 0; j < map.y; j++)
        {
            for (int d = 0; d < map.x; d++)
            {
                cout << map.room[j][d] << " ";
            }
            cout << endl;

        }
    };

    void move(string input, Map map)		//movement mechanic
    {
        if (input == "down") //	if our input down, our hero will move one square down
        {
            if (pos_Y != map.enterY || pos_X != map.enterX)
                if (map.room[pos_Y][pos_X] == map.room[pos_Y + 1][pos_X]) //check for the walls: it checks what is inside the wall. If it is the same rhat our hero stands in, than hero goes on it
                    pos_Y++;
        }
        if (input == "left")
        {
            if (pos_X != map.enterX || pos_Y != map.enterY)
                if (map.room[pos_Y][pos_X] == map.room[pos_Y][pos_X - 1]) //same as the previous one
                    pos_X--;
        }
        if (input == "up")
        {
            if (pos_Y != map.exitY || pos_X != map.exitX)
                if (map.room[pos_Y][pos_X] == map.room[pos_Y - 1][pos_X]) //same...
                    pos_Y--;
        }
        if (input == "right")
        {
            if (pos_X != map.exitX || pos_Y != map.exitY)
                if (map.room[pos_Y][pos_X] == map.room[pos_Y][pos_X + 1]) //same...
                    pos_X++;
        }
        system("cls");		//clears the console

        if (pos_X != map.exitX || pos_Y != map.exitY)
        {
            onexit = 0;

        }
        if (pos_X == map.exitX && pos_Y == map.exitY)
        {
            onexit = 1;
            cout << "You are on exit, press <Enter> for going next " << endl;

        }
        if (pos_X == map.enterX && pos_Y == map.enterY)
        {
            cout << "You are on enter door, press <Enter> for going back " << endl;
        }
        map.room[pos_Y][pos_X] = "H"; //our Hero symbol on the map
        for (int j = 0; j < map.y; j++) //prints our map, including our Hero movement
        {
            for (int d = 0; d < map.x; d++)
            {
                cout << map.room[j][d] << " ";
            }
            cout << endl;
        }
    }
    void death()
    {
        system("cls");
        cout << "YOU DIED" << endl;
        system("pause");
        exit(0);
    }
    void use_heal()
    {
        if (heal_ammount > 0)
        {
            heal_ammount--;
            if (health + 60 >= 100)
            {
                health = 125;

            }
            else
            {
                health += 100;
            }
            cout << " Your health: " << health << endl << " Your heals(food): " << heal_ammount << endl;
        }
        else
        {
            cout << "you have no heals :(" << endl;
        }
    }
};
#endif // HERO_H
