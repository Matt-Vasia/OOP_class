#include "template.h"

void read(duom &laik, vector <duom> &grupe);

int main(){
    duom laik;
    vector <duom> grupe;
    read(laik, grupe);
    for(auto i:grupe)
    {
        cout<<i.var<<" "<<i.pav<<" ";
        for(auto j: i.pazymiai)
        {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    return 0;
}




