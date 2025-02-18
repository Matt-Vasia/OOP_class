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
        cout<<"Jei duomenis norite ivesti patys (terminalas), spauskite '1'"<<endl;
        cout<<"Jei duomenis norite ivesti patys (kursiokai.txt), spauskite '2'"<<endl;
        cout<<"Jei norite sugeneruoti mokinio pazymius atsitiktinai, spauskite '3'"<<endl;
        cout<<"Jei norite sugeneruoti mokinio pazymius ir vardus atsitiktinai, spauskite '4'"<<endl;
        cout<<"Jei norite baigti darba, spauskite '5'"<<endl;
        cin>>rule;
    } while(rule!='1' and rule!='2' and rule!='3' and rule!='4' and rule!='5');
    if(rule=='1')
        read(grupe);
    else if (rule=='2')
    {
        read_file(grupe);
    }        
    else if (rule=='3')
    {
        read_half(grupe);
        random(grupe, grupe.size());
    }
    else if (rule=='4')
        random_full(grupe);
    else if (rule=='5')
        return 0;
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
            i.vid_med=average(i);
    }
    else
    {
        for(auto &i:grupe)
            i.vid_med=median(i);
    }
    for(auto &i:grupe)
    {
        i.mark=0.4*i.vid_med+0.6*i.exam;
    }
    ///
    do
    {
        cout<<"Noredami surusiuoti pagal varda, spauskite '1'"<<endl;
        cout<<"Noredami surusiuoti pagal pavarde, spauskite '2'"<<endl;
        cout<<"Noredami surusiuoti pagal galutini bala, spauskite '3'"<<endl;
        cin>>rule;
        rule=tolower(rule);
    } while(rule!='1' and rule!='2' and rule!='3');
    if(rule=='1')
        sort(grupe.begin(), grupe.end(), [](duom a, duom b){return a.var<b.var;});
    else if(rule=='2')
        sort(grupe.begin(), grupe.end(), [](duom a, duom b){return a.pav<b.pav;});
    else if(rule=='3')
        sort(grupe.begin(), grupe.end(), [](duom a, duom b){return a.mark>b.mark;});
    ///
    for(auto i:grupe)
    {
        cout << left << fixed << setprecision(2) << setw(20) << i.var << " " << setw(20) << i.pav << " " << setw(20) << i.mark << endl;
    }
    return 0;
}




