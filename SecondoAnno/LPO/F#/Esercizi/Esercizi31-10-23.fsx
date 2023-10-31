(*
    ES 1:

    Definire mediante ricorsione di coda e parametro di accumulazione la funzione 
        filter : ('a -> bool) -> 'a list -> 'a list 
    tale che filter p l restituisce, rispettando l'ordine iniziale, la lista degli elementi 
    e di l tali che p e = true.

    Esempio:

    filter ((<)0) [-1;1;-2;2;0] = [1;2] (* tiene solo gli elementi positivi *)
    filter (fun x -> x % 2=0) [-1;1;-2;2;0] = [-2; 2; 0] (* tiene solo gli elementi pari *)    
*)
let rec filter p l = 
    //crea una funzione ausiliaria
    let rec aux p lista acc =
        match lista with
        | [] -> acc
        | head::tail -> 
            if p head then aux p tail (head::acc)
            else aux p tail acc
    aux p l []

filter ((<)0) [-1;1;-2;2;0]

(*
    Definire filter usando List.fold
*)
let filter2 p l = 
    List.fold (fun acc x -> if p x then x::acc else acc) [] l

filter2 ((<)0) [-1;1;-2;2;0]