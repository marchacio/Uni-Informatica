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

//Con la parola "static" si definiscono i campi di classe: campi a cui si può accedere 
// anche quando la classe non è stata ancora inizializzata.
class Point2 {
    private int x,y;
    private static int z = 5; 

    //...
}
//...
Point2.z;       //5


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
//Ecco un esempio di classe con 3 costruttori diversi che inizializzano le variabili 
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

    //...
}

//Se non viene specificato nessun parametro ai campi privati, questi vengono inizializzati
//automaticamente con dei valori di default:
//  0 per int, flase per boolean...
    