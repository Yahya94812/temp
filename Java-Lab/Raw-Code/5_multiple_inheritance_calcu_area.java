interface compute
{
	double calculate();
}
class Rectangle implements compute 
{
	double l,b;
    void getvalues()
	{
		l = 10.5F;
		b=7.3F;
	}
	
public double calculate()
 {
		return (l*b);
	}
}

class TRI extends Rectangle implements compute
{
	public double calculate()
	{
		return (0.5*b*l);
	}
}
class prog4b
{
	public static void main(String[] args)
	{
	Rectangle R = new Rectangle();
	R.getvalues();
	System.out.println("Area of Rectangle = " + R.calculate());
	TRI T =new TRI();
	T.getvalues();
	System.out.println("Area of triangle = " + T.calculate());
	}}
