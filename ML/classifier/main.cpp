#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Eigen>
#include <stdio.h>
#include "classifier.h"


using namespace std;
using namespace Eigen;

int main()
{
    vector<Sample> s;
    vector<Sample> st;
    int dimension = 18;
    int size = 30000;
    int tsize = 10000;
    int cNum = 10;
    FILE* f1 = fopen("trainsamples.txt", "r");
    FILE* f2 = fopen("TrainLabels.csv", "r");
    FILE* f3 = fopen("testsamples.txt", "r");
    if (!f1 || !f2 || !f3) exit(1);
    double x = 0;
    int y = 0;
    for (int i = 0; i < size; ++i)
    {
        Sample ss;
        VectorXd v = VectorXd::Zero(dimension);
        v(dimension-1)=1;
        for (int j = 0; j < dimension-1; ++j)
        {
            fscanf(f1, "%lf", &x);
            v(j) = x;
        }
        fscanf(f2, "%d", &y);
        ss.setVec(v);
        ss.setLabel(y);
        s.push_back(ss);
    }
    for (int i = 0; i < tsize; ++i)
    {
        Sample ss;
        VectorXd v = VectorXd::Zero(dimension);
        v(dimension-1)=1;
        for (int j = 0; j < dimension - 1; ++j)
        {
            fscanf(f3, "%lf", &x);
            v(j) = x;
        }
        ss.setVec(v);
        st.push_back(ss);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    cout<<"Perceptron or LMSE?(p/l)"<<endl;
    char select;
    Perceptron p(dimension, cNum);
    LMSE l(dimension, cNum, size);
    cin>>select;
    switch(select)
    {
        case 'p':
            p.train(s);
            p.classify(st);
            break;
        case 'l':
            l.calcMatroid(s);
            l.classify(st);
            break;
        default:break;
    }
    cout<<"Completed!"<<endl;
}

