#include <iostream>
#define add_parameter(T,X)  \
   NamedParam<T> X;    \
//This object is created during function call
template<typename T>
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
add_parameter(double,point);
add_parameter(int,line);
add_parameter(double,circle);

//Function to be implemented
void function_impl(double point_, int line_, double circle_)
{
    std::cout<<"C*L-P = "<<circle_*line_-point_<<std::endl;
}
//Function to accept named parameters and forward to function_impl

template<typename...T>
void function(T... t)
{
    auto point_=point.get_value();
    auto line_=line.get_value();
    auto circle_= circle.get_value();
    function_impl(point_,line_,circle_);
}

/*Consider a function that takes 3 parameters and does certain arithmetic operations on it.
 * We implement here a prototype for using named parameter function
 * The function currently takes only int values, but order doesn't matter.
 */

int main() {
    function(point=2.5,line=9,circle=9.2);
}