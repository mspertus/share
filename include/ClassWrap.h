#ifndef MSPERTUS_CLASS_WRAP_H
#define MSPERTUS_CLASS_WRAP_H

// Wrap a class as a concept
// This allows the decision of whether to use a base class with
// virtual functions or statically-dispatched templates to be
// tuned over time
//
// For details, and examples, see http://bit.ly/ClassWrap_2kTMK4z 
// and http://bit.ly/ClassTemplateWrap_2m25YoB

#include<type_traits>
#include<utility>
namespace mspertus {

template<class B, class D>
concept ClassWrap = requires(D * d) { static_cast<B*>(d); };

template<template<class ...> class B, class D>
struct inherits_from_specialization {
    static char x(...);
    template<typename ...T>
    static int x(B<T...> const&);
    static bool constexpr value = std::is_same_v<decltype(x(std::declval<D>())), int>;
};
template<template<class ...> class B, class D>
concept ClassTemplateWrap = inherits_from_specialization<B, D>::value;

}
#endif