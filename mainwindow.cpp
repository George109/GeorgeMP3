#include "mainwindow.h"
#include "ui_mainwindow.h"

bool playing = false;
bool muted = false;
int oldVolume;
using namespace std;
using namespace Qt;

QString filePath;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupPlayer();
    timerId = startTimer(100);
    count = 0;

}

MainWindow::~MainWindow()
{
    killTimer(timerId);
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    QString a = QString::number(mediaPlayer.position()/1000);
    QString b = QString::number(mediaPlayer.duration()/1000);
    ui->po->setText(a + "s");
    ui->du->setText(b + "s");
    if (playing == true){
        dur = mediaPlayer.duration();
        pos = mediaPlayer.position();
        ui->Progress->setRange(0, dur);
        ui->ProgressSlider->setRange(0, dur);
        if(pos < dur){
            pos = mediaPlayer.position();
            ui->Progress->setValue(pos);
            ui->ProgressSlider->setValue(pos);
        }
    }
    if (colourChange == true){
        if (count == 20){
            setStyleSheet("background-color: red;");
        }
        else if (count == 40){
            setStyleSheet("background-color: green;");
        }
        else if (count == 60){
            setStyleSheet("background-color: blue;");
        }
        else if (count == 80){
            setStyleSheet("background-color: yellow;");
        }
        else if (count == 100){
            setStyleSheet("background-color: pink;");
        }
        else if (count == 120){
            setStyleSheet("background-color: white;");
            count = 0;
        }
        else {
            //do nothing
        }
        qDebug() << count <<endl;
        count++;
    }
    else{
        //do nothing
    }

}

void MainWindow::setupPlayer(){

    ui->path->setText("Please open a file!");
    ui->play->setEnabled(false);
    ui->pause->setEnabled(false);
    ui->stop->setEnabled(false);
    ui->mute->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
    ui->ProgressSlider->setEnabled(false);
    ui->play->setCursor(ForbiddenCursor);
    ui->pause->setCursor(ForbiddenCursor);
    ui->stop->setCursor(ForbiddenCursor);
    ui->mute->setCursor(ForbiddenCursor);
    ui->horizontalSlider->setCursor(ForbiddenCursor);
    ui->ProgressSlider->setCursor(ForbiddenCursor);
    ui->actionPlay->setEnabled(false);
    ui->actionPause->setEnabled(false);
    ui->actionStop->setEnabled(false);
}


void MainWindow::on_Quit_clicked()
{
    QMessageBox msgBox4;
    QMessageBox msgBox5;
    QMessageBox msgBox6;

    msgBox4.setIcon(QMessageBox::Question);
    msgBox4.setText("Do you wanna exit?");
    msgBox4.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox4.setDefaultButton(QMessageBox::Yes);

    int ret = msgBox4.exec();

    switch (ret) {
    case QMessageBox::Yes:
        msgBox5.setIcon(QMessageBox::Information);
        msgBox5.setText("cya");
        msgBox5.exec();
        exit(0);
        break;

    case QMessageBox::No:
        msgBox6.setIcon(QMessageBox::Question);
        msgBox6.setText("Why are you still here?");
        msgBox6.exec();
        break;

    default:
        // should never be reached
        break;
    }
}

void MainWindow::on_play_clicked()
{
    mediaPlayer.play();
    playing = true;
    ui->play->setEnabled(false);
    ui->pause->setEnabled(true);
}

void MainWindow::on_pause_clicked()
{
    mediaPlayer.pause();
    ui->play->setEnabled(true);
    ui->pause->setEnabled(false);
}

void MainWindow::on_stop_clicked()
{
    mediaPlayer.stop();
    setupPlayer();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    mediaPlayer.setVolume(position);
    oldVolume = position;
}

void MainWindow::on_open_clicked()
{
    filePath = QFileDialog::getOpenFileName(this,tr("Open File"), "C:\\Users\\George\\Music\\", tr("MP3 Files (*.mp3)"));
    mediaPlayer.setMedia(QUrl::fromLocalFile(filePath));
    ui->path->setText(filePath);
    ui->play->setEnabled(true);
    ui->pause->setEnabled(true);
    ui->stop->setEnabled(true);
    ui->mute->setEnabled(true);
    ui->horizontalSlider->setEnabled(true);
    ui->ProgressSlider->setEnabled(true);
    ui->path->setText(filePath);
    ui->play->setCursor(ArrowCursor);
    ui->pause->setCursor(ArrowCursor);
    ui->stop->setCursor(ArrowCursor);
    ui->mute->setCursor(ArrowCursor);
    ui->horizontalSlider->setCursor(ArrowCursor);
    ui->ProgressSlider->setCursor(ArrowCursor);
    ui->actionPlay->setEnabled(true);
    ui->actionPause->setEnabled(true);
    ui->actionStop->setEnabled(true);
}

void MainWindow::on_ProgressSlider_sliderMoved(int position)
{
    mediaPlayer.pause();
    mediaPlayer.setPosition(position);
    mediaPlayer.play();
}

void MainWindow::on_mute_clicked()
{
    if (muted == false)
    {
        mediaPlayer.setVolume(0);
        ui->horizontalSlider->setValue(0);
        muted = true;
    }
    else if (muted == true)
    {
        mediaPlayer.setVolume(oldVolume);
        ui->horizontalSlider->setValue(oldVolume);
        muted = false;
    }
    else
    {
        exit(1);
    }
}

void MainWindow::on_Help_clicked()
{
    QMessageBox msgBox1;
    QMessageBox msgBox2;
    QMessageBox msgBox3;
    QMessageBox msgBox4;
    QMessageBox msgBox8;
    msgBox1.setText("This isn't how it works.\nUse Spotify.\nIt's probably little better than this 😉");
    msgBox1.setIcon(QMessageBox::Critical);
    msgBox1.exec();

    msgBox2.setIcon(QMessageBox::Warning);
    msgBox2.setText("Using this was probably a bad decision...");
    msgBox2.exec();

    msgBox3.setIcon(QMessageBox::Question);
    msgBox3.setText("Wanna download Spotify instead of this junk?");
    msgBox3.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox3.setDefaultButton(QMessageBox::Yes);

    int ret = msgBox3.exec();

    switch (ret) {
    case QMessageBox::Yes:
        msgBox4.setIcon(QMessageBox::Information);
        msgBox4.setText("This was a GOOD decision 😁");
        msgBox4.exec();
        QDesktopServices::openUrl(QUrl("https://www.spotify.com", QUrl::TolerantMode));
        break;

    case QMessageBox::No:
        msgBox8.setIcon(QMessageBox::Information);
        msgBox8.setText("Whatever...");
        msgBox8.exec();
        break;

    default:
        // should never be reached
        break;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    MainWindow::on_open_clicked();
}

void MainWindow::on_actionPlay_triggered()
{
    MainWindow::on_play_clicked();
}

void MainWindow::on_actionPause_triggered()
{
    MainWindow::on_pause_clicked();
}

void MainWindow::on_actionStop_triggered()
{
    MainWindow::on_stop_clicked();
}

void MainWindow::on_actionExit_triggered()
{
    MainWindow::on_Quit_clicked();
}

void MainWindow::on_actionHelp_triggered()
{
    MainWindow::on_Help_clicked();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox AboutMSG;
    AboutMSG.setWindowTitle("About...");
    AboutMSG.setIcon(QMessageBox::Information);
    AboutMSG.setTextFormat(Qt::RichText);
    AboutMSG.setText("Version 0.4 Dreadful<br>Changelog: <br>-Added some colours <br>-Added many many more bugs to fix later ;) <br><a href='https://github.com/George109/GeorgeMP3/'>Find this bs on GitHub.</a>");
    AboutMSG.exec();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (colourChange == true){
        colourChange = false;
    }
    else if (colourChange == false){
        colourChange = true;
    }
}

void MainWindow::on_actionReg_triggered()
{
    setStyleSheet("background-color: red;");
    //QCheckBox.setchecked(false);
    colourChange = false;
}

void MainWindow::on_actionGreen_triggered()
{
    setStyleSheet("background-color: green;");
    //QCheckBox.setchecked(false);
    colourChange = false;
}

void MainWindow::on_actionYellow_triggered()
{
    setStyleSheet("background-color: yellow;");
    //QCheckBox.setchecked(false);
    colourChange = false;
}

void MainWindow::on_actionBlue_triggered()
{
    setStyleSheet("background-color: blue;");
    //QCheckBox.setchecked(false);
    colourChange = false;
}

