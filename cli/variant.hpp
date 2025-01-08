#pragma once
#include <variant>

template<class... Ts>
struct overloads : Ts... { using Ts::operator()...; };


template<class... Ts> 
struct cases : Ts... { using Ts::operator()...; };

template<class... Ts> 
cases(Ts...)->cases<Ts...>;

template<typename V, typename Callable>
decltype(auto) match(V&& v, Callable&& c) {
    return std::visit(std::forward<Callable>(c), std::forward<V>(v));
}