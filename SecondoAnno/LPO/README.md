# LPO: Linguaggi e Programmazione orientata agli Oggetti

In questa cartella troverai tutto ciò che riguarda LPO.
Sia in F# sia in Java ho creato un file "basi" che contiene le basi del linguaggio, e una cartella "esercizi" che contiene gli esercizi svolti.

# F#

Ti lascio una guida copiata del README del primo labo LPO su F#, che ti spiega come compilare ed eseguire codice:

Per il testing del codice è consigliabile compilare il codice creando un progetto Ionide con Visual Studio Code, come spiegato
nella [pagina di supporto su F#](https://2023.aulaweb.unige.it/mod/page/view.php?id=68151) e poi
lanciarlo da terminale con il comando <code>dotnet run</code>.

Un modo conveniente per verificare che l'output delle funzioni sia quello corretto è tramite il costrutto <code>assert bool-expr</code>
che valuta l'espressione booleana <code>bool-expr</code> e termina il programma con un messaggio di errore se il valore calcolato è false; se invece il valore è true, allora l'esecuzione prosegue normalmente.

Esempio:
```fsharp
assert (prod [2;4;3]=24) (* se l'output non è corretto, allora l'asserzione fallisce *) 
```
Per stampare sullo standard output il valore di un'espressione è possibile usare la funzione <code>printfn</code>
con il formato generico "%A".

Esempio:
```fsharp
insert 0 [2;4;3] |> printfn "%A"
```
stampa
```fsharp
[2;4;3;0] 
```

# JAVA

Ti lascio una guida copiata dal README del primo labo LPO su JAVA, che ti spiega come compilare ed eseguire codice:

## Come compilare ed eseguire codice Java
Un programma Java è costituito da uno o più file sorgenti riconoscibili dall'estensione `.java`; per poter eseguire il programma, i file sorgente devono essere prima compilati in file binari, riconoscibili dall'estensione `.class`,
    che contengono codice intermedio chiamato bytecode. Per semplicità, al momento considereremo programmi dove tutti i file sorgenti sono contenuti nella stessa cartella.

### Esempio
Provare a definire nel file `PrintArguments.java` la seguente classe pubblica con il metodo `main`:

```java
public class PrintArguments {
    public static void main(String[] args) {
        for (String s : args)
            System.out.println(s); // prints with blank
        assert args instanceof Object;
    }
}
```
Ogni classe pubblica dev'essere contenuta in un file con lo stesso nome (nell'esempio sopra il file deve chiamarsi `PrintArguments.java`). Se il programma è composto da più classi pubbliche, sarà necessariamente costituito da più file sorgenti.

### Compilazione
Per compilare un file sorgente è possibile lanciare da shell il comando `javac`, passando come argomento il nome del file. Per semplicità è consigliabile lanciare il comando dalla stessa cartella del file da compilare:

```bash
$ javac PrintArguments.java
```

Se la compilazione avrà successo, allora per ogni file sorgente verrà generato nella stessa cartella un corrispondente file `.class`, contenente il programma in bytecode.

### Esecuzione
Il bytecode Java non è direttamente eseguibile, ma deve essere interpretato mediante il comando `java` che si aspetta come argomento il nome della classe (quindi, senza l'estensione `.class`!) da cui si vuole iniziare l'esecuzione del
programma tramite la chiamata del suo metodo `main`:

```bash
$ java PrintArguments
```
Il comando `java` fallisce se non viene lanciato dalla stessa cartella in cui si trova il file `.class` della classe; per le prime esperienze di laboratorio è consigliabile lanciare `java` dalla stessa cartella. È comunque possibile specificare un *classpath* con l'opzione `-cp`, ovvero, una lista di cartelle in cui l'interprete cerca i file `.class` da caricare:
    
```bash
$ java -cp cartella/PrintArguments
```

Dato che il metodo `main` della classe `PrintArguments` contiene un'asserzione, per essere eseguita deve essere
abilitata con l'opzione `-ea` (abbreviazione di "enable assertions"):

```bash
$ java -ea PrintArguments
```

Se si modifica l'asserzione con `!(args instanceof Object)`, si ricompila la classe e si esegue il programma con l'opzione `-ea`, viene sollevata un'eccezione di tipo `AssertionError`.

### Programmi composti da più file
Se il programma è composto da più file sorgenti nella stessa cartella, conviene compilarli tutti insieme:

```bash
$ javac *.java
```

<!-- Per eseguire il programma, lanciare il comando `java` passando come argomento il nome delle classi da cui si vuole che inizi l'esecuzione (la classe deve necessariamente definire il metodo `main`).-->