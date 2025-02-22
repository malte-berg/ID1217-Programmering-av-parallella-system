public class Monitor_Dish {
    //Monitor_Dish is a monitor of type shared cell (lecture 12)
    private int dish_size, worm_count = 0;
    private boolean chirped_empty;

    public Monitor_Dish(int dish_size) {
        this.dish_size = dish_size;
        this.worm_count = dish_size;
        this.chirped_empty = false;
    }

    // For mommy bird (producer)
    public synchronized void add_worm() {
        while (!chirped_empty) {
            try {
                wait();
            } catch (InterruptedException e) { }
        }
        worm_count = dish_size;
        notifyAll();
    }

    // For baby birds (consumers)
    public synchronized void eat_worm() {
        while (worm_count == 0) {
            // If the bird is the first to discover the empty dish, chirp.
            if (!chirped_empty) {
                chirped_empty = true;
                notifyAll();
            }
            try {
                wait();
            } catch (InterruptedException e) { }
        }
        worm_count--;
    }

}
