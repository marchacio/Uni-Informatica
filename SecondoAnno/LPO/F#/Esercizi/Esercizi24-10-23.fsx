(*
------------------------------------------------------------------------
Per eseguire i file, installa dotnet sul pc poi, nella cartella contenente 
i file .fsx (F Sharp eXecutive) chiama il comando:

'dotnet fsi NOME_FILE.fsx'

------------------------------------------------------------------------
*)

(*
    ES 1:
    Definire la funzione generica genSum : (int -> int) -> int -> int tale che genSum f n calcola f 0 + f 1 + ... + f n.

    Una funzione è una specializzazione di genSum se ottenuta chiamando genSum e passando un'opportuna funzione come primo argomento.

    Definire come specializzazioni di genSum le funzioni sumSquare e sumCube che calcolano la somma dei quadrati e cubi dei numeri naturali da 0 a n inclusi.

    > sumSquare 3;;
    val it: int = 14

    > sumCube 3;;  
    val it: int = 36
*)

///genSum è una funzione ricorsiva che accetta in input una funzione f e un intero n;
/// esegue ricorsivamente f 0 + f 1 + ... + f n
let rec genSum (f: int -> int) (n:int) =
    if n=0 then f 0 else f n + genSum f (n-1)

//Ritorna il quadrato di x
let square x = x*x

///Ritorna la somma di quadrati di n
let sumSquare n = genSum square n



//Ritorna il cubo di x
let cube x = x*x*x

///Ritorna la somma di cubi di n
let sumCube n = genSum cube n


//funzioni di stampa:
printfn "sumSquare 3 = %d" (sumSquare 3)
printfn "sumCube 3 = %d" (sumCube 3)


//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------

(*
    ES 2:
    Definire la funzione generica genProd : (int -> int) -> int -> int tale che genProd f n calcola f 0 * f 1 * ... * f n.

    Definire come specializzazioni di genProd le funzioni fact e twoRaisedTo che calcolano il fattoriale di n e 2 elevato alla n.

    > fact 5;;
    val it: int = 120

    > twoRaisedTo 10;;
    val it: int = 1024
*)

let rec genProd (f: int->int) n: int =
    if n = 0 then f 0 else f (n) * (genProd f (n-1))

///Per definire il fattoriale in funzione di genProd, bisogna creare una funzione 
/// ausiliaria locale chiamata "identica" che ritorna x solo se è != 0.
/// In tal caso, ritorna 1 come da regola matematica del fattoriale 
let fact x: int = 

    //Creo una funzione aux locale
    let identica x = 
        if x = 0 then 1 else x
    
    genProd identica x


///Stesso ragionamento per l'elevamento a potenza:
let twoRaisedTo x:int = 

    //Creo una funzione aux locale
    let elevamento n:int =
        if n = 0 then 1 else 2
    
    genProd elevamento x 


//funzioni di stampa:
printfn "fact 5 = %d" (fact 5)
printfn "twoRaisedTo 10 = %d" (twoRaisedTo 10)