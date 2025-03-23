# 欢迎使用 SSH(Student Studying Helper)

[SSH](https://github.com/Ylbl/SSH)，是一个基于 `Mediapipe` 和 `PyQt` 的视觉辅助学习监督软件.支持根据手部存在性判断学习行为;远程通知;错题本等功能,外设仅需一个摄像头,可以调用手机摄像头,如果没有专门配备的话

---

## 如何使用
- 离线包 视频教程 文字教程均在上传作品的 "LOOK ME"文件夹内,github不能上传大文件所以克隆的文件里没有
- 所有功能的使用将在附件的视频中演示.如果要使用手机摄像头代替usb摄像头,请在提交文件中找到双端对应的程序并安装.具体请查看文字教程

---

## 如何部署

### 安装环境

- 在线安装anaconda
  
  ```cmd
  https://www.anaconda.com/download
  ```
- 使用此连接直接下载
  
  ```cmd
  https://repo.anaconda.com/archive/Anaconda3-2024.10-1-Windows-x86_64.exe
  ```
  
  或使用库里提供的离线包
- 安装后在侧边栏找到 `Anaconda Prompt`
  打开并输入
  
  ```cmd
  conda create -n qt python=3.9
  ```
  
  来创建一个名为qt的带有python3.9的环境
- 创建完成后输入

```cmd
conda activate qt
```

来激活环境

- 输入pip install -r (留空,将会自动补全的路径,-r 后有空格)
  将项目中的requirements.txt拖入命令行窗口
  现在它应该形如这样
  
  ```cmd
  pip install -r F:\qt_test\SSH\requirements.txt
  ```
  
  ---

### 执行程序

- 回车执行后,在项目中找到init.bat并执行,它将完成初次使用所需配置
- 最后一步,在项目窗口打开命令行,分别输入
  
  ```cmd
  conda activate qt
  
  python main.py
  ```

来启动项目
初次使用应配置邮箱秘钥,详情看演示视频

---

## 如何卸载

- 双击执行uninstall.bat即可

## 开源地址

[Mediapipe](https://chuoling.github.io/mediapipe/)
[Qt for Python](https://doc.qt.io/qtforpython-6/)

## 写在后面

此项目十分不完美,因为工时只有4天,很多功能并没有实现,技术栈也是新的,所以很多地方并不规范.造成阅读或理解这臃肿的源码而感到困惑的,十分抱歉

谨以此作,献给第一次参赛的自己
