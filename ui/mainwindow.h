#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void whenEnterClicked();
    void whenLeaveClicked();
    void whenOkClicked();
    void whenRegiClicked();
    void printRFID();
    void displayInfo(QString id, QString name, QString in, QString out);
    void checkStatus(QString temp);

private:
    Ui::MainWindow *ui;
    QProcess *msg;
};
#endif // MAINWINDOW_H
