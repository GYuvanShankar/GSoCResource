#include <iostream>

//This object is created during function call
template<typename T,class Y>
class NamedParam
{
public:
    T value;
    explicit NamedParam()= default;
    NamedParam* operator=(T x)
    {
        value=x;
        return this;
    }
    T get_value()
    {
        return value;
    }
};
struct Params {
#define add_parameter(T,X,Tag)                 \
      struct Tag{};                            \
     NamedParam<T,Tag> X; \

    add_parameter(double,point,p);
    add_parameter(int,line,l);
    add_parameter(double,circle,c);
#undef add_parameter

}p1;

//Function to be implemented
void function_impl(double point_, int line_, double circle_)
{
    std::cout<<"C*L-P = "<<circle_*line_-point_<<std::endl;
}
//Function to accept named parameters and forward to function_impl

int main() {
    p1.point=23.4;
}