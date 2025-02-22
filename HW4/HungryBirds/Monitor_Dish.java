public class Monitor_Dish {
    //Monitor_Dish is a monitor of type shared cell (lecture 12)
    private int dish_size, worm_count = 0;

    public Monitor_Dish(int dish_size) {
        this.dish_size = dish_size;
    }

    public synchronized void add_worm() {
        while (worm_count == dish_size) {
            try {
                wait();
            } catch (InterruptedException e) { }
        }
        worm_count = dish_size;
        notifyAll();
    }

    public synchronized void eat_worm() {
        while (worm_count == 0) {
            try {
                wait();
            } catch (InterruptedException e) { }
        }
        worm_count--;
        notifyAll();
    }

}
