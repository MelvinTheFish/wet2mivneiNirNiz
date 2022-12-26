//
// Created by Nir on 12/25/2022.
//

#ifndef WET2MIVNEINIRNIZ_LIST_H
#define WET2MIVNEINIRNIZ_LIST_H
#include "memory"
#include "Player.h"

class List{
    struct Node{

        shared_ptr<Player> player;
        Node* prev;
        Node* next;
        int count;
        Node():player(nullptr),prev(nullptr),next(nullptr),count(0)
        {}

        Node(shared_ptr<Player> player):player(player),prev(nullptr),next(nullptr),count(1)
        {}

        Node* getNext(){
            return this->next;
        }
        Node* getPrev(){
            return this->prev;
        }
        int getCount(){
            return this->count;
        }
        shared_ptr<Player> getData(){
            return this->player;
        }
        void setCount(int count){
            this->count = this->count + count;
        }


    };

public:
    List();
    List(const List& other) = default;
    List& operator=(const List& other) = default;
    ~List() = default;
    int isInList(int playerId);
    void AddToList(shared_ptr<Player> player);
    Node* getIndexInList(int index);
    int getListLength();


private:
    int sizeOfList;
    Node* first;
    Node* Last;

};

#endif //WET2MIVNEINIRNIZ_LIST_H
