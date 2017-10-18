/***************************************************************************
 *
 *  Name: Long Le
 *  PSU ID: 923532743
 *
 *  File name: popularity.h
 *  Purpose: header file of popularity concept
 *
 ***************************************************************************/

#ifndef POPULARITY_H
#define POPULARITY_H
#include "vehicle.h"
#include <fstream>

class popularityNode
{
    public:
        popularityNode(); //default constructor
        popularityNode(const popularityNode& n); //copy constructor
        popularityNode(int type, char* interval, int pop);
        ~popularityNode(); //destructor
        popularityNode*& goNext();
        void display() const;
        void connectNext(popularityNode*& n);

    protected:
        int type; //to check to type of the node
        char* interval; //time interval
        int pop; //population
        popularityNode* next;
};

class popularity
{
    public:
        popularity();
        popularity(const popularity& p);
        ~popularity();
        void generate();
        void display() const;
        
    protected:
        int size;
        popularityNode** head;

        void copyList(popularityNode*& des, popularityNode* src);
        void deleteList(popularityNode*& head);
        void addNode(popularityNode*& head, popularityNode*& n);
        void displayList(popularityNode* head) const;
};

#endif

