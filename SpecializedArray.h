#pragma once

// include the version of item (derived from basic_item) you want to build the array around
#include "ArrayItem_v3.h"
#include "generalArraywithTemplate_v2.h"

#include "RB_R1.h"
#include "Zayne_Release1.h"

#include "Release2&3.h"

#include "Release4.h"

// array of integer_item
typedef items_array <integer_item> int_item_array;

// array of intmat_item
typedef items_array <intmat_item> intmat_item_array;


typedef items_array <integer_itemWithLimits_Zayne> int_item_array_with_limits;

//array of integer_itemWithLimits_Ryan 
typedef items_array <integer_itemWithLimits_Ryan> int_item_limits_array;

//array of string_item 
typedef items_array <string_item> string_array;

//Array of group1_item
typedef items_array <group1_item> group1_array;


// specializing a function (example)
/*
template <>
void int_item_array::functionToBeImplementedDifferentlyForThisType()
{
	// code that is specific to this type
}
*/


