# check_hu
# 描述：mahjong判胡算法（带癞子和不带癞子都适用)， 使用语言：golang

# algorithm采用查表法判胡,algorithm2是采用拆分法判胡
# main.go文件用于性能测试文件，线上环境可以去掉main-test.go这个测试文件
# 性能：linux上实测运行main-test.go, 测试40万数据，用时8-10秒