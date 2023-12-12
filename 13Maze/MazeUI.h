#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MazeUI.h"

class MazeUI : public QMainWindow
{
    Q_OBJECT

public:
    MazeUI(QWidget *parent = nullptr);
    ~MazeUI();
    void ButtonClick();
    void Button2Click();

private:
    Ui::MazeUIClass ui;
};
