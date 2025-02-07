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

#endif // TEMPLATE_H_INCLUDED


