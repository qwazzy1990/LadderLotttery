/***Name: Patrick Di Salvo
 * 0629465
 * */


#ifndef _STRING_
#define _STRING_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdarg.h>
#include "utilities.h"
#include "Numbers.h"

#define DEFAULT_SIZE 10000

#define PRINTSTRING false


/**
  MOST USEFUL THING EVER!!
  THE PREPROCESSOR WILL REPLACE destroystring(myarg) with destroystring_real(&myarg)
**/
#define destroystring(myarg) destroystring_real(&myarg)



#define resize_string(myarg, x) resize_string_real(&myarg, &x)


        /**PRE-PROCESSOR DIRECTIVES FOR ASCII VERIFICATION*****/
#define IS_UPPER(x) ((x>=65)&&(x<=90))
#define IS_LOWER(x) ((x>=97)&&(x<=122))
#define IS_DIGIT(x) ((x>=48)&&(x<=57))
#define IS_VISIBLE(x) ((x >= 33) && (x <= 126))

        /**PRE-PRCOCESSOR DIRECTIVIES FOR CONVERTING ARGUMENT TOKEN TO STRINGS***/

#define $(myarg) #myarg 

#define $$(myarg) $(myarg) 



    /***DEFINING FUNCTION POINTERS FOR STRING STATUS FUNCTIONS FIX ME:***/

/*typedef bool (*AllUpperFunc)(void* s);
typedef bool (*AllLowerFunc)(void* s);
typedef bool (*IsDigitFunc)(void * s);
typedef bool (*)*/

/***CASE SENSITIVITY ENUM****Set case sensitivity for comparison***/

enum cc{CASE_SENSITIVE, CASE_INSENSITIVE};
typedef enum cc CaseSensitivity;

enum sstat{OK_STRING, 
    FAIL_ADD_STRING, 
    FAIL_DELETE_STRING, 
    DNE_STRING, 
    DNF_STRING
};
typedef enum sstat StringStatus;

//typedef struct intt* Int;

struct str
{
    char* string;
    unsigned int len;
    PrintFunc print;
    CompareFunc compare;


    /***FUNCTION POINTERS FOR COPIERS****/

    struct str* (*copy)(struct str*);//DONE
    struct str* (*slice)(struct str*, unsigned int, unsigned int);//DONE
    struct str* (*copy_to)(struct str*, int);//DONE
    /**FUNCTION POINTERS TO CONVERTERS***/
    struct str* (*file_to_string)(FILE*);//DONE
    struct str* (*to_string)(Primitive, void*);//DONE
    struct intt* (*to_int)(struct str*);//DONE
    /***FUNCTION POINTERS TO ACCESSORS***/
    char* (*get)(struct str*);//DONE
    char (*get_char)(struct str*, int);//DONE
    struct intt* (*get_index)(struct str*, char);//DONE
    struct intt* (*get_ss_index)(struct str*, struct str*);

    /***FUNCTION POINTERS TO DESTROYERS***/
    StringStatus (*remove)(void*);//DONE
    void (*destroy)(void*);//DONE



    /***FUNCTION POINTERS TO SETTERS***/
    StringStatus (*add)(struct str*, char*);//DONE
    StringStatus (*add_char)(struct str*, char);//DONE
    StringStatus (*make_empty)(struct str*);

    /***FUNCTION POINTERS TO MUTATORS****/
    struct str* (*concat)(struct str*, struct str*);//DONE
    struct str* (*to_lower)(struct str*);//DONE
    struct str* (*to_upper)(struct str*);//DONE
    struct str* (*reverse)(struct str*);//DONE
    struct str* (*replace_all)(struct str*, char, char);//DONE
    struct str* (*replace_at)(struct str*, int, char);//DONE
    

    /****FIX ME: ADD TRIM FUNCTION****/
    struct str* (*trim)(struct str*);//FIX ME
    struct str* (*remove_hard_return)(struct str*);//FIX ME
    struct str* (*remove_at)(struct str*, int);//DONE
    struct str* (*remove_all)(struct str*, char);//DONE
    struct str* (*remove_once)(struct str*, char);//DONE

    /****FUNCTION POINTERS TO VALIDATORS****/
    bool (*empty)(struct str*);//FIX ME
    bool (*contains)(struct str*, char);//DONE
    bool (*contains_ss)(struct str*, struct str*);
    bool (*is_upper)(char);//DONE
    bool (*is_lower)(char);//DONES
    bool (*is_white)(char);//DONE
    bool (*is_digit)(char);//DONE
    bool (*is_alpha)(char);//DONE
    /***FIX ME: ADD LOWER AND UPPER VALIDATORS FOR STRING***/
    bool (*all_upper)(struct str*);//DONE
    bool (*all_lower)(struct str*);//DONE
    bool (*all_white)(struct str*);//DONE
    bool (*all_alpha)(struct str*);//DONE
    bool (*all_digit)(struct str*);//DONE
    bool (*is_number)(struct str*);//DONE
    bool (*alpha_numeric)(struct str*);//DONE
    bool (*equals)(struct str*, struct str*, CaseSensitivity);//DONE



};
typedef struct str Str;
typedef Str* String;

   





                        /******MEORY ALLOCATING FUNCTIONS******/

//DONE
String string_alloc(int size);


//DONE
void resize_string_real(String* s, int* size);




//DONE
String new_string( void );
//DONE
String createvoidstring(void);




/**
    Input: size
    Output: null-terminated string = to size
**/

//DONE
String createnstring(unsigned int size);






/******CONVERTERS***/



/***Function to convert data pointed to by a function pointer to a string object.
 * Pre-conditions: fp must not be NULL. fp must be terminated with EOF char
 * Post conditions: a new string objtect containing the file as an ASCII string.
 * */

//DONE
String readfile(FILE* fp);

/**Function to convert a String to an int
 * Pre-conditions: s must not be null. s->string must not be null. s->string must be all digit or digit with leading '-' or digit 
 * with intermediate '.' or any combination of above mentioned requirements
 * Post-conditions: an integer representation of s->string
 * */

//DONE
Int stringtoint(String s);

/**
    Function to convert data in memory to a string
    Preconditions: The data must be numeric, i.e. floating point or integer
    Postconditions: A string containing the data is returned
**/

//DONE
String tostring(Primitive type, void* data);



                      /***********DESTROYERS****************/

/**
    Input: string
    Output: freed string
**/



//DONE FUNCTION
void destroy_string(void* s);

/**clears s->string. Sets s->len = 0**/
//DONE FUNCTION
StringStatus remove_char_star(void* s);







                    /***************COPIERS********************/
/**
   Function to copy a string to another
   Preconditions: Source must exist and contain content
   Postconditions:  Source is unchanged
   Input: source string
   Output: newstring with content of source
**/

//DONE
String stringcopy(String source);


/***Function to copy the first n characters of source->string.
 * Creates a new String with newString->string = to copy of first n characters in source->string
 * */

//DONE
String stringncopy(String source, int n);






    /**
      Function to copy a segment of a string to another from start to end.
      The copy includes both the start and end character
      Preconditions: Source must exist and contain content. The end must be >= to
      the start. The start must be > 0. The end will be reduced to length of source if
      > than length of source.
      Postconditions: Source is unchanged, copy of segment of source is returned
    **/

//DONE
String stringsegmentcopy(String s, unsigned int start, unsigned int end);






                      /***************MUTATORS****************/

                /****NOTE: ALL MUTATORS PERMANENTLY MODIFY STRING OR STRINGS ARGUMENTS PASSED TO THEM****/



/**
  Function to concatenate one string to the end of another
  Preconditions: Neither Source nor Dest can be NULL
                 source must be null terminated

   Postconditions: Source is unchanged. Destination is modified with source appended
**/

//DONE
String stringcat(String dest, String source);



/**
    Function to reverse the order of a string
    Preconditions: string muest not be empty or null
    Postconditions: New string in reverse order. s is freed
**/

//DONE
String reversestring(String s);


/**Creates a new String with the character of s->string[index] with c**/


//DONE
String replace_in_string(String s, int index, char c);


//DONE
String replace_all_string(String s, char r, char c);

/***Creates a string wih newString->s in all lower case
 * of s->string
 * Preconditions: s->string does NOT have to be all alpha
 * ***/

//DONE
String to_lower(String s);


/***Creates a string wih newString->s in all upper case
 * of s->string
 * Preconditions: s->string does NOT have to be all alpha
 * ***/


//DONE
String to_upper(String s);



//DONE
String remove_in_string_once(String s, char c);

//DONE
String remove_all_in_string(String s, char c);


//DONE
String remove_char_at(String s, int index);

String trim(String s);

String remove_hard_return(String s);

                        /*************PRINT FUNCTIONS**************/


//DONE
char* print_string(void* s);


                        /****SETTERS***/

//DONE
StringStatus add_char_star(String s, char* ch);


//DONE
StringStatus add_char(String s, char c);

StringStatus make_empty(String s);

                        /**************VALIDATORS**********/
/**
    Checks if a pointer is NULL or Empty
      Returns true if NULL or Empty
      else false
**/

//DONE
bool badstring(String s);

                      /**Checks if a string is static
                         Returns true if static else false**/
bool isstatic(String s);

//DONE
bool is_upper(char c);


//done
bool is_lower(char c);


//DONE
bool is_white(char c);
//DONE
bool is_alpha(char c);
//DONE
bool is_digit(char c);
//DONE
bool contains_char(String s, char c);
//DONE 
bool all_upper(String s);
//FIX ME
bool all_lower(String s);

//DONE
bool all_white(String s);
//FIX ME
bool all_alpha(String s);
//DONE
bool all_digit(String s);
//DONE
bool is_number(String s);
//DONE
bool alpha_numeric(String s);
//DONE
bool empty_string(String s);

//DONE
bool strequal(String s1, String s2, CaseSensitivity c);

//TEST ME
bool contains_substring(String s, String ss);
//DONE
int string_compare(const void* a, const void* b);


                    /**
                     * Checks of two String are equal. Returns an object of type EqualStringStatus.
                     * If strings are equal EqualStringStatus returns true and -1
                     * Else returns false and the index at which the strings differ
                     * */




                                    /*****ACCESSORS*****/


        /**
         * Gets the length of a string.
         * Preconditions: string must exist
         * Postconditions: string remains unchanged and length of string excluding null terminator is returned
         * */

//DONE
int stringlen(String s);


        /**
         * Returns the indecies of all occurrencs of c in s.
         * Returns a dynamic array of all indecies of c in s terminated with a value of -1. Or  if no occurences of c in s then returns 
         * array with value of -1.
         * Preconidtions: s must exist. c must be a valid character
         * Postconditions: s and c remain unchanged. 
         * */

//DONE
Int indecies_of_char(String s, char c);


//TEST ME
Int indecies_of_substring(String s, String ss);


//DONE
char* get_char_star(String s);

        /**
         * Gets the nth characters in string s
         * Preconditions: string must exist and be non empty. n must be >= 1 and <= string length
         * Postconidtions: The nth character in string s is returned. 
         * */
//DONE
char getch(String s, int n);







#endif
