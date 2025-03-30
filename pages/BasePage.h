#ifndef BasePage_H
#define BasePage_H

#include <ElaScrollPage.h>

class QVBoxLayout;
class BasePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit BasePage(QWidget* parent = nullptr);
    ~BasePage();

protected:
    void createCustomWidget(QString desText);
};

#endif // BasePage_H
