#include <iostream>
#include <vector>
#include <random>
#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Eigen;

// 定义卡尔曼滤波器类
class KalmanFilter {
public:
    KalmanFilter() {
        // 初始化卡尔曼滤波器参数
        state_ = VectorXd(2);
        state_ << 0, 0;

        // 状态转移矩阵A
        A_ = MatrixXd(2, 2);
        A_ << 1, 1,
              0, 1;

        // 控制输入矩阵B
        B_ = VectorXd(2);
        B_ << 0, 0;

        // 测量矩阵H
        H_ = MatrixXd(1, 2);
        H_ << 1, 0;

        // 过程噪声协方差矩阵Q
        Q_ = MatrixXd(2, 2);
        Q_ << 0.01, 0,
              0, 0.01;

        // 测量噪声协方差矩阵R
        R_ = MatrixXd(1, 1);
        R_ << 0.1;
    }

    // 更新状态
    void Update(double measurement) {
        // 预测步骤
        state_ = A_ * state_ + B_;
        MatrixXd P = A_ * P_ * A_.transpose() + Q_;

        // 计算卡尔曼增益K
        MatrixXd K = P * H_.transpose() * (H_ * P * H_.transpose() + R_).inverse();
        
        // 创建测量向量
        VectorXd measurement_vector(1);
        measurement_vector << measurement;
        
        // 更新状态估计
        state_ = state_ + K * (measurement_vector - H_ * state_);
        
        // 更新状态协方差矩阵
        P_ = (MatrixXd::Identity(2, 2) - K * H_) * P;
    }

    // 获取当前状态
    double GetState() {
        return state_(0);
    }

private:
    VectorXd state_; // 状态向量
    MatrixXd A_;     // 状态转移矩阵
    VectorXd B_;     // 控制输入矩阵
    MatrixXd H_;     // 测量矩阵
    MatrixXd Q_;     // 过程噪声协方差矩阵
    MatrixXd R_;     // 测量噪声协方差矩阵
    MatrixXd P_ = MatrixXd::Identity(2, 2); // 状态协方差矩阵
};

int main() {
    // 随机数生成器
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> noise(0.01, 0.1); // 噪声范围

    // 生成真值数据
    vector<double> true_data;
    for (int i = 0; i < 200; ++i) {
        true_data.push_back(i * 0.1); // 真值为线性增加的数据
    }

    // 添加噪声
    vector<double> noisy_data;
    for (const auto& value : true_data) {
        double n = noise(gen);
        noisy_data.push_back(value + n);
    }

    // 初始化卡尔曼滤波器
    KalmanFilter kf;

    // 用卡尔曼滤波器滤波
    vector<double> filtered_data;
    for (const auto& measurement : noisy_data) {
        kf.Update(measurement);
        filtered_data.push_back(kf.GetState());
    }

    // 绘制图表
    cv::Mat plot(400, 600, CV_8UC3, cv::Scalar(255, 255, 255));

    for (int i = 0; i < 199; ++i) {
        cv::Point p1(i * 3, 400 - true_data[i] * 10);
        cv::Point p2((i + 1) * 3, 400 - true_data[i + 1] * 10);
        cv::line(plot, p1, p2, cv::Scalar(0, 0, 255), 2); // 绘制真值

        cv::Point p3(i * 3, 400 - noisy_data[i] * 10);
        cv::Point p4((i + 1) * 3, 400 - noisy_data[i + 1] * 10);
        cv::line(plot, p3, p4, cv::Scalar(0, 255, 0), 1); // 绘制带噪声的测量值

        cv::Point p5(i * 3, 400 - filtered_data[i] * 10);
        cv::Point p6((i + 1) * 3, 400 - filtered_data[i + 1] * 10);
        cv::line(plot, p5, p6, cv::Scalar(255, 0, 0), 2); // 绘制滤波后的值
    }

    cv::imshow("Kalman Filter", plot); // 显示图像
    cv::waitKey(0); // 按键

    return 0;
}
