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
            if(id-1 <= 24){
                fill_random_permutation(arr);
                players[id-1] = make_shared<Player>(id, i, permutation_t(arr), id, 0, 0, true);
                shared_ptr<Player_UnionFind_Node> node = make_shared<Player_UnionFind_Node>(players[id-1], teams[i]);
                players[id-1]->setUnionFindNode(node);
                if (teams[i]->getSize() == 0){
                    teams[i]->setRootPlayer(node);
                }
                teams[i]->setSize(teams[i]->getSize()+1);
                id++;
            }
        }
    }

    ///testing spirits right after adding
    id = 1;
    for (int i = 0; i < 5; ++i) {
        permutation_t so_far = permutation_t::neutral();
        for (int j = 0; j < 5; ++j) {
            Find(players[id-1]);
            cout << "player " << id << "'s partial spirit: " << players[id-1]->getPartialSpirit() << endl;
            so_far = so_far * players[id-1]->getSpirit();
            cout << "so_far :" << so_far << endl;
            id++;
        }
        cout << "team " << i << "'s spirit: " << teams[i]->getTeamSpirit() << endl;
    }

    cout << "testing after union of bigger buys smaller " << endl;
    cout << "testing after union of bigger buys smaller " << endl;
    cout << "testing after union of bigger buys smaller " << endl;


    shared_ptr<Team> team0_bought_1 = Union(teams[0], teams[1]);

    permutation_t so_far = permutation_t::neutral();
    for (int i = 0; i < 10; ++i) {
        Find(players[i]);
        cout << "player " << i+1 << "'s partial spirit: " << players[i]->getPartialSpirit() << endl;
        so_far = so_far * players[i]->getSpirit();
        cout << "so_far :" << so_far << endl;
    }
    cout << "team " << 0 << "'s spirit: " << teams[0]->getTeamSpirit() << endl;


    cout << "testing after union of bigger buys smaller " << endl;
    cout << "testing after union of bigger buys smaller " << endl;
    cout << "testing after union of bigger buys smaller " << endl;


    shared_ptr<Team> team01_bought_2 = Union(teams[0], teams[2]);

    so_far = permutation_t::neutral();
    for (int i = 0; i < 15; ++i) {
        Find(players[i]);
        cout << "player " << i+1 << "'s partial spirit: " << players[i]->getPartialSpirit() << endl;
        so_far = so_far * players[i]->getSpirit();
        cout << "so_far :" << so_far << endl;
    }
    cout << "team " << 0 << "'s spirit: " << teams[0]->getTeamSpirit() << endl;


    cout << "testing after union of smaller buys bigger " << endl;
    cout << "testing after union of smaller buys bigger " << endl;
    cout << "testing after union of smaller buys bigger " << endl;


    shared_ptr<Team> team3_bought_012 = Union(teams[3], teams[0]);

    so_far = permutation_t::neutral();
    int tmp;
    for (int i = 0; i < 20; ++i) {
        if (i < 5){
            tmp = i+15;
        }
        else{
            tmp = i-5;
        }
        Find(players[tmp]);
        cout << "player " << tmp+1 << "'s partial spirit: " << players[tmp]->getPartialSpirit() << endl;
        so_far = so_far * players[tmp]->getSpirit();
        cout << "so_far :" << so_far << endl;
    }
    cout << "team " << 3 << "'s spirit: " << teams[3]->getTeamSpirit() << endl;




    return 0;
}
