#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;
using std::ifstream;
using std::setprecision;
using std::fixed;
using std::istringstream;
using std::terminate;

struct duom
{
    string var="test";
    string pav="test";
    int C[100]={0};
    int exam=0;
    double vid=0, med=0;
    double mark;
};

double average(duom given, int n)
{
    double sum=0.0;
    for(int i=0; i<n; i++)
    {
        sum+=given.C[i];
    }
    return sum/n;
}
double median(duom given, int n)
{
    if(n%2==1)
    {
        return given.C[((n/2)+1)-1];
    }
    else
    {
        double ats=0.0;
        ats=given.C[n/2-1];
        ats+=given.C[n/2+1-1];
        ats/=2;
        return ats;
    }
}

#endif // TEMPLATE_H_INCLUDED


