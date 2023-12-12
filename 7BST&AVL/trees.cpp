#pragma once

#include "trees.h"
#include <QFileDialog>
#include <QTextStream>
#include<iostream>
#include <QtWidgets>

trees::trees(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this); 
    Treemode = 0;
    BSTtreeObject = new BST();
    AVLtreeObject = new AVL();
    connect(ui.ReadFileButton, &QPushButton::clicked,
        this, &trees::OpenFile_Clicked);
    connect(ui.CreateBSTButton, &QPushButton::clicked,
        this, &trees::CreateBST_Clicked);
    connect(ui.CreateAVLButton, &QPushButton::clicked,
        this, &trees::CreateAVL_Clicked);
    connect(ui.ShowTreeButton, &QPushButton::clicked,
        this, &trees::ShowTrees);
    connect(ui.ShowArrayButton, &QPushButton::clicked,
        this, &trees::ArrayShow_Clicked);
    connect(ui.LNRbutton, &QPushButton::clicked,
        this, &trees::showLNR);
    connect(ui.InsertNewButton, &QPushButton::clicked,
        this, &trees::AddNode_Clicked);
    connect(ui.DeleteButton, &QPushButton::clicked,
        this, &trees::DeleteNode_Clicked);
    connect(ui.CalAvgButton, &QPushButton::clicked,
        this, &trees::ASL_Clicked);
}

trees::~trees()
{}

class TreeVisualizationWidget : public QWidget {
public:
    TreeVisualizationWidget(QWidget* parent = nullptr) : QWidget(parent), tree(nullptr) {
    }

    void setTree(BST* tree) {
        this->tree = tree;
        update();
    }

protected:
    void drawTree(QPainter& painter, node* currentNode, int x, int y, int radius, int xOffset, int yOffset) {
        if (!currentNode) return;

        // Calculate the width of the left and right subtrees
        int leftSubtreeWidth = getSubtreeWidth(currentNode->left);
        int rightSubtreeWidth = getSubtreeWidth(currentNode->right);

        // Draw the current node
        painter.drawEllipse(x - radius, y - radius, 2 * radius, 2 * radius);
        painter.drawText(x - radius, y - radius, 2 * radius, 2 * radius, Qt::AlignCenter, QString::number(currentNode->data));

        // Draw the left child
        if (currentNode->left) {
            int xLeft = x - xOffset - leftSubtreeWidth / 2;
            int yLeft = y + yOffset;
            painter.drawLine(x, y + radius, xLeft, yLeft - radius);
            drawTree(painter, currentNode->left, xLeft, yLeft, radius, xOffset / 2, yOffset);
        }

        // Draw the right child
        if (currentNode->right) {
            int xRight = x + xOffset + rightSubtreeWidth / 2;
            int yRight = y + yOffset;
            painter.drawLine(x, y + radius, xRight, yRight - radius);
            drawTree(painter, currentNode->right, xRight, yRight, radius, xOffset / 2, yOffset);
        }
    }

    int getSubtreeWidth(node* currentNode) {
        if (!currentNode) return 0;
        int leftWidth = getSubtreeWidth(currentNode->left);
        int rightWidth = getSubtreeWidth(currentNode->right);
        return leftWidth + rightWidth + 40;
    }

    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);
        if (!tree) return;

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        int radius = 20; // Radius of the circle representing each node
        int xOffset = 50; // Horizontal distance between nodes
        int yOffset = 60; // Vertical distance between nodes
        drawTree(painter, tree->root, width() / 2, 50, radius, xOffset, yOffset);
    }

private:
    BST* tree;
};

// 读取文件输入
void trees::OpenFile_Clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"),
        "C:/Users/origin/Desktop",
        tr("Files (*.txt)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream in(&file);
        QString text = in.readAll();
        ui.plainTextEdit->setPlainText(text);
        file.close();
    }
}

void trees::CreateBST_Clicked() {
    Treemode = 0;
    delete BSTtreeObject;
    BSTtreeObject = new BST();
    QString text = ui.plainTextEdit->toPlainText();
    QStringList textList = text.split(" ");
    std::vector<int> nums(BSTtreeObject->MAX_NODES);
    int index = 0;
    for (QString s : textList) {
        nums[index++] = s.toInt();
    }
    nums.resize(index);
    BSTtreeObject->generateBST(nums);

    TreeVisualizationWidget* BSTWidget = new TreeVisualizationWidget();
    BSTWidget->setAttribute(Qt::WA_DeleteOnClose, true);
    BSTWidget->setTree(BSTtreeObject);
    BSTWidget->setMinimumSize(1200, 800);
    BSTWidget->show();
}

void trees::CreateAVL_Clicked() {
    Treemode = 1;
    delete AVLtreeObject;
    AVLtreeObject = new AVL();
    QString text = ui.plainTextEdit->toPlainText();
    QStringList textList = text.split(" ");
    std::vector<int> nums(AVLtreeObject->MAX_NODES);
    int index = 0;
    for (QString s : textList) {
        nums[index++] = s.toInt();
    }
    nums.resize(index);
    AVLtreeObject->generateAVL(nums);

    TreeVisualizationWidget* AVLWidget = new TreeVisualizationWidget();
    AVLWidget->setAttribute(Qt::WA_DeleteOnClose, true);
    AVLWidget->setTree(AVLtreeObject);
    AVLWidget->setMinimumSize(1200, 800);
    AVLWidget->show();
}

void trees::ShowTrees() {
    if (!Treemode) {
        TreeVisualizationWidget* BSTWidget = new TreeVisualizationWidget();
        BSTWidget->setTree(BSTtreeObject);
        BSTWidget->setAttribute(Qt::WA_DeleteOnClose, true);
        BSTWidget->setMinimumSize(1200, 800);
        BSTWidget->show();
    }
    else {
        TreeVisualizationWidget* AVLWidget = new TreeVisualizationWidget();
        AVLWidget->setTree(AVLtreeObject);
        AVLWidget->setAttribute(Qt::WA_DeleteOnClose, true);
        AVLWidget->setMinimumSize(1200, 800);
        AVLWidget->show();
    }
}

class ArrayElementWidget : public QWidget {
public:
    ArrayElementWidget(int value, int index, QWidget* parent = nullptr) : QWidget(parent), value(value), index(index) {}

protected:
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        // 绘制背景框
        painter.drawRect(0, 0, width() - 1, height() - 1);

        // 绘制元素值
        if (value != -1) {
            painter.drawText(rect(), Qt::AlignCenter, QString::number(value));
        }

        // 如果元素是 -1，绘制一个倒着的V表示没有
        if (value == -1) {
            int vSize = 10;
            painter.drawLine(width() / 2, 0.3 * height() , 0.2*width(), 0.8*height());
            painter.drawLine(width() / 2, 0.3 * height(),  0.8*width(), 0.8*height());
        }

        // 在底部标注索引
        painter.drawText(0, height(), width(), 20, Qt::AlignCenter, QString::number(index));
    }

private:
    int value;
    int index;
};

class ArrayDisplayWindow : public QWidget {
public:
    ArrayDisplayWindow(const std::vector<int>& array, QWidget* parent = nullptr)
        : QWidget(parent), array(array) {
        setupUI();
        setFixedSize(800, 50 + 50 * (array.size() / 10));
    }

private:
    void setupUI() {
        QGridLayout* layout = new QGridLayout(this);

        int elementsPerRow = 10; // 每行元素个数
        int currentIndex = 0;

        while (currentIndex < array.size()) {
            for (int i = 0; i < elementsPerRow && currentIndex < array.size(); ++i) {
                int value = array[currentIndex];
                ArrayElementWidget* elementWidget = new ArrayElementWidget(value, currentIndex, this);
                layout->addWidget(elementWidget, currentIndex / elementsPerRow, currentIndex % elementsPerRow);

                ++currentIndex;
            }
        }
    }

private:
    std::vector<int> array;
};

void trees::ArrayShow_Clicked() {
    std::vector<int> elems;
    elems.clear();
    if (!Treemode) {
        BSTtreeObject->levelOrderTraversal(BSTtreeObject->root, elems);
    }
    else {
        AVLtreeObject->levelOrderTraversal(AVLtreeObject->root, elems);
    }
    ArrayDisplayWindow* displayWindow = new ArrayDisplayWindow(elems);
    displayWindow->setAttribute(Qt::WA_DeleteOnClose, true);
    displayWindow->show();
}

void trees::showLNR() {
    std::vector<int> array;
    if (!Treemode) {
        array = BSTtreeObject->LNRTree();
    }
    else {
        array = AVLtreeObject->LNRTree();

    }
    QString arrayString = array.empty() ? "Empty Array" : QString::number(array[0]);

    for (size_t i = 1; i < array.size(); ++i) {
        arrayString += " " + QString::number(array[i]);
    }

    QMessageBox::information(this, "中序遍历", arrayString);
}

void trees::AddNode_Clicked() {
        QString inputText = ui.InsertNewEdit->text();
        bool conversionOK;
        int value = inputText.toInt(&conversionOK);
        if (conversionOK) {
            if (!Treemode) {
                BSTtreeObject->insertNode(value);
                TreeVisualizationWidget* BSTWidget = new TreeVisualizationWidget();
                BSTWidget->setAttribute(Qt::WA_DeleteOnClose, true);
                BSTWidget->setTree(BSTtreeObject);
                BSTWidget->setMinimumSize(1200, 800);
                BSTWidget->show();
            }
            else {
                auto p = AVLtreeObject->insertNode(value);
                TreeVisualizationWidget* AVLWidget = new TreeVisualizationWidget();
                AVLWidget->setTree(AVLtreeObject);
                AVLWidget->setAttribute(Qt::WA_DeleteOnClose, true);
                AVLtreeObject->refreshHeight(AVLtreeObject->root);
                auto unBalance = AVLtreeObject->findUnbalanceNode(p);
                if (unBalance != nullptr) {
                    if (unBalance == AVLtreeObject->root) {
                        AVLtreeObject->root = AVLtreeObject->balanceAndRotate(unBalance);
                    }
                    else {
                        auto  tmp = unBalance->parent;
                        unBalance = AVLtreeObject->balanceAndRotate(unBalance);
                        unBalance->data > tmp->data ? tmp->right = unBalance : tmp->left = unBalance;
                    }
                }   
                AVLWidget->setMinimumSize(1200, 800);
                    AVLWidget->show();
             }
        }
        else {
            QMessageBox::information(this, "Error", "非法输入");
         }
}

void trees::DeleteNode_Clicked() {
    QString inputText = ui.DeleteEdit->text();
    bool conversionOK;
    int value = inputText.toInt(&conversionOK);
    if (conversionOK) {
        if (!Treemode) {
            auto t = BSTtreeObject->deleteNode(value);
            if (t == nullptr) {
                QMessageBox::information(this, "Error", "找不到对象");
                return;
            }     
            TreeVisualizationWidget* BSTWidget = new TreeVisualizationWidget();
            BSTWidget->setAttribute(Qt::WA_DeleteOnClose, true);
            BSTWidget->setTree(BSTtreeObject);
            BSTWidget->setMinimumSize(1200, 800);
            BSTWidget->show();  
        }
        else {
            auto t = AVLtreeObject->deleteNode(value);
            if (t == nullptr) {
                QMessageBox::information(this, "Error", "找不到对象");
                return;
            }
            AVLtreeObject->refreshHeight(AVLtreeObject->root);
            auto unBalance = AVLtreeObject->findUnbalanceNode(t);
            if (unBalance != nullptr) {
                if (unBalance == AVLtreeObject->root) {
                    AVLtreeObject->root = AVLtreeObject->balanceAndRotate(unBalance);
                }
                else {
                    auto  tmp = unBalance->parent;
                    unBalance = AVLtreeObject->balanceAndRotate(unBalance);
                    unBalance->data > tmp->data ? tmp->right = unBalance : tmp->left = unBalance;
                }
            }
            TreeVisualizationWidget* AVLWidget = new TreeVisualizationWidget();
            AVLWidget->setTree(AVLtreeObject);
            AVLWidget->setAttribute(Qt::WA_DeleteOnClose, true);
            AVLWidget->setMinimumSize(1200, 800);
            AVLWidget->show();
        }
    }  
    else {
        QMessageBox::information(this, "Error", "非法输入");
    }
}

void trees::ASL_Clicked() {
    float l;
    if (!Treemode) {
         l = BSTtreeObject->getASL();
    }
    else {
         l = AVLtreeObject->getASL();
    }
    QString message = QString("平均查找长度是: %1").arg(l);
    QMessageBox::information(this, "Information", message);
}