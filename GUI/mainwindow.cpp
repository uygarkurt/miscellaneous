#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <Qstring>
#include <QtMath>
//Uygar Kurt
//25036 uygark@sabanciuniv.edu
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createElements();
    setupLayouts();
    setupConnections();
}

void MainWindow::createElements(){
    zeroButton = new QPushButton("0");
    zeroButton->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    oneButton = new QPushButton("1");
    oneButton->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    clearButton = new QPushButton("Clear");
    clearButton->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    signMagButton = new QPushButton("Sign Magnitude");
    signMagButton->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    resultLabel = new QLabel;
    inputLineEdit = new QLineEdit;
    inputLineEdit->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    inputLineEdit->setReadOnly(true);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setText("Please enter a number to convert");
}

void MainWindow::setupLayouts(){
    outerL = new QVBoxLayout(this); // This is the outer Vertical layout; it will contain
                                    // all the other layouts
    inputR = new QHBoxLayout(this); // The first row; contains the inputLineEdit only
    zeroOneR = new QHBoxLayout(this); // Second row; contains the 0, 1, and Clear buttons
    buttonR = new QHBoxLayout(this); // Third row; contains the Sign Magnitude Button
    labelR = new QHBoxLayout(this); // Fourth row; contains the resultLabel label
    //Adding layouts
    zeroButton->setText("0");
    oneButton->setText("1");
    clearButton->setText("clear");
    signMagButton->setText("Sign Magnitude");
    zeroOneR->addWidget(zeroButton); zeroOneR->addWidget(oneButton); zeroOneR->addWidget(clearButton);
    inputR->addWidget(inputLineEdit);
    buttonR->addWidget(signMagButton);
    resultLabel->setText("Please enter a number to convert");
    labelR->addWidget(resultLabel);
    //Final layouts
    outerL->addLayout(inputR); outerL->addLayout(zeroOneR); outerL->addLayout(buttonR); outerL->addLayout(labelR);
    QWidget *parentWidget = new QWidget;
    parentWidget->setLayout(outerL);
    setCentralWidget(parentWidget);
}

void MainWindow::setupConnections(){
    QObject::connect(oneButton, SIGNAL(clicked()), this, SLOT(writeOne()));
    QObject::connect(zeroButton, SIGNAL(clicked()), this, SLOT(writeZero()));
    QObject::connect(clearButton, SIGNAL(clicked()),this, SLOT(clearInput()));
    QObject::connect(signMagButton, SIGNAL(clicked()), this, SLOT(signConvert()));
}

void MainWindow::writeOne(){
    //Getting text and converting
    QString str;
    str=inputLineEdit->text();
    str+="1";
    inputLineEdit->setText(str);
}

void MainWindow::writeZero(){
    QString str;
    str=inputLineEdit->text();
    str+="0";
    inputLineEdit->setText(str);
}

void MainWindow::clearInput(){
    //Change input with empty string
    inputLineEdit->setText("");
}

void MainWindow::signConvert(){
    int len=(inputLineEdit->text()).length();
    //Appropriate error messages
    if(len==0){
        resultLabel->setText("Please enter a number in the input fields");
    }
    else if(len==1)
    {
        resultLabel->setText("Please enter at least two bits");
    }
    else
    {
        int total=0;
        QString str=inputLineEdit->text();
        //Negative cheks the MSB
        bool negative;
        if(str.at(0)=='1')
            negative=true;
        else
            negative=false;
        //Converting number to decimal
        for(int i=1; i<str.length(); i++)
        {
            if(str.at(i)=='1')
            {
                total+=qPow(2, (str.length()-(i+1)));
            }
        }
        QString nstr=QString::number(total);
        //Checking if it is negative or not
        if(negative)
            nstr="-"+nstr;
        resultLabel->setText(nstr);
    }
}

MainWindow::~MainWindow()
{

}
