
# ACDC: Multithreading

Zoratti Marco, 5562866.

Consegna esercitazione sul multithreading. 



## Compilazione

Per compilare il file con libreria <thread>, bisogna eseguire su LINUX (o WSL):

```bash
  g++ -std=c++0x multithreading.cpp
```

Per compilare il file con libreria <Pthread>, bisogna eseguire su LINUX (o WSL):

```bash
  g++ -std=c++0x -pthread multithreading_Pthread.cpp
```


## Note

Nella consegna sono presenti due file:

- `multithreading.cpp`, che utilizza la libreria <thread> della STD;
- `multithreading_Pthread.cpp`, che utilizza la libreria <pthread>

#### Esecuzione del programma

Il programma genera un array di 1 di N elementi e ne modifica il K-esimo valore in 0.
Dopodiche esegue una ricerca di 0 sull'array con un numero T di thread.


NOTA: N, K e T vengolo scelti dall'utente.
Per comodità, assumiamo che N, K e T siano tutti numeri interi positivi e K sia divisore di N.

## Problematiche
- L'esecuzione del programma che utilizza la libreria <thread> non supporta array molto grandi, per esempio con un array di dimensione 1.000.000.000 ritorna `Segmentation fault`.

- L'esecuzione del programma che utilizza la libreria <pthread> non sempre completa la ricerca di un valore in un array. Non sono riuscito a capire se il problema sia relativo al mio computer, al mio codice o alla compilazione errata.

## Tempi di Esecuzione

Per comodità, assumiamo che l'elemento da cercare sia sempre nell'ultima posizione dell'array.

Tempi di esecuzione calcolati con la libreria <thread>:
#### Array di <1000 elementi
- ricerca con 1 thread: **1** microsecondo;
- ricerca con 2 thread: <**1** microsecondo;
- ricerca con 5 thread: <**1** microsecondo;

#### Array di 10.000 elementi
- ricerca con 1 thread: **24** microsecondi;
- ricerca con 2 thread: **9** microsecondi;
- ricerca con 5 thread: **4** microsecondi;

#### Array di 100.000 elementi
- ricerca con 1 thread: **253** microsecondi;
- ricerca con 2 thread: **123** microsecondi;
- ricerca con 5 thread: **42** microsecondi;

#### Array di 1.000.000 elementi
- ricerca con 1 thread: **2202** microsecondi;
- ricerca con 2 thread: **1187** microsecondi;
- ricerca con 5 thread: **419** microsecondi;