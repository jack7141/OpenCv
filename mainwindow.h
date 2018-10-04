#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include "opencv2/opencv.hpp"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void mouseMoveEvent(int event, int x, int y, int flags, void* mouseImage);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsPixmapItem pixmap;
    cv::VideoCapture video;
    bool Gray_Btn;
    bool HP_Btn;
    bool RGB_Btn;
    bool Cap_Btn;
    int colorMode;
    int imgLabel_X;
    int imgLabel_Y;
    int cursor_X;
    int cursor_Y;
    int Pixloc;
    int Width[256];
    int Height[256];
    int Width_data[256];
    QString Text;
    QString save;

    QString src;
    QString dst;
    QString low;
    QString high;
    QDateTime date;
    QString SDate;
    cv::Mat mouseImage;
private slots:
void on_startBtn_clicked();

void on_grayBtn_clicked();

void on_HP_Btn_clicked();

void on_RGB_Btn_clicked();

void on_Cap_Btn_clicked();

protected:
void closeEvent(QCloseEvent *event);
void mouseMoveEvent(QMouseEvent *event) override;

};

#endif // MAINWINDOW_H
