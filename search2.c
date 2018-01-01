#include <stdio.h>

#define MAP_W 5
#define MAP_H 5


//void printMap(int **map);

void printMap(int arr[5][5])
{
    for (int i=0; i<MAP_H; i++) //each row
    {
        for (int j=0; j<MAP_W; j++) //each column
        {
            printf("%d",arr[i][j]);
        }
        printf("\n");
    }
}


int main()
{
    int **map;
    int row1[5] = {1,1,1,1,0};
    map[0]=row1;
    // map = (int **)malloc(100);

    // *map = (int *){1,1,1,1,0};
    // *(map+1) = (int *){0,2,0,0,0};
    // *(map+2) = (int *){0,1,1,1,1};
    // *(map+3) = (int *){0,1,1,3,1};
    // *(map+4) = (int *){0,0,0,0,0};

    printf("%d",**map);


    //printMap(map);

    return 0;
}

