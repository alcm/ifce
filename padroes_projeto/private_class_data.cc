#include <iostream>

class Triangle {
   public:
    Triangle(const float base, const float height)
        : base_(base), height_(height)
    {

    }

    float CalculateArea() const
    {
        return (base_ * height_) / 2;

    }

   private:
    float base_;
    float height_;
};

int main()
{
    Triangle t(4.0, 10.0);

    std::cout << t.CalculateArea() << std::endl;
}
