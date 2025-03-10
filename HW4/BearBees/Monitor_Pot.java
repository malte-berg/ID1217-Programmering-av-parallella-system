public class Monitor_Pot {
    /** Monitor_Pot is a monitor of type shared cell (lecture 12)
      * This type of monitor with the solution down below provides a fair
      * solution as there is no preference for what thread goes next in the
      * synchronized methods. It is random.
    **/
    private int honeypot_size, honey_in_pot;
    private boolean pot_full;

    public Monitor_Pot(int honeypot_size) {
        this.honeypot_size = honeypot_size;
        this.honey_in_pot = 0;
        this.pot_full = false;
    }

    // For honeybees (producers)
    public synchronized void add_honey() {
        while (pot_full) {
            try {
                wait();
            } catch (InterruptedException e) { }
        }
        // If the honeybee adds the last drop of honey, wake the bear
        if (++honey_in_pot == honeypot_size) {
            pot_full = true;
            notifyAll();
        }
    }

    // For bear (consumer)
    public synchronized void eat_honey() {
        while (!pot_full) {
            try {
                wait();
            } catch (InterruptedException e) { }
        }
        honey_in_pot = 0;
        pot_full = false;
        notifyAll();
    }
}
