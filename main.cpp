#include <iostream>
#include <cstring>
using TagName = const char*&;


//This class acts as a wrapper class for associating tag and data
template<TagName Name, typename T>
class named_value
{
public:
    TagName name=Name;
    T value;
    explicit named_value(TagName tag,T a)
    {
        value=a;
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
template<TagName Name>
class NamedParam
{
public:
    TagName tag = Name;
    template<typename T>
    auto operator=(T value)
    {
        return named_value<Name, decltype(value)>(tag,value);
    }

};


char* str;
//Function to associate name to value, from a list of variadic templates
template<typename T>
auto find(T x)
{
    if(strcmp(x.get_name(),str)==0)
        return x.get_param();
    return 0;
}
template<typename T1,typename...T>
auto find(T1 x,T... t)
{
    if(strcmp(x.get_name(),str)==0)
        return x.get_param();
    return find(t...);
}


//Tag/variable declaration
const char* _a="point";
const char* _b="line";
const char* _c="circle";
NamedParam<_a> point;
NamedParam<_b> line;
NamedParam<_c> circle;

//Function to be implemented
void function_impl(int point, int line, int circle)
{
    std::cout<<"C*L-P = "<<circle*line-point<<std::endl;
}
//Function to accept named parameters and forward to function_impl
template<typename...T>
void function(T... t)
{
    str="point";
    auto point=find(t...);
    str="line";
    auto line=find(t...);
    str="circle";
    auto circle= find(t...);
    function_impl(point,line,circle);
}

/*Consider a function that takes 3 parameters and does certain arithmetic operations on it.
 * We implement here a prototype for using named parameter function
 * The function currently takes only int values, but order doesn't matter.
 */

int main() {
    function(point=2,line=9,circle=3);
    function(line=9,circle=3,point=2);
}