#include "template.h"

double average(duom given, int n);
double median(duom given);

int main(){
    ifstream in("duom.txt");
    if(!in)
    {
        cout<<"Neatsidaro failas"<<endl;
        terminate();
    }
    int n, m;
    in>>n>>m;
    duom grupe[m];
    for(int i=0; i<m; i++)
    {
        in>>grupe[i].var>>grupe[i].pav;
        for(int j=0; j<n; j++)
            in>>grupe[i].C[j];
        in>>grupe[i].exam;
    }
    for(int i=0; i<m; i++)
    {
        grupe[i].vid=average(grupe[i], n);
        grupe[i].med=median(grupe[i], n);
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




