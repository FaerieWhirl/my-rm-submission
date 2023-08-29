#include <iostream>
#include <vector>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>

// 四种操作函数
float calculateSum(std::vector<float>& data) {
    float sum = 0;
    for (float value : data) {
        sum += value;
    }
    return sum;
}

float calculateAverage(std::vector<float>& data) {
    float sum = calculateSum(data);
    return sum / data.size();
}

float calculateVariance(std::vector<float>& data) {
    float mean = calculateAverage(data);
    float variance = 0;
    for (float value : data) {
        variance += (value - mean) * (value - mean);
    }
    return variance / data.size();
}

float calculateProduct(std::vector<float>& data) {
    float product = 1;
    for (float value : data) {
        product *= value;
    }
    return product;
}

// 定时器函数
float createTimerLoop(int period, std::vector<float>& data, std::vector<std::function<float(std::vector<float>&)>>& operations) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    while (true) {
        // 随机选择一个操作
        int randomOperationIndex = std::rand() % operations.size();
        std::function<float(std::vector<float>&)> operation = operations[randomOperationIndex];

        // 执行操作并记录时间
        auto startTime = std::chrono::high_resolution_clock::now();
        float result = operation(data);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        // 打印操作结果和执行时间
        std::cout << "Operation #" << randomOperationIndex + 1 << " Result: " << result << " (Took " << duration << "ms)" << std::endl;

        // 等待指定的定时周期
        std::this_thread::sleep_for(std::chrono::milliseconds(period));
    }
}

int main() {
    // 初始化数据向量
    std::vector<float> data;
    for (int i = 0; i < 100; ++i) {
        data.push_back(static_cast<float>(std::rand()) / RAND_MAX);
    }

    // 初始化操作函数向量
    std::vector<std::function<float(std::vector<float>&)>> operations = {
        calculateSum,
        calculateAverage,
        calculateVariance,
        calculateProduct
    };

    // 启动定时器循环
    createTimerLoop(500, data, operations);

    return 0;
}
