#include <iostream>
#include <Eigen/Eigen>
#include <stdio.h>

using namespace std;
using namespace Eigen;

int main()
{
    FILE* p = fopen("samples.txt", "r");
    while (!feof(p))
    {
        double x = 0;
        VectorXd v(2);
        for (int i = 0; i < 2; i++)
        {
            fscanf(p, "%lf", &x);
            v(i) = x;
        }
        cout<<v.transpose()<<endl;    
    }
    fclose(p);
}
