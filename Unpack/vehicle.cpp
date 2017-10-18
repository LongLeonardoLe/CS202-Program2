/**************************************************************************
 *
 *  Name: Long Le
 *  PSU ID: 923532743
 *
 *  File name: vehicle.cpp
 *  Purpose: Implementation of vehicle.h
 *
 ***************************************************************************/

#include "vehicle.h"

/************************** class node ************************/
node::node()
{
    this->size = 10;
    this->data = new int[this->size];
    this->pos = 0;
    this->next = NULL;
}

node::node(int size)
{
    this->size = size;
    this->data = new int[this->size];
    this->pos = 0;
    this->next = NULL;
}

node::node(const node& n)
{
    this->size = n.size;
    this->pos = n.pos;
    this->data = new int[this->size];
    for (int i = 0; i < pos; ++i)
        this->data[i] = n.data[i]; 
    this->next = n.next;
}

//destructor
node::~node()
{
    delete this->data;
    this->next = NULL;
    this->data = NULL;
}

//go to the next node
node*& node::goNext()
{
    return this->next;
}

//display
void node::display() const
{
    for (int i = 0; i < pos; ++i)
        std::cout << this->data[i] << std::endl;
}

//calculate the average
float node::getAvg()
{
    float  sum = 0;
    for (int i = 0; i < this->pos; ++i)
        sum += this->data[i];
    return sum/pos;
}

//add rating
bool node::addValue(int n)
{
    if (this->pos == this->size)
        return false;
    this->data[pos++] = n;
    return true;
}

//connect next
void node::connectNext(node*& n)
{
    if (!n)
        return;
    this->next = new node(*n);
}

/************************** class history ************************/
//default constructor
history::history()
{
    this->head = NULL;
}

//copy constructor
history::history(const history& h)
{
    this->copyList(this->head, h.head);
}

//destructor
history::~history()
{
    node* cur = this->head;
    while(head)
    {
        this->head = this->head->goNext();
        delete cur;
        cur = this->head;
    }
}

//copy list
void history::copyList(node*& des, node* src)
{
    if (!src)
        return;
    des = new node(*src);

    this->copyList(des->goNext(), src->goNext());
}

//display list
void history::displayList(node* head) const
{
    if (!head)
        return;
    head->display();

    this->displayList(head->goNext());
}

//display
void history::display() const
{
    this->displayList(this->head);
}

//add a new rating
void history::addRate(int rate)
{
    if (!this->head)
    {
        this->head = new node();
        this->head->addValue(rate);
        return;
    }
    if (this->head->addValue(rate) == true)
        return;
    node* n = new node();
    n->addValue(rate);
    n->connectNext(this->head);
    this->head = n;
}

//return the average rate
float history::avg() const
{
    if (!this->head)
        return 0;
    float size = 0;
    float avg = 0;
    node* cur = this->head;
    while(cur)
    {
        avg += this->head->getAvg();
        size+=1;
        cur = cur->goNext();
    }
    return avg/size;
}

//add a node
void history::addNode(node*& n)
{
    n->connectNext(this->head);
    this->head = n;
}

/************************** class vehicle ************************/
vehicle::~vehicle()
{
}

//display
void vehicle::display() const
{
    using namespace std;
    cout << "Fare: " << this->fee << endl;
    if (this->status == true)
        cout << "The vehicle is not delayed.\n";
    else cout << "The vehicle has a high chance to be delayed.\n";
    cout << "The average rating: " << this->exp.avg() << endl;
}

/************************** class uber ************************/
//default constructor
uber::uber()
{
    using namespace std;
    cout << "Fee per 100 meters: ";
    cin >> this->fee;

    int hour;
    cout << "The planned hour to travel: ";
    cin >> hour;
    if (hour >= 17 && hour <= 20)
        this->status = false;
    else this->status = true;

    cout << "Is there any review you want to add? (Y/N): ";
    char response;
    cin >> response;
    cin.ignore(1000, '\n');
    if (toupper(response) == 'Y')
    {
        do
        {
            cout << "Your rating: ";
            int rate;
            cin >> rate;
            this->exp.addRate(rate);
            cout << "Other review? (Y/N): ";
            cin >> response;
            cin.ignore(1000, '\n');
        } while (toupper(response) == 'Y');
    }
    cout << "How long do you want to travel (m)?: ";
    cin >> this->distance;
}

uber::~uber()
{
}

//get fare
float uber::getFare() const
{
    return this->fee/100*this->distance;
}

//display()
void uber::display() const
{
    vehicle::display();
    std::cout << "Distance travelled: " << this->distance << " m.\n";
    std::cout << "Total fare: $" << this->getFare() << std::endl;
}

//let the user rate the vehicle
void uber::rate()
{
    using namespace std;
    cout << "Do you want to rate this Uber car? (Y/N): ";
    char response;
    cin >> response;
    cin.ignore(1000, '\n');
    if (toupper(response) == 'Y')
    {
        cout << "Your rating: ";
        int rate;
        cin >> rate;
        this->exp.addRate(rate);
    }
    else return;
}

/************************** class maxTrans ************************/
maxTrans::maxTrans()
{
    using namespace std;
    this->fee = 2.5;

    int hour;
    cout << "The planned hour to travel: ";
    cin >> hour;
    if (hour >= 17 && hour <= 20)
        this->status = false;
    else this->status = true;

    cout << "Is there any review you want to add? (Y/N): ";
    char response;
    cin >> response;
    cin.ignore(1000, '\n');
    if (toupper(response) == 'Y')
    {
        do
        {
            cout << "Your rating: ";
            int rate;
            cin >> rate;
            this->exp.addRate(rate);
            cout << "Other review? (Y/N): ";
            cin >> response;
            cin.ignore(1000, '\n');
        } while (toupper(response) == 'Y');
    }
}

maxTrans::~maxTrans()
{
}

//get fare
float maxTrans::getFare() const
{
    return this->fee;
}

//display
void maxTrans::display() const
{
    vehicle::display();
}

//let the user rate the vehicle
void maxTrans::rate()
{
    using namespace std;
    cout << "Do you want to rate this MAX train? (Y/N): ";
    char response;
    cin >> response;
    cin.ignore(1000, '\n');
    if (toupper(response) == 'Y')
    {
        cout << "Your rating: ";
        int rate;
        cin >> rate;
        this->exp.addRate(rate);
    }
    else return;
}

/************************** class streetcar ************************/
streetcar::streetcar()
{
    using namespace std;
    char response;

    cout << "Are you a PSU student? (Y/N): ";
    cin >> response;
    cin.ignore(1000, '\n');
    if (toupper(response) == 'Y')
        this->fee = 0;
    else this->fee = 2.5;

    int hour;
    cout << "The planned hour to travel: ";
    cin >> hour;
    if (hour >= 17 && hour <= 20)
        this->status = false;
    else this->status = true;

    cout << "Is there any review you want to add? (Y/N): ";
    cin >> response;
    cin.ignore(1000, '\n');
    if (toupper(response) == 'Y')
    {
        do
        {
            cout << "Your rating: ";
            int rate;
            cin >> rate;
            this->exp.addRate(rate);
            cout << "Other review? (Y/N): ";
            cin >> response;
            cin.ignore(1000, '\n');
        } while (toupper(response) == 'Y');
    }
}

streetcar::streetcar(bool isPSU)
{
    this->isPSU = isPSU;
}

streetcar::~streetcar()
{
}

void streetcar::display() const
{
    vehicle::display();
}

//get fare
float streetcar::getFare() const
{
    if (this->isPSU == true)
        return 0;
    return 2.5;
}

//let the user rate the vehicle
void streetcar::rate()
{
    using namespace std;
    cout << "Do you want to rate this street car? (Y/N): ";
    char response;
    cin >> response;
    cin.ignore(1000, '\n');
    if (toupper(response) == 'Y')
    {
        cout << "Your rating: ";
        int rate;
        cin >> rate;
        this->exp.addRate(rate);
    }
    else return;
}

