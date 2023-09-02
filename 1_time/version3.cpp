#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <chrono>
#include <thread>

float sumFun(std::vector<float>& data) {
    float sum = 0;
    for (float num : data) {
        sum += num;
    }
    return sum;
}

float avgFun(std::vector<float>& data) {
    float sum = sumFun(data);
    return sum / data.size();
}

float varFun(std::vector<float>& data) {
    float average = avgFun(data);
    float variance = 0;
    for (float num : data) {
        variance += (num - average) * (num - average);
    }
    return variance / data.size();
}

float mulFun(std::vector<float>& data) {
    float result = 1;
    for (float num : data) {
        result *= num;
    }
    return result;
}

void createTimerLoop(std::vector<std::function<float(std::vector<float>&)>>& functions) {
    std::vector<float> data(100);
    for (int i = 0; i < 100; i++) {
        data[i] = static_cast<float>(rand() % 10 + 1);  // Generate random numbers between 1 and 10
    }

    std::vector<std::string> functionNames = {"sumFun", "avgFun", "varFun", "mulFun"};

    while (true) {
        for (int i = 0; i < functions.size(); i++) {
            float result = functions[i](data);
            std::cout << functionNames[i] << " : " << result << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Sleep for 1 second
    }
}

int main() {
    std::vector<std::function<float(std::vector<float>&)>> functions = {sumFun, avgFun, varFun, mulFun};
    createTimerLoop(functions);
    return 0;
}
