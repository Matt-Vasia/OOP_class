#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib> //rand lib
#include <ctime> //time lib
#include <algorithm>

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
using std::sort;
using std::setw;

struct duom
{
    string var="test";
    string pav="test";
    vector<int> pazymiai;
    int exam=0;
    double vid_med=0;
    double mark;
};

vector<string> vardai={
"Matas",
"Tomas",
"Andrius",
"Daumantas",
"Jonas",
"Petras",
"Kestas",
"Paulius",
"Juozas",
"Rokas"};

void read(vector <duom> &grupe)
{
    bool con=1;
    char check;
    duom local;
    while(con)
    {
        cout<<"Iveskite varda ir pavarde"<<endl;
        cin>>local.var>>local.pav;
        cout<<"Iveskite pazymius uz namu darbus (iveskite -1 norint uzbaigti)"<<endl;
        int temp;
        while(true)
        {
            cin>>temp;
            if (cin.fail() || temp < -1 || temp > 10)
            {
                cin.clear();
                cout << "Netinkama ivestis. Iveskite pazymi tarp 1 ir 10 arba -1 norint uzbaigti" << endl;
            }
            else if (temp == -1)
                break;
            else
                local.pazymiai.push_back(temp);
        }
        if(local.pazymiai.size()!=0)
        {
            local.exam=local.pazymiai[local.pazymiai.size()-1];
                local.pazymiai.pop_back();
        }
        grupe.push_back(local);
        local.pazymiai.clear();
        local.exam=0;
        cout<<"Noredami uzbaigti darba iveskite 0"<<endl;
        cin>>check;
        if(check=='0')
            con=0;
    }
}
void read_half(vector <duom> &grupe)
{
    bool con=1;
    char check;
    duom local;
    while(con)
    {
        cout<<"Iveskite varda ir pavarde"<<endl;
        cin>>local.var>>local.pav;
        grupe.push_back(local);
        cout<<"Noredami uzbaigti darba iveskite 0"<<endl;
        cin>>check;
        if(check=='0')
            con=0;
    }
}
void read_file(vector <duom> &grupe)
{
    duom laik;
    ifstream in("kursiokai.txt");
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
    if(!given.pazymiai.size())
        return 0;
    return sum/given.pazymiai.size();
}
double median(duom given)
{
    if(given.pazymiai.size()==0)
        return 0;
    else if(given.pazymiai.size()%2==1)
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
void random(vector <duom> &grupe, int m)
{
    duom laik;
    int n=5; //pazymiu skaicius
    srand(time(0));
    for(int j=0; j<m; j++)
    {
        for(int i=0; i<n; i++)
            laik.pazymiai.push_back(1 + (rand() % 10));
        laik.exam=(1 + (rand() % 10));
        grupe[j].pazymiai=laik.pazymiai;
        grupe[j].exam=laik.exam;
        laik.pazymiai.clear();
    }
}
void random_full(vector <duom> &grupe)
{
    duom laik;
    int n=5; //pazymiu skaicius
    int m=5; //studentu skaicius
    srand(time(0));
    for(int j=0; j<m; j++)
    {
        laik.var=vardai.at((rand() % 10));
        laik.pav=65 + (rand() % 26);
        for(int i=0; i<n; i++)
            laik.pazymiai.push_back(1 + (rand() % 10));
        laik.exam=(1 + (rand() % 10));
        grupe.push_back(laik);
        laik.pazymiai.clear();
    }
}
#endif // TEMPLATE_H_INCLUDED


