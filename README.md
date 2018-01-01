# C_warmup
Breadth &amp; Width first search functions in C

need to research the two algorithm concepts
set map width and map height with #define

make a function that takes a map input from an input file(?) and prints it out nicely formatted.
-determine how to feed the map in
-get used to double pointers


breadth first search would be to check all adjacent nodes before moving to the next level of nodes.
depth first search would be to search down one path fully before trying the other one.

Ultimately this comes down to a difference in the way coordinates of interest are stored and accessed.
Breadth first: beginning at the root, search adjacent tiles for movable zero tiles, change their digits to 4, and add them to the end of the queue of tiles to be searched from. Search from the oldest tile in the list, and add new tiles to the end of the list.
Depth first: use a stack variant. search for tiles and add any nearby tiles with a zero to the beginning of the list. Pop from the beginning of the list of get the next search tile.
-Assuming a data structure with an add pointer and a remove pointer:
--Last in First Out would have add constantly one location ahead of remove.
--First in First Out would have add and remove independent of each other, though add would always be at the end and remove at the beginning.

Data struct might be set up to have a toggle variable determining how add and remove pointers work.

Add always goes to the same place, it's remove that changes.

Prototype search algorithm
Add start location 
Remove location
if 3, done
change to 4
search, Add located zeroes
Remove location 
if 3, done
change to 4
search, Add located zeroes


typedef struct {
    int x;
    int y;
} coord

struct stack{
    int nextIn;
    int nextOut;
    coord list[MAP_H x MAP_W]
}


Example code from Stack Exchange
To create a char array using malloc which can be accessed as a 2D array using a[x][y] and with the data contiguous in memory, one could do:

/* NOTE: only mildly tested. */
char** allocate2Dchar(int count_x, int count_y) {
    int i;

    # allocate space for actual data
    char *data = malloc(sizeof(char) * count_x * count_y);

    # create array or pointers to first elem in each 2D row
    char **ptr_array = malloc(sizeof(char*) * count_x);
    for (i = 0; i < count_x; i++) {
        ptr_array[i] = data + (i*count_y);
    }
    return ptr_array;
}
Note that the returned ptr_array is a pointer to the array of row pointers. The address of the actual data can be referenced using ptr_array[0] (first col of first row would be the beginning of the data).

For deallocation, a normal free() on ptr_array would be insufficient as the data array itself will still be kicking about.

/* free data array first, then pointer to rows */
void free2Dchar(char** ptr_array) {
    if (!ptr_array) return;
    if (ptr_array[0]) free(ptr_array[0]);
    free(ptr_array);
}
Example usage:

#define ROWS 9
#define COLS 9
int main(int argc, char** argv) {
    int i,j, counter = 0;
    char **a2d = allocate2Dchar(ROWS, COLS);

    /* assign values */
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            a2d[i][j] = (char)(33 + counter++);
        }
    }

    /* print */
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%c ", a2d[i][j]);
        }
        printf("\n");
    }

    free2Dchar(a2d);
    return 0;
}
The above code in action:

[me@home]$ gcc -Wall -pedantic main.c
[me@home]$ ./a.out
! " # $ % & ' ( ) 
* + , - . / 0 1 2 
3 4 5 6 7 8 9 : ; 
< = > ? @ A B C D 
E F G H I J K L M 
N O P Q R S T U V 
W X Y Z [ \ ] ^ _ 
` a b c d e f g h 
i j k l m n o p q 
