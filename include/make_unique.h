#ifndef mspertus_make_unique_h
#  define mspertus_make_unique_h
#include <memory>
#include <utility>

namespace mspertus { 
template<template <typename ...U> typename T, typename ...A>
auto make_unique(A&& ...a) {
    return std::make_unique<decltype(T(std::forward<A>(a)...))>(std::forward<A>(a)...);
}

template<template <class ...U> class T, class ...Args>
auto make_shared(Args&& ... args) {
    return std::make_shared<decltype(T(std::forward<Args>(args)...))>(std::forward<Args>(args)...);
}

template<template <class ...U> class T, class A, class ...Args>
auto allocate_shared(const A& a, Args&& ... args) {
    return std::allocate_shared<decltype(T(std::forward<Args>(args)...))>(a, std::forward<Args>(args)...);
}
}
#endif
