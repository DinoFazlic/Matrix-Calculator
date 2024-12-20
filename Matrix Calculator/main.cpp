#include <iostream>
#include "matrica.h"
using namespace std;

int main(){
try{
    // [1 2; 3 4]^3 * (4 * [1 2 3; 4 5 6] + [7 8; 9 1; 2 4]^T ) - [1 3; 7 2]^-1 * [7 8 1; 1 2 3] * I3

/*
    Matrica m;
    cin>>m;
    cout<<m<<endl;
    cout<<endl;
    */

    Matrica d("[1 2; 3 4]^3 * (4 * [1 2 3; 4 5 6] + [7 8; 9 1; 2 4]^T ) - [1 3; 7 2]^-1 * [7 8 1; 1 2 3] * I3");
    cout<<d<<endl;
    cout<<endl;


    // Matrica n = m;
    // cout<<n<<endl;


    /*
    cout<<endl;

    //TRANSPONOVANA
    cout<<d^T<<endl;
    cout<<endl;

    //INVERZNA MATRICA
    cout<<d^-1<<endl;
    cout<<endl;

    //MNOZENJE MATRICA
    cout<<d*m<<endl;
    cout<<endl;

    //MNOZENJE SA SKALAROM
    cout<<d*4<<endl;

    cout<<"Determinanta matrice je: "<<Det(d)<<endl;
    */
}
catch(const char* greska){
    cout<<greska<<endl;
}

}
