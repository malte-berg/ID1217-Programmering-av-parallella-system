public class Bear extends Thread {
    //Consumer
    private Monitor_Pot honeypot;

    public Bear (Monitor_Pot honeypot) {
        this.honeypot = honeypot;
    }

    public void run() {
        while (true) {
            honeypot.eat_honey();
            System.out.println("Yum! I ate <3");
        }
    }
}
