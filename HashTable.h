//
// Created by Nir on 12/21/2022.
//

#ifndef DATASTRUCTURES2_HASHTABLE_H
#define DATASTRUCTURES2_HASHTABLE_H

#include "Player.h"
#include "memory"
#include "List.h"

class HashTable{


public:

    HashTable();
    HashTable(int tableSize ,int PowerOf2Index);
    HashTable(const HashTable& hashTable);
    HashTable& operator=(const HashTable& hashTable);
    ~HashTable() = default;

    bool isTableFull();
    void ExpandTable();
    int hash(int key);
    int insertHash(shared_ptr<Player> player);
    void removeFromTable(shared_ptr<Player> player);
    void RahashTable();
    void printTable();
    int findInHashTable(int playerId);
    int getTableSize();
    shared_ptr<Player>& getPlayerinIndex(int index);
    int getCurrentSize();
    int getAvailability(int index);










private:

    List* hashTable;
    int curretnSize;
    int sizeOfTable;
    int PowerOf2Index;










};
#endif //DATASTRUCTURES2_HASHTABLE_H
