#ifndef Ryan-Release1_h
#define Ryan-Release1_h

#include "ArrayItem_v3.h"

class integer_itemWithLimits_Ryan : public integer_item{
    protected:
        bool rangeSet;
        int minValRange, maxValRange;
    public:
        integer_itemWithLimits_Ryan(){
            //Range has not been set by the user
            rangeSet = false;
            //Setting default limits
            maxValRange = 50;
            minValRange = -50;
        } 

        void enterSetRangeFromKeyboard(){
            if(!rangeSet){
                cout << "Insert Maximum Range then hit enter." << endl;
		        cin >> maxValRange;
		        cout << endl;

		        cout << "Insert Minimum Range then hit enter." << endl;
		        cin >> minValRange;
			    cout << endl;
                
                

                rangeSet = true;
            }
            else
                cout << "Error in enterSetRange: Range already set." << endl;
        }

        void enterItemFromKeyboardWithinRange(){
            enterItemFromKeyboard();
            while(item_value > maxValRange || item_value < minValRange){
                empty = true;
                cout << "Error: Integer out of range [" << minValRange << ", " << maxValRange << "]" << endl;
                enterItemFromKeyboard();
            }
        }

        void printItemAndRange(){
            if(rangeSet){
                printItemOnScreen();
                cout << "Range: [" << minValRange << ", " << maxValRange << "]" << endl;
            }
            else    
                cout << "Error in printItemAndRange: Range has not been set." << endl;
        } 
        
        int getMinValRange(){
            if(rangeSet){
                return minValRange;
            }
            else
                cout << "Error in getMinValRange: Range has not been set;" << endl;
        }

        int getMaxValRange(){
            if(rangeSet){
                return maxValRange;
            }
            else
                cout << "Error in getMinValRange: Range has not been set;" << endl;
        }

        void generateRandomItemWithinRange(){
            generateRandomItemWithinLimits(minValRange, maxValRange);
        }
};

#endif Ryan-Release1_h