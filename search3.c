#include <stdio.h>
#include <stdlib.h>

#define MAP_W 5
#define MAP_H 5

typedef struct
{
    int row;
    int column;
} coordinate;

/**************PROTOTYPES*********************/
void printMap(int **map);
int** allocateMemory();
void freeintMemory(int** ptr_array);
void freeCoordMemory(coordinate **pth_array);
void df_search(int **map);
void bf_search(int **map);
void finishPath(int **map, coordinate *path);

/**************MAIN****************************/
int main()
{
    int **map = allocateMemory();
    int input=0;

    //assign values to map
    for (int i = 0; i < MAP_H; i++) //For each row
    {
        for (int j = 0; j < MAP_W; j++) //For each column
        {
            scanf("%d",&input); //1 1 1 1 0  0 2 0 0 0  0 1 1 1 1  0 1 1 3 1  0 0 0 0 0
            map[i][j] = input;
            // printf("%d",input); //Debug
        }
        // printf("\n"); //Debug
    }

    //Find path and modify map to contain it
    df_search(map);
    //bf_search(map);

    //print map by passing **map
    printMap(map);

    freeintMemory(map);
    return 0;
}


/***************HELPER FUNCTIONS****************/
int** allocateMemory()
{
    //Allocate pointer space
    int **ptr_array = malloc( sizeof(int*) * MAP_H );

    //Allocate contiguous data space
    int *data = malloc( sizeof(int) * MAP_H * MAP_W);

    //Fill pointer array with addresses for each row of data
    for (int i = 0; i < MAP_H; i++)
    {
        ptr_array[i] = data + (i * MAP_W);
    }

    //Return the address of row address array
    return ptr_array;
}

void freeintMemory(int** ptr_array)
{
    if (!ptr_array) return;
    if (ptr_array[0]) free(ptr_array[0]);
    free(ptr_array);
}

void freeCoordMemory(coordinate** ptr_array)
{
    if (!ptr_array) return;
    if (ptr_array[0]) free(ptr_array[0]);
    free(ptr_array);
}

void printMap(int **map)
{
    for (int i=0; i<MAP_H; i++) //each row
    {
        for (int j=0; j<MAP_W; j++) //each column
        {
            printf("%d",map[i][j]);
        }
        printf("\n");
    }
}

void df_search(int **map)
{
    //allocate memory for 25 paths of length 25
    // coordinate **pth_array = malloc( sizeof(coordinate*) * 25); //for breadth
    coordinate *path = malloc(sizeof(coordinate) * 25 /** 25*/ );
    //Initialize path at -1.
    for (int i=0; i<25; i++)
    {
        path[i].row = -1;
        path[i].column = -1;
    }

    // //print valid path coordinates. Debug
    // for (int i=0; i<25; i++)
    // {
    //     if ((path[i].row == -1)||(path[i].column == -1))
    //         break;
    //     printf("%d, %d\n", path[i].row,path[i].column);
    // }

    //allocate memory for search array length 30, declare add & remove indices.
    coordinate *search = malloc(sizeof(coordinate) * 30);
    int add = 0;
    int remove = -1;
    //Initialize search array with -1.
    for (int i=0; i<30; i++)
    {
        search[i].row = -1;
        search[i].column = -1;
    }


    //Add start to search array
    search[add].row = 1;
    search[add].column = 1;
    add++;
    remove++;


    coordinate pos;
    for ( int i=0; i < 40; i++ ); //loop
    {
        //get search coord from search array
        pos.row = search[remove].row;
        pos.column = search[remove].column;

        //remove coord from search array
        search[remove].row = -1;
        search[remove].column = -1;
        add--;
        remove--;

        //add coord to path
        path[index].row = pos.row;
        path[index].column = pos.column;

        //search around coord
        //change search coord to 4
        //if zeros found, add their coords to search array
            //if two or more zeroes found, add the path index to the branches array.
            //if no zeroes found, remove entries from the path back to the last branch point
            //if there are zeroes around branch point then continue, if there are no zeroes then remove branch point from list, remove entries from the path back to the previous branch point and repeat check there
    //issue here, I want to remove the branch and go back to the previous branch if there are no more viable paths from this point, but if I add it into the search array it will add zeroes to the search array that were already there.
        //if 3 found, add its coords to the path and break loop

    }
    // //create a fabricated path for debug
    // for (int i=0; i<25; i++)
    // {
    //     path[i].row = pos.row;
    //     path[i].column = pos.column;
    //     if(i == 0)
    //         pos.column--;
    //     if((i==1)||(i==2)||(i==3))
    //         pos.row++;
    //     if((i==4)||(i==5)||(i==6))
    //         pos.column++;
    //     if(i==7)
    //         pos.row--;
    // }

    //send path to finishing function
    finishPath(map, path);

    //Free memory
    free(path);
}



void bf_search(int **map)
{
    //
}

void finishPath(int **map, coordinate *path)
{
    for (int i=0; i<25; i++)
    {
        if ((path[i].row == -1)||(path[i].column == -1))
            break;
        // printf("%d\n",i); //Debug loop number
        map[path[i].row][path[i].column] = 5;
    }
}




/*
TODO:

change allocate to sizeof(content)
set pos to variable start position
make index lowering function to keep breadth search array short
implement more intelligent df loop type
change remove strategy for breadth

*/
