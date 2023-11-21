#include <string>
#include <iostream>
#include <cmath>
#include <iomanip> //necessario per la stampa di table ordinati

using namespace std;

//Codici matricola:
const string MARCO = "5562866";
const string ANNA = "5565836";

//Lunghezza del codice matricola
const int LUNGH_MATR = 7;


//-----------------------------------------------------------------------
//-------------------------FUNZIONI AUSILIARIE---------------------------
//-----------------------------------------------------------------------

//funzione ausiliaria per stampare delle tabelle su standard output
template<typename T> void stampaElemTabella(T t){
    cout << left << setw(16) << setfill(' ') << t;
}

//stampa un divisore per la tabella
void stampaDivisoreTabella(int nColonne) {
    for(int i = 0; i < nColonne; ++i)
        cout << "---------------";
    cout << "\n";
}

//calcola il fattoriale del numero n passato come argomento
double fattoriale(double n){
    double fattor = 1;
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

    //converti il char in se stesso ma come numero
    int d0 = ((int)s0)-((int)'0');
    int d1 = ((int)s1)-((int)'0');

    cout << "Numero matricola: " << nMatr << "; ultime due cifre: " << d0 << ", " << d1 << ".\n\n";

    //stampa gli header della tabella
    stampaElemTabella("i");
    stampaElemTabella("(a+b)+c");
    stampaElemTabella("a+(b+c)");
    cout << endl;
    stampaDivisoreTabella(3);
    
    //facendo i calcoli matematici, il risultato di a+b+c (indipendentemente dalle parentesi) dovrebbe essere a,
    //in quanto c = -b e quindi c e b si semplificano.
    //Come si vede dall'output del programma, il primo metodo di calcolo (a+b)+c è instabile, mentre il secondo è stabile
    //e riporta i risultati corretti per via dell'ordine delle cancellazioni.
    for(int i = 0; i <= 6; ++i){
        double a = (double)(d0+1)*pow(10, i); //10^i
        double b = (double)(d1+1)*pow(10, 20);//10^20
        double c = -b;                        //-b

        stampaElemTabella(i);
        stampaElemTabella((a+b)+c);
        stampaElemTabella(a+(b+c));
        cout << endl;
    }
    cout << endl << endl;
}

//l'argomento "bool reciproco" sta ad indicare se è da calcolare e stampare il reciproco
//della funzione fNx 
void es2(double x, bool reciproco) {

    cout << "---> Valore x in input: " << x << ":\n\n";

    double fx = f(x);
    cout << "output di f(x): " << fx << "\n\n";

    const int SIZE = 5;
    int numeri[SIZE] = {3, 10, 50, 100, 150};

    //stampa gli header della tabella
    stampaElemTabella("N");
    stampaElemTabella("fN(x)");
    stampaElemTabella("Err Ass");
    stampaElemTabella("Err Rel");
    if(reciproco)
        stampaElemTabella("Rec");
    
    cout << endl;
    stampaDivisoreTabella(reciproco ? 5 : 4);

    //esegui i calcoli e stampa una riga con i risultati
    for(int i = 0; i < SIZE; ++i){
        double fnx = fNx(numeri[i], x);
        
        //formula errore assoluto: EA = x('perturbata') - x
        double errAssoluto = fnx - fx;

        //formula errore relativo: ER = ( x('perturbata') - x ) / x
        double errRelativo = (fnx - fx)/fx;

        //il "reciproco di n" è quel numero che moltiplicato per n fa 1.
        double rec = 1/fnx;

        //stampa risultati ottenuti
        stampaElemTabella(numeri[i]);
        stampaElemTabella(fnx);
        stampaElemTabella(errAssoluto);
        stampaElemTabella(errRelativo);
        if(reciproco)
            stampaElemTabella(rec);
        
        cout << endl;
    }
    cout << endl << endl; 
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

    cout << "\n--------------------------ESERCIZIO 2--------------------------\n";
    cout << "ALGORITMO 1:\n";

    es2(0.5, false);
    es2(30, false);

    es2(-0.5, false);
    es2(-30, false);

    cout << "ALGORITMO 2:\n";

    es2(0.5, true);
    es2(30, true);

    cout << "\n--------------------------ESERCIZIO 3--------------------------\n";

    es3();

    return 0;
}