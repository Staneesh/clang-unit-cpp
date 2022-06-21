template <typename T>
class Square
{
public:
    T side;
    T area;

    Square() { setSide(0); }
    Square(T s) { setSide(s); }
    void setSide(T newSide)
    {
        this->side = newSide;
        this->area = this->side * this->side;
    }
};