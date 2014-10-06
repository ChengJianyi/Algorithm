#include <iostream>
#include <vector>
#include <Eigen/Eigen>
#include <cmath>

using namespace std;
using namespace Eigen;

class Gaussian{
private:
	const int dimension;
	const double threhold;
	const double pi;
	MatrixXd gCovMatrix;
	VectorXd gExpVector;
	double alpha;
public:
	Gaussian(int d);
	void initiallize(VectorXd x, double m);
	void initiallize(MatrixXd c, VectorXd e, double a);
	const MatrixXd& getCov();
	const VectorXd& getExp();
	const double& getAlpha();
	void setCov(MatrixXd c);
	void setExp(VectorXd e);
	void setAlpha(double a);
	double calcGaussian(VectorXd x);
	bool checkCovergence(MatrixXd c, VectorXd e, double a);
    Gaussian& operator=(Gaussian&){};
};
