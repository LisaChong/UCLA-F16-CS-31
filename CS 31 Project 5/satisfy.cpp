#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>

using namespace std;

const int MAX_WORD_LENGTH = 20;

int normalizeRules(char word1[][MAX_WORD_LENGTH + 1],
	char word2[][MAX_WORD_LENGTH + 1],
	int distance[],
	int nRules)
{
	for (int r = 0; r != nRules; r++)
	{
		if (word1[r][0] == '\0' || word2[r][0] == '\0') //Tests if there is an empty string and replaces the row with the last row, then tests it again.
		{
			strcpy(word1[r], word1[nRules - 1]);
			strcpy(word2[r], word2[nRules - 1]);
			distance[r] = distance[nRules - 1];
			nRules--;
			r--;
		}
	}
	for (int r = 0; r != nRules; r++) //Tests if there is a non-letter character in word1 and replaces the row with the last row, then tests it again.
	{
		for (int w = 0; word1[r][w] != '\0'; w++)
		{
			if (isalpha(word1[r][w]) != 0)
				word1[r][w] = tolower(word1[r][w]);
			else
			{
				strcpy(word1[r], word1[nRules - 1]);
				strcpy(word2[r], word2[nRules - 1]);
				distance[r] = distance[nRules - 1];
				nRules--;
				r--;
			}
		}
	}
	for (int r = 0; r != nRules; r++) //Tests if there is a non-letter character in word2 and replaces the row with the last row, then tests it again.
	{
		for (int w = 0; word2[r][w] != '\0'; w++)
		{
			if (isalpha(word2[r][w]) != 0)
				word2[r][w] = tolower(word2[r][w]);
			else
			{
				strcpy(word1[r], word1[nRules - 1]);
				strcpy(word2[r], word2[nRules - 1]);
				distance[r] = distance[nRules - 1];
				nRules--;
				r--;
			}
		}
	}
	for (int r = 0; r != nRules; r++) //Tests if there is a negative or 0 for distance and replaces the row with the last row, then tests it again.
	{
		if (distance[r] > 0);
		else
		{
			strcpy(word1[r], word1[nRules - 1]);
			strcpy(word2[r], word2[nRules - 1]);
			distance[r] = distance[nRules - 1];
			nRules--;
			r--;
		}
	}
	for (int r = 0; r != nRules; r++) //Tests if there is an exact string and replaces the row with the larger of the two distances and then tests it again.
	{
		for (int p = r + 1; p != nRules; p++)
		{
			int deleteRow;
			if (strcmp(word1[r], word1[p]) == 0 && strcmp(word2[r], word2[p]) == 0)
			{
				if (distance[r] > distance[p])
					deleteRow = p;
				else
					deleteRow = r;
				strcpy(word1[deleteRow], word1[nRules - 1]);
				strcpy(word2[deleteRow], word2[nRules - 1]);
				distance[deleteRow] = distance[nRules - 1];
				nRules--;
				p--;
			}
		}
	}
	for (int r = 0; r != nRules; r++)  //Tests if there is an cross match string and replaces the row with the larger of the two distances and then tests it again.
	{
		for (int p = r + 1; p != nRules; p++)
		{
			int deleteRow;
			if (strcmp(word1[r], word2[p]) == 0 && strcmp(word2[r], word1[p]) == 0)
			{
				if (distance[r] > distance[p])
					deleteRow = p;
				else
					deleteRow = r;
				strcpy(word1[deleteRow], word1[nRules - 1]);
				strcpy(word2[deleteRow], word2[nRules - 1]);
				distance[deleteRow] = distance[nRules - 1];
				nRules--;
				p--;
			}
		}
	}
	return nRules;
}

int calculateSatisfaction(const char word1[][MAX_WORD_LENGTH + 1],
	const char word2[][MAX_WORD_LENGTH + 1],
	const int distance[],
	int nRules,
	const char document[])
{
	char documentEdit[201] = {}; //makes a copy of the document to edit
	strcpy(documentEdit, document);
	for (int k = 0; documentEdit[k] != '\0'; k++)
		documentEdit[k] = tolower(documentEdit[k]);
	for (int k = 0; documentEdit[k] != '\0'; k++) //removes all non-alphabet characters
	{
		if (isalpha(documentEdit[k]) != 0 || (documentEdit[k] == ' '));
		else
		{
			for (int j = k; documentEdit[j] != '\0'; j++)
				documentEdit[j] = documentEdit[j + 1];
			k--;
		}
	}
	char document2D[100][200 + 1]; //stores every word on a different line
	int documentRows = 0;
	for (int k = 0; documentEdit[k] != '\0'; k++)
	{
		char tempWord[200 + 1] = {};
		int lengthTempWord = 0;
		for (int j = k; documentEdit[j] != ' ' && documentEdit[j] != '\0'; j++)
		{
			tempWord[j - k] = documentEdit[j];
			lengthTempWord++;
		}
		strcpy(document2D[documentRows], tempWord);
		k += lengthTempWord;
		documentRows++;
	}
	char word1copy[1000][MAX_WORD_LENGTH + 1];//initializes an editable word1/word2/distance
	for (int k = 0; k != nRules; k++)
	{
		strcpy(word1copy[k], word1[k]);
	}
	char word2copy[1000][MAX_WORD_LENGTH + 1];
	for (int k = 0; k != nRules; k++)
	{
		strcpy(word2copy[k], word2[k]);
	}
	int distancecopy[1000];
	for (int k = 0; k != nRules; k++)
	{
		distancecopy[k] = distance[k];
	}
	int satisfied = 0; 
	for (int k = 0; k != documentRows; k++) //deletes a rule if it has been satisfied (direct match)
	{
		for (int j = 0; j != nRules; j++)
		{
			for (int m = 0; m != distance[j]; m++)
			{
				if (strcmp(document2D[k], word1copy[j]) == 0 && strcmp(document2D[k + m + 1], word2copy[j]) == 0)
				{
					satisfied++;
					strcpy(word1copy[j], word1copy[nRules - 1]);
					strcpy(word2copy[j], word2copy[nRules - 1]);
					distancecopy[j] = distancecopy[nRules - 1];
					m = 0;
				}
			}
		}
		for (int j = 0; j != nRules; j++) //deletes a rule if it has been satisfied (cross match)
		{
			for (int m = 0; m != distance[j]; m++)
			{
				if (strcmp(document2D[k], word2copy[j]) == 0 && strcmp(document2D[k + m + 1], word1copy[j]) == 0)
				{
					satisfied++;
					strcpy(word1copy[j], word1copy[nRules - 1]);
					strcpy(word2copy[j], word2copy[nRules - 1]);
					distancecopy[j] = distancecopy[nRules - 1];
					m = 0;
				}
			}
		}
	}
	return satisfied;
}

int main()
{
	char word1[7][MAX_WORD_LENGTH + 1] = { "mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have" };
	char word2[7][MAX_WORD_LENGTH + 1] = { "scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad" };
	int distance[7] = { 2,4,1,3,2,1,13 };
	assert(normalizeRules(word1, word2, distance, 7) == 4);
	const int TEST1_NRULES = 4;
	char test1w1[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"mad",       "deranged", "nefarious", "have"
	};
	char test1w2[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"scientist", "robot",    "plot",      "mad"
	};
	int test1dist[TEST1_NRULES] = {
		2,           4,          1,           13
	};
	assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
		"The mad UCLA scientist unleashed a deranged evil giant robot.") == 2);
	assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
		"The mad UCLA scientist unleashed    a deranged robot.") == 2);
	assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
		"**** 2016 ****") == 0);
	assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
		"  That plot: NEFARIOUS!") == 1);
	assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
		"deranged deranged robot deranged robot robot") == 1);
	assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
		"That scientist said two mad scientists suffer from deranged-robot fever.") == 0);
	cout << "All tests succeeded" << endl;
}