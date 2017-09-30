#include <iostream>
#include <cctype>
#include <string>
using namespace std;

//These allows us to main function before the other functions.
bool hasCorrectSyntax(string pollData);
int countVotes(string pollData, char party, int& voteCount);
bool isValidUppercaseStateCode(string stateCode);
void uppercase(string& capitalize);

int main()
{
	//This is the main function which tests three different cases.
	if (hasCorrectSyntax("TX38RCA55D"))
	cout << "Passed test 1: hasCorrectSyntax(\"TX38RCA55D\")" << endl;
	if (!hasCorrectSyntax("MX38RCA55D"))
	cout << "Passed test 2: !hasCorrectSyntax(\"MX38RCA55D\")" << endl;
	int votes;
	votes = -999;    // so we can detect whether countVotes sets votes
	if (countVotes("TX38RCA55DMs6rnY29dUT06L", 'd', votes) == 0  &&  votes == 84)
	cout << "Passed test 3: countVotes(\"TX38RCA55DMs6rnY29dUT06L\", 'd', votes)" << endl;
	votes = -999;    // so we can detect whether countVotes sets votes
	if (countVotes("TX38RCA55D", '%', votes) == 3  &&  votes == -999)
	cout << "Passed test 4: countVotes(\"TX38RCA55D\", '%', votes)" << endl;
}

bool hasCorrectSyntax(string pollData)
{
	uppercase(pollData); //This capitalizes all of the letters in the string.
	if (pollData == "")
		return true; //This returns a proper function for an empty string.
	for (int k = 0; k < pollData.size(); k++)
	{
		int numberOfDigits;
		if (isalpha(pollData[k]) && isalpha(pollData[k + 1])) //This ensures that the first two characters in the string segment that we're looking at are letters.
		{
			string stateCode = pollData.substr(k, 2); //This creates a substring of the first two characters.
			if (isValidUppercaseStateCode(stateCode) == false) //This checks the substring against proper state codes.
				return false;
			else {
			    if (isdigit(pollData[k+2])) //If the state is proper then we proceed with checking the next characters for being digits.
			    {
			        if (isdigit(pollData[k+3])) //This checks if the number is one or two digits long.
					numberOfDigits = 2;
		        	else numberOfDigits = 1;
			    }
			    else
			        return false; //This returns false if there are no digits after the state.
			    
				if (isalpha(pollData[k+2+numberOfDigits])) //Given there are digits, we check if the next character (party) is a letter.
				    k = (k+2+numberOfDigits); //This adds the length of 2 (for the state code and party) and number of digits to k to reach where k is the last place of our first poll data.
				else
				    return false; //This returns false if the party is not a letter.
			    }
		 }
		else
			return false; //This returns false if the first two characters are not letters.
	}
	return true; //If the string passes through everything, it is true that it is correct.
}

int countVotes(string pollData, char party, int& voteCount)
{
	if(hasCorrectSyntax(pollData) == false) //This returns 1 if the syntax is not correct for the string.
		return 1;
	for (int k = 0; k < pollData.size(); k++) //This returns two if there are no votes for party in the entire string.
	{
	    int numberOfDigits;
	    if (isdigit(pollData[k+3])) //This checks the if there are two digits or one digit.
		{
			numberOfDigits = 2;
			if ((pollData[k+2] == '0') && (pollData[k+3] == '0')) //If both digits are 0 then return 2.
				return 2;
		}
		else if (pollData[k+2] == '0') //If the only digit is 0, return 2.
				{
				    return 2;
		            numberOfDigits = 1;
				}
		k = (k+2+numberOfDigits); //This adds on the proper length so that the next segment we check begins after this party character.
	}
	if (!isalpha(party)) //This returns 3 if the party is not a letter.
		return 3;
	voteCount = 0;
	for (int k = 0; k < pollData.size(); k++) //This counts the votes for a certain party.
	{
		int numberOfDigits;
		if (isdigit(pollData[k+3])) //This checks how many digits there are.
				numberOfDigits = 2;
		else numberOfDigits = 1;
		
		party = toupper(party); //This changes the party to an uppercase letter.
		uppercase(pollData);
	
		if (pollData[k+2+numberOfDigits] == party) //This looks for the correct party and adds the numbers in front of it to the vote count.
		{
			if (numberOfDigits == 1)
				voteCount += (pollData[k+2]-'0');
			else
				voteCount += (((pollData[k+2]-'0')*10)+(pollData[k+3]-'0'));
		}
		k = (k+2+numberOfDigits);
	}
	return 0;
}

bool isValidUppercaseStateCode(string stateCode) //This checks if the state codes are valid.
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
		"KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC."
		"ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos  &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}

void uppercase(string& capitalize) //This capitalizes the letters in a string.
{  
    for (int k = 0; k != capitalize.size(); k++)
	{
		if (isalpha(capitalize[k]))
			capitalize[k] = toupper(capitalize[k]);
	}
}