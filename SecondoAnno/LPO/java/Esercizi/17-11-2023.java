package Esercizi;

class AnotherTimerClass {
    // total time (in seconds) is seconds+60*minutes
    private int seconds;//@ invariant: 0<=seconds<=59;
    private int minutes;//@ invariant: 0<=minutes<=60 && (minutes<60 || seconds==0);

    public AnotherTimerClass() { // keeps the default values
       this.seconds = 0;
       this.minutes = 0;
    }

    //@ requires minutes>=0 && minutes<=60;
    public AnotherTimerClass(int minutes) { // timer starts with total time 60*minutes
        if(minutes < 0 || minutes > 60)
            throw new IllegalArgumentException();

       this.minutes = minutes;
       this.seconds = 0;
    }

    public AnotherTimerClass(AnotherTimerClass other) { // copy constructor
       
        //evito di fare controlli in quanto l'istanza other sarà gia safety
        //in quanto è AnotherTimerClass
        this.minutes = other.minutes;
        this.seconds = other.seconds;
    }


    public boolean isRunning() {
        return this.getTime() > 0;
    }

    public int getTime() {
        return this.seconds + 60 * this.minutes;
    }

    public void tick() {
        if (this.seconds > 0)
            this.seconds--;
        else if (this.minutes > 0) {
            this.minutes--;
            this.seconds = 59;
        }
    }

    public int reset(int minutes) {
        if (minutes < 0 || minutes > 60)
            throw new IllegalArgumentException();
        int prevTime = this.getTime();
        this.minutes = minutes;
        this.seconds = 0;
        return prevTime;
    }

    public static void main(String[] args) {
        AnotherTimerClass t1 = new AnotherTimerClass();
        AnotherTimerClass t2 = new AnotherTimerClass(42);
        AnotherTimerClass t3 = new AnotherTimerClass(t2);
        assert t1.getTime()==0 && t2.getTime()==42*60 &&
                t2.getTime()==t3.getTime();

    }
}