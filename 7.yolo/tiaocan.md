# 调参过程记录

## 1 前言

**采用yolov5-face**

- 数据集2000例：自搜集1000余例，并采用群里分享的数据集
- 按照4:1区分为数据集和验证集
- 完成自行环境搭建，在自己的电脑上配置好了Anaconda+cudnn+cuda+Pytorch


## 2 自行编写程序区分验证集和训练集

> 思路:
> 
> part 1
> 
> 将原数据4：1分
> 
> 先获取文件列表，接着计算分割点，利用循环，遍历文件列表循环到分割点，一个个处理
> fda
> part 2
> 
> 在循环过程中，区分.jpg和.txt
> 

```cpp
import os
import random
import shutil

# 设置数据文件夹的路径
data_folder = "/home/data/data_RM"  

# 创建训练集和验证集文件夹
train_folder = os.path.join(data_folder, "train")
val_folder = os.path.join(data_folder, "val")

os.makedirs(train_folder, exist_ok=True)
os.makedirs(val_folder, exist_ok=True)

# 获取数据文件列表
data_files = os.listdir(data_folder)
random.shuffle(data_files)

# 计算训练集和验证集的切分点
split_point = int(0.8 * len(data_files))

# 将文件移动到训练集和验证集文件夹中
for i, file_name in enumerate(data_files):
    src_path = os.path.join(data_folder, file_name)
    if i < split_point:
        if file_name.endswith(".jpg"):
            dst_path = os.path.join(train_folder, "tra", file_name)
        elif file_name.endswith(".txt"):
            dst_path = os.path.join(train_folder, "val", file_name)
        else:
            continue
    else:
        if file_name.endswith(".jpg"):
            dst_path = os.path.join(val_folder, "tra", file_name)
        elif file_name.endswith(".txt"):
            dst_path = os.path.join(val_folder, "val", file_name)
        else:
            continue

    os.makedirs(os.path.dirname(dst_path), exist_ok=True)
    shutil.move(src_path, dst_path)

print("数据分割完成。")
```


## 3 肝模型训练部分

因为模型只train，没有test，所以2000组数据都用来train

```cpp
# coco128.yaml 
#13行
train: home/yolov5-face/data/images/train/

#14行
val: home/yolov5-face/data/images/val/

#17行
nc: 6

#20
names: [ 'blue_r', 'blue_hitted', 'blue_not_hitted', 'red_r', 'red_hitted', 'red_not_hitted']

#---------------------------------------------------------------------------------------------------------------------

#train.py

#435行
parser.add_argument('--data', type=str, default='data/coco128.yaml', help='data.yaml path')

#437
parser.add_argument('--epochs', type=int, default=200)


#---------------------------------------------------------------------------------------------------------------
yolov5s.yaml
#2
nc: 6 # number of classes

```

开始运行时，一直缺模块，pip了很多次


![图片.png](https://p9-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/273b438ace7b4ece8cea8b030cabab15~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1758&h=802&e=png&b=181818)


![图片.png](https://p9-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/912fbb07b6094f93a57f4f9fe96e1fb0~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=2188&h=441&e=png&b=181818)


> 最后开始训练，报错，按照报错修改了np.int，还是有问题，见同文件两张图