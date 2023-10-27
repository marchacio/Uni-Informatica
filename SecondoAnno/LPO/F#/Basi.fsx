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

(*
    Funzioni per le liste:
        - List.length : ’a list -> int
            returns the length (number of elements) of the given list
        - List.item : int -> ’a list -> ’a
            returns the n-th element of the given list. The head of the list is at position 0
        - List.init : int -> (int -> ’a)-> ’a list
            List.init len f is [f 0; f 1; ...; f (len-1)]

    Esempi:
    
    > let ls = List.init 10000 (fun x->x+1);;
        val ls : int list = [1; 2; 3; ... ]
    > List.length ls;;
        val it: int = 10000
    > List.item 0 ls;;
        val it: int = 1
    > List.item 9999 ls;;
        val it: int = 10000
*)

//----------------------------
//------------TIPI------------
//----------------------------

//i tipi di variabili sono il tipo generico che rappresenta la variabile in questione:
//2 has type int
//[] has type ’a list
//2::[] has type int list
//true has type bool

 
//----------------------------------------
//------------PATTERN MATCHING------------
//----------------------------------------
//è sostanzialmente uno switch negli altri linguaggi di programmazione:
///Questa funzione [myNot] prende b e se b "matcha" con false, ritorna true (1);
/// Prende b e se b "matcha" con true, ritorna false (2)
let myNot b = 
    match b with 
    | false -> true         //(1)
    | true -> false         //(2)

//Altri esempi un po piu complessi:

(* functions defined by two cases;

In questo caso c'è la definizione di una variable t che rappresenta
la "parte destra" della lista.
L'identificatore "_" indica un elemento generico.
*)
let rec length ls =
    match ls with
    | _::t -> 1+length t (* the scope of t is the expression 1+length t *)
    | [] -> 0;;


//anche nel caso seguente, t rappresenta una parte della lisa e h un suo elemento
let rec sum ls =
    match ls with
    | h::t -> h+sum t (* the scope of h and t is the expression h+sum t *)
    | [] -> 0;;

let swap ls = (* function defined by three cases *)
    match ls with
    | x::y::t -> y::x::t (* the scope of x, y and t is the expression y::x::t *)
    | [x] -> [x] (* the scope of x is the expression [x] *)
    | [] -> [];;


//Altri modi per definire il pattern matching:
let mynot2 = function | false -> true | _ -> false
let iszero2 = function | 0 -> true | _ -> false
let rec length2 = function | _::tl -> 1+length2 tl | _ -> 0



//--------------------------------
//------------STRINGHE------------
//--------------------------------
(*
    Riassunto:
        - primitive type string supported as sequences of values of type char
        - standard literals (the only constructors):
            "" is the empty string, "hello world" is a non-empty string
        - concatenation ˆ or +: left-associative, lower precedence than application
        - interpolated strings $"...{expression}...{expression}..."
*)
let s = "hello" + " " + "world";;
//val s: string = "hello world"

//let s2 = "hello" ˆ " " ˆ "world";;
//val s2: string = "hello world"

let s3 = $"int value {2*3} bool value {true&&false}";;
//val s3: string = "int value 6 bool value False"
