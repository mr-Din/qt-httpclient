#pragma once

#include <QMainWindow>

class Ui_MainWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::unique_ptr<Ui_MainWindow> ui;
};
