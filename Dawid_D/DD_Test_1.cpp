// EE4013 - Assignment 1
// Release 1 - Test file 1 
// by Dawid Drewicz 
//
// DD_Test_1.cpp

#include "R1_DD.h"

int main()
{
    integer_item base_item; 

    base_item.generateRandomItem(); 
    base_item.printItemTypeName();
    base_item.printItemOnScreen(); 

    integer_itemWithLimits my_item1; 

    //my_item.generateRandomItem(); 
    my_item1.enterItemFromKeyboard(); 
    my_item1.printItemTypeName();
    my_item1.printItemOnScreen();

    integer_itemWithLimits my_item2;
    
    my_item2.generateRandomItem(); 
    my_item2.printItemOnScreen(); 

    integer_itemWithLimits my_item3;
    my_item3.enterItemFromKeyboard(); 
    //my_item3.generateRandomItemWithinLimits(10,20); // check if it possible to store item that's not within limit's.
    my_item3.printItemOnScreen(); 



    

    return 0; 
}