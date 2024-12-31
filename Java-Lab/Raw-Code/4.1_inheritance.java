class sup {
    int x;

    sup(int x) {
        this.x = x;
    }

    void display() {
        System.out.println("sup+x = " + x);
    }
}

class supr extends sup {
    int y;

    supr(intx,int y)
    {
    super(x);
    this.y=y;
    }

    void display() {
        System.out.println("sup-x = " + x);
        System.out.println("sup-y = " + y);
    }
}

class prog4a {
    public static void main(String args[]) {
        supr s1 = new supr(100, 200);
        s1.display();
    }
}
