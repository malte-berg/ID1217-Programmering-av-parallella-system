public class Baby_Bird extends Thread {
    //Consumer
    private Monitor_Dish dish;
    private int id;
    private int[] worm_tracker;

    public final long SLEEPDURATION = 0;

    public Baby_Bird (Monitor_Dish dish, int id, int[] worm_tracker) {
        this.dish = dish;
        this.id = id;
        this.worm_tracker = worm_tracker;
    }

    public void run() {
        try {
            while (true) {
                dish.eat_worm();
                worm_tracker[id]++;
                System.out.println("Baby bird " + id + " ate a worm.");
                Thread.sleep(SLEEPDURATION);
            }
        } catch (InterruptedException e) {}
    }
}
