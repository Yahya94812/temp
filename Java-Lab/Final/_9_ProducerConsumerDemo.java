/**
 * SharedBuffer class handles the synchronization between producer and consumer
 * Acts as a single-slot buffer for data exchange
 */
class SharedBuffer {
    private int contents; // The shared data
    private boolean available; // Flag to indicate if data is available

    public SharedBuffer() {
        available = false;
    }

    /**
     * Method for consumer to get data
     * Synchronized to ensure thread safety
     */
    public synchronized int get() {
        // Wait while buffer is empty
        while (!available) {
            try {
                System.out.println("Consumer waiting for data...");
                wait();
            } catch (InterruptedException e) {
                System.out.println("Consumer interrupted");
            }
        }

        // Buffer is now available
        available = false; // Mark buffer as empty
        notifyAll(); // Notify producers waiting to put data

        System.out.println("Consumer got: " + contents);
        return contents;
    }

    /**
     * Method for producer to put data
     * Synchronized to ensure thread safety
     */
    public synchronized void put(int value) {
        // Wait while buffer is full
        while (available) {
            try {
                System.out.println("Producer waiting to put data...");
                wait();
            } catch (InterruptedException e) {
                System.out.println("Producer interrupted");
            }
        }

        // Buffer is now empty and ready for new data
        contents = value; // Put new value in buffer
        available = true; // Mark buffer as full
        notifyAll(); // Notify consumers waiting to get data

        System.out.println("Producer put: " + value);
    }
}

/**
 * Producer class - produces data and puts it in the shared buffer
 */
class Producer implements Runnable {
    private SharedBuffer buffer;
    private int producerId;

    public Producer(SharedBuffer buffer, int id) {
        this.buffer = buffer;
        this.producerId = id;
    }

    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            buffer.put(i);
            try {
                // Sleep for random time to simulate varying production speeds
                Thread.sleep((int) (Math.random() * 1000));
            } catch (InterruptedException e) {
                System.out.println("Producer " + producerId + " interrupted");
            }
        }
    }
}

/**
 * Consumer class - consumes data from the shared buffer
 */
class Consumer implements Runnable {
    private SharedBuffer buffer;
    private int consumerId;

    public Consumer(SharedBuffer buffer, int id) {
        this.buffer = buffer;
        this.consumerId = id;
    }

    @Override
    public void run() {
        int value;
        for (int i = 0; i < 5; i++) {
            value = buffer.get();
            try {
                // Sleep for random time to simulate varying consumption speeds
                Thread.sleep((int) (Math.random() * 1000));
            } catch (InterruptedException e) {
                System.out.println("Consumer " + consumerId + " interrupted");
            }
        }
    }
}

/**
 * Main class to demonstrate Producer-Consumer pattern
 */
public class _9_ProducerConsumerDemo {
    public static void main(String[] args) {
        // Create shared buffer
        SharedBuffer buffer = new SharedBuffer();

        // Create producer and consumer threads
        Thread producerThread = new Thread(new Producer(buffer, 1), "Producer-1");
        Thread consumerThread = new Thread(new Consumer(buffer, 1), "Consumer-1");

        // Start the threads
        System.out.println("Starting Producer and Consumer threads...");
        producerThread.start();
        consumerThread.start();

        // Wait for threads to complete
        try {
            producerThread.join();
            consumerThread.join();
        } catch (InterruptedException e) {
            System.out.println("Main thread interrupted");
        }

        System.out.println("Producer-Consumer demonstration completed.");
    }
}