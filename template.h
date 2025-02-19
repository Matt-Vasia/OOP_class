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
#include "std.h"

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

void menu_with_read(vector <duom> &grupe);
double average(duom given);
double median(duom given);
void random(vector <duom> &grupe, int m);
void random_full(vector <duom> &grupe);
void read_file(vector <duom> &grupe);
void read_half(vector <duom> &grupe);
void vid_med_calc(vector <duom> &grupe);
void sorting(vector <duom> &grupe);
void print(vector <duom> &grupe);

#endif


