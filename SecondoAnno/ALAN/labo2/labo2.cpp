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


void printTermineNoto(vector<float> b){
    for(unsigned int i = 0; i<b.size(); ++i)
        cout << " " << b[i];
}

//-----------------------------------------------------------------------
//-------------------------------ESERCIZI--------------------------------
//-----------------------------------------------------------------------

vector<vector<int>> defMatricePascal() {
    //Creazione della matrice Pascal 10x10:
    const int DIM_MATRICE_PASCAL = 10;
    vector<vector<int>> matricePascal(DIM_MATRICE_PASCAL);

    for(int i = 0; i<DIM_MATRICE_PASCAL; ++i){
        //inizializza la riga i
        matricePascal[i] = vector<int>(DIM_MATRICE_PASCAL);

        for(int j = 0; j<DIM_MATRICE_PASCAL; ++j)
            //Riempi righe e colonne della matrice
            matricePascal[i][j] = (fattoriale(i+j-2) / (fattoriale(i-1) * fattoriale(j-1)));
    }

    return matricePascal;
}

//Funzione ausiliaria per creare ed inizializzare la matrice triangolare
vector<vector<int>> defMatriceTriangolare() {
    //utilizziamo il numero matricola di MARCO
    string nMatr = MARCO;

    char s0 = nMatr[LUNGH_MATR-1];
    char s1 = nMatr[LUNGH_MATR-2];
    //converti il char in se stesso ma numero
    int d0 = ((int)s0)-((int)'0');
    int d1 = ((int)s1)-((int)'0');

    //definisci la dimensione della matrice come definito nel PDF
    int DIM_MATRICE_TRIANGOLARE = 10*(d1+1)+d0;
    vector<vector<int>> matriceTriangolare(DIM_MATRICE_TRIANGOLARE);

    for(int i = 0; i < DIM_MATRICE_TRIANGOLARE; ++i){
        //inizializza la riga i
        matriceTriangolare[i] = vector<int>(DIM_MATRICE_TRIANGOLARE);

        //definisci gli elementi di tutta la matrice
        for(int j = 0; j < DIM_MATRICE_TRIANGOLARE; ++j)
            if(i == j)
                matriceTriangolare[i][j] = 2;
            else if(abs(i-j) == 1)
                matriceTriangolare[i][j] = -1;
            else
                matriceTriangolare[i][j] = 0;
    }

    return matriceTriangolare;
} 

//norma infinito definita come il max tra le norme dei vettori della matrice quadrata.
double normaInfinito(vector<vector<int>> matrice) {
    double normaInf;

    //per ogni vettore:
    for(unsigned int i = 0; i<matrice.size(); ++i){
        //variabile che contiene la somma di tutti gli elementi
        //del vettore i.
        double sommaElementiVettoreI = 0;

        //per ogni elemento del vettore i aggiungi il suo elevamento alla seconda
        for(unsigned int j = 0; j<matrice.size(); ++j)
            sommaElementiVettoreI += pow(matrice[i][j], 2);
        
        //se la norma i è la prima o è maggiore della norma 
        //infinito trovata fin'ora:
        double normaVettoreI = sqrt(sommaElementiVettoreI);
        if(i == 0 || normaVettoreI > normaInf)
            normaInf = normaVettoreI;
    }

    return normaInf;
}

void es1(vector<vector<int>> matrice1, vector<vector<int>> matrice2, vector<vector<int>> matricePascal, vector<vector<int>> matriceTriangolare) 
{

    cout << "\n--------------------------ESERCIZIO 1--------------------------\n";

    //--------------------------PARTE 1--------------------------

    cout << "Norma Infinito della matrice1: " << normaInfinito(matrice1) << "\n";
    cout << "Norma Infinito della matrice2: " << normaInfinito(matrice2) << "\n";
    
    //--------------------------PARTE 2--------------------------
    
    cout << "Norma Infinito della matrice di Pascal: " << normaInfinito(matricePascal) << "\n";

    //--------------------------PARTE 3--------------------------
    
    cout << "Norma Infinito della matrice triangolare: " << normaInfinito(matriceTriangolare) << "\n";
}

//A è la matrice in input.
//Questa funzione ritorna il termine noto b
vector<float> riduzioneGauss(vector<vector<int>> A){
    const int DIM = A.size();
    vector<float> b(DIM);

    //RIDUZIONE
    double mik; vector<float> kcolonna; int kmax;
     
    for(int k=1; k < DIM; k++){
        for(int h = k; h <= DIM; h++){
            kcolonna[h]=A[h][k];
            
            //cerca il pivot
            double maxmodulo=fabs(kcolonna[k]);
    
            int imax=k;
            
            for(int i=k+1; i< DIM; i++)
                if(!maxmodulo)
                    exit (1);
            
            kmax = imax;

            
            if(kmax!=k){
                double aux;
     
                for(int j=k; j< DIM; j++){
                    aux=A[j][k];
        
                    A[j][k]=A[j][kmax];
        
                    A[j][kmax]=aux;
                }
            };                               
        }
    
        for(int i = k+1; i < DIM; i++){
            mik=A[i][k]/A[k][k];
            
            for(int j = k+1; j < DIM; j++)
                A[i][j]=A[i][j]-mik*A[k][j];
            
            b[i]=b[i]-mik*b[k];
        }
    }

    return b;
}

//Funzione del secondo esercizio
void es2(vector<vector<int>> matrice1, vector<vector<int>> matrice2, vector<vector<int>> matricePascal, vector<vector<int>> matriceTriangolare) 
{

    cout << "\n--------------------------ESERCIZIO 2--------------------------\n";

    //--------------------------PARTE 1, 2 e 3--------------------------

    cout << "Eliminazione di Gauss della matrice1: ";
    printTermineNoto(riduzioneGauss(matrice1));

    cout << "\nEliminazione di Gauss della matrice2: ";
    printTermineNoto(riduzioneGauss(matrice2));
    
    cout << "\nEliminazione di Gauss della matrice di Pascal: ";
    printTermineNoto(riduzioneGauss(matricePascal));

    cout << "\nEliminazione di Gauss della matrice triangolare: ";
    printTermineNoto(riduzioneGauss(matriceTriangolare));
}

int main() {

    //Definizione ed inizializzazione delle prime due matrici
    vector<vector<int>> matrice1{{3, 0, 0, 0}, {1, 7, -3, 0}, {-1, -3, 9, 4}, {0, 0, -2, -10}};
    vector<vector<int>> matrice2{{2, 1, 3, 0}, {4, 3, -1, -1}, {-2, 0, 1, 2}, {0, 1, 2, 1}};

    //Definizione ed inizializzazione delle due matrici create dalle funzioni ausiliarie
    vector<vector<int>> matricePascal = defMatricePascal();
    vector<vector<int>> matriceTriangolare = defMatriceTriangolare();

    //esegui il primo esercizio
    es1(matrice1, matrice2, matricePascal, matriceTriangolare);

    //esegui il secondo esercizio
    es2(matrice1, matrice2, matricePascal, matriceTriangolare);

    return 0;
}