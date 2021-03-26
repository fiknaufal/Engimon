#include <iostream>
#include <string>
#include <time.h>
#include "Map.hpp"

int main(){
    srand(time(0));
    cout << "  _____ _            _____             _" << endl;
    cout << " |_   _| |__   ___  | ____|_ __   __ _(_)_ __ ___   ___  _ __" << endl;
    cout << "   | | | '_ \\ / _ \\ |  _| | '_ \\ / _` | | '_ ` _ \\ / _ \\| '_ \\" << endl;
    cout << "   | | | | | |  __/ | |___| | | | (_| | | | | | | | (_) | | | |" << endl;
    cout << "  _|_|_|_| |_|\\___| |_____|_| |_|\\__, |_|_| |_| |_|\\___/|_| |_|" << endl;
    cout << " |  ___|_ _  ___| |_ ___  _ __ _ |___/" << endl;
    cout << " | |_ / _` |/ __| __/ _ \\| '__| | | |" << endl;
    cout << " |  _| (_| | (__| || (_) | |  | |_| |" << endl;
    cout << " |_|  \\__,_|\\___|\\__\\___/|_|   \\__, |" << endl;
    cout << "                               |___/" << endl;
    cout << endl;
    int jumlah, level;
    cout << "Masukkan jumlah maksimum Engimon pada peta:";
    cin >> jumlah;
    cout << "Masukkan level pembeda tampilan Engimon:";
    cin >> level;
    cout << endl;
    cout << "Selamat bermain!\n" << endl;
    Map map(level, "Map.txt", jumlah);
    map.gameFlow();
    cout << endl;
    cout << "  _____ _                 _           __" << endl;
    cout << " |_   _| |__   __ _ _ __ | | _____   / _| ___  _ __" << endl;
    cout << "   | | | '_ \\ / _` | '_ \\| |/ / __| | |_ / _ \\| '__|" << endl;
    cout << "   | | | | | | (_| | | | |   <\\__ \\ |  _| (_) | |   " << endl;
    cout << "  _|_| |_| |_|\\__,_|_|_|_|_|\\_\\___/ |_|  \\___/|_|" << endl;
    cout << " |  _ \\| | __ _ _   _(_)_ __   __ _" << endl;
    cout << " | |_) | |/ _` | | | | | '_ \\ / _` |" << endl;
    cout << " |  __/| | (_| | |_| | | | | | (_| |_ _ _" << endl;
    cout << " |_|   |_|\\__,_|\\__, |_|_| |_|\\__, (_|_|_)" << endl;
    cout << "                |___/         |___/" << endl;
}
