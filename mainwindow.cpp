#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// void MainWindow::on_pushButtonRotate_clicked()
// {
// //    ui->labelZbuffer->rotate_objects(5.9f, 5.9f, 0.9f);
// }

void MainWindow::on_pushButtonRotateX_clicked()
{
    ui->labelZbuffer->rotate_objects_X(1.0f);
}


void MainWindow::on_pushButtonRotateY_clicked()
{
    ui->labelZbuffer->rotate_objects_Y(1.0f);
}


void MainWindow::on_pushButtonRotatez_clicked()
{
    ui->labelZbuffer->rotate_objects_Z(1.0f);
}


void MainWindow::on_autoRotate_checkStateChanged(const Qt::CheckState &arg1)
{
    if (ui->autoRotate->isChecked()) {
        ui->labelZbuffer->rotate_objects(0.001f, 0.001f, 0.001f);
    }
}

