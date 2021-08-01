#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    int index;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pbtAdd_clicked();

    void on_pbtDel_clicked();

    void on_pbtAddressCalc_clicked();

private:
    Ui::Widget *ui;

    enum Column
    {
        OrignalAddress, CalcAddress, Description
    };

    void calcAddressValues();
};
#endif // WIDGET_H
