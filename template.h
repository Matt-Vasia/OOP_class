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
#include <random>
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
"Tomas",
"Andrius",
"Daumantas",
"Jonas",
"Petras",
"Kestas",
"Paulius",
"Juozas",
"Rokas"
"Adomas",
"Amelija",
"Motiejus",
"Jonas",
"Olivija",
"Lukas",
"Emilija",
"Jokubas",
"Adele",
"Benas",
"Ema",
"Dominykas",
"Liepa",
"Nojus",
"Ugne",
"Matas",
"Lukne",
"Markas",
"Barbora",
"Augustas"
};

char check_menu();
void menu_with_read(vector <duom> &grupe);
double average(duom given);
double median(duom given);
void random(vector <duom> &grupe, int m);
void random_full(vector <duom> &grupe, int record_amount, int mark_amount);
void read_file(vector <duom> &grupe);
void read_half(vector <duom> &grupe);
void vid_med_calc(vector <duom> &grupe);
void sorting(vector <duom> &grupe);
void print_data_to_file(vector <duom> &grupe, int mark_amount);
void print_answers(vector <duom> &grupe);

#endif


