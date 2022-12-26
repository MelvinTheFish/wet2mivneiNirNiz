#include <iostream>
#include "avl_rank.h"
#include "Team.h"
#include "Player.h"
#include <memory>
#include <stdlib.h>     /* srand, rand */
#include "Player_UnionFind_Node.h"
#include "List.h"
#include "HashTable.h"

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

//    srand((unsigned int)time(NULL));
//    shared_ptr<Team> teams[5];
//    shared_ptr<Player> players[25];
//
//    int id = 1;
//
//    int arr[5] = {0,0,0,0,0};
//
//    for (int i = 0; i < 5; ++i) {
//        teams[i] = make_shared<Team>(i);
//        for (int j = 0; j < 5; ++j) {
//            if(id-1 < 24){
//                fill_random_permutation(arr);
//                players[id-1] = make_shared<Player>(id, i, permutation_t(arr), 0, 0, 0, true);
//                Player_UnionFind_Node node = Player_UnionFind_Node(players[id-1], teams[i]);
//                id++;
//            }
//        }
//    }

//    shared_ptr<Player> player[25];
//    List list;
//    for(int i=0;i<25;++i){
//        player[i] = make_shared<Player>(i%12);
//        list.AddToList(player[i]);
//    }
//    for(int i=0;i<list.getListLength();++i){
////        cout << list.isInList(player[i%3]->getPlayerId())<<endl;
//        cout << list.getIndexInList(i)->getData()->getPlayerId()<<" ";
//        cout << list.getIndexInList(i)->getCount() << endl;
//    }
//    cout << list.getListLength() << endl;
//

    HashTable hashTable;
    shared_ptr<Player> arr[2000];
    for(int i=0;i<2000;++i){
        Player player(rand());
        arr[i] = make_shared<Player>(player);
        hashTable.insertHash(arr[i]);
   }

    hashTable.printTable();
    cout << hashTable.getCurrentSize()<<" "<<hashTable.getTableSize() << endl;





    return 0;
}
