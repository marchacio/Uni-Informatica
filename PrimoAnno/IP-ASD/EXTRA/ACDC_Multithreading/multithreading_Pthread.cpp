#include <pthread.h>
#include <iostream>
#include <chrono>
#include <string>

using namespace std;


/*
Il seguente codice genera un array di 1 di N elementi e ne modifica il K-esimo valore in 0.
Dopodiche esegue una ricerca di 0 sull'array con T thread.


NOTA: N, K e T vengolo scelti dall'utente;
Per comodità, assumiamo che N, K e T siano tutti numeri interi positivi.
*/


//errore in caso N/K/T siano valori non corretti
void err(){
    cout << "Valore non valido";
    exit(1);
}

//struct per passare valori ai thread
struct threadData {
    int* array;
    int size;

    //puntatore ad una lista di thread per poterli fermare tutti una volta trovato l'elemento
    pthread_t* threads;
    int sizeThreads;
};


//funzione per cercare un elemento in un array 
void* ricercaElemento(void* threadarg){

    struct threadData *data;
    data = (struct threadData *) threadarg;

    auto time1 = chrono::high_resolution_clock::now();

    for(int i = 0; i < data->size; ++i){
        if(data->array[i] == 0){
            //caso in cui è stato trovato l'elemento;
            //blocca gli altri thread
            cout<< "trovato";

            auto time2 = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::seconds>(time2 - time1);
            cout << duration.count() << " second(s)"<< endl;

            for(int j = 0; j < data->sizeThreads; ++j)
                pthread_exit(&(data->threads[j]));

        }
    }

    return NULL;
}

int main() {

    int n, k, t;    

    cout << "Quanto deve essere lungo l'array? ";
    cin >> n;

    if(n <= 0)
        err();

    cout << "Quale elemento vuoi modificare (0 < elem < " << n << ")? ";
    cin >> k;

    if(k <= 0 || k >= n)
        err();
    
    cout << "Con quanti thread vuoi eseguire la ricerca (inserire valore che sia divisore di " << n << ")? ";
    cin >> t;

    if(t <= 0 || t >= n || (n % t) != 0)
        err();

    //Generazione di un array di N elementi inizializzati con 1
    int array[n];
    for(int i = 0; i < n; ++i)
        array[i] = 1;

    //Modifica il k-esimo elemento dell'array
    array[k] = 0;

    //partiziona gli array in una matrice di t colonne da n/t elementi;
    int numeroElementiPerArray = n/t;
    int matrice[t][numeroElementiPerArray];

    for(int i = 0; i < t; ++i){
        for(int j = 0; j < numeroElementiPerArray; ++j){
            int index = numeroElementiPerArray*i + j;
            matrice[i][j] = array[index];
        }
    }

    //Inizializza la ricerca sulla matrice:
    
    //crea un'array di thread
    pthread_t threads[t];
    /*
    for(int i = 0; i < t; ++i){
        pthread_t thread;
        threads[i] = thread;
    }
    */
    
    //per ogni thread, crealo e fai partire la ricerca;
    for(int i = 0; i < t; ++i){
        threadData data = {matrice[i], numeroElementiPerArray, threads, t};

        threads[i] = pthread_create(&threads[i], NULL, ricercaElemento, (void *)&data); 
    }
 

    //dopodiche aspetta che finisca la sua esecuzione, in questo modo evita che il main termini prima della fine della ricerca
    for (int i = 0; i < t; i++)
       pthread_join(threads[i], NULL);

}