#ifndef Release2_h
#define Release2_h

#include "arrayItem_v3.h"
#include "generalArraywithTemplate_v2.h"

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

        //Small function to clear the string item
        void clearString(){
            item_value.clear();
            stringSet = false;
            empty = true;
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
    enum compsiteEqualityOptions{inf_val=0, family_name, DoB, both_equal, sup_val};
protected:
	bool sort_fam_first;	
	compsiteEqualityOptions equlOpt;
public:
    basic_sort_criteria fam_name_crit;
    basic_sort_criteria DoB_year_crit;
    basic_sort_criteria DoB_month_crit;
    basic_sort_criteria DoB_day_crit;
public:
    group1_sorting_criteria(){sort_fam_first=true; equlOpt=both_equal;}
	void setSortFamFirst(bool val){sort_fam_first=val;}	
	bool getSortFamFirst() const {return sort_fam_first;}	
	void setEqualityOption(compsiteEqualityOptions val)
	{
		if(inf_val<val && val<sup_val)
			equlOpt=val;
	}	
    compsiteEqualityOptions getEqualityOption() const {return equlOpt;}	
    virtual void setAscending(bool value ){	fam_name_crit.setAscending(value); DoB_year_crit.setAscending(value); DoB_month_crit.setAscending(value); DoB_day_crit.setAscending(value);}
    virtual void setOptionFromKeyboard()
    {
        cout << "Enter sort option for compsite_item: " << endl;
		cout << " Enter Sort option for Date of Birth year  : "; DoB_year_crit.setOptionFromKeyboard();
        cout << " Enter Sort option for Date of Birth month : "; DoB_year_crit.setOptionFromKeyboard();
        cout << " Enter Sort option for Date of Birth day   : "; DoB_year_crit.setOptionFromKeyboard();
		cout << " Enter Sort option for Family Name         : "; fam_name_crit.setOptionFromKeyboard();

        char sortopt;
		cout << " Choose option to compare Date of Birth first (and then Family name) when sorting two items:" << endl;
		cout << " Type Y and press ENTER (otherwise Family name is compared first): ";
        cin >> sortopt;
		if( (sortopt=='y') || (sortopt == 'Y') )
			setSortFamFirst(true);
		else
			setSortFamFirst(false);
		cout << endl;
		cout << " Choose option to estabilish strict equality:" << endl;
		cout << "  Type F to base decision on family name only;" << endl;
		cout << "  Type D to base decision on date of birth only;" << endl;
		cout << "  Type B to base decision on both. Then press ENTER: " ;
		cin >> sortopt;
		cout << endl;
		switch (sortopt) {
		case 'D':
		case 'd':
			setEqualityOption(DoB);
			break;
		case 'F':
		case 'f':
			setEqualityOption(family_name);
			break;
		case 'B':
		case 'b':
			setEqualityOption(both_equal);
			break;
		default:
			setEqualityOption(both_equal);
		}	
    }
	virtual void printOptionToScreen() const
	{
		cout << "Sorting option for compsite_item: " << endl;
		cout << " Family name: "; fam_name_crit.printOptionToScreen(); cout << endl; 
		cout << " DoB: "; DoB_year_crit.printOptionToScreen(); cout << endl; 	
		cout << " When sorting two composite items: ";	
		if(sort_fam_first)
			cout << "Compare family name first (and then DoB)" << endl;	
		else
			cout << "Compare DoB first (and then family name)" << endl;	
		
		cout << " When estabilishing strict equality between two composite items: ";	
		switch (getEqualityOption()) {
		case family_name:
			cout << "base decision on family name only." << endl;	
			break;
		case DoB:
			cout << "base decision on date of birth only." << endl;	
			break;
		case both_equal:
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
        //Add the other items when you can
    public:
        group1_item(){
            string the_name = "Group1_item - comprising: ";
		    the_name += first_Name.getName();
		    the_name += "; ";
		    the_name += last_Name.getName();
		    the_name += "; ";
            the_name += yearOfEnrolement.getName();
            the_name += ".";
            //Add other fields when you can
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
        
        virtual void printItemOnScreen() const{
            if(isEmpty()){
                cout << "Item is empty." << endl;
            }
            else{
                cout << "First Name: " << first_Name.returnString() << endl;
                cout << "Last Name: " << last_Name.returnString() << endl;
                cout << "Year of enrolement: " << yearOfEnrolement.getItemVal() << endl;
                //Add the other data when you can
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
                //Add other fields when you can
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
			    //Add other fields when you can
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
            bool result_LName_larger, result_DoB_larger, result_LName_equal, result_DoB_equal;
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
                    group1_crit.DoB_year_crit.setAscending(typecasted_sort->fam_name_crit.getAscending());
                    group1_crit.DoB_month_crit.setAscending(typecasted_sort->fam_name_crit.getAscending());
                    group1_crit.DoB_day_crit.setAscending(typecasted_sort->fam_name_crit.getAscending());

                    group1_crit.setSortFamFirst(typecasted_sort->getSortFamFirst());
                }
            }

            //Comparing the family name first
            //Step1: Extracting the pointer from other
            const string_item* the_other_LName_ptr = typecast_other_item->getPointer2_LName();
            //Step2: Check if it is larger than the string part of the criteria
            result_LName_larger = last_Name.IsLargerThan(the_other_LName_ptr, &(group1_crit.fam_name_crit));
            //Step3: Check if it is equal to the string part of the criteria
            result_LName_equal = last_Name.IsEqualTo(the_other_LName_ptr, &(group1_crit.fam_name_crit));

            //Will do the same as above when DoB is finished

            
            if(group1_crit.getSortFamFirst()){
                //The last name component is larger
                if(result_LName_larger){
                    return true;
                } 
                //If last names are equal let the DoB decide
                if(result_LName_equal){
                    return result_DoB_larger;
                }
                //The DoB component is smaller
                return false;
            }
            //The DoB is sorted first
            if(result_DoB_larger){
                return true; //DoB is larger
            }
            if(result_DoB_equal){
                return result_LName_larger; //DoB are equal so let last name decide
            }
            //The DoB is smaller 
            return false;
        }	

	    virtual bool IsEqualTo(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const{
            bool result_LName_equal, result_DoB_equal;
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
                    group1_crit.DoB_year_crit.setAscending(typecasted_sort->fam_name_crit.getAscending());
                    group1_crit.DoB_month_crit.setAscending(typecasted_sort->fam_name_crit.getAscending());
                    group1_crit.DoB_day_crit.setAscending(typecasted_sort->fam_name_crit.getAscending());

                    group1_crit.setSortFamFirst(typecasted_sort->getSortFamFirst());
                    group1_crit.setEqualityOption(typecasted_sort->getEqualityOption());
                }
            }

            //Comparing the family name first
            //Step1: Extracting the pointer from other
            const string_item* the_other_LName_ptr = typecast_other_item->getPointer2_LName();
            //Step2: Check if it is equal to the string part of the criteria
            result_LName_equal = last_Name.IsEqualTo(the_other_LName_ptr, &(group1_crit.fam_name_crit));


            //Will compare the DoB when it is done.

            switch(group1_crit.getEqualityOption()){
                case group1_sorting_criteria::family_name:
                    return result_LName_equal;
                    break;
                case group1_sorting_criteria::DoB:
                    return result_DoB_equal;
                    break;
                case group1_sorting_criteria::both_equal:
                    return (result_LName_equal&&result_DoB_equal);
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