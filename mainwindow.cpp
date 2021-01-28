#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(lcd_countDown()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//color functions
float timeToFloat(int m, int s, int totalm)
{
    float f = (float)(m*60 + s) / (float)(totalm * 60);
    return f;
}
QColor floatToRGB(float f)
{
    QColor color;
    if (f > 0.5f)
    {
        color.setRed((1 - f) * 2 * 255);
        color.setGreen(255);
        color.setBlue(0);
    }
    else
    {
        color.setRed(255);
        color.setGreen(f * 2 * 255);
        color.setBlue(0);
    }
    return color;
}

//Work & Rest State functions
void MainWindow::nextTimerState()
{
    switch(timerstate)
    {
        case (WORK):
        iShortRestCount++;
        if (iShortRestCount % 4 == 0)
        {
            timerstate = LONG_REST;
            ui->topLabel->setText("Pomodoro - Long Rest");
            setWindowTitle("Pomodoro - Long Rest");
        } else
        {
            timerstate = SHORT_REST;
            ui->topLabel->setText("Pomodoro - Short Rest");
            setWindowTitle("Pomodoro - Short Rest");
        }
        break;
        case (SHORT_REST):
        timerstate = WORK;
        ui->topLabel->setText("Pomodoro - Work");
        setWindowTitle("Pomodoro - Work");
        break;
        case (LONG_REST):
        timerstate = WORK;
        ui->topLabel->setText("Pomodoro - Work");
        setWindowTitle("Pomodoro - Work");
        break;
    }
    stateResetTimer();
    setWindowGradient();
}

int MainWindow::getCurrentStateMax()
{
    switch(timerstate)
    {
        case (WORK):
        return ui->workSpin->value();
        break;
        case (SHORT_REST):
        return ui->shortRestSpin->value();
        break;
        case (LONG_REST):
        return ui->longRestSpin->value();
        break;
    }
    //definitely would never happen but just for edge-case safety
    return 0;
}

//timer functions
void MainWindow::startTimer()
{
    timer->start(1000);
    ui->startButton->setText("Stop Timer");
    ui->resetButton->setEnabled(false);
    ui->settingsLayout->hide();
    ui->resetButtons->hide();
    ui->topLabel->setText("Pomodoro - Work");
    setWindowTitle("Pomodoro - Work");
}

void MainWindow::stopTimer()
{
    timer->stop();
    ui->startButton->setText("Start Timer");
    ui->resetButton->setEnabled(true);
    ui->softResetButton->setEnabled(true);
    ui->settingsLayout->show();
    ui->resetButtons->show();
    ui->topLabel->setText("Pomodoro Timer");
    setWindowTitle("Pomodoro Timer");
}

void MainWindow::stateResetTimer() {
    ui->secsDisplay->display(0);
    ui->minsDisplay->display(getCurrentStateMax());
}

void MainWindow::fullResetTimer()
{
    ui->secsDisplay->display(0);
    timerstate = WORK;
    ui->minsDisplay->display(ui->workSpin->value());
    ui->topLabel->setText("Pomodoro Timer");
}

//color setting functions
void MainWindow::setWindowGradient()
{
    int m = ui->minsDisplay->intValue();
    int s = ui->secsDisplay->intValue();
    int tm = getCurrentStateMax();
    QColor gradient = floatToRGB(timeToFloat(m, s, tm));
    QPalette palette(gradient);
    this->setPalette(palette);
}

void MainWindow::resetWindowColor()
{
    QColor gray = "#333333";
    QPalette palette(gray);
    this->setPalette(palette);
}

//auto generated slot functions
void MainWindow::on_startButton_clicked()
{
    if(timer->isActive())
    {
    stopTimer();
    resetWindowColor();
    }
    else
    {
    this->setWindowGradient();
    startTimer();
    }

}

//countdown the LCD Screens
void MainWindow::lcd_countDown()
{
    int m = ui->minsDisplay->intValue();
    int s = ui->secsDisplay->intValue();
    if (m == 0 && s == 0) {
        nextTimerState();
    } else if(s == 0)
    {
        ui->minsDisplay->display(m - 1);
        ui->secsDisplay->display(59);
    } else
    {
        ui->secsDisplay->display(s - 1);
    }
    //set color
    this->setWindowGradient();
}


//OPENS ABOUT DIALOG
void MainWindow::on_actionAbout_triggered()
{
    aboutDialog aboutWindow;
    aboutWindow.setModal(true);
    aboutWindow.setWindowTitle("About Pomodoro");
    aboutWindow.exec();
}

void MainWindow::on_softResetButton_clicked()
{
   ui->softResetButton->setEnabled(false);
   stateResetTimer();
}

void MainWindow::on_resetButton_clicked()
{
    ui->softResetButton->setEnabled(false);
    ui->resetButton->setEnabled(false);
    fullResetTimer();
}

void MainWindow::on_workSpin_valueChanged(int arg1)
{
    if (timerstate == WORK) {ui->minsDisplay->display(arg1);}
}

void MainWindow::on_shortRestSpin_valueChanged(int arg1)
{
   if (timerstate == SHORT_REST) {ui->minsDisplay->display(arg1);}
}

void MainWindow::on_longRestSpin_valueChanged(int arg1)
{
   if (timerstate == LONG_REST) {ui->minsDisplay->display(arg1);}
}


