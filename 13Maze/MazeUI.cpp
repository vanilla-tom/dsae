#pragma once
#include "MazeUI.h"
#include "maze_head.h"
#include <QFileDialog>
#include <vector>
#include <QPainter>
#include <QtWidgets>

MazeUI::MazeUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.pushButton, &QPushButton::clicked,
        this, &MazeUI::ButtonClick);
    connect(ui.pushButton_2, &QPushButton::clicked,
        this, &MazeUI::Button2Click);
}

MazeUI::~MazeUI()
{}

class MazeWidget : public QWidget {
public:
    MazeWidget(const std::vector<std::vector<int>>& maze, QWidget* parent = nullptr)
        : QWidget(parent), maze(maze) {}

protected:
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);

        QPainter painter(this);

        // 设置方块大小
        int blockSize = 20;

        // 绘制迷宫
        for (int i = 0; i < maze.size(); ++i) {
            for (int j = 0; j < maze[i].size(); ++j) {
                if (maze[i][j] == 1) {
                    painter.fillRect(i * blockSize, j * blockSize, blockSize, blockSize, Qt::black);
                }
                if (maze[i][j] == 3) {
                    painter.fillRect(i * blockSize, j * blockSize, blockSize, blockSize, Qt::red);
                }
            }
        }
    }
private:
    std::vector<std::vector<int>> maze;
};

void output(node* n, std::vector<std::vector<int> >& map) {
    if (n->parent != nullptr) {
        output(n->parent, map);
    }
    map[n->x][n->y] = 3;
}

void MazeUI::ButtonClick() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"),
        "C:/Users/origin/Desktop",
        tr("Files (*.txt)"));
    auto s = fileName.toStdString();
    std::vector<std::vector<int> > map(0, std::vector<int>(0));
    readMap(map, s);
    int mapHeight = map.size();
    int mapWidth = map[0].size();
    node* path = astar(map, 1, 1, mapWidth - 2, mapHeight - 2);
    if (path == nullptr) {
        QMessageBox::information(this, "Error", "找不到路");
    }
    else {
        output(path,map);
    }
    MazeWidget* w =  new MazeWidget(map);
    w->setWindowTitle("Maze");
    w->resize(20*mapWidth+20, 20*mapHeight+20);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
}

void MazeUI::Button2Click() {
    std::vector<std::vector<int> > map(0, std::vector<int>(0));
    QString width = ui.lineEdit->text();
    QString height = ui.lineEdit_2->text();
    bool conversionOK1;
    bool conversionOK2;
    int w = width.toInt(&conversionOK1);
    int h = height.toInt(&conversionOK2);
    if (!(conversionOK1 && conversionOK2)) {
        QMessageBox::information(this, "Error", "输入错误");
        return;
    }
    randomMap(map, h,w);
    int mapHeight = map.size();
    int mapWidth = map[0].size();
    node* path = astar(map, 1, 1, mapWidth - 2, mapHeight - 2);
    if (path == nullptr) {
        QMessageBox::information(this, "Error", "找不到路");
    }
    else {
        output(path, map);
    }
    MazeWidget* widget = new MazeWidget(map);
    widget->setWindowTitle("Maze");
    widget->resize(20 * mapWidth + 20, 20 * mapHeight + 20);
    widget->setAttribute(Qt::WA_DeleteOnClose, true);
    widget->show();
}