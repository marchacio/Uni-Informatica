package Esercizi;

/*
Modificare il metodo tick() della classe TimerClass in modo che restituisca come risultato 
l'oggetto stesso su cui è stato chiamato, oltre a modificare il suo campo come nella versione iniziale.
In questo modo è possibile chiamare il metodo consecutivamente su uno stesso oggetto come in questo esempio:

TimerClass t1 = new TimerClass();
t1.reset(1);
t1.tick().tick(); // calls twice tick() on t1


Completare la classe AnotherTimerClass in modo che i suoi metodi di istanza implementino 
la stessa interfaccia specificata per la classe TimerClass.
*/

class TimerClass {
    // private field of the object = hidden internal state
    private int time; // in seconds, invariant: 0 <= time <= 3600

    // public instance methods = interface of visible operations
    public boolean isRunning() {   // 'this' is the target of the method
        return this.getTime() > 0;
    }
    public int getTime() {         // 'this' is the target of the method
        return this.time;
    }
    public TimerClass tick() {           // 'this' is the target of the method
        if (this.isRunning())
            this.time--;

        return this;
    }
    public int reset(int minutes) { // 'this' is the target of the method
        if (minutes < 0 || minutes > 60) // Java exceptions are special objects
            throw new IllegalArgumentException();
        int prevTime = this.getTime();
        this.time = minutes * 60;
        return prevTime;
    }

    public static void main(String[] args) {
        // creates an object of class TimerClass, assigns its reference to t1
        TimerClass t1 = new TimerClass();
        // calls reset(1) on the object referenced by t1
        t1.reset(1);
        // creates an object of class TimerClass, assigns its reference to t2
        TimerClass t2 = new TimerClass();
        // calls reset(2) on the object referenced by t2
        t2.reset(2);
    }
}


class AnotherTimerClass {

	private int seconds;    // invariant: 0<=seconds<=59
	private int minutes;    // invariant: 0<=minutes<=60 && (minutes<60 || seconds==0)

	public boolean isRunning() { 
        return this.getTime() > 0;
	}

	public int getTime() {
		//total time (in seconds) is seconds+60*minutes
        return seconds + minutes*60;
	}

	public void tick() {
        if (this.isRunning()){
            if(this.seconds == 0)
                this.minutes--;
            else 
                this.seconds--;
        }
	}

	public int reset(int minutes) {
		if (minutes < 0 || minutes > 60)
            throw new IllegalArgumentException();

        int prevTime = this.getTime();
        this.minutes = minutes * 60;
        return prevTime;
	}

	public static void main(String[] args) {
        AnotherTimerClass t1 = new AnotherTimerClass(); 
        t1.reset(1);            // t1 reset to 1 minute

        int seconds = 0;
        while (t1.isRunning()) {
            t1.tick();           // one second per tick
            seconds++;
        }
        assert seconds == 60;   // expected to hold
        assert !t1.isRunning(); // expected to hold
	}
}