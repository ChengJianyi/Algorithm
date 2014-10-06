#include "Gaussian.h"
#include <iomanip>
#include <time.h>

Gaussian::Gaussian(int d):dimension(d),threhold(0.01),pi(3.1416),gCovMatrix(MatrixXd::Zero(dimension, dimension)),gExpVector(VectorXd::Zero(dimension)),alpha(0){}

void Gaussian::initiallize(VectorXd x, double m)
{
	for (int i = 0; i < dimension; i++)
		gCovMatrix(i, i) = pow(10, 7);
	for (int i = 0; i < dimension; i++)
		gExpVector(i) = x[i];
	alpha = 1/m;
}

void Gaussian::initiallize(MatrixXd c, VectorXd e, double a)
{
	gCovMatrix = c;
	gExpVector = e;
	alpha = a;
}

const MatrixXd& Gaussian::getCov()
{
	return gCovMatrix;
}

const VectorXd& Gaussian::getExp()
{
	return gExpVector;
}

const double& Gaussian::getAlpha()
{
	return alpha;
}

void Gaussian::setCov(MatrixXd c)
{
	gCovMatrix = c;
}

void Gaussian::setExp(VectorXd e)
{
	gExpVector = e;
}

void Gaussian::setAlpha(double a)
{
	alpha = a;
}

double Gaussian::calcGaussian(VectorXd x)
{
	double part1 = 1/(pow((2*pi),dimension/2.0)*sqrt(gCovMatrix.determinant()));
	double part2 = exp(-0.5*((x - gExpVector).transpose())*(gCovMatrix.inverse())*(x - gExpVector));
	//cout << -0.5*((x - gExpVector).transpose())*(gCovMatrix.inverse())*(x - gExpVector) << endl;
	//cout << part2 << endl;
	if (part2 == 0) cout << "error" << endl;
	return part1*part2;
}

bool Gaussian::checkCovergence(MatrixXd c, VectorXd e, double a)
{
	bool c1 = true, c2 = true;
	for (int i = 0; i < dimension; i++)
	{
		for(int j = 0; j < dimension; j++)
		{
			if (fabs(gCovMatrix(i,j) - c(i,j)) > threhold)
			{
			    return false;
            }
		}
	}
	for (int i = 0; i < dimension; i++)
		if (fabs(gExpVector(i) - e(i)) > threhold)
		{
		    return false;
        }
	if (fabs(alpha - a) > threhold) return false;
	return true;
}

