// HttpUrl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HttpUrl.h"

using namespace std;

std::string Information(CHttpUrl curl)
{
	std::string information = "URL: " + curl.GetURL() + "\n";
	if (curl.GetProtocol() == Protocol::HTTP)
	{
		information += "\tProtocol: http\n";
	}
	else
	{
		information += "\tProtocol: https\n";
	}
	information += "\tDomain: " + curl.GetDomain() + "\n";
	information += "\tPort: " + std::to_string(curl.GetPort()) + "\n";
	information += "\tDocument: " + curl.GetDocument() + "\n";
	return information;
}

int main()
{
	std::string url;
	CHttpUrl urld("yandex.ru", "doc.txt", Protocol::HTTPS);
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "Enter URL: ";
		getline(std::cin, url);
		if (std::cin.eof() || std::cin.fail())
		{
			break;
		}
		try
		{
			std::cout << Information(CHttpUrl(url));
		}
		catch (exception const& e)
		{
			std::cout << e.what();
		}
	}
	return 0;
}