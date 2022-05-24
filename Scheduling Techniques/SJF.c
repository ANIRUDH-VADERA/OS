#include <stdio.h>

int burst_min(int burst[], int temp_arr[], int temp_idx)
{
    int i, min_burs = temp_arr[0];
    for (i = 0; i < temp_idx; i++)
    {
        if (burst[temp_arr[i]] < burst[min_burs])
        {
            min_burs = temp_arr[i];
        }
    }
    return min_burs;
}

int burst_total(int already_exec[], int exec_idx, int burst[])
{
    int x, sum = 0;
    for (x = 0; x < exec_idx; x++)
    {
        sum = sum + burst[already_exec[x]];
    }
    return sum;
}

void set_next(int n, int arrival[], int burst[], int *temp_arr, int *temp_idx, int already_exec[], int exec_idx, int flag[])
{
    int x;
    for (x = 0; x < n; x++)
    {
        if (flag[x] != 1)
        {
            if (arrival[x] <= burst_total(already_exec, exec_idx, burst))
            {
                *(temp_arr + *temp_idx) = x;
                *temp_idx = *temp_idx + 1;
            }
        }
    }
}

int main()
{
    int n, i, arrival[100], burst[100], min, already_exec[100], exec_idx = 0, flag[100], total, sum1 = 0, sum2 = 0, turn[100], waiting[100], temp_arr[100], temp_idx = 0;
    float average_wait, average_turn;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arrival[i]);
    }
    for (i = 0; i < n; i++)
    {
        scanf("%d", &burst[i]);
    }
    min = 0;
    for (i = 0; i < n; i++)
    {
        if (arrival[i] < arrival[min])
        {
            min = i;
        }
    }
    for (i = 0; i < n; i++)
    {
        if (arrival[i] == arrival[min])
        {
            temp_arr[temp_idx++] = i;
        }
    }
    min = temp_arr[0];
    for (i = 0; i < temp_idx; i++)
    {
        if (burst[temp_arr[i]] < burst[min])
        {
            min = temp_arr[i];
        }
    }
    temp_idx = 0;
    waiting[min] = 0;
    flag[min] = 1;
    already_exec[exec_idx++] = min;
    int min_2 = min;
    while (exec_idx < n)
    {
        set_next(n, arrival, burst, &temp_arr[0], &temp_idx, already_exec, exec_idx, flag);
        min = burst_min(burst, temp_arr, temp_idx);
        waiting[min] = burst_total(already_exec, exec_idx, burst);
        flag[min] = 1;
        already_exec[exec_idx++] = min;
        temp_idx = 0;
    }
    for (i = 0; i < n; i++)
    {
        waiting[i] = waiting[i] - arrival[i] + arrival[min_2];
    }
    for (i = 0; i < n; i++)
    {
        sum1 = sum1 + waiting[i];
    }
    average_wait = (float)sum1 / n;
    for (i = 0; i < n; i++)
    {
        turn[i] = burst[i] + waiting[i];
    }
    for (i = 0; i < n; i++)
    {
        sum2 = sum2 + turn[i];
    }
    printf("waiting = [ ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", waiting[i]);
    }
    printf("]\n");
    printf("already exec = [ ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", already_exec[i]);
    }
    printf("]\n");
    average_turn = (float)sum2 / n;
    printf("%.2f %.2f", average_wait, average_turn);
    return 0;
}