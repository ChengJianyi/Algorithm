#include <iostream>
#include <Eigen/Eigen>
#include <vector>

using namespace std;
using namespace Eigen;

class Sample{
private:
	//const int dimension;
	VectorXd sVec;
	int label;
	double sSum;
public:
	Sample():label(0){}
	//Sample(int d, bool t);
	void setSample(vector<double> x);	
	const VectorXd& getVec();
	const int& getLabel();
	//const bool& getType();
	void setLabel(int l);
	void setSum(double sum);
	const double& getSum();
};