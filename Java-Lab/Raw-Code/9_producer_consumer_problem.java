class Consumer extends Thread {
    private Sync sync;
    private int number;

    public Consumer(Sync c, int number) {
        sync = c;
        this.number = number;
    }

    public void run() {
        int value = 0;
        for (int i = 0; i < 5; i++) {
            value = sync.get();
            System.out.println("Consumer#" + this.number + "got:" + value);
            try {
                sleep((int) (Math.random() * 10000));
            } catch (InterruptedException e) {
            }
        }
    }
}

class Producer extends Thread {
    private Sync sync;
    private int number;

    public Producer(Sync c, int number) {
        sync = c;
        this.number = number;
    }

    public void run() {
        for (int i = 0; i < 5; i++) {
            sync.put(i);
            System.out.println("Produces" + this.number + "put:" + i);
            try {
                sleep((int) (Math.random() * 10000));
            } catch (InterruptedException e) {
            }
        }
    }
}

class ProducerConsumerTest {
    public static void main(String[] args) {
        Sync c = new Sync();
        Producer p1 = new Producer(c, 1);
        Consumer c1 = new Consumer(c, 1);
        p1.start();
        c1.start();
    }
}

class Sync {
    private int contents;
    private boolean available = false;

    public synchronized int get() {
        while (available == false) {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        available = false;
        notifyAll();
        return contents;
    }

    public synchronized void put(int value) {
        while (available == true) {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        contents = value;
        available = true;
        notifyAll();
    }
}
