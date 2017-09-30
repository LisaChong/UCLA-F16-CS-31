	#include <iostream>
	#include <string>
	using namespace std;

	int main()
	{
		//Defining the cut offs and percentages for different brackets for the license fee.
		double FIRST_CUT_OFF = 20;
		double SECOND_CUT_OFF = 50;
		double FIRST_BRACKET = 0.181;
		double SECOND_BRACKET_UAETURKEY = 0.217;
		double SECOND_BRACKET = 0.203;
		double THIRD_BRACKET = 0.23;

		//Input the Identification
		cout << "Identification: ";
		string identification;
		getline(cin, identification);

		//Input the Expected revenue
		cout << "Expected revenue (in millions): ";
		double exprev;
		cin >> exprev;
		cin.ignore(1000, '\n'); //Switches back to strings from numbers

								//Input the Country
		cout << "Country: ";
		string country;
		getline(cin, country);

		//Set the number of numbers after the decimal point
		cout.setf(ios::fixed);
		cout.precision(3);

		//Output the three hyphens
		cout << "---" << endl;

		//if ladder that reads out the error line based on the first occuring error.
		if (identification == "")
			cout << "You must enter a property identification." << endl;
		if (exprev < 0)
			cout << "The expected revenue must be nonnegative." << endl;
		if (country == "")
			cout << "You must enter a country." << endl;

		//if ladder continuation if the input is not error inducing.
		if (identification != "" && exprev >= 0 && country != "") //The error inducing conditions must all be false.
		{
			cout << "The license fee for " << identification << " is $"; //types the sentence before the numerical evaluation.
			if (exprev < FIRST_CUT_OFF)
				cout << (FIRST_BRACKET * exprev); //output if the revenue is less than 20 million.
			else if (country == "UAE" || country == "Turkey")
				if (exprev < SECOND_CUT_OFF)
					cout << (FIRST_BRACKET * 20 + (exprev - 20) * SECOND_BRACKET_UAETURKEY); //output if the revenue is 20 < x < 50 and the country is UAE or Turkey.
				else cout << (FIRST_BRACKET * 20 + 30 * SECOND_BRACKET_UAETURKEY + (exprev - 50) * THIRD_BRACKET); //output if the revenue is greater than 50 and the country is UAE or Turkey.
			else if (exprev < SECOND_CUT_OFF)
				cout << (FIRST_BRACKET * 20 + (exprev - 20) * SECOND_BRACKET); //output if the revenue is 20 < x < 50 and the country is not UAE or Turkey.
			else cout << (FIRST_BRACKET * 20 + 30 * SECOND_BRACKET + (exprev - 50) * THIRD_BRACKET); //output if the revenue is greater than 50 and the country is not UAE or Turkey.
			cout << " million." << endl; //types the million. after the value.
		}
	}
