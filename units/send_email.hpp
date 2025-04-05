# ifndef  SEND_EMAIL_HPP
#define SEND_EMAIL_HPP

#include <iostream>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>

using mailio::message;
using mailio::mail_address;
using mailio::smtps;
using mailio::smtp_error;
using mailio::dialog_error;
using std::cout;
using std::endl;

#include "MyConfig.h"

int send_email(QString _subject,QString _content)
{
    try
    {
        // create mail message
        message msg;
        //qDebug()<<MyConfig::getInstance().my_email.toStdString();
        msg.from(mail_address("SSH", MyConfig::getInstance().my_email.toStdString()));// set the correct sender name and address
        msg.add_recipient(mail_address("SSH", MyConfig::getInstance().to_email.toStdString()));// set the correct recipent name and address
        msg.subject(_subject.toStdString());
        msg.content(_content.toStdString());

        // connect to server
        smtps conn(MyConfig::getInstance().email_type.toStdString(), 587);
        // modify username/password to use real credentials
        conn.authenticate(MyConfig::getInstance().my_email.toStdString(), MyConfig::getInstance().key.toStdString(), smtps::auth_method_t::START_TLS);
        conn.submit(msg);
    }
    catch (smtp_error& exc)
    {
        cout << exc.what() << endl;
    }
    catch (dialog_error& exc)
    {
        cout << exc.what() << endl;
    }

    return EXIT_SUCCESS;
}
#endif
