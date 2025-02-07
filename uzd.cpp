#include "template.h"

void read(duom &laik, vector <duom> &grupe);
double average(duom given);
double median(duom given);

int main(){
    duom laik;
    vector <duom> grupe;
    read(laik, grupe);
    for(auto &i:grupe)
    {
        i.vid=average(i);
        i.med=median(i);
    }

    return 0;
}




