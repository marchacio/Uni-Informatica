(*
    Definire la funzione interval : int -> int -> int list tale che interval a b restituisce 
    la lista ordinata corrispondente all'intervallo dei numeri interi compresi tra a e b, 
    estremi inclusi.

    Esempi:
    > interval (-1) 3;; 
    val it: int list = [-1; 0; 1; 2; 3]

    > interval 5 3;;
    val it: int list = []
*)

///Prima versione easy
let interval (a:int) (b:int) = 
    if b<a 
        then
            []
        else
            [a..b]


///Seconda versione (ricorsiva)
let interval2 (a:int) (b:int) =
    
    let rec intervalRec (x:int) (lista:list<int>) =
        if x = a 
            then 
                let nuovalista = x::lista
                nuovalista 
            else 
                let nuovalista = x::lista
                intervalRec (x-1) nuovalista

    if b<a 
        then
            []
        else
            let listaFinale = (intervalRec (b-1) [b])
            listaFinale 



(*
    Provare a definire per casi le seguenti funzioni su liste, mostrando i pattern 
    che individuano i vari casi e le espressioni che corrispondono al valore che 
    deve essere restituito.

    La funzione length: 'a list -> int che calcola la lunghezza di una lista.
    La funzione sum: int list -> int che calcola la somma di tutti gli elementi di una lista.
    La funzione swap: 'a list -> 'a list che restituisce la lista dove i primi due 
    elementi sono stati scambiati se la sua lunghezza è maggiore di 1, la lista inalterata altrimenti.

    Esempi:
    > swap [1;2;3]=[2;1;3];;
    val it: bool = true

    > swap [1]=[1];;        
    val it: bool = true

    > swap []=[];;  
    val it: bool = true
*)

(* functions defined by two cases *)
let rec length ls =
    match ls with
    | _::t -> 1+length t (* the scope of t is the expression 1+length t *)
    | [] -> 0;;
    
let rec sum ls =
    match ls with
    | h::t -> h+sum t (* the scope of h and t is the expression h+sum t *)
    | [] -> 0;;

let swap ls = (* function defined by three cases *)
    match ls with
    | x::y::t -> y::x::t (* the scope of x, y and t is the expression y::x::t *)
    | [x] -> [x] (* the scope of x is the expression [x] *)
    | [] -> [];;
