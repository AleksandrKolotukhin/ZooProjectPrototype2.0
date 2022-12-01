#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>
#include <iostream>
class Item;
using namespace std;
class  Map
{

public:
    vector <Item> items;
    vector < vector <string> > room; //initializing vector for 2d
    int corridor_type = 0;//1-horizontal,2-vertical
    int x, y, exit = 0, enter = 1, exitX = 0, exitY = 0, enterX = 0, enterY = 0, room_type = 0, mid_x, mid_y;
    string way_out = "", way_in = "botom";
    bool Monster_exist = true;
    Map(int a = 5, int b = 5, int ex = 1, int room_ty = 1) //our arguments: 1) the length of the room by X 2) The length of the room by Y 3) 1 - from above 2 - from the right side, default from above 4) the type of room(1 - ordinary square, 2 - L shaped)
    {
        room_type = room_ty;
        exitX = 0;
        exitY = 0;
        x = a;	//initializing variables, that were made through the constructor
        y = b;
        exit = ex;

    }
    void create_room()		//function, that creates room, walls, and escape (in theory entrance?)
    {
        srand(time(0));
        system("cls");			//clears console
        room.resize(y);					   //room size by Y
        for (int i = 0; i < y; i++)		   //room size by X
        {
            room[i].resize(x);
        }
        if (room_type == 1 || corridor_type > 0)
        {
            for (int i = 0; i < y; i++)		   //filling room by walls and empty space
            {
                for (int a = 0; a < x; a++)
                {
                    if (i == 0 || i == y - 1 || a == 0 || a == x - 1)
                    {
                        room[i][a] = (char)35;
                    }
                    else
                    {
                        room[i][a] = (char)32;
                    }
                }
            }
            for (int i = 0; i < y; i++)
            {
                for (int a = 0; a < x; a++) //generates exit
                {
                    if (i != 0 && (a != 0 && a != x) && i != y && (a != 0 && a != x))  //used for not making exit at the corners
                    {
                        if (corridor_type == 2) {
                            exit = 0;
                            exitY = 0;
                            exitX = 2;
                            way_out = "up";
                        }
                        else if (corridor_type == 1) {
                            exit = 0;
                            exitY = 2;
                            exitX = x - 1;
                            way_out = "side";
                        }
                        else {
                            if (exit == 1)                        //if we selected UP exit
                            {
                                exit = 0;
                                exitY = 0;
                                exitX = 1 + rand() % (x - 2);
                                way_out = "up";
                            }
                            if (exit == 2)							//... side exit
                            {
                                exit = 0;
                                exitY = 1 + rand() % (i);
                                exitX = x - 1;
                                way_out = "side";
                            }
                        }
                        room[exitY][exitX] = (char)32;

                    }
                }
            }
            {

                for (int i = 0; i < y; i++)
                {
                    for (int a = 0; a < x; a++) //generates entrance
                    {
                        if (i != 0 && i != y && a != 0 && a != x)  //not making exit at the corners
                        {
                            if (corridor_type == 2) {
                                enter = 0;
                                enterY = y - 1;
                                enterX = exitX;
                            }
                            else if (corridor_type == 1) {
                                enter = 0;
                                enterY = exitY;
                                enterX = 0;
                            }
                            else {
                                if (way_in == "botom" && enter == 1)                        //... UP exit
                                {
                                    enter = 0;
                                    enterY = y - 1;
                                    enterX = 1 + rand() % (x - 2);
                                }
                                if (way_in == "left" && enter == 1)							//... side exit
                                {
                                    enter = 0;
                                    enterY = 1 + rand() % (y - 2);
                                    enterX = 0;
                                }
                            }
                            room[enterY][enterX] = (char)32;
                        }
                    }
                }
            }
        }
        else if (room_type == 2)
        {
            mid_x = 2 + rand() % (x - 2);
            mid_y = 2 + rand() % (y - 2);
            for (int i = 0; i < y; i++)
            {
                for (int a = 0; a < x; a++)
                {
                    if (i == 0 || a == 0)
                    {
                        room[i][a] = (char)35;
                    }
                    else if (a == x - 1 && i <= mid_y - 1)
                    {
                        room[i][a] = (char)35;
                    }
                    else if (a > mid_x && i == mid_y)
                    {
                        room[i][a] = (char)35;
                    }
                    else if (a == mid_x && i >= mid_y)
                    {
                        room[i][a] = (char)35;
                    }
                    else if (i == y - 1 && a <= mid_x)
                    {
                        room[i][a] = (char)35;
                    }
                    else
                    {
                        room[i][a] = (char)32;
                    }

                }
            }
            if (exit == 1)                        //...selected UP exit
            {
                exit = 0;
                exitY = 0;
                exitX = 1 + rand() % (x - 2);
                way_out = "up";
            }
            if (exit == 2)						  //... side exit
            {
                exit = 0;
                exitY = 1 + rand() % (mid_y - 1);
                exitX = x - 1;
                way_out = "side";
            }
            room[exitY][exitX] = (char)32;
            if (way_in == "botom" && enter == 1)                        //if the entrance is DOWN
            {
                enter = 0;
                enterY = y - 1;
                enterX = 1 + rand() % (mid_x - 1);
            }
            if (way_in == "left" && enter == 1)							//... selected side exit
            {
                enter = 0;
                enterY = 1 + rand() % (y - 2);
                enterX = 0;
            }
            room[enterY][enterX] = (char)32;
        }
        for (int j = 0; j < y; j++)		//printing room
        {
            for (int d = 0; d < x; d++)
            {
                cout << room[j][d] << " ";
            }
            cout << endl;
        }
    }
};
#endif // MAP_H
