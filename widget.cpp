#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList tableHeader;
    tableHeader << "Original Address" << "Calculated Address" << "Description";
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    ui->tableWidget->setColumnWidth(0, 200);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->teBaseAddress->setText("0x100000000");

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pbtAdd_clicked()
{
    int index = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(index);
    ui->tableWidget->setItem(index, OrignalAddress , new QTableWidgetItem("OrignalAddress"));
    ui->tableWidget->setItem(index, CalcAddress , new QTableWidgetItem("BaseAddress + OrignalAddress"));
    ui->tableWidget->setItem(index, Description , new QTableWidgetItem("설명을 적어주세요."));
}



void Widget::on_pbtDel_clicked()
{
    QModelIndexList indexes = ui->tableWidget->selectionModel()->selectedRows();

    for(int i = indexes.count()-1; i>=0; i--)
    {
        ui->tableWidget->removeRow(indexes.at(i).row());
    }
}


void Widget::on_pbtAddressCalc_clicked()
{
    calcAddressValues();
}

void Widget::calcAddressValues()
{
    int rowCount = ui->tableWidget->rowCount();

    QRegularExpression hexMatcher("^0x[0-9A-Fa-f]+$", QRegularExpression::CaseInsensitiveOption);

    QString baseAddressValueStr = ui->teBaseAddress->toPlainText();
    QRegularExpressionMatch BaseAddressmatch = hexMatcher.match(baseAddressValueStr);
    if(!BaseAddressmatch.hasMatch())
    {
        return;
    }

    for(int i=0; i<rowCount; i++)
    {
        QString OrignalAddressValueStr = ui->tableWidget->item(i, OrignalAddress)->text();
        if(!OrignalAddressValueStr.compare(""))
        {
            continue;
        }

        if(!OrignalAddressValueStr.startsWith("0x"))
        {
            OrignalAddressValueStr.push_front("0x");
        }
        if(!baseAddressValueStr.startsWith("0x"))
        {
            baseAddressValueStr.push_front("0x");
        }
        QRegularExpressionMatch OrignalValuematch = hexMatcher.match(OrignalAddressValueStr);

        if(!OrignalValuematch.hasMatch())
        {
            ui->tableWidget->setItem(i, CalcAddress, new QTableWidgetItem("Check Orignal Address", 16));
            continue;
        }

        bool ok;
        unsigned long long OrignalAddressValue = OrignalAddressValueStr.toULongLong(&ok, 16);
        unsigned long long  bassAddressValue = baseAddressValueStr.toULongLong(&ok, 16);
        unsigned long long  calcAdressValue = OrignalAddressValue + bassAddressValue;
        QString calcAddressValueStr = QString::number(calcAdressValue, 16);
        calcAddressValueStr.push_front("0x");
        ui->tableWidget->setItem(i, CalcAddress, new QTableWidgetItem(calcAddressValueStr, 16));
        ui->tableWidget->setItem(i, OrignalAddress, new QTableWidgetItem(OrignalAddressValueStr, 16));
        ui->teBaseAddress->setText(baseAddressValueStr);
    }

}

