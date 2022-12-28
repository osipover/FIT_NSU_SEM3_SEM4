#pragma once 
#include <iostream>
#include <tuple>

template <size_t>
struct int_ {};

template <class Ch, class Tr, class...Types>
void printTuple(std::basic_ostream<Ch, Tr>& os, std::tuple<Types...> const& t, int_<1>) {
	os << std::get<sizeof...(Types) - 1>(t) << " ";
}

template <class Ch, class Tr, class...Types, size_t pos>
void printTuple(std::basic_ostream<Ch, Tr>& os, std::tuple<Types...> const& t, int_<pos>) {
	os << std::get<sizeof...(Types) - pos>(t) << " ";
	printTuple(os, t, int_<pos - 1>());
}

template <class Ch, class Tr, class...Types>
auto& operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Types...> const& t) {
	printTuple(os, t, int_<sizeof...(Types)>());
	return os;
}
