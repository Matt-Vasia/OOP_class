#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <list>  // Changed from vector to list
#include <fstream>
#include <sstream>
#include <random>
#include <stdexcept>
#include <chrono>
#include <execution>

using namespace std;

struct duom
{
    string var;
    string pav;
    list<double> pazymiai;  // Changed from vector to list
    double exam;
    double vid_med = 0;
    double mark = 0;
};

const vector<string> vardai = {"Petras", "Jonas", "Marius", "Juozas", "Vytas", "Matas", "Rimas", "Simas", "Antanas", "Domas", "Herkus", "Benas", "Kajus", "Aistas", "Lukas", "Adomas", "Tauras", "Karolis", "Markas", "Jokubas", "Tadas", "Darius", "Mantas", "Domantas", "Paulius", "Justas", "Mindaugas", "Urte"};

// Function declarations
void menu(list<duom> &grupe);
void read(list<duom> &grupe);
void read_file(list<duom> &grupe, string filename);
void read_names_only(list<duom> &grupe);
void random(list<duom> &grupe, int m);
void random_full(list<duom> &grupe, int record_amount, int mark_amount);
void sort_file_by_grades(list<duom> &grupe, string filename);
void print_data_to_file(list<duom> &grupe, int mark_amount, string filename);
void print_answers_to_file(list<duom> &grupe, string filename);
void print_answers(list<duom> &grupe);
char check_menu();
void vid_med_calc(list<duom> &grupe);
void sorting(list<duom> &grupe, char rule);
double average(duom given);
double median(duom given);
bool compare(string a, string b, string rule);

#endif