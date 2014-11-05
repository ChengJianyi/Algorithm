#include "sample.h"

Sample::Sample():label(0){}

const VectorXd& Sample::getVec() const
{
    return vec;
}

const int& Sample::getLabel() const
{
    return label;
}

void Sample::setVec(const VectorXd& v)
{
    vec = v;
}

void Sample::setLabel(const int& l)
{
    label = l;
}

