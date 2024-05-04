#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the QTimer
    timer = new QTimer(this);  // Ensure that 'timer' is properly initialized

    // Connections
    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::newDocument);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    connect(ui->userInput, &QTextEdit::textChanged, this, &MainWindow::startTimerIfNotRunning);

    // Countdown Timer
    ui->timerLabel->setText("60");                                      // Set initial display to 60 seconds
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::newDocument()
{
    ui->textEdit->clear();                                              // Make sure this matches the QTextEdit's name in Qt Designer
    currentFile.clear();
}

void MainWindow::startTimer(){
    if (!timer->isActive()) {
        timeLeft = 60;  // Reset the countdown
        timer->start(); // Start the timer
    }
}

void MainWindow::updateTimer(){
    if (timeLeft > 0){
        timeLeft--;
        ui->timerLabel->setText(QString::number(timeLeft));             // Update the label display
    } else {
        // Handle logic for when timer reaches 0
        timer->stop();
        ui->timerLabel->setText("Time is up!");
    }

}

void MainWindow::startTimerIfNotRunning()
{
    if (!timer->isActive()) {
        timeLeft = 60;  // Reset the timer to 60 seconds
        timer->start(1000);  // Timer ticks every second
    }
}

// void MainWindow::displayTextFile()
// {
//     QFile file("/input/input.txt");
//     if (!file.open(QIODevice::ReadOnly) | QIODevice::Text)
//         return;

//     while (!file.atEnd()) {
//         QByteArray. line = file.readLine();
//         process_line(line);
//     }
// }
