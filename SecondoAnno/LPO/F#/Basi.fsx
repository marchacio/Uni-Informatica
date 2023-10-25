//dichiarazione di variabili
let x = 2;;
let y = x+40;; // 42

let a,b = 2, 42;;


//-----------------------------------
//------------OP BOOLEANE------------
//-----------------------------------

let b1 = true;;
let b2 = false;;

b1 = b2;; //false, nota: l'uguaglianza viene eseguita con un solo "="
b1 && b2;; //false
b1 || b2;; //true
not b1;; //false, nota: il not ha precedenza sugli altri operatori

//If [CONDIZIONE] then [ESPRESSIONE 1] else [ESPRESSIONE 2]
if b1 then 1 else 2;; 


//----------------------------------
//------------RICORSIONE------------
//----------------------------------

///In questo esempio si dichiara una funzione ricorsiva che calcola 
/// il fattoriale di un numero.
/// Dato che è ricorsiva, bisogna specificare "rec" subit dopo "let"
let rec fact x = 
    if x = 0 then 1 else x * fact (x-1);;


//-----------------------------
//------------LISTE------------
//-----------------------------

//Si possono definire in 2 modi (il secondo è il più usato e "comodo"):
// primo modo, aggiungere gli elementi uno alla volta distanziati da ::
let ls = 1::2::3::[];; // [1;2;3]

// secondo modo: classico modo di definire una lista in tutti i linguaggi
let ls2 = [1;2;3];; // [1;2;3]

//ovviamente gli elementi dentro le liste possono essere stringhe, tuple,
//funzioni, altre liste...
//Le liste devono essere omogenee, non si possono mescolare tipi diversi!

//Per concatenare liste dello stesso tipo (vedi TIPI), si usa l'operatore "@":
[2]@[3];; //[2; 3]

//Nota, l'operatore @ è verso dall'operatore :: usato nelle dichiarazioni delle liste
//infatti :: è come se fosse un "add(i)" con i=int 
//mentre @ è come se fosse un "append(ls)" con ls=lista;
//Operano su tipi diversi!


//----------------------------
//------------TIPI------------
//----------------------------

//i tipi di variabili sono il tipo generico che rappresenta la variabile in questione:
//2 has type int
//[] has type ’a list
//2::[] has type int list
//true has type bool

 