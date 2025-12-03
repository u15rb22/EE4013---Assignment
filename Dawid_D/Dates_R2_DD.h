// EE4013 - Assignment 1
// Release 2 - Group 1 - Date of birth 
// by Dawid Drewicz 
//
// Dates_R2_DD.h

#ifndef DATES_R2_DD_H 
#define DATES_R2_DD_H

#include "R1_DD.h"

class year_Item: public integer_itemWithLimits{
    protected:
        bool leap_year;

    private:
        //using integer_itemWithLimits::generateRandomItem;
    public:
        year_Item()
        {
            itemTypeName = "year_item";
            setLimits(1915,2025); // 110 years should be good 
            leap_year = false; // set dafult as not leap year
        }

        ~year_Item(){;}

        bool is_leapYear(int year) const
        {
            int by4, by100, by400;
            bool Leap = false; 

            by4 = year % 4;
            by100 = year % 100; 
            by400 % 400; 

            if(((by4 == 0)&&(by100 != 0)) || ((by4 == 0)&&(by100 == 0)&&(by400 == 0)) )
                Leap = true;
            
            return Leap; 

        }

        bool GetLeapStatues() const
        {
            if(isEmpty())
                cout << "* Note: Item is Empty" << endl;
            return leap_year; 
        }

        virtual void printItemOnScreen() const 
        {
            if(isEmpty())
                cout << "Item is empty." << endl; 
            else
            {
                cout << " The Year is : "<< item_value << "." ; 
                cout << " which is " ;

                if(leap_year)
                    cout << "a Leap Year.";
                else 
                    cout << "NOT a Leap Year.";
                cout << endl;
            }
        }

        virtual void enterValueFromKeyboard()
        {
            bool Valid_int = false;
            while(!Valid_int)
            {
		        cout << "Insert a Year then hit enter." << endl;
		        cin >> item_value;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "* Warning: Input must be an integer." << endl; 
                    cout << endl;
                }
                else
                {
                    if(inLimits(item_value))
                        Valid_int = true; 
                    else
                    {
                        cout << "*Warning*: year must fall within set limits :"<< max_val << "-" << min_val << endl << endl;  
                    } 
                } 
            }

            leap_year = is_leapYear(item_value);
            empty = false;

        }

        virtual void generateRandomItem()// generates random Year
        {
            if(isLocked())
                cout << "Error in generateRandomitem: Item is Locked." << endl;
            else 
            {
                generateRandomItem();
                leap_year = is_leapYear(item_value);
            }
        }
        

};

enum months { January = 1, February, March, April, May, June, July, August, September, October, November, December };

class month_Item: public integer_itemWithLimits{
    protected:
        string month_text; 

        virtual string PassMonthtext(int monthVal)
        {
            
        }
    public: 
        month_Item()
        {
            itemTypeName = "month_item";
            setLimits(1,12); 
        }

        ~month_Item(){;}

        

};

class day_Item: public integer_itemWithLimits{

};

class dates_composite_Item: public basic_item{
    protected:
        year_Item Year;
        month_Item Month;
        day_Item Day; 
};

#endif