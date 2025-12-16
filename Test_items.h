#pragma once
#include "arrayItem_v3.h"
#include "RB_R1.h"
#include "Release2&3.h"

//Release 1 Testing - Ryan
void testRangeFunctions(integer_itemWithLimits_Ryan* itemWithRange_ptr){
	cout << "Function printing item type" << endl;
	itemWithRange_ptr->printItemTypeName();
	cout << endl;

	cout << "Function requesting user to input range limits." << endl;
	itemWithRange_ptr->enterSetRangeFromKeyboard();
	cout << endl;

	cout << "Function requesting user to input item value" << endl;
	itemWithRange_ptr->enterItemFromKeyboard();
	cout << endl;

	cout << "Function printing item and range on screen." << endl;
	itemWithRange_ptr->printItemAndRange();
	cout << endl;

	cout << "Function to get the minimum range limit." << endl;
	cout << "Minimum Limit: " << itemWithRange_ptr->getMinValRange() << endl;

	cout << "Function to get the maximum range limit." << endl;
	cout << "Maximum Limit: " << itemWithRange_ptr->getMaxValRange() << endl;

	cout << "Function to generate random item within the range limits." << endl;
	itemWithRange_ptr->generateRandomItemWithinRange();
	cout << endl;

	cout << "Function printing item and range on screen." << endl;
	itemWithRange_ptr->printItemAndRange();
	cout << endl;
}

void testStringClass(string_item* item_ptr){
	cout << "Function printing item type" << endl;
	item_ptr->printItemTypeName();
	cout << endl;

	cout << "Function requesting user to input string." << endl;
	item_ptr->enterItemFromKeyboard();
	cout << endl;

	cout << "Function printing item and range on screen." << endl;
	item_ptr->printItemOnScreen();
	cout << endl;

	cout << "Function to clear string item." << endl;
	//item_ptr->clearString();
	cout << endl;

	cout << "Function to generate random item." << endl;
	item_ptr->generateRandomItem();
	cout << endl;

	cout << "Function printing item and range on screen." << endl;
	item_ptr->printItemOnScreen();
	cout << endl;
}

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

	//Testing release 1 implemented function - Ryan.
	integer_itemWithLimits_Ryan testRange1;

	//Testing release 2 string class - Ryan
	string_item testString1;
	//intmat_item testitem1, testitem1a; intmat_sort_criteria testsort_crit; //testsort_crit.setOption(intmat_sort_criteria::sort_determ);


	//Release 1 testing - Ryan
	//cout << "Test input range funcitons:" << endl;
	//testRangeFunctions(&testRange1);
	//cout << endl;

	//Release 2 string class testing - Ryan
	cout << "Test string class funcitons:" << endl;
	testStringClass(&testString1);
	cout << endl;
	//testItemFunctions_part1(&testitem1);
	//cout << "Now with locked item:" << endl;
	//testitem1.setLocked(true);
	//testItemFunctions_part1(&testitem1);
	//testitem1.setLocked(false);
	//cout << endl;


	//cout << "Test comparison of two items:" << endl;
	// this uses the default comparison option:
	//testItemFunctions_part2(&testitem1, &testitem1a, NULL);

	// this uses the full default comparison rule (via user input)
	//testItemFunctions_part2(&testitem1, &testitem1a, &testsort_crit);
	//cout << endl;

}