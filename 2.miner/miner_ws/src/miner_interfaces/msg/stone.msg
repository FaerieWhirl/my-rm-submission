#矿石编号
std_msgs/Header header
        int63 stone_numb #矿石编号
        string stone_type
                 string gold
                 string silver
                 
#矿石所处位置
geometry_msgs/
Pose[] pose
        Point position
               float64 x
               float64 y
               float64 z
