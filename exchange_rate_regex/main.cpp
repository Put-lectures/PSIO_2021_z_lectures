#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
using namespace std;
struct ExchangeRate
{
    string currency;
    int units;
    float rate;
};
int main()
{
    vector<ExchangeRate> rates;
    map<string, float> rates_bt;

    //    rates_bt["PLN"]

    fstream file("/home/piotr/workspace/PSIO_2021_z_lectures/exchange_rate_regex/rates.html");
    stringstream sstream;
    sstream << file.rdbuf();
    string text = sstream.str();

    //    cout << text;
    regex pattern(R"(<td class="right">(\d+) (\w{3})<\/td> <td class="right">(\d+\,\d+))");
    smatch m;

    while (regex_search(text, m, pattern)) {
        cout << m[0] << endl;
        cout << m[1] << endl;
        cout << m[2] << endl;
        cout << m[3] << endl;
        ExchangeRate rate;
        rate.currency = m[2];
        rate.units = stoi(m[1]);
        string rate_str = m[3];
        rate_str.replace(rate_str.find(","), 1, ".");
        rate.rate = stof(rate_str);
        rates_bt[rate.currency] = rate.rate / rate.units;

        rates.emplace_back(rate);
        text = m.suffix();
    }

    for (auto &el : rates) {
        cout << el.currency << " - " << el.rate / el.units << endl;
    }

    cout << "USD rate: " << rates_bt["USD"] << endl;
    //    regex_match
    return 0;
}
