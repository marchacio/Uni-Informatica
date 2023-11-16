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
    int fattor = 1;
    for (int i = 1; i <= n; i++)
        fattor *= i;
    
    return fattor;
}

//funzione esponenziale
double f(double x) {
    return exp(x);
}

//funzione Polinomio di Taylor
double fNx(double n, double x) {
    if(x == 0)
        throw "x uguale a 0, errore!"; //0^0 -> F.I.

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

    //converti il char in se stesso ma numero
    int d0 = ((int)s0)-((int)'0');
    int d1 = ((int)s1)-((int)'0');

    cout << "Numero matricola: " << nMatr << "; ultime due cifre: " << d0 << ", " << d1 << ".\n";
    
    //facendo i calcoli matematici, il risultato di a+b+c (indipendentemente dalle parentesi) dovrebbe essere a,
    //in quanto c = -b e quindi c e b si semplificano.
    //Come si vede dall'output del programma, il primo metodo di calcolo (a+b)+c è instabile, mentre il secondo è stabile
    //e riporta i risultati corretti.
    for(int i = 0; i <= 6; ++i){
        double a = (double)(d0+1)*pow(10, i);
        double b = (double)(d1+1)*pow(10, 20);
        double c = -b;

        cout << (a+b)+c << "\t" << a+(b+c) << "\n";
    }
}

void es2(double x1, double x2) {

    cout << "Valori x in input: " << x1 << ", " << x2 << ":\n\n";

    double fx1 = f(x1);
    double fx2 = f(x2);

    cout << "output di f: " << fx1 << "   " << fx2 << "\n\n";

    const int SIZE = 5;
    int numeri[SIZE] = {3, 10, 50, 100, 150};

    for(int i = 0; i < SIZE; ++i){
        double fNx1 = fNx(numeri[i], x1);
        double fNx2 = fNx(numeri[i], x2);
        
        //formula errore assoluto: EA = x('perturbata') - x
        double errAssoluto1 = fNx1 - fx1;
        double errAssoluto2 = fNx2 - fx2;

        //formula errore relativo: ER = ( x('perturbata') - x ) / x
        double errRelativo1 = (fNx1 - fx1)/fx1;
        double errRelativo2 = (fNx2 - fx2)/fx2;

        //il "reciproco di n" è quel numero che moltiplicato per n fa 1.
        double reciproco1 = 1/fNx1;
        double reciproco2 = 1/fNx2;

        //stampa risultati ottenuti
        cout << "fN(N = " << numeri[i] << "): " << fNx1 << " (EA: " << errAssoluto1 << ", ER: " << errRelativo1 << ", REC: " << reciproco1 << ")   " 
        << fNx2 << " (EA: " << errAssoluto2 << ", ER: " << errRelativo2 << ", REC: " << reciproco2 << ").\n";
    }    
}

/*
Implementare un programma che determina la precisione di macchina eps, ossia il valore positivo eps =2^(−d), 
dove d è il piu grande intero positivo tale che 1 + 2^(−d) > 1 in aritmetica di macchina; calcolarne il
valore sia in singola che in doppia precisione.
*/
void es3(){
    
    //singola precisione
    float eps = 1;
    while(eps+1 != 1) //ovvero fino a quando eps non risulta 0
        eps /= 2;

    cout << "Precisione di macchina (eps) in singola precisione: " << eps << "\n";

    //doppia precisione
    double eps2 = 1;
    while(eps2+1 != 1) //ovvero fino a quando eps non risulta 0
        eps2 /= 2;

    cout << "Precisione di macchina (eps) in doppia precisione: " << eps2 << "\n";
}


//-----------------------------------------------------------------------
//---------------------------------MAIN----------------------------------
//-----------------------------------------------------------------------
int main() {

    cout << "\n--------------------------ESERCIZIO 1--------------------------\n";
    es1();

    cout << "\n\n--------------------------ESERCIZIO 2--------------------------\n";

    es2(0.5, 30);
    cout << "\n\n";
    es2(-0.5, -30);

    cout << "\n\n--------------------------ESERCIZIO 3--------------------------\n";

    es3();

    return 0;
}