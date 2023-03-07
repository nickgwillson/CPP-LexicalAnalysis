#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

ofstream outfile;
ifstream infile;

bool valid = true;


bool isKEYWORD(const string& token)
// Test whether it is a keyword, 
// like cout, cin, if, else, while, for...
{
	//if (token == "cin" || "if" || "else" || "while" || "cout")
	if (token == "if")
		return true;
	else if (token == "for")
		return true;
	else if (token == "else")
		return true;
	else if (token == "while")
		return true;
	else if (token == "cin")
		return true;
	else if (token == "cout")
		return true;
	else if (token == "bool")
		return true;
	else if (token == "case")
		return true;
	else if (token == "const")
		return true;
	else if (token == "float")
		return true;
	else if (token == "false")
		return true;
	else if (token == "true")
		return true;
	else if (token == "void")
		return true;
	else if (token == "switch")
		return true;
	else if (token == "int")
		return true;
	else if (token == "double")
		return true;
	else return false;
}


bool isSignedInt(const string& token)
{
// test whether it is a +/- integer, ie. 123, +123, -123 ...
//if starts with + or - its ok
//scan string for any letters or symbols, making sure only numbers are shown

	const char* c = token.c_str();						 //break down one word token into a char class
	bool value = true;


	if (c[0] == '+' || c[0] == '-' || isdigit(c[0]))	//checking first sign of token 
	{
		for (size_t i = 1; i < token.size(); i++)			 //for the whole char array
		{
			if (isdigit(c[i]))						
				value = true;
			else if (!isdigit(c[i]))
				 return false;
			else
				return false;;
		}
	}
	else
		return false;

	return value;
	
}

bool isSignedFloatingPoint(const string& token)
{
//test whether it is 12, 12.34, -1.23, -12.3E5, 1.23e-3, +.123E-2, 123E5 ....

	//if starts with +-. or . it is ok.
	//can scan for all numbers, if something isnt a number check that it is an E/e, a

	const char* c = token.c_str();						 //break down one word token into a char class
	bool value = true;
	int periodCNTR = 0;
	int eCNTR = 0;
	int addCNTR = 0;


	if (c[0] == '+' || c[0] == '-' || isdigit(c[0]))
	{
		//cout << "token : " << token << " is being tested for class 4" << endl;
		for (size_t i = 1; i < token.size(); i++)			 //for the whole char array
		{
			string s(1, c[i]);							 //make each char a string
			if (isdigit(c[i]))
				value = true;
			else if (!isdigit(c[i]))
			{
				if (c[i] == '.')				//if the nondigit is a period. categorize it
				{
					periodCNTR = periodCNTR + 1;
					value = true;
				}
				else if (c[i] == 'e' || c[i] == 'E')		//if nondigit is an e, log it
				{
					eCNTR = eCNTR + 1;
					value = true;
				}
				else if (c[i] == '+' || c[i] == '-')
				{
					if (c[i-1] == 'E' || c[i-1] == 'e')
					{
						addCNTR = addCNTR + 1;
						value = true;
					}
					else
						return false;
				}
			}
			else
				return false;
		}  

	   if (periodCNTR > 1 || eCNTR > 1 || addCNTR > 1)		  //checking for only one period and 'E'
		{
		   cout << "invalid expression " << c << " has incorrect syntax" << endl;
		   valid = false;
		   return false;   
		}
	}													 
	else
		return false;

	return value;
}

 bool isIdentifier(const string& token) 
// test whether it is a variable name,e function name, class...
{

	if ( isKEYWORD(token) || isSignedInt(token) || isSignedFloatingPoint(token))
		return false;
	else
		return true;


}


int main()
{

	int count = 0;
	const int SIZE = 45;
	string tokens[SIZE];
	int tokenClass[SIZE];

	infile.open("prog1in.txt");

	if (!infile) {
		cout << "ERROR OPENING FILE!" << endl;
		exit(1);
	}

	int x = 0;
	while (count <SIZE && infile >> tokens[count])	    //displaying all tokens 
	{												 
		cout << "token " << count << " is " << tokens[count] << endl;
		count++;	

		x = count;
	}
	
	infile.close();

	cout << endl << "*********************************************************" << endl;

	int validCNTR = 0;

	for (int i = 0; i < x; i++)
	{
		if (isKEYWORD(tokens[i]))
			tokenClass[i] = 1;
		else if (isSignedInt(tokens[i]))
			tokenClass[i] = 3;
		else if (isSignedFloatingPoint(tokens[i]))
			tokenClass[i] = 4;
		 else if (isIdentifier(tokens[i]))
			tokenClass[i] = 2;
		else
		{
			cout << tokens[i] << " on line " << i << " is not accecpted." << endl;
			valid = false;
			tokenClass[i] == 0;
		}

		if (valid == false)
		{
			validCNTR = validCNTR + 1;
			cout << "An invalid signed integer is detected at line: " << i << endl;
			if (validCNTR<=1)
				outfile.open("prog1out.txt");
			outfile <<"*An invalid signed integer is detected at line: " << i << "*"<<endl;

		}
			
	}

	//	 ************************************************************************************
	//	 table displaying tokens, their class, and what line they live on
	//	************************************************************************************
	if (valid)
	 outfile.open("prog1out.txt");
	

	for (size_t i = 0; i < x; i++)
	{
		outfile << tokens[i] << endl;
	}
	outfile << endl;
	

	cout << "tokens now stored in file prog1out.txt" << endl<<endl;

	//outfile.close();

	if (valid)	   //print table, and store in file
	{
		cout << "line\t\t" << "token class\t\t" << "token value\t\t" << endl;
		cout << "----\t\t" << "-----------\t\t" << "-----------\t\t" << endl;

		for (size_t i = 0; i < x; i++)
		{
			cout << i+1<<"   \t\t   " << tokenClass[i]<<"\t\t\t" << tokens[i] << endl;
		}

		//*************************************************************

		//outfile.open("prog1out.txt");	  //now store table in prog1out.txt

		outfile << "line\t\t" << "token class\t\t" << "token value\t\t" << endl;
		outfile << "----\t\t" << "-----------\t\t" << "-----------\t\t" << endl;
		for (size_t i = 0; i < x; i++)
		{
			outfile << i + 1 << "   \t\t   " << tokenClass[i] << "\t\t\t" << tokens[i] << endl;
		}

		cout << endl<< "token table now stored in file prog1out.txt" << endl;

		outfile.close();

	}
	else
		outfile.close();



	int y;
	cin >> y;



 }