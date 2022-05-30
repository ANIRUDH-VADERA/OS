#include <stdio.h>

int findbest(int blockSize[100], int i, int processSize[100], int b, int allocated[100])
{
    int min = -1;
    int c = 0;
    for (int j = 0; j < b; j++)
    {
        if (allocated[j] != 1)
        {
            if (processSize[i] <= blockSize[j])
            {
                if (c == 0)
                {
                    min = j;
                    c++;
                }
                if ((blockSize[j] - processSize[i]) < (blockSize[min] - processSize[i]))
                {
                    min = j;
                }
            }
        }
    }
    return min;
}

int findworst(int blockSize[100], int i, int processSize[100], int b, int allocated[100])
{
    int max = -1;
    int c = 0;
    for (int j = 0; j < b; j++)
    {
        if (allocated[j] != 1)
        {
            if (processSize[i] <= blockSize[j])
            {
                if (c == 0)
                {
                    max = j;
                    c++;
                }
                if ((blockSize[j] - processSize[i]) > (blockSize[max] - processSize[i]))
                {
                    max = j;
                }
            }
        }
    }
    return max;
}

int findfirst(int blockSize[100], int i, int processSize[100], int b, int allocated[100])
{
    for (int j = 0; j < b; j++)
    {
        if (allocated[j] != 1)
        {
            if (processSize[i] <= blockSize[j])
            {
                return j;
            }
        }
    }
    return -1;
}

int main()
{
    int n, b;
    printf("Enter the no of Processes:\n");
    scanf("%d", &n);
    printf("Enter the no of Blocks:\n");
    scanf("%d", &b);
    int blockSize[100];
    int processSize[100];
    printf("Enter the process sizes\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter the process size for %d process:", i + 1);
        scanf("%d", &processSize[i]);
    }
    printf("Enter the block sizes\n");
    for (int i = 0; i < b; i++)
    {
        printf("Enter the block size for %d block:", i + 1);
        scanf("%d", &blockSize[i]);
    }
    printf("According to which Algo:\n");
    printf("1:Best Fit\n");
    printf("2:First Fit\n");
    printf("3:Worst Fit\n");
    int algo = 0;
    scanf("%d", &algo);
    int allocated[100];
    for (int i = 0; i < b; i++)
    {
        allocated[i] = 0;
    }
    int blockallocated[100];
    int free_idx;
    for (int i = 0; i < n; i++)
    {
        blockallocated[i] = -1;
    }
    if (algo == 1)
    {
        for (int i = 0; i < n; i++)
        {
            free_idx = findbest(blockSize, i, processSize, b, allocated);
            if (free_idx != -1)
            {
                allocated[free_idx] = 1;
                blockallocated[i] = free_idx + 1;
            }
        }
    }
    else if (algo == 2)
    {
        for (int i = 0; i < n; i++)
        {
            free_idx = findfirst(blockSize, i, processSize, b, allocated);
            if (free_idx != -1)
            {
                allocated[free_idx] = 1;
                blockallocated[i] = free_idx + 1;
            }
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            free_idx = findworst(blockSize, i, processSize, b, allocated);
            if (free_idx != -1)
            {
                allocated[free_idx] = 1;
                blockallocated[i] = free_idx + 1;
            }
        }
    }

    printf("blockallocated=[ ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", blockallocated[i]);
    }
    printf("]\n");
    printf("allocated=[ ");
    for (int i = 0; i < b; i++)
    {
        printf("%d ", allocated[i]);
    }
    printf("]\n");
    return 0;
}