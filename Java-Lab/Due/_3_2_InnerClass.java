
class Outer {
    private int x = 10;
    protected int z = 30;

    class inner {
        private int x = 20;
        protected int z = 85;
    }

    public static void main(String args[]) {
        Outer obj1 = new Outer();
        inner obj2 = new Outer().new inner();
        System.out.println("Through Outer Class, x = " + obj1.x);
        System.out.println("Through Inner Class, x = " + obj2.x);
    }
}

public class _3_2_InnerClass {
    public static void main(String args[]) {
        Outer ob1 = new Outer();
        Outer.inner ob2 = new Outer().new inner();
        System.out.println("Through Different Class, Outer's protected z = " + ob1.z);
        System.out.println("Through Different Class, Inner's protected z = " + ob2.z);
    }
}