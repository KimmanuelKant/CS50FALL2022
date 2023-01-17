// Implements a dictionary's functionality
#define _GNU_SOURCE
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 5000;
int wordCount = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Check if the key exists in table
    int hashedIndex = hash(word);
    if (!table[hashedIndex])
    {
        return false;
    }

    // if key exists, compare values
    if (strcasecmp(table[hashedIndex]->word, word) == 0)
    {
        return true;
    }

    // If node value is not found in the first node, itterate through next pointers.
    // And check for match.
    node *checkNode = table[hashedIndex];
    while (checkNode)
    {
        if (strcasecmp(checkNode->word, word) == 0)
        {
            return true;
        }
        checkNode = checkNode->next;
    }
    return false;
}

unsigned int hash(const char *key)
{

    unsigned int sum = 2;
    int index = 0;

    while (key[index] != '\0')
    {
        // if (index % 2 == 0)
        sum *= tolower(key[index]);
        index++;
    }
    return sum % N;
}

// Insert new element in to hash table. (Written by Kim - not CS50 ORGINAL)
void insert(char *key)
{

    node *newWord;
    newWord = malloc(sizeof(node));

    strncpy(newWord->word, key, LENGTH);

    newWord->next = table[hash(key)];
    table[hash(key)] = newWord;

    wordCount++;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *fp;
    fp = fopen(dictionary, "r");

    if (fp == NULL)
    {
        return false;
    }

    // Get each word in dictionary, with correct null character and everything.
    char c;
    char word[LENGTH + 1];
    int index = 0;
    while (fread(&c, sizeof(char), 1, fp))
    {

        if (isalpha(c) || (c == '\'' && index > 0))
        {
            word[index] = c;
            index++;
        }
        else
        {
            word[index] = '\0';
            insert(word);
            index = 0;
        }
    }

    fclose(fp);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}
void save_to_file()
{
    FILE *fp = fopen("tablefile.txt", "w+");
    int nodeSum = 0;
    int avg[N];

    char *biggestBucket;
    int biggestChain = 0;

    for (int i = 0; i < N; i++)
    {
        if (!table[i])
        {
            fprintf(fp, "      ... \n");
            continue;
        }

        fprintf(fp, "(%d) %s ", i, table[i]->word);
        node *nextNode = table[i];
        while (nextNode)
        {
            nodeSum++;
            nextNode = nextNode->next;
        }
        fprintf(fp, "(%d) \n", nodeSum);

        if (nodeSum > biggestChain)
        {
            biggestBucket = table[i]->word;
            biggestChain = nodeSum;
        }

        avg[i] = nodeSum;
        nodeSum = 0;
    }

    // Get avg
    int avgSum = 0;
    for (int i = 0; i < N; i++)
    {
        avgSum += avg[i];
    }

    float printAvg = (float)N / (float)avgSum;

    fprintf(fp, "\n ----- %s (%d) ----- \n", biggestBucket, biggestChain);
    fprintf(fp, "\n ----- avg chain (%f) ----- \n", printAvg);

    fclose(fp);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // save_to_file();
    for (int i = 0; i < N; i++)
    {
        if (table[i])
        {
            node *nextNode = table[i]->next;
            while (nextNode)
            {
                node *currentNode = nextNode;
                nextNode = nextNode->next;
                free(currentNode);
            }

            free(table[i]);
        }
    }

    return true;
}
