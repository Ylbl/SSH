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


int send_email(std::string _sender, std::string _to,std::string _subject,std::string _text,std::string _smtp="smtp.qq.com")
{
    try
    {
        // create mail message
        message msg;
        msg.from(mail_address("SSH", _sender));// set the correct sender name and address
        msg.add_recipient(mail_address("SSH", _to));// set the correct recipent name and address
        msg.subject(_subject);
        msg.content(_text);

        // connect to server
        smtps conn(_smtp, 587);
        // modify username/password to use real credentials
        conn.authenticate("1278309552@qq.com", "ytgdxyosqhnajhih", smtps::auth_method_t::START_TLS);
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

int send_email()
{
    try
    {
        // create mail message
        message msg;
        msg.from(mail_address("SSH", "1278309552@qq.com"));// set the correct sender name and address
        msg.add_recipient(mail_address("SSH", "1278309552@qq.com"));// set the correct recipent name and address
        msg.subject("tip");
        msg.content("Hello, World!");

        // connect to server
        smtps conn("smtp.qq.com", 587);
        // modify username/password to use real credentials
        conn.authenticate("1278309552@qq.com", "ytgdxyosqhnajhih", smtps::auth_method_t::START_TLS);
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
