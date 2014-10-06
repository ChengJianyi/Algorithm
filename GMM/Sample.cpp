#include "Sample.h"

void Sample::setSample(vector<double> x)
{

	sVec = VectorXd::Zero(x.size());
	for (int i = 0; i < x.size(); i++)
		sVec(i) = x[i];
	//label = x[0];
}

const VectorXd& Sample::getVec()
{
	return sVec;
}

const int& Sample::getLabel()
{
	return label;
}

void Sample::setLabel(int l)
{
	label = l;
}

void Sample::setSum(double sum)
{
	sSum = sum;
}

const double& Sample::getSum()
{
	return sSum;
}