#include <stdio.h>

int burst_min(int burst[], int temp_arr[], int temp_idx)
{
    int x, min_burs = temp_arr[0];
    for (x = 0; x < temp_idx; x++)
    {
        if (burst[temp_arr[x]] < burst[min_burs])
        {
            min_burs = temp_arr[x];
        }
    }
    return min_burs;
}

int burst_total(int already_exec[], int exec_idx, int burst[], int total_remaining_time)
{
    int x, sum = 0;
    for (x = 0; x < exec_idx; x++)
    {
        sum = sum + burst[already_exec[x]];
    }
    return sum + total_remaining_time;
}

void set_next(int n, int arrival[], int burst[], int *temp_arr, int *temp_idx, int already_exec[], int exec_idx, int flag[], int total_remaining_time)
{
    int x;
    for (x = 0; x < n; x++)
    {
        if (flag[x] != 1)
        {
            if (arrival[x] <= burst_total(already_exec, exec_idx, burst, total_remaining_time))
            {
                *(temp_arr + *temp_idx) = x;
                *temp_idx = *temp_idx + 1;
            }
        }
    }
}

void real_set_next(int n, int arrival[], int burst[], int *temp_arr, int *temp_idx, int already_exec[], int exec_idx, int flag[], int min, int total_remaining_time)
{
    int x, y, f = 0;
    for (x = 0; x < n; x++)
    {
        if (flag[x] != 1)
        {
            for (y = 0; y < *temp_idx; y++)
            {
                if (*(temp_arr + y) == x)
                {
                    f = 1;
                }
            }
            if (f == 0)
            {
                if (arrival[x] <= (burst_total(already_exec, exec_idx, burst, total_remaining_time) + burst[min]))
                {
                    *(temp_arr + *temp_idx) = x;
                    *temp_idx = *temp_idx + 1;
                }
            }
            else
            {
                f = 0;
            }
        }
    }
}

int main()
{
    int n, i, m = 0, arrival[100], burst[100], min, already_exec[100], exec_idx = 0, flag[100], temp_arr[100], temp_idx = 0, real_min, waiting[100], sum1 = 0, remaining_time = 0, total_remaining_time = 0, temp_arr2[100], temp_idx2 = 0, f = 0, k = 0, j = 0, temp = 0;
    float average_wait;
    scanf("%d", &n);
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
    for (i = 0; i < n; i++)
    {
        if (arrival[i] == arrival[min] || arrival[i] <= burst[min])
        {
            temp_arr[temp_idx++] = i;
        }
    }
    real_min = temp_arr[0];
    for (i = 0; i < temp_idx; i++)
    {
        if (burst[temp_arr[i]] < burst[real_min])
        {
            real_min = temp_arr[i];
        }
    }
    f = burst[min];
    if (real_min != min)
    {
        for (i = arrival[min] + 1; i < arrival[real_min] + 1; i++)
        {
            for (m = 0; m < temp_idx; m++)
            {
                if (arrival[temp_arr[m]] == i && burst[temp_arr[m]] < f)
                {
                    if (k == 0)
                    {
                        burst[min] -= (arrival[temp_arr[m]] - burst_total(already_exec, exec_idx, burst, total_remaining_time));
                        waiting[min] -= arrival[temp_arr[m]] - burst_total(already_exec, exec_idx, burst, total_remaining_time);
                        total_remaining_time += arrival[temp_arr[m]] - burst_total(already_exec, exec_idx, burst, total_remaining_time);
                        temp = temp_arr[m];
                        f = burst[temp_arr[m]];
                        k = 1;
                    }
                    else
                    {
                        burst[temp] -= (arrival[temp_arr[m]] - burst_total(already_exec, exec_idx, burst, total_remaining_time));
                        waiting[temp] -= arrival[temp_arr[m]] - burst_total(already_exec, exec_idx, burst, total_remaining_time);
                        total_remaining_time += arrival[temp_arr[m]] - burst_total(already_exec, exec_idx, burst, total_remaining_time);
                        temp = temp_arr[m];
                        f = burst[temp_arr[m]];
                    }
                }
            }
        }
        temp = 0;
        f = 0;
        k = 0;
        waiting[real_min] += 0;
        flag[real_min] = 1;
        already_exec[exec_idx++] = real_min;
        temp_idx = 0;
    }
    else
    {
        waiting[real_min] += 0;
        flag[real_min] = 1;
        already_exec[exec_idx++] = real_min;
        temp_idx = 0;
    }
    while (exec_idx < n)
    {
        set_next(n, arrival, burst, &temp_arr[0], &temp_idx, already_exec, exec_idx, flag, total_remaining_time);
        min = burst_min(burst, temp_arr, temp_idx);
        real_set_next(n, arrival, burst, &temp_arr[0], &temp_idx, already_exec, exec_idx, flag, min, total_remaining_time);
        real_min = burst_min(burst, temp_arr, temp_idx);
        f = burst[min];
        if (real_min != min)
        {
            for (i = arrival[min] + 1; i < arrival[real_min] + 1; i++)
            {
                for (m = 0; m < temp_idx; m++)
                {
                    if (arrival[temp_arr[m]] == i && burst[temp_arr[m]] < f)
                    {
                        if (k == 0)
                        {
                            burst[min] -= (arrival[temp_arr[m]] - burst_total(already_exec, exec_idx, burst, total_remaining_time));
                            waiting[min] -= arrival[temp_arr[m]] - burst_total(already_exec, exec_idx, burst, total_remaining_time);
                            total_remaining_time += arrival[temp_arr[m]] - burst_total(already_exec, exec_idx, burst, total_remaining_time);
                            temp = temp_arr[m];
                            f = burst[temp_arr[m]];
                            k = 1;
                        }
                        else
                        {
                            burst[temp] -= (arrival[temp_arr[m]] - burst_total(already_exec, exec_idx, burst, total_remaining_time));
                            waiting[temp] -= arrival[temp_arr[m]] - burst_total(already_exec, exec_idx, burst, total_remaining_time);
                            total_remaining_time += arrival[temp_arr[m]] - burst_total(already_exec, exec_idx, burst, total_remaining_time);
                            temp = temp_arr[m];
                            f = burst[temp_arr[m]];
                        }
                    }
                }
            }
            temp = 0;
            f = 0;
            k = 0;
            waiting[real_min] += burst_total(already_exec, exec_idx, burst, total_remaining_time);
            flag[real_min] = 1;
            already_exec[exec_idx++] = real_min;
            temp_idx = 0;
            temp_idx2 = 0;
        }
        else
        {
            waiting[real_min] += burst_total(already_exec, exec_idx, burst, total_remaining_time);
            temp_idx2 = 0;
            flag[real_min] = 1;
            already_exec[exec_idx++] = real_min;
            temp_idx = 0;
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
        sum1 = sum1 + waiting[i];
    }
    average_wait = (float)sum1 / n;
    printf("%.2f", average_wait);
    return 0;
}
