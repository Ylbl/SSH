//
// Created by O on 25-4-6.
//

#include "MyConfig.h"

MyConfig &MyConfig::getInstance() {
    // 静态局部变量在第一次调用时初始化，且只初始化一次
    return myconfig;
}

MyConfig::MyConfig() {
    //文件路径+文件名
    QString fileName = "Config.ini";
    //创建配置目标，输入文件路径，文件格式
    QSettings *setting = new QSettings(fileName, QSettings::IniFormat);
    // 判断文件是否存在
    if (QFile::exists(fileName)) {
        // 文件存在，读出配置项
        // 这里的setting->value的第二参数，是配置项缺省值，即当读取的配置项不存在时，读取该值
        // User是配置组，name和age是配置项
        /*name = setting->value("User/name", "张三").toString();
        age = setting->value("User/age", 30).toInt();*/
        rest_time = setting->value("rest_time", rest_time).toInt();
        object_time = setting->value("object_time", object_time).toInt();
        my_email = setting->value("my_email", my_email).toString();
        to_email = setting->value("to_email", to_email).toString();
        key = setting->value("key", key).toString();
        music_path = setting->value("music_path", music_path).toString();
        models_path = setting->value("models_path", models_path).toString();
        email_type = setting->value("email_type", email_type).toString();
    } else {
        // 文件不存在，写入配置项，生成配置文件
        /*setting->setValue("User/name", "张三");
        setting->setValue("User/age", 30);*/
        setting->setValue("rest_time", rest_time);
        setting->setValue("object_time", object_time);
        setting->setValue("my_email", my_email);
        setting->setValue("to_email", to_email);
        setting->setValue("key", key);
        setting->setValue("music_path", music_path);
        setting->setValue("models_path", models_path);
        setting->setValue("email_type", email_type);
        // setValue只是把配置项写入了缓冲区，若要写入文件，还需执行同步
        // 不同步，无法写入文件，无法生成文件
        setting->sync();
    }
}
