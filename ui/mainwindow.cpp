#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "teamproject.h"

QProcess process;

Room room();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->enterBtn, SIGNAL(clicked(bool)), this, SLOT(whenEnterClicked()));
    connect(ui->leaveBtn, SIGNAL(clicked(bool)), this, SLOT(whenLeaveClicked()));
    connect(ui->okBtn, SIGNAL(clicked(bool)), this, SLOT(whenOkClicked()));
    connect(ui->tempEdit_2, SIGNAL(textChanged()), this, SLOT(checkStatus(ui->tempEdit_2->text())));
    msg = new QProcess(this);
    QObject::connect(msg, SIGNAL(rfidOutput()), this, SLOT(printRFID));
}

void MainWindow::checkStatus(QString temp){
    int temparture = temp.toFloat();
    if(temparture>=37.5){
        ui->statusEdit_2->setText("WARN! HIGH TEMPARTURE");
    }
    else if(temparture<30){
        ui->statusEdit_2->setText("TOO LOW");
    }
    else{
        ui->statusEdit_2->setText("NORMAL");
    }

}

void MainWindow::displayInfo(QString id, QString name, QString in, QString out = ""){
    ui->idEdit_2->setText(id);
    ui->nameEdit_2->setText(name);
    ui->inEdit_2->setText(in);
    ui->outEdit_2->setText(out);
}

void MainWindow::printRFID(){
    QByteArray data;
    data = msg ->readAllStandardOutput();
}

void MainWindow::whenEnterClicked(){
    //process.start("sh", QStringList() << "-c" << "cin <<");
    //process.waitForFinished();
    //rfid = data (get data from RFID)
    //id, name, in, out = room.in(rfid);
    //displayInfo(id, name, in, out);
}

void MainWindow::whenLeaveClicked(){
    //process.start("sh", QStringList() << "-c" << "cin <<");
    //process.waitForFinished();
    //rfid = data (get RFID)
    //room.out(rfid);
}


void MainWindow::whenRegiClicked(){
    //RegisterDialog regiDialog;
    //regiDialog.setModal(true);
    //regiDialog.exec();
}


void MainWindow::whenOkClicked(){
    QString roomnum;
    roomnum = (ui->roomEdit->text());
    int num = roomnum.toInt();
    //Room room(num);
    roomnum = QString("Classroom %1").arg(roomnum);
    ui->classLabel->setText(roomnum);
    ui->okBtn->close();
    ui->roomEdit->close();
    ui->label->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
