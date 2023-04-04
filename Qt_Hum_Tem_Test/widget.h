#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

#include <QByteArray>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QStringList>

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelation>
#include <QSqlQuery>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void sendData();//发送数据
    void analysisData(QByteArray Data);//解析数据
    void insertData(QString Hum,QString Temp);//往数据库添加数据

private slots:
    void on_btnListen_clicked();
    void acceptConnection();
    void receiveData();

    void on_btn_send_clicked();

    void on_btn_selectSql_clicked();

    void on_btn_Abnshow_clicked();

    void on_btn_delAll_clicked();

private:
    Ui::Widget *ui;
    QTcpServer tcpServer;
    QTcpSocket *tcpSocket;
    QByteArray receiveBuf;

    QSqlQuery *query;
    QSqlDatabase db;
    QSqlQueryModel *qmodel;
    QModelIndex modelIndex;
    QSqlTableModel *model;

    float AbnTemp = 32.0;
};
#endif // WIDGET_H
