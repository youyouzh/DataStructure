#include <iostream>
#include <functional>

// 定义一个std::function类型
typedef std::function<int(int, int)> ComputeFunction;
// 定义一个函数指针类型
typedef int (*compute_pointer)(int, int);

int compute1(int x, int y, ComputeFunction func) {
	std::cout << x << " " << y << ": " << func(x, y) << std::endl;
	return func(x, y);
}

int compute2(int x, int y, compute_pointer func)
{
	std::cout << x << " " << y << ": " << func(x, y) << std::endl;
	return func(x, y);
}

// 定义标准的回调接口
class ComputeFunc
{
public:
	virtual int compute(int x, int y) const = 0;
};

// 实现回调接口
class ComputeAdd : public ComputeFunc
{
public:
	int compute(int x, int y) const override { return x + y; }
};

int compute3(int x, int y, const ComputeFunc& compute)
{
	// 调用接口方法
	return compute.compute(x, y);
}

std::function<int(int, int)> SumFunction;

// 声明一个compute函数指针，函数参数为两个int型，返回值为int型
int(*compute)(int, int);

int max(int x, int y) { return x >= y ? x : y; }
int min(int x, int y) { return x <= y ? x : y; }
int add(int x, int y) { return x + y; }
int multiply(int x, int y) { return x * y; }

// 一个包含函数指针作为回调的函数
int compute_x_y(int x, int y, int(*compute)(int, int))
{
	// 调用回调函数
	return compute(x, y);
}

// 普通函数
int func_sum(int a, int b)
{
	return a + b;
}

class Calcu
{
public:
	int base = 20;
	// 类的成员方法，参数包含this指针
	int class_func_sum(const int a, const int b) const { return this->base + a + b; };
	// 类的静态成员方法，不包含this指针
	static int class_static_func_sum(const int a, const int b) { return a + b; };
};

// 仿函数
class ImitateAdd
{
public:
	int operator()(const int a, const int b) const { return a + b; };
};

// lambda函数
auto lambda_func_sum = [](int a, int b) -> int { return a + b; };

// 函数指针
int (*func_pointer)(int, int);

void print_func(int x, int y, int z)
{
	std::cout << x << " " << y << " " << z << std::endl;
}
std::function<void(int, int, int)> Func;

int main(void) 
{
	int x = 2; 
	int y = 5;

	// 普通函数
	SumFunction = func_sum;
	int sum = SumFunction(x, y);
	std::cout << "func_sum：" << sum << std::endl;

	// 类成员函数
	Calcu obj;
	SumFunction = std::bind(&Calcu::class_func_sum, obj, 
		std::placeholders::_1, std::placeholders::_2); // 绑定this对象
	sum = SumFunction(x, y);
	std::cout << "Calcu::class_func_sum：" << sum << std::endl;

	// 类静态函数
	SumFunction = Calcu::class_static_func_sum;
	sum = SumFunction(x, y);
	std::cout << "Calcu::class_static_func_sum：" << sum << std::endl;

	// lambda函数
	SumFunction = lambda_func_sum;
	sum = SumFunction(x, y);
	std::cout << "lambda_func_sum：" << sum << std::endl;

	// 带捕获的lambda函数
	int base = 10;
	auto lambda_func_with_capture_sum = [&base](int x, int y)->int { return x + y + base; };
	SumFunction = lambda_func_with_capture_sum;
	sum = SumFunction(x, y);
	std::cout << "lambda_func_with_capture_sum：" << sum << std::endl;

	// 仿函数
	ImitateAdd imitate;
	SumFunction = imitate;
	sum = SumFunction(x, y);
	std::cout << "imitate func：" << sum << std::endl;

	// 函数指针
	func_pointer = func_sum;
	SumFunction = func_pointer;
	sum = SumFunction(x, y);
	std::cout << "function pointer：" << sum << std::endl;

	Func = std::bind(&print_func, 1, 2, 3);
	Func(4, 5, 6); // 输出： 1 2 3

	Func = std::bind(&print_func, std::placeholders::_2, std::placeholders::_1, 3);
	Func(1, 2, 7); // 输出： 2 1 3

	int n = 10;
	Func = std::bind(&print_func, std::placeholders::_1, std::placeholders::_1, n);
	Func(5, 6, 7); // 输出： 5 5 10

	getchar();
	return 0;
}