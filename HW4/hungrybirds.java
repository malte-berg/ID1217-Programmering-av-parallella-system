public class Monitor_Dish {
    //private int[] buffer;
    private int n, count = 0, front = 0, rear = 0;

    public Monitor_Dish(int n) {
        this.n = n;
        //buffer = new int[n];
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
