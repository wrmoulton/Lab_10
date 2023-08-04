#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct TrieNode
{
    struct TrieNode* children[26];
    int flag;
};

// Inserts the word to the trie structure
void insert(struct TrieNode *pTrie, char *word)
{
    struct TrieNode *tmp = pTrie;
    int size = strlen(word);
    for (int i = 0; i < size; i++)
    {
        int index = word[i] - 'a';
        if (tmp->children[index] == NULL)
        {
            tmp->children[index] = (struct TrieNode *)malloc(sizeof(struct TrieNode));
            for (int j = 0; j < 26; j++)
            {
                tmp->children[index]->children[j] = NULL;
            }
            tmp->children[index]->flag = 0;
        }
        tmp = tmp->children[index];
    }
    tmp->flag++;
}

// computes the number of occurrences of the word
int numberOfOccurrences(struct TrieNode *pTrie, char *word)
{
    struct TrieNode *tmp = pTrie;
    int size = strlen(word);
    for (int i = 0; i < size; i++)
    {
        int index = word[i] - 'a';
        if (tmp->children[index] == NULL)
        {
            return 0; // Word not found, so the occurrence is zero.
        }
        tmp = tmp->children[index];
    }
    return tmp->flag;
}

// deallocate the trie structure
// deallocate the trie structure
struct TrieNode *deallocateTrie(struct TrieNode *pTrie)
{
    if (pTrie == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < 26; i++)
    {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}


// Initializes a trie structure
struct TrieNode *createTrie()
{
    struct TrieNode *root = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    for (int i = 0; i < 26; i++)
    {
        root->children[i] = NULL;
    }
    root->flag = 0;
    return root;
}


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    if (filename == NULL)
        return -1;

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return -1;
    }

    int size = 0;
    fscanf(file, "%d", &size);
    
    for (int i = 0; i < size; i++)
    {
        pInWords[i] = (char *)malloc(256 * sizeof(char)); // Assuming a maximum word length of 255 characters
        fscanf(file, "%s", pInWords[i]);
    }

    fclose(file);
    return size;
}

int main(void)
{
    char *inWords[256];
    
    // read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }
    
    struct TrieNode *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }

    // parse line-by-line, and insert each word into the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");

    
    return 0;
}





