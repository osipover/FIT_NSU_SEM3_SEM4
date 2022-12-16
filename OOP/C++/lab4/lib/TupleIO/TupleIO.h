#pragma once
#include <iostream>
#include <tuple>

template <size_t>
struct int_ {};

template <class Ch, class Tr, class...Args>
void printTuple(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t, int_<1>) {
	os << std::get<sizeof...(Args) - 1>(t) << " ";
}

template <class Ch, class Tr, class...Args, size_t pos>
void printTuple(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t, int_<pos>) {
	os << std::get<sizeof...(Args) - pos>(t) << " ";
	printTuple(os, t, int_<pos - 1>());
}

template <class Ch, class Tr, class...Args>
auto& operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) {
	printTuple(os, t, int_<sizeof...(Args)>());
	return os;
}
