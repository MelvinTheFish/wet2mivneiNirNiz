#include <iostream>
#include "avl_rank.h"
#include "Team.h"
#include "Player.h"
#include <memory>
#include <stdlib.h>     /* srand, rand */
#include "Player_UnionFind_Node.h"
#include "worldcup23a2.h"


using namespace std;

void fill_random_permutation (int * a){
    int used[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 5; ++i) {
        int j = rand()%5;
        while (used[j]){
            j = rand()%5;
        }
        used[j] = 1;
        a[i] = j;
    }
}

int main() {

    srand((unsigned int)time(NULL));

    int id = 1;

    int arr[5] = {0,0,0,0,0};

    world_cup_t *world_cup = new world_cup_t();

    for (int i = 0; i < 1; ++i) {
        world_cup->add_team(i+1);
        for (int j = 0; j < 1; ++j) {
            fill_random_permutation(arr);
            world_cup->add_player(id, i+1, arr, 0, id, id, true);
            id++;
        }
    }
    world_cup->add_team(3);
    world_cup->buy_team(1,3);



//    world_cup->play_match(3,4);
//    world_cup->play_match(4,5);
//    world_cup->play_match(2,5);
//    world_cup->play_match(1,2);
//    cout << world_cup->get_team_points(4).ans()<<" "<<world_cup->get_team_points(5).ans()<<endl;
//    world_cup->buy_team(4,5);
//    cout << world_cup->get_team_points(4).ans()<<endl;
//
//    for (int j = 0; j < 25; ++j) {
//        cout << "player: " << j+1 << " played: " << world_cup->num_played_games_for_player(j+1).ans() << " games." << endl;
//    }


    return 0;
}
