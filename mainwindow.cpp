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
}


void MainWindow::on_Quit_clicked()
{
    exit(0);
}

void MainWindow::on_play_clicked()
{
    mediaPlayer.play();
    playing = true;

}

void MainWindow::on_pause_clicked()
{
    mediaPlayer.pause();
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

    msgBox1.setText("This isn't how it works.\nUse Spotify.\nIt's probably little better than this 😉");
    msgBox1.setIcon(QMessageBox::Critical);
    msgBox1.exec();

    msgBox2.setIcon(QMessageBox::Warning);
    msgBox2.setText("This was a BAD decision 😢");
    msgBox2.exec();

    msgBox3.setIcon(QMessageBox::Question);
    msgBox3.setText("Wanna download Spotify instead of this junk?");
    msgBox3.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox3.setDefaultButton(QMessageBox::Save);

    int ret = msgBox3.exec();

    switch (ret) {
    case QMessageBox::Yes:
        msgBox4.setIcon(QMessageBox::Information);
        msgBox4.setText("This was a GOOD decision 😁");
        msgBox4.exec();
        QDesktopServices::openUrl(QUrl("https://www.spotify.com", QUrl::TolerantMode));
        break;

    case QMessageBox::No:
        msgBox4.setIcon(QMessageBox::Information);
        msgBox4.setText("Whatever...");
        msgBox4.exec();
        break;

    default:
        // should never be reached
        break;
    }
}
