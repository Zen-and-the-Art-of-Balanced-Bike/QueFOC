![](https://picss.sunbangyan.cn/2023/10/20/d1a2fba430c6ce085f878d808f4de35e.png)

# QueFOC 无刷方案

- FOC有感无刷方案
- 已打板验证
- 已实现电流环、速度环
- 采用PLL算法观测速度
- 有完整的终端命令调试系统
- 提供完整的PCB工程文件（KICAD）

![功率板](https://files.catbox.moe/oh9nwy.png)
![控制板](https://files.catbox.moe/5zdesl.png)
![测试](https://files.catbox.moe/clrkut.PNG)

## 文件目录介绍

```
PCB/ # 存放PCB KiCAD工程文件
  QueCtrl/ # 控制板的PCB工程文件
  QueDriverS/ # 功率板的PCB工程文件

QueFOC_dev/ # 电机控制程序

QueFOC_CH32V307/ # CH33V307单片机的工程目录
```

## 性能介绍

### 综合
使用此系统配合控制算法已实现K/N车平衡

### 快速响应
使用逐飞的N车黑色无刷电机测试，280ms从0 turn/s达到50 turn/s
![](https://files.catbox.moe/00hey0.png)

### 瞬间反转
![](https://files.catbox.moe/bvumej.png)

## 移植说明

控制程序均采用函数指针加载，软硬完全解耦，移植仅需将`QueFOC_CH32V307`目录下的各函数按照单片机平台特性重新实现即可



