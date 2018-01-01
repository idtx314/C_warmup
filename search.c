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
    int map[5][5] = {{1,1,1,1,0},{0,2,0,0,0},{0,1,1,1,1},{0,1,1,3,1},{0,0,0,0,0}};

    printMap(map);

    return 0;
}

