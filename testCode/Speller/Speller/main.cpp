/****************************************************************************
* Implements a spell-checker.
***************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


// default dictionary
#define DICTIONARY "C:/TC/BIN/large"

// Dictionary Functionality
#define LENGTH 45
/**
* Structure to store dictionary , following Trie pattern
*/
struct dict
{
	// to indicate end of word 
	short word;
	// 26 chars + 1 apostrophe
	struct dict* next[27];
};
unsigned int size(void);

// Declare dictionary 
struct dict* D = NULL;

// Keep track of words 
int words = 0;

/**
* Returns true if word is in dictionary else false.
*/
short check(const char* word)
{
	// Declare pointer to dictionary
	struct dict* Dptr = NULL;
	int loc;

	Dptr = D;
	// while end of word , i.e. go char by char
	while (*word != '\0')
	{
		// loc in Dptr->next[loc]
		loc = (tolower(*word) == '\'') ? 26 : (tolower(*word) - 'a');

		Dptr = Dptr->next[loc];
		if (Dptr == NULL)
		{
			return 0;
		}
		// increment word count
		word++;
	}
	// if word exists
	if (Dptr->word)
	{
		return 1;
	}
	// else
	return 0;
}
/**
* Loads dictionary into memory.  Returns 1 if successful else 0.
*/
short load(const char* dictionary)
{
	struct dict *temp;
	int loc, i, j;
	// Declare pointer to dictionary
	struct dict* Dptr = NULL;
	// used to store current word
	char word[50];
	char c;

	FILE* dictptr = NULL;
	dictptr = fopen(dictionary, "r");

	if (dictptr == NULL)
	{
		printf("Could not read %s", dictionary);
		return 1;
	}
	// Init D , use malloc coz else cant free D
	D = (struct dict*) malloc(sizeof(struct dict));
	D->word = 0;
	for (i = 0; i < 27; i++)
	{
		D->next[i] = NULL;
	}

	// while next word exists
	while (fscanf(dictptr, "%s", word) == 1)
	{
		// reset Dptr to rootNode
		Dptr = D;
		// used to count/point char
		i = 0;
		// read word char by char
		while (word[i] != '\0')
		{
			// used to store temperory character
			c = word[i];

			// used to calc next[loc]
			loc = (c == '\'') ? 26 : (c - 'a');

			// check if Dict next[char] is not initialized
			if (Dptr->next[loc] == NULL)
			{
				// Allocate memory for next node
				temp = (struct dict *) malloc(sizeof(struct dict));


				// confirm that allocation was successfull
				if (temp == NULL)
				{
					printf("Could not allocate memory for next dictionary node.Current word count is %d\n", size());
					return 1;
				}
				temp->word = 0;
				for (j = 0; j < 27; j++)
				{
					temp->next[j] = NULL;
				}

				Dptr->next[loc] = temp;
			}
			// increment i
			i++;
			// increment Dptr level
			Dptr = Dptr->next[loc];
		}
		// set Dptr->word to true to indicate that word exist
		Dptr->word = 1;
		printf("loaded %s\n", word);

		// increase words
		words++;
	}

	// all finished
	return 1;
}

/**
* Returns number of words in dictionary if loaded else 0 if not yet loaded.
*/
unsigned int size(void)
{
	return words;
}

/**
* Helper function to unload , recursive unload
*/
void unload_dict(struct dict * Dptr)
{
	int i;
	// check if each next[loc] is NULL , else free it recursively
	for (i = 0; i < 27; i++)
	{
		if (Dptr->next[i])
		{
			unload_dict(Dptr->next[i]);
			// not needed as it will be not checked again
			Dptr->next[i] = NULL;
		}
	}
	// once all next is freed , free current node
	free(Dptr);
}
/**
* Unloads dictionary from memory.  Returns true if successful else false.
*/
short unload(void)
{
	// check if dict exists , i.e. init'd
	struct dict * Dptr = D;
	if (Dptr)
	{
		// free each node
		unload_dict(Dptr);
		// reset word count
		words = 0;

		return 1;
	}
	// dont know when it will come here 
	return 0;
}
// End Dictionary Functionality

int main(int argc, char* argv[])
{
	char* dictionary;
	short loaded;
	char* text;
	FILE* fp;
	int index = 0, misspellings = 0, words = 0;
	char word[LENGTH + 1];
	int c;
	unsigned int n;

	// check for correct number of args
	if (argc != 2 && argc != 3)
	{
		printf("Usage: speller [dictionary] text\n");
		return 1;
	}


	// determine dictionary to use
	dictionary = (argc == 3) ? argv[1] : DICTIONARY;

	// load dictionary
	loaded = load(dictionary);

	// abort if dictionary not loaded
	if (!loaded)
	{
		printf("Could not load %s.\n", dictionary);
		return 1;
	}

	// try to open text
	text = (argc == 3) ? argv[2] : argv[1];
	fp = fopen(text, "r");
	if (fp == NULL)
	{
		printf("Could not open %s.\n", text);
		unload();
		return 1;
	}

	// prepare to report misspellings
	printf("\nMISSPELLED WORDS\n\n");

	// prepare to spell-check
	// spell-check each word in text
	for (c = fgetc(fp); c != EOF; c = fgetc(fp))
	{ 
		// allow only alphabetical characters and apostrophes
		if (isalpha(c) || (c == '\'' && index > 0))
		{
			// append character to word
			word[index] = c;
			index++;

			// ignore alphabetical strings too long to be words
			if (index > LENGTH)
			{
				// consume remainder of alphabetical string
				while ((c = fgetc(fp)) != EOF && isalpha(c));

				// prepare for new word
				index = 0;
			}
		}

		// ignore words with numbers (like MS Word can)
		else if (isdigit(c))
		{
			// consume remainder of alphanumeric string
			while ((c = fgetc(fp)) != EOF && isalnum(c));

			// prepare for new word
			index = 0;
		}

		// we must have found a whole word
		else if (index > 0)
		{
			// terminate current word
			word[index] = '\0';
			// update counter
			words++;

			// print word if misspelled
			if (!check(word))
			{
				printf("%s\n", word);
				misspellings++;
			}

			// prepare for next word
			index = 0;
		}
	}
	// We are on last word so check it
	word[index] = '\0';

	// update counter
	words++;

	// print word if misspelled
	if (!check(word))
	{
		printf("%s\n", word);
		misspellings++;
	}
	// checked last word

	// check whether there was an error
	if (ferror(fp))
	{
		fclose(fp);
		printf("Error reading %s.\n", text);
		unload();
		return 1;
	}

	// close text
	fclose(fp);

	// determine dictionary's size
	n = size();

	// abort if dictionary not unloaded
	if (!unload())
	{
		printf("Could not unload %s.\n", dictionary);
		return 1;
	}


	// report results
	printf("\nWORDS MISSPELLED:     %d\n", misspellings);
	printf("WORDS IN DICTIONARY:  %d\n", n);
	printf("WORDS IN TEXT:        %d\n", words);

	return 0;
}


