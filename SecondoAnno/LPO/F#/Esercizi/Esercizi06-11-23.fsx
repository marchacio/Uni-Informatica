(*
    Definire il tipo QuadTree degli alberi con i seguenti tipi di nodi:
        nodi Gray: hanno sempre quattro figli
        nodi foglia: posso essere di tipo Black o White
    
    Definire la funzione invert : QuadTree -> QuadTree tale che invert t restituisce l'albero ottenuto da t
        invertendo il colore di tutti i nodi foglia e lasciando invariati quelli di tipo Gray.
    Esempio:
    Gray(Gray(Black, White, Black, White), Black, White, Black) |> invert;;
    val it: QuadTree = Gray (Gray (White, Black, White, Black), White, Black, White)
*)
type QuadTree =
    | Gray of QuadTree*QuadTree*QuadTree*QuadTree // "of ..." si mette solo quando il tipo ha degli argomenti
    | Black //se il tipo non ha argomenti, non mettere "of ..."
    | White

//Con la keyword function, specifico che è una funzione definita per pattern matching
let rec invert = function
    | Gray(t1, t2, t3, t4) 
        -> Gray(invert t1, invert t2, invert t3, invert t4)
    | Black -> White
    | White -> Black  
    

(*
    Dato il tipo dell'albero della sintassi astratta per semplici espressioni aritmetiche
    type ExpAST =
        | IntLiteral of int
        | Sign of ExpAST
        | Add of ExpAST * ExpAST
        | Mul of ExpAST * ExpAST
    definire la funzione prefixNotation: ExpAST -> string che dato un albero della sintassi astratta, 
        restituisce la stringa corrispondente all'espressione in forma polacca prefissa. 
        Suggerimento: usare le stringhe interpolate $"..."
    Esempio:
    Sign(Add(IntLiteral 1, Mul(IntLiteral 2, IntLiteral 3))) |> prefixNotation;;
    val it: string = "- + 1 * 2 3"
*)
type ExpAST =
    | IntLiteral of int
    | Sign of ExpAST
    | Add of ExpAST * ExpAST
    | Mul of ExpAST * ExpAST

let rec prefixNotation = function
    | Sign x -> $"- {prefixNotation(x)}"
    | Add (x, y) -> $"+ {prefixNotation(x)} {prefixNotation(y)}"
    | Mul (x, y) -> $"* {prefixNotation(x)} {prefixNotation(y)}"
    | IntLiteral x -> string(x)
