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

int burst_ocur(int already_exec[], int exec_idx, int burst[], int remaining_time)
{
    int total = 0, x;
    for (x = 0; x < exec_idx; x++)
    {
        total = total + burst[already_exec[x]];
    }
    return total + remaining_time;
}

void set_next(int n, int arrival[], int burst[], int *temp_arr, int *temp_idx, int already_exec[], int exec_idx, int flag[], int total_remaining_time)
{
    int x;
    for (x = 0; x < n; x++)
    {
        if (flag[x] != 1)
        {
            if (arrival[x] <= burst_ocur(already_exec, exec_idx, burst, total_remaining_time))
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
                if (arrival[x] <= (burst_ocur(already_exec, exec_idx, burst, total_remaining_time) + burst[min]))
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
    int n, m, f = 0, temp = 0, k = 0, arrival[100], prio[100], burst[100], i, waiting[100], turn[100], min, temp_arr[100], temp_idx = 0, already_exec[100], exec_idx = 0, idx, sum1 = 0, sum2 = 0, turn_around[100], flag[100], real_min = 0, total_remaining_time = 0, temp_idx2 = 0, temp_arr2[100];
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
        if (prio[temp_arr[i]] < prio[real_min])
        {
            real_min = temp_arr[i];
        }
    }
    f = prio[min];
    if (real_min != min)
    {
        for (i = arrival[min] + 1; i < arrival[real_min] + 1; i++)
        {
            for (m = 0; m < temp_idx; m++)
            {
                if (arrival[temp_arr[m]] == i && prio[temp_arr[m]] < f)
                {
                    if (k == 0)
                    {
                        burst[min] = burst[min] - (arrival[temp_arr[m]] - burst_ocur(already_exec, exec_idx, burst, total_remaining_time));
                        waiting[min] -= arrival[temp_arr[m]] - burst_ocur(already_exec, exec_idx, burst, total_remaining_time);
                        total_remaining_time += arrival[temp_arr[m]] - burst_ocur(already_exec, exec_idx, burst, total_remaining_time);
                        temp = temp_arr[m];
                        f = prio[temp_arr[m]];
                        k = 1;
                    }
                    else
                    {
                        burst[temp] = burst[temp] - (arrival[temp_arr[m]] - burst_ocur(already_exec, exec_idx, burst, total_remaining_time));
                        waiting[temp] -= arrival[temp_arr[m]] - burst_ocur(already_exec, exec_idx, burst, total_remaining_time);
                        total_remaining_time += arrival[temp_arr[m]] - burst_ocur(already_exec, exec_idx, burst, total_remaining_time);
                        temp = temp_arr[m];
                        f = prio[temp_arr[m]];
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
        min = set_next_idx(temp_idx, temp_arr, prio);
        real_set_next(n, arrival, burst, &temp_arr[0], &temp_idx, already_exec, exec_idx, flag, min, total_remaining_time);
        real_min = set_next_idx(temp_idx, temp_arr, prio);
        f = prio[min];
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
                            burst[min] = burst[min] - (arrival[temp_arr[m]] - burst_ocur(already_exec, exec_idx, burst, total_remaining_time));
                            waiting[min] -= arrival[temp_arr[m]] - burst_ocur(already_exec, exec_idx, burst, total_remaining_time);
                            total_remaining_time += arrival[temp_arr[m]] - burst_ocur(already_exec, exec_idx, burst, total_remaining_time);
                            temp = temp_arr[m];
                            f = prio[temp_arr[m]];
                            k = 1;
                        }
                        else
                        {
                            burst[temp] = burst[temp] - (arrival[temp_arr[m]] - burst_ocur(already_exec, exec_idx, burst, total_remaining_time));
                            waiting[temp] -= arrival[temp_arr[m]] - burst_ocur(already_exec, exec_idx, burst, total_remaining_time);
                            total_remaining_time += arrival[temp_arr[m]] - burst_ocur(already_exec, exec_idx, burst, total_remaining_time);
                            temp = temp_arr[m];
                            f = prio[temp_arr[m]];
                        }
                    }
                }
            }
            temp = 0;
            f = 0;
            k = 0;
            waiting[real_min] += burst_ocur(already_exec, exec_idx, burst, total_remaining_time);
            temp_idx2 = 0;
            flag[real_min] = 1;
            already_exec[exec_idx++] = real_min;
            temp_idx = 0;
        }
        else
        {
            waiting[real_min] += burst_ocur(already_exec, exec_idx, burst, total_remaining_time);
            temp_idx2 = 0;
            flag[real_min] = 1;
            already_exec[exec_idx++] = real_min;
            temp_idx = 0;
        }
    }
    printf("already_exec=[");
    for (i = 0; i < n; i++)
    {
        printf("%d ", already_exec[i]);
    }
    printf("]\n");
    for (i = 0; i < n; i++)
    {
        waiting[i] = waiting[i] - arrival[i];
    }
    printf("waiting=[");
    for (i = 0; i < n; i++)
    {
        printf("%d ", waiting[i]);
    }
    printf("]\n");
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

    return 0;
}