#include <stdio.h>
int main()
{
    int n, waiting_time[50], burst_time[50], i, sum1 = 0, sum2 = 0, turn_around[50], arrival_time[50];
    float average_waiting_time = 0, average_turnaround_time = 0;
    int temp_array[50];
    int temp_idx = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arrival_time[i]);
    }
    for (i = 0; i < n; i++)
    {
        scanf("%d", &burst_time[i]);
    }
    int min_idx = 0;
    for (int i = 0; i < n; i++)
    {
        temp_array[temp_idx++] = i;
    }
    for (int i = 0; i < (n - 1); i++)
    {
        min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arrival_time[min_idx] > arrival_time[j])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            int temp = temp_array[i];
            temp_array[i] = temp_array[min_idx];
            temp_array[min_idx] = temp;
        }
    }

    waiting_time[temp_array[0]] = arrival_time[temp_array[0]];
    for (i = 1; i < n; i++)
    {
        waiting_time[temp_array[i]] = waiting_time[temp_array[i - 1]] + burst_time[temp_array[i - 1]];
    }
    for (i = 1; i < n; i++)
    {
        waiting_time[temp_array[i]] = waiting_time[temp_array[i]] - arrival_time[temp_array[i]];
    }
    for (i = 0; i < n; i++)
    {
        sum1 = sum1 + waiting_time[i];
    }
    average_waiting_time = (float)sum1 / n;
    for (i = 0; i < n; i++)
    {
        turn_around[i] = burst_time[i] + waiting_time[i];
    }
    for (i = 0; i < n; i++)
    {
        sum2 = sum2 + turn_around[i];
    }
    average_turnaround_time = (float)sum2 / n;
    printf("%.2f ", average_turnaround_time);
    printf("%.2f", average_waiting_time);
    return 0;
}