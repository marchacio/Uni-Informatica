//--------------------------------------------
//-----------VISIBILITA' DEI CAMPI------------
//--------------------------------------------

// 1) private: cami e metodi visibili solo all'interno della classe
// 2) public: campi e metodi visibili anche al di fuori della classe
// 3) public class: classe visibile in tutto il programma
//  esempio:
class Point {
    private int x,y;

    public boolean overlaps(Point p) {  // fields of ’p’ and ’this’ are visible
        return this.x == p.x && this.y == p.y;
    }
}

//Con la parola "static" si definiscono i campi di classe:
//questi campi mantengono lo stesso valore attraverso le instanze delle classi.
//Per es: 
class Point2 {
    private int x,y;
    private static int z; 

    //...
}
//se imposto z = 10, z sarà 10 per ogni istanza della classe Point2:
Point2 p1 = Point2();
p1.modificaZ(5);        //imposta z = 5

Point2 p2 = Point2();
p2.getZ()               //ritorna 5

//I campi statici possono essere inizializzati in due modi:
public class Test {
    private static int val = 5; //1° modo: inizializzarli nella loro definizione
    private static int fact = 1;

    //2° modo: inizializzarli con la parola static seguita da {...} 
    static { 
        for (int i = 1; i <= Test.val; i++)
            Test.fact *= i;
    }
}


//Con la parola FINAL si definisce una variabile read-only, ovvero non può
//essere modificata e conterrà sempre lo stesso valore dalla sua inizializzazione
//fino alla sua morte.



// In java, come nella maggior parte dei linguaggi di programmazione, gli oggetti sono referenze in memoria:
//      tutti gli oggetti inizializzati sono "puntatori" a zone di memoria dello heap (mem dinamica).
//      Gli oggetti non inizializzati sono "puntatori" a null.
//      Es:
Point t1 = new Point();     //crea e alloca un nuovo oggetto nella memoria dinamica
Point t2 = t1;              // t2 and t1 refer to the same object
Point t3 = null;            // t3 refers to no object

t1 instanceof Point;        // true
t3 instanceof Point;        // false


//-----------------------------------------
//-----------DESIGN BY CONTRACT------------
//-----------------------------------------
/*
    Lo sviluppatore può richiedere certe condizioni sul suo codice:
    condizioni pre-codice, condizioni post-codice e condizioni invarianti.
    Questo può essere utile sia per la correttezza del codice sia per una buona documentazione. 
    NOTA: Questa implementazione non è di default per il linguaggio java, ma bisogna installare
    dei tool appositi: https://www.cs.ucf.edu/~leavens/JML/index.shtml
    
    1) "requires p"
        con questo codice si indica che il parametro p è richiesto e non può non esistere.
    
    2) "ensures p"
        con questo codice si vuol dire che p deve essere non nullo subito dopo l'esecuzione 
        del metodo a cui viene applicato l'ensures
    
    3) "invariant p"
        p deve avere un valore:
            - subito dopo la creazione della classe C che lo genera
            - subito prima e subito dopo la chiamata ad ogni metodo della classe C

    es:
*/
public class TimerClass {
    private int time;
    @ invariant 0 <= time && time <= 3600;

    public int getTime() {
        @ ensures \result == this.time;
        return this.time;
    }

    public boolean isRunning() {
        @ ensures \result == this.getTime() > 0;

        return this.getTime() > 0;
    }

    public int reset(int minutes) {
        @ requires 0 <= minutes && minutes <= 60;
        @ ensures \result == \old(this.time) && this.time == minutes * 60;

        if (minutes < 0 || minutes > 60)
            throw new IllegalArgumentException();
    
        int prevTime = this.getTime();
        this.time = minutes * 60;
        return prevTime;
    }
}

//--------------------------------------------
//-----------COSTRUTTORI DI CLASSI------------
//--------------------------------------------
//
//Un altro modo per garantire la sicurezza del codice e l'information hiding
//è tramite i costruttori:
//  un costruttore è sempre chiamato quando si definisce un'instanza di una classe e 
//  serve per inizializzare correttamente gli oggetti all'interno di essa.
//
//Se non è specificato un costruttore, il compilatore ne aggiunge uno "vuoto" che
// riempie i campi con valori di default.
//
//Ecco un esempio di classe con 4 costruttori diversi che inizializzano le variabili 
//private in modo diverso tra loro (NOTA: tutti i costruttori devono differire per numero o tipo di parametri):
public class TimerClass {
    private int time = 60;

    public TimerClass() {   // ’time’ has the default value 60.
    }

    public TimerClass(int minutes) { // ’time’ has value minutes * 60
        if (minutes < 0 || minutes > 60)
            throw new IllegalArgumentException();

        this.time = minutes * 60;
    }

    public TimerClass(TimerClass other) { // copy constructor
        this.time = other.getTime();
    }

    //Costruttore di tipo statico (factory) che serve per rendere
    //piu espliciti i parametri del costruttore
    public static TimerClass timerFromTime(int time){
        return new TimerClass(time/60);
    }

    //...
}

//Se non viene specificato nessun parametro ai campi privati, questi vengono inizializzati
//automaticamente con dei valori di default:
//  0 per int, flase per boolean...
    

//---------------------------------------------
//-----------------SUB-TYPING------------------
//---------------------------------------------
//
//I sotto-tipi (sub-typing) sono delle relazioni tra classi.
//Per esempio, TimerClass è un sottotipo di Object e in java si definisce cosi:
// TimerClass <= Object         (minore uguale)
// ma Object ≤\ TimerClass      (non minore uguale)


//---------------------------------------------
//-----------------INTERFACCE------------------
//---------------------------------------------
//
//Le interfacce definiscono i metodi pubblici di una classe 
//ma non contengono il codice implementativo:

public interface Timer { // Timer is a type but not a class
    
    // all these methods are abstract and public
    boolean isRunning();

    int getTime();
    
    void tick();

    int reset(int minutes);
}

public class TimerClass implements Timer { // TimerClass ≤ Timer
    private int time = 60;
    public int getTime() {
        return this.time;
    }

    //ALL METHODS of Timer must be defined in the class
    //...

    public TimerClass(Timer other) {
        this.time = other.getTime();
    }
}

//NOTA1: una classe può implementare piu interfacce.
//NOTA2: le interfacce non sono oggetti, sono dei tipi ma non 
//       possono essere inizializzate.


//-----------------------------------------------------------
//-----------------EREDITARIETA' TRA CLASSI------------------
//-----------------------------------------------------------
//
//Data una classe C, essa può essere "estesa" (aggiungendo
//metodi e dati) con la parola "extends".
//L'esempio seguente è fatto con le interfacce:
public interface Timer {
    boolean isRunning();
    int getTime();
    void tick();
    int reset(int minutes);
}

public interface StoppableTimer extends Timer {
    boolean stopped();
    void stop();
    void restart();
}

//In questo esempio StoppableTimer ha dei metodi in più di Timer.
//L'ereditarietà può avvenire anche tra classi, non per forza interfacce 
//con una piccola differenza:
//l'eredità tra classi è SINGOLA (una classe può essere l'estensione di 
//solo un'altra classe) mentre l'ereditarietà tra interfacce è MULTIPLA.

//I costruttori non sono ereditati tra sottoclassi:
//questo vuol dire che tutte le sottoclassi hanno bisogno di un costruttore loro.


//--------------PROTECTED--------------
//Con l'ereditarietà bisogna introdurre un nuovo modificatore d'accesso:
protected int time = 60;
//grazie a "protected", il campo "time" è come se fosse private ma accessibile
//dalle sottoclassi, ovvero tutte le classi che estendono la classe contenente time.

//--------------OVERRIDE--------------
//Con l'ereditarietà bisogna anche aggiungere il concetto di override:
@Override
public boolean isRunning() {...}
//con la parola "Override" si sovrascrive il metodo isRunning definito dalla 
//classe superiore rispetto alla classe che esegue l'override (ovvero la classe figlia).

//--------------SUPER--------------
//"super.method()" è una chiamata diretta al metodo "method()" della classe madre.
//Ovviamente fa riferimento all'istanza dell'oggetto "this".
//Si chiama super perche in gergo la classe madre è chiamata SUPERCLASSE.
public class StoppableTimerClass extends TimerClass {
    ...
    @Override
    public boolean isRunning() {
        // calls ’isRunning’ of ’TimerClass’ on target object ’this’
        return super.isRunning() && !this.stopped();
    }
    ...
}

//--------------TIPI GENERICI--------------
//Se una classe deve poter accettare qualsiasi tipo di oggetto all'interno
//delle sue variabili, queste sono da definire come TIPI GENERICI.
//Per definire una classe che accetta tipi generici, bisogna aggiungere 
//  <T1 ...>
//subito dopo il nome della classe nella sua definizione:
public class Pair<T1,T2> { // T1, T2 generic type parameters 
    private final T1 fst;
    private final T2 snd;

    public Pair(T1 fst, T2 snd) { this.fst = fst; this.snd = snd; }

    public T1 getFst() { return fst; }
    public T2 getSnd() { return snd; }
}
...
Pair<String, Color> p = new Pair<String,Color>("a string", Color.RED);
//Meglio utilizzare i tipi generici rispetto alla classe Object in quanto
//questa è la superclasse di tutte le classi, quindi può essere soggetta 
//a casting tra classi diverse che potrebbero creare eccezioni.
//Utilizzando T1, T2 (ma si può usare anche A, B, K, E...) si impone che 
//il tipo di quella variabile sia uno solo e non generico.


//--------------OVERLOAD--------------
//L'overload di un metodo è la definizione multipla dello stesso metodo
//ma con argomenti diversi:
public class Overload {
    public String m(int i) { return "int"; }
    public String m(float f) { return "float"; }
    public String m(Number n) { return "Number"; }
    public String m(Number... nums) { return "Number..."; }
    public String m(Object obj) { return "OBJ"; }
}
//come si può notare, il metodo "m" ha sempre lo stesso nome e accetta diversi
//argomenti con i quali fa operazioni diverse.
//in generale, l'overloading dei metodi è una pratica da evitare.


//-------------------------------------------------------
//--------------------CLASSI ASTRATTE--------------------
//-------------------------------------------------------
//Partendo da un esempio:
/*
Abbiamo due classi A e B che implementano l'interfaccia I.
Vogliamo aggiungere una funzione funz() uguale per entrambe le classi.
Teoricamente bisognerebbe riscrivere funz() due volte, una per A e una per B.

Per evitare questa ripetizione e migliorare la scalabilità del codice,
esistono le CLASSI ASTRATTE:

sono una via di mezzo tra interfacce e classi, infatti esse implementano un'interfaccia
lasciando inalterati i metodi e senza implementazione, ma danno la possibilità
di aggiungere altri metodi (non specificati nell'interfaccia implementata) con
la loro implementazione.
Inoltre si possono creare metodi non implementati, come nelle interfacce.

Si definiscono aggiungendo la parola "abstract" prima di "class".

ALTRO: 
Anche le classi astratte hanno bisogno del loro costruttore.
Come per le interfacce, le classi astratte non possono essere utilizzate
per creare oggetti.
ES:*/
public abstract class AbstractTimer implements Timer {

    protected AbstractTimer(){} // for subclasses use

    protected static int checkMinutes(int minutes) { // for subclasses use
        if (minutes < 0 || minutes > 60) throw new IllegalArgumentException();
        return minutes;
    }

    public boolean isRunning() {
        return this.getTime() > 0;
    }

    // the other methods of Timer are not implemented
    abstract public int getTime(); // optional declaration
    abstract public void tick(); // optional declaration
    abstract public int reset(int minutes); // optional declaration
}

//Come si nota nell'esempio, i metodi getTime, tick e reset non sono implementati
//perche sono parte dell'interfaccia.
//Allo stesso tempo, la classe astratta aggiunge due metodi (checkMinutes e 
//isRunning), implementandoli; questi due metodi potranno essere utilizzati
//dalle sottoclassi che estendono AbstractTimer.


//---------------------------------------------
//--------------------ARRAY--------------------
//---------------------------------------------
//
//Gli array in java si definiscono cosi:
int[] array;        //array è una reference a un array di interi
array = new int[10] //array è stato inizializzato dinamicamente ed è utilizzabile.
                    //quando si inizializza, bisogna specificare la dimensione

//Per gli array multidimensionali si applica la sintassi come in c++:
int[][] matrice = new int[3][] //solo l'ultima size è opzionale


//L'ultimo elemento di un costruttore o di una funzione può avere 
//arità variabile:
public static int max(int first, int... others) {

    // in the body ’others’ is considered an array of type ’int[]’
    int res = first;
    for (int e : others)
        if (e > res)
            res = e;

    return res;
}
//A questo punto max() può essere chiamato con un primo elemento di tipo
//int, e il secondo di tipo int o list<int>


//---------------------------------------------
//--------------------MAIN---------------------
//---------------------------------------------
//
//In java, l'esecuzione di un programma deve iniziare dal main di una classe
//e questo main deve avere la seguente forma: 
public static void main(String[] args) {...}

//Lo standard output è definito come System.out, con i metodi print, println...


//-----------------------------------------
//----------------PACKAGES-----------------
//-----------------------------------------
//
//Con la parola "package nome_pack" ad inizio file, si definisce che quel file
//faccia parte del pacchetto nome_pack (che solitamente ha il nome del folder contenente
//tale file).
//ES:
/*
Project (root):
  SubFolder SF1:
    file c1.java:
        package p1;
        import ...;

        public class C1 {...}
        class D1 {...}
    
    file c2.java:
        package p1;
        import ...;

        public class C2 {...}
        class D2 {...}

  SubFolder SF2:
    file c1.java:
        package p2;
        import ...;

        public class C1 {...}
        class D1 {...}
*/
//I packages contengono classi (solo le pubbliche potranno essere usate al di 
//fuori del pacchetto) e sotto-pacchetti.
//Le classi private potranno essere usate solamente all'interno del pacchetto.
//
//In sostanza, i pacchetti rispecchiano la struttura del progetto:
//package = folder containing:
//  subpackages (=subfolders)
//  compilation units (=files) declaring classes and interfaces
//Inoltre, i nomi dei pacchetti rispecchiano il path della loro cartella:
//  javax.swing.tree corrisponde a javax/swing/tree
//
//Per importare tutti i sottofile di una cartella, utilizza l'asterisco:
import java.System.*

//-------------COMPILAZIONE PACKAGES-------------
//per compilare tutti i file inclusi in un pack, da terminale vai nella 
//cartella esterna ad esso ed esegui:

//  javac /project/path/to/files/*.java

//Poi per eseguire il file:

//  java -ea project.path.to.file.NOMEFILE_SENZA_ESTENSIONE

