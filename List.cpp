//
// Created by Nir on 12/25/2022.
//
#include "List.h"

class List;

List::List():sizeOfList(0),first(),Last()
{

}

void List::DestroyList() {

    Node* tmpNode = this->first;
    while(this->sizeOfList > 0){
        Node* toDelete = tmpNode;
        if(sizeOfList>1){
            tmpNode = tmpNode->next;
        }
        delete toDelete;
        this->sizeOfList --;
    }
}


List::~List() {

    Node* tmpNode = this->first;
    while(this->sizeOfList > 0){
        Node* toDelete = tmpNode;
        if(sizeOfList>1){
            tmpNode = tmpNode->next;
        }
        delete toDelete;
        this->sizeOfList --;
    }
}


int List::AddToList(shared_ptr<Player> player) {

    Node* newNode = new Node;
    newNode->player = player;
    if(this->sizeOfList == 0){
        this->first = newNode;
        this->sizeOfList++;
        return 0;
    }
    int isinList = isInList(player->getPlayerId());
    if(isinList != -1){
      return -1;
    }
//    if(isinList != -1){
//        Node* tmpNode = this->first;
//        if(isinList == this->sizeOfList-1){
//            this->Last->setCount(1);
//        }
//        else{
//            int i =0;
//            while(i<isinList){
//                tmpNode = tmpNode->next;
//                i++;
//            }
//            tmpNode->setCount(1);
//        }
//        delete newNode;
//        return;
//    }
    if(this->sizeOfList == 1){
        this->Last = newNode;
        this->Last->prev = this->first;
        this->first->next = this->Last;
    }
    if(this->sizeOfList > 1){
        this->Last->next = newNode;
        this->Last->next->prev = this->Last;
        this->Last = this->Last->next;
    }
    this->sizeOfList++;
    return sizeOfList-1;
}

int List::getListLength() {
    return this->sizeOfList;
}

List::Node *List::getIndexInList(int index) {

    if(index == 0){
        return this->first;
    }
    if(index == this->getListLength() - 1){
        return this->Last;
    }
    Node* tmpNode = this->first;
    for(int i=0;i<index;++i){
        tmpNode = tmpNode->next;
    }
    return tmpNode;
}

int List::isInList(int playerId) {
    if(sizeOfList == 0){
        return -1;
    }

    Node* tmpNode = this->first;
    for(int i=0;i<this->getListLength()-1;i++){
        if(tmpNode->player->getPlayerId() == playerId){
            return i;
        }
        tmpNode = tmpNode->next;
    }
    if(tmpNode->player->getPlayerId() == playerId){
        return this->sizeOfList - 1;
    }
    return -1;

}
