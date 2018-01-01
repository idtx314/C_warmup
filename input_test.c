#include <stdio.h>


int main()
{
    int input = 0;
    char c;

    for (int i=0; i<5; i++)
    {
        scanf("%d",&input);
        printf("%d\n",input);
    }

    while ((c = getchar()) != '\n' && c != EOF)
    {}
    return 0;
}
