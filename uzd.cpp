#include "template.h"

void read(vector <duom> &grupe);
double average(duom given);
double median(duom given);

int main(){
    vector <duom> grupe;
    char rule;
    do
    {
        cout<<"Jei norite sugeneruoti mokinio pazymius atsitiktinai, spauskite 'Y'"<<endl;
        cout<<"Jei mokinio pazymius jau turite, spauskite 'N'"<<endl;
        cin>>rule;
        rule=tolower(rule);
    } while(rule!='y' and rule!='n');
    if(rule=='n')
        read(grupe);
    else
        random(grupe);
    for(auto &i:grupe)
    {
        i.vid=average(i);
        i.med=median(i);
    }
    ///
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




