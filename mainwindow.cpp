#include "mainwindow.h"

#include <QFileDialog>

//----------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
   : QMainWindow(parent,flags)
{
   ui.setupUi(this);
}

//----------------------------------------------------------------------------

MainWindow::~MainWindow()
{
}

//----------------------------------------------------------------------------

void MainWindow::on_actionExit_triggered(bool checked)
{
   close();
}

//----------------------------------------------------------------------------

void MainWindow::on_actionOpen_triggered(bool checked)
{
   QFileDialog::getOpenFileName();
}

//----------------------------------------------------------------------------
