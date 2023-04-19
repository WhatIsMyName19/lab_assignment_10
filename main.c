#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie
{
    int occurrences;
    struct Trie* next[26];
};

struct Trie* init()
{
    struct Trie* newTrie = calloc(1, sizeof(struct Trie));

    return newTrie;
}

void insert(struct Trie** ppTrie, char* word)
{
    int length = strlen(word);

    struct Trie** temp = ppTrie;

    for (int i = 0; i < length; i++)
    {
        temp = &(*temp)->next[word[i] - 'a'];

        if (*temp == NULL)
            *temp = init();
    }

    (*temp)->occurrences++;
}

int numberOfOccurances(struct Trie* pTrie, char* word)
{
    int length = strlen(word);

    struct Trie* temp = pTrie;

    for (int i = 0; i < length; i++)
    {
        temp = temp->next[word[i] - 'a'];

        if (temp == NULL)
            return 0;
    }

    return temp->occurrences;
}

void dealloc(struct Trie* pTrie)
{
    for (int i = 0; i < 26; i++)
    {
        if (pTrie->next[i] != NULL)
            dealloc(pTrie->next[i]);
    }

    free(pTrie);
}

struct Trie* deallocateTrie(struct Trie* pTrie)
{
    // Have to use recursion, but since we have a return type I have to do it this way.
    dealloc(pTrie);

    pTrie = NULL;

    return pTrie;
}

int main(void)
{
    //read the number of the words in the dictionary
    //parse line  by line, and insert each word to the trie data structure
    char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };

    struct Trie *trie = init();

    for (int i = 0;i < 5;i++)
    {
        insert(&trie, pWords[i]);
    }

    for (int i = 0;i < 5;i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    // The line below these comments was modified. It was impossible to do this with the required method signatures.
    // This line and the one below require trie to be a pointer, 
    // but pass in a double pointer to the methods that want a single pointer. This also happens on line 83.
    // There is also a typo here :)
    trie = deallocateTrie(trie);

    if (trie != NULL)
        printf("There is an error in this program\n");

    return 0;
}