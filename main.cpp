#include <iostream>
#include <windows.h>


std::pair<int,int> testInput(){
    int number;
    int num;
    std::cout << "请输入第一个数字：";
    std::cin >> number;
    std::cout << "请输入第二个数字：";
    std::cin >> num;
    return {number, num};
}

int main() {
    // 设置控制台输出为 UTF-8
    SetConsoleOutputCP(65001);

    auto [a, b] = testInput();
    std::cout << "你输入的是: " << a << "和" << b << std::endl;
    return 0;
}