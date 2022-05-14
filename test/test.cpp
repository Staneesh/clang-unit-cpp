class Square
{
    float side;
    float area;

public:
    Square() = default;
    Square(float side) { this->setSide(side); }

    void setSide(float newSide)
    {
        this->side = newSide;
        this->area = this->side * this->side;
    }
    float getArea() const { return this->area; }
    float getSide() const { return this->side; }
};