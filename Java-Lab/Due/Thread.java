public class Thread {
    
}

class Square {
    int a, A;

    public void inputvalues(int x) {
        a = x;
    }

    public void displayArea() {
        A = a * a;
        System.out.println("Area of square: " + A);
    }
}

class Triangle {
    double a, b, A;

    public void inputvalues(int x, int y) {
        a = x;
        b = y;
    }

    public void displayArea() {    A = 0.5 * a * b;
        System.out.println("Area of Triangle: " + A);
    }
}

class Circle {
    double r, A;

    public void inputvalues(int x) {
        r = x;
    }

    public void displayArea() {
        A = 3.14 * r * r;
        System.out.println("Area of circle: " + A);
    }
}

public class _6_package {
    public static void main(String[] args) {
        Square S = new Square();
        Triangle T = new Triangle();
        Circle C = new Circle();

        S.inputvalues(10);
        T.inputvalues(9, 10);
        C.inputvalues(12);    S.displayArea();
        T.displayArea();
        C.displayArea();
    }
}
	 }
	System.out.println(thrd.getName() + " terminating");
    }
}

public class JoinThreads{

    public static void main(String[] args) {
	System.out.println("Main thread starting");
	MyThread mt1=new MyThread("Child #1");
	MyThread mt2=new MyThread("Child #2");
	MyThread mt3=new MyThread("Child #3");
	 try
	 {
	mt1.thrd.join();
	System.out.println("Child #1 joined");
	mt2.thrd.join();
	System.out.println("Child #2 joined");
	mt3.thrd.join();
	System.out.println("Child #3 joined");
	 }catch(InterruptedExceptionexc)
	 {
		System.out.println("Main thread interrupted");
	 }
	System.out.println("Main thread ending");
    }
}
