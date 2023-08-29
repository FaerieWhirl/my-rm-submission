#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// 定义能量机关检测类
class EnergyGunDetector {
public:
    EnergyGunDetector(const string& videoPath) : videoPath_(videoPath) {
        cap_.open(videoPath_);
        if (!cap_.isOpened()) {
            cerr << "Error: Cannot open video source." << endl;
            exit(-1);
        }
    }

    void RunDetection() {
        while (true) {
            Mat frame;
            cap_ >> frame;

            if (frame.empty()) {
                cerr << "End of video." << endl;
                break;
            }

            // 图像处理
            DetectArmor(frame);

            imshow("Energy Gun Detection", frame);

            if (waitKey(1) == 27) {
                cout << "Esc key is pressed by user. Stopping the video." << endl;
                break;
            }
        }

        cap_.release();
        destroyAllWindows();
    }

private:
    string videoPath_;
    VideoCapture cap_;

    void DetectArmor(Mat& frame) {
        Mat gray, blurred, edged;
        cvtColor(frame, gray, COLOR_BGR2GRAY); // 转为灰度图像
        GaussianBlur(gray, blurred, Size(5, 5), 0); // 高斯模糊
        Canny(blurred, edged, 50, 150); // 边缘检测

        vector<vector<Point>> contours;
        findContours(edged.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for (size_t i = 0; i < contours.size(); i++) {
            double area = contourArea(contours[i]);

            if (area > 1000) { // 根据装甲板面积阈值调节
                RotatedRect rect = minAreaRect(contours[i]);
                Point2f vertices[4];
                rect.points(vertices);

                // 绘制矩形
                for (int j = 0; j < 4; j++) {
                    line(frame, vertices[j], vertices[(j + 1) % 4], Scalar(0, 255, 0), 2);
                }

                // 计算旋转圆心
                Point2f center = rect.center;
                circle(frame, center, 3, Scalar(0, 0, 255), -1);

                // 输出坐标信息
                cout << "Armor Center: (" << center.x << ", " << center.y << ")" << endl;
            }
        }
    }
};

int main() {
    EnergyGunDetector detector("/home/sanja/Documents/shijue/answer/4.opencv/3低曝光红.mp4");
    detector.RunDetection();

    return 0;
}
