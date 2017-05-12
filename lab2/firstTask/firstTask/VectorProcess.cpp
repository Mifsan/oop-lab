#include "VectorProcess.h"
#include "stdafx.h"

using namespace std;

struct SumAndAmountOfPositiveNumbers
{
	SumAndAmountOfPositiveNumbers()
	{
		sum = 0;
		amount = 0;
	}
	void operator() (float number)
	{
		if (number > 0)
		{
			amount++;
			sum += round(number * 1000) / 1000;
		}
	}
	float sum;
	int amount;
};

float CalculateArithmeticalMeanOfFloats(float sum, int amount)
{
	return (amount > 0) ? sum / amount : 0;
}

void ProcessVector(vector<float>& vectorForProcessing)
{
	SumAndAmountOfPositiveNumbers SumAndAmount = for_each(vectorForProcessing.begin(), vectorForProcessing.end(), SumAndAmountOfPositiveNumbers());
	const float arithmeticalMean = CalculateArithmeticalMeanOfFloats(SumAndAmount.sum, SumAndAmount.amount);
	for (size_t i = 0; i < vectorForProcessing.size(); i++)
	{
		vectorForProcessing[i] += round(arithmeticalMean * 1000) / 1000;
	}
}