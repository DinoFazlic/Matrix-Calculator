#ifndef MATRICA_CPP
#define MATRICA_CPP
#include "matrica.h"

//OPERATORI
//Operator za ispis matrice
ostream& operator<<(ostream& ispis, const Matrica& mat){
    ispis<<endl;
    for(int i = 0; i < mat.rezultat.size();i++){
        for(int j=0;j < mat.rezultat[i].size();j++)
            ispis<<setw(8)<< mat.rezultat[i][j]<<" ";
        ispis<<endl;
    }
    return ispis;
}

//Operator za unos matrice
istream& operator>>(istream& upis, Matrica& mat){
    string input;
    cout<<"Unesite izraz matrice: "<<endl;
    getline(upis,input);
    mat.izraz = input;
    mat.CitanjeIzraza();

    return upis;
}

//Operator za sabiranje dvije matrice
Matrica operator+(const Matrica& mat1,const Matrica& mat2){
    Matrica pomocna;
    pomocna.rezultat = pomocna.Sabiranje(mat1.rezultat,mat2.rezultat);
    return pomocna;
}

//Operator za oduzimanje dvije matrice
Matrica operator-(const Matrica& mat1,const Matrica& mat2){
    Matrica pomocna;
    pomocna.rezultat = pomocna.Oduzimanje(mat1.rezultat,mat2.rezultat);
    return pomocna;
}

//Operator za mnozenje dvije matrice
Matrica operator*(const Matrica& mat1,const Matrica& mat2){
    Matrica pomocna;
    pomocna.rezultat = pomocna.MnozenjeMatrica(mat1.rezultat,mat2.rezultat);
    return pomocna;
}

//Operator za stepenovanje matrice
Matrica operator^(Matrica& mat,int stepen){
    if(stepen == -1)
        mat.InverznaMatrica(mat.rezultat);
    else
        mat.Stepenovanje(mat.rezultat,stepen);
    return mat;
}

//Operator za transponovanje matrice
Matrica operator^(Matrica& mat,char t){
    if(t == 'T')
        mat.Transponovanje(mat.rezultat);
    else
        throw "Pogresna operacija";
    return mat;
}

//Funkcija za racunanje determinante matrice
int Det(Matrica mat){
    return mat.Determinanta(mat.rezultat);
}

//Operator za mnozenje skalara matrice
Matrica operator*(const Matrica& mat,int skalar){
    Matrica pomocna;
    pomocna.rezultat = pomocna.SkalarnoMnozenje(skalar,mat.rezultat);
    return pomocna;
}

//Operator za mnozenje skalara matrice
Matrica operator*(int skalar,const Matrica& mat){
    Matrica pomocna;
    pomocna.rezultat = pomocna.SkalarnoMnozenje(skalar,mat.rezultat);
    return pomocna;
}


//POMOCNE FUNCKIJE

//Funkcija koja provjerava da li je proslijedjeni znak cifra
bool JeLiCifra(char z){
    return z >= '0' && z <= '9';
}

//Funkcija koja provjerava da li je proslijedjeni znak operacija
bool JeLiOperacija(char z){
    return z == '+' || z == '*' || z == '-' || z == '^';
}

//Funkcija koja provjerava da li je proslijedjeni znak validan za kreiranje matrice
bool pravilnaMatrica(char znak){
    return znak == ';' || znak == ']' || isdigit(znak) || znak == '-' || znak == ' ' ;
}

bool jeLiBroj(const string& str) {

    try {
        size_t pos;
        stod(str, &pos);
        return pos == str.length();
    } catch (...) {
        return false;
    }
}

//Funkcija koja provjerava da li je proslijedjeni string transformacija ^-1 ili ^T ili stepenovanje
bool jeLiTransformacija(string znak){
    return znak == "T" || znak == "-1" || jeLiBroj(znak);
}

//Funkcija koja provjerava da li je proslijedjeni znak razmak
bool jeLiSpace(char znak){
    return znak == ' ';
}

//Funkcija koja odredjuje prioritet operacija
int prioritet(char operacija){
if(operacija == '+' || operacija == '-') return 1;
else if(operacija == '*') return 2;
else return 0;
}

//Funkcija koja provjerava da li proslijedjena matrica ima paran broj kolona i redova koji su djeljivi sa 2
bool jeliDjeljivoSaDva(const vector<vector<double>> &mat){
     int dimenzija = mat.size();
     while(true){
        if(dimenzija % 2 != 0) return false;
        dimenzija /= 2;
     }
     return true;
}

//Funkcija koja za proslijedjenu dimenziju napravi jedinicnu matricu te dimenzije
vector<vector<double>> Matrica::NapraviJedinicnuMatricu(const int &dimenzija){
    vector<vector<double>> jedinicna(dimenzija, vector<double>(dimenzija, 0));
            for(int i = 0; i < jedinicna.size();i++)
                jedinicna[i][i] = 1;
    return jedinicna;
}

bool Matrica::jeLiGrbavaMatrica(const vector<vector<double>> &mat){

    for(int i = 1;i<mat.size();i++)
        if(mat[i].size() != mat[0].size()) return false;

    return true;
}

//Funkcija koja provjerava da li je matrica kvadratna
bool Matrica::jeLiKvadratna(const vector<vector<double>>& mat){
    int velicina = mat.size();
    for(int i = 0; i < velicina;i++){
        if(mat[i].size() != velicina) return false;
    }
    return true;
}

//zio = ZagradeIOperacije
void Matrica::IzvrsiOperaciju(stack<vector<vector<double>>> &mat, stack<char> &zio, stack<double> &skalar,stack<ElementiIzraza> &red){
    if(zio.empty()) throw "Izraz nije ispravno napisan";

    char operacija = zio.top();
    zio.pop();

    ElementiIzraza operand2 = red.top();
    red.pop();

    ElementiIzraza operand1 = red.top();
    red.pop();

    if((operand1 == Skalar && operand2 == Mat) || (operand1 == Mat && operand2 == Skalar)){
        if(operacija == '-' || operacija == '+') throw "Nije moguce sabrati ili oduzeti skalar sa matricom";

        vector<vector<double>> matrica = mat.top();
        mat.pop();

        double br = skalar.top();
        skalar.pop();

        mat.push(this->SkalarnoMnozenje(br,matrica));
        red.push(Mat);
    }

    else if(operand1 == Mat && operand2 == Mat){

        vector<vector<double>> matrica2 = mat.top();
        mat.pop();

        vector<vector<double>> matrica1 = mat.top();
        mat.pop();

        if(operacija == '+'){
            vector<vector<double>> rez = this->Sabiranje(matrica1,matrica2);
            mat.push(rez);
            red.push(Mat);
        }
        else if(operacija == '-'){
            vector<vector<double>> rez = this->Oduzimanje(matrica1,matrica2);
            mat.push(rez);
            red.push(Mat);
        }
        else{
            vector<vector<double>> rez = this->MnozenjeMatrica(matrica1,matrica2);
            mat.push(rez);
            red.push(Mat);
        }
    }
}

//Funkcija koja provjerava da li je izraz koji je unesen validan
void Matrica::CitanjeIzraza(){
    stack<vector<vector<double>>> matrice;
    stack<double> skalari;
    stack<char> ZagradeIOperacije;
    stack<ElementiIzraza> redoslijed;

    izraz += " ";
    //string izraz = "[1 2; 3 4]^3 * (4 * [1 2 3; 4 5 6] + [7 8; 9 1; 2 4]^T ) - [1 3; 7 2]^-1 * [7 8 1; 1 2 3] * I3";
    ElementiIzraza prethodni = OtvorenaZagrada;

    int i = 0;
    while( i < izraz.size()){
        //cout<<"Slovo je: "<<izraz[i]<<endl;

        //AKO UCITAMO OTVORENU ZAGRADU
        if(izraz[i] == '('){

            //PROVJERA DA LI JE VALIDAN REDOSLIJED
            if(prethodni == Skalar || prethodni == Mat || prethodni == ZatvorenaZagrada)
                throw "Unos nije validan";

            ZagradeIOperacije.push(izraz[i]);
            prethodni = OtvorenaZagrada;
        }

        //AKO UCITAMO OZNAKU ZA POCETAK MATRICE
        else if(izraz[i] == '['){

                //PROVJERA DA LI JE VALIDAN REDOSLIJED
                if(prethodni == Skalar || prethodni == ZatvorenaZagrada) throw "Unos nije validan";
                string m = "";
                i++;
                while(true){
                    if(pravilnaMatrica(izraz[i]) == false) throw "Unos nije validan";

                    if(izraz[i] != ']'){
                        m += izraz[i];
                        i++;
                    }
                    else {
                    m += izraz[i];
                    //i--;
                    break;
                    }
                }
                this->NapraviMatricu(m,matrice);
                m = "";
                prethodni = Mat;
                redoslijed.push(Mat);
        }

        //AKO UCITAMO ZATVORENU ZAGRADU
        else if(izraz[i] == ')'){

            //PROVJERA DA LI JE VALIDAN REDOSLIJED
            if(prethodni == Operacija || prethodni == OtvorenaZagrada)throw "Unos nije validan";

            while(!ZagradeIOperacije.empty() && ZagradeIOperacije.top() != '('){
                    IzvrsiOperaciju(matrice,ZagradeIOperacije,skalari,redoslijed);
            }

            if(ZagradeIOperacije.empty()) throw "Unos nije validan";
            if(ZagradeIOperacije.top() == '(') ZagradeIOperacije.pop();
            prethodni = ZatvorenaZagrada;
        }

        //AKO UCITAMO OPERACIJU
        else if(JeLiOperacija(izraz[i])){

            //PROVJERA DA LI JE VALIDAN REDOSLIJED
            if(prethodni == Operacija || prethodni == OtvorenaZagrada) throw "Unos nije validan";


            //PROVJERA DA LI TREBA RADITI TRANSFORMACIJU
            if(izraz[i] == '^'){

                //PROVJERA DA LI JE VALIDAN REDOSLIJED
                if(prethodni == Skalar || prethodni == ZatvorenaZagrada || prethodni == OtvorenaZagrada) throw "Unos nije validan";

                string s = "";
                i++;
                //UCITAVANJE TRANSFORMACIJE DO PRVOG RAZMAKA, OPERACIJE ILI ZATVORENE ZAGRADE
                while(izraz[i] != ' ' && izraz[i] != ')' && izraz[i] != '*' && izraz[i] != '+' && izraz[i] != '['){
                    s += izraz[i];
                    i++;
                }
                //PROVJERA DA LI JE VALIDNA TRANFORMACIJE, TE POZIVANJE ISTE NAD MATRICOM NA VRHU KOLEKCIJE ZA MATRICE
                if( !jeLiTransformacija(s) ) throw "Unos nije validan";
                else{
                    if( s == "T"){
                        this->Transponovanje(matrice.top());
                        prethodni = Mat;
                    }
                    else if( s == "-1"){
                        this->InverznaMatrica(matrice.top());
                        prethodni = Mat;
                    }
                    else{
                        if(stoi(s) < 0) throw "Unos nije validan";

                        this->BrzoStepenovanje(matrice.top(),stoi(s));
                        prethodni = Mat;
                    }
                }
                i--;
            }
            //UKOLIKO NIJE TRANSFORMACIJA ONDA JE OPERACIJA +,-,*
            //POZIVA SE OPERACIJA UKOLIKO JE PRIORITET OPERACIJE VECI ILI JEDNAK OD OPERACIJE NA VRHU KOLEKCIJE SA ZAGRADAMA I OPERACIJAMA
            else{

                while(!ZagradeIOperacije.empty() && prioritet(ZagradeIOperacije.top()) >= prioritet(izraz[i])){
                    IzvrsiOperaciju(matrice,ZagradeIOperacije,skalari,redoslijed);
                }

                ZagradeIOperacije.push(izraz[i]);
                prethodni = Operacija;
            }

        }

        //PROVJERA DA LI JE CIFRA
        else if((JeLiCifra(izraz[i]))){

            //PROVJERA DA LI JE VALIDAN REDOSLIJED
            if(prethodni == ZatvorenaZagrada || prethodni == Mat) throw "Unos nije validan";

            string broj = "";
            //UCITAVANJE CIFRI DO PRVOG RAZMAKA,OPERACIJE,ZATVORENE ZAGRADE ILI MATRICE
            while(izraz[i] != ' ' && izraz[i] != '*' && izraz[i] != ')' && izraz[i]!='['){
                broj += izraz[i];
                i++;
            }
            i--;
            int br = stoi(broj);
            skalari.push(br);

            prethodni = Skalar;
            redoslijed.push(Skalar);
        }

        //PROVJERA DA LI JE RAZMAK
        else if(jeLiSpace(izraz[i])){
            // AKO JE RAZMAK SAMO GA PRESKOCI
        }

        //PROVJERA DA LI JE OZNAKA ZA JEDINICNU MATRICU
        else if( izraz[i] == 'I'){

            //PROVJERA DA LI JE VALIDAN REDOSLIJED
            if(prethodni == ZatvorenaZagrada || prethodni == Skalar) throw "Unos nije validan";
            prethodni = Mat;

            i++;
            string dimenzija = "";
            while(izraz[i] != ' ' && izraz[i] != ')' && izraz[i] != '*'){
                dimenzija += izraz[i];
                i++;
            }
            i--;
            matrice.push(NapraviJedinicnuMatricu(stoi(dimenzija)));
            redoslijed.push(Mat);
        }

        else throw "Unos nije validan";
        i++;
    }

    //NAKON PROLASKA KROZ UNOS POZIVANJE PREOSTALIH OPERACIJA UKOLIKO KOLEKECIJA NIJE PRAZNA
    while (!ZagradeIOperacije.empty() && ZagradeIOperacije.top() != '('){
        IzvrsiOperaciju(matrice,ZagradeIOperacije,skalari,redoslijed);
    }

    //AKO NAKON SVEGA KOLEKCIJA ZA OPERACIJE I ZAGRADE NIJE PRAZNA UNOS NIJE VALIDAN
    if(!ZagradeIOperacije.empty() || !skalari.empty()){
        throw "Unos nije validan";
    }

    else{
        cout<<"Unos je validan"<<endl;
        cout<<endl;
        rezultat = matrice.top();
    }
}

//Funkcija koja od proslijedjenog izraza pravi matricu
void Matrica::NapraviMatricu(const string &izraz,stack<vector<vector<double>>> &matrice){
    vector<vector<double>> mat;
    vector<double> red;

    string br = "";
    for(int i = 0;i < izraz.size();i++){
            if(izraz[i] == ' ' && br != ""){
                //Ukoliko se neko bude igrao sa unosom matrica i bude dodavao viska razmaka izmedju brojeva, preskoci ih
                while( izraz[i] == ' '){
                    i++;
                }
                i--;
                int value = stoi(br);
                red.push_back(value);
                br = "";
            }
            else if(izraz[i] == ';' || izraz[i] == ']'){
                int vrijednost = stoi(br);
                red.push_back(vrijednost);
                mat.push_back(red);
                red.clear();
                br = "";
            }
            else{
                br += izraz[i];
            }
        }
    if(jeLiGrbavaMatrica(mat)){
        matrice.push(mat);
    }
    else{
        throw "Zabranjen je unos grbavih matrica";
    }
}

//Funkcija koja Strassenovom metodom mnozi matrice
vector<vector<double>> Matrica::Strassen(vector<vector<double>> mat1, vector<vector<double>> mat2, int dimenzija){

    if( dimenzija == 1){
        vector<vector<double>> rezultat(dimenzija, vector<double>(dimenzija, 0));

        rezultat[0][0] = mat1[0][0]*mat2[0][0];
        return rezultat;
    }
    else if( dimenzija == 2){
        vector<vector<double>> rezultat(dimenzija, vector<double>(dimenzija, 0));

        rezultat[0][0] = mat1[0][0]*mat2[0][0] + mat1[0][1]*mat2[1][0];
        rezultat[0][1] = mat1[0][0]*mat2[0][1] + mat1[0][1]*mat2[1][1];
        rezultat[1][0] = mat1[1][0]*mat2[0][0] + mat1[1][1]*mat2[1][0];
        rezultat[1][1] = mat1[1][0]*mat2[0][1] + mat1[1][1]*mat2[1][1];
        return rezultat;
    }
    else{
        vector<vector<double>> rezultat(dimenzija, vector<double>(dimenzija, 0));
        int nova_dimenzija = dimenzija/2;

        vector<vector<double>> a11(nova_dimenzija, vector<double>(nova_dimenzija, 0));
        vector<vector<double>> a12(nova_dimenzija, vector<double>(nova_dimenzija, 0));
        vector<vector<double>> a21(nova_dimenzija, vector<double>(nova_dimenzija, 0));
        vector<vector<double>> a22(nova_dimenzija, vector<double>(nova_dimenzija, 0));

        vector<vector<double>> b11(nova_dimenzija, vector<double>(nova_dimenzija, 0));
        vector<vector<double>> b12(nova_dimenzija, vector<double>(nova_dimenzija, 0));
        vector<vector<double>> b21(nova_dimenzija, vector<double>(nova_dimenzija, 0));
        vector<vector<double>> b22(nova_dimenzija, vector<double>(nova_dimenzija, 0));

        for (int i=0; i < nova_dimenzija; i++) {
            for (int j=0; j < nova_dimenzija; j++) {
                a11[i][j] = mat1[i][j];
                a12[i][j] = mat1[i][j + nova_dimenzija];
                a21[i][j] = mat1[i + nova_dimenzija][j];
                a22[i][j] = mat1[i + nova_dimenzija][j + nova_dimenzija];

                b11[i][j] = mat2[i][j];
                b12[i][j] = mat2[i][j + nova_dimenzija];
                b21[i][j] = mat2[i + nova_dimenzija][j];
                b22[i][j] = mat2[i + nova_dimenzija][j + nova_dimenzija];
            }
        }

        vector<vector<double>> p1 = Strassen(this->Sabiranje(a11,a22) , this->Sabiranje(b11,b22), nova_dimenzija);
        vector<vector<double>> p2 = Strassen(a22 , this->Oduzimanje(b21,b11) , nova_dimenzija);
        vector<vector<double>> p3 = Strassen(this->Sabiranje(a11,a12) , b22 , nova_dimenzija);
        vector<vector<double>> p4 = Strassen(this->Oduzimanje(a12,a22) , this->Sabiranje(b21,b22) ,nova_dimenzija);
        vector<vector<double>> p5 = Strassen(a11 , this->Oduzimanje(b12,b22) , nova_dimenzija);
        vector<vector<double>> p6 = Strassen(this->Sabiranje(a21,a22) , b11 ,nova_dimenzija);
        vector<vector<double>> p7 = Strassen( this->Oduzimanje(a11,a21) , this->Sabiranje(b11,b12) ,nova_dimenzija);

        vector<vector<double>> rez11 = this->Oduzimanje(this->Sabiranje(this->Sabiranje(p1,p2),p4),p3);
        vector<vector<double>> rez12 = this->Sabiranje(p5,p3);
        vector<vector<double>> rez21 = this->Sabiranje(p6,p2);
        vector<vector<double>> rez22 = this->Oduzimanje(this->Sabiranje(p5,p1),this->Sabiranje(p6,p7));

        for(int i = 0 ; i < nova_dimenzija ; i++){
            for(int j = 0 ; j < nova_dimenzija ; j++){
                rezultat[i][j] = rez11[i][j];
                rezultat[i][j + nova_dimenzija] = rez12[i][j];
                rezultat[i + nova_dimenzija][j] = rez21[i][j];
                rezultat[i + nova_dimenzija][j + nova_dimenzija] = rez22[i][j];
            }
        }

        return rezultat;
    }
}

vector<vector<double>> PomocnaZaAdjugovanje(const vector<vector<double>> &mat, int red, int kolona){

    vector<vector<double>> rez;
    vector<double> pomocni_red;

    for(int i = 0;i < mat.size();i++){
        for(int j = 0; j < mat[i].size();j++){
            if( j != kolona &&  i != red){
                pomocni_red.push_back(mat[i][j]);
            }
        }
        if( !pomocni_red.empty() ){
            rez.push_back(pomocni_red);
            pomocni_red.clear();
        }
    }
    return rez;
}

//Funkcija koja racuna adjugovanu matricu proslijedjene matrice
vector<vector<double>> Matrica::Adjugovana(const vector<vector<double>> &mat){
    int dimenzija = mat.size();
    vector<vector<double>> adj;
    vector<double> red;

    for(int i = 0;i < dimenzija;i++){
       for(int j = 0; j < dimenzija;j++){
                int broj = (pow(-1,i + j))*Determinanta(PomocnaZaAdjugovanje(mat,i,j));

                if( broj == -0)
                    red.push_back(0);

                else
                    red.push_back(broj);
       }
      adj.push_back(red);
      red.clear();
    }

    this->Transponovanje(adj);
    return adj;
}




//GLAVNE FUNKCIJE
//Funkcija koja transponuje datu matricu
void Matrica::Transponovanje(vector<vector<double>>& mat){
        int x = mat.size();
        int y = mat[0].size();
        vector<vector<double>> nova(y, vector<double>(x));

        for(int i = 0;i < mat.size();i++){
            for(int j = 0;j < mat[i].size();j++){
                nova[j][i] = mat[i][j];
            }
        }
        mat = nova;
}

//Funkcija koja racuna determinantu proslijedjene matrice
int Matrica::Determinanta(const vector<vector<double>>& mat){
    //PROVJERA DA LI JE KVADRATNA MATRICA
    if( !jeLiKvadratna(mat) ) throw "Determinanta se ne moze izracunati ukoliko matrica nije kvadratna";
    else{

        if(mat.size() == 1) return mat[0][0];
        else if(mat.size() == 2) return mat[0][0]*mat[1][1]-mat[0][1]*mat[1][0];

        vector<vector<double>> nova = mat;

        //AKO REDOVI NISU FINO NAMJESTENI RADIMO ZAMJENU REDOVA
        int dimenzija = nova.size();
        int predznak = 1;
        int indeks_dijagonale = 0;
        for(int i = 0;i < dimenzija - 1;i++){
            for(int j = i + 1;j < dimenzija;j++){
                    if((nova[i][indeks_dijagonale] == 0 && nova[j][indeks_dijagonale] != 0)){
                        swap(nova[i],nova[j]);
                        indeks_dijagonale++;
                        predznak *= -1;
                        break;
                    }
            }
        }

        //PRAVIMO NULE ISPOD DIJAGONALE
        int indeks_pivota = 0;
            for(int i = 1;i < dimenzija;i++){
                double pivot = nova[indeks_pivota][indeks_pivota];
                for(int j = i;j < dimenzija;j++){
                    if(nova[j][indeks_pivota] != 0){
                        double broj_s_kojim_mnozimo = (nova[j][indeks_pivota])/pivot;
                        for(int k = 0;k < nova[j].size();k++){
                                nova[j][k] = nova[j][k] - nova[indeks_pivota][k]*broj_s_kojim_mnozimo;
                        }
                    }
                }
                indeks_pivota++;
            }

        double proizvod = 1;
        for(int i = 0;i < nova.size();i++){
                proizvod *= nova[i][i];
        }

        return predznak * round(proizvod);
    }
}

//Funkcija koja invertuje matricu
void Matrica::InverznaMatrica(vector<vector<double>>& mat){
    int determinanta = this->Determinanta(mat);

    //AKO JE DETERMINANTA MATRICE 0 ONDA NEMA INVERZNE MATRICE
    if(determinanta == 0) throw "Determinanta matrice je 0, pa matrica nije invertibilna";
    //AKO MATRICA NIJE KVADRATNA NEMA INVERZNE
    else if( !jeLiKvadratna(mat) ) throw "Matrica nije kvadratna, pa nije invertibilna";

    else{
        vector<vector<double>> adjugovana = Adjugovana(mat);
        mat = this->SkalarnoMnozenje((1./determinanta),adjugovana);
    }
}

//Funkcija koja stepenuje datu matricu sa proslijedjenim stepenom
void Matrica::Stepenovanje(vector<vector<double>> &mat,int stepen){
    if( !jeLiKvadratna(mat)) throw "Matrica nije kvadratna pa se ne moze stepenovati";

    if(stepen == 0){
        mat = NapraviJedinicnuMatricu(mat.size());
    }
    else if(stepen == 1){
    //AKO JE STEPEN 1 NE TREBA NISTA MIJENJATI
    }
    else{
        int brojac = 1;
        vector<vector<double>> rezultat = mat;

        while(brojac != stepen){
            rezultat = MnozenjeMatrica(rezultat,mat);
            brojac++;
        }
        mat = rezultat;
    }
}

//Funkcija koja izvrsava brzo stepenovanje sa proslijedjenim stepenom
void Matrica::BrzoStepenovanje(vector<vector<double>> &mat,int stepen){

    if(stepen == 0){
        mat = this->NapraviJedinicnuMatricu(mat.size());
    }

    else if(stepen == 1){
    //AKO JE STEPEN 1 NE TREBA NISTA MIJENJATI
    }
    else{
        vector<vector<double>> rezultat;
        vector<vector<double>> kvadrat;

        //AKO JE STEPEN PARAN
        if(stepen % 2 == 0){
            int br = 2;
            kvadrat = this->MnozenjeMatrica(mat,mat);
            rezultat  = kvadrat;

            while(br != stepen){
                rezultat = this->MnozenjeMatrica(rezultat,kvadrat);
                br += 2;
            }
            mat = rezultat;
        }
        //AKO JE STEPEN NEPARAN
        else{
            int br = 2;
            kvadrat = this->MnozenjeMatrica(mat,mat);
            rezultat = kvadrat;
            while(stepen - br != 1){
                rezultat = this->MnozenjeMatrica(rezultat,kvadrat);
                br += 2;
            }
            mat = this->MnozenjeMatrica(rezultat,mat);
        }
    }
}

//Vrijeme: T(n) = 7T(n/2) + n^2 -> O(n^2.81) < O(n^3)
vector<vector<double>> Matrica::MnozenjeMatrica(vector<vector<double>> mat1,vector<vector<double>> mat2){
    if(mat1[0].size() != mat2.size()) throw "Mnozenje ovih matrica nije moguce zbog njihovih dimenzija";


    //CUVANJE DIMENZIJA REZULTATA
    int dimenzijaRezultataRedovi = mat1.size();
    int dimenzijaRezultataKolone = mat2[0].size();


    //UKOLIKO MATRICE JESU KVADRATNE NAPRAVIMO I DIMENZIJA IM JE DJELJIVA SA DVA
    //POZIVAMO ODMA STRASSENA
    if(jeLiKvadratna(mat1) == true && jeLiKvadratna(mat2) == true && jeliDjeljivoSaDva(mat1) && jeliDjeljivoSaDva(mat2)){
        vector<vector<double>> rezultat(mat1.size(), vector<double>(mat2[0].size(), 0));
        rezultat = this->Strassen(mat1,mat2,mat1.size());
        return rezultat;
    }
    else{

        //AKO MATRICE NISU KVADRATNE NAPRAVIMO DA JESU
        //DOPUNOM SA NULAMA
        if( !jeLiKvadratna(mat1) ){

            if(mat1.size() > mat1[0].size()){
                for(int i = 0;i < mat1.size();i++)
                    mat1[i].resize(mat1.size());
            }
            else{
               mat1.push_back(vector<double>(mat1[0].size()));
            }

        }

        if( !jeLiKvadratna(mat2) ){

            if(mat2.size() > mat2[0].size()){
                for(int i = 0;i < mat2.size();i++)
                    mat2[i].resize(mat2.size());
            }
            else{
               mat2.push_back(vector<double>(mat2[0].size()));
            }

        }


        //AKO DIMENZIJE MATRICA NISU DJELJIVE SA 2 NADOPUNIMO
        //DO PRVOG VECEG STEPENA 2 SA NULAMA
        if( !jeliDjeljivoSaDva(mat1)){
            int nova_d = 1;
            while( nova_d < mat1.size())
                nova_d *= 2;

            for(int i = 0;i < mat1.size();i++)
                mat1[i].resize(nova_d);

            mat1.resize(nova_d, vector<double>(nova_d, 0));

        }

        if( !jeliDjeljivoSaDva(mat2) ){
            int nova_d = 1;
            while( nova_d < mat2.size())
                nova_d *= 2;

            for(int i = 0;i < mat2.size();i++)
                mat2[i].resize(nova_d);

            mat2.resize(nova_d, vector<double>(nova_d, 0));

       }


       //AKO NISU ISTE DIMENZIJE DVIJE MATRICE
       //NAMJESTIMO MANJU MATRICU NA DIMENZIJU VECE
       if(mat1.size() > mat2.size()){
            for(int i = 0;i < mat2.size();i++)
                mat2[i].resize(mat1[i].size());

            for(int i = 0;i < mat1.size() - mat2.size() + 1;i++)
                mat2.push_back(vector<double>(mat1[0].size()));
       }

       if(mat1.size() < mat2.size()){
            for(int i = 0;i < mat1.size();i++)
                mat1[i].resize(mat2[i].size());

            for(int i = 0;i < mat2.size() - mat1.size() + 1;i++)
                mat1.push_back(vector<double>(mat2[0].size()));
       }


       //NAKON SVIH PROVJERA POZIVAMO STRASSENA
        vector<vector<double>> rezultat;
        rezultat = this->Strassen(mat1,mat2,mat1.size());


        //NULE SA KOJIM SMO NADOPUNILI MATRICE BRISEMO IZ REZULTATA
        //JER ONE NE MIJENJAJU REZULTAT
        for(int i = 0;i < rezultat.size();i++)
            rezultat[i].resize(dimenzijaRezultataKolone);

        rezultat.resize(dimenzijaRezultataRedovi, vector<double>(dimenzijaRezultataKolone, 0));
        return rezultat;
    }
}

//Funkcija koja mnozi matricu sa skalarom
vector<vector<double>> Matrica::SkalarnoMnozenje(const double &skalar,const vector<vector<double>>& mat){
    vector<vector<double>> rez;
    vector<double> red;

    for(int i = 0;i < mat.size();i++){
        for(int j = 0;j < mat[i].size();j++){
            double broj = mat[i][j] * skalar;
                if(broj == -0){
                    red.push_back(0);
                }
                else{
                   red.push_back(broj);
                }
            }
        rez.push_back(red);
        red.clear();
        }

    return rez;
}

//Funkcija koja sabira dvije proslijedjene matrice
vector<vector<double>> Matrica::Sabiranje(vector<vector<double>> mat1,vector<vector<double>> mat2){
    if(mat1.size() != mat2.size() || mat1[0].size() != mat2[0].size()) throw "Matrice nisu istih dimenzija pa se ne mogu sabrati";

    vector<vector<double>> rezultat;
    vector<double> red;

    for(int i = 0; i < mat1.size();i++){
        for(int j = 0; j < mat1[i].size();j++){
            red.push_back(mat1[i][j] + mat2[i][j]);
        }
        rezultat.push_back(red);
        red.clear();
    }
    return rezultat;
}

//Funkcija koja oduzima dvije proslijedjene matrice
vector<vector<double>> Matrica::Oduzimanje(vector<vector<double>> mat1,vector<vector<double>> mat2){
    if(mat1.size() != mat2.size() || mat1[0].size() != mat2[0].size()) throw "Matrice nisu istih dimenzija pa se ne mogu oduzimati";

    vector<vector<double>> rezultat;
    vector<double> red;

    for(int i = 0; i < mat1.size();i++){
        for(int j = 0; j < mat1[i].size();j++){
            red.push_back(mat1[i][j] - mat2[i][j]);
        }

        rezultat.push_back(red);
        red.clear();
    }
    return rezultat;
}


#endif // MATRICA_CPP

