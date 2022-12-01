#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "hero.h"
using namespace std;
class Item
{
public:
    string type;
    int Ipos_X, Ipos_Y;
    bool picked_up = false;
    Item(string type)
    {
        this->type = type;
    }
    void spawn_item(Map& map, Hero hero) //spawning item in the room
    {
        if (map.room_type == 1)
        {
            Ipos_X = 1 + rand() % (map.x - 2);
            Ipos_Y = 1 + rand() % (map.y - 2);
        }
        else if (map.room_type == 2)
        {
            Ipos_X = 1 + rand() % (map.mid_x - 1);
            Ipos_Y = 1 + rand() % (map.mid_y - 1);
        }
        if (type == "sword")
            map.room[Ipos_Y][Ipos_X] = "S";
        else if (type == "food")
            map.room[Ipos_Y][Ipos_X] = "F";
        else if (type == "bottle")
            map.room[Ipos_Y][Ipos_X] = "B";
    }
    void on_pick_up(Map& map, Hero& hero) //after picking up item it will choose the effect/type
    {
        if (picked_up == false)
        {
            if (type == "sword")
            {
                hero.damage = 25, 0;
                map.room[Ipos_Y][Ipos_X] = " ";
                hero.move("", map);
                picked_up = true;
            }
            else if (type == "food")
            {
                hero.heal_ammount = hero.heal_ammount + 1;
                map.room[Ipos_Y][Ipos_X] = " ";
                hero.move("", map);
                picked_up = true;
            }
            else if (type == "bottle")
            {
                hero.bottle_ammount = hero.bottle_ammount + 1;
                map.room[Ipos_Y][Ipos_X] = " ";
                hero.move("", map);
                picked_up = true;
            }
        }
    }
};
#endif // ITEM_H
