#ifndef Release2&3_h
#define Release2&3_h

#include "ArrayItem_v3.h"
#include "generalArraywithTemplate_v2.h"
#include "Dawid_D/Dates_R2_DD.h"        //inludes Dates class

class string_item : public basic_item{
    protected:
        string item_value;
        bool stringSet;
    public:
        string_item(){
            stringSet = false;
            itemTypeName = "String";
        }
        ~string_item(){;}

        //Small function to get the string length
        int getStringLength() const {
            if(!stringSet){
                cout << "Warning: Empty item." << endl;
            }
            return item_value.length();
        }

        //Function to print the string value
        virtual void printItemOnScreen() const{
            if(stringSet){
                cout << "String value: " << item_value << endl;
            }
            else{
                cout << "Error: String has not been set." << endl;
            }
        }

        //Function to enter a string from keyboard
        virtual void enterItemFromKeyboard(){
            if(!isLocked()){

                if(!stringSet){
                    //Print is commented out for better readability in the group1 print function
                    //cout << "Enter string: " << endl;
                    cin >> item_value;
                    cout << endl;

                    //Item has been filled
                    empty = false;
                    stringSet = true;
                }
                else{
                    cout << "Error on enterItemFromKeyboard: String already set." << endl;
                }
            }
            //Cannot access item
            else{
                cout << "Error: Item is locked." << endl;
            }   
        }

        //Function to check the type of another item to the strings
        virtual bool compatibilityCheck(const basic_item* other_item) const{
            //True if the same, false if not
            bool result = false;

            //Check to see if the other item is allocated, if not skip
            if(other_item != NULL){

                //Type casting the other item to confirm its the same as the string
                const string_item* typecast_OtherItem = typecastItem(other_item, this);

                if(typecast_OtherItem != NULL){result = true;}
                else{
                    cout << "Check failed for Item type: " << itemTypeName << endl;
                }
            }

            return result;
        }
        
        virtual bool IsLargerThan(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const{
            bool result = false;

            //Check if other item is not allocated, if not dont compare
            if(other_item == NULL){return false;}

            //Type cast the other item
            const string_item* typecast_OtherItem = typecastItem(other_item, this);

            //Check if the items are the same type
            if(typecast_OtherItem == NULL){
                cout << "Error: Other item is not of the same string type." << endl;
                return false;
            }
            
            //Check if the strings have been set or not
            if(!stringSet || !typecast_OtherItem->stringSet) {
                cout << "Error: Cannot compare, one or both strings are not set." << endl;
                return false;
            }

            //Return true if the current item is larger than the other item
            if(item_value > (typecast_OtherItem->item_value) ){
                result = true;
            }
            
            //check if there are sorting options to apply 
		    if(sort_criteria!=NULL)
		    {
			    //if sorting is in descending order the result is reversed 
			    if(!( sort_criteria->getAscending())){
                    result=!result;
                }
		    }
            return result;
        }

        virtual bool IsEqualTo(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const{
            bool result = false;

            //Check if other item is not allocated, if not dont compare
            if(other_item == NULL){return false;}

            //Type cast the other item
            const string_item* typecast_OtherItem = typecastItem(other_item, this);

            //Check if the items are the same type
            if(typecast_OtherItem == NULL){
                cout << "Error: Other item is not of the same string type." << endl;
                return false;
            }
            
            //Check if the strings have been set or not
            if(!stringSet || !typecast_OtherItem->stringSet) {
                cout << "Error: Cannot compare, one or both strings are not set." << endl;
                return false;
            }

            //Return true if the current item is larger than the other item
            if(item_value == (typecast_OtherItem->item_value) ){
                result = true;
            }
            return result;
        }

        //Function to generate a random string
        virtual void generateRandomItem(){
            if(!isLocked()){
                if(!stringSet){
                    const char charSet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

                    //Random string length 1 - 10
                    int length = rand() % 10 + 1;

                    //Function to loop through the given length
                    //And append a random character from the character set 
                    //Into item_value
                    for(int i = 0; i < length; i++){
                        item_value += charSet[rand() % (sizeof(charSet) - 1)];
                    }

                    //Item is not empty and string has been set.
                    empty = false;
                    stringSet = true;
                }
                else{
                    cout << "Error in generateRandomItem: String is already set." << endl;
                }
            }
            else{
                cout << "Error: Item is locked." << endl;
            }
            
        }

        //Small function to return the string item value
        string returnString() const{
            if(!stringSet){
                cout << "Error in returnString: String has not been set." << endl;
            }
            return item_value;
        }
};

class year_of_enrolment : public integer_item{
protected:
    bool limits_initFlag;
    static int min_year, max_year;
public:
    year_of_enrolment(){itemTypeName = "Year of enrolment";}

    void setLimits()
    {
        if(!limits_initFlag)
        {
            // CHECKING WHETHER TO USE DEFAULT LIMITS OR NOT
            char limit_options;
            cout << "Add limits or use default limits? Y TO ADD, N FOR DEFAULT: ";
            cin >> limit_options;
            if(limit_options=='Y' || limit_options=='y')
            {
                cout << "Input the upper limit for the year: " << endl;
                cin >> max_year;   // Directly input into the max_year

                cout << "Input the lower limit for the year: " << endl;
                cin >> min_year;   // Directly input into the minIntVal

                // Below is checking whether the minIntVal is less than the max_year. If not, it swaps them
                if (min_year > max_year)
                {
                    cout << "Error in setLimits(): min_year is greater than max_year. They will be swapped." << endl;
                    int temp = min_year;
                    min_year = max_year;
                    max_year = temp;
                }

                if(min_year<0 || max_year<0)
                    cout << "Error in setLimits(): Limit is a negative year. Input not set." << endl;
                limits_initFlag = true; // Set the flag to true
            }
            else
            {
                cout<<"Using default years [2010, 2040]"<<endl;
                min_year = 2010;
                max_year = 2040;
                limits_initFlag = true;
            }
        }
        else
            cout << "Error in setLimits(): Limits have already been set." << endl;
    }

    virtual void enterItemFromKeyboard()
    {
        char limit_check;
        cout<<"Carry on limits or set new limits? Y TO SET NEW, N OTHERWISE: ";
        cin>>limit_check;

        if(limit_check == 'Y'||limit_check == 'y')
        {year_of_enrolment::setLimits();}
            

        cout << "Enter the value of the integer item within the set limits [" << min_year << ", " << max_year << "] :" << endl;
        integer_item::enterItemFromKeyboard();
        // Check if the input is within limits
        if(item_value < min_year || item_value > max_year)
        {
            cout << "Error in enterItemFromKeyboard(): Input year is out of limits." << endl;
            empty = true;               // Reset the item to empty if out of limits
            enterItemFromKeyboard();    // Prompt user to enter again
        }
        else 
            return;
    }

    virtual void generateRandomItem()
    {integer_item::generateRandomItemWithinLimits(min_year, max_year);}
};

class group1_sorting_criteria : public basic_sort_criteria{
public:
    enum compsiteEqualityOptions{inf_val=0, first_name, last_name, DoB, all_equal, sup_val};
protected:
	bool sort_fam_first, sort_first_name_first, sort_DoB_first;	
    bool sort_fam_second, sort_first_name_second, sort_DoB_second;
	compsiteEqualityOptions equlOpt;
public:
    basic_sort_criteria first_name_crit;
    basic_sort_criteria fam_name_crit;
    basic_sort_criteria DoB_crit;
    basic_sort_criteria DoB_year_crit;
    basic_sort_criteria DoB_month_crit;
    basic_sort_criteria DoB_day_crit;
public:
    group1_sorting_criteria(){sort_fam_first=true; sort_DoB_first = false; sort_first_name_first = false; sort_fam_second = false; sort_DoB_second = true; sort_first_name_second = false; equlOpt=all_equal; }

    void setSortFNameFirst(bool val){sort_first_name_first=val;}
	void setSortFamFirst(bool val){sort_fam_first=val;}	
    void setSortDoBFirst(bool val){sort_DoB_first=val;}

    void setSortFNameSecond(bool val){sort_first_name_second=val;}
	void setSortFamSecond(bool val){sort_fam_second=val;}	
    void setSortDoBSecond(bool val){sort_DoB_second=val;}

    bool getSortFNameFirst() const {return sort_first_name_first;}
	bool getSortFamFirst() const {return sort_fam_first;}	
    bool getSortDoBFirst() const {return sort_DoB_first;}

    bool getSortFNameSecond() const {return sort_first_name_second;}
	bool getSortFamSecond() const {return sort_fam_second;}	
    bool getSortDoBSecond() const { return sort_DoB_second;}

	void setEqualityOption(compsiteEqualityOptions val)
	{
		if(inf_val<val && val<sup_val)
			equlOpt=val;
	}	
    compsiteEqualityOptions getEqualityOption() const {return equlOpt;}	
    virtual void setAscending(bool value ){first_name_crit.setAscending(value);	fam_name_crit.setAscending(value); DoB_year_crit.setAscending(value); DoB_month_crit.setAscending(value); DoB_day_crit.setAscending(value);}
    virtual void setOptionFromKeyboard()
    {
        cout << "Enter sort option for compsite_item: " << endl;
		cout << " Enter Sort option for Date of Birth year  : "; DoB_year_crit.setOptionFromKeyboard();
        cout << " Enter Sort option for Date of Birth month : "; DoB_year_crit.setOptionFromKeyboard();
        cout << " Enter Sort option for Date of Birth day   : "; DoB_year_crit.setOptionFromKeyboard();
		cout << " Enter Sort option for First Name          : "; first_name_crit.setOptionFromKeyboard();
        cout << " Enter Sort option for Family Name         : "; fam_name_crit.setOptionFromKeyboard();

        char sortopt;
		cout << " Choose option to compare multiple fields when sorting two items or a single field:" << endl;
		cout << " Type Y and press ENTER: ";
        cin >> sortopt;
		if((sortopt == 'y') || (sortopt == 'Y')){
            cout << "Select which field to sort first: " << endl;
            cout << "Type F for first name: " << endl;
            cout << "Type L for last name: " << endl;
            cout << "Type D for date of birth: " << endl;
            cin >> sortopt;
            switch(sortopt){
                case 'F':
                case 'f':
                    setSortFNameFirst(true);
                    setSortFamFirst(false);
                    setSortDoBFirst(false);

                    setSortFNameSecond(false);
                    break;
                case 'L':
                case 'l': 
                    setSortFNameFirst(false);
                    setSortFamFirst(true);
                    setSortDoBFirst(false);

                    setSortFamSecond(false);
                    break;
                case 'D':
                case 'd':
                    setSortFNameFirst(false);
                    setSortFamFirst(false);
                    setSortDoBFirst(true);

                    setSortDoBSecond(false);
                    break;
            }

            cout << "Select which field to sort second: " << endl;
            cout << "Type F for first name: " << endl;
            cout << "Type L for last name: " << endl;
            cout << "Type D for date of birth: " << endl;
            cin >> sortopt;
            switch(sortopt){
                case 'F':
                case 'f':
                    //Check if first name isnt the first criteria
                    if(!getSortFNameFirst()){
                        setSortFNameSecond(true);
                        setSortFamSecond(false);
                        setSortDoBSecond(false);
                        break;
                    }
                    else{
                        cout << "Error: First name is first criteria." << endl;
                        break;
                    }
                case 'L':
                case 'l':
                    //Check if last name isnt the first criteria
                    if(!getSortFamFirst()){
                        setSortFNameSecond(false);
                        setSortFamSecond(true);
                        setSortDoBSecond(false);
                        break;
                    }
                    else{
                        cout << "Error: Last name is first criteria." << endl;
                        break;
                    }
                case 'D':
                case 'd':
                    //Check if date of birth isnt the first criteria
                    if(!getSortDoBFirst()){
                        setSortFNameSecond(false);
                        setSortFamSecond(false);
                        setSortDoBSecond(true);
                        break;
                    }
                    else{
                        cout << "Error: Date of birth is first criteria." << endl;
                        break;
                    }
            }
        }
		else{
            cout << "Select which field to sort: " << endl;
            cout << "Type F for first name: " << endl;
            cout << "Type L for last name: " << endl;
            cout << "Type D for date of birth: " << endl;
            cin >> sortopt;
            switch(sortopt){
                case 'F':
                case 'f':
                    setSortFNameFirst(true);
                    setSortFamFirst(false);
                    setSortDoBFirst(false);

                    setSortFNameSecond(false);
                    setSortFamSecond(false);
                    setSortDoBSecond(false);
                    break;
                case 'L':
                case 'l': 
                    setSortFNameFirst(false);
                    setSortFamFirst(true);
                    setSortDoBFirst(false);

                    setSortFNameSecond(false);
                    setSortFamSecond(false);
                    setSortDoBSecond(false);
                    break;
                case 'D':
                case 'd':
                    setSortFNameFirst(false);
                    setSortFamFirst(false);
                    setSortDoBFirst(true);

                    setSortFNameSecond(false);
                    setSortFamSecond(false);
                    setSortDoBSecond(false);
            }
        }
			
		cout << endl;
		cout << " Choose option to estabilish strict equality:" << endl;
        cout << "  Type F to base decision on first name only; " << endl;
		cout << "  Type L to base decision on last name only;" << endl;
		cout << "  Type D to base decision on date of birth only;" << endl;
		cout << "  Type B to base decision on all three. Then press ENTER: " ;
		cin >> sortopt;
		cout << endl;
		switch (sortopt) {
        case 'L':
        case 'l':
            setEqualityOption(last_name);
            break;
		case 'D':
		case 'd':
			setEqualityOption(DoB);
			break;
		case 'F':
		case 'f':
			setEqualityOption(first_name);
			break;
		case 'B':
		case 'b':
			setEqualityOption(all_equal);
			break;
		default:
			setEqualityOption(all_equal);
		}	
    }
	virtual void printOptionToScreen() const
	{
		cout << "Sorting option for compsite_item: " << endl;
        cout << "First name: "; first_name_crit.printOptionToScreen(); cout << endl;
		cout << " Family name: "; fam_name_crit.printOptionToScreen(); cout << endl; 
		cout << " DoB: "; DoB_year_crit.printOptionToScreen(); cout << endl; 	
		cout << " When sorting two composite items: ";	
		if(sort_fam_first)
			cout << "Compare family name first (and then DoB)" << endl;	
		else
			cout << "Compare DoB first (and then family name)" << endl;	
		
		cout << " When estabilishing strict equality between two composite items: ";	
		switch (getEqualityOption()) {
        case first_name:
            cout << "base decision on first name only." << endl;
            break;
		case last_name:
			cout << "base decision on last name only." << endl;	
			break;
		case DoB:
			cout << "base decision on date of birth only." << endl;	
			break;
		case all_equal:
			cout << "base decision on both family name and date of birth." << endl;	
			break;
		default:
			cout << "ERROR: Option not set." << endl;	
		}		
	}
};

class group1_item : public basic_item{
    protected: 
        string_item first_Name;
        string_item last_Name;
        year_of_enrolment yearOfEnrolement;
        dates_composite_Item DateOfBirth;           // added the DoB , * enter from keyboard not Yet added
    public:
        group1_item(){
            string the_name = "Group1_item - comprising: ";
		    the_name += first_Name.getName();
		    the_name += "; ";
		    the_name += last_Name.getName();
		    the_name += "; ";
            the_name += yearOfEnrolement.getName();
            the_name += "; ";
            the_name += DateOfBirth.getName();
            the_name += ".";
            
		    itemTypeName = the_name;
        }

        ~group1_item(){;}

        //These functions below let us get the pointer to the 
        //Different items used in group 1, the pointer lets us
        //Access but not modify the items values.
        const string_item* getPointer2_FName() const{
            const string_item* the_ptr = &first_Name;
		    return the_ptr;
        }
        const string_item* getPointer2_LName() const{
            const string_item* the_ptr = &last_Name;
		    return the_ptr;
        }
        const year_of_enrolment* getPointer2_YoE() const{
            const year_of_enrolment* the_ptr = &yearOfEnrolement;
            return the_ptr;
        }

        const dates_composite_Item* getPointer2_DoB() const{
            const dates_composite_Item* the_ptr = &DateOfBirth;
            return the_ptr;
        }

        virtual void printItemOnScreen() const{
            if(isEmpty()){
                cout << "Item is empty." << endl;
            }
            else{
                cout << "First Name: " << first_Name.returnString() << endl;
                cout << "Last Name: " << last_Name.returnString() << endl;
                cout << "Year of enrolement: " << yearOfEnrolement.getItemVal() << endl;
                cout << "Date of Birth:  " << DateOfBirth.getDayVal() << " - " << DateOfBirth.getMonthVal() << " - " << DateOfBirth.getYearVal() << endl;
            }
        }

        virtual void enterItemFromKeyboard(){
            if(isLocked()){
                cout << "Error in enterItemFromKeyboard: Item is locked" << endl;
            }
            else{
                cout << "Enter first name: " << endl;
                first_Name.enterItemFromKeyboard();
                cout << endl;
                cout << "Enter last name: " << endl;
                last_Name.enterItemFromKeyboard();
                cout << endl;
                cout << "Enter year of enrolement: " << endl;
                yearOfEnrolement.enterItemFromKeyboard();
                cout <<"Enter Date of Birth: " << endl;
                DateOfBirth.enterItemFromKeyboard(yearOfEnrolement.getItemVal());    // Takes year in 1915-2025, Month as val 1-12, and Day as val 1-(28,29,30, or 31) depending on month and year. Rejects non-int entries 
                empty = false;
            }
        }

        virtual void generateRandomItem()
	    {
		    if (isLocked()){
                cout << "Error in generateRandomItem: Item is locked" << endl;
            }
		    else
		    {
		    	first_Name.generateRandomItem();
			    last_Name.generateRandomItem();
                yearOfEnrolement.generateRandomItem();
                DateOfBirth.generateRandomItem(yearOfEnrolement.getItemVal());
			    empty = false;
		    }
	    }

        //Have not finished yet
        virtual bool compatibilityCheck(const basic_item* other_item) const{
            //True if the same, false if not
            bool result = false;

            //Check to see if the other item is allocated, if not skip
            if(other_item != NULL){
                //Type casting the other item to confirm its the same as the string
                const group1_item* typecast_OtherItem = typecastItem(other_item, this);

                if(typecast_OtherItem != NULL){result = true;}
                else{
                    cout << "Check failed for Item type: " << itemTypeName << endl;
                }
            }

            return result;
        }
	    virtual bool IsLargerThan(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const{
            bool result_FName_larger, result_FName_equal, result_LName_larger, result_DoB_larger, result_LName_equal, result_DoB_equal;
            group1_sorting_criteria group1_crit;

            if(other_item == NULL){return false;}

            const group1_item* typecast_other_item = typecastItem(other_item, this);

            if(typecast_other_item == NULL){
                cout << "Error: Other item is not of the same type." << endl;
                return false;
            }

            if(this->isEmpty() || (typecast_other_item->isEmpty())){
                cout << "Error: Either or both items are empty" << endl;
                return false;
            }

            //Now checking if all components of the other item is larger than the current
            if(sort_criteria != NULL){
                const group1_sorting_criteria* typecasted_sort = typecastItem(sort_criteria, &group1_crit);
                if(typecasted_sort != NULL){
                    //Copying the criteria for each component into a local copy group1_crit
                    group1_crit.first_name_crit.setAscending(typecasted_sort->first_name_crit.getAscending());
                    group1_crit.fam_name_crit.setAscending(typecasted_sort->fam_name_crit.getAscending());
                    group1_crit.DoB_crit.setAscending(typecasted_sort->DoB_year_crit.getAscending());

                    group1_crit.setSortFamFirst(typecasted_sort->getSortFamFirst());
                    group1_crit.setSortDoBFirst(typecasted_sort->getSortDoBFirst());
                    group1_crit.setSortFNameFirst(typecasted_sort->getSortFNameFirst());

                    group1_crit.setSortFamSecond(typecasted_sort->getSortFamSecond());
                    group1_crit.setSortDoBSecond(typecasted_sort->getSortDoBSecond());
                    group1_crit.setSortFNameSecond(typecasted_sort->getSortFNameSecond());
                }
            }

            //Comparing the family name first
            //Step1: Extracting the pointer from other
            const string_item* the_other_LName_ptr = typecast_other_item->getPointer2_LName();
            //Step2: Check if it is larger than the string part of the criteria
            result_LName_larger = last_Name.IsLargerThan(the_other_LName_ptr, &(group1_crit.fam_name_crit));
            //Step3: Check if it is equal to the string part of the criteria
            result_LName_equal = last_Name.IsEqualTo(the_other_LName_ptr, &(group1_crit.fam_name_crit));

            //Step1: Extracting the pointer from other
            const dates_composite_Item* the_other_DoB_ptr = typecast_other_item->getPointer2_DoB();
            //Step2: Check if it is larger than the DoB part of the criteria
            result_DoB_larger = DateOfBirth.IsLargerThan(the_other_DoB_ptr, &(group1_crit.DoB_crit));
            //Step3: Check if it is equal to the DOB of the criteria
            result_DoB_equal = DateOfBirth.IsEqualTo(the_other_DoB_ptr);

            //Step1: Extracting the pointer from other
            const string_item* the_other_FName_ptr = typecast_other_item->getPointer2_FName();
            //Step2: Check if it is larger than the First name part of the criteria
            result_FName_larger = first_Name.IsLargerThan(the_other_FName_ptr, &(group1_crit.first_name_crit));
            //Step3: Check if it is equal to the First name of the criteria
            result_FName_equal = first_Name.IsEqualTo(the_other_FName_ptr, &(group1_crit.first_name_crit));
            
            if(group1_crit.getSortFamFirst()){
                //Family name first
                if(result_LName_larger){
                    return true;
                } 
                //If last names are equal let the other fields decide
                if(result_LName_equal){
                    if(group1_crit.getSortFNameSecond()){
                        //Let the first name decide first
                        if(result_FName_larger){
                            return true;
                        }
                        else if(result_FName_equal){
                            //If the first names are equal let the date of birth decide
                            return result_DoB_larger;
                        }
                    }
                    if(group1_crit.getSortDoBSecond()){
                        //Let the date of birth decide first
                        if(result_DoB_larger){
                            return true;
                        }
                        else if(result_DoB_equal){
                            //If the date of births are equal let the first name decide
                            return result_FName_larger;
                        }
                    }
                }
                //The last name component is smaller
                return false;
            }

            if(group1_crit.getSortDoBFirst()){
                //The DoB component is larger
                if(result_DoB_larger){
                    return true;
                } 
                //If DoB are equal let the other fields decide
                if(result_DoB_equal){
                    if(group1_crit.getSortFamSecond())
                    //Let the last name decide first
                    if(result_LName_larger){
                        return true;
                    }
                    else if(result_LName_equal){
                        //If the last names are equal let the first name decide
                        return result_FName_larger;
                    }
                    if(group1_crit.getSortFNameSecond()){
                        //Let the first name decide first
                        if(result_FName_larger){
                            return true;
                        }
                        else if(result_FName_equal){
                            //If the first names are equal let the last name decide
                            return result_LName_larger;
                        }
                    }
                }
                //The date of birth component is smaller
                return false;
            }

            if(group1_crit.getSortFNameFirst()){
                //The first name component is larger
                if(result_FName_larger){
                    return true;
                } 
                //If First names are equal let the other fields decide
                if(result_FName_equal){
                    if(group1_crit.getSortFamSecond()){
                        //Let the last name decide first
                        if(result_LName_larger){
                            return true;
                        }
                        else if(result_LName_equal){
                            //If the last names are equal let the date of birth decide
                            return result_DoB_larger;
                        }
                    }
                    if(group1_crit.getSortDoBSecond()){
                        //Let the Last name decide first
                        if(result_DoB_larger){
                            return true;
                        }
                        else if(result_DoB_equal){
                            //If the date of births are equal let the last name decide
                            return result_LName_larger;
                        }
                    }
                }
                //The last name component is smaller
                return false;
            }
            //The components are smaller 
            return false;
        }	

	    virtual bool IsEqualTo(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const{
            bool result_FName_equal, result_LName_equal, result_DoB_equal;
            group1_sorting_criteria group1_crit;

            if(other_item == NULL){return false;}

            const group1_item* typecast_other_item = typecastItem(other_item, this);

            if(typecast_other_item == NULL){
                cout << "Error: Other item is not of the same type." << endl;
                return false;
            }

            if(this->isEmpty() || (typecast_other_item->isEmpty())){
                cout << "Error: Either or both items are empty" << endl;
                return false;
            }

            //Now checking if all components of the other item is larger than the current
            if(sort_criteria != NULL){
                const group1_sorting_criteria* typecasted_sort = typecastItem(sort_criteria, &group1_crit);
                if(typecasted_sort != NULL){
                    //Copying the criteria for each component into a local copy group1_crit
                    group1_crit.fam_name_crit.setAscending(typecasted_sort->fam_name_crit.getAscending());
                    group1_crit.DoB_crit.setAscending(typecasted_sort->DoB_year_crit.getAscending());
                    group1_crit.first_name_crit.setAscending(typecasted_sort->first_name_crit.getAscending());

                    group1_crit.setSortFNameFirst(typecasted_sort->getSortFNameFirst());
                    group1_crit.setSortFamFirst(typecasted_sort->getSortFamFirst());
                    group1_crit.setSortDoBFirst(typecasted_sort->getSortDoBFirst());

                    group1_crit.setEqualityOption(typecasted_sort->getEqualityOption());
                }
            }

            //Comparing the family name first
            //Step1: Extracting the pointer from other
            const string_item* the_other_LName_ptr = typecast_other_item->getPointer2_LName();
            //Step2: Check if it is equal to the string part of the criteria
            result_LName_equal = last_Name.IsEqualTo(the_other_LName_ptr, &(group1_crit.fam_name_crit));

            //Step1: Extracting the pointer from other
            const string_item* the_other_FName_ptr = typecast_other_item->getPointer2_FName();
            //Step2: Check if it is equal to the string part of the criteria
            result_FName_equal = first_Name.IsEqualTo(the_other_FName_ptr, &(group1_crit.first_name_crit));

            //Step1: Extracting the pointer from other
            const dates_composite_Item* the_other_DoB_ptr = typecast_other_item->getPointer2_DoB();
            //Step2: Check if it is larger than the DoB part of the criteria
            result_DoB_equal = DateOfBirth.IsEqualTo(the_other_DoB_ptr);

            switch(group1_crit.getEqualityOption()){
                case group1_sorting_criteria::first_name:
                    return result_FName_equal;
                    break;
                case group1_sorting_criteria::last_name:
                    return result_LName_equal;
                    break;
                case group1_sorting_criteria::DoB:
                    return result_DoB_equal;
                    break;
                case group1_sorting_criteria::all_equal:
                    return (result_LName_equal&&result_DoB_equal&&result_FName_equal);
                    break;
                default:
                    cout << "Error: Options not set." << endl;
                    return false;
            }
        }
};

int year_of_enrolment::min_year = 2010;
int year_of_enrolment::max_year = 2040;

#endif