/**
 * NAME: Patrick Di Salvo
 * 0629465
 * */


#ifndef _STRING_ARRAY_
#define _STRING_ARRAY_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "DynamicString.h"
#include "utilities.h"




//#define destroy_string_array(a) destroy_string_array_real(&a)
enum SAE{
    OK_STRING_ARRAY,
    DNF_STRING_ARRAY, 
    DNE_STRING_ARRAY,
    MEM_ERR_STRING_ARRAY,
    FAIL_DELETE_STRING_ARRAY,
    FAIL_ADD_STRING_ARRAY
};typedef enum SAE StringArrayError;


struct sa{
    String* strings;
    unsigned int size;
    PrintFunc print;
    DeleteFunc destroy;
    CloneFunc clone;
    CompareFunc compare;

    /**FUNCTION POINTERS FOR OBJECT ORIENTED APPROACH***/

    /***CONSTRUCTOR FP***/
    struct sa* (*split)(String, String);//FIX ME

    /***COPIER FP***/
    struct sa* (*copy)(struct sa*);
    struct sa* (*slice)(struct sa*, int, int);
    /***ACCESSOR FP***/
    unsigned int (*get_size)(struct sa*);
    String (*get_at)(struct sa*, int);
    Int (*get_index)(struct sa*, String);


    /**DESTROYER FP***/
    void (*remove_all)(struct sa*);//ADD FUNCTION
    struct sa* (*remove)(struct sa*, String);
    struct sa* (*remove_at)(struct sa*, int);
    struct sa* (*remove_once)(struct sa*, String);

    /**SETTER FP***/
    StringArrayError (*add)(struct sa*, String);
    StringArrayError (*make_empty)(struct sa*);
    struct sa* (*concat)(struct sa*, struct sa*);

    /***SORTERS***/
    void (*sort)(struct sa*, CaseSensitivity);

    /***MUTATOR FP***/
    //void (*print)(AnyData);

    /***VALIDATOR FP***/
    bool (*empty)(struct sa*);
    bool (*contains)(struct sa*, String);
    bool (*equals)(struct sa*, struct sa*, CaseSensitivity);//FIX ME: ADD FUNCTION

};typedef struct sa SA;
typedef SA* StringArray;




/*****CONSTRUCTORS***/
StringArray new_string_array(void);


StringArray new_string_array_clone(CloneFunc cl);


//DONE
StringArray split(String s, String delims);
StringArray split_substring(String s, String delims);

/****END CONSTRUCTORS***/

/****ACCESSORS*****/

unsigned int get_string_array_size(StringArray a);

//FIX ME
String get_string(StringArray a, int index);

//FIX ME
Int get_string_index(StringArray a, String s);

/*****END ACCESSORS***/
/***COMPARATORS***/

//FIX ME
int string_array_compare(const void* a, const void* b);

/***END COMPARATORS***/
/****DESTROYERS*****/

//DONE
void destroy_string_array_real(void* sa);

//DONE
void remove_all_string_array(StringArray a);

//DONE
StringArray remove_string_at(StringArray a, int n);

//DONE
StringArray remove_string_once(StringArray a, String s);

//DONE
StringArray remove_string(StringArray a, String s);


/***END DESTROYERS****/

/****SETTERS****/

//DONE
StringArrayError add_string(StringArray a, String s);

StringArrayError make_string_array_empty(StringArray sa);

//DONE
StringArray concat_string_array(StringArray dest, StringArray source);

//DONE
StringArray string_array_copy(StringArray a);

//DONE
StringArray string_array_segment_copy(StringArray a, int start, int end);


/***END SETTERS***/

/*****MUTATORS****/


    /****PRINTERS****/
        //DONE
        char* print_string_array(AnyData d);
    /***END PRINTERS***/

    /***SORTERS***/
        //FIX ME
        void sort_string_array(StringArray a, CaseSensitivity mode);
    /***END SORTERS***/
/****END MUTATORS***/

/***VALIDATORS****/

    //DONE
    bool is_empty_string_array(StringArray a);

    //DONE
    bool contains_string(StringArray a, String s);

    //DONE
    int compare_string_array(const void* a, const void* b);

    //DONE
    bool equals_string_array(StringArray a, StringArray b, CaseSensitivity mode);
/***END VALIDATORS***/



#endif