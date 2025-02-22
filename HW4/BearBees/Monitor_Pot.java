public class Monitor_Pot {
    //Monitor_Pot is a monitor of type shared cell (lecture 12)
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
    }
}
