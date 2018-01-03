#include <stdio.h>


void main()
{
    {
    for (int i=0; i<10; i++)
    {
        if(i > -1)
        {
            printf("%d",i);
            if (i>5)
            {
                break;
            }
        }
    }
    }
}
