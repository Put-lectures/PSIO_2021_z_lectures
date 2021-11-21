#include <iostream>

using namespace std;

int main()
{
    int tab[] = {100, 5, 1, 0, -10, 20};

    int size = 6;
    bool is_swapped = false;
    do {
        is_swapped = false;
        for (int i = 0; i < size - 1; i++) {
            if (tab[i] > tab[i + 1]) {
                int tmp = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = tmp;
                is_swapped = true;
            }
        }
    } while (is_swapped);
    //print
    for (int i = 0; i < 6; i++) {
        cout << tab[i] << ", ";
    }

    return 0;
}
