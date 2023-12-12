#pragma once

#include "trees.h"
#include <QtWidgets/QApplication>
#include "linked_bst_avl.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    trees w;
    w.show();
    return a.exec();
}
