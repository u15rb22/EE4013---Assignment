#pragma once

// include the version of item (derived from basic_item) you want to build the array around
#include "ArrayItem_v3.h"
#include "generalArraywithTemplate_v2.h"
#include "Zayne_Release1.h"

// array of integer_item
typedef items_array <integer_item> int_item_array;

// array of intmat_item
typedef items_array <intmat_item> intmat_item_array;

typedef items_array <integer_itemWithLimits_Zayne> int_item_array_with_limits;



// specializing a function (example)