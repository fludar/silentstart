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
std::vector<HWND> hwnds;
void MainWindow::on_hookButton_clicked()
{
    std::string s = ui->windowText->text().toStdString();
    const char* window = s.c_str();
    HWND hwnd = FindWindowA(NULL, window);
    if(hwnd == NULL){
        ui->hookButton->setText("Error");
    }
    else {
        m_hwnds.push_back(hwnd);
    }

}
