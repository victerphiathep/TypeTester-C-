#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>

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
    // Declare methods as slots here
    void newDocument();  // clears the main inputBox
    void startTimer();
    void updateTimer();
    void startTimerIfNotRunning();

private:
    Ui::MainWindow *ui;
    QString currentFile;  // Holds the file path or name of the current document
    QTimer *timer;
    int timeLeft;
};

#endif // MAINWINDOW_H
