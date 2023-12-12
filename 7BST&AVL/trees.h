#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_trees.h"
#include "linked_BST_AVL.h"

class trees : public QMainWindow
{
    Q_OBJECT

public:
    trees(QWidget* parent = nullptr); 
    ~trees();
    void OpenFile_Clicked();
    void CreateBST_Clicked();
    void CreateAVL_Clicked();
    void ShowTrees();
    void ArrayShow_Clicked();
    void showLNR();
    void AddNode_Clicked();
    void DeleteNode_Clicked();
    void ASL_Clicked();

private:
    Ui::treesClass ui;
    BST *BSTtreeObject;
    AVL *AVLtreeObject;
    bool Treemode; // 0 BST ;1 AVL
};