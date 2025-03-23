import ctypes
import json
import logging
import os
import shutil
import sys
from pathlib import Path

import winsound
from PyQt6 import QtGui, QtWidgets
from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget
from ui.AddItemWindow import Ui_AddItemWindow
from ui.MainWindow import Ui_MainWindow
from ui.SettingWindow import Ui_SettingWindow
from ui.TimeRunOutWindow import Ui_TimeRunOutWindow
from ui.WQbWindow import Ui_WQbWindow
from unit.image_process import *
from PyQt6.QtCore import pyqtSignal as Signal, QTimer, QObject, Qt, QUrl, pyqtSignal

class SettingWindow(QWidget,Ui_SettingWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.water_time.setText(str(myconfig.get("water_time")))
        self.waiting_time.setText(str(myconfig.get("waiting_time")))
        self.email_address.setText(myconfig.get("email_address"))
        self.email_password.setText(myconfig.get("email_password"))
        self.to_email_address.setText(myconfig.get("to_email_address"))

    def confirmBC(self):
        for obj in self.findChildren(QtWidgets.QLineEdit):
            myconfig._data[obj.objectName()] = obj.text()
        myconfig.save()
        self.close()

class AddItemWindow(QWidget,Ui_AddItemWindow):
    s_add_item_window_closed = Signal()  # 添加信号
    running = True
    args=None
    row=None
    img_lasted=None
    def __init__(self,args=None,row=-1,is_edit=False):
        super().__init__()
        self.setupUi(self)

        self.args=args
        self.row = row
        self.is_edit=is_edit
        self.s_add_item_window_closed.connect(args.onAddItemWindowClosed)

        if is_edit:
            self.pushButton_3.setEnabled(False)
            self.running=False
            self.sourceInput.setText(args.all_json_data[row]['source'])
            self.descriptionInput.setText(args.all_json_data[row]['description'])

            pixmap = QPixmap(args.all_img_path[row])
            scaled_pixmap = pixmap.scaled(
                self.widget.width(),
                self.widget.height(),
                Qt.AspectRatioMode.KeepAspectRatio,
                Qt.TransformationMode.SmoothTransformation
            )
            self.video.setPixmap(scaled_pixmap)

        sender = threading.Thread(target=read1, args=(self,))
        receiver = threading.Thread(target=get1, args=(self,))
        sender.start()
        receiver.start()




    def captureBC(self):
        self.running=False

        ret, resized_img = cap.read()
        resized_img = cv2.flip(resized_img, -1)
        roi = cv2.selectROI('e', resized_img, showCrosshair=False, fromCenter=False)
        xmin, ymin, w, h = roi  # 矩形裁剪区域 (ymin:ymin+h, xmin:xmin+w) 的位置参数

        imgROI = resized_img[ymin:(ymin + h), xmin:(xmin + w)].copy()  # 切片获得裁剪后保留的图像区域

        ih, iw, _ = imgROI.shape
        # 获取标签的长和高
        w = self.video.geometry().width()
        h = self.video.geometry().height()
        # 上述的目的是为了保持原始的纵横比
        if iw / w > ih / h:
            scal = w / iw
            nw = w
            nh = int(scal * ih)
            im_new = cv2.resize(imgROI, (nw, nh))
        else:
            scal = w / iw
            nw = int(scal * iw)
            nh = h
            im_new = cv2.resize(imgROI, (nw, nh))
        self.img_lasted = im_new
        im_new = cv2.cvtColor(im_new, cv2.COLOR_BGR2RGB)



        im = QImage(im_new.data, im_new.shape[1], im_new.shape[0], im_new.shape[2] * im_new.shape[1],
                    QImage.Format.Format_RGB888)

        self.video.setPixmap(QPixmap.fromImage(im))


    def confirmBC(self):
        try:
            if self.is_edit==False:
                timestamp = time.time()

                img_path="C:\\Users\\Public\\Documents\\SSH\\img\\"+str(int(timestamp))+".jpg"

                cv2.imwrite(img_path,self.img_lasted)

                json_path="C:\\Users\\Public\\Documents\\SSH\\img_js\\"+str(int(timestamp))+".json"
                file = open(json_path, "w")

                WQd={}
                WQd['img_path']=img_path
                WQd['date']=int(timestamp)
                WQd['source']=self.sourceInput.text()
                WQd['description']=self.descriptionInput.toPlainText()


                with open(json_path, "w", encoding='utf-8') as f:
                    # json.dump(dict_, f)  # 写为一行
                    json.dump(WQd, f, indent=2, sort_keys=True, ensure_ascii=False)  # 写为多行
            else:
                #json_path = self.args.all_json_data[self.row]['']  "C:\\Users\\Public\\Documents\\SSH\\img_js\\"+str(int(timestamp))+".json"
                json_path = "C:\\Users\\Public\\Documents\\SSH\\img_js\\" + str(int(self.args.all_json_data[self.row]['date'])) + ".json"
                print(json_path)
                file = open(json_path, "w")



                WQd = {}
                WQd['img_path'] = self.args.all_json_data[self.row]['img_path']
                WQd['date'] = int(self.args.all_json_data[self.row]['date'])
                WQd['source'] = self.sourceInput.text()
                WQd['description'] = self.descriptionInput.toPlainText()

                with open(json_path, "w", encoding='utf-8') as f:
                    # json.dump(dict_, f)  # 写为一行
                    json.dump(WQd, f, indent=2, sort_keys=True, ensure_ascii=False)  # 写为多行

        except Exception as e:
            print(f"Error : {str(e)}")

        self.s_add_item_window_closed.emit()
        self.close()

class WQbWindow(QWidget,Ui_WQbWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        # 定义两个容器
        self.all_json_data = []  # 存放所有JSON内容

        self.all_img_path = []  # 存放所有img_path值
        self.all_json_path = []
        self.all_source = []

        self.showList()

    def editBC(self):
        row = self.listWidget.currentRow()
        self.AddItemWindow = AddItemWindow(self,row,True)
        self.AddItemWindow.show()

    def addItemBC(self):
        # 设置初始大小，增加条目，设置标题

        self.AddItemWindow = AddItemWindow(self)
        self.AddItemWindow.show()

    def onAddItemWindowClosed(self):
        self.showList()

    def showList(self):
        self.listWidget.clear()
        self.all_source.clear()
        self.all_json_data.clear()
        self.all_img_path.clear()
        self.all_json_path.clear()
        # 获取当前目录下所有文件
        for filename in os.listdir('C:\\Users\\Public\\Documents\\SSH\\img_js'):
            # 只处理.json文件
            if filename.endswith('.json'):
                # 拼接完整路径
                file_path = os.path.join('C:\\Users\\Public\\Documents\\SSH\\img_js\\', filename)

                try:
                    # 打开并读取文件
                    with open(file_path, 'r') as f:
                        # if not os.path.getsize(file_path) == 0:
                        data = json.load(f)
                        self.all_json_data.append(data)  # 存入第一个容器
                        self.all_json_path.append(file_path)
                        # 提取img_path（如果存在）
                        if 'img_path' in data:
                            self.all_img_path.append(data['img_path'])
                        if 'source' in data:
                            self.all_source.append(data['source'])
                except json.JSONDecodeError:
                    print(f"Invalid JSON: {file_path}")
                    continue
        for source in self.all_source:
            self.listWidget.addItem(source)

    def itemC(self):
        row = self.listWidget.currentRow()
        if row == -1:
            return

        pixmap = QPixmap(self.all_img_path[row])
        scaled_pixmap = pixmap.scaled(
            self.WQ.width(),
            self.WQ.height(),
            Qt.AspectRatioMode.KeepAspectRatio,
            Qt.TransformationMode.SmoothTransformation
        )
        self.WQ.setPixmap(scaled_pixmap)

        self.description.setText(self.all_json_data[row]['description'])


    def deleteBC(self):
        self.WQ.clear()
        self.description.clear()
        row = self.listWidget.currentRow()
        if row==-1:
            return
        item = self.listWidget.item(row)

        self.listWidget.takeItem(row)

        json_path = self.all_json_path[row]
        img_path = self.all_img_path[row]
        print(json_path)
        try:
            if os.path.exists(json_path):
                os.remove(json_path)
                #print(f"Deleted JSON: {json_path}")
            if os.path.exists(img_path):
                os.remove(img_path)
                #print(f"Deleted Image: {img_path}")
        except Exception as e:
            print(f"Error deleting files: {str(e)}")


class TimeRunOutWindow(QWidget,Ui_TimeRunOutWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        # 初始化一个定时器
        self.timer = QTimer()
        self.timer.timeout.connect(self.close_window)

        self.timer.start(5000)
    def close_window(self):
        self.close()

class MainWindow(QMainWindow,Ui_MainWindow):

    show_timeout_signal = Signal()  # 添加信号
    running = False

    def __init__(self):

        super().__init__()

        self.setupUi(self)
        self.WQbWindow = WQbWindow()
        self.TimeRunOutWindow=TimeRunOutWindow()
        self.SettingWindow=SettingWindow()


        self.show_timeout_signal.connect(self.showTimeRunOutWindow)

        self.water_time = int(myconfig.get("water_time"))
        self.now_water_time=self.water_time


    def startBC(self):
        # 创建线程
        sender = threading.Thread(target=read, args=(self,))
        receiver = threading.Thread(target=get, args=(self,))
        t_water_check=threading.Thread(target=self.remind2drinkWater)
        t_hand_away = threading.Thread(target=hand_away, args=(self,))

        if not self.running:
            self.running=True
            # 启动线程
            sender.start()
            receiver.start()
            t_water_check.start()
            t_hand_away.start()
            send_message("提示", "被监护人打开监护")
        else:
            self.running=False
            time.sleep(0.5)
            self.video.clear()
            self.video.setText("等待画面")
            send_message("提示","被监护人关闭监护")

    def WQbBC(self):
        self.WQbWindow.show()

    def dictationBC(self):
        print("d")

    def settingBC(self):
        self.SettingWindow.show()


    def showTimeRunOutWindow(self):
        self.TimeRunOutWindow.show()

    def remind2drinkWater(self):
        while True:
            if self.running==False:
                self.now_water_time=self.water_time
                break
            if self.now_water_time==0:
                winsound.Beep(1000, 500)
                self.now_water_time=self.water_time
            self.now_water_time-=1
            time.sleep(1)

    def closeEvent(self, a0):

        os._exit(0)



class ConfigHelper:

    def __init__(self, filepath: str):
        self._data = {}
        self.filepath = filepath
        self.load()

    def load(self):
        """加载/重载配置文件"""
        try:
            with open(self.filepath, 'r', encoding='utf-8') as f:
                self._data = json.load(f)
        except FileNotFoundError:
            raise Exception(f"配置文件不存在: {self.filepath}")
        except json.JSONDecodeError as e:
            raise Exception(f"JSON解析失败: {str(e)}")

    def get(self, key: str, default=None):
        """获取配置值"""
        return self._data.get(key, default)

    def __getattr__(self, name: str):
        """通过点符号访问配置"""
        if name in self._data:
            return self._data[name]
        raise AttributeError(f"配置项不存在: {name}")

    def save(self):
        """保存配置到文件"""
        try:
            with open(self.filepath, 'w', encoding='utf-8') as f:
                json.dump(self._data, f, indent=2, ensure_ascii=False)
        except Exception as e:
            print(f"保存失败: {str(e)}")

myconfig=ConfigHelper("C:\\Users\\Public\\Documents\\SSH\\config\\config.json")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    mainWindow = MainWindow()

    mainWindow.show()

    app.exec()