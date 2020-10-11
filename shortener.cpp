#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;

class URLShortner
{
private:
	map<int, string> database;
	map<int, char> lookup;
	long long int entries_count;
	long long int base;

public:
	string Encode(string);
	string Decode(string);
	int GetEntryCount() {return entries_count;}
	URLShortner();
	~URLShortner();
	void ToString();
};

URLShortner::URLShortner()
{
	base = 1000000;
	entries_count = base;
	for(int i=0;i<=25;i++)
	{
		lookup[i] = i+97;		//looks for lowercase characters
	}
	for(int i=0;i<=25;i++)
	{
		lookup[i] = i+65;	// looks for upper case characters 
	}
	for(int i=0;i<=9;i++)
	{
		lookup[i] = i+48;	// looks for numbers 0 is 48 and 9 is 57
	}
}

URLShortner::~URLShortner()
{
	lookup.clear();
	database.clear();
}

string URLShortner::Encode(string longURL)
{
	entries_count++;
	long long int key = entries_count;
	database[key] = longURL;
	string shortURL = "";
	while(key > 0)		//base 62 encoding
	{
		int modulo = key%62;
		key /= 62;
		shortURL += lookup[modulo];
	}
	reverse(shortURL.begin(), shortURL.end());
	return shortURL;
}

string URLShortner::Decode(string shortURL)	// converts short url into long url 
{
	long long int key=0;
	long long int multiplier = 1;
	for(int i=shortURL.length()-1;i>=0;i--)
	{
		int lookupIndex;
		char lookupValue = shortURL[i];
		if(lookupValue>=97 && lookupValue<=122)
		{
			lookupIndex = lookupValue-97;
		}
		else if(lookupValue>=65 && lookupValue<=90)
		{
			lookupIndex = lookupValue-65;
			lookupIndex += 26;
		}
		else if(lookupValue>=48 && lookupValue<=57)
		{
			lookupIndex = lookupIndex-48;
			lookupIndex += 52;
		}
		key += multiplier*lookupIndex;
		multiplier *= 62;
	}
	if(key <= GetEntryCount() && key >= base)
	{
		string longURL;
		longURL = database[key];
		return longURL;		
	}
	else
	{
		string temp = "";
		return temp;
	}
	
}


int main()
{
	URLShortner urlShortner;
	//cout << "Set Of Operations Those Can Be Requested:" << endl;
	cout << "1. Enter compress for Compression Of URL" << endl;
	cout << "2. Enter decompress for De-Compression Of URL" << endl;
	cout << "3. Enter exit to Exit\n\n\n";
	string operation;
	string input;
	string output;
	const string compress = "compress";
	const string decompress = "decompress";
	const string exit = "exit";
	const string prefix = "ca.ke/";
	while(true)
	{
		cout << "Enter the operation you want to perform:\n> ";
		cin >> operation;
		if(operation == compress)
		{
			cout << "Enter the URL you want to compress:\n> ";
			cin >> input;
			output = urlShortner.Encode(input);
			cout << "Your compressed URL is: \"ca.ke/" << output << "\"" << endl;
		}
		else if(operation == decompress)
		{
			cout << "Enter the compressed URL which you want to decompress:\n> ";
			cin >> input;
			if(input.length() <= 6)
			{
				cout << "The prefix of the URL should be \"ca.ke/\"\n\n\n";
				continue;
			}
			string temp = "";
			for(int i=0;i<=5;i++)
			{
				temp += input[i];
			}
			if(temp.compare(prefix)==0)
			{
				string input_suffix = "";
				for(int i=6;i<input.length();i++)
				{
					input_suffix += input[i];
				}
				output = urlShortner.Decode(input_suffix);
				string forcheck = "";
				if(output.compare(forcheck)==0)
				{
					cout << "This URL has not been compressed previously\n\n\n";
					continue;
				}
				cout << "Your Original URL is: \"" << output << "\"" << endl;
			}
			else
			{
				cout << "The prefix of the URL should be \"ca.ke/\"\n\n\n";	
				continue;	
			}
			
		}
		else if(operation == exit)
		{
			cout << "Exited!";
			return 0;
		}
		else
		{
			cout << "Please input a valid command.\n";
		}
		cout << "\n\n";
	}
}