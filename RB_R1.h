#ifndef RB_R1_h
#define RB_R1_h

#include "ArrayItem_v3.h"

class integer_itemWithLimits_Ryan : public integer_item{
    protected:
        bool rangeSet;
        int minValRange, maxValRange;
    public:
        //Constructor 
        integer_itemWithLimits_Ryan(){
            //Range has not been set by the user
            rangeSet = false;
            //Setting default limits
            maxValRange = 50;
            minValRange = -50;
            //Setting the item name
            itemTypeName = "integer_itemWithLimits.";
        } 
        //Deconstructor 
        ~integer_itemWithLimits_Ryan(){;}

        void enterSetRangeFromKeyboard(){
            char limit_change;
            cout << "Do you want to change integer limits? (Type Y for yes)" << endl;
            cin >> limit_change;
            if((limit_change == 'Y') || (limit_change == 'y')){
                while(!rangeSet){
                
                    cout << "Insert Maximum Range then hit enter." << endl;
		            cin >> maxValRange;
		            cout << endl;

		            cout << "Insert Minimum Range then hit enter." << endl;
		            cin >> minValRange;
			        cout << endl;

                    if(maxValRange < minValRange){
                        cout << "Error: Limits entered in the wrong order, they are now corrected." << endl;
                        int temp = maxValRange;
                        maxValRange = minValRange;
                        minValRange = temp;
                    }

                    if(maxValRange > minValRange){
                        rangeSet = true;
                    }      
                }
            }
            else{
                cout << "Keeping the default limits [-50, 50]." << endl;
                rangeSet = true;
            }
             
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
            else{
                cout << "Error in printItemAndRange: Range has not been set." << endl;
            }                   
        } 
        
        int getMinValRange(){
            if(rangeSet){
                return minValRange;
            }
            else{
                cout << "Error in getMinValRange: Range has not been set." << endl;
                return -1;
            }     
        }

        int getMaxValRange(){
            if(rangeSet){
                return maxValRange;
            }
            else{
                cout << "Error in getMinValRange: Range has not been set." << endl;
                return -1;
            }
        }

        void generateRandomItemWithinRange(){
            if(empty){
                generateRandomItemWithinLimits(minValRange, maxValRange);
            }
            else{
                cout << "Error: Item already set." << endl;
            }
        }
};

#endif