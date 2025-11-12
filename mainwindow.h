#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <vector>
#include <thread>
#include <chrono>

class QLineEdit;
class QPushButton;
class QVBoxLayout;

struct HookedWindow {
    HWND hwnd;
    std::string title;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void addHookedWindowUI(const HookedWindow& windowInfo);
    QVBoxLayout* m_mainLayout;

    QLineEdit* m_windowTitleInput;
    QPushButton* m_hookButton;

    std::vector<HookedWindow> m_hookedWindows;

private slots:
    void onHookNewWindow();
};
#endif // MAINWINDOW_H
