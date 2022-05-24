#include <stdio.h>

int min_send(int n, int arrival[], int flag[])
{
    int x, i, f = 0;
    for (x = 0; x < n; x++)
    {
        if (f == 0)
        {
            i = x;
            f = 1;
        }
        else
        {
            if (arrival[x] < arrival[i])
            {
                i = x;
            }
        }
    }
    return i;
}

int burst_ocur(int already_exec[], int exec_idx, int burst[])
{
    int total = 0, x;
    for (x = 0; x < exec_idx; x++)
    {
        total = total + burst[already_exec[x]];
    }
    return total;
}

void set_next(int n, int arrival[], int burst[], int *temp_arr, int *temp_idx, int already_exec[], int exec_idx, int flag[])
{
    int x;
    for (x = 0; x < n; x++)
    {
        if (flag[x] != 1)
        {
            if (arrival[x] <= burst_ocur(already_exec, exec_idx, burst))
            {
                *(temp_arr + *temp_idx) = x;
                *temp_idx = *temp_idx + 1;
            }
        }
    }
}

int set_next_idx(int temp_idx, int temp_arr[], int prio[])
{
    int x, min = temp_arr[0], f = 0;
    for (x = 0; x < temp_idx; x++)
    {
        if (prio[temp_arr[x]] < prio[min])
        {
            min = temp_arr[x];
        }
    }
    return min;
}

int main()
{
    int n, arrival[100], prio[100], burst[100], i, waiting[100], turn[100], min, temp_arr[100], temp_idx = 0, already_exec[100], exec_idx = 0, idx, sum1 = 0, sum2 = 0, turn_around[100], flag[100];
    float average_wait = 0, average_turn = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arrival[i]);
    }
    for (i = 0; i < n; i++)
    {
        scanf("%d", &prio[i]);
    }
    for (i = 0; i < n; i++)
    {
        scanf("%d", &burst[i]);
    }
    min = 0;
    min = min_send(n, arrival, flag);
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
        if (prio[temp_arr[i]] < prio[min])
        {
            min = temp_arr[i];
        }
    }
    waiting[min] = 0;
    already_exec[exec_idx++] = min;
    flag[min] = 1;
    temp_idx = 0;
    while (exec_idx < n)
    {
        set_next(n, arrival, burst, &temp_arr[0], &temp_idx, already_exec, exec_idx, flag);
        idx = set_next_idx(temp_idx, temp_arr, prio);
        waiting[idx] = burst_ocur(already_exec, exec_idx, burst);
        flag[idx] = 1;
        already_exec[exec_idx++] = idx;
        temp_idx = 0;
    }
    for (i = 0; i < n; i++)
    {
        waiting[i] = waiting[i] - arrival[i];
    }

    for (i = 0; i < n; i++)
    {
        sum1 = sum1 + waiting[i];
    }
    average_wait = (float)sum1 / n;
    for (i = 0; i < n; i++)
    {
        turn_around[i] = burst[i] + waiting[i];
    }
    for (i = 0; i < n; i++)
    {
        sum2 = sum2 + turn_around[i];
    }
    average_turn = (float)sum2 / n;
    printf("%.2f %.2f", average_wait, average_turn);
    printf("\nwaiting = [ ");
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
    return 0;
}