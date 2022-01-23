#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <vector>
using namespace std;
struct kurs
{
    int jednostka;
    string symbol;
    float kurs;
};

int main()
{
    vector<kurs> waluty;
    map<string, float> waluty_bt;
    fstream file("/home/piotr/workspace/PSIO_2021_z_lectures/kursy_walut_regex/kursy.html");
    string text;
    stringstream sstr;
    sstr << file.rdbuf();
    text = sstr.str();

    std::regex pat(R"(\<td class="right"\>(\d+) (\w+)\<\/td\> \<td class="right">(\d+,\d+))");
    std::smatch res;
    while (std::regex_search(text, res, pat)) {
        cout << res[0] << endl;
        cout << "jednostka: " << res[1] << endl;
        cout << "symbol: " << res[2] << endl;
        cout << "kurs: " << res[3] << endl;
        kurs waluta;
        waluta.jednostka = stoi(res[1]);
        waluta.symbol = res[2];
        string kurs_str = res[3];
        int pos = kurs_str.find(",");
        kurs_str[pos] = '.';
        waluta.kurs = stof(kurs_str);
        text = res.suffix();
        waluty.emplace_back(waluta);
        //        waluty_bt[res[2]] = waluta.kurs / waluta.jednostka;
        //        waluty_bt.emplace(std::make_pair(string(res[2]), waluta.kurs / waluta.jednostka));
    }

    cout << "kurs USD" << waluty_bt["USD"];

    return 0;
}
