class MyRunnable implements Runnable {
    private String threadName;

    public MyRunnable(String threadName) {
        this.threadName = threadName;
    }

    @Override
    public void run() {
        System.out.println(threadName + "Starting.");
        for (int i = 0; i < 10; i++) {
            System.out.println("In " + threadName + "  count is " + i);
            try {
                Thread.sleep(100); // Simulate some work
            } catch (InterruptedException e) {
                System.out.println(threadName + " interrupted.");
            }
        }
        System.out.println(threadName + " terminating.");
    }
}

public class _8_Threads {
    public static void main(String[] args) {
        System.out.println("Main thread starting");

        // Creating threads
        Thread child1 = new Thread(new MyRunnable("Child #1 "));
        Thread child2 = new Thread(new MyRunnable("Child #2 "));
        Thread child3 = new Thread(new MyRunnable("Child #3 "));

        // Starting threads
        child1.start();
        child2.start();
        child3.start();

        // Waiting for threads to finish
        try {
            child1.join();
            System.out.println("Child #1 joined");
            child2.join();
            System.out.println("Child #2 joined");
            child3.join();
            System.out.println("Child #3 joined");
        } catch (InterruptedException e) {
            System.out.println("Main thread interrupted.");
        }

        System.out.println("Main thread ending");
    }
}
