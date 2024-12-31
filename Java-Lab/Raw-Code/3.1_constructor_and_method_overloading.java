import java.util.Scanner;
class Prog5 {
    public int a, b;
    Prog5() {
        Scanner S1 = new Scanner(System.in);
System.out.println("Enter any 2 integers:");
        a = S1.nextInt();
        b = S1.nextInt();
    }
    void display() {
System.out.println("Addition=" + (a + b));
System.out.println("Subtraction=" + (a - b));
System.out.println("Multiplication=" + (a * b));
System.out.println("Division=" + ((float) a / b)); // Convert one operand to float to get float division
    }

    Prog5(float a1, float b1) {
System.out.println("Addition=" + (a1 + b1));
System.out.println("Subtraction=" + (a1 - b1));
System.out.println("Multiplication=" + (a1 * b1));
System.out.println("Division=" + (a1 / b1));
    }

    void display(int x) {
System.out.println("Square of " + x + " is " + (x * x));
    }
}

class Program3rd {
    public static void main(String[] args) {
        Scanner S1 = new Scanner(System.in);
System.out.println("\nArithmetic operations on float");
System.out.println("Enter any two float values");
        float a1 = S1.nextFloat();
        float a2 = S1.nextFloat();
        Prog5 arth1 = new Prog5(a1, a2);

System.out.println("\nArithmetic operations on integers");
        Prog5 arth2 = new Prog5();

System.out.println("\nEnter number to find Square");
        int x = S1.nextInt();
        arth1.display(x);
    }
}
