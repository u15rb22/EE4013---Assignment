// EE4013 - Assignment 1
// Release 2 - Test file 1 
// by Dawid Drewicz 
//
// DD_Test_2.cpp

#include "Dates_R2_DD.h"

void test1_randGenIndiv()
{
    cout << "test1_randGenIndiv" << endl;
    year_Item the_year; 

    the_year.generateRandomItem(); 
    the_year.printItemTypeName();
    the_year.printItemOnScreen();

    month_Item the_month; 

    the_month.generateRandomItem(); 
    the_month.printItemTypeName();
    the_month.printItemOnScreen();

    day_Item the_day;

    the_day.generateRandomItem(); 
    the_day.printItemTypeName();
    the_day.printItemOnScreen();
    

}

void test1_randGen()
{
    cout << "test1_randGen" << endl;
    
    dates_composite_Item Date;

    Date.generateRandomItem(); 
    Date.printItemTypeName();
    Date.printItemOnScreen();

}


void test2_InputIndiv()
{
    cout << "test1_randGenIndiv" << endl;
    year_Item the_year; 

    the_year.printItemTypeName();
    the_year.printItemOnScreen();
    the_year.enterValueFromKeyboard();
    the_year.printItemOnScreen();

    month_Item the_month; 
 
    the_month.printItemTypeName();
    the_month.printItemOnScreen();
    the_month.enterValueFromKeyboard();
    the_month.printItemOnScreen();

    day_Item the_day;
     
    the_day.printItemTypeName();
    the_day.printItemOnScreen();
    the_day.enterValueFromKeyboard();
    the_day.printItemOnScreen();


}

int main()
{
    //test1_randGenIndiv();
    //test2_InputIndiv();

    test1_randGen();
    test1_randGen();
    test1_randGen();
    test1_randGen();

    return 0;
}