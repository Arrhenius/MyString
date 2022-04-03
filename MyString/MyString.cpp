#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "help_func.h"
#include "MyString.h"


//MyString class constructor
MyString::MyString()
{
	size	= 0;
	string	= NULL;
}

// Overloaded MyString class constructor 
MyString::MyString(const char* pszString)
{

	size	= 0;	// Initialize object variable size to 0
	string	= NULL;	// Initialize object variable string to NULL
	if (*pszString)
	{
		const char*	ptr;	// Variable used to traverse pszString
		char*		ptr2;	// Variable used to copy to object variable string

		ptr = pszString;	// point to pszString
		while (*ptr)		// count chars within string to determine size
			size++;

		// Allocate memory for string. Error check to see if
		// memory allocation succeeded
		string = (char*)malloc(sizeof(char) * size + 1);
		if (!string)
			errExit("Failed to malloc memory for string!", __FILE__, __LINE__);
		memset(string, 0, sizeof(string));
		ptr = pszString;				// Assign ptr to pszString for traversing
		ptr2 = string;					// Assign ptr2 to string to copy chars into memory
		while (*ptr2++ = *pszString++);	// Copy pszString to object variable string
	}
	else
		return;
}

// Object MyString deconstructor checks if there is data
// and then frees the string of that memory.
MyString::~MyString()
{
	// Wipe allocated memory of data before freeing
	// This is just in case there is some sort of sensitive data
	// present and we no longer want any representation of it
	// in memory
	if (string)
	{
		memset(string, 0, sizeof(string));
		free(string);
	}
}

// Function reverses the string characters in object variable string
void MyString::reverse()
{
	char*	begin_ptr;	// pointer to beginning of string
	char*	end_ptr;	// pointer to end of string
	char	tmp;		// char holder when swapping places

	begin_ptr = end_ptr = string;		// place pointers at the beginning of string
	end_ptr = end_ptr + (size - 1);	// move end_ptr to the end of string

	// while the end pointer and beginning pointer haven't met at
	// the same point in memory, move the end_ptr up the string
	// and move the begin_ptr down the string
	while (end_ptr > begin_ptr)
	{
		tmp = *begin_ptr;		// hold char for begin_ptr
		*begin_ptr = *end_ptr;	// change char at begin_ptr to end_ptr char
		*end_ptr = tmp;			// change char at end_ptr to begin_ptr char
		end_ptr--;				// move ptr up string
		begin_ptr++;			// move ptr down string
	}
}

// Function appends a string to the end of object variable string.
// Reallocation of memory occurs and the proceeds to copy the
// string to the end of the original string
void MyString::append(const char* pszString)
{
	const char*	src_ptr;
	char*		dest_ptr;
	char*		tmp;
	int			pszStringSize = 0;

	if (*pszString)
	{
		dest_ptr = string;		// assign dest_ptr to original string
		src_ptr = pszString;	// assign src_ptr to string that will be appended 
								// to original string

		// Count characters in string to determine size
		while (*src_ptr)
			pszStringSize++;

		// realloc original string size to fit original string and the new string
		// to be appended to it. Error check to make sure realloc did not fail.
		tmp = (char*)realloc(string, sizeof(string) + pszStringSize + 1);
		if (!string)
			errExit("Failed to realloc string!", __FILE__, __LINE__);


		string = tmp;		// reassign reallocated string from tmp to object variable string
		while (*dest_ptr)	// Move dest_ptr to end of string to append pszString
			dest_ptr++;		// to the original string

		while (*dest_ptr++ = *src_ptr++);	// copy string to be appended to original
											// string until null terminator is reached
		*dest_ptr = '\0';					// Add null terminator to end of string


		// change string object size to new size that includes the appended string
		size = size + pszStringSize;
	}
	else
	{
		fprintf(stderr, "Failed to append string. Returning from function\n");
		return;
	}
}



/*
 * Note:	This function is meant to handle ASCII characters only.
 *			I have not taken the time to develop these functions to
 *			use UNICODE at this time but plan to add the functionality
 *			in the future. If the characters present are not part of
 *			this table it will simply skip the character and go on to
 *			the next one. If the whole string doesn't have ASCII
 *			characters than the string won't be changed at all.
 */
void MyString::toUpperCase()
{
	char* char_ptr;			// variable used to traverse the string
	char_ptr = string;		// point char_ptr to object variable string
	if (*char_ptr)			// Check to see if data is present
	{
		while (*char_ptr)	// While there are characters, perform loop instructions
		{
			if (*char_ptr >= 97 && *char_ptr <= 122)// Check to see if the character is lowercase, if it is
				*char_ptr -= 32;					// proceed to subtract a decimal value of 32 to obtain
													// the uppercase ascii character
			char_ptr++;								
		}
	}
}

/*
 * Note:	This function is meant to handle ASCII characters only.
 *			I have not taken the time to develop these functions to
 *			use UNICODE at this time but plan to add the functionality
 *			in the future. If the characters present are not part of
 *			this table it will simply skip the character and go on to
 *			the next one. If the whole string doesn't have ASCII
 *			characters than the string won't be changed at all.
 */
void MyString::toLowerCase()
{
	char* char_ptr;			// variable used to traverse the object variable string
	char_ptr = string;		// point char_ptr to object variable string
	if (*char_ptr)			// Check to see if data is present
	{
		while (*char_ptr)	// While there are characters, perform loop instructions
		{
			if (*char_ptr >= 65 && *char_ptr <= 90)	// Check to see if the character is uppercase, if it is
				*char_ptr += 32;					// proceed to add a decimal value of 32 to obtain
													// the lowercase ascii character
			char_ptr++;								// Increase pointer position in string by 1
		}
	}
}



// This function acts like the java method substring when
// handling string objects. It starts at the index indicated
// by beginIndex and ends at endIndex - 1. beginIndex is
// an inclusive value while endIndex is exclusive
// NOTE:
// The function is meant to allocate memory for a new string and
// returns a pointer to that string. It is up to the user to remember
// to free that memory and avoid memory leaks
char* MyString::subString(int beginIndex, int endIndex)
{
	char*	substr = NULL;
	char*	begin;
	int		size = 0;
	if (beginIndex < 0)
	{
		fprintf(stderr, "beginIndex can't be less than 0!\n");
		fprintf(stderr, "Return from function...\n");
		return;
	}
	if (endIndex > getSize())
	{
		fprintf(stderr, "endIndex is greater than the size of the string!\n");
		fprintf(stderr, "Value provided can't be greater than string size\n");
		fprintf(stderr, "Function is returning");
		return;
	}
	size = endIndex - beginIndex;
	substr = (char*) malloc(sizeof(char) * (size + 1));
	if (!substr)
	{
		fprintf(stderr, "Failed to allocate memory for substring!\n");
		fprintf(stderr, "Returning from function with NULL value...\n");
		return NULL;
	}
}

int MyString::getSize()
{
	return size;
}

char* MyString::getString()	const
{
	return string;
}

