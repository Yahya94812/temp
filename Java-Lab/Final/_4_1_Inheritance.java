// Parent/Super class
class Supr {
    int x;

    Supr(int x) {
        this.x = x;
    }

    void display() {
        System.out.println("Supr x = " + x);
    }
}

// Child/Sub class demonstrating single-level inheritance
class Sub extends Supr {
    int y;

    Sub(int x, int y) {
        super(x);
        this.y = y;
    }

    void display() {
        System.out.println("Supr x = " + x);
        System.out.println("Sub y = " + y);
    }
}

// Another child class demonstrating multilevel inheritance
class SubSubr extends Sub {
    int z;

    SubSubr(int x, int y, int z) {
        super(x, y);
        this.z = z;
    }

    void display() {
        System.out.println("Supr x = " + x);
        System.out.println("Sub y = " + y);
        System.out.println("SubSubr z = " + z);
    }
}

// Main class
public class _4_1_Inheritance {
    public static void main(String[] args) {
        System.out.println("Single-level Inheritance:");
        Sub s1 = new Sub(100, 200);
        s1.display();

        System.out.println("\nMulti-level Inheritance:");
        SubSubr s2 = new SubSubr(100, 200, 300);
        s2.display();
    }

}