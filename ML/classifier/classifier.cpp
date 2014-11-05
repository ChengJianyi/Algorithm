#include "classifier.h"
#include <math.h>
#include <time.h>


bool convergence(const VectorXd& v, const double& threhold, const int& dimension)
{
    for (int i = 0; i < dimension; i++)
        if (fabs(v(i)) > threhold) return false;
    return true;
}

Perceptron::Perceptron(int d, int c):dimension(d), cNum(c), threhold(0.0001)
{
    srand(unsigned(time(NULL)));
    for (int i = 0; i < cNum; ++i)
    {
        VectorXd v = VectorXd::Zero(dimension);
        aVec.push_back(v);
    }
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < cNum; ++j)
            (aVec[j])(i) = ((double)rand())/RAND_MAX;
}

int Perceptron::determine(const Sample& s, const int& i)
{
    if (s.getLabel() == i)
    {
        if (aVec[i].transpose()*s.getVec()>0)
            return 0;
        else return 1;
    }
    else 
    {
        if (aVec[i].transpose()*s.getVec()>0)
            return -1;
        else return 0;
    }
}

void Perceptron::train(const vector<Sample>& s)
{
    bool flag = true;
    for (int i = 0; i < cNum; ++i)
    {
        double k = 1;
        double step = 0;
        VectorXd v(dimension);
        do{
            step = 0.1;
            v = VectorXd::Zero(dimension);
            for (int j = 0; j < s.size(); ++j)
            {
                int a = determine(s[j], i);
                v += a*s[j].getVec();
            }
            aVec[i] = aVec[i] + step*v;
            ++k;
        }while(!convergence(step*v, threhold, dimension));
        cout<<"The weight vector a is:"<<endl<<aVec[i].transpose()<<endl;        
    }
}

const vector<VectorXd>& Perceptron::getVec()
{
    return aVec;
}

void Perceptron::classify(const vector<Sample>& s)
{
    fstream out;
    out.open("result.txt", ios::out);
    for (int i = 0; i < s.size(); ++i)
        for (int j = 0; j < cNum; ++j)
            if (aVec[j].transpose()*s[i].getVec() > 0)
                out<<j<<endl;
    out.close();
}


LMSE::LMSE(int d, int c, int s):dimension(d), cNum(c), threhold(0.0001)
{
    yMat = MatrixXd::Zero(s, dimension);
    aMat = MatrixXd::Zero(dimension, c);
    srand(unsigned(time(NULL)));
    for (int i = 0; i < c; ++i)
        for (int j = 0; j < dimension; ++j)
            aMat(j, i) = ((double)rand())/RAND_MAX;
    VectorXd v1 = VectorXd::Zero(c);
    for (int i = 0; i < s; ++i)
    {
        for (int j = 0; j < c; ++j)
            v1(j) = -0.01;
        bVec.push_back(v1);
    }
}

void LMSE::train(const vector<Sample>& s)
{
    /*double step = 0;
    int k = 1;
    VectorXd v(dimension);
    for (int i = 0; i < s.size(); ++i)
    {   
        for (int j = 0; j < dimension; ++j)
        {
           // int a = (s[i].getLablel())
            yMat(i,j) = (s[i].getVec())(j);
        }
    }
    for (int k = 0; k < cNum; ++k)
    {
        do{
            step = 1/k;
            v = VectorXd::Zero(dimension);
            for (int i = 0; i < s.size(); ++i)
                v = v + (bVec(i) - aVec.transpose()*s[i].getVec())*s[i].getVec();
            aVec = aVec + step*v;
            ++k;
        }while(!convergence(step*v, threhold, dimension));
    }*/
}
void LMSE::calcMatroid(const vector<Sample>& s)
{
    MatrixXd bMat(s.size(), cNum);
    for (int i = 0; i < s.size(); ++i)
    {  
        int c = s[i].getLabel();
        (bVec[i])(c) = 10;
        for (int j = 0; j < dimension; ++j)
            yMat(i, j) = (s[i].getVec())(j);
        for (int j = 0; j < cNum; ++j)
            bMat(i, j) = (bVec[i])(j);
    }
    aMat = (yMat.transpose()*yMat).inverse()*(yMat.transpose())*bMat;
    cout<<"The weight matrix is:"<<endl<<aMat<<endl;
}

void LMSE::classify(const vector<Sample>& s)
{
    ofstream out;
    out.open("result.txt", ios::out);
    for (int i = 0; i < s.size(); ++i)
    {
        RowVectorXd v(dimension);
        v = s[i].getVec().transpose()*aMat;
        double max = 0;
        int maxid = 0;
        for (int j = 0; j < cNum; ++j)
            if (max < v(j))
            {
                max = v(j);
                maxid = j;
            }
        //cout<<maxid<<endl;
        out<<maxid<<endl;
    }
    out.close();
}
