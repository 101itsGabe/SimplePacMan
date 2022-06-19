
//Gabe
#include <iostream>
#include "grid.h"

using namespace std;

int main() {
    int r,c,mr,mc,er,ec;




    cout << "\nRows: ";
    cin >> r;
    cout << "\nCols: ";
    cin >> c;


    Grid g(r,c);
    mr = g.GetRow();
    mc =g.GetCol();
    g.Display();


    do {
        g.Move(1);
        mr = g.GetRow();
        mc = g.GetCol();
        if (mr == 0 || mr == r - 1 || mc == 0 || mc == c - 1)
            break;
    }while(g.FrontIsClear());

    if (mr == 0 || mr == r - 1 || mc == 0 || mc == c - 1) {
        cout << "\nWE OUT THIS BITCH!";
        g.Display();
        return 0;
    }
    else {
        g.TurnLeft();
        g.Display();
    }




    do {
        g.Move(1);
        mr = g.GetRow();
        mc = g.GetCol();
        if (mr == 0 || mr == r - 1 || mc == 0 || mc == c - 1)
            break;
        else if (g.RightIsClear())
            break;
    }while(g.FrontIsClear());

    if (mr == 0 || mr == r - 1 || mc == 0 || mc == c - 1) {
        cout << "\nWE OUT THIS BITCH!";
        g.Display();
        return 0;
    }

    else
    {
        g.TurnLeft();
        g.Display();
    }
    int ll = 0;
    do {
        g.Move(1);
        mr = g.GetRow();
        mc = g.GetCol();
        if (mr == 0 || mr == r - 1 || mc == 0 || mc == c - 1)
            break;
        else if (g.RightIsClear()) {
            cout << "\n" << ll << endl;
            break;
        }
    }while(g.FrontIsClear());



    if (mr == 0 || mr == r - 1 || mc == 0 || mc == c - 1) {
        cout << "\nWE OUT THIS BITCH!";
        g.Display();
        return 0;
    }


    else
    {
        g.TurnLeft();
        g.Display();
    }







    return 0;
}
