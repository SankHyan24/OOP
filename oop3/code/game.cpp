#include <game.hpp>
#include <fstream>
#include <ctime>
using namespace std;
bool game::random_generator(int mim) const
{
    int up_range = 1024;
    int down_range = 16; // 1/64
    int measure_num = ROOM_NUM * ROOM_NUM;
    if (8 * mim > measure_num)
        down_range *= 4; // 1/16
    if (4 * mim > measure_num)
        down_range *= 2; // 1/8
    if (2 * mim > measure_num)
        down_range *= 6; // 3/4
    if (mim + mim / 2 > measure_num)
        down_range *= 2; // 3/2
    return rand() % up_range < down_range;
}
void game::room_generate()
{
    std::cout << "room_generate" << std::endl;
    srand(time(NULL));
    bool have_princess = false;
    bool have_monster = false;
    int cur_num = 0;
    int room_num = this->room_list.size();
    for (int i = 0; i < ROOM_NUM; i++)
        for (int j = 0; j < ROOM_NUM; j++)
        {
            cur_num++;
            rooms[i][j].set_room(room_list[rand() % room_num]);
            if (!have_princess)
                if (random_generator(cur_num))
                {
                    rooms[i][j].set_princess(true);
                    have_princess = true;
#ifdef TEST
                    cout << "princess in room " << i << " " << j << endl;
#endif
                }
                else
                    ;
            else if (!have_monster)
                if (random_generator(cur_num))
                {
                    rooms[i][j].set_monster(true);
                    have_monster = true;
#ifdef TEST
                    cout << "monster in room " << i << " " << j << endl;
#endif
                }
        }
    for (int i = 0; i < ROOM_NUM - 1; i++)
        for (int j = 0; j < ROOM_NUM; j++)
            for (int k = 0; k < 2; k++)
                road[i][j][k] = rand() % 100 < 80;
}
void game::read_rooms()
{
    ifstream fin("./map.txt");
    string this_line;
    if (!fin)
    {
        std::cout << "open map.txt failed" << std::endl;
        return;
    }
    while (getline(fin, this_line))
    {
        auto tmp = this_line;
        getline(fin, this_line);
        room_list.emplace_back(tmp, this_line, false, false);
    }
}
void game::print_map() const
{
    for (int i = 0; i < ROOM_NUM; i++)
    {
        for (int j = 0; j < ROOM_NUM; j++)
            cout << rooms[i][j].name.substr(0, 2) << " ";
        cout << endl;
    }
}
void game::scan_room_for_demo(int scale) const
{
    std::cout << "You have carefully investigated the situation around you" << std::endl;
    bool is_demo_near = false;
    for (int i = (((x - scale) < 0) ? 0 : x - scale); i < (((x + scale) > ROOM_NUM - 1) ? ROOM_NUM - 1 : x + scale); i++)
        for (int j = (((y - scale) < 0) ? 0 : y - scale); j < (((y + scale) > ROOM_NUM - 1) ? ROOM_NUM - 1 : (y + scale)); j++)
            if (rooms[i][j].have_monster)
            {
                is_demo_near = true;
                if (war3)
                    std::cout << "demo in room " << i << " " << j << std::endl;
                break;
            }
    if (!is_demo_near)
        std::cout << "It's very quiet around, at least there won't be any monsters around" << std::endl;
    else
        std::cout << "You heard the devil's roar"
                  << endl
                  << "The Monster is in eight rooms around you!" << std::endl;
}
void game::scan_room_for_princess(int scale) const
{
    std::cout << "You have carefully investigated the situation around you" << std::endl;
    bool is_princess_near = false;
    for (int i = 0; i < ROOM_NUM; i++)
        for (int j = 0; j < ROOM_NUM; j++)
            if (rooms[i][j].have_princess)
            {
                is_princess_near = true;
                if (war3)
                    std::cout << "princess in room " << i << " " << j << std::endl;
                break;
            }
    if (!is_princess_near)
        std::cout << "It's very quiet around, at least the princess won't be around" << std::endl;
    else
        std::cout << "You heard the princess cry for help!"
                  << endl
                  << "The princess is in eight rooms around you!" << std::endl;
}
void game::logic_tick()
{
#ifndef TEST
    system("cls");
    system("clear");
#endif
    if (!war3)
    {
        if (rand() % 100 < 40)
            scan_room_for_demo(1);
        if (rand() % 100 < 25)
            scan_room_for_princess(1);
    }
    else
    {
        if (rand() % 100 < INT32_MAX)
            scan_room_for_demo(INT32_MAX);
        if (rand() % 100 < INT32_MAX)
            scan_room_for_princess(INT32_MAX);
    }
    if (rooms[x][y].have_monster)
    {
        std::cout << "A demon is lurking in the corner of this room," << std::endl
                  << "but at the moment you only have the princess on your mind." << std::endl
                  << "The devil is silently approaching you behind your back," << std::endl
                  << "and stretches his sinful claws to your throat." << std::endl
                  << "You are killed by monster\n\n\n\n"
                  << "Bad Ending...." << std::endl;
        is_end = true;
        return;
    }
    if (rooms[x][y].have_princess)
    {
        std::cout << "In this room, you see your beloved princess." << std::endl
                  << "She is so beautiful, so charming, so captivating. You look at the princess affectionately, and the princess looks at you affectionately." << std::endl
                  << "You took her cute, lovely hand, ready to kiss her..." << std::endl
                  << "Oh stop! Now is not the time for this kind of thing." << std::endl
                  << "You hug the princess and walk towards the first entrance step by step..." << std::endl;
        rooms[x][y].have_princess = false;
        with_princess = true;
    }
    if (x == 0 && y == 0)
    {
        std::cout << "You are in the first room, and you see a door to exit." << std::endl;
        if (with_princess)
        {
            std::cout << "You and the princess escaped from this place and lived happily ever after\n\n\n\n"
                      << "Good Ending...." << std::endl;
            is_end = true;
            return;
        }
        else
        {
            cout << "But you can't just leave because you have to rescue the princess who is trapped in it." << endl;
        }
    }
    if (with_princess)
    {
        std::cout << "Escape this place with the princess! Now!" << std::endl;
    }
    rooms[x][y].print_room();
    move_on();
}
void game::game_process()
{
    while (!this->is_end)
        logic_tick();
}
void game::move_on()
{
    print_door();
}
void game::print_door()
{
    if (war3)
        cout << "Your current position is " << x << " " << y << endl;
    cout << "You can go:";
    bool u = false, d = false, r = false, l = false;
    if (x != 0 && road[x - 1][y][1])
    {
        cout << " left";
        l = true;
    }
    if (y != 0 && road[x][y - 1][0])
    {
        cout << " up";
        u = true;
    }
    if (x != ROOM_NUM - 1 && road[x][y][1])
    {
        cout << " right";
        r = true;
    }
    if (y != ROOM_NUM - 1 && road[x][y][0])
    {
        cout << " down";
        d = true;
    }
    cout << endl;
    while (1)
    {
        string s;
        cin >> s;
        if (s == "up" && (u || (war3 && y != 0)))
        {
            y--;
            break;
        }
        if (s == "down" && (d || (war3 && y != ROOM_NUM - 1)))
        {
            y++;
            break;
        }
        if (s == "left" && (l || (war3 && x != 0)))
        {
            x--;
            break;
        }
        if (s == "right" && (r || (war3 && x != ROOM_NUM - 1)))
        {
            x++;
            break;
        }
        if (s == "whosyourdaddy")
        {
            war3 = !war3;
            break;
        }
        cout << "You can't go there." << endl;
    }
}