#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

//----------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
   : QMainWindow(parent,flags)
{
   m_ui.setupUi(this);
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
   QString filename=
           QFileDialog::getOpenFileName(this,"Open File",QString(),"*.png");

   if(filename.length())
   {
       if(m_pixmap.load(filename))
       {
           m_ui.label->setPixmap(m_pixmap);
       }
       else
       {
           QMessageBox::critical( this,"Error",
                                  tr("Could not open %1").arg(filename) );
       }
   }
}

//----------------------------------------------------------------------------
