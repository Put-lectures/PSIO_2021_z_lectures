#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;
struct osoba
{
    string imie;
    string nazwisko;
    int wiek;
};

void example_iterators()
{
    //kod działa dla kontenera vector i list
    list<double> tab = {1.5, 5, 2.4, 1, 5};
    // vector<double> tab = {1.5, 5, 2.4, 1, 5};

    for (auto itr = tab.begin(); itr != tab.end();) {
        cout << *itr << endl;
        if (*itr == 5.0) {
            itr = tab.emplace(itr, -1);
            itr++;
        }
        if (*itr > 2) {
            itr = tab.erase(itr);
        } else {
            itr++;
        }
    }
}

//zastosowanie predykatów

void example_copy_elements()
{
       list<double> tab = {1.5, 5, 2.4, 1, 5};
       vector<double> tab_vect;
       copy(tab.begin(), tab.end(), std::back_inserter(tab_vect));
       
       for (auto el : tab) {
        cout << el<< endl;
    }
}
bool pred(const double &el)
{
    //    if (el > 2)
    //        return true;
    //    else
    //        return false;
    return el > 2;
}

class threshold_pred
{
    double th_;

public:
    void set_th(double th) { th_ = th; }
    bool operator()(const double &el) { return el > th_; }
};

void example_predicate_function()
{
    list<double> tab = {1.5, 5, 2.4, 1, 5};

    cout << count_if(tab.begin(), tab.end(), pred);
}
void example_predicate_object()
{
    list<double> tab = {1.5, 5, 2.4, 1, 5};
    threshold_pred pred_object;
    pred_object.set_th(2);
    cout << count_if(tab.begin(), tab.end(), pred_object);
}

void example_lambda_exp()
{
    list<double> tab = {1.5, 5, 2.4, 1, 5};
    threshold_pred pred_object;
    pred_object.set_th(2);
    double th = 3.0;
    cout << count_if(tab.begin(), tab.end(), [th](const double &val) { return val > th; });
}
void intro_iterators_insert_remove_elements()
{
    //kod działa zarówno dla list jak i vector
    list<double> tab = {1.5, 5, 2.4, 1, 5};
    //    vector<double> tab = {1.5, 5, 2.4, 1, 5};

    for (auto itr = tab.begin(); itr != tab.end();) {
        //        cout << *itr << endl;
        if (*itr == 5.0) {
            itr = tab.emplace(itr, -1);
            itr++;
        }
        if (*itr > 2) {
            itr = tab.erase(itr);
        } else {
            itr++;
        }
    }
}
void algorithms_intro()
{
    //kopiowanie elementów z jednego kontenera do drugiego
    list<double> lista = {1.5, 5, 2.4, 1, 5};

    vector<double> tab_vect(lista.begin(), lista.end());
    copy(lista.begin(), lista.end(), std::back_inserter(tab_vect));

    //sortowanie listy
    lista.sort();

    //sortowanie wektora
    sort(tab_vect.begin(), tab_vect.end());

    //algorytmy find i count
    auto itr = tab_vect.begin();
    //    itr++;
    do {
        itr = find(itr, tab_vect.end(), 5.0);
        itr = tab_vect.erase(itr);
    } while (itr != tab_vect.end()); //}
    cout << count(tab_vect.begin(), tab_vect.end(), 5.0);
}
int main()
{
    //Przykłady z zajęć do odkomentowania
    //intro_iterators_insert_remove_elements();
    //algorithms_intro();
    //example_predicate_object();
    //example_predicate_function();
    //example_lambda_exp();

    //sortowanie kontenerów z typami użytkownika
    vector<osoba> osoby = {{"Potr", "Kaczmarek", 40}, {"Jan", "Nowak", 30}, {"John", "Smith", 20}};
    sort(osoby.begin(), osoby.end(), [](const osoba &o1, const osoba &o2) {
        return o1.wiek > o2.wiek;
    });

    for (auto &el : osoby) {
        cout << el.imie << el.nazwisko << el.wiek << endl;
    }
    return 0;
}
