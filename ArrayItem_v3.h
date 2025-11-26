#ifndef __ARRAYITEM_V3_H_
#define __ARRAYITEM_V3_H_

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <string>

#include <iostream>
using namespace std;


////// this is needed to check compatibility between items (and to use a derived-class pointer that is passed as "base class")
template <class Base, class Derived> const Derived* typecastItem(const Base* basic_ptr, const Derived* derivedItem_ptr)
{
	const Derived* typecasted_ptr = dynamic_cast <const Derived*>(basic_ptr);

	if (typecasted_ptr == NULL)
		printf("\n Error typecasting item: type does not match the expected derived item\n");

	return typecasted_ptr;
}
//////


class basic_sort_criteria{
protected:
	bool ascending;	//	
public:
	basic_sort_criteria(){setAscending(true);}
	virtual void setAscending(bool value){ascending=value;}
	bool getAscending() const {return ascending;}
	virtual void setOptionFromKeyboard()
	{
		char sortascending;
		cout << "Sort option is ASCENDING? Type Y and press ENTER: ";
		cin >> sortascending;
		if( (sortascending=='y') || (sortascending == 'Y') )
			setAscending(true);
		else
			setAscending(false);
		cout << endl;	
	}
	virtual void printOptionToScreen() const
	{
		cout << "Sort option is ";
		if(getAscending())
			cout << "ASCENDING" << endl;
		else
			cout << "DISCENDING" << endl;		
	}
};


class basic_item{
protected:
	bool empty;
	string itemTypeName;	
	bool locked;
	
	// Used later on
	// FV note: acceess to this may need to be regulated via Attonrey-Client paradigm: 
	// https://en.wikibooks.org/wiki/More_C++_Idioms/Friendship_and_the_Attorney-Client
	int includedBy;
	void incrementincludedBy() { includedBy++; }
	void decrementincludedBy() { includedBy=( (includedBy>0) ? (includedBy-1) : 0 ); }
	// end test
public:
	basic_item() { empty = true; locked = false;  includedBy = 1; }
	~basic_item() { ; }
	bool isEmpty() const {return empty;}
	bool isLocked() const { return locked; }
	virtual void setLocked(bool lock_input)
	{
		if(!isEmpty())
			locked = lock_input;
	}
	int isIncludedBy() const {return includedBy;}
	void printItemTypeName() const { cout << endl << "Item type: " << itemTypeName << endl; }
	string getName() const {return itemTypeName;}
	//These must be implemented by any derived item	
	virtual void printItemOnScreen() const =0;
	virtual void enterItemFromKeyboard()=0;
	virtual void generateRandomItem()=0;	
	virtual bool compatibilityCheck(const basic_item* other_item) const = 0;
	virtual bool IsLargerThan(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const =0;	
	virtual bool IsEqualTo(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const =0;	
	
	//*
	bool IsLargerOrEqualThan(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL)
	{
		bool is_larger = IsLargerThan(other_item, sort_criteria);
		bool is_equal = IsEqualTo(other_item, sort_criteria);
		return (is_larger || is_equal);
	}
	bool IsSmallerThan(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL)
	{
		return !( IsLargerOrEqualThan(other_item, sort_criteria) );
	}
	bool IsSmallerOrEqualThan(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL)
	{
		return !( IsLargerThan(other_item, sort_criteria) );
	}
	
	//*/
	//virtual void loadItemFromFile(FILE* fin)=0;
	//virtual basic_item* makeCopyofItem()=0;	
};

//
class integer_item: public basic_item{
protected:
	int item_value;	
public:
	integer_item(){itemTypeName = "integer_item";}
	//~integer_item() { cout << "integer_item destructor called" << endl; } // use for inital test; remove the printout after.
	~integer_item() { ; } // without printout

	int getItemVal() const 
	{
		if(isEmpty())
			cout << "Warning: getItemVal() called on an empty object" << endl; 
		return item_value;
	}
	
	virtual void printItemOnScreen() const
	{
		if(isEmpty())
			cout << "Item is empty." << endl;
		else
			cout << "Item value is " << item_value << " . " << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		if(isLocked())
			cout << "Error in enterItemFromKeyboard: Item is locked" << endl;
		else
		{
			cout << "Insert integer element then hit enter." << endl;
			cin >> item_value;
			cout << endl;

			// item filled
			empty = false;
		}		
	}

	virtual void generateRandomItem()
	{
		if (isLocked())
			cout << "Error in generateRandomItem: Item is locked" << endl;
		else
		{
			int item;
			int max_rand_val = 1000;

			item = rand();
			item = item % (max_rand_val + 1);

			// turn to negative 30% of the time
			if ((rand() % 10) >= 7)
				item = (-1)*item;

			item_value = item;
			// item filled
			empty = false;
		}
	}
	
	void generateRandomItemWithinLimits(int min_val, int max_val)
	{
		if (isLocked())
			cout << "Error in generateRandomItem: Item is locked" << endl;
		else
		{
			int item;

			if (min_val > max_val)
			{
				int temp = min_val;
				min_val = max_val;
				max_val = temp;
			}

			int max_rand_val = max_val - min_val;

			item = rand();
			item = item % (max_rand_val);
			item = item + min_val;
			item_value = item;
			// item filled
			empty = false;
		}
	}

	virtual bool compatibilityCheck(const basic_item* other_item) const
	{
		bool result = false;

		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item != NULL)
		{
			// typecast the other item to confirm it is the same as this;
			const integer_item* typecasted_other_item = typecastItem(other_item, this);
			if (typecasted_other_item != NULL)
				result = true;
			else
			{
				cout << endl << "Check failed for Item type: ";
				cout << itemTypeName << endl;
			}
		}
		return result;
	}
	
	virtual bool IsLargerThan(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const
	{
		bool result=false;
		
		// if the other item is "empty" (non allocated) don't do any comparison
		if(other_item==NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		const integer_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type integer_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// if eitehr is not initialized, return false
		if( this->isEmpty() || (typecasted_other_item->isEmpty()) )
		{
			cout << "Either or both items are empty." << endl;
			return false;
		}
		
		// now verify if the other item is larger than the curren
		if( getItemVal() > (typecasted_other_item->getItemVal()) )
			result=true;


		// chek if there are sorting options to apply 
		if(sort_criteria!=NULL)
		{
			// if sorting is in descending order the result is reversed 
			if( !( sort_criteria->getAscending() ) )
				result=!result;
		}

		return result;
	}	
	
	virtual bool IsEqualTo(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const
	{
		bool result=false;
		
		// if the other item is "empty" (non allocated) don't do any comparison
		if(other_item==NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		const integer_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type integer_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// if eitehr is not initialized, return false
		if( this->isEmpty() || (typecasted_other_item->isEmpty()) )
		{
			cout << "Either or both items are empty." << endl;
			return false;
		}
		
		// now verify if the other item is equal to the curren
		if( getItemVal() == (typecasted_other_item->getItemVal()) )
			result=true;		

		return result;
	}
	
};



class intmat_sort_criteria : public basic_sort_criteria{
public:
	enum matsortoptions{inf_val=0, sort_maxval, sort_determ, sup_val};
private:
	matsortoptions thesortoption;
public:	
	intmat_sort_criteria() {setOption(sort_maxval);}
	void setOption(matsortoptions value)
	{ 
		if( (value>inf_val) && (value < sup_val) )
			thesortoption = value;
		else
			thesortoption = sort_maxval;
	}
	matsortoptions getOption() const { return thesortoption; }
	virtual void setOptionFromKeyboard()
	{
		char sortoption;
		cout << "Sort option: Type M for MAXVAL; Type D for DETERMINANT; then press ENTER: ";
		cin >> sortoption;
		switch (sortoption) {
		case 'M':
		case 'm':
			setOption(sort_maxval);
			break;
		case 'D':
		case 'd':
			setOption(sort_determ);
			break;
		}
		cout << endl;
		basic_sort_criteria::setOptionFromKeyboard();
	}
	virtual void printOptionToScreen() const
	{
		cout << "intmat Sorting by ";
		switch (getOption()) {
		case sort_maxval:
			cout << "MAXVAL " << endl;
			break;
		case sort_determ:
			cout << "DETERMINANT " << endl;
			break;
		}
		basic_sort_criteria::printOptionToScreen();
	}
};



class intmat_item: public basic_item{
protected:
	static const int matsize=2;
	int matrix[matsize][matsize];

	int getMatVal(int i, int j) const 
	{
		if( (i>=0 && i<matsize) && (j>=0 && j<matsize) && (!isEmpty()) )
		{
			return matrix[i][j];
		}
		else
			return 0;
	}

	void setMatVal(int i, int j, int val)
	{
		//if( (i>=0 && i<matsize) && (j>=0 && j<matsize) && (isEmpty()) )
		if( (i>=0 && i<matsize) && (j>=0 && j<matsize) )
		{
			matrix[i][j] = val;
		}
	}

public:
	intmat_item(){itemTypeName = "intmat_item";}
	//~intmat_item() { cout << "intmat_item destructor called" << endl; } // can remove the printout after testing
	~intmat_item() { ; } 
	
	//find and report the largest value in the matrix
	int getMaxVal() const 
	{
		int max=getMatVal(0, 0);
		for(int i=0; i<matsize; i++)
			for(int j=0; j<matsize; j++)
				if( max < getMatVal(i,j) )
					max=getMatVal(i,j);
		return max;
	}
	
	//compute and report matrix determinant
	int getDet() const
	{	
		if (matsize == 2)
		{
			int maindiag = getMatVal(0, 0) * getMatVal(1, 1);
			int secdiag = getMatVal(0, 1) * getMatVal(1, 0);
			return (maindiag * ((-1)*secdiag));
		}
		cout << endl << " Determinant not ready for general case " << endl;
		return 0;
	}

	virtual void printItemOnScreen() const 
	{
		if(isEmpty())
			cout << "Item is empty." << endl;
		else
		{
			for(int i=0; i<matsize; i++)
				for(int j=0; j<matsize; j++)
					cout << "Item pos "<< i << " , " << j << " value is " << getMatVal(i,j) << " . " << endl;
			cout << endl;
		}
	}

	virtual void enterItemFromKeyboard()
	{
		if (isLocked())
			cout << "Error in enterItemFromKeyboard: Item is locked" << endl;
		else
		{
			int val;
			for (int i = 0; i < matsize; i++)
				for (int j = 0; j < matsize; j++)
				{
					cout << "Enter integer value for";
					cout << "Item pos " << i << " , " << j << " :" << endl;
					cin >> val;
					setMatVal(i, j, val);
				}
			cout << "Matrix filled" << endl;
			// item filled
			empty = false;
		}
	}

	virtual void generateRandomItem()
	{
		if (isLocked())
			cout << "Error in generateRandomItem: Item is locked" << endl;
		else
		{
			int item;
			int max_rand_val = 100;

			for (int i = 0; i < matsize; i++)
				for (int j = 0; j < matsize; j++)
				{

					item = rand();
					item = item % (max_rand_val + 1);

					// turn to negative 30% of the time
					if ((rand() % 10) >= 7)
						item = (-1)*item;

					setMatVal(i, j, item);
				}
			// item filled
			empty = false;
		}
	}
	
	//virtual void loadItemFromFile(FILE* fin);
	
	virtual bool IsLargerThan(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const
	{
		bool result=false;
		intmat_sort_criteria matSortOption;
		
		// if the other item is "empty" (non allocated) don't do any comparison
		if(other_item==NULL)
			return false;

		
		// first typecast the other item to confimr it is the same as this;
		const intmat_item* typecasted_other_item = typecastItem(other_item, this);
		
		// check that it worked
		if(typecasted_other_item==NULL)
		{
			cout << "Other item is not of type intmat2x2_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// check if the sort_option is specific for the int_mat
		if (sort_criteria != NULL)
		{
			// first typecast the other item to confirm it is the same as this;
			const intmat_sort_criteria* typecasted_sortoption = typecastItem(sort_criteria, &matSortOption);
			if (typecasted_sortoption != NULL)
				matSortOption.setOption(typecasted_sortoption->getOption());
		}

		// now verify if the other item is larger than the current
		switch (matSortOption.getOption()) {
		case(intmat_sort_criteria::sort_maxval):
			if (getMaxVal() > (typecasted_other_item->getMaxVal()))
				result = true;
			break;
		case(intmat_sort_criteria::sort_determ):
			if( getDet() > (typecasted_other_item->getDet()) )
				result = true;
			break;
		}
		
		// chek if ascending/decenting sorting applies 
		if(sort_criteria!=NULL)
		{
			// if sorting is in descending order the result is reversed 
			if( !( sort_criteria->getAscending() ) )
				result=!result;
		}

		return result;
	}

	virtual bool compatibilityCheck(const basic_item* other_item) const
	{
		bool result = false;

		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item != NULL)
		{
			// typecast the other item to confirm it is the same as this;
			const intmat_item* typecasted_other_item = typecastItem(other_item, this);
			if (typecasted_other_item != NULL)
				result = true;
			else
			{
				cout << endl << "Check failed for Item type: ";
				cout << itemTypeName << endl;
			}
		}
		return result;
	}
	
	virtual bool IsEqualTo(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const
	{
		bool result=false;
		intmat_sort_criteria matSortOption;
		
		// if the other item is "empty" (non allocated) don't do any comparison
		if(other_item==NULL)
			return false;

		
		// first typecast the other item to confimr it is the same as this;
		const intmat_item* typecasted_other_item = typecastItem(other_item, this);
		
		// check that it worked
		if(typecasted_other_item==NULL)
		{
			cout << "Other item is not of type intmat2x2_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// check if the sort_option is specific for the int_mat
		if (sort_criteria != NULL)
		{
			// first typecast the other item to confimr it is the same as this;
			const intmat_sort_criteria* typecasted_sortoption = typecastItem(sort_criteria, &matSortOption);
			if (typecasted_sortoption != NULL)
				matSortOption.setOption(typecasted_sortoption->getOption());
		}

		// now verify if the other item is larger than the curren
		switch (matSortOption.getOption()) {
		case(intmat_sort_criteria::sort_maxval):
			if (getMaxVal() == (typecasted_other_item->getMaxVal()))
				result = true;
			break;
		case(intmat_sort_criteria::sort_determ):
			if( getDet() == (typecasted_other_item->getDet()) )
				result = true;
			break;
		}
		
		return result;
	}

};

// this is used for the example composite item (further below) that comprises an int_item and an intmat_item
class compsite_item_sort_criteria : public basic_sort_criteria{
public:
	enum compsiteEqualityOptions{inf_val=0, int_equal, mat_equal, both_equal, sup_val};
protected:
	bool sort_int_first;	
	compsiteEqualityOptions equlOpt;
public:
	// assumng those two can be set independently of each other, I can make those public; may reconsider later 	
	basic_sort_criteria the_int_crit;
	intmat_sort_criteria the_mat_crit;
public:
	compsite_item_sort_criteria(){sort_int_first=true; equlOpt=both_equal;}
	void setSortIntFirst(bool val){sort_int_first=val;}	
	bool getSortIntFirst() const {return sort_int_first;}	
	void setEqualityOption(compsiteEqualityOptions val)
	{
		if(inf_val<val && val<sup_val)
			equlOpt=val;
	}	
	compsiteEqualityOptions getEqualityOption() const {return equlOpt;}	
	virtual void setAscending(bool value ){	the_int_crit.setAscending(value); the_mat_crit.setAscending(value);}
	virtual void setOptionFromKeyboard()
	{
		cout << "Enter sort option for compsite_item: " << endl;
		cout << " Enter Sort option for integer type: "; the_int_crit.setOptionFromKeyboard();
		cout << " Enter Sort option for int_mat type: "; the_mat_crit.setOptionFromKeyboard();
		
		char sortopt;
		cout << " Choose option to compare integer first (and then int_mat) when sorting two items:" << endl;
		cout << " Type Y and press ENTER (otherwise int_mat is compared first): ";
		cin >> sortopt;
		if( (sortopt=='y') || (sortopt == 'Y') )
			setSortIntFirst(true);
		else
			setSortIntFirst(false);
		cout << endl;
			
		cout << " Choose option to estabilish strict equality:" << endl;
		cout << "  Type I to base decision on integer only;" << endl;
		cout << "  Type M to base decision on matrix only;" << endl;
		cout << "  Type B to base decision on both. Then press ENTER: " ;
		cin >> sortopt;
		cout << endl;
		switch (sortopt) {
		case 'I':
		case 'i':
			setEqualityOption(int_equal);
			break;
		case 'M':
		case 'm':
			setEqualityOption(mat_equal);
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
		cout << " Integer type: "; the_int_crit.printOptionToScreen(); cout << endl; 
		cout << " Int_mat type: "; the_mat_crit.printOptionToScreen(); cout << endl; 	
		cout << " When sorting two composite items: ";	
		if(sort_int_first)
			cout << "Compare integer first (and then int_mat)" << endl;	
		else
			cout << "Compare int_mat first (and then integer)" << endl;	
		
		cout << " When estabilishing strict equality between two composite items: ";	
		switch (getEqualityOption()) {
		case int_equal:
			cout << "base decision on integer only." << endl;	
			break;
		case mat_equal:
			cout << "base decision on matrix only." << endl;	
			break;
		case both_equal:
			cout << "base decision on both integer and matrix." << endl;	
			break;
		default:
			cout << "ERROR: Option not set." << endl;	
		}		
	}
};


// this is an example composite item that comprises an int_item and an intmat_item
class compsite_item: public basic_item{
protected:
	// if you don't want those to be set independently of each other, make those protected 
	integer_item the_int;
	intmat_item the_mat;
public:		
	compsite_item()
	{
		string the_name = "compsite_item - comprising: ";
		the_name += the_int.getName();
		the_name += "; ";
		the_name += the_mat.getName();
		the_name += ".";
		itemTypeName = the_name;
	}
	// obtain a Const Pointer to the int component (using that pointer you can access but not modify)
	const integer_item* getCP2the_int() const 
	{ 
		const integer_item* the_ptr = &the_int;
		return the_ptr;
	}
	// obtain a Const Pointer to the int_mat component (using that pointer you can access but not modify)
	const intmat_item* getCP2the_mat() const 
	{ 
		const intmat_item* the_ptr = &the_mat;
		return the_ptr;
	}
	virtual void printItemOnScreen() const
	{
		if(isEmpty())
			cout << "Item is empty." << endl;
		else
		{
			cout << "Integer item is: ";
			the_int.printItemOnScreen();			
			cout << endl;
			cout << "Matrix item is: "<< endl;
			the_mat.printItemOnScreen();			
			cout << endl;
		}
	}
	virtual void enterItemFromKeyboard()
	{
		if (isLocked())
			cout << "Error in enterItemFromKeyboard: Item is locked" << endl;
		else
		{
			cout << "Integer item: ";
			the_int.enterItemFromKeyboard();			
			cout << endl;
			cout << "Matrix item: " << endl;
			the_mat.enterItemFromKeyboard();
			// item filled
			empty = false;
		}
	}
	virtual void generateRandomItem()
	{
		if (isLocked())
			cout << "Error in generateRandomItem: Item is locked" << endl;
		else
		{
			the_int.generateRandomItem();
			the_mat.generateRandomItem();
			// item filled
			empty = false;
		}
	}
	virtual bool IsLargerThan(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const
	{
		bool result_int_larger, result_int_equal, result_mat_larger, result_mat_equal;
		compsite_item_sort_criteria comp_crit;
				
		// if the other item is "empty" (non allocated) don't do any comparison
		if(other_item==NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		const compsite_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type integer_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// if eitehr is not initialized, return false
		if( this->isEmpty() || (typecasted_other_item->isEmpty()) )
		{
			cout << "Either or both items are empty." << endl;
			return false;
		}
		
		// now verify if each component of the other item is larger than the current
		
		
		// preliminary step:
		// first check the input cirteria is of the correct type
		if (sort_criteria != NULL)
		{
			// first typecast the other item to confimr it is the correct type;
			const compsite_item_sort_criteria* typecasted_sortoption = typecastItem(sort_criteria, &comp_crit);
			if (typecasted_sortoption != NULL)
			{
				// copy the criteria (for each component) into (the local copy) comp_crit (otherwise filled with default values); 
				comp_crit.the_int_crit.setAscending(typecasted_sortoption->the_int_crit.getAscending());
				comp_crit.the_mat_crit.setOption(typecasted_sortoption->the_mat_crit.getOption());
				comp_crit.the_mat_crit.setAscending(typecasted_sortoption->the_mat_crit.getAscending());
				//
				comp_crit.setSortIntFirst(typecasted_sortoption->getSortIntFirst());
			}				
		}
		
		
		// Comparison: first the integer
		// step 1: extract a pointer (to the integer component) from "other"
		const integer_item* the_other_int_ptr = typecasted_other_item->getCP2the_int();		
		// step 2: check if it is larger (use the "integer part" of the criteria);
		result_int_larger = the_int.IsLargerThan(the_other_int_ptr, &(comp_crit.the_int_crit));
		// step 3: check if it is equal (use the "integer part" of the criteria);
		result_int_equal = the_int.IsEqualTo(the_other_int_ptr, &(comp_crit.the_int_crit));
		
		// Comparison: next the matrix
		// step 1: extract a pointer (to the matrix component) from "other"
		const intmat_item* the_other_mat_ptr = typecasted_other_item->getCP2the_mat();		
		// step 2: check if it is larger (use the "matrix part" of the criteria);
		result_mat_larger = the_mat.IsLargerThan(the_other_mat_ptr, &(comp_crit.the_mat_crit));
		// step 3: check if it is equal (use the "matrix  part" of the criteria);
		result_mat_equal = the_mat.IsEqualTo(the_other_mat_ptr, &(comp_crit.the_mat_crit));		
		///
		
		if(comp_crit.getSortIntFirst())
		{
			// the integer component is sorted first;
			if(result_int_larger)
				return true;// the integer component is larger;
			if(result_int_equal)
				return result_mat_larger; // the integer component is euqal, so the matrix decides;
			return false; // the integer component is smaller;
		}
		// the matrix component is sorted first;
		if(result_mat_larger)
			return true;// the mat component is larger;
		if(result_mat_equal)
			return result_int_larger; // the mat component is euqal, so the integer decides;
		return false;	// the mat component is smaller;		
	}
	virtual bool compatibilityCheck(const basic_item* other_item) const
	{
		bool result = false;

		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item != NULL)
		{
			// typecast the other item to confirm it is the same as this;
			const compsite_item* typecasted_other_item = typecastItem(other_item, this);
			if (typecasted_other_item != NULL)
				result = true;
			else
			{
				cout << endl << "Check failed for Item type: ";
				cout << itemTypeName << endl;
			}
		}
		return result;
	}
	virtual bool IsEqualTo(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const	
	{
		bool result_int_equal, result_mat_equal;
		compsite_item_sort_criteria comp_crit;
				
		// if the other item is "empty" (non allocated) don't do any comparison
		if(other_item==NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		const compsite_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type integer_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// if eitehr is not initialized, return false
		if( this->isEmpty() || (typecasted_other_item->isEmpty()) )
		{
			cout << "Either or both items are empty." << endl;
			return false;
		}
		
		// now verify if either/both component of the other item are equal		
		
		// preliminary step:
		// first check the input cirteria is of the correct type
		if (sort_criteria != NULL)
		{
			// first typecast the other item to confimr it is the correct type;
			const compsite_item_sort_criteria* typecasted_sortoption = typecastItem(sort_criteria, &comp_crit);
			if (typecasted_sortoption != NULL)
			{
				// copy the criteria (for each component) into (the local copy) comp_crit (otherwise filled with default values); 
				comp_crit.the_int_crit.setAscending(typecasted_sortoption->the_int_crit.getAscending());
				comp_crit.the_mat_crit.setOption(typecasted_sortoption->the_mat_crit.getOption());
				comp_crit.the_mat_crit.setAscending(typecasted_sortoption->the_mat_crit.getAscending());
				//
				comp_crit.setSortIntFirst(typecasted_sortoption->getSortIntFirst());
					comp_crit.setEqualityOption(typecasted_sortoption->getEqualityOption());
			}				
		}
		
		
		// Comparison: first the integer
		// step 1: extract a pointer (to the integer component) from "other"
		const integer_item* the_other_int_ptr = typecasted_other_item->getCP2the_int();			
		// step 2: check if it is equal (use the "integer part" of the criteria);
		result_int_equal = the_int.IsEqualTo(the_other_int_ptr, &(comp_crit.the_int_crit));
		
		// Comparison: next the matrix
		// step 1: extract a pointer (to the matrix component) from "other"
		const intmat_item* the_other_mat_ptr = typecasted_other_item->getCP2the_mat();		
		// step 2: check if it is equal (use the "matrix  part" of the criteria);
		result_mat_equal = the_mat.IsEqualTo(the_other_mat_ptr, &(comp_crit.the_mat_crit));		
		///
		
		switch (comp_crit.getEqualityOption()) {
		case compsite_item_sort_criteria::int_equal:
			return result_int_equal;
			break;
		case compsite_item_sort_criteria::mat_equal:
			return result_mat_equal;	
			break;
		case compsite_item_sort_criteria::both_equal:
			return (result_mat_equal && result_int_equal);	
			break;
		default:
			cout << "ERROR: Option not set." << endl;	
			return false;
		}			
	}
};

#endif
