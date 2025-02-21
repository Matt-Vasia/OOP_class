#include "template.h"

void menu_with_read(vector <duom> &grupe);
void vid_med_calc(vector <duom> &grupe);
void sorting(vector <duom> &grupe);
void print(vector <duom> &grupe);

int main(){
    vector <duom> grupe;
    ///
    menu_with_read(grupe);
    ///
    vid_med_calc(grupe);
    ///
    sorting(grupe);
    ///
    print(grupe);
    return 0;
}
