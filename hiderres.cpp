#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct menuItemType {
    string menuItem;
    double menuPrice;
};

void getData(menuItemType menuList[], int &count) {
    ifstream file("menu.txt");

    count = 0;

    if (!file) {
        cout << "Klaida: nerastas menu.txt failas!\n";
        return;
    }

    while (getline(file, menuList[count].menuItem)) {
        file >> menuList[count].menuPrice;
        file.ignore();
        count++;
    }

    file.close();
}

void showMenu(menuItemType menuList[], int count) {
    cout << fixed << setprecision(2);

    cout << "Sveiki atvyke i restorana \"HiderRes\"\n\n";
    cout << "MENIU:\n";

    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". "
             << menuList[i].menuItem << " - "
             << menuList[i].menuPrice << " EUR\n";
    }

    cout << "\nPasirinkite patiekalo numeri ir porciju kieki.\n";
    cout << "Jei norite baigti, iveskite 0.\n";
}

void printCheck(menuItemType menuList[], int count) {
    ofstream receipt("receipt.txt");

    int nr, kiekis;
    double suma = 0;

    cout << fixed << setprecision(2);
    receipt << fixed << setprecision(2);

    cout << "\nJusu uzsakymas:\n";
    receipt << "Restoranas HiderRes\n\n";
    receipt << "Jusu uzsakymas:\n";

    while (true) {
        cout << "\nPatiekalo numeris: ";
        cin >> nr;

        if (nr == 0) break;

        if (nr < 1 || nr > count) {
            cout << "Tokio patiekalo nera!\n";
        } else {
            cout << "Porciju kiekis: ";
            cin >> kiekis;

            double kaina = menuList[nr - 1].menuPrice * kiekis;
            suma += kaina;

            cout << kiekis << " " << menuList[nr - 1].menuItem
                 << " - " << kaina << " EUR\n";

            receipt << kiekis << " " << menuList[nr - 1].menuItem
                    << " - " << kaina << " EUR\n";
        }
    }

    double pvm = suma * 0.21;
    double galutine = suma + pvm;

    cout << "\nMokesciai (21%): " << pvm << " EUR\n";
    cout << "Galutine suma: " << galutine << " EUR\n";

    receipt << "\nMokesciai (21%): " << pvm << " EUR\n";
    receipt << "Galutine suma: " << galutine << " EUR\n";

    receipt.close();
}

int main() {
    menuItemType menuList[20];
    int count;

    getData(menuList, count);

    if (count > 0) {
        showMenu(menuList, count);
        printCheck(menuList, count);
    }

    return 0;
}