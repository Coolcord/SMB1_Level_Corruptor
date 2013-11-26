#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "binarymanipulator.h"
#include <string>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateLevels()
{
    BinaryManipulator *bm = new BinaryManipulator();
    std::vector<bool> bits;
    for (int i = 0; i < 8; ++i)
    {
        bits.push_back(false);
    }

    bm->WriteByteToBitVector(bits, 0, 0xFF);
    bm->WriteHexDigitToBitVector(bits, 0, 0x0, 0, 1);
    std::string combo = bm->BitVectorToString(bits);

    ui->btnGenerateLevels->setText(combo.c_str());
    delete bm;
    return;
}
