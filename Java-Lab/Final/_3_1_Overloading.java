import java.util.Scanner;

public class _3_1_Overloading {
    public int a, b;

    _3_1_Overloading() { 
        Scanner input = new Scanner(System.in);
        System.out.println("\nEnter number to find Square");
        a = input.nextInt();
    }

    _3_1_Overloading(float a1, float b1) {
        System.out.println("Addition=" + (a1 + b1));
        System.out.println("Subtraction=" + (a1 - b1));
        System.out.println("Multiplication=" + (a1 * b1));
        System.out.println("Division=" + (a1 / b1));
    }

    void display() {
        System.out.println("Addition=" + (a + b));
        System.out.println("Subtraction=" + (a - b));
        System.out.println("Multiplication=" + (a * b));
        System.out.println("Division=" + ((float) a / b)); // Convert one operand to float to get float division
    }

    void display(int x) {
        System.out.println("Square of " + x + " is " + (x * x));
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.println("\nArithmetic operations on float");
        System.out.println("Enter any two float values:");
        float a1 = input.nextFloat();
        float a2 = input.nextFloat();
        _3_1_Overloading arth1 = new _3_1_Overloading(a1, a2);
        arth1.display();

        System.out.println("\nfinding square of integers");
        _3_1_Overloading sq = new _3_1_Overloading();
        sq.display(sq.a);
    }
}
