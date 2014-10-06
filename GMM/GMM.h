#include <iostream>
#include <Eigen/Eigen>
#include <vector>
#include "Gaussian.h"
#include "Sample.h"
#include <stdio.h>

using namespace std;
using namespace Eigen;

class GMM
{
private:
	const int gNum;
	vector<Gaussian> gVec;
	vector<Gaussian>::iterator gIter;
	vector<vector<double> > prob;
public:
	GMM(int n, vector<Gaussian> g);
	void inistiallize(vector<Sample> s);
	void eStep(vector<Sample> s);
	bool mStep(vector<Sample> s, int dimension);
	void train(vector<Sample> s, int dimension, int num);
};
