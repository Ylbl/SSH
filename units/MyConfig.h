//
// Created by O on 25-4-6.
//

#ifndef MYCONFIG_H
#define MYCONFIG_H

#include <QtCore/QtCore>

class MyConfig {
public:
    // 静态公有成员函数，返回类的唯一实例
    static MyConfig &getInstance();
    void myset(QString _key,QString _value);
    void mysave();
    int rest_time = 120;
    int object_time = 120;
    QString my_email = "1278309552@qq.com";
    QString to_email = "1278309552@qq.com";
    QString key = "njmbagitzanzfeci";
    QString music_path = "music/Lovely_Picnic.ogg";
    QString models_path = "models";
    QString email_type = "smtp.qq.com";
    QString target_object = "bottle";

private:
    MyConfig();

    // 私有化析构函数

    ~MyConfig() {
    };

    // 禁止拷贝构造函数和赋值运算符
    MyConfig(const MyConfig &) = delete;

    MyConfig &operator=(const MyConfig &) = delete;

    //定义一个静态指针或者引用
    static MyConfig myconfig;

    QSettings *setting;
};


#endif //MYCONFIG_H
