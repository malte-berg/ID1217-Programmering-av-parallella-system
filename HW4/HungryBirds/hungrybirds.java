public class hungrybirds {
    static int[] worm_tracker;
    static int no_of_bbirds;
    static final int DISHSIZE = 10;

    public static void main(String[] args) {
        // Set no of baby birds (consumers) to args or 4 if no args.
        if (args.length > 0) no_of_bbirds = Integer.parseInt(args[0]);
        else no_of_bbirds = 4;
        Monitor_Dish dish = new Monitor_Dish(DISHSIZE);

        Mommy_Bird mommy = new Mommy_Bird(dish);
        Baby_Bird[] bbird_array = new Baby_Bird[no_of_bbirds];

        mommy.start();
        for (int i = 0; i < no_of_bbirds; i++) {
            bbird_array[i] = new Baby_Bird(dish, i);
            bbird_array[i].start();
        }
    }
}
