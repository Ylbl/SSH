import time

import cv2

import mediapipe as mp
from PIL.ImageQt import QImage, QPixmap

import main
from main import myconfig

from unit.send_mail import send_mail, send_message

cap=cv2.VideoCapture(0)

mpHands=mp.solutions.hands
hands=mpHands.Hands()

mpDraw=mp.solutions.drawing_utils



import threading
import queue

# 创建线程安全队列（最大容量3条消息）
msg_queue = queue.Queue(maxsize=3)
msg_queue1 = queue.Queue(maxsize=3)

handCount=0


def read(args):
    global handCount,is_t_hand_away_runnning,waiting_time,now_waiting_time

    while args.running:
        ret,img=cap.read()
        if ret:
            imgRGB=cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
            result=hands.process(imgRGB)

            if result.multi_hand_landmarks:
                handCount=len(result.multi_hand_landmarks)
                for handLms in result.multi_hand_landmarks:
                    mpDraw.draw_landmarks(img,handLms)
            else:
                handCount=0

            label = args.video
            ih, iw, _ = img.shape
            # 获取标签的长和高
            w = label.geometry().width()
            h = label.geometry().height()
            # 上述的目的是为了保持原始的纵横比
            if iw / w > ih / h:
                scal = w / iw
                nw = w
                nh = int(scal * ih)
                im_new = cv2.resize(img, (nw, nh))
            else:
                scal = w / iw
                nw = int(scal * iw)
                nh = h
                im_new = cv2.resize(img, (nw, nh))
            frame = cv2.cvtColor(im_new, cv2.COLOR_BGR2RGB)
            frame=cv2.flip(frame,-1)

            cv2.putText(frame, 'hand_count: '+str(handCount), (5, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (0, 0, 255), 1)
            cv2.putText(frame, 'water_time: ' + str(args.now_water_time), (5, 50), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (0, 0, 255), 1)
            if handCount <2:
                cv2.putText(frame, 'Please make sure both hands', (300, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255, 0, 0), 1)
                cv2.putText(frame, 'rest_time: ' + str(now_waiting_time), (300, 50), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255, 0, 0),1)
            else:
                now_waiting_time=waiting_time

            msg_queue.put(frame)  # 阻塞直到有空位


def read1(args):
    while args.running:
        ret, img = cap.read()

        label = args.video
        ih, iw, _ = img.shape
        # 获取标签的长和高
        w = label.geometry().width()
        h = label.geometry().height()
        # 上述的目的是为了保持原始的纵横比
        if iw / w > ih / h:
            scal = w / iw
            nw = w
            nh = int(scal * ih)
            im_new = cv2.resize(img, (nw, nh))
        else:
            scal = w / iw
            nw = int(scal * iw)
            nh = h
            im_new = cv2.resize(img, (nw, nh))
        frame = cv2.cvtColor(im_new, cv2.COLOR_BGR2RGB)
        frame=cv2.flip(frame,-1)
        msg_queue1.put(frame)  # 阻塞直到有空位


def get(args):
    while args.running:
        try:
            message = msg_queue.get(timeout=1)  # 阻塞最多1秒

            im = QImage(message.data, message.shape[1], message.shape[0], message.shape[2] * message.shape[1],
                        QImage.Format.Format_RGB888)

            args.video.setPixmap(QPixmap.fromImage(im))
        except Exception as e:
            print(repr(e))

            msg_queue.task_done()  # 标记任务完成
        except queue.Empty:
            continue



def get1(args):
    while args.running:
        try:
            message = msg_queue1.get(timeout=1)  # 阻塞最多1秒

            im = QImage(message.data, message.shape[1], message.shape[0], message.shape[2] * message.shape[1],
                        QImage.Format.Format_RGB888)

            args.video.setPixmap(QPixmap.fromImage(im))
        except Exception as e:
            print(repr(e))

            #msg_queue1.task_done()  # 标记任务完成
        except queue.Empty:
            continue


is_t_hand_away_runnning=False


waiting_time=int(myconfig.get("waiting_time"))
now_waiting_time=waiting_time


def hand_away(args):
    if not args.running:
        return
    if handCount==2:
       return
    global now_waiting_time,waiting_time,is_t_hand_away_runnning
    while now_waiting_time>0:
        if not args.running:
            return
        now_waiting_time-=1
        time.sleep(1)
        if now_waiting_time==0:
            args.show_timeout_signal.emit()
            send_message('超时','被监护人双手离开时长以超过设定值')
            is_t_hand_away_runnning=False
            now_waiting_time=waiting_time
