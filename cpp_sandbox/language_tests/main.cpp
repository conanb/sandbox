// this is literally just a test of "modern" c++
// i've used/taught a lot of this in the past, but it's always
// good to rehash knowledge
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <map>

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

// a reminder on data padding
struct padded_bad {
	char c;
	// extra 3 bytes padding here!
	float f;
	short s;
	// extra 2 bytes padding here!
	int i;
};
struct padded_better {
	float f;
	int i;
	short s;
	char c;
	// extra 1 byte padding here
};

// force padding
struct alignas(4) padded_char {
	char c;
	// extra 3 bytes padding
	char c2;
	// extra 3 bytes padding
};

// final 
class Brand {};
class CarBrand : Brand {};
class Subaru final : CarBrand {};
// class FunkySubaru : Subaru {};

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
	std::cout << arr10[0] << ' ' << arr10[9] << std::endl;
	auto arr = new array_10i;

	// type aliases
	using vec2f = vec<float, 2>();
	using vec3f = vec<float, 3>();
	using vec4f = vec<float, 4>();
	using vec4d = vec<double, 4>();

	// initialiser list is a little different to what I remember
	foo({ 1, 2, 3 });

	// vec with size 5
	std::vector<int> v1(5);
	// vec with a single int added with value 5
	std::vector<int> v2{ 5 };

	auto j = { 5 }; // std::initializer_list copy, so auto becomes std::initializer_list<int>
	auto k{ 5 }; // deduction, not std::initializer_list in c++17+

	auto lis = { 5, 6 }; // std::initializer_list copy
	// auto m{ 5, 6 }; // not posible since it isn't using a std::initializer_list

	// for some reason this is missing
	std::byte x = (std::byte)10;

	 // good ol scoped enums for clearer code
	enum class Result { Success, Failure, Ongoing };
	Result result = Result::Ongoing;
	// or using...
	using Result::Ongoing;
	Result result2 = Ongoing;

	// this is great!
	switch (result)
	{
		// with using you don't need to declare enum scope constantly
		using enum Result;
		case Success:
		case Failure:
		case Ongoing:
		default:
			break;
	}

	// fun way to expose enums within class
	class Behaviour {
	public:
		enum class Result { Success, Failure, Ongoing };
		using enum Result;
	};
	auto g_thing = Behaviour::Failure;

	std::map<std::string, int> ma{
		{"Conan", 42},
		{"Cheaky", 69}
	};
	// ok I'm liking this...
	for (auto&& [key, value] : ma) {
		std::cout << key << ' ' << value << std::endl;
	}

	return 0;
}