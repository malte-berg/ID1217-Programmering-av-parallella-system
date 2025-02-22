public class Baby_Bird extends Thread {
    //Consumer
    private Monitor_Dish dish;
    private int id;

    public final long SLEEPDURATION = 200;

    public Baby_Bird (Monitor_Dish dish, int id) {
        this.dish = dish;
        this.id = id;
    }

    public void run() {
        try {
            while (true) {
                dish.eat_worm();
                System.out.println("Baby bird " + id + " ate a worm.");
                Thread.sleep(SLEEPDURATION);
            }
        } catch (InterruptedException e) {}
    }
}
