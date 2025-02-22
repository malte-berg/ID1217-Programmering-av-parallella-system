public class bearbees {
    static int[] honey_tracker;
    static int no_of_bees;
    static final int POTCAPACITY = 10;
    static final int SIMDURATION = 10000;

    public static void main(String[] args) {
        // Set no of honeybees (producers) to args or 4 if no args.
        if (args.length > 0) no_of_bees = Integer.parseInt(args[0]);
        else no_of_bees = 4;
        Monitor_Pot honeypot = new Monitor_Pot(POTCAPACITY);

        Bear bear = new Bear(honeypot);
        Honeybee[] honeybees = new Honeybee[no_of_bees];
        honey_tracker = new int[no_of_bees];

        bear.start();
        for (int i = 0; i < no_of_bees; i++) {
            honeybees[i] = new Honeybee(honeypot, i, honey_tracker);
            honeybees[i].start();
        }

        try {
            Thread.sleep(SIMDURATION);
        } catch (InterruptedException e) {}
        bear.interrupt();
        for (Honeybee bee : honeybees) {
            bee.interrupt();
        }
        System.out.println("\n-------- RESULTS --------");
        for (int i = 0; i < no_of_bees; i++) {
            System.out.println("Honeybee " + i + " added " + honey_tracker[i] + " drops of honey.");
        }
        System.exit(0);
    }
}
