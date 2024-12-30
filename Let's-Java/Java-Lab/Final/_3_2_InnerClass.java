// Outer class
class Outer {
    private int x = 10;
    protected int z = 30;

    // Inner class
    class Inner {
        private int x = 20;
        protected int z = 85;

        // Method to demonstrate access to both Outer and Inner class variables
        void displayValues() {
            System.out.println("Inner class x = " + x);
            System.out.println("Outer class x = " + Outer.this.x);
            System.out.println("Inner class z = " + z);
            System.out.println("Outer class z = " + Outer.this.z);
        }
    }

    // Method to create and use Inner class
    // void createInner() {
    //     Inner inner = new Inner();
    //     inner.displayValues();
    // }

    public static void main(String[] args) {
        Outer outer = new Outer();
        Outer.Inner inner = new Outer().new Inner();
        
        System.out.println("From Outer class main:");
        System.out.println("Outer class x = " + outer.x);  // Accessing private x
        System.out.println("Inner class x = " + inner.x);  // Accessing private x
    }
}

// Different class to demonstrate protected access
public class _3_2_InnerClass {
    public static void main(String[] args) {
        Outer outer = new Outer();
        Outer.Inner inner = outer.new Inner();
        
        System.out.println("\nFrom different class:");
        System.out.println("Outer class protected z = " + outer.z);     // Accessing protected z
        System.out.println("Inner class protected z = " + inner.z);     // Accessing protected z
        
        // Note: Cannot access private members x from here
        // System.out.println(outer.x);  // This would cause compilation error
        // System.out.println(inner.x);  // This would cause compilation error
    }
}
