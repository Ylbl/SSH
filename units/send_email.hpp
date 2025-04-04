#pragma once

#include <QtCore>
#include "SmtpMime"


int send_email(QString _sender, QString _to,QString _subject,QString _text,QString _smtp="smtp.qq.com")
{
    MimeMessage message;

    EmailAddress sender(_sender, "SSH");
    message.setSender(sender);

    EmailAddress to(_to, " ");
    message.addRecipient(to);

    message.setSubject(_subject);

    // Now add some text to the email.
    // First we create a MimeText object.

    MimeText text;

    text.setText(_text);

    // Now add it to the mail

    message.addPart(&text);

    // Now we can send the mail
    SmtpClient smtp(_smtp, 465, SmtpClient::SslConnection);

    smtp.connectToHost();
    if (!smtp.waitForReadyConnected()) {
        qDebug() << "Failed to connect to host!";
        return -1;
    }

    smtp.login("1278309552@qq.com", "ytgdxyosqhnajhih");
    if (!smtp.waitForAuthenticated()) {
        qDebug() << "Failed to login!";
        return -2;
    }

    smtp.sendMail(message);
    if (!smtp.waitForMailSent()) {
        qDebug() << "Failed to send mail!";
        return -3;
    }

    smtp.quit();
}

int send_email()
{
    MimeMessage message;

    EmailAddress sender("1278309552@qq.com", "Your Name");
    message.setSender(sender);

    EmailAddress to("1278309552@qq.com", "Recipient's Name");
    message.addRecipient(to);

    message.setSubject("SmtpClient for Qt - Demo");

    // Now add some text to the email.
    // First we create a MimeText object.

    MimeText text;

    text.setText("Hi,\nThis is a simple email message.\n");

    // Now add it to the mail

    message.addPart(&text);

    // Now we can send the mail
    SmtpClient smtp("smtp.qq.com", 465, SmtpClient::SslConnection);

    smtp.connectToHost();
    if (!smtp.waitForReadyConnected()) {
        qDebug() << "Failed to connect to host!";
        return -1;
    }

    smtp.login("1278309552@qq.com", "ytgdxyosqhnajhih");
    if (!smtp.waitForAuthenticated()) {
        qDebug() << "Failed to login!";
        return -2;
    }

    smtp.sendMail(message);
    if (!smtp.waitForMailSent()) {
        qDebug() << "Failed to send mail!";
        return -3;
    }

    smtp.quit();
}