class Square
{
public:
    int side;
    int area;

    Square() { setSide(0); }
    Square(int s) { setSide(s); }
    void setSide(int newSide)
    {
        this->side = newSide;
        this->area = this->side * this->side;
    }
};