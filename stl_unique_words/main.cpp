#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>
using namespace std;
void tablica_asocjacyjna()
{
    std::ifstream is("/home/piotr/license.txt");
    map<string, int> words;

    //    words[ "las"];
    while (!is.eof()) {
        string text;
        is >> text;
        transform(text.begin(), text.end(), text.begin(), [](char z) { return tolower(z); });
        words[text]++;
    }
    for (auto &el : words)
        cout << el.first << " - " << el.second << endl;
}
void drzewo_binarne()
{
    std::string from, to;
    std::cin >> from >> to; // pobiera źródłową i docelową nazwę pliku

    std::ifstream is(from); // otwiera plik do odczytu
    std::ofstream os(to);   // otwiera plik docelowy

    std::istream_iterator<std::string> ii(is); // tworzy iterator dla wejścia

    std::ostream_iterator<std::string> oo(cout, "\n"); // tworzy iterator wyjścia
        // dodaje "\n" za każdym razem
    std::set<std::string> b(ii, {}); // b jest typu vector inicjalizowanym z wejścia

    //    std::sort(b.begin(), b.end());            // sortuje wektorb
    std::copy(b.begin(), b.end(), oo); // kopiuje b na wyjście pomijając powtorzenia
}
int main()
{
    tablica_asocjacyjna();
}
