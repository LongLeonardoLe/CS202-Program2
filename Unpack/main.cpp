/***************************************************************************
 *
 *  Name: Long Le
 *  PSU ID: 923532743
 *
 *  File name: main.cpp
 *
 ***************************************************************************/

#include "popularity.h"

int main()
{
    popularity p;
    p.generate();

    std::cout << "-----------------------------" << std::endl;
    vehicle* ptr;
    std::cout << "Which wehicle do you want to use?\n1.Uber\n2.MAX Train\n3.Street car\n";
    int choice;
    std::cin >> choice;
    if (choice < 1 || choice > 3)
    {
        std::cout << "Re-enter: ";
        std::cin >> choice;
    }

    switch (choice)
    {
        case 1:
            {
                ptr = new uber();
                ptr->rate();
                ptr->display();
                break;
            }
        case 2:
            {
                ptr = new maxTrans();
                ptr->rate();
                ptr->display();
                break;
            }
        case 3:
            {
                ptr = new streetcar();
                ptr->rate();
                ptr->display();
                break;
            }
        default:
            break;
    }

    return 0;
}

