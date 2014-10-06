#include <iostream>
#include <Eigen/Eigen>
#include <cmath>
#include <vector>
#include "GMM.h"

using namespace std;
using namespace Eigen;

int main()
{
	int dimension = 17;
	int gnum = 10;
	int num = 30000;
	vector<Gaussian> gv;
	vector<Sample> s;
	for (int i = 0; i < gnum; i++)
	{
		Gaussian g(dimension);
		gv.push_back(g);
	}
	GMM gmm(gnum, gv);
	cout << "Start." << endl;
	gmm.train(s, dimension, num);
	cout<<"Finished."<<endl;
}	
