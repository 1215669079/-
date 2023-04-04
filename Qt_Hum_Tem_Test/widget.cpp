#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
     connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

     //数据库
     db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("Humiture.db");
     bool flag = db.open();

     if(flag){
     query = new QSqlQuery();
     //                        日常温湿度  湿度  温度 时间  是否异常
     query->exec("create table NorHumture(Hum,Temp,Time,AbnOrNot)");

     }
     else{
         qDebug() << "打开数据库失败";
     }
     qmodel = new QSqlQueryModel(this);

     model = new QSqlTableModel(this);

     model->setHeaderData(0, Qt::Horizontal, tr("湿度"));
     model->setHeaderData(1, Qt::Horizontal, tr("温度"));
     model->setHeaderData(2, Qt::Horizontal, tr("时间"));
     model->setHeaderData(3, Qt::Horizontal, tr("是否异常"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::acceptConnection()
{
    tcpSocket=tcpServer.nextPendingConnection ();
    if(!tcpSocket->isValid()) return;
    ui->lblConnection->setText (tr("A connection come in"));
    receiveBuf.resize(0);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveData()));
}

//发送数据
void Widget::sendData(){
    QString tmp = ui->sendEdit->text();
    if(tmp == "" || tmp == NULL){
        QMessageBox::warning(this,tr("警告"),tr("发送数据不能为空！"),QMessageBox::Ok);
    }
    else{
        tcpSocket->write(tmp.toUtf8());
        tcpSocket->flush();
        qDebug()<<"发送数据成功！";
        ui->sendEdit->clear();
    }
}

void Widget::receiveData()
{
    QByteArray tmpbuf;
    tmpbuf=tcpSocket->readAll ();

    QDateTime dateTime(QDateTime::currentDateTime());
    QString timeStr = "[" + dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz") + "] ";
    QString strReceiveInfo=QString::fromUtf8 (tmpbuf);

   // ui->txtReceiveInformation->setText(strReceiveInfo);
    ui->txtReceiveInformation->append(timeStr + '\n' + strReceiveInfo + '\n' + '\n');
    analysisData(tmpbuf);
}

void Widget::on_btnListen_clicked()
{
    tcpServer.listen (QHostAddress(tr("192.168.43.148")),12345);
    ui->btnListen->setEnabled(false);
}

void Widget::on_btn_send_clicked()
{
    sendData();
}

//数据库
//解析数据
void Widget::analysisData(QByteArray Data)
{
    QString tmp = QString::fromUtf8(Data);
    QStringList list = tmp.split(",");
    if(!list.isEmpty())
    {
        QString Hum = list.at(0);
        QString Temp = list.at(1);
        qDebug() << "湿度为：" << Hum << " 温度为：" << Temp;
        insertData(Hum,Temp);
    }else qDebug() << tmp;
}

//把解析的数据丢进数据库
void Widget::insertData(QString Hum, QString Temp)
{
    //时间
    QDateTime dateTime(QDateTime::currentDateTime());
    QString timeStr = "[" + dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz") + "] ";

    //是否数据异常
    QString Abn;

    float tempData = Temp.toFloat();
    if(tempData >= AbnTemp)
    {
        Abn = "Yes";
    }
    else Abn = "No";
    //NorHumture(Hum,Temp,Time,AbnOrNot)")
    //                                            湿度        温度          时间       是否异常
    query->exec("insert into NorHumture values('"+Hum+"', '"+Temp+"', '"+timeStr+"','"+Abn+"')");//往数据库插入数据
}

//显示历史记录
void Widget::on_btn_selectSql_clicked()
{
    ui->tableView->clearMask();
    model->setTable("NorHumture");


    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("湿度"));
    model->setHeaderData(1, Qt::Horizontal, tr("温度"));
    model->setHeaderData(2, Qt::Horizontal, tr("时间"));
    model->setHeaderData(3, Qt::Horizontal, tr("是否异常"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
}

void Widget::on_btn_Abnshow_clicked()
{
    model->setFilter(QString("AbnOrNot = Yes"));
    model->select();
    ui->tableView->setModel(model);

}

void Widget::on_btn_delAll_clicked()
{
    model->removeRows(0,model->rowCount());
    model->submitAll();
}
