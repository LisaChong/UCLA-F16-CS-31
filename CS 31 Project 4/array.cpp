#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);

int main()
{
	string h[7] = { "jill", "hillary", "donald", "tim", "", "evan", "gary" };
	assert(lookup(h, 7, "evan") == 5);
	assert(lookup(h, 7, "donald") == 2);
	assert(lookup(h, 2, "donald") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "jill", "hillary", "gary", "mindy" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "jill?" && g[3] == "mindy?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "gary?" && g[3] == "hillary?");

	string e[4] = { "donald", "tim", "", "evan" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "hillary", "hillary", "hillary", "tim", "tim" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "gary", "donald", "mike" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "gary");

	assert(separate(h, 7, "gary") == 4);

	cout << "All tests succeeded" << endl;
}
	
	
int appendToAll(string a[], int n, string value)
{
	if (n<0)
	return -1; //if a negative number is inputted, we return -1
	else
	{
		for (int k=0; k < n; k++)
			a[k] += value; //for every position k, we count through and add on the value at the end
		return n;
	}
}

int lookup(const string a[], int n, string target)
{
	if (n<0)
	return -1; //if a negative number is inputted, we return -1
	else
	{
		for (int k=0; k<n; k++)
		{
			if (a[k]==target) //the array of strings is searched from position 0 until the target is found
				return k;
		}
		return -1; //If the target is not found, the array returns -1
	}
}

int positionOfMax(const string a[], int n)
{
	if (n<0)
	return -1; //if a negative number is inputted, we return -1
	for (int k=0; k<n; k++) //This takes the first position of the array and runs it through the check
	{
		for (int j=0; j<n; j++) //This check compares that position of the array to see if it is larger than every other position.
		{
			if(a[k] < a[j]) //If the string is not larger than another position, it breaks out of this loop to continue to the next array position.
				break;
			if (j==(n-1)) //if the end of the array is reached and it is larger than every other position of the array, it returns that very number.
				return k;
		}
	}
	return -1;
}

int rotateLeft(string a[], int n, int pos)
{
	if (n<0)
	return -1; //if a negative number is inputted, we return -1
	string last = a[pos]; //This stores the position that we are shifting
	for (int k=pos; k<(n-1); k++)
	{
		a[k] = a[k+1]; //every number at the position onward will be assigned the array position after it.
	}
	a[n-1] = last; //The last array position will be assigned the stored value.
	return pos;
}

int countRuns(const string a[], int n)
{
	if (n<0)
	return -1; //if a negative number is inputted, we return -1
	int consec = 0; //This counts the number of unique values that are consequetive.  
	for (int k=0; k<n; k++)
	{
		int tally = 0; //This sets a tally at 0
		int m = 0; //This sets m at 0
		for (int j=(k+1); j<n; j++)
			{
			if (a[k] == a[j]) //If the position is equivilant to the one after it, we add one to the tally
				tally++;
			else
				break;
		    }
		k += tally; //The k is added to the tally such that we skip over the ones that are consecutive.
		consec++; //We add a value to our consecutive count.
	}
	return consec;
}

int flip(string a[], int n)
{
	if (n<0)
	return -1; //if a negative number is inputted, we return -1
	for (int k=0; k<n; k++)
	{
		if (k > n/2.0) //If we've reached past the midway point, we stop and return the value that we inputted because this means that we've switched all of the values.
			return n;
		string temp = a[k]; //This stores our value as a temporary one.
		a[k] = a[n-1-k]; //This switches it with the respective position in from the other end
		a[n-1-k] = temp; //This restores the first value to the space it was replaced with.
	}
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	if (n1<0 || n2<0)
		return -1; //if a negative number is inputted, we return -1
	int n = 0;
	if (n1<=n2)
		n = n1;
	else
		n = n2; //This if else sets the n to the smaller of the two numbers
	int place = 0; //This sets a place integer to 0.
	for (int k=0; k<n; k++)
	{
		if (a1[k] == a2[k]) //If the first array space is equal to the next, we add one to the place counter.
			place++;
		else
			break;
	}
	if (place == n) //If we've reached the end of one array, we return the smaller of the two n's.
		{
		if (n1<=n2)
			return n1;
		else
			return n2;
		}
	return place; //We return the place that it was first not equivalent.
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n1<0 || n2<0)
		return -1; //if a negative number is inputted, we return -1
	int sub = -1; //Set a sub equal to -1.
	for (int k=0; k<n1; k++)
	{
		if (k > (n1-n2)) //If a1 has reached a point where it can't contain all of the values of a2, we return -1.
			return -1;
		if (a1[k] == a2[0]) //If the position of k is equivalent to a2 position 0, we run through the following array strings to see if they match up
		{
			sub = k;
			for (int j=(k+1); j<(k+n2); j++)
			{
				if (a1[j] == a2[j-k]);
				else
					break;
				if (j==(k+n2-1))
					return sub; //If they all add up, we return the array spot.
			}
		}
	}
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1<0 || n2<0)
		return -1; //if a negative number is inputted, we return -1
	for (int k=0; k<n1; k++) //We start at the first spot in array 1 and see if anything array 2 matches up
	{
		for (int j=0; j<n2; j++) //This checks if any of the array 2 match up with that position of array 1
		{
			if (a1[k] == a2[j])
				return k;
		}
	}
	return -1; //If nothing matches, we return -1.
}

int separate(string a[], int n, string separator)
{
	if (n<0)
		return -1; //if a negative number is inputted, we return -1
	for (int k=0; k<n; k++)
	{
		string temp;
		for (int j=(k+1); j<n; j++) //This compares the array space with all of those after it.
		{
			if (a[k] >= a[j]) //This searchs through and switches array positions until the smallest is in the k position.
			{
			    temp = a[j];
				a[j] = a[k];
				a[k] = temp;
			}
		} //Repeating this loop, we slowly arrange the array from smallest to largest.
	}
	for (int m=0; m<n; m++)
	{
		if (a[m] <= separator); //This counts through the array until we get a value that isn't smaller than the given separator, then return that value.
		else
			return m;
	}
}