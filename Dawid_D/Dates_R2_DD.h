// EE4013 - Assignment 1
// Release 2 - Group 1 - Date of birth 
// by Dawid Drewicz 
//
// Dates_R2_DD.h

#ifndef DATES_R2_DD_H 
#define DATES_R2_DD_H

#include "R1_DD.h"

// \/ set range for acceptable year Limits,  defualt 110 year range
#define minYear 1915   
#define MaxYear 2025

class year_Item: public integer_itemWithLimits{
    protected:
        bool leap_year;

        void updateMaxYear(int YoE)  
        {
            if(isLocked())
                cout << "Item is Locked." << endl;
            else 
                setLimits(minYear, (YoE));
        }

    private:
        using integer_itemWithLimits::enterItemFromKeyboard;
        using integer_itemWithLimits::enterLimitsFromKeyboard;
    public:
        year_Item()
        {
            itemTypeName = "year_item";
            setLimits(minYear,MaxYear); // 110 years should be good 
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
            if(isLocked())
                cout << "Item is Locked." << endl;
            else
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
                            cout << "*Warning*: year must fall within set limits :"<< min_val << "-" << max_val << endl << endl;  
                        } 
                    } 
                }

                leap_year = is_leapYear(item_value);
                empty = false;
            }
        }

        virtual void enterValueFromKeyboard(int YoE)
        {
            updateMaxYear(YoE - 18);        // assume must be min 18 to enrol 
            enterValueFromKeyboard(); 
        }

        virtual void generateRandomItem()// generates random Year
        {
            if(isLocked())
                cout << "Error in generateRandomitem: Item is Locked." << endl;
            else 
            {
                integer_itemWithLimits::generateRandomItem();
                leap_year = is_leapYear(item_value);
            }
        }

        virtual void generateRandomItem(int YoE)// generates random Year not exceeding YoE
        {
            updateMaxYear(YoE-18);  // assume must be min 18 to enrol 
            generateRandomItem();
        }
        

};

enum months { January = 1, February, March, April, May, June, July, August, September, October, November, December };

class month_Item: public integer_itemWithLimits{
    protected:
        string month_text; 

        virtual string PassMonthText(int monthVal)
        {
            string text; 

            switch (monthVal)
            {
            case January:
                text = "January";
                break;
            case February:
                text = "February";
                break;
            case March:
                text = "March";
                break;
            case April:
                text = "April";
                break;
            case May:
                text = "May";
                break;
            case June:
                text = "June";
                break;
            case July:
                text = "July";
                break;
            case August:
                text = "August";
                break;
            case September:
                text = "September";
                break;
            case October:
                text = "October";
                break;
            case November:
                text = "November";
                break;
            case December:
                text = "December";
                break;
            
            default:
                cout << "Error in PassMonthtext: value passed not in 1-12." << endl;
                break;
            }

            return text; 
        }

        virtual void SetMonth_text()
        {
            month_text = PassMonthText(item_value); 
        }


    private:
        using integer_itemWithLimits::enterItemFromKeyboard;
        using integer_itemWithLimits::enterLimitsFromKeyboard;

    public: 
        month_Item()
        {
            itemTypeName = "month_item";
            setLimits(1,12); 
        }

        ~month_Item(){;}

        virtual void printItemOnScreen() const 
        {
            if(isEmpty())
                cout << "Item is empty." << endl; 
            else
            {
                cout << " The Month is : "<< month_text ;
                cout << ". Which is month number : " << item_value << endl;
            }
        }

        virtual void generateRandomItem()// generates random Month
        {
            if(isLocked())
                cout << "Error in generateRandomitem: Item is Locked." << endl;
            else 
            {
                integer_itemWithLimits::generateRandomItem();
                SetMonth_text();
            }
        }

        virtual void enterValueFromKeyboard()
        {
            if(isLocked())
                cout << "Item is Locked."<< endl;
            else
            {
                bool Valid_int = false;
                while(!Valid_int)
                {
		            cout << "Insert a Month in numerical format then hit enter." << endl;
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
                            cout << "*Warning*: there is 12 months, you must enter a value between :"<< min_val << "-" << max_val << endl << endl;  
                        } 
                    } 

                }

                SetMonth_text();
                empty = false;
            }
        }

};

class day_Item: public integer_itemWithLimits{  
    protected:
        int month_val;
        bool inLeapYear; 

        int NumbOfDaysIn(int month)
        {
            int NumOfDays; 

            if((month ==March)||(month ==May)||(month ==July)||(month ==August)||(month ==October)||(month ==December))
                NumOfDays = 31;
            else if((month ==June)||(month ==September)||(month ==November))
                NumOfDays = 30;
            else 
            {
                if(inLeapYear)
                    NumOfDays = 29;
                else
                    NumOfDays = 28;
            }
            return NumOfDays;
        }

        using integer_itemWithLimits::enterItemFromKeyboard;
        using integer_itemWithLimits::enterLimitsFromKeyboard;

        void setDays()
        {
            setLimits(1,NumbOfDaysIn(month_val));
        }

    public: 
        day_Item()
        {
            itemTypeName = "day_item";
            month_val = January; // set defult as 1
            inLeapYear = false; // deafult not as not leap year 
            setLimits(1,31);
        }

        ~day_Item(){;}

        virtual void printItemOnScreen() const 
        {
            if(isEmpty())
                cout << "Item is empty." << endl; 
            else
            {
                cout << " The Day is : # "<< item_value ;
                cout << ". in month number : " << month_val << " . Which has : "<< max_val; 
                cout << " Days. and is "; 
                if(inLeapYear)
                    cout << "in a Leap Year." << endl;
                else 
                    cout << "in a Non-Leap year." << endl;
            }
        }

        virtual void generateRandomItem()// generates random day within set month
        {
            if(isLocked())
                cout << "Error in generateRandomitem: Item is Locked." << endl;
            else 
            {
                setDays();
                integer_itemWithLimits::generateRandomItem();
            }
        }

        virtual void generateRandomItem(int monthIn, bool LeapYearIn)
        {
            if(isLocked())
                cout << "Error in generateRandomItem(int,bool): Item is Locked." << endl;
            else
            {
                if((monthIn<=12)&&(monthIn>=1))
                {
                    month_val = monthIn; 
                    inLeapYear = LeapYearIn;
                    generateRandomItem();
                }
                else
                    cout << "Error in generateRandomItem(int,bool): Invalid passed month value ." << endl;
            }
            
        }

        virtual void enterValueFromKeyboard()
        {
            if(isLocked())
                cout << "Item is Locked."<< endl;
            else
            {
                bool Valid_int = false;
                setDays();
                while(!Valid_int)
                {
		            cout << "Insert number of Day then hit enter." << endl;
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
                            cout << "*Warning*: there is " << max_val << " days in chosen month, you must enter a value between :"<< min_val << "-" << max_val << endl << endl;  
                        } 
                    } 

                }
                
                empty = false;
            }
        }

        virtual void enterValueFromKeyboard(int monthIn, bool LeapYearIn)
        {
            if(isLocked())
                cout << "Error in enterValuefromkeyboard(int,bool): Item is Locked." << endl;
            else
            {
                if((monthIn<=12)&&(monthIn>=1))
                {
                    month_val = monthIn; 
                    inLeapYear = LeapYearIn;
                    enterValueFromKeyboard();
                }
                else
                    cout << "Error in enterValuefromkeyboard(int,bool): Invalid passed month value ." << endl;
            }
            
        }

};

class dates_composite_Item: public basic_item{
    protected:
        year_Item Year;
        month_Item Month;
        day_Item Day; 

    public:
        dates_composite_Item()
        {
            itemTypeName = "dates_composite_item";
        }

        ~dates_composite_Item(){;}

        virtual int getYearVal() const 
        {
            return Year.getItemVal();
        }

        virtual int getMonthVal() const 
        {
            return Month.getItemVal();
        }

        virtual int getDayVal() const 
        {
            return Day.getItemVal();
        }

        virtual void printItemOnScreen() const
        {
            if(isEmpty())
                cout << "Item is Empty." << endl;
            else
            {
                Year.printItemTypeName();
                Year.printItemOnScreen();
                Month.printItemTypeName();
                Month.printItemOnScreen();
                Day.printItemTypeName();
                Day.printItemOnScreen();
            }
        }

        virtual void generateRandomItem()
        {
            if(isLocked())
                cout << "Error in generateRandomitem: Item is Locked." << endl;
            else 
            {
                Year.generateRandomItem();
                Month.generateRandomItem();
                Day.generateRandomItem(Month.getItemVal(),Year.GetLeapStatues());
                empty = false;
            }
        }

        virtual void generateRandomItem(int YoE) // created to prevent DoB's after YoE
        {
            if(isLocked())
                cout << "Error in generateRandomitem: Item is Locked." << endl;
            else 
            {
                //Year.
                Year.generateRandomItem(YoE);
                Month.generateRandomItem();
                Day.generateRandomItem(Month.getItemVal(),Year.GetLeapStatues());
                empty = false;
            }
        }


        
	virtual void enterItemFromKeyboard()
    {
        if(isLocked())
                cout << "Error in enterItemfromKeyboard: Item is Locked." << endl;
            else 
            {
                Year.enterValueFromKeyboard();
                Month.enterValueFromKeyboard();
                Day.enterValueFromKeyboard(Month.getItemVal(),Year.GetLeapStatues());
                empty = false;
            }
    }

    virtual void enterItemFromKeyboard(int YoE)
    {
        if(isLocked())
                cout << "Error in enterItemfromKeyboard: Item is Locked." << endl;
            else 
            {
                Year.enterValueFromKeyboard(YoE);
                Month.enterValueFromKeyboard();
                Day.enterValueFromKeyboard(Month.getItemVal(),Year.GetLeapStatues());
                empty = false;
            }
    }


	virtual bool compatibilityCheck(const basic_item* other_item) const
    {
        ;
    }
	virtual bool IsLargerThan(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const 
    {
        ;
    }	
	virtual bool IsEqualTo(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const
    {
        ;
    }	


        
};

#endif