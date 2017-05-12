#include "stdafx.h"
#include "HTMLDecoder.h"


using namespace std;

void Replace(string& currentStr, string const& searchStr, string const& replaceStr)
{
	size_t currentPos = 0;
	size_t searchStrPos = currentStr.find(searchStr, 0);

	string tmpStr;

	while (currentPos < currentStr.length())
	{
		if (currentPos < searchStrPos)
		{
			tmpStr += currentStr[currentPos];
			++currentPos;
		}
		else
		{
			tmpStr += replaceStr;
			currentPos += searchStr.length();
			searchStrPos = currentStr.find(searchStr, currentPos);
		}
	}
	currentStr.swap(tmpStr);
}


string HtmlDecode(string const& html)
{
	string newHtmlStr = html;
	map <string, string> decodeMap = {
		{ "&quot;", "\"" },
		{ "&apos;", "'" },
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&amp;", "&" }
	};

	for (auto i = decodeMap.begin(); i != decodeMap.end(); i++)
	{
		Replace(newHtmlStr, i->first, i->second);
	}
	return newHtmlStr;
}