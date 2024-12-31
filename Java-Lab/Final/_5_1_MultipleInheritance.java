// Interface for shape calculations
interface Shape {
    double calculate();
    void getValues(double length, double width);
}

// Rectangle class implementing Shape interface
class Rectangle implements Shape {
    protected double length;
    protected double width;
    
    @Override
    public void getValues(double length, double width) {
        this.length = length;
        this.width = width;
    }
    
    @Override
    public double calculate() {
        return length * width;
    }
}

// Triangle class implementing Shape interface
class Triangle implements Shape {
    private double base;
    private double height;
    
    @Override
    public void getValues(double base, double height) {
        this.base = base;
        this.height = height;
    }
    
    @Override
    public double calculate() {
        return 0.5 * base * height;
    }
}

// Main class to test the implementation
public class _5_1_MultipleInheritance{
    public static void main(String[] args) {
        // Create Rectangle object
        Rectangle rectangle = new Rectangle();
        rectangle.getValues(10.5, 7.3);
        System.out.println("Area of Rectangle = " + rectangle.calculate());
        
        // Create Triangle object
        Triangle triangle = new Triangle();
        triangle.getValues(10.5, 7.3);
        System.out.println("Area of Triangle = " + triangle.calculate());
    }
}
