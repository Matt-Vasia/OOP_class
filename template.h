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
    vector<int> pazymiai;
    int exam=0;
    double vid=0, med=0;
    double mark;
};

void read(duom &laik, vector <duom> &grupe)
{
        ifstream in("duom.txt");
        if(!in)
        {
            cout<<"Neatsidaro failas"<<endl;
            terminate();
        }
        string eil;
        while(getline(in, eil))
        {
            istringstream line(eil);
            line>>laik.var>>laik.pav;
            double grade;
            while(line>>grade)
                laik.pazymiai.push_back(grade);
            if(laik.pazymiai.size()!=0)
            {
                laik.exam=laik.pazymiai[laik.pazymiai.size()-1];
                laik.pazymiai.pop_back();
            }
            grupe.push_back(laik);
            laik.pazymiai.clear();
            laik.exam=0;
        }
}
double average(duom given)
{
    double sum=0.0;
    for(auto i:given.pazymiai)
    {
        sum+=i;
    }
    return sum/given.pazymiai.size();
}
double median(duom given)
{
    if(given.pazymiai.size()%2==1)
    {
        return given.pazymiai[((given.pazymiai.size()/2)+1)-1];
    }
    else
    {
        double ats=0.0;
        ats=given.pazymiai[given.pazymiai.size()/2-1];
        ats+=given.pazymiai[given.pazymiai.size()/2+1-1];
        ats/=2;
        return ats;
    }
}

#endif // TEMPLATE_H_INCLUDED


