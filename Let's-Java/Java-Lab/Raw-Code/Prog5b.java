class Outer {
    private int x = 10;
    protected int z = 30;

    class inner {
        private int x = 20;
        protected int z = 85;
    }

   
}

 public class Prog5b {
    public static void main(String args[]) {
        Outer ob1 = new Outer();
        Outer.inner ob2 = new Outer().new inner();
        System.out.println("Through Different Class, Outer's protected z = " + ob1.z);
        System.out.println("Through Different Class, Inner's protected z = " + ob2.z);
    }
}
