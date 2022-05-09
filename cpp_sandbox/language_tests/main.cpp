// this is literally just a test of "modern" c++
// i've used/taught a lot of this in the past, but it's always
// good to rehash knowledge
#include <iostream>
#include <vector>
#include <string>

// needed for the string litteral s, i.e. auto str = "Hello"s;
using namespace std::string_literals;

template <typename T>
auto add(T a, T b) {
	return a + b;
}

struct {
	template <typename T, typename U>
	auto operator () (T const a, U const b) const { return a + b; }
} L;

template <typename T, int COUNT>
struct vec
{
	T v[COUNT];
};

void foo(int a, int b, int c) {}
void foo(std::initializer_list<int> l) {}

int main(int argc, char* argv[]) {

	auto i = 42;
	auto f = 42.f;
	auto d = 42.0;
	auto s = "Blep";
	auto a = { 1, 2, 3, 4 };

	auto l = []() { std::cout << "Blag" << std::endl; };
	l();

	auto ii = add(5, 9);
	auto dd = add(5.0, 9.0);

	auto add = [](auto const a, auto const b) {return a + b; };

	auto ii2 = add(5, 9);
	auto id = add(8, 9.0);

	// use auto because .size() is a size_t not int etc
	// sure, could use unsigned int, but why bother?
	auto v = std::vector<int>{ 1, 2, 3, 4 };
	auto sz = v.size();

	// note: auto doesn't work for non-moveable types
	//auto at = std::atomic<int>(42);

	// not possible with multi-word types
	//auto ll = long long(42);
	using llong = long long;
	auto ll = llong(42); // all good
	auto ll2 = 42LL; // also ok because of compiler specifying LL type

	auto la = L("forty six"s, " and two"s);

	using uint = unsigned int;
	using byte = unsigned char;
	using array_10i = int[10];

	array_10i arr10 = {};
	// VS gives me a warning that arr10[10] is reading from an invalid source, 
	// so that's awesome!
	std::cout << arr10[0] << ' ' << arr10[10] << std::endl;
	auto arr = new array_10i;

	// type aliases
	using vec2f = vec<float, 2>();
	using vec3f = vec<float, 3>();
	using vec4f = vec<float, 4>();
	using vec4d = vec<double, 4>();

	// initialiser list is a little different to what I remember
	foo({ 1, 2, 3 });

	return 0;
}