/***************************************************************************
 *
 *  Name: Long Le
 *  PSU ID: 923532743
 *
 *  File name: popularity.cpp
 *  Purpose: Implementation of popularity.h
 *
 ***************************************************************************/

#include "popularity.h"

/************************** class popularityNode *********************/
//default constructor
popularityNode::popularityNode()
{
    this->interval = NULL;
    this->next = NULL;
}

//copy constructor
popularityNode::popularityNode(const popularityNode& n)
{
    this->type = n.type;
    this->interval = new char[strlen(n.interval)+1];
    strcpy(this->interval, n.interval);
    this->pop = n.pop;
    this->next = NULL;
}

//constructor
popularityNode::popularityNode(int type, char* interval, int pop)
{
    this->type = type;
    this->interval = new char[strlen(interval)+1];
    strcpy(this->interval, interval);
    this->pop = pop;
    this->next = NULL;
}

//destructor
popularityNode::~popularityNode()
{
    this->next = NULL;
    delete this->interval;
    this->interval = NULL;
}

//go to the next node
popularityNode*& popularityNode::goNext()
{
    return this->next;
}

//display the node
void popularityNode::display() const
{
    std::cout << this->interval << ": " << this->pop << std::endl;
}

//connect the next node
void popularityNode::connectNext(popularityNode*& n)
{
    if (!n)
        return;
    this->next = new popularityNode(*n);
}

/************************ class popularity *******************************/
//default constructor
popularity::popularity()
{
    this->head = NULL;
}

//copy constructor
popularity::popularity(const popularity& p)
{
    this->size = p.size;
    for (int i = 0; i < this->size; ++i)
        this->copyList(this->head[i], p.head[i]);
}

//destructor
popularity::~popularity()
{ 
    for (int i = 0; i < this->size; ++i)
        this->deleteList(this->head[i]);
    delete this->head;
    this->head = NULL;
}

//copy list
void popularity::copyList(popularityNode*& des, popularityNode* src)
{
    if (!src)
        return;
    des = new popularityNode(*src);
    this->copyList(des->goNext(), src->goNext());
}

//delete the list
void popularity::deleteList(popularityNode*& head)
{
    popularityNode* cur = head;
    while(head)
    {
        head = head->goNext();
        delete cur;
        cur = head;
    }
}

//display
void popularity::display() const
{
    for (int i = 0; i < this->size; ++i)
        this->displayList(this->head[i]);
}

//add another node to a list
void popularity::addNode(popularityNode*& head, popularityNode*& n)
{
    n->connectNext(head);
    head = n;
}

//display one list
void popularity::displayList(popularityNode* head) const
{
    if (!head)
        return;
    this->displayList(head->goNext());
    head->display();
}

//generate the popularity
void popularity::generate()
{
    this->size = 3;
    this->head = new popularityNode*[3];
    using namespace std;
    char response;

    cout << "Input popularity for vehicles.\n";
    for (int i = 0; i < this->size; ++i)
    {
        if (i == 0)
            cout << "1. Uber\n";
        else if (i == 1)
            cout << "2. MAX Train\n";
        else cout << "3. Street car\n";

        do
        {
            cout << "Time interval: ";
            char* tmp = new char[256];
            cin.getline(tmp, 256, '\n');
            cout << "Population: ";
            int pop;
            cin >> pop;
            popularityNode* n = new popularityNode(i+1, tmp, pop);
            this->addNode(this->head[i], n);
            cout << "Do you want to input another time interval? (Y/N): ";
            cin >> response;
            cin.ignore(1000, '\n');
        }
        while (toupper(response) == 'Y');
    }
}

