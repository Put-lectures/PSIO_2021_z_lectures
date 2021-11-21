#include <iostream>

using namespace std;

int main()
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            if (j == 0 || j == 4 || i == 0 || i == 9)
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }
    return 0;
}
