//
// Created by Nir on 12/21/2022.
//
#include "HashTable.h"
#include "iostream"

#include "math.h"

HashTable::HashTable(){

    this->curretnSize = 0;
    this->PowerOf2Index = 4;
    this->sizeOfTable =  pow(2,4)-1;
    this->sizeOfHash2 = sizeOfTable - 3;
    hashTable = new shared_ptr<Player>[sizeOfTable];
    isAvailable = (int*) malloc(sizeOfTable*sizeof(int));
    for(int i=0;i<this->sizeOfTable;++i){
        this->isAvailable[i] = 1;
    }
}
HashTable::HashTable(int tableSize, int hash2, int PowerOf2Index) {

    this->curretnSize = 0;
    this->PowerOf2Index = PowerOf2Index;
    this->sizeOfTable = tableSize;
    this->sizeOfHash2 = hash2;
    hashTable = new shared_ptr<Player>[sizeOfTable];
    isAvailable = (int*) malloc(sizeOfTable*sizeof(int));
    for(int i=0;i<this->sizeOfTable;++i){
        this->isAvailable[i] = 1;
    }

}

HashTable::HashTable(const HashTable &other) {

    this->curretnSize = other.curretnSize;
    this->hashTable = (shared_ptr<Player>*)malloc(other.curretnSize*sizeof(shared_ptr<Player>));
    for(int i=0;i<other.curretnSize;++i) {
        this->hashTable[i].swap(other.hashTable[i]);
        this->isAvailable[i] = other.isAvailable[i];
    }

}

HashTable &HashTable::operator=(const HashTable &other) {
    if(this == &other) {
        return *this;
    }

    free(this->hashTable);
    free(this->isAvailable);
    this->curretnSize = other.curretnSize;
    this->hashTable = (shared_ptr<Player>*)malloc(other.curretnSize*sizeof(shared_ptr<Player>));
    this->isAvailable = (int*) malloc(other.curretnSize*sizeof(int));
    for(int i=0;i<other.curretnSize;++i) {
        this->hashTable[i].swap(hashTable[i]);
        this->isAvailable[i] = other.isAvailable[i];
    }
    return *this;

}
//HashTable::~HashTable() {
//    free(this->hashTable);
//    free(this->isAvailableToSearch);
//}

int HashTable::hash1(int key) {
    return key % this->sizeOfTable;
}

int HashTable::hash2(int key) {
    return 1 + key % this->sizeOfHash2;
}



int HashTable::insertHash(shared_ptr<Player> player) {
//    if(player->getPlayerId() == 27644){
//        cout<< 444 <<endl;
//    }
//    if(this->findInHashTable(player->getPlayerId())!=-1){
//        return -1;
//    }


    if(this->isTableFull()){
        this->ExpandTable();
    }
    int hash1Index = hash1(player->getPlayerId());
    int hash2Index = hash2(player->getPlayerId());

    if(!this->isAvailable[hash1Index]){
        int k = 0;
        bool isFound = false;
        while(!isFound){
            int newIndex = (hash1Index+k*hash2Index)%this->sizeOfTable;
            if(this->isAvailable[newIndex]){
                hashTable[newIndex].swap(player);
                this->isAvailable[newIndex]=0;
                isFound = true;
                this->curretnSize++;
                return newIndex;
            }
            k++;
        }
    }
    else{

        hashTable[hash1Index].swap(player);
        this->isAvailable[hash1Index] = 0;
        this->curretnSize++;
        return hash1Index;
    }
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

    int hash1Index = hash1(playerId);
    int hash2Index = hash2(playerId);
    int k = 0;
    bool isFound = false;
    while(!isFound){
        int newIndex = (hash1Index+k*hash2Index)%this->sizeOfTable;
        if(this->isAvailable[newIndex]){
            return -1;
        }
        if(!this->isAvailable[newIndex]){
            if(this->hashTable[newIndex]->getPlayerId() == playerId){
                isFound = true;
                return newIndex;
            }
        }
        k++;
    }
    return -1;
}

void HashTable::ExpandTable() {

    this->PowerOf2Index++;
    int newSize = pow(2,this->PowerOf2Index)-1;

    HashTable newHashTable(newSize,newSize-1,this->PowerOf2Index);
    for(int i=0;i<this->sizeOfTable;++i){
        if(!this->isAvailable[i]) {
            newHashTable.insertHash(this->hashTable[i]);
        }
    }
    this->hashTable = new shared_ptr<Player>[newSize];
    for(int i=0;i<newSize;++i){
        this->hashTable[i].swap(newHashTable.hashTable[i]);
    }
    free(this->isAvailable);
    this->isAvailable = new int[newSize];
    for(int i=0;i<newSize;i++){
        this->isAvailable[i] = newHashTable.getAvailability(i);
    }
    this->sizeOfTable = newSize;
    this->sizeOfHash2 = newSize - 3;
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
    if(this->curretnSize >=(float)(0.5 *this->sizeOfTable)){
        return true;
    }
    return false;
}

void HashTable::printTable() {
    for(int i=0;i< this->sizeOfTable;++i){
        if(!isAvailable[i]){
            cout<<i<<" "<< this->hashTable[i]->getPlayerId()<<endl;
        }
    }
}

shared_ptr<Player> &HashTable::getPlayerinIndex(int index) {
    return this->hashTable[index];
}

int HashTable::getTableSize() {
    return this->sizeOfTable;
}

int HashTable::getCurrentSize() {
    return this->curretnSize;
}

int HashTable::getAvailability(int index) {
    return this->isAvailable[index];
}