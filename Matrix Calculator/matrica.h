#ifndef MATRICA_H
#define MATRICA_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>
#include <stack>
#include <stdexcept>
using namespace std;

//Implementirati klasu Matrica koja čuva matricu proizvoljnih dimenzija. Potrebno je preklopiti operatore << i
// >>, pri čemu prvi operator ispisuje matricu na ekran, a drugi omogućava unos objekata tipa Matrica sa
//tastature. Format za unošenje matrice formata 2 × 3 sa tastature je [1 2 3; 4 5 6]. Međutim, potrebno je
//podržati unos i složenijih izraza (ovo je ključna stvar u projektu pored algoritma za množenje), kao npr.
//[1 2; 3 4]^3 ∗ (4 ∗ [1 2 3; 4 5 6] + [7 8; 9 1; 2 4]^𝑇) − [1 3; 7 2]^−1 ∗ [7 8 1; 1 2 3] ∗ I3. Ukoliko izraz nije
//validan iz nekog razloga (npr. ne slažu se dimenzije matrica), treba baciti izuzetak. Također, imlementirati
//funkciju koja računa determinantu matrice (ukoliko se radi o kvadratnoj matrici). Za množenje je potrebno
//implementirati brzi algoritam koji koristi strategiju podijeli pa vladaj.

enum ElementiIzraza {OtvorenaZagrada, ZatvorenaZagrada, Mat , Skalar , Operacija};

class Matrica{

    string izraz;
    vector<vector<double>> rezultat;

public:
    Matrica(){}
    Matrica(const string &i):izraz(i){CitanjeIzraza();}
    Matrica(const Matrica &mat):izraz(mat.izraz),rezultat(mat.rezultat){}
    Matrica& operator=(const Matrica& mat) {
        if (this != &mat) {
            rezultat = mat.rezultat;
        }
        return *this;
    }
    Matrica& operator=(Matrica&& kopija) noexcept {
        if (this != &kopija) {
            izraz = kopija.izraz;
            rezultat = kopija.rezultat;
        }
        return *this;
    }
    Matrica(Matrica&& kopija) noexcept {
        izraz = kopija.izraz;
        rezultat = kopija.rezultat;
    }

    void Transponovanje(vector<vector<double>>& mat);
    int Determinanta(const vector<vector<double>>& mat);
    void InverznaMatrica(vector<vector<double>>& mat);
    void Stepenovanje(vector<vector<double>> &mat,int stepen);
    void BrzoStepenovanje(vector<vector<double>> &mat,int stepen);
    vector<vector<double>> MnozenjeMatrica(vector<vector<double>> mat1,vector<vector<double>> mat2);
    vector<vector<double>> SkalarnoMnozenje(const double &skalar,const vector<vector<double>>& mat);
    vector<vector<double>> Sabiranje(vector<vector<double>> mat1,vector<vector<double>> mat2);
    vector<vector<double>> Oduzimanje(vector<vector<double>> mat1,vector<vector<double>> mat2);

    void IzvrsiOperaciju(stack<vector<vector<double>>> &mat, stack<char> &zio, stack<double> &skalar,stack<ElementiIzraza> &red);
    void NapraviMatricu(const string &izraz,stack<vector<vector<double>>> &matrice);
    void CitanjeIzraza();
    bool jeLiKvadratna(const vector<vector<double>>&);
    bool jeLiGrbavaMatrica(const vector<vector<double>> &mat);
    vector<vector<double>> NapraviJedinicnuMatricu(const int &dimenzija);
    vector<vector<double>> Strassen(vector<vector<double>> mat1, vector<vector<double>> mat2, int dimenzija);
    vector<vector<double>> Adjugovana(const vector<vector<double>> &mat);

    friend ostream& operator<<(ostream& ispis, const Matrica& mat);
    friend istream& operator>>(istream& upis, Matrica& mat);
    friend Matrica operator+(const Matrica& mat1,const Matrica& mat2);
    friend Matrica operator-(const Matrica& mat1,const Matrica& mat2);
    friend Matrica operator*(const Matrica& mat1,const Matrica& mat2);
    friend Matrica operator*(const Matrica& mat,int skalar);
    friend Matrica operator*(int skalar,const Matrica& mat);
    friend Matrica operator^(Matrica& mat,int stepen);
    friend Matrica operator^(Matrica& mat,char t);
    friend int Det(Matrica mat);

};

ostream& operator<<(ostream& ispis, const Matrica& mat);
istream& operator>>(istream& upis, Matrica& mat);
Matrica operator+(const Matrica& mat1,const Matrica& mat2);
Matrica operator-(const Matrica& mat1,const Matrica& mat2);
Matrica operator*(const Matrica& mat1,const Matrica& mat2);
Matrica operator^(Matrica& mat,int stepen);
Matrica operator^(Matrica& mat,char t);
int Det( Matrica mat);

#endif // MATRICA_H
