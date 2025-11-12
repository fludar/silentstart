#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_windowTitleInput = new QLineEdit(this);
    m_windowTitleInput->setPlaceholderText("Enter exact window title...");

    m_hookButton = new QPushButton("Hook New Window", this);
    m_mainLayout = new QVBoxLayout;

    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(m_windowTitleInput);
    topLayout->addWidget(m_hookButton);

    m_mainLayout->addLayout(topLayout);

    m_mainLayout->addStretch();

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(m_mainLayout);
    setCentralWidget(centralWidget);

    connect(m_hookButton, &QPushButton::clicked, this, &MainWindow::onHookNewWindow);

    setWindowTitle("Silent Start");
    resize(400, 200);
}

MainWindow::~MainWindow(){}


void MainWindow::onHookNewWindow()
{
    std::string title = m_windowTitleInput->text().toStdString();
    if (title.empty()) {
        return;
    }

    HWND hwnd = FindWindowA(NULL, title.c_str());

    if (hwnd == NULL) {
        qDebug() << "Window not found:" << QString::fromStdString(title);
        return;
    }

    qDebug() << "Successfully hooked window:" << QString::fromStdString(title);

    HookedWindow newWindow = {hwnd, title};
    m_hookedWindows.push_back(newWindow);

    addHookedWindowUI(newWindow);

    m_windowTitleInput->clear();
}


void MainWindow::addHookedWindowUI(const HookedWindow& windowInfo)
{
    QLabel* titleLabel = new QLabel(QString::fromStdString(windowInfo.title), this);
    QPushButton* toggleButton = new QPushButton("Toggle Visibility", this);

    QHBoxLayout* rowLayout = new QHBoxLayout;
    rowLayout->addWidget(titleLabel);
    rowLayout->addStretch();
    rowLayout->addWidget(toggleButton);

    HWND hwndToToggle = windowInfo.hwnd;
    connect(toggleButton, &QPushButton::clicked, this, [hwndToToggle]() {
        bool isVisible = IsWindowVisible(hwndToToggle);
        ShowWindow(hwndToToggle, isVisible ? SW_HIDE : SW_SHOW);
        qDebug() << "Toggled visibility for HWND:" << hwndToToggle;
    });

    m_mainLayout->insertLayout(m_mainLayout->count() - 1, rowLayout);
}


