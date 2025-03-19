#include "template.cpp"

int main()
{
    list<duom> grupe; // Changed from vector to list
    
    menu(grupe);
     vid_med_calc(grupe);
     sorting(grupe, '\0');
     print_answers(grupe);
    
    return 0;
}