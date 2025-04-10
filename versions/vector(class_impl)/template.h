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
        string var = "";
        string pav = "";
        vector<int> pazymiai;
        int exam = 0;
        double vid_med = 0.0;
        double mark = 0.0;
    public:
        duom(temp &a)
        {
            this->var=a.var;
            this->pav=a.pav;
            this->pazymiai=a.pazymiai;
            this->exam=a.exam;
            this->vid_med=a.vid_med;
            this->mark=a.mark;
        }
        duom(string var, string pav)
        {
            this->var=var;
            this->pav=pav;
        }
        duom(string var, string pav, vector<int> &pazymiai, int exam)
        {
            this->var=var;
            this->pav=pav;
            this->pazymiai=pazymiai;
            this->exam=exam;
        }        
        ~duom()
        {
            var.clear();
            pav.clear(); 
            pazymiai.clear();
            exam=0;
            vid_med=0;
            mark=0;
        }
    ///
        duom(const duom &to_copy)
        {
            this->var=to_copy.var;
            this->pav=to_copy.pav;
            this->pazymiai=to_copy.pazymiai;
            this->exam=to_copy.exam;
            this->vid_med=to_copy.vid_med;
            this->mark=to_copy.mark;
            
        }
        duom(duom &&to_move) noexcept
        {
            this->var=std::move(to_move.var);
            this->pav=std::move(to_move.pav);
            this->pazymiai=std::move(to_move.pazymiai);
            this->exam=to_move.exam;
            to_move.exam=0;
            this->vid_med=to_move.vid_med;
            to_move.vid_med=0;
            this->mark=to_move.mark;
            to_move.mark=0;
            ///move naudojam tik su elementais saugomais heap'e
        }
        //
        duom& operator=(const duom &to_copy)
        {
            if(this == &to_copy) return *this;
            //
            this->var=to_copy.var;
            this->pav=to_copy.pav;
            this->pazymiai=to_copy.pazymiai;
            this->exam=to_copy.exam;
            this->vid_med=to_copy.vid_med;
            this->mark=to_copy.mark;   
            return *this;
        }
        duom& operator=(duom &&to_move) noexcept
        {
            if(this == &to_move) return *this;
            //
            this->var=std::move(to_move.var);
            this->pav=std::move(to_move.pav);
            this->pazymiai=std::move(to_move.pazymiai);
            this->exam=to_move.exam;
            to_move.exam=0;
            this->vid_med=to_move.vid_med;
            to_move.vid_med=0;
            this->mark=to_move.mark;
            to_move.mark=0;
            ///move naudojam tik su elementais saugomais heap'e
            return *this;
        }
    ///
        friend std::ifstream& operator>>(std::ifstream& in, duom& student)
        {
            string eil;
            if (!std::getline(in, eil)) return in;

            stringstream line(eil);
            line>>student.var>>student.pav;

            double grade;
            student.pazymiai.clear();
            while(line>>grade)
                student.pazymiai.push_back(grade);

            if(student.pazymiai.size()==0)
                throw invalid_argument("Truksta pazymiu");

            student.exam=student.pazymiai.back();
            student.pazymiai.pop_back();

            return in;
        }
        friend std::ostream& operator<<(std::ostream& out, duom& student)
        {
            return out << left << fixed << setprecision(2) << setw(20) << student.var << " " << setw(20) << student.pav << " " << setw(20) << student.mark << endl;
        }
    ///
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
    /// 
        void setPazymiai(vector<int> &pazymiai)
        {
            this->pazymiai=pazymiai;
        }
        void addPazymiai(int grade)
        {
            if(grade>=1 && grade <=10)
                pazymiai.push_back(grade);
            else
                throw("Neteisingas pazymys");
        }
        void setExam(int exam)
        {
            if(exam>=1 && exam <=10)
                this->exam = exam;
            else
                throw("Neteisingas pazymys");
        }
        void setVid_med(double vid_med)
        {
            if(vid_med>=1 && vid_med <=10)
                this->vid_med=vid_med;
            else
                throw("Neteisingas pazymys");
        }
        void setMark(double mark)
        {
            if(mark>=1 && mark <=10)
                this->mark=mark;
            else
                throw("Neteisingas pazymys");
        }
    ///
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

//const string test_file_location = TEST_FILE_LOCATION; //CMake version
const string test_file_location = "../../test_files/"; ///Manual complilation version (debug)

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


