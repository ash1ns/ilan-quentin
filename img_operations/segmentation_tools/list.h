#ifndef LIST
#define LIST

// this is the basic chained list we saw in programming course.
typedef struct List List;
struct List
{
    struct List *next; // the next value of the list
    int *letter; // the pixels inside of this element
    int width; // the width of the image the element contain 
    int height; // the height of the image the element contain
};

#endif

