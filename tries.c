#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
  char letter;
  int count;
  struct Trie *pChildren[26];
};

void insert(struct Trie *pTrie, char *word)
{
  struct Trie *p = pTrie;
  int i = 0;
  while (word[i] != '\0')
  {
    if (p->pChildren[word[i] - 'a'] == NULL)
    {
      struct Trie *newNode = (struct Trie *)malloc(sizeof(struct Trie));
      newNode->letter = word[i];
      newNode->count = 0;
      for (int j = 0; j < 26; j++)
      {
        newNode->pChildren[j] = NULL;
      }
      p->pChildren[word[i] - 'a'] = newNode;
    }
    p = p->pChildren[word[i] - 'a'];
    i++;
  }
  if (word[i] == '\0')
  {
    p->count++;
  }
}


// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
  struct Trie *p = pTrie;
  int i = 0;
  while (word[i] != '\0')
  {
    if (p->pChildren[word[i] - 'a'] == NULL)
    {
      return 0;
    }
    p = p->pChildren[word[i] - 'a'];
    i++;
  }
  return p->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
  struct Trie *p = pTrie;
  for (int i = 0; i < 26; i++)
  {
    if (p->pChildren[i] != NULL)
    {
      deallocateTrie(p->pChildren[i]);
    }
  }
  free(p);
  return NULL;
}

struct Trie *createTrie()
{
  struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
  pTrie->letter = '\0';
  pTrie->count = 0;
  for (int i = 0; i < 26; i++)
  {
    pTrie->pChildren[i] = NULL;
  }
  return pTrie;
}

int readDictionary(char *filename, char **pInWords)
{
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Error in opening the file %s\n", filename);
    return 0;
  }
  char line[256];
  int numWords = 0;
  while (fgets(line, sizeof(line), fp) != NULL)
  {
    line[strlen(line) - 1] = '\0';
    pInWords[numWords] = (char *)malloc(sizeof(char) * (strlen(line) + 1));
    strcpy(pInWords[numWords], line);
    numWords++;
  }
  fclose(fp);
  return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}