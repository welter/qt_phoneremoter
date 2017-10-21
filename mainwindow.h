#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <jni.h>
#include <jni_md.h>
#include <QtNetwork/qtcpsocket.h>
#include <QThread>
#include <QPoint>
#include <QtNetwork/qtcpserver.h>
//#include <string>
//using namespace std;
namespace Ui {
class MainWindow;
}
class QMouseEvent;
class SendMessage:public QThread
{
    Q_OBJECT
public:
    SendMessage(char *host,quint16 port,char *msg);
    void run();
private slots:
    void onTcpConnected();
    void onTcpDisConnected();
private:
    QTcpSocket *tcpsocket;
    char *message;
    char *Host;
    quint16 Port;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    static JNIEnv *env;
    static JavaVM *jvm;
    static jclass cls_screenshot;
    static jclass cls_rawimage;
    //ramimage protery
    static jfieldID f_bpp;
    static jfieldID f_data;
    static jfieldID f_red_l;
    static jfieldID f_blue_l;
    static jfieldID f_green_l;
    static jfieldID f_red_o;
    static jfieldID f_blue_o;
    static jfieldID f_green_o;
    static jfieldID f_alpha_l;
    static jfieldID f_alpha_o;
    static jfieldID f_height;
    static jfieldID f_width;

    static jobject obj;
    //mothed of getscreen;
    static jmethodID J_getScreen;


    ~MainWindow();

public slots:
    bool eventFilter(QObject *, QEvent *);

private slots:
    void on_pushButton_clicked();
    void tcpconnected();

    void on_backButton_clicked();

    void on_homeButton_clicked();

    void on_menuButton_clicked();

    void on_VOLDownButton_clicked();

    void on_VOLUPButton_clicked();

    void on_serverconnected();

    void readmessage();

private:
    Ui::MainWindow *ui;
    int m_nTimerId;
    int windowwidth,windowheight;
    QTcpSocket *tcpsocket;
    QTcpServer *tcpserver;
    void timerEvent(QTimerEvent *);
    QPoint getRealxy(QPoint p);
    static int oldx,oldy;
    static bool mousepressed;

//protected:
//    void mousePressEvent(QMouseEvent *q);
public:
    void sleep(unsigned int msec)    ;
};
class TcpServerSocket :QTcpSocket{

}
#endif // MAINWINDOW_H
