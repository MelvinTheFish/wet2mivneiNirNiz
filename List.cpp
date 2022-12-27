//
// Created by Nir on 12/25/2022.
//
#include "List.h"

class List;

List::List():first(),Last(),sizeOfList(0)
{

}



int List::AddToList(shared_ptr<Player> player) {

    Node* newNode = new Node(player);
    if(this->sizeOfList == 0){
        this->first = newNode;
        this->sizeOfList++;
        return 1;
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
