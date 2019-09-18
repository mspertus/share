#include<string_view>
#include<iostream>
#include<string>
using namespace std;

// See my CPPCon slides at ... for explanation
template<typename T>
concept DeducesBasicStringView = requires(T x) {
    basic_string_view(x);
};

template<typename charT, typename Traits>
void f_impl(basic_string_view<charT, Traits> s)
{
    cout << s.size() << endl;
}

void f(DeducesBasicStringView auto&& t)
{
    f_impl(basic_string_view(t));
}

template<typename charT, typename traits, typename alloc>
void f(string<charT, traits, alloc>& s)
{
    return f_impl(basic_string_view<charT, traits>(s));
}

// Note: The following example requires C++20 CTAD for alias templates
#ifdef CPP20_CTAD_FOR_ALIAS_TEMPLATES
template<typename W> struct SSS { SSS(W); };

template<typename T>
void fp_impl(SSS<T*>) {}

template<typename T>
using STP = SSS<T*>;
template<typename T>
void fp(T t)
{
    STP arg0(t);
    fp_impl(arg0);
}
#endif

int main()
{
    f("foo");
#ifdef CPP20_CTAD_FOR_ALIAS_TEMPLATES
    fp(new int);
#endif
    return 0;
}