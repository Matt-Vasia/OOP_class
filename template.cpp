#include "template.h"


char check_menu()
{
    string input;
    char check;
    do
    {
        cout<<"Noredami uzbaigti ivedima iveskite 'F'"<<endl;
        cout<<"Noredami testi ivedima iveskite 'T'"<<endl;
        getline(cin, input);
        if(input.size()>1 or input.size()==0)
        {
            cout<<"Netinkama ivestis"<<endl;
            continue;
        }
        check=toupper(input[0]);
    } while (check!='F' and check!='T');
    return check;
}
void read(vector <duom> &grupe)
{
    bool con=1;
    char check;
    duom local;
    while(con)
    {
        cout<<"Iveskite varda ir pavarde"<<endl;
        cin>>local.var>>local.pav;
        cout<<"Iveskite pazymius (paskutinis pazymys is egzamino) (iveskite -1 norint uzbaigti)"<<endl;
        int temp;
        while(true)
        {
            try
            {
                cin>>temp;
                if (cin.fail() || temp < -1 || temp > 10)
                {
                    cin.clear();
                    throw invalid_argument("Netinkama ivestis");
                }
            }
            catch(const exception& e)
            {
                cerr << e.what() << '\n';
                continue;
            }
            if (temp == -1)
                break;
            else
                local.pazymiai.push_back(temp);
        }
        try
        {
            if(local.pazymiai.size()==0)
                throw invalid_argument("Neivesti pazymiai");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            terminate();
        }
        local.exam=local.pazymiai.back();
        local.pazymiai.pop_back();
        grupe.push_back(local);
        local.pazymiai.clear();
        local.exam=0;
        cout<<"Noredami uzbaigti ivedima iveskite 0"<<endl;
        cin>>check;
        if(check=='0')
            con=0;
    }
}

void read_names_only(vector <duom> &grupe)
{
    bool con=1;
    char check;
    string input_check;
    duom local;
    while(con)
    {
        cout<<"Iveskite varda ir pavarde"<<endl;
        cin>>local.var>>local.pav;
        grupe.push_back(local);
        if(check_menu()=='F')
            con=0;
    }
}
void read_file(vector <duom> &grupe)
{
    duom laik;
    ifstream in("kursiokai.txt");
    try
    {
        if(!in)
        {
            throw invalid_argument("Failas nerastas");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        terminate();
    }
    stringstream ss;
    ss<<in.rdbuf();
    in.close();
    string eil;
    try
    {
        if(!getline(ss, eil))
            throw invalid_argument("Failas tuscias");
        while(getline(ss, eil))
        {
            stringstream line(eil);
            line>>laik.var>>laik.pav;
            double grade;
            while(line>>grade)
                laik.pazymiai.push_back(grade);
            if(laik.pazymiai.size()==0)
                throw invalid_argument("Truksta pazymiu");
            laik.exam=laik.pazymiai.back();
            laik.pazymiai.pop_back();
            grupe.push_back(laik);
            laik.pazymiai.clear();
            laik.exam=0;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        terminate();
    }
    grupe.shrink_to_fit();
    for (auto& student : grupe)
        student.pazymiai.shrink_to_fit();
}
double average(duom given)
{
    try
    {
        if(given.pazymiai.empty())
            throw invalid_argument("Truksta pazymiu");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        terminate();
    }
    double sum=0.0;
    for(auto i:given.pazymiai)
    sum+=i;
    return sum/given.pazymiai.size();
}
double median(duom given)
{
    try
    {
        if(given.pazymiai.size()==0)
            throw invalid_argument("Truksta pazymiu");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        terminate();
    }
    if(given.pazymiai.size()%2==1)
    {
        return given.pazymiai[((given.pazymiai.size()/2)+1)-1];
    }
    else
    {
        double ats=0.0;
        ats=given.pazymiai[given.pazymiai.size()/2-1];
        ats+=given.pazymiai[given.pazymiai.size()/2+1-1];
        ats/=2;
        return ats;
    }

}
void random(vector <duom> &grupe, int m)
{
    duom laik;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 10);
    uniform_int_distribution<int> dist2(5, 20);
    int n = dist2(mt);
    for(int j=0; j<m; j++)
    {
        for(int i=0; i<n; i++)
            laik.pazymiai.push_back(dist(mt));
        laik.exam=(dist(mt));
        grupe[j].pazymiai=laik.pazymiai;
        grupe[j].exam=laik.exam;
        laik.pazymiai.clear();
    }
}
void random_full(vector <duom> &grupe)
{
    duom laik;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 10);
    uniform_int_distribution<int> dist2(5, 20);
    uniform_int_distribution<int> dist3(0, 27); //random vardu generavimas
    uniform_int_distribution<int> dist4(65, 86); //ASCII values for uppercase letters
    int n=dist2(mt); //pazymiu skaicius
    int m=dist2(mt); //studentu skaicius
    for(int j=0; j<m; j++)
    {
        laik.var=vardai.at(dist3(mt));
        laik.pav=dist4(mt);
        laik.pav+=".";
        for(int i=0; i<n; i++)
            laik.pazymiai.push_back(dist(mt));
        laik.exam=(dist(mt));
        grupe.push_back(laik);
        laik.pazymiai.clear();
    }
}
void menu_with_read(vector <duom> &grupe)
{
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
        read_file(grupe);    
    else if (rule=='3')
    {
        read_names_only(grupe);
        random(grupe, grupe.size());
    }
    else if (rule=='4')
        random_full(grupe);
    else if (rule=='5')
    {
        cout<<"Darbas baigtas"<<endl;
        terminate();
    }
}
void vid_med_calc(vector <duom> &grupe)
{
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
}
bool compare(string a, string b, string rule)
{
    if(a.rfind(rule, 0)==0 and b.rfind(rule, 0)==0)
        return stoi(a.substr(rule.length()))<stoi(b.substr(rule.length()));
    else
        return a<b;
}
void sorting(vector <duom> &grupe)
{
    char rule;
    do
    {
        cout<<"Noredami surusiuoti pagal varda, spauskite '1'"<<endl;
        cout<<"Noredami surusiuoti pagal pavarde, spauskite '2'"<<endl;
        cout<<"Noredami surusiuoti pagal galutini bala, spauskite '3'"<<endl;
        cin>>rule;
        rule=tolower(rule);
    } while(rule!='1' and rule!='2' and rule!='3');
    if(rule=='1')
        sort(grupe.begin(), grupe.end(), [](duom a, duom b){return compare(a.var, b.var, "Vardas");});
    else if(rule=='2')
        sort(grupe.begin(), grupe.end(), [](duom a, duom b){return compare(a.pav, b.pav, "Pavarde");});
    else if(rule=='3')
        sort(grupe.begin(), grupe.end(), [](duom a, duom b){return a.mark>b.mark;});
}
void print(vector <duom> &grupe)
{
    stringstream ss;
    ss << left << fixed << setprecision(2) << setw(20) << "Vardas"<<setw(20)<<"Pavarde"<<setw(20)<<"Galutinis"<<endl;
    ss << "------------------------------------------------------------" << endl;
    for(auto i:grupe)
    {
        ss << left << fixed << setprecision(2) << setw(20) << i.var << " " << setw(20) << i.pav << " " << setw(20) << i.mark << endl;
    }
    cout<<ss.str();
}