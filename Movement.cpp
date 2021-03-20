#include "Map.hpp"
#include "Player.hpp"
#include <iostream>
using namespace std;

int main(){
    Map m;
    Player p;
    string c;

    m.show();
    cout << "command: ";
    cin >> c;
    while (c == "w" || c == "a" || c == "s" || c == "d"){
        p.Move(c);
        m.updateMap(p.getPlayerPos());
        m.show();

        cout << "command :";
        cin >> c;
    }
    return 0;
}