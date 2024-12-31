class Square {
    int a, A;

    public void inputvalues(int x) {
        a = x;
    }

 public void displayArea ()
 {
 A=a*a;
 System.out.println ('Area of square : " +A);
 }
}

class Triangle {
    double a, b, A;

 public void inputvalues (int x, int y)
 {
 a=x;
 b=y;

    public void displayArea() {
        A = 0.5 * a * b;
        System.out.println("Area of Triangle: " + A);
    }}

 Class Circle{
    Double r, A;Public

    void inputvalues(int x) {
        r = x;
    }Public

    void displayArea()
{
A=3.14*r*r;
System.out.println(“Area of circle:”+A);
}
}

Public

class shapeex1
{
Public static void main(String args[])
{
Square S=new Square();
Triangle T=new Triangle();
Circle C=new Circle();
S.inputvalues(10);
T.inputvalues(9,10);
C.inputvalues(12);

S.displayArea();
T.displayArea();
C.displayArea();
}
}
