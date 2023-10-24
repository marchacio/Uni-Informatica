(*
    ES 1;

    Definire la funzione scalar : int -> int * int -> int * int che presi n e (x,y) restituisce (n*x,n*y).
    Esempio:
    # scalar 3 (2,3);;
    - : int * int = (6, 9)
*)
let scalar n (x,y) = (n*x, n*y);;


(*
    ES 2;

    Definire la funzione add_vect : int * int -> int * int -> int * int che presi (x1,y1) e (x2,y2) restituisce (x1+x2,y1+y2).
    Esempio:
    # add_vect (1,2) (3,4);;
    - : int * int = (4, 6)
*)
let add_vect (x1,y1) (x2,y2) = (x1+x2, y1+y2);;


(*
    ES 3;

    Definire la funzione scalar_prod : int * int -> int * int -> int che presi (x1,y1) e (x2,y2) restituisce x1*x2+y1*y2.
    Esempio:
    # scalar_prod (1,2) (3,4);;
    - : int = 11
    
*)
let scalar_prod (x1,y1) (x2,y2) = x1*x2 + y1*y2;;