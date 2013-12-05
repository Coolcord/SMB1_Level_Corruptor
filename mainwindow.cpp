#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include "binarymanipulator.h"
#include "smb1levelgenerator.h"
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
    SMB1LevelGenerator *smb1 = new SMB1LevelGenerator();
    //std::string romLocation = "C:\\Users\\Cord\\Desktop\\Level-Headed Test Files\\Super Mario Bros. Hacked.nes";
    std::string romLocation = "/mnt/Seven/Users/Cord/Desktop/Level-Headed Test Files/Super Mario Bros. Hacked.nes";

    //std::basic_fstream<unsigned char> file;
    std::fstream file;
    file.open(romLocation.c_str(), std::ios::in | std::ios::out | std::ios::binary);

    if (!smb1->isROMValid(file))
    {
        QMessageBox::critical(this, "Error!", "This is NOT an NES ROM");
        return;
    }

    if (smb1->RandomizeAllLevels(file))
    {
        QMessageBox::information(this, "Success!", "Changes made!");
    }
    else
    {
        QMessageBox::critical(this, "Error!", "Something went wrong...");
    }

    delete smb1;
}
