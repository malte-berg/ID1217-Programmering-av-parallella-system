public class Monitor_Dish {
    //Monitor_Dish is a monitor of type Bounded Buffer (lecture 11)
    private int n, count = 0, front = 0, rear = 0;

    public Monitor_Dish(int n) {
        this.n = n;
    }
    
    public synchronized void add_worm() {
        while (count == n)
            try {wait();}
            catch (InterruptedException e) { }
        count++;
        notifyAll();
    }

    public synchronized void eat_worm() {
        while (count == 0)
            try { wait(); }
            catch (InterruptedException e) { }
        count--;
        notifyAll();
    }

}
