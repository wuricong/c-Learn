#include <iostream>
#include <windows.h>


int testInput(){
    int number;
    std::cout << "请输入：";
    std::cin >> number;
    return number;
}

int main() {
    // 设置控制台输出为 UTF-8
    SetConsoleOutputCP(65001);

    int result = testInput();
    std::cout << "你输入的是: " << result << std::endl;
    return 0;
}