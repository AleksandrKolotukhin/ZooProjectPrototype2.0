#ifndef GAME_H
#define GAME_H
#include "item.h"
#include "monster.h"
#ifndef __clang__
#include <conio.h>
#endif
class Game {
public:
    Game(vector<Monster> m, vector<Map> d, Hero b) :monsters(m), dungeon(d), Boy(b) {};
    bool handleKeys();
    void handleWay();
    void createRoomAndSpawnObjects();
    bool isGameExists();
    void startGame();
    void endGame();
    void startKeysCycle();
private:
    vector <Monster> monsters;
    vector<Map> dungeon;
    Hero Boy;
    int room_id = 0;
    std::string way = "";
};
static std::vector<Map> getDungeon() {
    Map vcorridor(4, 15, 1, 1);
    vcorridor.corridor_type = 2;
    vcorridor.Monster_exist = false;
    Map hcorridor(15, 4, 2, 1);
    hcorridor.corridor_type = 1;
    hcorridor.Monster_exist = false;

    vector <Map> dungeon = { Map(10,10,2,1),hcorridor,Map(12,13,1,1),vcorridor,Map(12,15,2,2),hcorridor,Map(15,20,1,2) };//rooms are created here, transmitted (length X, length Y, exit type, room type)
    dungeon[0].create_room();
    Item sword("sword"); //creating sword
    Item food("food"); //creating food/heal
    Item bottle("bottle");
    dungeon[0].items.push_back(bottle);
    dungeon[2].items.push_back(bottle);
    dungeon[4].items.push_back(bottle);
    dungeon[6].items.push_back(bottle);
    dungeon[0].items.push_back(sword); //objects are entered into the vector of objects, the vector is stored in the object, so each object has its own vector with objects.
    dungeon[0].items.push_back(food);
    dungeon[0].items.push_back(food);
    dungeon[0].items.push_back(food);
    dungeon[0].create_room();


    return dungeon;
}
static Hero getBoy(std::vector<Map>& dungeon, int const& room_id) {
    Hero Boy(dungeon[0]); //hero initialization

    for (int i = 0; i < dungeon[0].items.size(); i++) //spawning all predefined items
    {
        dungeon[0].items[i].spawn_item(dungeon[0], Boy);
    }

    Boy.pos_X = dungeon[room_id].enterX; //Sets the position of the hero to enter
    Boy.pos_Y = dungeon[room_id].enterY;
    Boy.move("", dungeon[room_id]);
    return Boy;
}

static Game  getGame() {
    auto dungeon = getDungeon();
    auto monster = std::vector<Monster>(7);
    auto Boy = getBoy(dungeon, 0);

    return Game(monster, dungeon, Boy);
}


#endif // GAME_H
