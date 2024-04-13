#include <stdio.h>
#include <stdlib.h> // Include this for malloc, free, and exit

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
};

// HashType
struct HashType
{
    struct RecordType* record;
    int occupied; // Flag to indicate if the index is occupied
};

// Compute the hash function
int hash(int x, int hashSz)
{
    return x % hashSz; // Simple modulo hash function for demonstration purposes
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType* pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }
        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
void displayRecordsInHash(struct HashType* pHashArray, int hashSz)
{
    int i;

    printf("\nHash Table:\n");
    for (i = 0; i < hashSz; ++i)
    {
        if (pHashArray[i].occupied)
        {
            printf("Index %d -> %d %c %d\n", i, pHashArray[i].record->id, pHashArray[i].record->name, pHashArray[i].record->order);
        }
    }
    printf("\n");
}

int main(void)
{
    struct RecordType* pRecords;
    struct HashType* pHashTable;
    int recordSz = 0;
    int hashSz = 10; // Size of the hash table, you can adjust this according to your needs

    recordSz = parseData("input_lab_9.txt", &pRecords); //had to switch file to match input file name
    printRecords(pRecords, recordSz);

    // Allocate memory for the hash table
    pHashTable = (struct HashType*)malloc(sizeof(struct HashType) * hashSz);
    if (pHashTable == NULL)
    {
        printf("Cannot allocate memory for hash table\n");
        exit(-1);
    }

    // Initialize the hash table
    for (int i = 0; i < hashSz; ++i)
    {
        pHashTable[i].occupied = 0; // Initialize all indices as unoccupied
    }

    // Insert records into the hash table
    for (int i = 0; i < recordSz; ++i)
    {
        int index = hash(pRecords[i].id, hashSz);
        pHashTable[index].record = &pRecords[i];
        pHashTable[index].occupied = 1;
    }

    // Display records in the hash table
    displayRecordsInHash(pHashTable, hashSz);

    // Free allocated memory
    free(pRecords);
    free(pHashTable);

    return 0;
}
