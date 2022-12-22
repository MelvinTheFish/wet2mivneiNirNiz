#include <iostream>
#include "avl_rank.h"
#include "Team.h"
#include "Player.h"
#include <memory>
#include <stdlib.h>     /* srand, rand */
#include "Player_UnionFind_Node.h"


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
    shared_ptr<Team> teams[5];
    shared_ptr<Player> players[25];

    int id = 1;

    int arr[5] = {0,0,0,0,0};

    for (int i = 0; i < 5; ++i) {
        teams[i] = make_shared<Team>(i);
        for (int j = 0; j < 5; ++j) {
            if(id-1 < 24){
                fill_random_permutation(arr);
                players[id-1] = make_shared<Player>(id, i, permutation_t(arr), 0, 0, 0, true);
                Player_UnionFind_Node node = Player_UnionFind_Node(players[id-1], teams[i]);
                id++;
            }
        }
    }




    return 0;
}
