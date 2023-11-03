#include <string>
#include <iostream>
#include <cmath>

using namespace std;

//Codici matricola:
const string MARCO = "5562866";
const string ANNA = "5565836";

//Lunghezza del codice matricola
const int LUNGH_MATR = 7;

//-----------------------------------------------------------------------
//-------------------------FUNZIONI MATEMATICHE--------------------------
//-----------------------------------------------------------------------

int fattoriale(int n){
    if(n == 0) //caso base
        return n;
    
    return n*fattoriale(n-1);
}

double f(double x) {
    return exp(x);
}

double fNx(double n, double x) {
    if(x == 0)
        throw "x uguale a 0, errore!";

    if(n == 0) //caso base:
        return 1; //questo perche x^n/n! -> x^0/1 -> 1/1

    return (pow(x, n)/fattoriale(n)) + fNx(n-1, x);
}

//-----------------------------------------------------------------------
//-------------------------------ESERCIZI--------------------------------
//-----------------------------------------------------------------------

void es1() {

    //utilizziamo il numero matricola di ANNA
    string nMatr = ANNA;

    char s0 = nMatr[LUNGH_MATR-1];
    char s1 = nMatr[LUNGH_MATR-2];

    int d0 = ((int)s0)-((int)'0');
    int d1 = ((int)s0)-((int)'0');
    
    for(int i = 0; i <= 6; ++i){
        double a = (double)(d0+1)*pow(10, i);
        double b = (double)(d1+1)*pow(10, 20);
        double c = -b;

        cout << (a+b)+c << "   " << a+(b+c) << "\n";
    }
}

void es2(double x1, double x2) {

    cout << "Valori x in input: " << x1 << " " << x2 << ":\n";

    cout << "f: " <<  f(x1) << "   " << f(x2) << "\n";

    const int SIZE = 5;
    int numeri[SIZE] = {3, 10, 50, 100, 150};

    for(int i = 0; i < SIZE; ++i)
        cout << "fN: " <<  fNx(numeri[i], x1) << "   " << fNx(numeri[i], x2) << "\n";
    
}


int main() {

    //es1();

    es2(0.5, 30);
    cout << "\n\n";
    es2(-0.5, -30);

    return 0;
}