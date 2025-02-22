public class Honeybee extends Thread {
    //Producer
    private Monitor_Pot honeypot;
    private int id;
    private int[] honey_tracker;

    public final long SLEEPDURATION = 20;

    public Honeybee (Monitor_Pot honeypot, int id, int[] honey_tracker) {
        this.honeypot = honeypot;
        this.id = id;
        this.honey_tracker = honey_tracker;
    }

    public void run() {
        try {
            while (true) {
                honeypot.add_honey();
                honey_tracker[id]++;
                System.out.println("Honeybee " + id + " added a drop of honey.");
                Thread.sleep(SLEEPDURATION);
            }
        } catch (InterruptedException e) {}
    }
}
