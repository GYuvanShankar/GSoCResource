#include <iostream>
void function_impl(char* name,int a, double b);
template <typename T>
class NamedParameter {
public:
    T value;

    NamedParameter<void>* operator =(const T &value) {
        this->value = value;
        return nullptr;
    }

    operator T() const {
        return value;
    }
};

class Wrapper
{
public:
    NamedParameter<int> a;
    NamedParameter<double> b;
    void function(char* name, NamedParameter<void> *)
    {
        function_impl(name,a,b);
    }
};
void function_impl(char* name,int a, double b)
{
    std::cout<<"name: "<<name<<std::endl;
    std::cout<<"a: "<<a<<std::endl;
    std::cout<<"b: "<<b<<std::endl;
}


int main() {
    Wrapper w;
    w.function("XYZ",(w.b=12,w.a=13));
    w.function("XYZ",(w.a=13,w.b=12));
}
