#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // void on_pushButtonRotate_clicked();

    void on_pushButtonRotateX_clicked();

    void on_pushButtonRotateY_clicked();

    void on_pushButtonRotatez_clicked();

    void on_autoRotate_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
