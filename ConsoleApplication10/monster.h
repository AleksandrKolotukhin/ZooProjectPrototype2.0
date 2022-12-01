#ifndef MONSTER_H
#define MONSTER_H
#include "hero.h"


static int getRandom(int min, int max) {
    srand(time(0));
    return rand() % (max + 1 - min) + min;
}
class Monster
{
public:
    double health = 100, damage = 15;
    int Mpos_X, Mpos_Y;
    bool dead = false;
    void spawn(Map& map)
    {
        if (map.way_out == "side")
        {
            Mpos_X = map.exitX - 1;
            Mpos_Y = map.exitY;
        }
        else
        {
            Mpos_X = map.exitX;
            Mpos_Y = map.exitY + 1;
        }
        map.room[Mpos_Y][Mpos_X] = 'M'; //our Monster symbol on the map
    }

    void take_damage(double dmg, Map& map, Hero& hero) //Monster takes damage, and fighting back
    {
        if (!dead)
        {
            health = health - dmg;
            auto curDamage = getRandom(15, 30);
            std::cout << "DAMAGE IS " << curDamage;
            hero.health = hero.health - curDamage;
            if (hero.health <= 0)
            {
                hero.death();
            }
            if (health <= 0)
            {
                map.Monster_exist = false;
                map.room[Mpos_Y][Mpos_X] = " ";
                dead = true;
            }
        }
    }
};
#endif // MONSTER_H
