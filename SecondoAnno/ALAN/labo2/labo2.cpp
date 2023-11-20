#include <string>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

//Codici matricola:
const string MARCO = "5562866";
const string ANNA = "5565836";

//Lunghezza del codice matricola
const int LUNGH_MATR = 7;

//-----------------------------------------------------------------------
//-------------------------FUNZIONI AUSILIARIE---------------------------
//-----------------------------------------------------------------------

double fattoriale(double n){
    double fattor = 1;
    for (int i = 1; i <= n; i++)
        fattor *= i;
    
    return fattor;
}

//-----------------------------------------------------------------------
//-------------------------------ESERCIZI--------------------------------
//-----------------------------------------------------------------------

//Dimensione predefinita delle matrici del primo esercizio, prima richiesta (a)
const int DIM_MATRICE_ES1A = 4;

//Dimensione predefinita della matrice di pascal del primo esercizio, 
//seconda richiesta (b)
const int DIM_MATRICE_PASCAL = 10;

//norma infinito definita come il max tra le norme dei vettori della matrice quadrata.
double normaInfinito(vector<vector<int>> matrice, const int DIM_MATRICE) {
    double normaInf;

    //per ogni vettore:
    for(int i = 0; i<DIM_MATRICE; ++i){
        //variabile che contiene la somma di tutti gli elementi
        //del vettore i.
        double sommaElementiVettoreI = 0;

        //per ogni elemento del vettore i aggiungi il suo elevamento alla seconda
        for(int j = 0; j<DIM_MATRICE; ++j)
            sommaElementiVettoreI += pow(matrice[i][j], 2);
        
        //se la norma i è la prima o è maggiore della norma 
        //infinito trovata fin'ora:
        double normaVettoreI = sqrt(sommaElementiVettoreI);
        if(i == 0 || normaVettoreI > normaInf)
            normaInf = normaVettoreI;
    }

    return normaInf;
}

void es1() {

    cout << "\n--------------------------ESERCIZIO 1--------------------------\n";

    //--------------------------PARTE 1--------------------------
    vector<vector<int>> matrice1{{3, 0, 0, 0}, {1, 7, -3, 0}, {-1, -3, 9, 4}, {0, 0, -2, -10}};
    vector<vector<int>> matrice2{{2, 1, 3, 0}, {4, 3, -1, -1}, {-2, 0, 1, 2}, {0, 1, 2, 1}};

    cout << "Norma Infinito della matrice1: " << normaInfinito(matrice1, DIM_MATRICE_ES1A) << "\n";
    cout << "Norma Infinito della matrice2: " << normaInfinito(matrice2, DIM_MATRICE_ES1A) << "\n";
    
    //--------------------------PARTE 2--------------------------
    //CREA LA MATRICE PASCAL 10x10:
    vector<vector<int>> matricePascal(DIM_MATRICE_PASCAL);

    for(int i = 0; i<DIM_MATRICE_PASCAL; ++i){
        //inizializza la riga i
        matricePascal[i] = vector<int>(DIM_MATRICE_PASCAL);

        for(int j = 0; j<DIM_MATRICE_PASCAL; ++j)
            //Riempi righe e colonne della matrice
            matricePascal[i][j] = (fattoriale(i+j-2) / (fattoriale(i-1) * fattoriale(j-1)));
    }
    
    cout << "Norma Infinito della matrice di Pascal: " << normaInfinito(matricePascal, DIM_MATRICE_PASCAL) << "\n";

    //--------------------------PARTE 3--------------------------
    //utilizziamo il numero matricola di MARCO
    string nMatr = MARCO;

    char s0 = nMatr[LUNGH_MATR-1];
    char s1 = nMatr[LUNGH_MATR-2];
    //converti il char in se stesso ma numero
    int d0 = ((int)s0)-((int)'0');
    int d1 = ((int)s1)-((int)'0');

    int DIM_MATRICE_TRIANGOLARE = 10*(d1+1)+d0; //76
    vector<vector<int>> matriceTriangolare(DIM_MATRICE_TRIANGOLARE);

    for(int i = 0; i < DIM_MATRICE_TRIANGOLARE; ++i){
        //inizializza la riga i
        matriceTriangolare[i] = vector<int>(DIM_MATRICE_TRIANGOLARE);

        for(int j = 0; j < DIM_MATRICE_TRIANGOLARE; ++j)
            if(i == j)
                matriceTriangolare[i][j] = 2;
            else if(abs(i-j) == 1)
                matriceTriangolare[i][j] = -1;
            else
                matriceTriangolare[i][j] = 0;
    }
    
    cout << "Norma Infinito della matrice triangolare: " << normaInfinito(matriceTriangolare, DIM_MATRICE_TRIANGOLARE) << "\n";
}

int main() {

    es1();

    return 0;
}