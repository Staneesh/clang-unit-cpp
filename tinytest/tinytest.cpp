class A
{
    int m;

public:
    template <typename T>
    T getM() { return (T)this->m; }
    A(int x) : m(x){};
};