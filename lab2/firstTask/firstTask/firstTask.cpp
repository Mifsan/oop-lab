// firstTask.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VectorProcess.h"

using namespace std;

int main()
{
	vector<float> vectorOfFloats((istream_iterator<float>(cin)), istream_iterator<float>());
	ProcessVector(vectorOfFloats);
	sort(vectorOfFloats.begin(), vectorOfFloats.end());
	copy(vectorOfFloats.begin(), vectorOfFloats.end(), ostream_iterator<float>(cout, " "));
	cout << endl;
	system("pause");
    return 0;
}

