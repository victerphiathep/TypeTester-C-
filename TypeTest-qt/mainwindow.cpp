#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the QTimer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);

    // Setup connections for buttons and text changes
    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::restartTest);
    connect(ui->userInput, &QTextEdit::textChanged, this, &MainWindow::onUserInputTextChanged);

    // Initial UI setup
    ui->timerLabel->setText("60"); // Set initial display to 60 seconds
    ui->userInput->setReadOnly(true); // Disable input until test starts

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
    QString filePath = QDir(appDir).filePath("word_bank.txt"); // Adjust 'sampletext.txt' to your text file's name

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
    timer->start(1000); // Start the timer
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
        updateWPM(); // Update WPM every second
    } else {
        timer->stop();
        ui->timerLabel->setText("Time is up!");
        ui->userInput->setReadOnly(true);
        evaluateTyping(); // Evaluate the final typing performance
    }
}

void MainWindow::updateWPM() {
    static const QRegularExpression reg("\\s+");
    int elapsedTimeInMinutes = (60 - timeLeft) / 60.0;
    int wordCount = ui->userInput->toPlainText().split(reg, Qt::SkipEmptyParts).count();
    int wpm = elapsedTimeInMinutes > 0 ? wordCount / elapsedTimeInMinutes : 0;

    ui->wpmLabel->setText(QString::number(wpm) + " WPM");
}

void MainWindow::onUserInputTextChanged() {
    QString userInput = ui->userInput->toPlainText();
    QString displayedText = ui->textDisplay->toPlainText();
    QString styledText;

    for (int i = 0; i < displayedText.length(); ++i) {
        if (i < userInput.length() && userInput[i] == displayedText[i]) {
            styledText += "<span style='color: black;'>" + QString(displayedText[i]) + "</span>";
        } else {
            styledText += "<span style='color: gray;'>" + QString(displayedText[i]) + "</span>";
        }
    }

    ui->textDisplay->setHtml(styledText);
}


void MainWindow::evaluateTyping() {
    static const QRegularExpression reg("\\s+");
    QString typedText = ui->userInput->toPlainText();
    QString originalText = ui->textDisplay->toPlainText();
    int typedWords = typedText.split(reg, Qt::SkipEmptyParts).count();
    int originalWords = originalText.split(reg, Qt::SkipEmptyParts).count();

    double accuracy = 100.0 * typedWords / originalWords;
    QString resultText = QString("You typed %1 words with %2% accuracy.").arg(typedWords).arg(accuracy, 0, 'f', 2);

    QMessageBox::information(this, "Typing Results", resultText);
}

void MainWindow::newDocument() {
    ui->userInput->clear();  // Assuming userInput is the QTextEdit where users type
}
