#pragma once
#include "arrayItem_v3.h"

void testItemFunctions_part1(basic_item* item_ptr)
{
	cout << "Function printing item type" << endl;
	item_ptr->printItemTypeName();
	cout << endl;

	cout << "Function requesting user to input item value" << endl;
	item_ptr->enterItemFromKeyboard();
	cout << endl;

	cout << "Function printing item on Screen" << endl;
	item_ptr->printItemOnScreen();
	cout << endl;

	cout << "Function generating Random item " << endl;
	item_ptr->generateRandomItem();
	item_ptr->printItemOnScreen();
	cout << endl;
	cout << endl;
}


void testItemFunctions_part2(basic_item* item_ptr_1, basic_item* item_ptr_2, basic_sort_criteria* sort_criteria)
{
	cout << "Assigning Random values to first item" << endl;
	item_ptr_1->generateRandomItem();
	item_ptr_1->printItemOnScreen();
	cout << endl;

	cout << "Assigning Random values to second item" << endl;
	item_ptr_2->generateRandomItem();
	item_ptr_2->printItemOnScreen();
	cout << endl;

	cout << "Check compatibility between the items" << endl;
	bool comparison = item_ptr_1->compatibilityCheck(item_ptr_2);
	if (comparison)
		cout << "Items compatible" << endl;
	else
		cout << "Items NOT compatible" << endl;
	cout << endl;

	cout << "Function comparing two items" << endl;
	if (sort_criteria != NULL)
	{
		cout << "  Set the comparison criteria:" << endl;
		sort_criteria->setOptionFromKeyboard();
		cout << endl;
	}
	comparison = item_ptr_1->IsLargerThan(item_ptr_2, sort_criteria);
	if (comparison)
		cout << "First item larger than the second" << endl;
	else
		cout << "First item smaller (or equal) than the second" << endl;

	cout << endl;
	cout << endl;
}



void test_IndividualItem()
{
	// Try each one below (ucomment one line at a time)
	// When ready, repleace these with items of the type you have implemented 

	integer_item testitem1, testitem1a; basic_sort_criteria testsort_crit;
	//intmat_item testitem1, testitem1a; intmat_sort_criteria testsort_crit; //testsort_crit.setOption(intmat_sort_criteria::sort_determ);


	// 
	cout << "Test input funcitons:" << endl;
	testItemFunctions_part1(&testitem1);
	cout << endl;
	cout << "Now with locked item:" << endl;
	testitem1.setLocked(true);
	testItemFunctions_part1(&testitem1);
	testitem1.setLocked(false);
	cout << endl;


	cout << "Test comparison of two items:" << endl;
	// this uses the default comparison option:
	//testItemFunctions_part2(&testitem1, &testitem1a, NULL);

	// this uses the full default comparison rule (via user input)
	testItemFunctions_part2(&testitem1, &testitem1a, &testsort_crit);
	cout << endl;

}