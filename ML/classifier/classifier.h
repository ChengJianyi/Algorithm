#include <iostream>
#include <vector>
#include <Eigen/Eigen>
#include <fstream>
#include "sample.h"

using namespace std;
using namespace Eigen;

bool convergence(const VectorXd& v, const double& threhold, const int& dimension);

class Perceptron{
    private:
        const int dimension;
        const double threhold;
        int cNum;
        vector<VectorXd> aVec;
    public:
        Perceptron(int d, int c);
        int determine(const Sample& s, const int& i);
        void train(const vector<Sample>& s);
        const vector<VectorXd>& getVec();
        void classify(const vector<Sample>& s);
};

class LMSE{
    private:
        const int dimension;
        const int cNum;
        const double threhold;
        vector<VectorXd> bVec;
        MatrixXd yMat;
        MatrixXd aMat;
    public:
        LMSE(int d, int c, int s);
        void train(const vector<Sample>& s);
        void calcMatroid(const vector<Sample>& s);
        void classify(const vector<Sample>& s);
};

