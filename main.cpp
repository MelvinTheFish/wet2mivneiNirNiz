#include <iostream>
#include "avl_rank.h"
#include "Team.h"
#include "Player.h"
#include <memory>

using namespace std;



int main() {

    weak_ptr<Player> kal = weak_ptr<Player>();
    shared_ptr<Player> realKal = kal.lock();
    if(realKal){
        cout << "not null" << endl;
    }
    else{
        cout << "null" << endl;///good
    }


    shared_ptr<Player> player1 = make_shared<Player>(1);

    kal = player1;


    realKal = kal.lock();
    if(realKal){
        cout << "not null" << endl;///good
    }
    else{
        cout << "null" << endl;
    }

    kal.reset();

    realKal = kal.lock();
    if(realKal){
        cout << "not null" << endl;
    }
    else{
        cout << "null" << endl;///good
    }

    kal = player1;
    realKal = kal.lock();
    if(realKal){
        cout << "not null" << endl;///good
    }
    else{
        cout << "null" << endl;
    }

    return 0;
}
