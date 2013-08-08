#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QtGlobal>
#include <QDebug>
#include <QGraphicsScene>

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

   qApp->processEvents();

   if(filename.length())
   {
       if(m_pixmap.load(filename))
       {
           QGraphicsScene *scene = new QGraphicsScene(m_ui.graphicsView);
           scene->setSceneRect(m_ui.graphicsView->rect());
           scene->addPixmap(m_pixmap);
           m_ui.graphicsView->setScene(scene);

           statusBar()-> showMessage(tr("Loaded file %0 alpha channel").arg(m_pixmap.hasAlphaChannel()?tr("with"):tr("without")));

           const QImage &bmp = m_pixmap.toImage();

           statusBar()-> showMessage(tr("Processing..."));

           for(int y=0; y<bmp.height(); y++)
           {
               QRgb *row = (QRgb*)bmp.scanLine(y);

               for(int x=0;x<bmp.width(); x++)
               {
                   if(qAlpha(row[x]) > 0)
                   {
                       bool merged=false;

                       QRect *newRect = new QRect(x-1,y-1,2,2);

                       QMutableListIterator<QRect*> it(m_rects);
                       while(it.hasNext())
                       {
                           QRect *r = it.next();

                           //merge if neighbor to exiting rectangle
                           if( r->intersects(*newRect) )
                           {
                               *newRect = r->united(*newRect);
                               delete r;
                               it.remove();
                           }
                       }

                       m_rects.append(newRect);
                   }
               }
           }

           statusBar()-> showMessage(tr("Done. Found %1 rectangles").arg(m_rects.size()));
           foreach(QRect *r,m_rects) {
               scene->addRect(QRectF(*r));
           }
       }
       else
       {
           QMessageBox::critical( this,"Error",
                                  tr("Could not open %1").arg(filename) );
       }
   }
}

//----------------------------------------------------------------------------

//bool MainWindow::findSprites( const QPixmap &pixmap )
//{
//    //convert to opencv convert to grayscale: set all pixels with zero alpha to black
//
//
//}

//----------------------------------------------------------------------------
