/////////////////////////////////////////////////////////////////////
//
// Laboratorio 3: calcolo di semplici espressioni numeriche
//                mediante pile e code
//
// vengono accettati dall'esterno solo numeri positivi.
// Per trattare anche numeri negativi occorre modificare
// l'analizzatore lessicale.
//
///////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "token.h"

using std::cout;
using std::cin;
using std::string;
using std::istringstream;
using std::ostringstream;

/////////////////////////////////////////////////////////////////////
// Funzioni ausiliarie su tipi di dato semplici
/////////////////////////////////////////////////////////////////////

// da stringa a numero
int str2int(const string &s) {
  int pn;
  istringstream itmp(s);
  itmp >> pn;

  return pn;
}

// da numero a stringa
string int2str(int n) {
  ostringstream otmp;
  otmp << n;

  return otmp.str();
}


//funzione ausiliaria per determinare se la stringa è un numero o no
bool isNumber(string str){
  bool isNumber = true;

  for(int i = 0; i < str.size(); ++i){
    if(!isdigit(str[i])){
      isNumber = false;
      break;
    }
  }

  return isNumber;
}

// ritorna false se e solo se non si può leggere un token dall'input stream;
// inserisce in t il token letto
bool prossimoToken(istringstream &iss, token &t) {
  string s;
  iss >> s;

  if (!iss) {
    // lo stream `e terminato:
    // gestire la fine dell’input
    return false;

  } else {

    //nel caso ci sia uno spazio, saltalo e continua la lettura con i prossimi elementi
    if(s == " ")
      return true;

    t.val = s;

    if(s == "(")
      t.k = kind::PARENTESI_APERTA;
    else if(s == ")")
      t.k = kind::PARENTESI_CHIUSA;
    else if(s == "+")
      t.k = kind::OP_SOMMA;
    else if(s == "-")
      t.k = kind::OP_SOTTRAZIONE;
    else if(s == "*")
      t.k = kind::OP_MOLTIPLICAZIONE;
    else if(isNumber(s))
      t.k = kind::NUMERO;
    else
      throw "Errore lessicale: simbolo sconosciuto";
    
    return true;
  }
}