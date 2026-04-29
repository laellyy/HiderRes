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

    while (count < 20 && getline(file, menuList[count].menuItem)) {
        file >> menuList[count].menuPrice;
        file.ignore(1000, '\n');
        count++;
    }

    file.close();
}

void showMenu(menuItemType menuList[], int count) {
    cout << fixed << setprecision(2);

    cout << "\nSveiki atvyke i restorana \"HiderRes\"\n\n";
    cout << "MENIU:\n";

    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". "
             << menuList[i].menuItem << " - "
             << menuList[i].menuPrice << " EUR\n";
    }

    cout << "\n0  - gauti ceki\n";
    cout << "-1 - iseiti be cekio\n";
}

void printCheck(menuItemType menuList[], int count, int staliukas) {
    int pasirinkimas, kiekis;
    double suma = 0;
    string cekis = "";

    cout << fixed << setprecision(2);

    while (true) {
        cout << "\nKa noretumete uzsisakyti? Iveskite meniu numeri: ";
        cin >> pasirinkimas;

        if (pasirinkimas == -1) {
            cout << "\nAciu, viso gero! Sugrizkite dar!\n";
            return;
        }

        if (pasirinkimas == 0) {
            string failoPavadinimas = "cekis_" + to_string(staliukas) + ".txt";
            ofstream receipt(failoPavadinimas);

            double pvm = suma * 0.21;
            double galutine = suma + pvm;

            cout << "\n--- CEKIS ---\n";
            cout << "Restoranas HiderRes\n";
            cout << "Staliuko numeris: " << staliukas << "\n\n";
            cout << cekis;
            cout << "\nMokesciai (21%): " << pvm << " EUR\n";
            cout << "Galutine suma: " << galutine << " EUR\n";
            cout << "Aciu, sugrizkite dar!\n";

            receipt << fixed << setprecision(2);
            receipt << "--- CEKIS ---\n";
            receipt << "Restoranas HiderRes\n";
            receipt << "Staliuko numeris: " << staliukas << "\n\n";
            receipt << cekis;
            receipt << "\nMokesciai (21%): " << pvm << " EUR\n";
            receipt << "Galutine suma: " << galutine << " EUR\n";
            receipt << "Aciu, sugrizkite dar!\n";

            receipt.close();

            cout << "\nCekis issaugotas faile: " << failoPavadinimas << endl;
            return;
        }

        if (pasirinkimas < 1 || pasirinkimas > count) {
            cout << "Tokio patiekalo nera!\n";
        } else {
            cout << "Kiek porciju noretumete? ";
            cin >> kiekis;

            if (kiekis <= 0) {
                cout << "Porciju kiekis turi buti didesnis uz 0.\n";
            } else {
                double vienetoKaina = menuList[pasirinkimas - 1].menuPrice;
                double bendraKaina = vienetoKaina * kiekis;
                suma += bendraKaina;

                cout << kiekis << " x " << menuList[pasirinkimas - 1].menuItem
                     << " | vnt. kaina: " << vienetoKaina
                     << " EUR | suma: " << bendraKaina << " EUR\n";

                cekis += to_string(kiekis) + " x " +
                         menuList[pasirinkimas - 1].menuItem +
                         " | vnt. kaina: " + to_string(vienetoKaina) +
                         " EUR | suma: " + to_string(bendraKaina) + " EUR\n";
            }
        }
    }
}

int main() {
    menuItemType menuList[20];
    int count;
    int staliukas;

    getData(menuList, count);

    if (count > 0) {
        cout << "Iveskite staliuko numeri: ";
        cin >> staliukas;

        showMenu(menuList, count);
        printCheck(menuList, count, staliukas);
    }

    cout << "\nSpauskite Enter, kad uzdarytumete programa...";
    cin.ignore(1000, '\n');
    cin.get();

    return 0;
}