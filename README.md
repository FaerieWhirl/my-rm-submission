# my-rm-submission
因为最近个人时间安排过于紧凑问题，题目完成时间极其紧张，在有限的时间里已经尽最大时间安排完成了部分题目

剩余未完成部分以及不完善的部分，本着学知识的目的，会尽快做完更新

## 1 time
> 此题有一点不太明白
> 有一处函数的调用，在windows上运行会报错，报错提示sleep_for前应该加上命名空间，在linux上可以正确运行
>


        ```cpp
        // 等待指定的定时周期
        std::this_thread::sleep_for(std::chrono::milliseconds(period));
        ```

## 4. opencv 

在低曝光输入视频中检测还较为合理，但在标准曝光视频中，会给其他物体标上矩形框

## yolov5-face
该部分调参过程见yolo文件里的md
