#include "template.h"

using namespace std;

void menu(vector <duom> &grupe)
{
    char rule;
    do
    {
        cout<<"Jei duomenis norite ivesti patys (terminalas), spauskite '1'"<<endl;
        cout<<"Jei duomenis norite ivesti patys (kursiokai.txt), spauskite '2'"<<endl;
        cout<<"Jei norite sugeneruoti mokinio pazymius atsitiktinai, spauskite '3'"<<endl;
        cout<<"Jei norite sugeneruoti mokinio pazymius ir vardus atsitiktinai (konsoleje), spauskite '4'"<<endl;
        cout<<"Jei norite sugeneruoti mokinio pazymius ir vardus atsitiktinai (failuose), spauskite '5'"<<endl;
        cout<<"Jei norite suruosiuoti mokinius pagal ju pazymius is failo, spauskite '6'"<<endl;
        cout<<"Jei norite baigti darba, spauskite '7'"<<endl;
        cin>>rule;
    } while(rule!='1' && rule!='2' && rule!='3' && rule!='4' && rule!='5' && rule!='6' && rule!='7');
    if(rule=='1')
        read(grupe);
    else if (rule=='2')
    {
        grupe.reserve(1000);
        read_file(grupe, "kursiokai.dat");
        grupe.shrink_to_fit();
    }   
    else if (rule=='3')
    {
        grupe.reserve(1000);
        read_names_only(grupe);
        random(grupe, grupe.size());
        grupe.shrink_to_fit();
    }
    else if (rule=='4')
    {
        random_full(grupe, 10, 5);
    }
    else if (rule=='5')
    {
        grupe.reserve(10000000);
        auto start = chrono::high_resolution_clock::now();
        random_full(grupe, 1000, 5);
        print_data_to_file(grupe, 5, "kursiokai_1000.dat");
        auto end = chrono::high_resolution_clock::now();
        cout << "1 failas sugeneruotas per: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " sec" << endl;cout << "1 failas sugeneruotas per: " << chrono::duration_cast<chrono::duration<double>>(end - start).count() << " sec" << endl;start = chrono::high_resolution_clock::now();
        random_full(grupe, 10000, 5);
        print_data_to_file(grupe, 5, "kursiokai_10000.dat");
        end = chrono::high_resolution_clock::now();
        cout << "2 failas sugeneruotas per: " << chrono::duration_cast<chrono::duration<double>>(end - start).count() << " sec" << endl;
        start = chrono::high_resolution_clock::now();
        random_full(grupe, 100000, 5);
        print_data_to_file(grupe, 5, "kursiokai_100000.dat");
        end = chrono::high_resolution_clock::now();
        cout << "3 failas sugeneruotas per: " << chrono::duration_cast<chrono::duration<double>>(end - start).count() << " sec" << endl;
        start = chrono::high_resolution_clock::now();
        random_full(grupe, 1000000, 5);
        print_data_to_file(grupe, 5, "kursiokai_1000000.dat");
        end = chrono::high_resolution_clock::now();
        cout << "4 failas sugeneruotas per: " << chrono::duration_cast<chrono::duration<double>>(end - start).count() << " sec" << endl;
        start = chrono::high_resolution_clock::now();
        random_full(grupe, 10000000, 5);
        print_data_to_file(grupe, 5, "kursiokai_10000000.dat");        
        end = chrono::high_resolution_clock::now();
        cout << "5 failas sugeneruotas per: " << chrono::duration_cast<chrono::duration<double>>(end - start).count() << " sec" << endl;
        // Pause before exiting
        cout << "Press Enter to continue..." << std::endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        exit(0);
    }
     else if (rule=='6')
    {
        string filename;
        cout<<"Iveskite norimo nuskaityti failo (.dat) pavadinima pvz. (vardai, duomenys, ...)"<<endl;
        cin>>filename;
        sort_file_by_grades(grupe, filename);
        // Pause before exiting
        cout << "Press Enter to continue..." << std::endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        exit(0);
    }
    else if (rule=='7')
    {
        cout<<"Darbas baigtas"<<endl;
        exit(0);
    }
}
void read(vector <duom> &grupe)
{
    bool con=1;
    char check;
    temp local;
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
        ///
        duom to_push(local);
        grupe.push_back(to_push);
        ///
        local.pazymiai.clear();
        local.exam=0;
        cout<<"Noredami uzbaigti ivedima iveskite 0"<<endl;
        cin>>check;
        if(check=='0')
            con=0;
    }
}
void read_file(vector <duom> &grupe, string filename)
{
    ifstream in(filename);
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

    in.seekg(0, ios::end);///pointeris i gala
    streamsize size = in.tellg();///nustatomas failo dydis
    in.seekg(0, ios::beg);///pointeris i pradzia

    try
    {
        if(size>100000000)
            grupe.reserve(10000000);
        else if(size>10000000)
            grupe.reserve(1000000);
        else
            grupe.reserve(100000);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Nepavyko rezervuoti atminties" << '\n';
    }
    

    string header_line;
    std::getline(in, header_line);
    ///
    duom laik;
    try
    {
        while(in>>laik)
        {
            grupe.push_back(std::move(laik));
        }
    }
    catch(const std::exception& e){}
    grupe.shrink_to_fit();
}
void read_names_only(vector <duom> &grupe)
{
    bool con=1;
    temp local;
    while(con)
    {
        cout<<"Iveskite varda ir pavarde"<<endl;
        cin>>local.var>>local.pav;
        ///
        duom to_push(local);
        grupe.push_back(std::move(to_push));
        ///
        if(check_menu()=='F')
            con=0;
    }
}
void sort_file_by_grades(vector<duom> &grupe, string filename) {
    
    // Start timing the entire process
    //auto total_start = chrono::high_resolution_clock::now();

    // Timing file reading
    auto start = chrono::high_resolution_clock::now();
    read_file(grupe, test_file_location + filename + ".dat"); 
    auto end = chrono::high_resolution_clock::now();
    auto read_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // vid_med_calc() is not timed
    //start = chrono::high_resolution_clock::now();
    vid_med_calc(grupe);
    //end = chrono::high_resolution_clock::now();
    //auto excluded_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Timing sorting
    start = chrono::high_resolution_clock::now();

    sorting(grupe, '3'); // Sorting by final grade

    end = chrono::high_resolution_clock::now();
    auto sort_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();



    cout<<"Kuria strategija norite naudoti?"<<endl;
    char rule='0';
    while(rule!='1' && rule!='2' && rule!='3')
    {
        cout<<"Jei norite naudoti 1 strategija, spauskite '1'"<<endl;
        cout<<"Jei norite naudoti 2 strategija, spauskite '2'"<<endl;
        cout<<"Jei norite naudoti 3 strategija, spauskite '3'"<<endl; 
        cin>>rule;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    auto splitting_time = 0;
    if(rule=='1')
    {
            //1 strategija
            vector<duom> blogi;
            vector<duom> geri;
            start = chrono::high_resolution_clock::now();
            for(auto &i:grupe)
            {
                if(i.getMark()<5)
                    blogi.push_back(i);
                else
                    geri.push_back(i);
            }
            end = chrono::high_resolution_clock::now();
            splitting_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            print_answers_to_file(geri, test_file_location + "/../output_file/" + filename + "_kietekai.dat");
            print_answers_to_file(blogi, test_file_location + "/../output_file/" + filename + + "_vargsiukai.dat");
            cout<<"printed"<<endl;
    }
    else if(rule=='2')
    {
            //2 strategija
            vector<duom> blogi;
            // Splitting the vector into two
            start = chrono::high_resolution_clock::now();

            auto it = std::remove_if(grupe.begin(), grupe.end(), [](duom& student) {
                return student.getMark() >= 5;
            });

            blogi.assign(it, grupe.end());
            grupe.erase(it, grupe.end());

            end = chrono::high_resolution_clock::now();
            splitting_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            print_answers_to_file(grupe, test_file_location + "/../output_file/" + filename + "_kietekai.dat");
            print_answers_to_file(blogi, test_file_location + "/../output_file/" + filename + + "_vargsiukai.dat");
    }
    else if(rule=='3')
    {
            //3 strategija
            vector<duom> blogi;
            // Splitting the vector into two
            start = chrono::high_resolution_clock::now();
            auto it = partition(grupe.begin(), grupe.end(), [](duom& student) {
                return student.getMark() >= 5;
            });

            blogi.assign(it, grupe.end());
            grupe.erase(it, grupe.end());

            end = chrono::high_resolution_clock::now();
            auto splitting_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            print_answers_to_file(grupe, test_file_location + "/../output_file/" + filename + "_kietekai.dat");
            print_answers_to_file(blogi, test_file_location + "/../output_file/" + filename + + "_vargsiukai.dat");
    }

    // Calculate and display total time
    /*
    auto total_end = chrono::high_resolution_clock::now();
    auto raw_time = chrono::duration_cast<chrono::milliseconds>(total_end - total_start).count();
    auto total_time = raw_time - excluded_time;
    */
    
    // Display summary of times
    cout << "\n\nSantrauka:" << endl;
        cout << "Skaitymas: " << float(read_time) / 1000 << " s "<< endl;
        cout << "Rusiavimas: " << float(sort_time) / 1000 << " s "<< endl;
        cout << "Skaidymas: " << float(splitting_time) / 1000 << " s "<< endl;
        //cout << "Rasymas: " << float(write_time) / 1000 << " s "<< endl;
        //cout << "Is viso: " << float(total_time) / 1000 << " s" << endl;

}
void random(vector <duom> &grupe, int m)
{
    temp laik;
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
        grupe[j].setPazymiai(laik.pazymiai);
        grupe[j].setExam(laik.exam);
        laik.pazymiai.clear();
    }
}
void random_full(vector <duom> &grupe, int record_amount, int mark_amount)
{
    temp laik;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 10);
    uniform_int_distribution<int> dist3(0, 27); //random vardu generavimas
    uniform_int_distribution<int> dist4(65, 86); //ASCII values for uppercase letters
    grupe.clear();
    for(int j=0; j<record_amount; j++)
    {
        laik.var=vardai.at(dist3(mt));
        laik.pav=dist4(mt);
        laik.pav+=".";
        for(int i=0; i<mark_amount; i++)
            laik.pazymiai.push_back(dist(mt));
        laik.exam=(dist(mt));
        ///
        duom to_push(laik);
        grupe.push_back(to_push);
        ///
        laik.pazymiai.clear();
    }
}
void print_data_to_file(vector <duom> &grupe, int mark_amount, string filename)
{
    ofstream out(filename);
    stringstream ss;
    const int ss_size = 10000; //stringstream max eiluciu skaicius
    int count = 0;
    ///
    ss << left << fixed << setw(20) << "Vardas"<<setw(20)<<"Pavarde";
    for(int i=0; i<mark_amount; i++)
    {
        ss << setw(7) << "ND" + to_string(i+1);
    }
    ss << setw(10) << "Egzaminas" <<endl;
    ///
    for(auto i:grupe)
    {
        ss << setw(20) << i.getVar() << setw(20) << i.getPav();
        for(auto j:i.getPazymiai())
            ss << setw(7) << j;
        ss << setw(10) << i.getExam() << endl;
        count++; //eiluciu skaicius ss stringstreame
        if(count==ss_size)
        {
            out<<ss.str();
            ss.str("");
            count=0;
            ss.clear();
        }
    }
    if(count!=0) //likusiu eiluciu isvedimas
        out<<ss.str();
    out.close();
}
void print_answers_to_file(vector <duom> &grupe, string filename)
{
    ofstream out(filename);
    out << left << fixed << setw(20) << "Vardas"<<setw(20)<<"Pavarde"
    << fixed << setprecision(2) << setw(20) << "Galutinis" <<endl;
    ///
    for(auto i:grupe)
        out<<i;
    out.close();
}
void print_answers(vector <duom> &grupe)
{
    cout << left << fixed << setw(20) << "Vardas"<<setw(20)<<"Pavarde"
    << fixed << setprecision(2) << setw(20) << "Galutinis" <<endl;
    cout << "------------------------------------------------------------" << endl;
    ///
    for(auto i:grupe)
        cout<<i;
}
///
char check_menu()
{
    string input;
    char check;
    do
    {
        cout<<"Noredami uzbaigti ivedima iveskite 'F'"<<endl;
        cout<<"Noredami testi ivedima iveskite 'T'"<<endl;
        getline(cin, input);
        if(input.size()>1 || input.size()==0)
        {
            cout<<"Netinkama ivestis"<<endl;
            continue;
        }
        check=toupper(input[0]);
    } while (check!='F' && check!='T');
    return check;
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
    } while(rule!='v' && rule!='m');
    if(rule=='v')
    {
        for(auto &i:grupe)
            i.setVid_med(average(i));
    }
    else
    {
        for(auto &i:grupe)
            i.setVid_med(median(i));
    }
    for(auto &i:grupe)
    {
        i.setMark(0.4*i.getVid_med()+0.6*i.getExam());
    }
}
bool compare(const string a, const string b, string rule)
{
    if(a.rfind(rule, 0)==0 && b.rfind(rule, 0)==0)
        return stoi(a.substr(rule.length()))<stoi(b.substr(rule.length()));
    else
        return a<b;
}
void sorting(vector <duom> &grupe, char rule)
{
    while(rule!='1' && rule!='2' && rule!='3')
    {
        cout<<"Noredami surusiuoti pagal varda, spauskite '1'"<<endl;
        cout<<"Noredami surusiuoti pagal pavarde, spauskite '2'"<<endl;
        cout<<"Noredami surusiuoti pagal galutini bala, spauskite '3'"<<endl;
        cin>>rule;
        rule=tolower(rule);
    }
    if(rule=='1')
        std::stable_sort(std::execution::par, grupe.begin(), grupe.end(), [](const duom& a, const duom& b){return compare(a.getVar(), b.getVar(), "Vardas");});
    else if(rule=='2')
        std::stable_sort(std::execution::par, grupe.begin(), grupe.end(), [](const duom& a, const duom& b){return compare(a.getPav(), b.getPav(), "Vardas");});
    else if(rule=='3')
        std::stable_sort(std::execution::par, grupe.begin(), grupe.end(), [](const duom& a, const duom& b){return a.getMark() > b.getMark();});
}
double average(duom given)
{
    try
    {
        if(given.getPazymiai().empty())
            throw invalid_argument("Truksta pazymiu");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        terminate();
    }
    double sum=0.0;
    for(auto i:given.getPazymiai())
    sum+=i;
    return sum/given.getPazymiai().size();
}
double median(duom given)
{
    try
    {
        if(given.getPazymiai().size()==0)
            throw invalid_argument("Truksta pazymiu");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        terminate();
    }
    if(given.getPazymiai().size()%2==1)
    {
        return given.getPazymiai()[((given.getPazymiai().size()/2)+1)-1];
    }
    else
    {
        double ats=0.0;
        ats=given.getPazymiai()[given.getPazymiai().size()/2-1];
        ats+=given.getPazymiai()[given.getPazymiai().size()/2+1-1];
        ats/=2;
        return ats;
    }

}