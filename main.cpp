#include <iostream>
#include <iomanip>
#include <utility> // for std::pair

#ifdef _WIN32
#include <windows.h>
#endif

std::pair<double, double> testInput()
{
    double number;
    double num;
    std::cout << "请输入第一个数字：";
    std::cin >> number;
    std::cout << "请输入第二个数字：";
    std::cin >> num;
    return {number, num};
}

int main()
{
    int num;

#ifdef _WIN32
    // 设置控制台输出为 UTF-8
    SetConsoleOutputCP(65001);
#endif

    auto [a, b] = testInput();
    // std::cout << "你输入的是: " << a << "和" << b << std::endl;

    // 检查输入操作是否成功
    if (std::cin.fail())
    {
        std::cerr << "Invalid input!" << std::endl;
    }
    else
    {
        // 打印和，保留 6 位小数（根据需要调整）
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "You entered: " << (a + b) << std::endl;
    }

    if (a > b)
    {
        std::cout << a << "大于" << b;
    }
    else if (a < b)
    {
        std::cout << a << "小于" << b;
    }
    else
    {
        std::cout << a << "等于" << b;
    }
    return 0;
}