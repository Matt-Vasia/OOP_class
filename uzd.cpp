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
    ///
    char rule;
    do
    {
        cout<<"Noredami skaiciuoti naudojant vidurki parasykite 'v'"<<endl;
        cout<<"Noredami skaiciuoti naudojant mediana parasykite 'm'"<<endl;
        cin>>rule;
        rule=tolower(rule);
    } while(rule!='v' and rule!='m');
    if(rule=='v')
    {
        for(auto &i:grupe)
        {
            i.mark=0.4*i.vid+0.6*i.exam;
        }
    }
    else
    {
        for(auto &i:grupe)
        {
            i.mark=0.4*i.med+0.6*i.exam;
        }
    }
    ///
    for(auto i:grupe)
    {
        cout<<fixed<<setprecision(2)<<i.var<<" "<<i.pav<<" "<<i.mark<<endl;
    }
    return 0;
}




