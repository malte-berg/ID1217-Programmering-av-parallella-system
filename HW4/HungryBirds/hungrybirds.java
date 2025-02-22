public class hungrybirds {
    static int[] worm_tracker;
    static int no_of_bbirds;

    public static void main(String[] args) {
        // Set no of baby birds (consumers) to args or 4 if no args.
        if (args.length > 0) no_of_bbirds = Integer.parseInt(args[0]);
        else no_of_bbirds = 4;


    }
}
