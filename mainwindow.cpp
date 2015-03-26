#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

#include "binarymanipulator.h"
#include "smb1levelgenerator.h"
#include <string>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMessageBox::information(this, "SMB1 Level Corruptor", "This application is a prototype for a random level generator "
                             "for Super Mario Bros. 1 on the NES (which is now known as Level-Headed). It messes with the level objects "
                             "and enemies to demonstrate that it is feasible to randomly generate levels.");
    QMessageBox::information(this, "SMB1 Level Corruptor", "Keep in mind that this simply randomizes all of the objects and/or enemies "
                             "in the game. It may create scenarios that are impossible to complete, but the game should never crash.");
    QMessageBox::information(this, "SMB1 Level Corruptor", "You'll need to provide an unmodified \"Super Mario Bros. (JU) [!].nes\" ROM. "
                             "Note that the provided file will be modified, so make a backup before using this!");
    QMessageBox::warning(this, "SMB1 Level Corruptor", "Please note that since this is a prototype, there is not much error checking. "
                             "It simply demonstrates that this can be done. Use it with caution!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGenerate_clicked()
{
    bool randomizeObjects = this->ui->cbObjects->isChecked();
    bool randomizeEnemies = this->ui->cbEnemies->isChecked();

    //Handle the case with nothing to do
    if (!randomizeObjects && !randomizeEnemies)
    {
        QMessageBox::critical(this, "Error!", "Try checking at least one option!");
        return;
    }

    SMB1LevelGenerator smb1;
    QString qROMLocation = QFileDialog::getOpenFileName(this, "Open a SMB1 ROM", QApplication::applicationDirPath(), "NES ROMs (*.nes)");
    if (qROMLocation == NULL || qROMLocation.isEmpty())
    {
        return; //nothing to do... the user canceled
    }
    std::string romLocation = qROMLocation.toStdString();

    std::fstream file;
    file.open(romLocation.c_str(), std::ios::in | std::ios::out | std::ios::binary);

    if (!smb1.isROMValid(file))
    {
        QMessageBox::critical(this, "Error!", "This is NOT an NES ROM");
        return;
    }

    if (smb1.RandomizeAllLevels(file, randomizeObjects, randomizeEnemies))
    {
        QMessageBox::information(this, "Success!", "Changes made!");
    }
    else
    {
        QMessageBox::critical(this, "Error!", "Something went wrong...");
    }
}
