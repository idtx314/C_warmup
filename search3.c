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
coordinate findStart(int **map);

/**************MAIN****************************/
int main()
{
    int **map = allocateMemory();
    int input=0;

    //assign values to map
    FILE *file_input;
    file_input = fopen("map.txt", "r");
    for (int i = 0; i < MAP_H; i++) //For each row
    {
        for (int j = 0; j < MAP_W; j++) //For each column
        {
            fscanf(file_input,"%d",&input);
            map[i][j] = input;
        }
    }
    fclose(file_input);

    //Find path and modify map to contain it
    df_search(map);
    // bf_search(map);

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
    int path_index = 0;
    //Initialize path at -1.
    for (int i=0; i<25; i++)
    {
        path[i].row = -1;
        path[i].column = -1;
    }

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
    coordinate pos = findStart(map);
    search[add].row = pos.row;
    search[add].column = pos.column;
    add++;
    remove++;

    //Allocate memory for array of path indices that are branch points
    int *branches = malloc(sizeof(int) * 10);
    int branch_index = 0; //index of branches to add to
    for(int i=0; i<10; i++)
        branches[i] = -1;

    //search loop
    int zerofind = 0;
    for ( int i=0; i < 40; i++ )
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
        path[path_index].row = pos.row;
        path[path_index].column = pos.column;
        path_index++;

        // //Debug print path array
        // for ( int j=0; j<25; j++)
        // {
        //     if ((path[j].row==-1)&&(path[j].column==-1))
        //     {
        //         break;
        //     }
        //     else
        //     {
        //         printf("(%d,%d) ",path[j].row,path[j].column);
        //     }
        // }
        // printf("\n");

        //change search coord to 4
        map[pos.row][pos.column] = 4;

        //Search around coord for zeroes and add them to search array.
        //if 3 found, add its coords to the path and break loop
        if (pos.column + 1 < MAP_W)
        {
            if (map[pos.row][pos.column + 1] == 0)
            {
                //add to search array
                search[add].row = pos.row;
                search[add].column = pos.column + 1;
                //++ counters
                add++;
                remove++;
                zerofind++;
            }
            else if (map[pos.row][pos.column + 1] == 3)
            {
                path[path_index].row = pos.row;
                path[path_index].column = pos.column + 1;
                path_index++;
                break;
            }
        }

        if (pos.row + 1 < MAP_H)
        {
            if (map[pos.row + 1][pos.column] == 0)
            {
                //add to search array
                search[add].row = pos.row + 1;
                search[add].column = pos.column;
                //++ counters
                add++;
                remove++;
                zerofind++;
            }
            else if (map[pos.row + 1][pos.column] == 3)
            {
                path[path_index].row = pos.row + 1;
                path[path_index].column = pos.column;
                path_index++;
                break;
            }
        }

        if (pos.column - 1 > -1)
        {
            if (map[pos.row][pos.column - 1] == 0)
            {
                //add to search array
                search[add].row = pos.row;
                search[add].column = pos.column - 1;
                //++ counters
                add++;
                remove++;
                zerofind++;
            }
            else if (map[pos.row][pos.column - 1] == 3)
            {
                path[path_index].row = pos.row;
                path[path_index].column = pos.column - 1;
                path_index++;
                break;
            }
        }

        if (pos.row - 1 > -1)
        {
            if (map[pos.row - 1][pos.column] == 0)
            {
                //add to search array
                search[add].row = pos.row - 1;
                search[add].column = pos.column;
                //++ counters
                add++;
                remove++;
                zerofind++;
            }
            else if (map[pos.row - 1][pos.column] == 3)
            {
                path[path_index].row = pos.row - 1;
                path[path_index].column = pos.column;
                path_index++;
                break;
            }
        }
        //if two or more zeroes found, add the path index to the branches array.
        if (zerofind > 1)
        {
            branches[branch_index] = path_index - 1;
            branch_index++;
        }

        //if no zeroes found, remove entries from the path back to the last branch point
        if (zerofind == 0)
        {
            while(1)
            {
                //printf("branch: %d, path: %d\n",branch_index,path_index); //Debug
                //trim back to branch point
                while ((branches[branch_index-1]) < (path_index -1))
                {
                    path[path_index-1].row = -1;
                    path[path_index-1].column = -1;
                    path_index--;
                }
                // printf("Break1\n"); //Debug
                // printf("branch: %d, path: %d\n",branch_index,path_index); //Debug
                // printf("Bool: %d\n",((path[path_index-1].column+1 < MAP_W) //Debug
                //         && (map[path[path_index-1].row][path[path_index-1].column+1]==0))
                //     ||
                //     ((path[path_index-1].row+1 < MAP_H)
                //         && (map[path[path_index-1].row+1][path[path_index-1].column]==0))
                //     ||
                //     ((path[path_index-1].column-1 > -1)
                //         && (map[path[path_index-1].row][path[path_index-1].column-1]==0))
                //     ||
                //     ((path[path_index-1].row-1 > -1)
                //         && (map[path[path_index-1].row-1][path[path_index-1].column]==0)));
                //if any coord both inside the map and adjacent to the branch point is zero break the loop. Else, trim from branch list and repeat pruning.
                if(
                    ((path[path_index-1].column+1 < MAP_W)
                        && (map[path[path_index-1].row][path[path_index-1].column+1]==0))
                    ||
                    ((path[path_index-1].row+1 < MAP_H)
                        && (map[path[path_index-1].row+1][path[path_index-1].column]==0))
                    ||
                    ((path[path_index-1].column-1 > -1)
                        && (map[path[path_index-1].row][path[path_index-1].column-1]==0))
                    ||
                    ((path[path_index-1].row-1 > -1)
                        && (map[path[path_index-1].row-1][path[path_index-1].column]==0))
                    )
                {
                    break;
                }
                else
                {
                    branches[branch_index-1] = -1;
                    branch_index--;
                }
            }
        }
        zerofind = 0;
        //issue here, I want to remove the branch and go back to the previous branch if there are no more viable paths from this point, but if I add it into the search array it will add coords to the search array that were already there. Need to do a separte check then.
    }

    //send path to finishing function
    finishPath(map, path);

    //Free memory
    free(path);
    free(search);
    free(branches);
}



void bf_search(int **map)
{
    //
}

coordinate findStart(int **map)
{
    coordinate result;
    for(int i=0; i<MAP_H; i++) //Each Row
    {
        for(int j=0; j<MAP_W; j++) //Each Column
        {
            if (map[i][j] == 2)
            {
                result.row = i;
                result.column = j;
                return result;
            }
        }
    }
}

void finishPath(int **map, coordinate *path)
{
    for (int i=0; i<25; i++)
    {
        if ((path[i].row == -1)||(path[i].column == -1))
            break;
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
resolve out of bounds searching issue

*/
