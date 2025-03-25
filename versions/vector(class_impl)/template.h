#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <string>
#include <chrono>
#include <execution>
#include "std.h"

struct temp
{
    string var="test";
    string pav="test";
    vector<int> pazymiai;
    int exam=0;
    double vid_med=0;
    double mark;
};


class duom
{
    private:
        string var;
        string pav;
        vector<int> pazymiai;
        int exam;
        double vid_med;
        double mark;
    public:
        duom(temp a)
        {
            this->var=a.var;
            this->pav=a.pav;
            this->pazymiai=a.pazymiai;
            this->exam=a.exam;
            this->vid_med=a.vid_med;
            this->mark=a.mark;
        }
        string getVar()
        {
            return var;
        }
        string getPav()
        {
            return pav;
        }
        int getPazymiai_at(int i)
        {
            return pazymiai[i];
        }
        vector<int> getPazymiai()
        {
            return pazymiai;
        }
        int getExam()
        {
            return exam;
        }
        double getVid_med()
        {
            return vid_med;
        }
        double getMark()
        {
            return mark;
        }
        void setPazymiai(vector<int> pazymiai)
        {
            this->pazymiai=pazymiai;
        }
        void setExam(int exam)
        {
            this->exam=exam;
        }
        void setVid_med(double vid_med)
        {
            this->vid_med=vid_med;
        }
        void setMark(double mark)
        {
            this->mark=mark;
        }
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

const string test_file_location = TEST_FILE_LOCATION; //CMake version
//const string test_file_location = "../../test_files/"; ///Manual complilation version (debug)

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


