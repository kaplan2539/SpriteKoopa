#include <QPixmap>

#include <ui_mainwindow.h>

//----------------------------------------------------------------------------

class MainWindow
   : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow(QWidget *parent=0, Qt::WindowFlags flags =0);
   virtual ~MainWindow();

public slots:
   // Should be auto-connected, gived the right naming & parameter signature:
   void on_actionExit_triggered( bool checked = false );
   void on_actionOpen_triggered( bool checked = false );

private:
   Ui_MainWindow m_ui;

   QPixmap m_pixmap;
};
