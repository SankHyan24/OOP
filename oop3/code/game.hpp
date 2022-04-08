#pragma once
#include <room.hpp>
#include <iostream>
#include <vector>
using namespace std;
#define ROOM_NUM 10
class game
{
private:
    bool is_end, with_princess, war3;
    void room_generate();
    void read_rooms();
    bool random_generator(int mim) const;
    void scan_room_for_demo(int) const;
    void scan_room_for_princess(int) const;
    void print_map() const;
    void logic_tick();

public:
    int x, y;
    room rooms[ROOM_NUM][ROOM_NUM];
    bool road[ROOM_NUM - 1][ROOM_NUM][2]; // 0 is rlmore, 1 is udmore
    vector<room> room_list;
    game() : x(0), y(0), with_princess(false), war3(false), is_end(false)
    {
        room_list.clear();
        read_rooms();
        for (int i = 0; i < ROOM_NUM - 1; i++)
            for (int j = 0; j < ROOM_NUM; j++)
                for (int k = 0; k < 2; k++)
                    road[i][j][k] = false;
        room_generate();
        print_map();
    };
    void game_process();
    void move_on();
    void print_door();
};