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

//Funzione che stampa un vettore 
void printVettore(vector<float> v) {
	cout << "[";
	for(float el : v)
		cout << el << " ";
	cout << "]" << endl;
}

//Funzione che stampa la matrice data.
//
void printMatrice(vector<vector<float>> A) {
	for(vector<float> v : A)
		printVettore(v);
}

//-----------------------------------------------------------------------
//-------------------------------ESERCIZI--------------------------------
//-----------------------------------------------------------------------

//------------------------------------------------------------------------
//------------------------------ESERCIZIO 1-------------------------------
//------------------------------------------------------------------------

vector<vector<float>> defMatricePascal() {
    //Creazione della matrice Pascal 10x10:
    const int DIM_MATRICE_PASCAL = 10;
    vector<vector<float>> matricePascal(DIM_MATRICE_PASCAL, vector<float>(DIM_MATRICE_PASCAL));

    //Inizializza i dati all'interno della matrice
    for(int i = 0; i<DIM_MATRICE_PASCAL; ++i)
        for(int j = 0; j<DIM_MATRICE_PASCAL; ++j)
            //Riempi righe e colonne della matrice
            matricePascal[i][j] = (fattoriale(i+j-2) / (fattoriale(i-1) * fattoriale(j-1)));
    
    return matricePascal;
}

//Funzione ausiliaria per creare ed inizializzare la matrice triangolare
vector<vector<float>> defMatriceTriangolare() {
    //utilizziamo il numero matricola di MARCO
    string nMatr = MARCO;

    char s0 = nMatr[LUNGH_MATR-1];
    char s1 = nMatr[LUNGH_MATR-2];
    //converti il char in se stesso ma numero
    int d0 = ((int)s0)-((int)'0');
    int d1 = ((int)s1)-((int)'0');

    //definisci la dimensione della matrice come definito nel PDF
    int DIM_MATRICE_TRIANGOLARE = 10*(d1+1)+d0;
    vector<vector<float>> matriceTriangolare(DIM_MATRICE_TRIANGOLARE, vector<float>(DIM_MATRICE_TRIANGOLARE));

    for(int i = 0; i < DIM_MATRICE_TRIANGOLARE; ++i)
        //definisci gli elementi di tutta la matrice
        for(int j = 0; j < DIM_MATRICE_TRIANGOLARE; ++j)
            if(i == j)
                matriceTriangolare[i][j] = 2;
            else if(abs(i-j) == 1)
                matriceTriangolare[i][j] = -1;
            else
                matriceTriangolare[i][j] = 0;

    return matriceTriangolare;
} 

//norma infinito definita come il max tra le norme dei vettori della matrice quadrata.
float normaInfinito(vector<vector<float>> matrice) {
    float normaInf;

    //per ogni vettore:
    for(unsigned int i = 0; i<matrice.size(); ++i){
        //variabile che contiene la somma di tutti gli elementi
        //del vettore i.
        float sommaElementiVettoreI = 0;

        //per ogni elemento del vettore i aggiungi il suo elevamento alla seconda
        for(unsigned int j = 0; j<matrice.size(); ++j)
            sommaElementiVettoreI += pow(matrice[i][j], 2);
        
        //se la norma i è la prima o è maggiore della norma 
        //infinito trovata fin'ora:
        float normaVettoreI = sqrt(sommaElementiVettoreI);
        if(i == 0 || normaVettoreI > normaInf)
            normaInf = normaVettoreI;
    }

    return normaInf;
}

void es1(vector<vector<float>> matrice1, vector<vector<float>> matrice2, vector<vector<float>> matricePascal, vector<vector<float>> matriceTriangolare) 
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

//------------------------------------------------------------------------
//------------------------------ESERCIZIO 2-------------------------------
//------------------------------------------------------------------------

//Funzione che calcola e ritorna il termine noto del sistema Ax = b con x = {1, ..., 1}.
vector<float> calcolaB(vector<vector<float>> A) {
	// numeroR_A è il numero di Righe della matrice A
	unsigned int numeroR_A = A.size();
    // numeroC_A è il numero di Colonne della matrice A
	unsigned int numeroC_A = A[0].size(); 
	
	vector<float> b(numeroR_A); // Inizializzazione di b

	//Scansione della matrice A per il calcolo del vettore b:
    //  dato che x = {1, ..., 1}, per trovare il termine noto dell'equazione avente come 
    //  coefficienti i valori alla riga i della matrice A, basta sommare questi valori tra loro
	for(unsigned int i = 0; i < numeroR_A; ++ i)
		for(unsigned int j = 0; j < numeroC_A; ++ j)
			b[i] += A[i][j]; 
	
	return b;
}

//Funzione che fa il merge di una matrice A e un vettore b
vector<vector<float>> merge(vector<vector<float>> A, vector<float> b) {

    //numeroR_A è il numero di righe della matrice A e del vettore b
	unsigned int numeroR_A = A.size(); 
	vector<vector<float>> matriceFinale = A;

	for(unsigned int i = 0; i < numeroR_A; ++ i)
		matriceFinale[i].push_back(b[i]);
		
	return matriceFinale;
}

//Funzione che effetua il pivoting parziale dove: 
//  A è la matrice sulla quale si effettua il pivoting parziale
//  b è il vettore dei termini noti sul quale si effettua il pivoting parziale
//  k è la riga presa in considerazione per l'esecuzione del pivoting parziale
void pivotingParziale(vector<vector<float>>& A, vector<float>& b, unsigned int k) {

	//i_max contiene la riga avente pivot di modulo massimo se scambiata con la riga k;
    //inizialmente tale riga è proprio k
	unsigned int i_max = k;	

    //numeroR_A è il numero di righe della matrice A e del vettore b
	unsigned int numeroR_A = A.size(); 
	
	//Scansione di tutti i valori sulla colonna k e sulle righe i > k
	for(unsigned int i = k+1; i < numeroR_A; ++ i)
        //se A[i][k] (valore corrente) è maggiore del pivot di massimo modulo corrente, 
        //allora A[i][k] diventa il nuovo pivot di massimo modulo corrente
		if(abs(A[i][k]) > abs(A[i_max][k])) 
			i_max = i;
	
	//Se è stata trovata una riga, diversa da k, avente pivot di modulo maggiore (e massimo) 
    //se scambiata con la riga k, allora viene effettuato tale scambio
	if(k != i_max) {
		//scambio dei valori interessati all'interno del vettore b dei termini noti
		swap(b[i_max], b[k]);
		
		//scambio delle righe interessate all'interno della matrice A
		swap(A[i_max], A[k]);
	}	
}


//Funzione che esegue l'Eliminazione Gaussiana sulla matrice A e 
//il vettore b dei termini noti
vector<vector<float>> Gauss(vector<vector<float>> A, vector<float> b) {

	float pivot;

    // Fattore moltiplicativo
	float m; 
	
    //numeroR_A è il numero di righe della matrice A e del vettore b
	unsigned int numeroR_A = A.size(); 
    //numeroC_A è il numero di colonne della matrice A
	unsigned int numeroC_A = A[0].size(); 
	
    //Variabile che conterrà la matrice A ridotta
	vector<vector<float>> ridotta_A = A; 
    //Variabile che conterrà il vettore b ridotto
	vector<float> ridotta_B = b; 

	//Algoritmo di Eliminazione Gaussiana
	for(unsigned int k = 0; k < numeroR_A-1; ++ k) {

		//Esecuzione del pivoting parziale, per essere sicuri di avere il pivot 
        //modulo più grande possibile e diverso da zero
		pivotingParziale(ridotta_A, ridotta_B, k);
		
		//Assegnazione del pivot
		pivot = ridotta_A[k][k];
		
		//Azzeramento dei valori sotto al pivot e conseguente modifica delle loro righe
		for(unsigned int i = k+1; i < numeroR_A; ++ i) {
			
			//Calcolo del fattore moltiplicativo
			m = ridotta_A[i][k] / pivot;
			
			//Modifica di b
			ridotta_B[i] = ridotta_B[i] - m*ridotta_B[k];
			
			//Modifica della riga i
			for(unsigned int j = k; j < numeroC_A; ++ j)
				ridotta_A[i][j] = ridotta_A[i][j] - m*ridotta_A[k][j];
		}
	}
	
	//ritorna l'unione di A e b ridotti per avere un'unica matrice ridotta A|b
	return merge(ridotta_A, ridotta_B);
}

//Funzione che divide una matrice A dal vettore b e lo ritorna
vector<float> dividi(vector<vector<float>>& A) {

    //numeroR_A è il numero di righe della matrice A e del vettore b
	unsigned int numeroR_A = A.size(); 
	vector<float> b(numeroR_A);

	for(unsigned int i = 0; i < numeroR_A; ++ i) {
		b[i] = A[i].back();
		A[i].pop_back();
	}
		
	return b;
}


//Funzione che esegue la sostituzione all'indietro sulla matrice A e il vettore b 
//dei termini noti (entrambi ridotti)
vector<float> sostituzioneIndietro(vector<vector<float>> A) {

    //Dividi A da b in A|b ridotta
	vector<float> b = dividi(A); 
	
    //numeroR_A è il numero di righe della matrice A e del vettore b
	unsigned int numeroR_A = A.size();
    //numeroC_A è il numero di colonne della matrice A 
	unsigned int numeroC_A = A[0].size(); 
	
    //il vettore x conterrà le soluzioni del sistema
	vector<float> x(numeroR_A); 

	//Scansione di tutte le righe della matrice a partire dall'ultima
	for(int i = numeroR_A - 1; i >= 0; --i) {
		
		//Inizializzazione del termine noto dell'equazione
		float local_b = b[i];

        //Per ogni j > i nella riga corrente, è stata trovata la soluzione x[j].
        //Di conseguenza il termine noto dell'equazione corrente si ottiene sottraendo 
        //a b[i] tutte x[j] note moltiplicate per i rispettivi coefficienti A[i][j]
		for(int j = numeroC_A - 1; j > i; --j) 
			local_b -= A[i][j]*x[j];     
		
        //Finito il ciclo, si è arrivati nella posizione i, quella per la quale manca la soluzione x[i];
        //quest'ultima viene quindi trovata facendo il rapporto tra il termine noto ricavato sopra e il coefficiente di x[i]
		x[i] = local_b/A[i][i];			
	}	
	
	return x;		
}

//calcola e stampa i vari punti dell'es 2
void es2_singolaMatrice(vector<vector<float>> A) {

	//Calcolo del termine noto del sistema Ax = b con x = {1 ... 1}
	vector<float> b = calcolaB(A);
	
	cout << "Il termine noto è: " << endl;
	printVettore(b);
	
	//Risoluzione del sistema Ax = b (perturbato)
	vector<vector<float>> reduced_Ab = Gauss(A, b);
	
	//Stampa di A|b ridotta
	cout << "\nLa riduzione Gaussiana è: " << endl;
	
	printMatrice(reduced_Ab);
	
	//Sostituzione all'indietro per ricavare il vettore delle soluzioni x
	vector<float> x = sostituzioneIndietro(reduced_Ab);
	
	cout << "x è uguale a:" << endl;
	printVettore(x);
}

//Funzione del secondo esercizio
void es2(vector<vector<float>> matrice1, vector<vector<float>> matrice2, vector<vector<float>> matricePascal, vector<vector<float>> matriceTriangolare) 
{
    cout << "\n--------------------------ESERCIZIO 2--------------------------\n";

    //esegui l'es2 per ogni matrice
    cout << "\n-- Matrice 1" << endl;
    es2_singolaMatrice(matrice1);
    cout << "\n-- Matrice 2" << endl;
    es2_singolaMatrice(matrice2);
    cout << "\n-- Matrice di Pascal" << endl;
    es2_singolaMatrice(matricePascal);
    cout << "\n-- Matrice Triangolare" << endl;
    es2_singolaMatrice(matriceTriangolare);
}

int main() {

    //Definizione ed inizializzazione delle prime due matrici
    vector<vector<float>> matrice1{{3, 0, 0, 0}, {1, 7, -3, 0}, {-1, -3, 9, 4}, {0, 0, -2, -10}};
    vector<vector<float>> matrice2{{2, 1, 3, 0}, {4, 3, -1, -1}, {-2, 0, 1, 2}, {0, 1, 2, 1}};

    //Definizione ed inizializzazione delle due matrici create dalle funzioni ausiliarie
    vector<vector<float>> matricePascal = defMatricePascal();
    vector<vector<float>> matriceTriangolare = defMatriceTriangolare();

    //Stampa tutte le matrici
    cout << "Le matrici analizzate:\n--Matrice 1:\n";
    printMatrice(matrice1);
    cout << "\n--Matrice 2:\n";
    printMatrice(matrice2);
    cout << "\n--Matrice di Pascal:\n";
    printMatrice(matricePascal);
    cout << "\n--Matrice Triangolare:\n";
    printMatrice(matriceTriangolare);

    //esegui il primo esercizio
    es1(matrice1, matrice2, matricePascal, matriceTriangolare);

    //esegui il secondo esercizio
    es2(matrice1, matrice2, matricePascal, matriceTriangolare);

    return 0;
}