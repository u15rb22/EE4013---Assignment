#pragma once
#include "generalArraywithTemplate_v2.h"
#include "SpecializedArray.h"
#include "Zayne_Release1.h"

void testArrayWithLimits()
{
	int arraysize;

	// uncomment either line below:
	int_item_array_with_limits testArray;
	//intmat_item_array testArray;
	testArray.printArrayInfoOnScreen();
	cout << "Enter arraysize and hit enter: " << endl;
	cin >> arraysize;
	testArray.allocateArray(arraysize);
	testArray.printArrayInfoOnScreen();
	testArray.printArrayOnScreen();
	// 
	testArray.fillRandomValueArray();
	testArray.printArrayOnScreen();
	cout << endl;
	//	
	cout << "Test input funciton:" << endl;
	testArray.enterArrayFromKeyboard();
	testArray.printArrayOnScreen();
	//
	cout << "Now with locked Array:" << endl;
	testArray.setArrayLocked(true);
	testArray.fillRandomValueArray();
	testArray.printArrayOnScreen();
	testArray.setArrayLocked(false);
	cout << endl;
}

void testArrayWithLimitsRyan()
{
	int arraysize;

	// uncomment either line below:
	int_item_limits_array testArray; basic_sort_criteria testsort_crit;
	//intmat_item_array testArray;
	testArray.printArrayInfoOnScreen();
	cout << "Enter arraysize and hit enter: " << endl;
	cin >> arraysize;
	testArray.allocateArray(arraysize);
	testArray.printArrayInfoOnScreen();
	testArray.printArrayOnScreen();
	//
	testArray.fillRandomValueArray();
	testArray.printArrayOnScreen();
	cout << endl;
	//	
	cout << "Test input funciton:" << endl;
	testArray.enterArrayFromKeyboard();
	testArray.printArrayOnScreen();
	//
	//
	testsort_crit.setOptionFromKeyboard();
	testArray.bubblesort(&testsort_crit);
	testArray.printArrayOnScreen();
	cout << endl;
	cout << endl;
}

void testArrayWithStrings(){
	int arraysize;
	string_array testArray1;

	testArray1.printArrayInfoOnScreen();
	cout << "Enter arraysize and hit enter: " << endl;
	cin >> arraysize;
	testArray1.allocateArray(arraysize);
	testArray1.printArrayInfoOnScreen();
	testArray1.printArrayOnScreen();
	//
	//testArray1.fillRandomValueArray();
	//testArray1.printArrayOnScreen();
	//cout << endl;
	//	
	cout << "Test input funciton:" << endl;
	testArray1.enterArrayFromKeyboard();
	testArray1.printArrayOnScreen();
	//
	//
}

void testArrayFunctions_part1()
{
	int arraysize;

	// uncomment either line below:
	int_item_array testArray;
	//intmat_item_array testArray;

	testArray.printArrayInfoOnScreen();
	cout << "Enter arraysize and hit enter: " << endl;
	cin >> arraysize;
	testArray.allocateArray(arraysize);
	testArray.printArrayInfoOnScreen();
	testArray.printArrayOnScreen();
	// 
	cout << "Test random input funciton:" << endl;
	testArray.fillRandomValueArray();
	testArray.printArrayOnScreen();
	cout << endl;
	//	
	cout << "Test input funciton:" << endl;
	testArray.enterArrayFromKeyboard();
	testArray.printArrayOnScreen();
	//
	cout << "Now with locked Array:" << endl;
	testArray.setArrayLocked(true);
	testArray.fillRandomValueArray();
	testArray.printArrayOnScreen();
	testArray.setArrayLocked(false);
	cout << endl;
}

void testArrayFunctions_withRange()
{
	int arraysize;

	int_item_array_with_limits testArray; basic_sort_criteria testsort_crit;
	cout << "Enter arraysize and hit enter: " << endl;
	cin >> arraysize;
	testArray.allocateArray(arraysize);
	testArray.printArrayInfoOnScreen();
	testArray.printArrayOnScreen();
	//	
	cout << "Test input funciton:" << endl;
	testArray.enterArrayFromKeyboard();
	testArray.printArrayOnScreen();
	//
	testsort_crit.setOptionFromKeyboard();
	testArray.bubblesort(&testsort_crit);
	testArray.printArrayOnScreen();
	cout << endl;
}

void testArrayFunctions_part2()
{
	int arraysize;
	int_item_array testArray; basic_sort_criteria testsort_crit;
	//intmat_item_array testArray; intmat_sort_criteria testsort_crit;


	cout << "Enter arraysize and hit enter: " << endl;
	cin >> arraysize;
	testArray.allocateArray(arraysize);

	cout << " Fill array randomly: " << endl;
	testArray.fillRandomValueArray();
	testArray.printArrayOnScreen();
	cout << "Done." << endl;

	cout << " Choose sort criterion: " << endl;
	testsort_crit.setOptionFromKeyboard();
	cout << "Done." << endl;

	cout << " Sort array and print the result: " << endl;
	testArray.bubblesort(&testsort_crit);
	testArray.printArrayOnScreen();
	cout << "Done." << endl;
}

