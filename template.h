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
using std::stringstream;
using std::terminate;

struct duom
{
    string var="test";
    string pav="test";
    vector<int> pazymiai;
    int exam;
    double vid=0, med=0;
};

void read(duom &laik, vector <duom> &grupe)
{
        char line[256];
        cin.getline(line, 256);
        stringstream s;
        s << line;
        s >> laik.var >> laik.pav;
        if(!s)
        {
            cout<<"Duomenų failas neatsidaro"<<endl;
            terminate();
        }
        while(s)
        {
            int temp;
            s>>temp;
            laik.pazymiai.push_back(temp); //saug 0-10 pazymiai
        }
        laik.exam=laik.pazymiai[laik.pazymiai.size()-1];
        laik.pazymiai.pop_back();
        grupe.push_back(laik);
    }
}

#endif // TEMPLATE_H_INCLUDED


