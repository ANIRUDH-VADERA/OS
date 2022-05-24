#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int seq_allocate(int *disk, int start, int len, int file_no)
{
    int flag = 0;
    int free_slots = 0;
    for (int i = start; i < (start + len); i++)
    {
        if (disk[i] != 0)
        {
            flag = 1;
        }
    }
    if (flag != 1)
    {
        for (int i = start; i < (start + len); i++)
        {
            disk[i] = file_no;
        }
    }
    for (int i = 0; i < 100; i++)
    {
        if (disk[i] == 0)
        {
            free_slots++;
        }
    }
    printf("Free Slots : %d\n", free_slots);
    return flag;
}

int linked_list_allocate(int **disk, int start, int len, int file_no)
{
    int flag = 0;
    int free_slots = 0;
    for (int i = 0; i < 100; i++)
    {
        if (disk[i][0] == 0)
        {
            free_slots++;
        }
    }
    if (len <= free_slots && disk[start][0] == 0)
    {
        int count = 0;
        int temp;
        int random_slot;
        while (count < len)
        {
            if (count > 0)
            {
                random_slot = rand() % 100;
            }
            else
            {
                random_slot = start;
                temp = random_slot;
            }
            if (disk[random_slot][0] == 0)
            {
                if (count > 0)
                {
                    disk[temp][1] = random_slot;
                    temp = random_slot;
                }
                count++;
                disk[random_slot][0] = file_no;
            }
        }
    }
    else
    {
        flag = 1;
    }
    free_slots = 0;
    for (int i = 0; i < 100; i++)
    {
        if (disk[i][0] == 0)
        {
            free_slots++;
        }
    }
    printf("Free Slots : %d\n", free_slots);
    return flag;
}

int indexed_allocate(int **disk, int start, int len, int file_no, int index_slot)
{
    if (index_slot == start)
    {
        return 1;
    }
    int flag = 0;
    int free_slots = 0;
    for (int i = 0; i < 100; i++)
    {
        if (disk[i][1] == 0)
        {
            free_slots++;
        }
    }
    if (len <= free_slots && disk[start][1] == 0 && disk[index_slot][1] == 0)
    {
        int count = 0;
        int random_slot;
        disk[index_slot][0] = 1; // As its a index slot
        disk[index_slot][1] = file_no;
        int index_slot_idx = 2;
        int block_no = 1;
        while (count < len)
        {
            if (count > 0)
            {
                random_slot = rand() % 100;
            }
            else
            {
                random_slot = start;
            }
            if (disk[random_slot][1] == 0)
            {
                disk[random_slot][1] = file_no;
                disk[random_slot][2] = block_no;
                disk[index_slot][index_slot_idx++] = random_slot;
                block_no++;
                count++;
            }
        }
    }
    else
    {
        flag = 1;
    }
    free_slots = 0;
    for (int i = 0; i < 100; i++)
    {
        if (disk[i][1] == 0)
        {
            free_slots++;
        }
    }
    printf("Free Slots : %d\n", free_slots);
    return flag;
}

int main()
{
    srand(time(NULL));
    printf("Select the file allocation technique : \n");
    printf("1 : Sequential File Allocation\n");
    printf("2 : Linked List File Allocation\n");
    printf("3 : Indexed File Allocation\n");
    int technique, start, len, check, go = 1;
    scanf("%d", &technique);
    int file_no = 1;
    // Disks
    int *disk1; // For sequential
    disk1 = (int *)calloc(100, sizeof(int));
    for (int i = 0; i < 100; i++)
    {
        disk1[i] = 0;
    }
    int **disk2; // For Linked Lists
    disk2 = (int **)calloc(100, sizeof(int *));
    for (int i = 0; i < 100; i++)
    {
        disk2[i] = (int *)calloc(2, sizeof(int));
        disk2[i][0] = 0;
        disk2[i][1] = -1;
    }

    int **disk3; // For Indexed
    disk3 = (int **)calloc(100, sizeof(int *));
    for (int i = 0; i < 100; i++)
    {
        disk3[i] = (int *)calloc(100, sizeof(int));
        disk3[i][0] = 0;
        disk3[i][1] = 0;
    }
    int index;
    // disk3[i][0] --> means its a storage for file
    // disk3[i][1] --> means its a storage for index
    while (go == 1)
    {
        printf("Enter the starting Block:\n");
        scanf("%d", &start);
        printf("Enter the length of the files:\n");
        scanf("%d", &len);
        check = -1;
        switch (technique)
        {
        case 1:
            check = seq_allocate(disk1, start, len, file_no);
            if (check == 1)
            {
                printf("File Not Allocated to the Disk: \n");
                printf("Do you want to enter more files : \n");
                printf("1 : Yes\n");
                printf("2 : No\n");
                scanf("%d", &go);
            }
            else
            {
                for (int i = start; i < (start + len); i++)
                {
                    printf("Slot No : %d :: Fill Flag(File No) : %d\n", i, disk1[i]);
                }
                printf("The File is Allocated to the Disk : \n");
                file_no++;
                printf("Do you want to enter more files : \n");
                printf("1 : Yes\n");
                printf("2 : No\n");
                scanf("%d", &go);
            }
            break;
        case 2:
            check = linked_list_allocate(disk2, start, len, file_no);
            if (check == 1)
            {
                printf("File Not Allocated to the Disk: \n");
                printf("Do you want to enter more files : \n");
                printf("1 : Yes\n");
                printf("2 : No\n");
                scanf("%d", &go);
            }
            else
            {
                int flag = 0;
                int temp = start;
                for (int i = start; i < (start + len); i++)
                {
                    if (flag == 0)
                    {
                        printf("Slot No : %d :: Fill Flag(File No) : %d :: Next Slot(Next File) : %d\n", temp, disk2[temp][0], disk2[temp][1]);
                        temp = disk2[temp][1];
                        flag = 1;
                    }
                    else
                    {
                        printf("Slot No : %d :: Fill Flag(File No) : %d :: Next Slot(Next File) : %d\n", temp, disk2[temp][0], disk2[temp][1]);
                        temp = disk2[temp][1];
                    }
                }
                printf("The File is Allocated to the Disk : \n");
                file_no++;
                printf("Do you want to enter more files : \n");
                printf("1 : Yes\n");
                printf("2 : No\n");
                scanf("%d", &go);
            }
            break;
        case 3:
            printf("Enter the block/slot for the index : \n");
            scanf("%d", &index);
            check = indexed_allocate(disk3, start, len, file_no, index);
            if (check == 1)
            {
                printf("File Not Allocated to the Disk: \n");
                printf("Do you want to enter more files : \n");
                printf("1 : Yes\n");
                printf("2 : No\n");
                scanf("%d", &go);
            }
            else
            {
                int flag = 0;
                int temp = start;
                printf("The Index is : \n");
                for (int i = 0; i < len; i++)
                {
                    printf("Block_No : %d :: Indexed at : %d \n", i + 1, disk3[index][i + 2]);
                }
                for (int i = 0; i < len; i++)
                {
                    if (flag == 0)
                    {
                        printf("Slot No : %d :: Fill Flag(File No) : %d :: Block_No : %d \n", temp, disk3[temp][1], disk3[temp][2]);
                        flag = 1;
                    }
                    else
                    {
                        temp = disk3[index][2 + i];
                        printf("Slot No : %d :: Fill Flag(File No) : %d :: Block_No : %d \n", temp, disk3[temp][1], disk3[temp][2]);
                        temp = disk3[temp][1];
                    }
                }
                printf("The File is Allocated to the Disk : \n");
                file_no++;
                printf("Do you want to enter more files : \n");
                printf("1 : Yes\n");
                printf("2 : No\n");
                scanf("%d", &go);
            }
            break;

        default:
            break;
        }
    }
    free(disk1);
    for (int i = 0; i < 100; i++)
    {
        free(disk2[i]);
    }
    free(disk2);
    return 0;
}