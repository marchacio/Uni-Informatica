/////////////////////////////////////////////////////////////////////
//
// Laboratorio 4: calcolo di semplici espressioni numeriche
//                mediante pile e code
//
// vengono accettati dall'esterno solo numeri positivi.
// Per trattare anche numeri negativi occorre modificare
// l'analizzatore lessicale.
//
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "token.h"
#include "queue.h"
#include "stack.h"

using std::cout;
using std::cin;
using std::string;
using std::istringstream;
using std::ostringstream;

/////////////////////////////////////////////////////////////////////
// Funzioni principali: leggi() e calcola()
/////////////////////////////////////////////////////////////////////

// Estrae uno dopo l'altro i token dalla stringa "str", inserendoli via via nella coda "codaToken"
bool leggi(const string &str, queue::Queue &codaToken) {

  try {
    //inizializza la coda contenente i Token
    codaToken = queue::createEmpty();

    //definisci i dati da dare a prossimoToken
    token tok;
    std::istringstream iss(str);

    while(prossimoToken(iss, tok)){
      enqueue(tok, codaToken);
    }

    //debug; controlla che tutto sia stato letto correttamente
    //printQueue(codaToken);

    return true;
  } catch(...){
    return false;
  }  
}

// Estrae uno dopo l'altro i token dalla coda, inserendoli via via sullo stack.
// Appena si incontra un token PARENTESI CHIUSA, quello segnala la fine
// di una sottoespressione; allora tiriamo giu' dallo stack gli ultimi cinque token inseriti.
// I token estratti dovrebbero essere esattamente, nell'ordine:
// un ")", un numero, un operatore aritmetico, un altro
// numero, e un "("; se non è così, allora si segnala
// errore sintattico e l'algoritmo termina.
// A questo punto la funzione deve convertire i token di tipo NUMERO in numeri interi,
// eseguire l'operazione aritmetica opportuna, e trasformare il risultato da numero a
// token e inserire quest'ultimo sullo stack.
// Alla fine se non ci sono errori sintattici la funzione deve mettere nella variabile
// risultato il valore dell'espressione
bool calcola(queue::Queue codaToken, int &risultato) {

  stack::Stack s;

  //per ogni elemento della coda:
  for(int i = 0; i < codaToken.size; ++i){

    //debug;
    //cout << "elemento valutato: " << codaToken.queue[i].val << "\n\n";
    
    if(codaToken.queue[i].k == kind::PARENTESI_CHIUSA){
      push(codaToken.queue[i], s);

      //se il token è una parentesi chiusa calcola il risultato dei 5 token precedenti
      token parentesiChiusa = pop(s);
      token primoNumero = pop(s);
      token operatore = pop(s);
      token secondoNumero = pop(s);
      token parentesiAperta = pop(s);

      //controlla che non ci siano errori sintattici
      if(parentesiChiusa.k != kind::PARENTESI_CHIUSA || parentesiAperta.k != kind::PARENTESI_APERTA 
        || primoNumero.k != kind::NUMERO || secondoNumero.k != kind::NUMERO 
        || (operatore.k != kind::OP_MOLTIPLICAZIONE && operatore.k != kind::OP_SOMMA && operatore.k != kind::OP_SOTTRAZIONE))
        return false; //errore sintattico

      //se non ci sono errori sintattici, calcola e inserisci nello stack
      int pn = str2int(primoNumero.val);
      int sn = str2int(secondoNumero.val);

      int res;
      if(operatore.k == kind::OP_MOLTIPLICAZIONE)
        res = pn * sn;
      else if(operatore.k == kind::OP_SOMMA)
        res = pn + sn;
      else if(operatore.k == kind::OP_SOTTRAZIONE)
        res = sn - pn;

      
      token tok = {int2str(res), kind::NUMERO};
      push(tok, s);
    } else {
      //se il token non è una parentesi chiusa, inseriscilo nello stack
      push(codaToken.queue[i], s);
    }
  }

  //ricava il risultato in int solo se hai un solo numero in coda
  if(s->next == stack::EMPTYSTACK && s->elem.k == kind::NUMERO){
    token t = s->elem;

    risultato = str2int(t.val);
    return true;
  } else 
    return false; //errore sintattico
}

/////////////////////////////////////////////////////////////////////
//                               MAIN
/////////////////////////////////////////////////////////////////////

int main() {

  string s;
  queue::Queue q;
  int r;

  cout << "Inserisci l'espressione che vuoi valutare: " << endl;
  getline(cin,s);

  if (!leggi(s,q)) {
    cerr << "errore lessicale" << endl;
    exit(1);
  }

  if (!calcola(q,r)) {
    cerr << "errore sintattico" << endl;
    exit(2);
  }

  cout << "risultato: " << r << endl;
  exit(0);
}
