
#include <stdio.h>
#include <string.h>

#define SIZE 11
#define MAX 20

struct Patient
{
    char id[10];
    char date[15];
    char time[10];
    float glucose;
    float pH;
    char protein[15];
};

struct Patient patients[] =
{
    {"H101", "2026-11-01", "09:00", 110, 6.0, "Negative"},
    {"H102", "2026-11-01", "09:15", 125, 6.5, "Trace"},
    {"H103", "2026-11-01", "09:30", 138, 5.5, "Negative"},
    {"H104", "2026-11-01", "09:45", 152, 6.0, "Positive"},
    {"H105", "2026-11-01", "10:00", 168, 7.0, "Trace"},
    {"H110", "2026-11-01", "10:15", 120, 6.5, "Negative"}
};

int n = 6;

/* HASH TABLE */
int hashTable[SIZE];

/* SORTED ARRAY */
struct Patient sorted[MAX];
int sortedReady = 0;

/* CIRCULAR QUEUE */
int queue[MAX];
int front = 0;
int rear = -1;
int count = 0;

/* DISPLAY PATIENT */
void displayPatient(int i)
{
    printf("\nPatient ID : %s", patients[i].id);
    printf("\nDate       : %s", patients[i].date);
    printf("\nTime       : %s", patients[i].time);
    printf("\nGlucose    : %.2f", patients[i].glucose);
    printf("\npH         : %.2f", patients[i].pH);
    printf("\nProtein    : %s\n", patients[i].protein);
}

/* HASH FUNCTION */
int hashFunction(char id[])
{
    int sum = 0;
    int i;

    for(i = 0; id[i] != '\0'; i++)
    {
        if(id[i] >= '0' && id[i] <= '9')
            sum += id[i] - '0';
    }

    return sum % SIZE;
}

/* INITIALIZE HASH TABLE */
void initializeHash()
{
    int i, index;

    for(i = 0; i < SIZE; i++)
        hashTable[i] = -1;

    printf("\nCreating Hash Table...\n");

    for(i = 0; i < n; i++)
    {
        index = hashFunction(patients[i].id);

        while(hashTable[index] != -1)
        {
            printf("Collision detected for %s\n",
                   patients[i].id);

            index = (index + 1) % SIZE;
        }

        hashTable[index] = i;
    }

    printf("Hash Table created successfully!\n");
}

/* SEARCH PATIENT USING HASH TABLE */
int searchHash(char id[])
{
    int index = hashFunction(id);
    int start = index;
    int i;

    for(i = 0; i < SIZE; i++)
    {
        if(hashTable[index] == -1)
            return -1;

        if(strcmp(patients[hashTable[index]].id, id) == 0)
            return hashTable[index];

        index = (index + 1) % SIZE;

        if(index == start)
            break;
    }

    return -1;
}

/* HASH TABLE MENU */
void hashMenu()
{
    int choice, result;
    char id[10];

    do
    {
        printf("\n----- HASH TABLE MENU -----\n");
        printf("1. Search Patient\n");
        printf("2. Display Hash Table\n");
        printf("3. Back\n");
        printf("Enter choice: ");

        if(scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            while(getchar() != '\n');
            continue;
        }

        switch(choice)
        {
            case 1:
                printf("Enter Patient ID: ");
                scanf("%9s", id);

                result = searchHash(id);

                if(result == -1)
                    printf("Patient not found!\n");
                else
                {
                    printf("\nPatient Found!\n");
                    displayPatient(result);
                }
                break;

            case 2:
                printf("\nIndex\tPatient ID\n");

                for(int i = 0; i < SIZE; i++)
                {
                    if(hashTable[i] == -1)
                        printf("%d\tEmpty\n", i);
                    else
                        printf("%d\t%s\n", i,
                               patients[hashTable[i]].id);
                }
                break;

            case 3:
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 3);
}

/* CONVERT TIME INTO MINUTES */
int getMinutes(char time[])
{
    int h, m;

    sscanf(time, "%d:%d", &h, &m);

    return h * 60 + m;
}

/* CREATE SORTED ARRAY */
void createSortedArray()
{
    int i, j;
    struct Patient key;

    for(i = 0; i < n; i++)
        sorted[i] = patients[i];

    /* INSERTION SORT */
    for(i = 1; i < n; i++)
    {
        key = sorted[i];
        j = i - 1;

        while(j >= 0 &&
              getMinutes(sorted[j].time) >
              getMinutes(key.time))
        {
            sorted[j + 1] = sorted[j];
            j--;
        }

        sorted[j + 1] = key;
    }

    sortedReady = 1;

    printf("\nRecords sorted successfully!\n");
}

/* DISPLAY SORTED ARRAY */
void displaySorted()
{
    int i;

    if(!sortedReady)
    {
        printf("\nPlease sort records first!\n");
        return;
    }

    printf("\nPatient ID\tTime\tGlucose\n");

    for(i = 0; i < n; i++)
    {
        printf("%s\t\t%s\t%.2f\n",
               sorted[i].id,
               sorted[i].time,
               sorted[i].glucose);
    }
}

/* BINARY SEARCH */
void binarySearch()
{
    char time[10];
    int low = 0, high = n - 1;
    int mid, target;

    if(!sortedReady)
    {
        printf("\nPlease sort records first!\n");
        return;
    }

    printf("Enter time to search (HH:MM): ");
    scanf("%9s", time);

    target = getMinutes(time);

    while(low <= high)
    {
        mid = (low + high) / 2;

        if(getMinutes(sorted[mid].time) == target)
        {
            printf("\nRecord Found!\n");
            printf("Patient ID: %s\n", sorted[mid].id);
            printf("Time: %s\n", sorted[mid].time);
            printf("Glucose: %.2f\n", sorted[mid].glucose);
            printf("pH: %.2f\n", sorted[mid].pH);
            printf("Protein: %s\n", sorted[mid].protein);
            return;
        }

        if(target < getMinutes(sorted[mid].time))
            high = mid - 1;
        else
            low = mid + 1;
    }

    printf("\nRecord not found!\n");
}

/* SORTED ARRAY MENU */
void sortedMenu()
{
    int choice;

    do
    {
        printf("\n----- SORTED ARRAY MENU -----\n");
        printf("1. Sort Records\n");
        printf("2. Display Sorted Records\n");
        printf("3. Search by Time\n");
        printf("4. Back\n");
        printf("Enter choice: ");

        if(scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            while(getchar() != '\n');
            continue;
        }

        switch(choice)
        {
            case 1:
                createSortedArray();
                break;

            case 2:
                displaySorted();
                break;

            case 3:
                binarySearch();
                break;

            case 4:
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 4);
}

/* ENQUEUE */
void enqueue()
{
    char id[10];
    int index;

    if(count == MAX)
    {
        printf("\nQueue is full!\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%9s", id);

    index = searchHash(id);

    if(index == -1)
    {
        printf("Patient not found!\n");
        return;
    }

    rear = (rear + 1) % MAX;
    queue[rear] = index;
    count++;

    printf("Patient %s added to queue!\n", id);
}

/* DEQUEUE */
void dequeue()
{
    int index;

    if(count == 0)
    {
        printf("\nQueue is empty!\n");
        return;
    }

    index = queue[front];

    printf("\nProcessing Patient:\n");
    displayPatient(index);

    front = (front + 1) % MAX;
    count--;

    printf("Patient processed successfully!\n");
}

/* DISPLAY QUEUE */
void displayQueue()
{
    int i, index;

    if(count == 0)
    {
        printf("\nQueue is empty!\n");
        return;
    }

    printf("\nFRONT -> ");

    for(i = 0; i < count; i++)
    {
        index = (front + i) % MAX;

        printf("%s", patients[queue[index]].id);

        if(i != count - 1)
            printf(" -> ");
    }

    printf(" -> REAR\n");
}

/* QUEUE MENU */
void queueMenu()
{
    int choice;

    do
    {
        printf("\n----- QUEUE MENU -----\n");
        printf("1. Add Patient (Enqueue)\n");
        printf("2. Process Patient (Dequeue)\n");
        printf("3. Display Queue\n");
        printf("4. Back\n");
        printf("Enter choice: ");

        if(scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            while(getchar() != '\n');
            continue;
        }

        switch(choice)
        {
            case 1:
                enqueue();
                break;

            case 2:
                dequeue();
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 4);
}

/* DISPLAY ALL RECORDS */
void displayAll()
{
    int i;

    for(i = 0; i < n; i++)
        displayPatient(i);
}

/* MAIN FUNCTION */
int main()
{
    int choice;

    initializeHash();

    do
    {
        printf("\n====================================\n");
        printf("     URINE TEST RECORD MANAGER\n");
        printf("====================================\n");

        printf("1. Display All Patient Records\n");
        printf("2. Hash Table Operations\n");
        printf("3. Sorted Array Operations\n");
        printf("4. Queue Operations\n");
        printf("5. Exit\n");

        printf("Enter choice: ");

        if(scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Enter a number.\n");
            while(getchar() != '\n');
            continue;
        }

        switch(choice)
        {
            case 1:
                displayAll();
                break;

            case 2:
                hashMenu();
                break;

            case 3:
                sortedMenu();
                break;

            case 4:
                queueMenu();
                break;

            case 5:
                printf("\nThank you for using the system!\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while(choice != 5);

    printf("\nPress ENTER to close the program...");
    getchar();
    getchar();

    return 0;
}

