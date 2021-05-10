//
//  replace_substring.c
//  ReplaceSubstring
//
//  Created by Simon Schöpke on 08.05.21.
//

#include "replace_substring.h"

#include <string.h>

/// Zeilenende
#define END_OF_LINE '\0'

static void copy_until(char *end_ptr, char *start_ptr, char *output)
{
    while (start_ptr != end_ptr)
    {
        *output = *start_ptr;
        start_ptr++;
        output++;
    }
}

extern void replace_substring(char *origin, char *replace, char *with, char *new_str)
{
    unsigned long len_replace;
    unsigned long len_with;
    unsigned long distance_to_occurrence;
    char *occurrence;
    
    if (origin == NULL || replace == NULL || with == NULL || new_str == NULL)
    {
        return;
    }
    
    len_replace = strlen(replace);
    len_with = strlen(with);
    distance_to_occurrence = 0;
    occurrence = NULL;
    
    while (*origin != END_OF_LINE)
    {
        occurrence = strstr(origin, replace);
        distance_to_occurrence = occurrence - origin;
        
        if (occurrence == NULL)
        {
            strcpy(new_str, origin);
            return;
        }
        
        copy_until(occurrence, origin, new_str);
        new_str += distance_to_occurrence;
        origin = occurrence + len_replace;
        
        strcpy(new_str, with);
        new_str += len_with;
    }
}
