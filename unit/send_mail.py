import smtplib
import threading  # 新增导入线程模块[1,10](@ref)
import time
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

from main import myconfig



def send_mail(subject, body):
    # 保持原有配置和逻辑不变
    qq_email = str(myconfig.get("email_address"))
    qq_password = str(myconfig.get("email_password"))
    to_email = str(myconfig.get("to_email_address"))
    print(qq_email)
    print(qq_password)
    print(to_email)


    msg = MIMEMultipart()
    msg['From'] = qq_email
    msg['To'] = to_email
    msg['Subject'] = subject
    msg.attach(MIMEText(body, 'plain'))

    try:
        server = smtplib.SMTP_SSL('smtp.qq.com', 465,timeout=10)  # 替代原587端口
        server.login(qq_email, qq_password)
        server.sendmail(qq_email, to_email, msg.as_string())
        print('Email sent successfully!')
    except Exception as e:
        print(f'Failed to send email: {e}')
    finally:
        pass

def send_message(subject,body):
    mail_thread = threading.Thread(
        target=send_mail,
        args=(subject, body)
    )
    mail_thread.start()

if __name__ == '__main__':
    send_message('1','2')