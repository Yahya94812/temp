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

    // public static void main(String[] args) {
    //     Outer outer = new Outer();
    //     Outer.Inner inner = outer.new Inner();

    //     System.out.println("From Outer class main:");
    //     System.out.println("Outer class x = " + outer.x); // Accessing private x of Outer class
    //     inner.displayValues(); // Demonstrating access to inner class members
    // }
}

// Different class to demonstrate protected access
public class InnerClassDemo {
    public static void main(String[] args) {
        Outer outer = new Outer();
        Outer.Inner inner = outer.new Inner();

        System.out.println("\nFrom different class:");
        System.out.println("Outer class protected z = " + outer.z); // Accessing protected z of Outer class
        System.out.println("Inner class protected z = " + inner.z); // Accessing protected z of Inner class

        // Note: Cannot access private members x directly
        // System.out.println(outer.x); // This would cause a compilation error
        // System.out.println(inner.x); // This would cause a compilation error

        inner.displayValues(); // Accessing the displayValues method to print values
    }
}
