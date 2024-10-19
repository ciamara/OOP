package gameoflife.structs;

public class Vector {
    private int x;
    private int y;

    public Vector(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public Vector(Vector other) {
        this.x = other.GetX();
        this.y = other.GetY();
    }

    public int GetX() {
        return x;
    }

    public int GetY() {
        return y;
    }

    public Vector Add(Vector other) {
        int tempx = this.x + other.GetX();
        int tempy = this.y + other.GetY();

        return new Vector(tempx, tempy);
    }

    public String ToString() {
        return "x: " + this.x + ", y: " + this.y;
    }

    public boolean IsEqual(Vector other) {
        
        if((this.x==other.GetX())&&(this.y==other.GetY())){
            return true;
        }
        return false;
    }
}
