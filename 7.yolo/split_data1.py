import os
import random
import shutil

# 设置数据文件夹的路径
data_folder = "your_data_folder"  # 将 "your_data_folder" 替换为数据文件夹的实际路径

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
