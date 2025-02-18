#include "template.h"

void read(vector <duom> &grupe);
double average(duom given);
double median(duom given);
void random(vector <duom> &grupe, int m);
void random_full(vector <duom> &grupe);

int main(){
    vector <duom> grupe;
    char rule;
    do
    {
        cout<<"Jei duomenis norite ivesti patys (duom.txt), spauskite '1'"<<endl;
        cout<<"Jei norite sugeneruoti mokinio pazymius atsitiktinai, spauskite '2'"<<endl;
        cout<<"Jei norite sugeneruoti mokinio pazymius ir vardus atsitiktinai, spauskite '3'"<<endl;
        cout<<"Jei norite baigti darba, spauskite '4'"<<endl;
        cin>>rule;
    } while(rule!='1' and rule!='2' and rule!='3' and rule!='4');
    if(rule=='1')
        read(grupe);
    else if (rule=='2')
    {
        read_half(grupe);
        random(grupe, grupe.size());
    }
    else if (rule=='3')
        random_full(grupe);
    else
        return 0;
    ///
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




