# MEGAROBO Update升级说明
## 需求
* 各个升级部分格式统一
* 操作方式统一

## 现状
* MRQ系列后缀 .upd
* MRH系列后缀 .mrh
* MRQ升级工具：
  * ![image.png](https://upload-images.jianshu.io/upload_images/3399573-5e02c0a1342e4f82.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
  * ![image.png](https://upload-images.jianshu.io/upload_images/3399573-ed403bc3d37427ca.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
* MRH升级工具
   * ![image.png](https://upload-images.jianshu.io/upload_images/3399573-c1a7ae6a0cf200f8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
  
* 升级文件内容
  
    | 名称 | 内容 | 大小 |
    | -- | -- | -- |
    | GreatShot_1.20_Beta1.mrh | | 6.29 MB |
    |  | ARM|  |
    |  | FPGA|  |
    | Sinanju(SOFT)_00.00.01.33.upd | | 906 KB |
    |  | 背板|  |
    |  | 主板|  |
    |  | 内核|  |
    |  | 设备|  |
    |  | webcontrol|  |
    |  | MCT| ? |

## 集成
* 升级文件组成
   * 映射表
   * entity(实体)
* 实体组成
   * 映射表
   * block(块)
* 块组成
   * 类型：描述，fpga,arm,mcu,kernel...
   * 格式: 原始，压缩
   * 大小
   * 验证
   * 数据
  
![image.png](https://upload-images.jianshu.io/upload_images/3399573-d6d0571b4df8d402.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



