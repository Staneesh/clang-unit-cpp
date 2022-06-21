class Square
{
private:
    int side;
    int area;

public:
    Square() { setSide(0); }
    Square(int s) { setSide(s); }
    void setSide(int newSide)
    {
        this->side = newSide;
        this->area = this->side * this->side;
    }
    int getArea() const { return this->area; }
    int getSide() const { return this->side; }
};