#include <stdio.h>
#include <math.h>

int burst_total(int already_exec[], int exec_idx, int burst[], int total_remaining_time)
{
    int x, sum = 0;
    for (x = 0; x < exec_idx; x++)
    {
        sum += burst[already_exec[x]];
    }
    return sum + total_remaining_time;
}

void set_next(int n, int arrival[], int already_exec[], int exec_idx, int burst[], int flag[], int total_remaining_time, int *temp_arr, int *temp_idx, int f, int lrpi, int *temp_flag)
{
    int i, j, temp_arr2[100], temp_idx2 = 0, min_idx, temp;
    for (i = 0; i < n; i++)
    {
        if (flag[i] != 1 && *(temp_flag + i) != 1)
        {
            if (arrival[i] <= burst_total(already_exec, exec_idx, burst, total_remaining_time))
            {
                *(temp_flag + i) = 1;
                temp_arr2[temp_idx2++] = i;
            }
        }
    }
    for (i = 0; i < (temp_idx2 - 1); i++)
    {
        min_idx = i;
        for (j = i + 1; j < temp_idx2; j++)
        {
            if (arrival[temp_arr2[min_idx]] > arrival[temp_arr2[j]])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            temp = temp_arr2[min_idx];
            temp_arr2[min_idx] = temp_arr2[i];
            temp_arr2[i] = temp;
        }
    }
    for (i = 0; i < temp_idx2; i++)
    {
        *(temp_arr + *temp_idx) = temp_arr2[i];
        *temp_idx = *temp_idx + 1;
    }
    temp_idx2 = 0;
    if (f == 1)
    {
        *(temp_flag + lrpi) = 1;
        *(temp_arr + *temp_idx) = lrpi;
        *temp_idx = *temp_idx + 1;
    }
}

void modify(int n, int arrival[], int *temp_arr, int *temp_idx, int f, int lrpi, int *temp_flag, int already_exec[], int exec_idx, int total_remaining_time, int flag[], int burst[])
{
    int i, j, temp_arr2[100], temp_idx2 = 0, min_idx, temp;
    ;
    for (i = 0; i < n; i++)
    {
        if (*(temp_flag + i) != 1 && flag[i] != 1)
        {
            if (arrival[i] <= burst_total(already_exec, exec_idx, burst, total_remaining_time))
            {
                *(temp_flag + i) = 1;
                temp_arr2[temp_idx2++] = i;
            }
        }
    }
    for (i = 0; i < (temp_idx2 - 1); i++)
    {
        min_idx = i;
        for (j = i + 1; j < temp_idx2; j++)
        {
            if (arrival[temp_arr2[min_idx]] > arrival[temp_arr2[j]])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            temp = temp_arr2[min_idx];
            temp_arr2[min_idx] = temp_arr2[i];
            temp_arr2[i] = temp;
        }
    }
    for (i = 0; i < temp_idx2; i++)
    {
        *(temp_arr + *temp_idx) = temp_arr2[i];
        *temp_idx = *temp_idx + 1;
    }
    temp_idx2 = 0;
    if (f == 1)
    {
        *(temp_flag + lrpi) = 1;
        *(temp_arr + *temp_idx) = lrpi;
        *temp_idx = *temp_idx + 1;
    }
}

int main()
{
    int i, n, tq, arrival[100], burst[100], min = 0, temp_arr[100], temp_idx = 0, already_exec[100], exec_idx = 0, flag[100], total_remaining_time = 0, f = 0, lrpi = 0, st_idx = 0, m = 0, temp_flag[100], waiting[100], sum = 0;
    int turn_around[100];
    int sum2 = 0;
    int burst2[100];
    float average_turnaround_time = 0;
    float average_wait = 0;
    scanf("%d", &n);
    scanf("%d", &tq);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arrival[i]);
    }
    for (i = 0; i < n; i++)
    {
        scanf("%d", &burst[i]);
    }
    for (i = 0; i < n; i++)
    {
        burst2[i] = burst[i];
    }
    for (i = 0; i < n; i++)
    {
        waiting[i] = 0;
    }
    min = 0;
    for (i = 0; i < n; i++)
    {
        if (arrival[i] < arrival[min])
        {
            min = i;
        }
    }
    printf("min=%d\n", min);
    total_remaining_time += arrival[min];
    if (burst[min] <= tq)
    {
        already_exec[exec_idx++] = min;
        flag[min] = 1;
        lrpi = min;
        waiting[min] += 0;
    }
    else
    {
        total_remaining_time += tq;
        burst[min] -= tq;
        f = 1;
        lrpi = min;
        waiting[min] -= tq;
    }
    temp_flag[min] = 1;
    while (exec_idx < n)
    {
        if (m == 0)
        {
            set_next(n, arrival, already_exec, exec_idx, burst, flag, total_remaining_time, &temp_arr[0], &temp_idx, f, lrpi, &temp_flag[0]);
            printf("temp=[ ");
            for (i = st_idx; i < temp_idx; i++)
            {
                printf("%d ", temp_arr[i]);
            }
            printf(" ]\n");
            m = 1;
            f = 0;
        }
        else
        {
            modify(n, arrival, &temp_arr[0], &temp_idx, f, lrpi, &temp_flag[0], already_exec, exec_idx, total_remaining_time, flag, burst);
            printf("temp1=[ ");
            for (i = st_idx; i < temp_idx; i++)
            {
                printf("%d ", temp_arr[i]);
            }
            printf(" ]\n");
            if (burst[temp_arr[st_idx]] <= tq)
            {
                waiting[temp_arr[st_idx]] += burst_total(already_exec, exec_idx, burst, total_remaining_time);
                already_exec[exec_idx++] = temp_arr[st_idx];
                flag[temp_arr[st_idx]] = 1;
                lrpi = temp_arr[st_idx];
                f = 0;
                st_idx++;
            }
            else
            {
                total_remaining_time += tq;
                waiting[temp_arr[st_idx]] -= tq;
                burst[temp_arr[st_idx]] -= tq;
                f = 1;
                lrpi = temp_arr[st_idx];
                st_idx++;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        waiting[i] -= arrival[i];
    }
    for (i = 0; i < n; i++)
    {
        if (waiting[i] < 0)
        {
            waiting[i] = 0;
        }
    }
    for (i = 0; i < n; i++)
    {
        turn_around[i] = burst2[i] + waiting[i];
    }
    for (i = 0; i < n; i++)
    {
        sum2 = sum2 + turn_around[i];
    }
    average_turnaround_time = (float)sum2 / n;
    for (i = 0; i < n; i++)
    {
        sum += waiting[i];
    }
    printf("waiting=[ ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", waiting[i]);
    }
    printf(" ]\n");
    printf("already_exec=[ ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", already_exec[i]);
    }
    printf(" ]\n");
    average_wait = (float)sum / n;
    printf("%.2f\n", average_wait);
    printf("%.2f\n", average_turnaround_time);
    return 0;
}
