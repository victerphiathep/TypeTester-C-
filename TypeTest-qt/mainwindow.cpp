#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QRegularExpression>  // Include this to use QRegularExpression

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the QTimer
    timer = new QTimer(this);

    // Connections
    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::restartTest);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    connect(ui->userInput, &QTextEdit::textChanged, this, &MainWindow::startTimerIfNotRunning);

    // Initial UI setup
    ui->timerLabel->setText("60"); // Set initial display to 60 seconds
    ui->userInput->setReadOnly(true); // Disable input until start

    // Load the text to type
    loadTextToType();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::loadTextToType() {
    QString appDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(appDir).filePath("word_bank.txt");
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "File Error", "Unable to open the text file for reading.");
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();
    ui->textDisplay->setPlainText(line); // Ensure 'textDisplay' is a valid QTextEdit in your UI
    file.close();
}

void MainWindow::restartTest() {
    ui->userInput->clear();
    ui->userInput->setReadOnly(false);
    timeLeft = 60;
    ui->timerLabel->setText(QString::number(timeLeft));
    loadTextToType();
    startTimer(); // Ensure timer starts immediately upon restart
}

void MainWindow::startTimer(){
    if (!timer->isActive()) {
        timer->start(1000); // Timer ticks every second
        ui->userInput->setReadOnly(false); // Enable typing
    }
}

void MainWindow::updateTimer(){
    if (timeLeft > 0) {
        timeLeft--;
        ui->timerLabel->setText(QString::number(timeLeft));
    } else {
        timer->stop();
        ui->timerLabel->setText("Time is up!");
        ui->userInput->setReadOnly(true);
        evaluateTyping(); // Call function to evaluate user's typing
    }
}

void MainWindow::evaluateTyping() {
    QString typedText = ui->userInput->toPlainText();
    QString originalText = ui->textDisplay->toPlainText();
    int typedWords = typedText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts).count();
    int originalWords = originalText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts).count();

    double accuracy = 100.0 * typedWords / originalWords;
    QString resultText = QString("You typed %1 words with %2% accuracy.").arg(typedWords).arg(accuracy, 0, 'f', 2);

    QMessageBox::information(this, "Typing Results", resultText);
}

void MainWindow::newDocument() {
    ui->userInput->clear();  // Assuming userInput is the QTextEdit where users type
}

void MainWindow::startTimerIfNotRunning()
{
    if (!timer->isActive()) {
        startTimer();
    }
}
