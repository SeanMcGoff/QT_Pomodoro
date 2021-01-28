#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPalette>
#include <QColor>

//eventually remove
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum TimerState{WORK, SHORT_REST, LONG_REST};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void lcd_countDown();
    void startTimer();
    void stopTimer();
    void stateResetTimer();
    void fullResetTimer();
    void nextTimerState();
    int getCurrentStateMax();
    void on_actionAbout_triggered();
    void setWindowGradient();
    void resetWindowColor();
    void on_resetButton_clicked();

    void on_workSpin_valueChanged(int arg1);

    void on_shortRestSpin_valueChanged(int arg1);

    void on_longRestSpin_valueChanged(int arg1);

    void on_softResetButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    TimerState timerstate = WORK;
    int iShortRestCount;
};
#endif // MAINWINDOW_H
