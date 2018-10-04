#include "mainwindow.h"
#include "ui_mainwindow.h"
#define useMouse "Mouse Event"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->graphicsView->setScene(new QGraphicsScene(this));
//    ui->graphicsView->scene()->addItem(&pixmap);
//    cv::namedWindow("ImageDisplay",1);
    colorMode=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(video.isOpened())
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Stop the video before closing the application!");
        event->ignore();
    }
    else
    {
        event->accept();
    }
}


void MainWindow::on_startBtn_clicked()
{
    using namespace cv;

    if(video.isOpened())
    {
        ui->startBtn->setText("Start");
        video.release();
        return;
    }

    bool isCamera;
    int cameraIndex = ui->videoEdit->text().toInt(&isCamera);
    if(isCamera)
    {
        if(!video.open(cameraIndex))
        {
            QMessageBox::critical(this,
                                  "Camera Error",
                                  "Make sure you entered a correct camera index,"
                                  "<br>or that the camera is not being accessed by another program!");
            return;
        }
    }
    else
    {
        if(!video.open(ui->videoEdit->text().trimmed().toStdString()))
        {
            QMessageBox::critical(this,
                                  "Video Error",
                                  "Make sure you entered a correct and supported video file path,"
                                  "<br>or a correct RTSP feed URL!");
            return;
        }
    }

    ui->startBtn->setText("Stop");

    Mat frame;
    while(video.isOpened())
    {

        video >> frame;
        date = QDateTime::currentDateTime();
        SDate = date.toString("yyyy.MM.dd.hh.mm.ss");
        cv::putText(frame,SDate.toStdString(),Point(10,30),FONT_HERSHEY_SCRIPT_SIMPLEX ,1,Scalar(0,255,255),1,LINE_8,false);

        if(!frame.empty())
        {

            switch(colorMode)
            {
            case 0:
                break;
            case 1:
                cv::cvtColor(frame, frame, CV_BGR2GRAY);
                for(int x=0;x<256;x++)
                {
                         Width[x]=0;
                         Height[x]=0;
                }
                for(int i=0;i<frame.cols;i++)//640
                {
                    Width[frame.data[i+(640*cursor_Y)]]++;//in pixline data count data.
                    cv::line(frame, Point(i,479-frame.data[i+(640*cursor_Y)]+1), Point(i,479-frame.data[i+(640*cursor_Y)]-1), Scalar(255,255,255),1,LINE_8,0);
                }
                for(int j=0;j<frame.rows;j++)//480
                {

                    Height[ frame.data[cursor_X+(640*j)]]++;
                    cv::line(frame, Point(639-frame.data[cursor_X+(640*j)]+1,j), Point(639-frame.data[cursor_X+(640*j)]-1,j), Scalar(255,255,255),1,LINE_8,0);

                }
                for(int x=0;x<256;x++)
                {
                    cv::line(frame, Point(x,0), Point(x,Width[x]),Scalar(255,255,255),1,LINE_8,0);
                    cv::line(frame, Point(0,x), Point(Height[x],x),Scalar(255,255,255),1,LINE_8,0);
                }

//                 cv::cvtColor(frame, frame, CV_GRAY2RGB);
                cv::line(frame, Point(0,cursor_Y), Point(639,cursor_Y), Scalar(0, 255, 255), 1, LINE_8, 0);
                cv::line(frame, Point(cursor_X,0), Point(cursor_X,480), Scalar(0, 255, 255), 1, LINE_8, 0);
                break;
            case 2:
                threshold(frame, frame, 150, 255, THRESH_BINARY);
                break;
            }

            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format(colorMode==2?24:13));



//            pixmap.setPixmap( );
            ui->ImgLabel->setPixmap(QPixmap::fromImage(qimg.rgbSwapped()) );


             if(Cap_Btn)
             {
                 Text = "/home/pi/Pictures/";
                 save = Text.append(SDate).append(".png");
                 imwrite(save.toStdString(), frame);
                 Cap_Btn=false;
             }

        }
        qApp->processEvents();
    }

    ui->startBtn->setText("Start");

}


void MainWindow::on_RGB_Btn_clicked()
{

    colorMode=0;
}
void MainWindow::on_grayBtn_clicked()
{

    colorMode =1;
}

void MainWindow::on_HP_Btn_clicked()
{

    colorMode = 2;
}


void MainWindow::on_Cap_Btn_clicked()
{
    Cap_Btn = true;
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    imgLabel_X=ui->ImgLabel->geometry().x();
    imgLabel_Y=ui->ImgLabel->geometry().y();
    cursor_X = event->pos().x()-imgLabel_X;
    cursor_Y = event->pos().y()-imgLabel_Y;
    if(ui->ImgLabel->geometry().width()-1<=cursor_X)
    {
        cursor_X=639;
    }
    if(cursor_X<=0)
    {
        cursor_X=0;
    }
    ui->label_X->setText(QString::number(cursor_X));

    if(ui->ImgLabel->geometry().height()-1<=cursor_Y)
    {
        cursor_Y=479;
    }
    if(cursor_Y<=0)
    {
        cursor_Y=0;
    }
    ui->label_Y->setText(QString::number(cursor_Y));
}
