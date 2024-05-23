#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT  // Enable signals and slots

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newDocument();  // Clears the main input box
    void startTimer();   // Starts the countdown timer
    void updateTimer();  // Updates the timer every second
    void restartTest();  // Restarts the test and resets everything
    void evaluateTyping();  // Evaluates the typing performance at the end of the test
    void startTimerIfNotRunning();  // Starts the timer if it is not already running

private:
    Ui::MainWindow *ui;          // Pointer to the UI elements
    QTimer *timer;               // Timer for countdown
    int timeLeft = 60;           // Time left in the countdown (initialized to 60 seconds)
    void loadTextToType();       // Loads text for the user to type
};

#endif // MAINWINDOW_H
