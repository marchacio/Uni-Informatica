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


//-----------------------------------
//------------INT E FLOAT------------
//-----------------------------------
(*
    NOTA: type float corresponds to double (64 bit).

    int and float not compatible, no implicit conversions, esempio:
        > 3.14 * 2;;
            error: The type ’int’ does not match the type ’float’
        > 3.14 * float 2;;
            val it: float = 6.28
        > int 3.14 * 2;;
            val it: int = 6

    -> come si può notare dall'esempio precedente, si possono fare dei
        cast semplicemente scrivendo il tipo voluto di dato prima della
        variabile di tipo diverso:
            int (3.14) -> 3
*)

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

    
    * Funzione map:
    Applica una funzione f a tutti gli elementi della lista:
        List.map f [x1; x2; ...;xn]=[f x1; f x2; ... ;f xn]

    Esempi:
      >> map ((+)1) [1;2;3];;       (* remark: (+) 1 equivalent to fun x -> 1+x *)
        val it: int list = [2; 3; 4]
      >> map ((<)0) [0;1;2];;       (* remark: (<) 0 equivalent to fun x -> 0<x *)
        val it: bool list = [false; true; true]
      >> map String.length ["apple"; "orange" ];;
        val it: int list = [5; 6]

    * Funzione fold:
*)

//----------------------------
//------------TIPI------------
//----------------------------

//i tipi di variabili sono il tipo generico che rappresenta la variabile in questione:
//2 has type int
//[] has type ’a list
//2::[] has type int list
//true has type bool


//----------------------------------
//------------RICORSIONE------------
//----------------------------------

///In questo esempio si dichiara una funzione ricorsiva che calcola 
/// il fattoriale di un numero.
/// Dato che è ricorsiva, bisogna specificare "rec" subit dopo "let"
let rec fact x = 
    if x = 0 then 1 else x * fact (x-1);;

//Ricorsione in coda:
// tipo particolare e ottimizzante di ricorsione che non fa uso dello stack;
// Tutte le funzioni ricorsive vanno messe in fondo al corpo della funzione:
let rec loop acc = function
    | hd::tl -> loop (acc+hd) tl (* last operation: recursive call *)
    | _ -> acc
//(se questo codice non ti è familiare, guarda il PATTERN MATCHING piu avanti).


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
    | _::tail -> 1+length tail (* the scope of t is the expression 1+length t *)
    | [] -> 0;;


//anche nel caso seguente, t rappresenta una parte della lisa e h un suo elemento
let rec sum ls =
    match ls with
    | head::tail -> head + sum tail (* the scope of h and t is the expression h+sum t *)
    | [] -> 0;;

let swap ls = (* function defined by three cases *)
    match ls with
    | x::y::t -> y::x::t (* the scope of x, y and t is the expression y::x::t *)
    | [x] -> [x] (* the scope of x is the expression [x] *)
    | [] -> [];;


//Altri modi per definire il pattern matching:
let mynot2 = function | false -> true | _ -> false
let iszero2 = function | 0 -> true | _ -> false
let rec length2 = function 
    | _::tl -> 1+length2 tl 
    | _ -> 0


//----------------------------------------
//--------------ACCUMULATORI--------------
//----------------------------------------

//link a questa pagina: 
//https://learn.microsoft.com/en-us/dotnet/fsharp/language-reference/lists#recursion-with-lists
(*
    The following code example shows how to use pattern matching to implement
    a recursive function that performs operations on a list.

    let rec sum list =
        match list with
        | head :: tail -> head + sum tail
        | [] -> 0   

The previous code works well for small lists, but for larger lists,
it could overflow the stack. 
The following code improves on this code by using an accumulator argument,
a standard technique for working with recursive functions. 
The use of the accumulator argument makes the function tail recursive, 
which saves stack space.

let sum list =
    let rec loop list acc =
        match list with
        | head :: tail -> loop tail (acc + head)
        | [] -> acc

    loop list 0
*)

//----------------------------------------
//---------------ECCEZIONI----------------
//----------------------------------------
//LINK: https://learn.microsoft.com/en-us/dotnet/fsharp/language-reference/exception-handling/

//Dichiarazione di eccezioni e i loro tipi:
//
// la sintassi è:
// "exception" exceptionType "of" argumentType 
//
//Per esempio:
exception MyError of string
exception GenericError                     (* constant constructor *)
exception Error1 of string          (* a unary constructor *)
exception Error2 of string*int      (* a binary constructor *)
let exc=GenericError
let exc1=Error1 "error message"
let exc2=Error2 ("msg", 10)

//Generazione di eccezioni:
raise(MyError("Error message"))
//Oppure
failwith "Error message"

//Catturare le eccezioni con try ... with;
//Esempio:

// ...
try
    if x = y then raise (Error1("x"))
    else raise (Error2("x", 10))
with
    | Error1(str) -> printfn "Error1 %s" str
    | Error2(str, i) -> printfn "Error2 %s %d" str i
// ...


//--------------------------------------------
//---------------TIPI DEFINITI----------------
//--------------------------------------------

//definizione di un nuovo tipo di dato "Color", che può avere uno solo 
//tra i valori Red o Green o Blue.
//Come per il Pattern Matching, anche qui esiste la definizione "verticale":

//Esempio di type costante:
type Color = | Red | Green | Blue;; (* just constant constructors *)
type Color2 = 
    | Red 
    | Green 
    | Blue;; (* just constant constructors *)

let toString = function (* toString : color -> string *)
    | Red -> "red"
    | Green -> "green"
    | Blue -> "blue";;

let toString2 x =  (* toString : color -> string *)
    match x with
        | Red -> "red"
        | Green -> "green"
        | Blue -> "blue";;

//Esempio di type NON-costante:
type Shape =
    | Square of float
    | Circle of float
    | Rectangle of float * float

let perimeter = function
    | Square side -> 4.0 * side
    | Circle ray -> 2.0 * System.Math.PI * ray
    | Rectangle (width,height) -> 2.0 * (width + height)

perimeter (Square 5.0)
perimeter (Circle 12.3)
perimeter (Rectangle (4.2, 4))

//Esempio di type NON-costante e RICORSIVO:
type ExpAST =
    | IntLiteral of int         (* integer literals *)
    | Sign of ExpAST            (* unary minus *)
    | Add of ExpAST * ExpAST    (* binary addition *)
    | Mul of ExpAST * ExpAST    (* binary multiplication *)

let rec eval = function
    | IntLiteral n -> n
    | Sign exp -> - eval exp
    | Mul (exp1,exp2) -> eval exp1 * eval exp2
    | Add (exp1,exp2) -> eval exp1 + eval exp2;;

let exp = Sign(Add(IntLiteral 40,IntLiteral 2)) // -(40+2)