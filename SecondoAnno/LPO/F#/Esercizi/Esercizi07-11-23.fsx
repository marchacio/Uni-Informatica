(*
    Dato il tipo polimorfo degli alberi binari di ricerca

    type 'a btree =
        | Empty
        | Node of 'a * 'a btree * 'a btree

    definire la funzione getMin: 'a btree -> 'a option che restituisce l'elemento minimo, se esiste, 
    di un albero binario di ricerca, None altrimenti.

    Esempi:
    > Node (3, Node (1, Empty, Node (2, Empty, Empty)), Node (6, Node (4, Empty, Empty), Empty)) |> getMin;;
    val it: int option = Some 1

    > getMin Empty |> Option.isNone;;
    val it: bool = true
*)

type 'a btree =
    | Empty
    | Node of 'a * 'a btree * 'a btree

let rec getMin (tree: 'a btree) : 'a option =
    match tree with
    | Empty -> None
    | Node (x, Empty, _) -> Some x
    | Node (_, l, _) -> getMin l  