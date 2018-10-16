# IPC_Serial
基于IPC的串口通讯程序

## Build
### GDBUS版本
默认是gdbus版本
```
mkdir build
cd build
cmake ..
make 
```
### QDBUS版本
如果需要编译使用qdbus版本，修CMakeLists.txt文件，设置SYSROOT_DIR为Qt本地路径。接着按如下代码配置即可
```
mkdir build
cd build
cmake ..
ccmake ..
```
修改Dus_mode状态为OFF
```
make 
```

## UML类图叠加分层设计
![image](http://www.fanjiafei.cn/wp-content/uploads/2018/03/Overview-of-Design-Model-of-IPC-2.jpg)
