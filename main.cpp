#include <iostream>
#include <cstring>
#define GET_VARIABLE_NAME(Variable) (#Variable)
#define add_parameter(X)                               \
   NamedParam X((const char*)GET_VARIABLE_NAME(X));    \
//This class acts as a wrapper class for associating tag and data
template<typename T>
class named_value
{
public:
    const char* name;
    T value;
    named_value(const char * name1, T a) : name(name1), value(a) {
    }
    T get_param()
    {
        return value;
    }
    const char* get_name()
    {
        return name;
    }
};


//This object is created during function call
class NamedParam
{
public:
    const char* tag;
    explicit NamedParam(const char * tag) : tag(tag) {
    }
    template<typename T>
    auto operator=(T value)
    {
        return named_value<decltype(value)>(tag, value);
    }

};


//Function to associate name to value, from a list of variadic templates
template<typename T>
auto find(const char* str,T x)
{
    if(strcmp(x.get_name(),str)==0)
        return x.get_param();
    return 0;
}
template<typename T1,typename...T>
auto find(const char* str,T1 x,T... t)
{
    if(strcmp(x.get_name(),str)==0)
        return x.get_param();
    return find(str,t...);
}


//Function to be implemented
void function_impl(int point, int line, int circle)
{
    std::cout<<"C*L-P = "<<circle*line-point<<std::endl;
}
//Function to accept named parameters and forward to function_impl
template<typename...T>
void function(T... t)
{
    auto point_=find("point",t...);
    auto line_=find("line",t...);
    auto circle_= find("circle",t...);
    function_impl(point_,line_,circle_);
}

/*Consider a function that takes 3 parameters and does certain arithmetic operations on it.
 * We implement here a prototype for using named parameter function
 * The function currently takes only int values, but order doesn't matter.
 */

int main() {
    add_parameter(point);
    add_parameter(line);
    add_parameter(circle);
    function(point=2,line=9,circle=3);
    function(line=9,circle=3,point=2);
}