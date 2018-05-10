#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtWinExtras>
#include <QMediaPlayer>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupPlayer();

private slots:

    void on_Quit_clicked();

    void on_play_clicked();

    void on_pause_clicked();

    void on_stop_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_open_clicked();

    void on_ProgressSlider_sliderMoved(int position);

    void on_mute_clicked();

    void on_Help_clicked();

    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_actionStop_triggered();

    void on_actionExit_triggered();

    void on_actionHelp_triggered();

    void on_actionAbout_triggered();

    void on_checkBox_stateChanged(int arg1);

    void on_actionReg_triggered();

    void on_actionGreen_triggered();

    void on_actionYellow_triggered();

    void on_actionBlue_triggered();

    void on_actionWhite_triggered();

    void on_actionPink_triggered();

    void on_actionOrange_triggered();

private:
    Ui::MainWindow *ui;
    quint64 dur, pos;
    QMediaPlayer mediaPlayer;
    int timerId;
    int count;
    bool colourChange = true;

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
