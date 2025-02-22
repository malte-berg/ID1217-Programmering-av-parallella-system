public class Mommy_Bird extends Thread {
    //Producer
    private Monitor_Dish dish;

    public Mommy_Bird (Monitor_Dish dish) {
        this.dish = dish;
    }

    public void run() {
        while (true) {
            dish.add_worms();
            System.out.println("Mommy refilled! <3");
        }
    }
}
