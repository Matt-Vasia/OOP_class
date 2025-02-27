#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime> //time lib
#include <algorithm>
#include <random>
#include <string>
#include <chrono>
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
"Rokas",
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

void menu(vector <duom> &grupe);
void read(vector <duom> &grupe);
void read_file(vector <duom> &grupe, string filename);
void read_names_only(vector <duom> &grupe);
void sort_file_by_grades(vector <duom> &grupe, string filename);
void random(vector <duom> &grupe, int m);
void random_full(vector <duom> &grupe, int record_amount, int mark_amount);
void print_data_to_file(vector <duom> &grupe, int mark_amount, string filename);
void print_answers_to_file(vector <duom> &grupe, string filename);
void print_answers(vector <duom> &grupe);
///
/// 
char check_menu();
void vid_med_calc(vector <duom> &grupe);
bool compare(string a, string b, string rule);
void sorting(vector <duom> &grupe, char rule);
double average(duom given);
double median(duom given);

#endif


