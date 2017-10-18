/***************************************************************************
 *
 *  Name: Long Le
 *  PSU ID: 923532743
 *
 *  File name: vehicle.h
 *
 ***************************************************************************/

#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <cstring>
#include <time.h>

//class review node
class node
{
    public:
        node();
        node(const node& n); //copy constructor
        node(int size); //constructor with size
        ~node(); //destructor
        node*& goNext(); //go to the next node
        void display() const; //display review
        void connectNext(node*& n); //connect to the next
        bool addValue(int n); //add new rating
        float getAvg(); //calculate the average rate

    protected:
        int* data;
        int size, pos; //size and current available new data
        node* next;
};

//class history
class history
{
    public:
        history(); //default constructor
        history(const history& h); //copy constructor
        ~history();
        void addNode(node*& n); //add the new node
        void display() const; //display the list
        void addRate(int n); //add a new rating
        float avg() const; //calculate the average

    protected:
        node* head;

        void copyList(node*& des, node* src);
        void displayList(node* head) const;
};

//abstract base class: vehicle
class vehicle
{
    public:
        virtual ~vehicle();
        virtual void display() const;
        virtual float getFare() const = 0;
        virtual void rate() = 0;

    protected:
        float fee; //fee for each vehicle
        bool status; //delay or not
        history exp; //passenger history
};

class uber : public vehicle
{
    public:
        uber();
        ~uber();
        void display() const;
        float getFare() const;
        void rate();

    protected:
        float distance;
};

class maxTrans : public vehicle
{
    public:
        maxTrans();
        ~maxTrans();
        void display() const;
        float getFare() const;
        void rate();

    protected:
};

class streetcar : public vehicle
{
    public:
        streetcar();
        streetcar(bool isPSU);
        ~streetcar();
        void display() const;
        float getFare() const;
        void rate();

    protected:
        bool isPSU;
};

#endif

