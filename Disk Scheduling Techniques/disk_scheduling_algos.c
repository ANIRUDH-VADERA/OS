#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int find_fcfs(int no_of_request, int *requestString, int init)
{
    int head_movements = 0;
    int temp = -1;
    for (int i = 0; i < no_of_request; i++)
    {
        if (temp == -1)
        {
            if (requestString[i] > init)
            {
                head_movements += requestString[i] - init;
                printf("Subtracting %d - %d : \n", requestString[i], init);
                temp = requestString[i];
            }
            else
            {
                head_movements += init - requestString[i];
                printf("Subtracting %d - %d : \n", init, requestString[i]);
                temp = requestString[i];
            }
        }
        else
        {
            if (requestString[i] > temp)
            {
                head_movements += requestString[i] - temp;
                printf("Subtracting %d - %d : \n", requestString[i], temp);
                temp = requestString[i];
            }
            else
            {
                head_movements += temp - requestString[i];
                printf("Subtracting %d - %d : \n", temp, requestString[i]);
                temp = requestString[i];
            }
        }
    }
    free(requestString);
    return head_movements;
}

int find_sstf(int no_of_request, int *requestString, int init)
{
    int head_movements = 0;
    int temp = init;
    int min_dis_idx;
    for (int i = 0; i < no_of_request - 1; i++)
    {
        min_dis_idx = i;
        for (int j = i + 1; j < no_of_request; j++)
        {
            if (abs(requestString[min_dis_idx] - temp) >= abs(requestString[j] - temp))
            {
                min_dis_idx = j;
            }
        }
        head_movements += abs(requestString[min_dis_idx] - temp);
        temp = requestString[min_dis_idx];
        if (min_dis_idx != i)
        {
            int temp1 = requestString[min_dis_idx];
            requestString[min_dis_idx] = requestString[i];
            requestString[i] = temp1;
        }
    }
    head_movements += abs(requestString[no_of_request - 1] - temp);
    printf("Modifies=[ ");
    for (int i = 0; i < no_of_request; i++)
    {
        printf("%d ", requestString[i]);
    }
    printf("]\n");
    free(requestString);
    return head_movements;
}

int find_scan(int no_of_request, int *requestString, int init, int max_c, int dir)
{
    int head_movements = 0;
    int min_dis_idx;
    int *scanOrder;
    scanOrder = (int *)calloc(no_of_request + 2, sizeof(int));
    int scanOrd_idx = 0;
    for (int i = 0; i < no_of_request - 1; i++)
    {
        min_dis_idx = i;
        for (int j = i + 1; j < no_of_request; j++)
        {
            if (requestString[min_dis_idx] >= requestString[j])
            {
                min_dis_idx = j;
            }
        }
        if (min_dis_idx != i)
        {
            int temp = requestString[min_dis_idx];
            requestString[min_dis_idx] = requestString[i];
            requestString[i] = temp;
        }
    }
    if (dir == 1)
    {
        scanOrder[scanOrd_idx++] = init;
        for (int i = no_of_request - 1; i >= 0; i--)
        {
            if (requestString[i] < init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
        scanOrder[scanOrd_idx++] = 0;
        for (int i = 0; i < no_of_request; i++)
        {
            if (requestString[i] >= init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
    }
    else
    {
        scanOrder[scanOrd_idx++] = init;
        for (int i = 0; i < no_of_request; i++)
        {
            if (requestString[i] >= init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
        scanOrder[scanOrd_idx++] = max_c;
        for (int i = no_of_request - 1; i >= 0; i--)
        {
            if (requestString[i] < init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
    }
    for (int i = 0; i < scanOrd_idx - 1; i++)
    {
        head_movements += abs(scanOrder[i + 1] - scanOrder[i]);
    }
    printf("Modifies=[ ");
    for (int i = 0; i < scanOrd_idx; i++)
    {
        printf("%d ", scanOrder[i]);
    }
    printf("]\n");
    free(scanOrder);
    free(requestString);
    return head_movements;
}

int find_look(int no_of_request, int *requestString, int init, int dir)
{
    int head_movements = 0;
    int min_dis_idx;
    int *scanOrder;
    scanOrder = (int *)calloc(no_of_request + 1, sizeof(int));
    int scanOrd_idx = 0;
    for (int i = 0; i < no_of_request - 1; i++)
    {
        min_dis_idx = i;
        for (int j = i + 1; j < no_of_request; j++)
        {
            if (requestString[min_dis_idx] >= requestString[j])
            {
                min_dis_idx = j;
            }
        }
        if (min_dis_idx != i)
        {
            int temp = requestString[min_dis_idx];
            requestString[min_dis_idx] = requestString[i];
            requestString[i] = temp;
        }
    }
    if (dir == 1)
    {
        scanOrder[scanOrd_idx++] = init;
        for (int i = no_of_request - 1; i >= 0; i--)
        {
            if (requestString[i] < init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
        for (int i = 0; i < no_of_request; i++)
        {
            if (requestString[i] >= init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
    }
    else
    {
        scanOrder[scanOrd_idx++] = init;
        for (int i = 0; i < no_of_request; i++)
        {
            if (requestString[i] >= init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
        for (int i = no_of_request - 1; i >= 0; i--)
        {
            if (requestString[i] < init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
    }
    for (int i = 0; i < scanOrd_idx - 1; i++)
    {
        head_movements += abs(scanOrder[i + 1] - scanOrder[i]);
    }
    printf("Modifies=[ ");
    for (int i = 0; i < scanOrd_idx; i++)
    {
        printf("%d ", scanOrder[i]);
    }
    printf("]\n");
    free(scanOrder);
    free(requestString);
    return head_movements;
}

int find_c_scan(int no_of_request, int *requestString, int init, int max_c, int dir)
{
    int head_movements = 0;
    int min_dis_idx;
    int *scanOrder;
    scanOrder = (int *)calloc(no_of_request + 3, sizeof(int));
    int scanOrd_idx = 0;
    for (int i = 0; i < no_of_request - 1; i++)
    {
        min_dis_idx = i;
        for (int j = i + 1; j < no_of_request; j++)
        {
            if (requestString[min_dis_idx] >= requestString[j])
            {
                min_dis_idx = j;
            }
        }
        if (min_dis_idx != i)
        {
            int temp = requestString[min_dis_idx];
            requestString[min_dis_idx] = requestString[i];
            requestString[i] = temp;
        }
    }
    if (dir == 1)
    {
        scanOrder[scanOrd_idx++] = init;
        for (int i = no_of_request - 1; i >= 0; i--)
        {
            if (requestString[i] < init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
        scanOrder[scanOrd_idx++] = 0;
        scanOrder[scanOrd_idx++] = max_c;
        for (int i = no_of_request - 1; i >= 0; i--)
        {
            if (requestString[i] >= init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
    }
    else
    {
        scanOrder[scanOrd_idx++] = init;
        for (int i = 0; i < no_of_request; i++)
        {
            if (requestString[i] >= init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
        scanOrder[scanOrd_idx++] = max_c;
        scanOrder[scanOrd_idx++] = 0;
        for (int i = 0; i < no_of_request; i++)
        {
            if (requestString[i] < init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
    }
    for (int i = 0; i < scanOrd_idx - 1; i++)
    {
        head_movements += abs(scanOrder[i + 1] - scanOrder[i]);
    }
    printf("Modifies=[ ");
    for (int i = 0; i < scanOrd_idx; i++)
    {
        printf("%d ", scanOrder[i]);
    }
    printf("]\n");
    free(scanOrder);
    free(requestString);
    return head_movements;
}

int find_c_look(int no_of_request, int *requestString, int init, int dir)
{
    int head_movements = 0;
    int min_dis_idx;
    int *scanOrder;
    scanOrder = (int *)calloc(no_of_request + 1, sizeof(int));
    int scanOrd_idx = 0;
    for (int i = 0; i < no_of_request - 1; i++)
    {
        min_dis_idx = i;
        for (int j = i + 1; j < no_of_request; j++)
        {
            if (requestString[min_dis_idx] >= requestString[j])
            {
                min_dis_idx = j;
            }
        }
        if (min_dis_idx != i)
        {
            int temp = requestString[min_dis_idx];
            requestString[min_dis_idx] = requestString[i];
            requestString[i] = temp;
        }
    }
    if (dir == 1)
    {
        scanOrder[scanOrd_idx++] = init;
        for (int i = no_of_request - 1; i >= 0; i--)
        {
            if (requestString[i] < init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
        for (int i = no_of_request - 1; i >= 0; i--)
        {
            if (requestString[i] >= init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
    }
    else
    {
        scanOrder[scanOrd_idx++] = init;
        for (int i = 0; i < no_of_request; i++)
        {
            if (requestString[i] >= init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
        for (int i = 0; i < no_of_request; i++)
        {
            if (requestString[i] < init)
            {
                scanOrder[scanOrd_idx++] = requestString[i];
            }
        }
    }
    for (int i = 0; i < scanOrd_idx - 1; i++)
    {
        head_movements += abs(scanOrder[i + 1] - scanOrder[i]);
    }
    printf("Modifies=[ ");
    for (int i = 0; i < scanOrd_idx; i++)
    {
        printf("%d ", scanOrder[i]);
    }
    printf("]\n");
    free(scanOrder);
    free(requestString);
    return head_movements;
}

int main()
{
    int algo;
    printf("Selct the required algorithm :\n");
    printf("FCFS : 1\n");
    printf("SSTF : 2\n");
    printf("SCAN : 3\n");
    printf("LOOK : 4\n");
    printf("C-SCAN : 5\n");
    printf("C-LOOK : 6\n");
    scanf("%d", &algo);

    int max_c;
    printf("Enter the max cylinders : \n");
    scanf("%d", &max_c);

    int init;
    printf("Enter the initial position of the read_write head : \n");
    scanf("%d", &init);

    int no_of_request;
    printf("Enter the number of incoming requests : \n");
    scanf("%d", &no_of_request);

    printf("Enter the request string : \n");
    int *requestString;
    requestString = (int *)calloc(no_of_request, sizeof(int));
    for (int i = 0; i < no_of_request; i++)
    {
        scanf("%d", &requestString[i]);
    }
    int head_movements;
    int dir = -1;
    switch (algo)
    {
    case 1:
        head_movements = find_fcfs(no_of_request, requestString, init);
        printf("The total number of head movements is : %d", head_movements);
        break;
    case 2:
        head_movements = find_sstf(no_of_request, requestString, init);
        printf("The total number of head movements is : %d", head_movements);
        break;
    case 3:
        printf("Enter the direction : \n");
        printf("Left : 1\n");
        printf("Right : 2\n");
        scanf("%d", &dir);
        head_movements = find_scan(no_of_request, requestString, init, max_c - 1, dir);
        printf("The total number of head movements is : %d", head_movements);
        break;
    case 4:
        printf("Enter the direction : \n");
        printf("Left : 1\n");
        printf("Right : 2\n");
        scanf("%d", &dir);
        head_movements = find_look(no_of_request, requestString, init, dir);
        printf("The total number of head movements is : %d", head_movements);
        break;
    case 5:
        printf("Enter the direction : \n");
        printf("Left : 1\n");
        printf("Right : 2\n");
        scanf("%d", &dir);
        head_movements = find_c_scan(no_of_request, requestString, init, max_c - 1, dir);
        printf("The total number of head movements is : %d", head_movements);
        break;
    case 6:
        printf("Enter the direction : \n");
        printf("Left : 1\n");
        printf("Right : 2\n");
        scanf("%d", &dir);
        head_movements = find_c_look(no_of_request, requestString, init, dir);
        printf("The total number of head movements is : %d", head_movements);
        break;
    default:
        break;
    }
    return 0;
}