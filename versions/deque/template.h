#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <deque>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>
#include <stdexcept>
#include <execution>
#include "std.h"

using namespace std;

struct duom {
    string var;
    string pav;
    vector<double> pazymiai;
    double exam = 0;
    double vid_med = 0;
    double mark = 0;
};

const vector<string> vardai = {"Petras", "Jonas", "Marius", "Juozas", "Vytas", "Matas", "Rimas", "Simas", "Antanas", "Domas", "Herkus", "Benas", "Kajus", "Aistas", "Lukas", "Adomas", "Tauras", "Karolis", "Markas", "Jokubas", "Tadas", "Darius", "Mantas", "Domantas", "Paulius", "Justas", "Mindaugas", "Urte"};

const char* test_file_location = TEST_FILE_LOCATION; //CMake version
//const char* test_file_location = "../../test_files/"; ///Manual complilation version (debug)

void menu(deque<duom> &grupe);
void read(deque<duom> &grupe);
void read_file(deque<duom> &grupe, string filename);
void read_names_only(deque<duom> &grupe);
void random(deque<duom> &grupe, int m);
void random_full(deque<duom> &grupe, int record_amount, int mark_amount);
void print_data_to_file(deque<duom> &grupe, int mark_amount, string filename);
void print_answers(deque<duom> &grupe);
char check_menu();
void vid_med_calc(deque<duom> &grupe);
double average(duom given);
double median(duom given);
void sorting(deque<duom> &grupe, char rule);
bool compare(string a, string b, string rule);
void print_answers_to_file(deque<duom> &grupe, string filename);
void sort_file_by_grades(deque<duom> &grupe, string filename);

#endif