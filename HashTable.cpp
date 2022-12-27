//
// Created by Nir on 12/21/2022.
//
#include "HashTable.h"
#include "iostream"

#include "math.h"
#include "List.h"

HashTable::HashTable(){

    this->curretnSize = 0;
    this->PowerOf2Index = 4;
    this->sizeOfTable =  pow(2,4)-1;
    hashTable = new List[sizeOfTable];

}
HashTable::HashTable(int tableSize, int PowerOf2Index) {

    this->curretnSize = 0;
    this->PowerOf2Index = PowerOf2Index;
    this->sizeOfTable = tableSize;
    hashTable = new List[sizeOfTable];

}

HashTable::HashTable(const HashTable &other) {

    this->curretnSize = other.curretnSize;
    this->hashTable = new List[other.sizeOfTable];
    this->PowerOf2Index = other.PowerOf2Index;
    for(int i=0;i<other.curretnSize;++i) {
        this->hashTable[i] = other.hashTable[i];
    }
}

HashTable &HashTable::operator=(const HashTable &other) {
    if(this == &other) {
        return *this;
    }

    delete(this->hashTable);
    this->curretnSize = other.curretnSize;
    this->PowerOf2Index = other.PowerOf2Index;
    this->hashTable = new List[other.sizeOfTable];
    for(int i=0;i<other.sizeOfTable;++i) {
        this->hashTable[i] = other.hashTable[i];
    }
    return *this;

}
//HashTable::~HashTable() {
//    free(this->hashTable);
//    free(this->isAvailableToSearch);
//}

int HashTable::hash(int key) {
    return key % this->sizeOfTable;
}

//int HashTable::hash2(int key) {
//    return 1 + key % this->sizeOfHash2;
//}



int HashTable::insertHash(shared_ptr<Player> player) {
//    if(player->getPlayerId() == 27644){
//        cout<< 444 <<endl;
//    }
//    if(this->findInHashTable(player->getPlayerId())!=-1){
//        return -1;
//    }

    if(this->findInHashTable(player->getPlayerId()) != -1){
        return -1;
    }
    if(this->isTableFull()){
        this->ExpandTable();
    }
    int hashIndex = hash(player->getPlayerId());
    int index = this->hashTable[hashIndex].AddToList(player);
    if(index == -1){
        return -1;
    }

    this->curretnSize++;
    return hashIndex;
}


//void HashTable::removeFromTable(shared_ptr<Player> player) {
//
//    int hash1Index = hash1(player->getPlayerId());
//    int hash2Index = hash2(player->getPlayerId());
//
//    if(!(this->hashTable[hash1Index] == player)){
//        int k = 0;
//        bool isFound = false;
//        while(!isFound){
//            int newIndex = (hash1Index+k*hash2Index) % CAPACITY;
//            if(hashTable[newIndex]){
//                hashTable[newIndex] == player;
//                isFound = true;
//                hashTable[newIndex] = nullptr;
//            }
//            k++;
//        }
//    }
//    else
//        hashTable[hash1Index] = nullptr;
//}
int HashTable::findInHashTable(int playerId) {

    int hashIndex = hash(playerId);
    int index = this->hashTable[hashIndex].isInList(playerId);
    if(index != -1){
        return hashIndex;
    }
    return index;

}

shared_ptr<Player> HashTable::getPlayerinIndex(int index, int playerId) {
    for(int i=0;i<this->hashTable[index].getListLength();++i) {
        if (this->hashTable[index].getIndexInList(i)->getData()->getPlayerId() == playerId) {
            return this->hashTable[index].getIndexInList(i)->getData();
        }
    }
    return nullptr;
}

void HashTable::ExpandTable() {

    this->PowerOf2Index++;
    int newSize = pow(2,this->PowerOf2Index)-1;

    HashTable newHashTable(newSize ,this->PowerOf2Index);
    for(int i=0;i<this->sizeOfTable;i++){
        for(int j=0;j<this->hashTable[i].getListLength();j++){
            newHashTable.insertHash(hashTable[i].getIndexInList(j)->getData());
        }
    }
    delete this->hashTable;
    this->hashTable = new List[newSize];
    this->sizeOfTable = newSize;
    for(int i=0;i<newSize;i++){
        for(int j=0;j<newHashTable.hashTable[i].getListLength();j++){
           this->hashTable[i].AddToList(newHashTable.hashTable[i].getIndexInList(j)->getData());
        }
    }
}
//void HashTable::ExpandTable() {
//
//
//    this->PowerOf2Index++;
//    int newSize = pow(2,this->PowerOf2Index)-1;
//    shared_ptr<Player>* newArray = (shared_ptr<Player>*) malloc(newSize*sizeof (shared_ptr<Player>));
//    int* newIntArray = (int*)malloc(newSize*sizeof(int));
//    for(int i=0;i<this->sizeOfTable;++i){
//        newArray[i].swap(hashTable[i]);
//    }
//    for(int i=0;i<this->curretnSize;++i){
//        newIntArray[i] = this->isAvailable[i];
//    }
//    for(int i=curretnSize;i<newSize;++i){
//        newIntArray[i] = 1;
//    }
//
//    this->hashTable = new shared_ptr<Player>[newSize];
//    this->isAvailable= (int*)malloc(newSize*sizeof(int));
//    for(int i=0;i<curretnSize;i++){
//        this->hashTable[i].swap(newArray[i]);
//    }
//    for(int i=0;i<newSize;++i){
//        this->isAvailable[i] = newIntArray[i];
//    }
//    this->sizeOfHash2 = newSize-1;
//    this->sizeOfTable = newSize;
//
//}

bool HashTable::isTableFull() {
    if(this->curretnSize >=(float)(0.8 *this->sizeOfTable)){
        return true;
    }
    return false;
}


void HashTable::printTable() {
    for(int i=0;i< this->sizeOfTable;++i){
       for(int j=0;j<this->hashTable[i].getListLength();j++){
           cout << this->hashTable[i].getIndexInList(j)->getData()->getPlayerId()<<" ";
           if(j < this->hashTable[i].getListLength()-1){
               cout<< ", ";
           }
       }
       if(this->hashTable[i].getListLength()!=0){
           cout<< " " << endl;
       }
    }
}

int HashTable::getTableSize() {
    return this->sizeOfTable;
}

int HashTable::getCurrentSize() {
    return this->curretnSize;
}

