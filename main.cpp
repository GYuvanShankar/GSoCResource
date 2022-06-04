#include <iostream>
#include<cstring>
#define add_parameter(Tag, Name)  \
    struct Tag{};\
   NamedParam<Tag> Name;         \
//This class acts as a wrapper class for associating tag and data
template<typename Tag, typename DT>
class named_value
{
public:
    DT value;
    explicit named_value(DT a) :value(a) {
    }
    DT get_param()
    {
        return std::forward<DT>(value);
    }
    template<typename Tp>
    bool compare(Tp a)
    {
        return std::is_same<Tp,Tag>::value;
    }
};
//This object is created during function call
template<class Tag>
class NamedParam
{
public:
    explicit NamedParam() = default;
    template<typename DT>
    auto operator = (DT value)
    {
        return named_value<Tag,DT>(value);
    }

};
add_parameter(point_,point);
add_parameter(line_,line);
add_parameter(circle_,circle);

//Function to associate name to value, from a list of variadic templates
template<typename DT,typename Tag,typename NV>
DT find(NV x)
{
    if(x.compare(Tag()))
        return x.get_param();
    return DT();
}
template<typename DT,typename Tag,typename NV,typename...T>
DT find(NV x,T... t)
{
    if(x.compare(Tag()))
        return x.get_param();
    return find<DT,Tag>(t...);
}


//Function to be implemented
void function_impl(int point, double line,char circle)
{
    std::cout<<"C*L-P = "<<line-point<<std::endl;
    std::cout<<circle<<std::endl;
}
//Function to accept named parameters and forward to function_impl
template<typename...T>
void func(T... t)
{
    auto p=find<int,point_>(std::forward<T>(t)...);
    auto l=find<double,line_>(std::forward<T>(t)...);
    auto c=find<char,circle_>(std::forward<T>(t)...);
    function_impl(p,l,c);
}

/*Consider a function that takes 3 parameters and does certain arithmetic operations on it.
 * We implement here a prototype for using named parameter function
 * The function currently takes only int values, but order doesn't matter.
 */

int main() {
    func(circle='a',line=9.5,point=2);
    func(line=9,circle='x',point=2);
}