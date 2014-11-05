#include <iostream>
#include <vector>
#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;

class Sample{
    private:
        VectorXd vec;
        int label;
    public:
        Sample();
        const VectorXd& getVec() const;
        const int& getLabel() const;
        void setVec(const VectorXd& v);
        void setLabel(const int& l);
};
