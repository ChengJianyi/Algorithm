#include "GMM.h"
#include <time.h>

GMM::GMM(int n, vector<Gaussian> g):gNum(n),threhold(0.001),gVec(g),gIter(gVec.begin()){}

double GMM::calcDistance(const VectorXd& v, const VectorXd& c)
{
    double sum = 0;
    for (int i = 0; i < v.size(); ++i)
        sum += pow(v(i) - c(i), 2);
    return sum;
}

void GMM::cluster(Sample& s)
{
    double min = calcDistance(s.getVec(), gVec[0].getExp());
    int minid = 0;
    for (int i = 0; i < gNum; ++i)
    {
        if (min > calcDistance(s.getVec(), gVec[i].getExp()))
        {
            min = calcDistance(s.getVec(), gVec[i].getExp());
            minid = i;
        } 
    }
    s.setLabel(minid);
}

bool GMM::calcCenter(vector<Sample>& s)
{
    int dimension = (s[0].getVec()).size();
    double c = 0;
    double diff = 0;
    bool con = true;
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < gNum; ++j)
        {
            double sum1 = 0, sum2 = 0;
            for (int k = 0; k < s.size(); ++k)
            {
                int a = (s[k].getLabel() == j)?1:0;
                sum1 += (s[k].getVec())(i)*a;
                sum2 += a;
            }
            c = sum1/sum2;
            diff = fabs((gVec[j].getExp())(i) - c);
            if (diff > threhold)
            {
                gVec[j].setExpItem(c, i);
                con = false;
            }
        }
    }
    return con;
}

void GMM::inistiallize(vector<Sample> s)
{
	//cout << 4 << endl;
	vector<int> r;
	vector<int>::iterator iter = r.begin();
	bool flag = false;
	int k = 0;
	srand((unsigned int)time(0));
	for (gIter = gVec.begin(); gIter != gVec.end(); ++gIter)
	{
		do{	
			flag = false;
			k = rand()%s.size();
			for (iter = r.begin(); iter != r.end(); ++iter)
				if ((*iter) == k) flag = true;
		}while(flag);
		r.push_back(k);
		//cout << s[k].getVec().transpose() << endl;
		(*gIter).initiallize(s[k].getVec(), gNum);
		vector<double> p;
		for(int i = 0; i < s.size(); i++)
			p.push_back(0);
		prob.push_back(p);
    }
    int count = 0;
    do{
        cout<<"cluster"<<count<<endl;
        for (int i = 0; i < s.size(); i++)
            cluster(s[i]);
        count++;
    }while(!calcCenter(s));
}

void GMM::eStep(vector<Sample> s)
{
	//cout << 1 << endl;
	int count = s.size();
	for (int i = 0; i < count; ++i)
	{
		double sum = 0;
		for (int j = 0; j < gNum; ++j)
		{
			sum += (gVec[j].getAlpha())*(gVec[j].calcGaussian(s[i].getVec()));
		}
		for (int j = 0; j < gNum; ++j)
		{
			(prob[j])[i] = (gVec[j].getAlpha())*(gVec[j].calcGaussian(s[i].getVec())) /sum;
		}
		//cout << i << endl;
	}
//	cout << 1 << endl;
}

bool GMM::mStep(vector<Sample> s, int dimension)
{
	//cout << 7 << endl;
	bool flag = true;
	for (int i = 0; i < gNum; i++)
	{
		double a = 0, sumA = 0;
		VectorXd e = VectorXd::Zero(dimension), sumE = VectorXd::Zero(dimension);
		MatrixXd c = MatrixXd::Zero(dimension, dimension), sumC = MatrixXd::Zero(dimension, dimension);
		for(int j = 0; j < s.size(); j++)
			sumA += (prob[i])[j]; 
		double sum = s.size();
		a = sumA / sum;
		for (int j = 0; j < s.size(); j++)
			sumE += (prob[i])[j]*s[j].getVec();
		e = sumE/sumA;
		for (int j = 0; j < s.size(); j++)
			sumC += (prob[i])[j] * (s[j].getVec() - gVec[i].getExp())*((s[j].getVec() - gVec[i].getExp()).transpose());
		c = sumC/sumA;
		flag = flag && gVec[i].checkCovergence(c, e, a);
		if (!gVec[i].checkCovergence(c, e, a))
		{
			gVec[i].setAlpha(a);
			gVec[i].setCov(c);
			gVec[i].setExp(e);
        }
    }
//	cout << 2 << endl;
	return flag;
}

void GMM::train(vector<Sample> s, int dimension, int num)
{
	FILE *fs;
	vector<double> v;
	double x; 
	if ((fs = fopen("TrainSamples.txt", "r"))== NULL)
	{
		cout<<"file1 error."<<endl;
		exit(1);
	}

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			fscanf(fs, "%lf", &x);
			v.push_back(x);
		}
		Sample ss;
		ss.setSample(v);
		s.push_back(ss);
		v.clear();
	}
	fclose(fs);
	FILE* fp;
	if((fp=fopen("result.txt","w")) == NULL)
	{
		cout<<"file error."<<endl;
		exit(1);
	}
	inistiallize(s);
   /* for (int i = 0; i < gNum; ++i)
    {
        cout<<"exp"<<i<<endl;
        cout<<gVec[i].getExp()<<endl;
    }
    exit(1);*/
	int count = 0;
	do{
		cout<<"iteration "<<count+1<<"."<<endl;
	/*	for (int i = 0; i < s.size(); i++)
		{
			double sum = 0;
			for (int j = 0; j < gNum; j++)
				sum += (gVec[j].getAlpha())*(gVec[j].calcGaussian(s[i].getVec()));
			s[i].setSum(sum);
            cout<<i<<endl;
		}*/
		eStep(s);
		count++;
	}while(!mStep(s, dimension));
	for (int i = 0; i < gNum; i++)
	{
		cout << "exp"<< i + 1<<":\n" << gVec[i].getExp() << endl;
		cout << "cov" << i + 1 << ":\n" << gVec[i].getCov() << endl;
		cout << "alpha" << i + 1 << ":\n" << gVec[i].getAlpha() << endl;
	}
	for (int i = 0; i < s.size(); i++)
	{
		double max = 0;
		int maxid = 0;
		for (int j = 0; j < gNum; j++)
		{
			if ((prob[j])[i] > max)
			{
				max = (prob[j])[i];
				maxid = j;
			}
		}
		s[i].setLabel(maxid);
		fprintf(fp, "%d\n", s[i].getLabel());
	}
	fclose(fp);
}
