#include "jni.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
//#include <QtNetwork>
#include <QtNetwork/QTcpSocket>
#include <QTime>
#include <QThread>
#include <QMutex>
#include <QTcpServer>
#include <QPicture>
#include <QCryptographicHash>
#include <stringtohex.h>

const char *RTPHeaderStr="RTPHWELTER";

JNIEnv *MainWindow::env;
JavaVM *MainWindow::jvm;
jclass MainWindow::cls_screenshot;
jobject MainWindow::obj;
jmethodID MainWindow::J_getScreen;
jclass MainWindow::cls_rawimage;
jfieldID MainWindow::f_bpp;
jfieldID MainWindow::f_data;
jfieldID MainWindow::f_red_l;
jfieldID MainWindow::f_blue_l;
jfieldID MainWindow::f_green_l;
jfieldID MainWindow::f_red_o;
jfieldID MainWindow::f_blue_o;
jfieldID MainWindow::f_green_o;
jfieldID MainWindow::f_alpha_l;
jfieldID MainWindow::f_alpha_o;
jfieldID MainWindow::f_height;
jfieldID MainWindow::f_width;
int MainWindow::oldx,MainWindow::oldy;
bool MainWindow::mousepressed;
bool istcpconnected=false;
QMutex tcpMutex;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->label->move((ui->centralWidget->width()-ui->label->width())/2,(ui->centralWidget->height()-ui->label->height())/2);


    windowheight=432;
    windowwidth=243;
//    ui->graphicsView->viewport()->installEventFilter(this);
        //tcpsocket = new QTcpSocket(this);
        tcpserver = new QTcpServer(this);
        //connect(tcpsocket,SIGNAL(connected()),this,SLOT(tcpconnected()));
        if (tcpserver->listen(QHostAddress("192.168.0.5"),22222)) ui->statusBar->showMessage("ok");
        connect(tcpserver,SIGNAL(newConnection()),this,SLOT(on_serverconnected()));
       m_nTimerId=-1;
        JavaVMInitArgs vm_args;
        JavaVMOption options[3];
        int res;
        //设置参数
        options[0].optionString = "-Djava.compiler=NONE";
        //classpath有多个时，UNIX下以“：”分割。
        options[1].optionString = "-Djava.class.path=./java:./java/ddmlib.jar";
        options[2].optionString = "-verbose:jni";

        vm_args.version = JNI_VERSION_1_6;
        vm_args.nOptions = 3;
        vm_args.options = options;
        vm_args.ignoreUnrecognized = JNI_TRUE;
        res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
//        ui->statusBar->showMessage(vm_args.options[1].optionString);
        if (res >= 0)
        {
            cls_screenshot=env->FindClass("com/android/screenshot/Screenshot");
  //          ui->statusBar->showMessage(env->);
            if (cls_screenshot!=NULL)  {
     //           ui->statusBar->showMessage("ooooo");
                //obj=env->AllocObject(cls_getScreen);
                //if (obj!=NULL){
//                     ui->statusBar->showMessage("kkkkkkkkk");
                    J_getScreen=env->GetStaticMethodID(cls_screenshot,"getScreen","(Z)Lcom/android/ddmlib/RawImage;");
                    if (J_getScreen!=NULL)
                    {
  //                      ui->statusBar->showMessage("ooooookkkkkk");
                    }
                //}

            }
            cls_rawimage=env->FindClass("com/android/ddmlib/RawImage");
  //          ui->statusBar->showMessage(env->);
            if (cls_rawimage!=NULL)  {
        //        ui->statusBar->showMessage("ooooo2");
                //obj=env->AllocObject(cls_getScreen);
                //if (obj!=NULL){
                   //  ui->statusBar->showMessage("kkkkkkkkk");
                    f_data =env->GetFieldID(cls_rawimage,"data","[B");
                    f_bpp=env->GetFieldID(cls_rawimage,"bpp","I");
                    f_height=env->GetFieldID(cls_rawimage,"height","I");
                    f_width=env->GetFieldID(cls_rawimage,"width","I");
                    f_red_l=env->GetFieldID(cls_rawimage,"red_length","I");
                    f_red_o=env->GetFieldID(cls_rawimage,"red_offset","I");
                    f_blue_l=env->GetFieldID(cls_rawimage,"blue_length","I");
                    f_blue_o=env->GetFieldID(cls_rawimage,"blue_offset","I");
                    f_green_l=env->GetFieldID(cls_rawimage,"green_length","I");
                    f_green_o=env->GetFieldID(cls_rawimage,"green_offset","I");
                    f_alpha_l=env->GetFieldID(cls_rawimage,"alpha_length","I");
                    f_alpha_o=env->GetFieldID(cls_rawimage,"alpha_offset","I");
                    //J_getScreen=env->GetStaticObjectField("get")
                    if (( f_data!=0) && ( f_bpp!=0) && ( f_height!=0) && ( f_width!=0) && ( f_red_l!=0) && ( f_red_o!=0) && ( f_blue_l!=0) && ( f_blue_o!=0) && ( f_green_l!=0) && ( f_green_o!=0) && ( f_alpha_l!=0) && ( f_alpha_o!=0) )
                    {
                        ui->statusBar->showMessage("ooooookkkkkk2");
                    }
                //}

            }
        }
    ui->label->installEventFilter(this);
//    ui->mainToolBar->hide();
//    ui->statusBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//void MainWindow::mousePressEvent(QMouseEvent *q)
//{
//   ui->statusBar->showMessage("ok");
//}
void MainWindow::tcpconnected()
{
    istcpconnected=true;
    ui->statusBar->showMessage("ok54");
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{

//     ui->statusBar->showMessage("ok3");
    printf("get in eventfilter");
    char *cmdstr;
    char numstr[5]={' ',' ',' ',' ',' '};
    cmdstr=(char*)malloc(35);

    if (watched==ui->label )
    {
        if (event->type()==QEvent::MouseMove)
        {
           /* strcpy(cmdstr,RTPHeaderStr);
            strcat(cmdstr,"TOHS");
            strcat(cmdstr,"1");
            sprintf(numstr,"%04d",((QMouseEvent*) event)->pos().x());
            strcat(cmdstr,numstr);
            sprintf(numstr,"%04d",((QMouseEvent*) event)->pos().y());
            strcat(cmdstr,numstr);*/

        }
        else
            if(event->type()==QEvent::MouseButtonRelease)
            {
               if(mousepressed&&((((QMouseEvent*) event)->pos().x()!=oldx) || (((QMouseEvent*) event)->pos().y()!=oldy)))
                {
                 ui->statusBar->showMessage("ok7");
                 strcpy(cmdstr,RTPHeaderStr);
                 strcat(cmdstr,"TOHS");
                 strcat(cmdstr,"1");
                 sprintf(numstr,"%04d",oldx);
                 strcat(cmdstr,numstr);
                 sprintf(numstr,"%04d",oldy);
                 strcat(cmdstr,numstr);
                 sprintf(numstr,"%04d",((QMouseEvent*) event)->pos().x());
                 strcat(cmdstr,numstr);
                 printf("%d",((QMouseEvent*) event)->pos().x());
                 sprintf(numstr,"%04d",((QMouseEvent*) event)->pos().y());
                 strcat(cmdstr,numstr);
                 ui->statusBar->showMessage(cmdstr);
                 SendMessage *sender=new SendMessage("172.18.1.8",9500,cmdstr);
                 sender->start();
                 mousepressed=false;
                   }
                else
                {
                    if(mousepressed){
                    ui->statusBar->showMessage("ok9");
                    strcpy(cmdstr,RTPHeaderStr);
                    strcat(cmdstr,"TOH ");
                    strcat(cmdstr,"1");
                    QPoint point=((QMouseEvent*) event)->pos();
                    point=getRealxy(point);
                    printf("realxy:%d,%d\n",point.x(),point.y());
                    sprintf(numstr,"%04d",point.x());
                    strcat(cmdstr,numstr);
                    sprintf(numstr,"%04d",point.y());
                    strcat(cmdstr,numstr);
                    ui->statusBar->showMessage(cmdstr);
                    SendMessage *sender=new SendMessage("172.18.1.8",9500,cmdstr);
                    sender->start();
                    mousepressed=false;
                    }
                 }
            }
        else
            if(event->type()==QEvent::MouseButtonPress)
            {
          //       ui->statusBar->showMessage("ok8");
                 oldx=((QMouseEvent*) event)->pos().x();
                 oldy=((QMouseEvent*) event)->pos().y();
                 mousepressed=true;
            }
        else
            if(event->type()==QEvent::KeyPress)
            {
                strcpy(cmdstr,RTPHeaderStr);
                strcat(cmdstr,"KEY ");
                sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
 //               strcpy(numstr,toascii(((QKeyEvent*) event)->key()));
                strcat(cmdstr,numstr);
//                sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
//                strcat(cmdstr,numstr);
                ui->statusBar->showMessage(cmdstr);
                SendMessage *sender=new SendMessage("172.18.1.8",9500,cmdstr);
                sender->start();
            }
        else
            if(event->type()==QEvent::KeyRelease)
            {
 /*               strcpy(cmdstr,RTPHeaderStr);
                strcat(cmdstr,"KEY ");
                sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
                strcat(cmdstr,numstr);
                sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
                strcat(cmdstr,numstr);
                ui->statusBar->showMessage(cmdstr);*/
            }
    free(cmdstr);
    return QWidget::eventFilter(watched,event);
}
}
void MainWindow::on_pushButton_clicked()
{
    if(m_nTimerId<0)
    {
    m_nTimerId = startTimer(2000);
    ui->pushButton->setText("停止截屏");
    }
    else
    {
        this->killTimer(m_nTimerId);
        ui->pushButton->setText("截屏");
        m_nTimerId=-1;
    }

}
void MainWindow::timerEvent(QTimerEvent * qe)
{
    jobject rawimage;
    //image->fromData()
    //ui->graphicsView->
    if (J_getScreen!=NULL)
    {
    rawimage=env->CallStaticObjectMethod(cls_screenshot,J_getScreen,"false");
//    if (rawimage!=NULL)
    {
       int bpp=env->GetIntField(rawimage,f_bpp);
       int width=env->GetIntField(rawimage,f_width);
       int height=env->GetIntField(rawimage,f_height);
       int red_l=env->GetIntField(rawimage,f_red_l);
       int red_o=env->GetIntField(rawimage,f_red_o);
       int blue_l=env->GetIntField(rawimage,f_blue_l);
       int blue_o=env->GetIntField(rawimage,f_blue_o);
       int green_l=env->GetIntField(rawimage,f_green_l);
       int green_o=env->GetIntField(rawimage,f_green_o);
       int alpha_l=env->GetIntField(rawimage,f_alpha_l);
       int alpha_o=env->GetIntField(rawimage,f_alpha_o);
       jbyteArray J_data=(jbyteArray ) env->GetObjectField(rawimage,f_data);
       int data_l=env->GetArrayLength(J_data);
       jbyte *jbarray = (jbyte *)malloc(data_l * sizeof(jbyte));
       env->GetByteArrayRegion(J_data,0,data_l,jbarray);
//       env->ReleaseByteArrayElements(J_data);

       unsigned char*data=(unsigned char*) jbarray;
       QImage *image = new QImage(width,height,QImage::Format_ARGB32);
       int index = 0;
       int IndexInc = bpp >> 3;
       for (int y = 0 ; y < height ; y++) {
           for (int x = 0 ; x < width ; x++) {
//               int value = rawImage.getARGB(index);
               int value;
               if (bpp == 16) {
                   value = data[index] & 0x00FF;
                   value |= (data[index+1] << 8) & 0x0FF00;
               } else if (bpp == 32) {
                   value = data[index] & 0x00FF;
                   value |= (data[index+1] & 0x00FF) << 8;
                   value |= (data[index+2] & 0x00FF) << 16;
                   value |= (data[index+3] & 0x00FF) << 24;
               } else {
//                   throw new UnsupportedOperationException("RawImage.getARGB(int) only works in 16 and 32 bit mode.");
               }
               unsigned int u_value=(unsigned) value;
               int r = ((u_value>> red_o) &((1<<red_l)-1) )<< (8 - red_l);
               int g = ((u_value >> green_o) & ((1<<green_l)-1) ) << (8 - green_l);
               int b = ((u_value >> blue_o) & ((1<<blue_l)-1) ) << (8 - blue_l);
               int a;
               if (alpha_l == 0) {
                   a = 0xFF; // force alpha to opaque if there's no alpha value in the framebuffer.
               } else {
                   a = ((u_value >> alpha_o) & ((1<<alpha_l)-1) ) << (8 - alpha_l);
               }

//               return a << 24 | r << 16 | g << 8 | b;
               index += IndexInc;
               image->setPixel(x,y,a << 24 | r << 16 | g << 8 | b);
           }
       }
       //scene->addPixmap(QPixmap::fromImage(*image));
       if (( ui->label->width()<width)|| (ui->label->height()<height))
       {
               *image=image->scaledToHeight(ui->label->height());
        }
       windowheight=image->height();
       windowwidth=image->width();
       ui->label->setPixmap(QPixmap::fromImage(*image));
       if (jbarray!=NULL)
       {
           free(jbarray);
       }
       if (image!=NULL)
       {
           free(image);
       }
       env->DeleteLocalRef(rawimage);
       }

    }


}

void MainWindow::on_backButton_clicked()
{
    char *cmdstr;

    cmdstr=(char*) malloc(25);
    strcpy(cmdstr,RTPHeaderStr);
    strcat(cmdstr,"BACK");
    //sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
//               strcpy(numstr,toascii(((QKeyEvent*) event)->key()));
    //strcat(cmdstr,numstr);
//                sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
//                strcat(cmdstr,numstr);
    ui->statusBar->showMessage(cmdstr);
    SendMessage *sender=new SendMessage("172.18.1.8",9500,cmdstr);
    sender->start();
    free(cmdstr);
}

void MainWindow::on_homeButton_clicked()
{
    char *cmdstr;
    cmdstr=(char*) malloc(25);
    strcpy(cmdstr,RTPHeaderStr);
    strcat(cmdstr,"HOME");
    //sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
//               strcpy(numstr,toascii(((QKeyEvent*) event)->key()));
    //strcat(cmdstr,numstr);
//                sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
//                strcat(cmdstr,numstr);

        ui->statusBar->showMessage(cmdstr);
        SendMessage *sender=new SendMessage("172.18.1.8",9500,cmdstr);
        sender->start();
    free(cmdstr);
}

void MainWindow::on_menuButton_clicked()
{
    char *cmdstr;
    cmdstr=(char*) malloc(25);
    strcpy(cmdstr,RTPHeaderStr);
    strcat(cmdstr,"MENU");
    //sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
//               strcpy(numstr,toascii(((QKeyEvent*) event)->key()));
    //strcat(cmdstr,numstr);
//                sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
//                strcat(cmdstr,numstr);
    ui->statusBar->showMessage(cmdstr);
    //tcpsocket->abort();
    //tcpsocket->connectToHost("172.18.1.8",9500);
    SendMessage *sender=new SendMessage("172.18.1.8",9500,cmdstr);
    sender->start();
    free(cmdstr);
}

void MainWindow::on_VOLDownButton_clicked()
{
    char *cmdstr;
    cmdstr=(char*) malloc(25);
    strcpy(cmdstr,RTPHeaderStr);
    strcat(cmdstr,"VOLD");
    //sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
//               strcpy(numstr,toascii(((QKeyEvent*) event)->key()));
    //strcat(cmdstr,numstr);
//                sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
//                strcat(cmdstr,numstr);
    ui->statusBar->showMessage(cmdstr);
    //tcpsocket->abort();
    //tcpsocket->connectToHost("172.18.1.8",9500);
    SendMessage *sender=new SendMessage("172.18.1.8",9500,cmdstr);
    sender->start();
    free(cmdstr);
}

void MainWindow::on_VOLUPButton_clicked()
{
    char *cmdstr;
    cmdstr=(char*) malloc(25);
    strcpy(cmdstr,RTPHeaderStr);
    strcat(cmdstr,"VOLU");
    //sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
//               strcpy(numstr,toascii(((QKeyEvent*) event)->key()));
    //strcat(cmdstr,numstr);
//                sprintf(numstr,"%04d",((QKeyEvent*) event)->key());
//                strcat(cmdstr,numstr);
    ui->statusBar->showMessage(cmdstr);
    //tcpsocket->abort();
    //tcpsocket->connectToHost("172.18.1.8",9500);
    SendMessage *sender=new SendMessage("172.18.1.8",9500,cmdstr);
    sender->start();
    free(cmdstr);
}

void MainWindow::on_serverconnected()
{
    if (tcpserver->hasPendingConnections()) {
        ui->statusBar->showMessage("ok2");
        tcpServerReceiver= new TcpServerReceiver(tcpserver->nextPendingConnection());
        //connect(tcpsocket,SIGNAL(readyRead()),this,SLOT(readmessage()));
        connect(tcpServerReceiver,SIGNAL(onDataReceived(QByteArray)),this,SLOT(readdata(QByteArray)));
    }
}
void MainWindow::sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
 }

void MainWindow::readmessage()
{
    char *rdstr;
    int bs;
    QString rdstring;
    bs=tcpsocket->bytesAvailable();
    rdstr=(char*) malloc(bs);
    memset(rdstr,0,sizeof(rdstr)/sizeof(char));
    tcpsocket->read(rdstr,bs);
    QImage* img=new QImage;
//    img->loadFromData((uchar *) rdstr,1);
    QPicture p;
    p.setData(rdstr,bs);
    ui->label->setPicture(p);
    rdstring= QString::fromLocal8Bit(rdstr,-1);
    ui->statusBar->showMessage(rdstring);
    free(rdstr);
    rdstr=NULL;
}
SendMessage::SendMessage(char *host,quint16 port,char *msg)
{
 //   QMutexLocker locker(&tcpMutex);
    printf(host);
    message=(char*)malloc(strlen(msg));
    strcpy(message,msg);
    Host=(char*)malloc(strlen(host));
    strcpy(Host,host);
    Port=port;
    printf("comming:\n");

}

void SendMessage::run()
{
    printf("run\n");
    printf("host:%s\n",Host);
    printf("port:%d\n",Port);
    printf("before create socket");
    tcpsocket=new QTcpSocket();
    printf("created socket");

    connect( tcpsocket, SIGNAL(disconnected()), tcpsocket, SLOT(deleteLater()) );
    connect(tcpsocket,SIGNAL(connected()),this,SLOT(onTcpConnected()),Qt::DirectConnection);
  //  connect( tcpsocket, SIGNAL(disconnected()), this, SLOT(onTcpDisConnected()) );
    connect( this, SIGNAL(finished()), this, SLOT(deleteLater()) );
//    try
//    {
       tcpsocket->connectToHost(Host,Port);
//    }
 //   catch (char *exception)
       {
//       printf(exception);
       }

   //if (tcpsocket!=NULL)
 //      free(tcpsocket);
  // if (message!=NULL)
//       free(message);
//   if (Host!=NULL)
 //      free(Host);
       exec();
}
void SendMessage::onTcpConnected()
{
    printf("connected");
    printf("message%s\n",message);
      printf("write bytes:%d\n",tcpsocket->write(message));
      tcpsocket->flush();
      tcpsocket->abort();
      if (message!=NULL)
          free(message);
      if (Host!=NULL)
          free(Host);
}
void SendMessage::onTcpDisConnected()
{
    printf("disconnected");
 //   if (message!=NULL)
  //      free(message);
 //   if (Host!=NULL)
   //     free(Host);
}
QPoint MainWindow::getRealxy(QPoint p)
{

    printf("labelwidth:%d,labelheight:%d,width:%d,x:%d,height:%d,y:%d\n",ui->label->width(),ui->label->height(),windowwidth,p.x(),windowheight,p.y());
    int x,y;
    double fx=((double) p.x()-((double)ui->label->width()-(double)windowwidth)/2)/(double) windowwidth;
    double fy=((double) p.y()-((double)ui->label->width()-(double)windowheight)/2)/(double) windowheight;
    printf("fx:%f,fy:%f\n",fx,fy);
    x=fx*720;
    y=fy*1280;
    printf("x2:%d,y2:%d\n",x,y);
    return QPoint(x,y);
}

void MainWindow::readdata(QByteArray d)
{
//    QImage *p;
    QPicture *p;
    QDataStream dataStream(&d,QIODevice::ReadOnly);
    pictureData.clear();
    pictureData.append(d);
    p->load(dataStream.device());
    ui->statusBar->showMessage(StringToHex(QCryptographicHash::hash(d,QCryptographicHash::Md5)));
    ui->label->setPicture(*p);
}
TcpServerReceiver::TcpServerReceiver()
{

}
TcpServerReceiver::TcpServerReceiver(QTcpSocket *t)
{
  _isReading=false;
  _waitingForWholeData=false;
  _targetLength=0;
  tcpSocket=t;
  connect(this->tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceiver()));
  connect(this->tcpSocket,SIGNAL(disconnected()),this,SLOT(onFinish()));
}

TcpServerReceiver::~TcpServerReceiver()
{

}
quint64 TcpServerReceiver::dataReceiver()
{
    qint32 nRead = 0;
    quint64 readReturn;
    QByteArray bytes;

    _isReading = true;

    _currentRead = tcpSocket->bytesAvailable();
    //qDebug () << "nAvailable: " << _currentRead;

    if (_currentRead < TcpHeaderFrameHelper::sizeofHeaderFrame())
        return 0;

    while (_currentRead >= TcpHeaderFrameHelper::sizeofHeaderFrame())
    {
        if (!_waitingForWholeData)
        {
            bytes.resize(TcpHeaderFrameHelper::sizeofHeaderFrame());
            readReturn = tcpSocket->read(bytes.data(), TcpHeaderFrameHelper::sizeofHeaderFrame());

            if (readReturn == -1)
                return -1;
            nRead += readReturn;

            TcpHeaderFrameHelper::praseHeader(bytes, _headerFrame);
            _targetLength = _headerFrame.messageLength + TcpHeaderFrameHelper::sizeofHeaderFrame();
            //qDebug () << "headerFrame length: " << _headerFrame.messageLength;
        }

        if (_currentRead >= _targetLength)
        {
            qint32 length = _targetLength - TcpHeaderFrameHelper::sizeofHeaderFrame();
            _data.resize(length);
            readReturn = tcpSocket->read(_data.data(), length);

            if (readReturn == -1)
                return -1;
            nRead += readReturn;

            //qDebug () << "_currentRead: " << _currentRead;

            _waitingForWholeData = false;
            _currentRead -= _targetLength;
            emit onDataReceived(_data);
            if(_currentRead == 0)
                _isReading = false;
        }
        //如果不等于headerFrame.messageLength，说明还没读完，继续读取
        else
        {
            _waitingForWholeData = true;
            break;
        }
    }

    return nRead;
}

void TcpServerReceiver::onFinish()
{

}

quint64 TcpHeaderFrameHelper::sizeofHeaderFrame()
{
 return 8;
}

void TcpHeaderFrameHelper::praseHeader(QByteArray &data, HeaderFrame &header)
{
    quint64 i;
    QDataStream stream(&data, QIODevice::ReadOnly);
    stream >> i;
    //i= (quint64*) data.left(8).data();
    header.messageLength=i;
}


