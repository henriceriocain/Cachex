// Author: Henri Cerio-Cain
// Date: April 9, 2024
// Purpose: To pass this course - pls Dr.Brodsky

// Include statement
#include <string.h>
#include "cache.h"

// Attributes
// Line struct
struct Line {
    unsigned long id;
    unsigned char values[64];
};

// Cache struct; uses the fast memory provided and holds the cache lines
struct Cache{
    struct Line *lines;
    int initialized;
};

// Cache struct
struct Cache cache;

// Methods
// init method; sets up all the pointers and structures
void init() {
    cache.initialized = 13;
    cache.lines = (struct Line *)c_info.F_memory;
}

// cache_get method; takes a memory address and a pointer to a value and loads a word (a long) located at memory address
//                   and copies it into the location pointed to by value.
int cache_get(unsigned long address, unsigned long *value) {

//    Ensures that the cache has been initialized
    if (cache.initialized != 13) {
        init();
    }

//    Local variables
    unsigned long tag = address / 64;
    unsigned int index = (address / 64) % (c_info.F_size / sizeof(struct Line));
    unsigned int offset = address % 64;
    struct Line *line = &cache.lines[index];

//    Checks if the cache hit; offset is used to locate the word in that line, the word should be copied
//                             into the buffer pointed to by value, and then the function returns.
    if ((line->id == tag) && (line->values[offset] != 0) ) {

        memcpy(value, line->values + offset, sizeof(line));
        return 1;

//     Cache doesn't hit; victim line is selected, initialized with the tag of
//                        the needed memory block, and loaded
    } else if(memget((address / 64) * 64, line->values, sizeof(line)*10)) {

        line->id = tag;

        memcpy(value, line->values + offset, sizeof(line));
        return 1;

//     Complete failure
    } else {

        return 0;

    }

}
