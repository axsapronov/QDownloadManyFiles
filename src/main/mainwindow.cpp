/*
  The basis for creating an application
  (QMainwindow)

  Tray + translate + about dialog + mainwindow

  Author: Sapronov Alexander
  E-mail: sapronov.alexander92@gmail.com
  */



#include "defines.h" /// defines
#include "mainwindow.h" ///
#include "debughelper.h"
#include "common.h"

#include <QDesktopWidget> /// moved to center
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QStringListModel>
#include <QTimer>

#include <QTableWidget>
#include <QCheckBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    about(new AboutDialog(this))
{
    ui->setupUi(this);

    createActions(); // create action for tray
    createTrayIcon(); // add actionts to tray menu
    createConnects(); // moved func
    trIcon->show();  //display tray


    /// moved to center desktop
    QRect rect = QApplication::desktop()->availableGeometry(this);
    this->move(rect.width() / 2 - this->width() / 2,
               rect.height() / 2 - this->height() / 2);
    /// maximized
    //    this->showMaximized();

//    debug();

}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//------------------------------------------------------------------------------
void MainWindow::debug()
{

}
//------------------------------------------------------------------------------
void MainWindow::createConnects()
{
    //tray
    connect(trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showHide(QSystemTrayIcon::ActivationReason)));

    // menu file
    connect(ui->actionFileQuit, SIGNAL(triggered()), this, SLOT(close()));

    // menu about
    connect(ui->actionAboutAbout, SIGNAL(triggered()), about, SLOT(show()));
    connect(ui->actionAboutAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionAboutHomeSite, SIGNAL(triggered()), this, SLOT(slot_aboutOpenSite()));

    // buttons
    connect(ui->pBBrowseOutputFolder, SIGNAL(clicked()), SLOT(slot_selectOutputFolder()));
    connect(ui->pBDownload, SIGNAL(clicked()), SLOT(slot_download()));
    connect(ui->pBAddUrlsFromFile, SIGNAL(clicked()), SLOT(slot_addUrlFromFile()));
    connect(ui->pBAddUrl, SIGNAL(clicked()), SLOT(slot_addUrlToList()));
}
//------------------------------------------------------------------------------
void MainWindow::showHide(QSystemTrayIcon::ActivationReason r)
{
    if (r == QSystemTrayIcon::Trigger)
    {
        if ( !this->isVisible() )
        {
            this->show();
        }
        else
        {
            this->hide();
        }
    }
}
//------------------------------------------------------------------------------
void MainWindow::createTrayIcon()
{
    trIcon = new QSystemTrayIcon();  //init
    trIcon->setIcon(QIcon(":/images/img.png"));  //set ico

    trayIconMenu = new QMenu(this);  // create menu
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trIcon->setContextMenu(trayIconMenu); //set menu
}
//------------------------------------------------------------------------------
void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("&Hide"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("&Expand"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("Q&uit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
}
//------------------------------------------------------------------------------
void MainWindow::slot_aboutOpenSite()
{
    QDesktopServices::openUrl(QUrl(GL_WEB_SITE));
}
//------------------------------------------------------------------------------
void MainWindow::slot_selectOutputFolder()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this
                                                          , tr("Select input folder")
                                                          , ""
                                                          , options);
    if (!directory.isEmpty())
        ui->LEOutputFolder->setText(directory);
}
//------------------------------------------------------------------------------
void MainWindow::slot_download()
{
    myDebug() << "start download";
}
//------------------------------------------------------------------------------
void MainWindow::slot_addUrlToList()
{
    myDebug() << "add url from LE to list";
//    ui->LEInputUrl->text();
}
//------------------------------------------------------------------------------
void MainWindow::slot_addUrlFromFile()
{
//    myDebug() << "add urls from file";
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Select file"),
                                "",
                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
    {
        addUrlFromFile(fileName);
    }
}
//------------------------------------------------------------------------------
void MainWindow::addUrlFromFile(const QString f_fileName)
{
    QString t_text = getTextFromHtmlFile(f_fileName);
}
//------------------------------------------------------------------------------

