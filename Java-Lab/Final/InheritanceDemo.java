public class _4_1_Inheritance {
    
}
// Parent/Super class
class Supr {
    int x;
    
    Supr(int x) {
        this.x = x;
    }
    
    void display() {
        System.out.println("Sup x = " + x);
    }
}

// Child/Sub class demonstrating single-level inheritance
class Sub extends Sup {
    int y;
    
    Supr(int x, int y) {
        super(x);
        this.y = y;
    }
    
    void display() {
        System.out.println("Sup x = " + x);
        System.out.println("Sup y = " + y);
    }
}

// Another child class demonstrating multilevel inheritance
class SubSubr extends Supr {
    int z;
    
    SubSubr(int x, int y, int z) {
        super(x, y);
        this.z = z;
    }
    
    void display() {
        System.out.println("Sup x = " + x);
        System.out.println("Sup y = " + y);
        System.out.println("Sup z = " + z);
    }
}

// Main class
public class InheritanceDemo {
    public static void main(String[] args) {
        System.out.println("Single-level Inheritance:");
        Supr s1 = new Supr(100, 200);
        s1.display();
        
        System.out.println("\nMulti-level Inheritance:");
        SubSubr s2 = new SubSubr(100, 200, 300);
        s2.display();
    }
}