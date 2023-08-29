#include <iostream>
#include <vector>
#include <random>
#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Eigen;

class KalmanFilter {
public:
    KalmanFilter() {
        state_ = VectorXd(2);
        state_ << 0, 0;

        A_ = MatrixXd(2, 2);
        A_ << 1, 1,
              0, 1;

        B_ = VectorXd(2);
        B_ << 0, 0;

        H_ = MatrixXd(1, 2);
        H_ << 1, 0;

        // 增加过程噪声协方差矩阵Q
        Q_ = MatrixXd(2, 2);
        Q_ << 0.1, 0,
              0, 0.1;

        // 减小测量噪声协方差矩阵R
        R_ = MatrixXd(1, 1);
        R_ << 0.01;
    }

    void Update(double measurement) {
        state_ = A_ * state_ + B_;
        MatrixXd P = A_ * P_ * A_.transpose() + Q_;

        MatrixXd K = P * H_.transpose() * (H_ * P * H_.transpose() + R_).inverse();
        VectorXd measurement_vector(1);
        measurement_vector << measurement;
        state_ = state_ + K * (measurement_vector - H_ * state_);
        P_ = (MatrixXd::Identity(2, 2) - K * H_) * P;
    }

    double GetState() {
        return state_(0);
    }

private:
    VectorXd state_;
    MatrixXd A_;
    VectorXd B_;
    MatrixXd H_;
    MatrixXd Q_;
    MatrixXd R_;
    MatrixXd P_ = MatrixXd::Identity(2, 2);
};

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> noise(0.01, 0.1);

    vector<double> true_data;
    for (int i = 0; i < 200; ++i) {
        true_data.push_back(i * 0.1);
    }

    vector<double> noisy_data;
    for (const auto& value : true_data) {
        double n = noise(gen);
        noisy_data.push_back(value + n);
    }

    KalmanFilter kf;

    vector<double> filtered_data;
    for (const auto& measurement : noisy_data) {
        kf.Update(measurement);
        filtered_data.push_back(kf.GetState());
    }

    cv::Mat plot(400, 600, CV_8UC3, cv::Scalar(255, 255, 255));

    for (int i = 0; i < 199; ++i) {
        cv::Point p1(i * 3, 400 - true_data[i] * 10);
        cv::Point p2((i + 1) * 3, 400 - true_data[i + 1] * 10);
        cv::line(plot, p1, p2, cv::Scalar(0, 0, 255), 2);

        cv::Point p3(i * 3, 400 - noisy_data[i] * 10);
        cv::Point p4((i + 1) * 3, 400 - noisy_data[i + 1] * 10);
        cv::line(plot, p3, p4, cv::Scalar(0, 255, 0), 1);

        cv::Point p5(i * 3, 400 - filtered_data[i] * 10);
        cv::Point p6((i + 1) * 3, 400 - filtered_data[i + 1] * 10);
        cv::line(plot, p5, p6, cv::Scalar(255, 0, 0), 2);
    }

    cv::imshow("Kalman Filter", plot);
    cv::waitKey(0);

    return 0;
}
