// secondTask.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HTMLDecoder.h"

using namespace std;

int main()
{
	string htmlString;
	cout << "Enter html strings to decode. Enter EOF for exit." << "\n";
	while (getline(cin, htmlString))
	{
		htmlString = HtmlDecode(htmlString);
		cout << htmlString << "\n";
	}
	return 0;
}

