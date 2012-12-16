#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ui_mainwindow.h"
#include "downloadmanager.h"
#include "about.h" /// aboutdialog

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui
{
class MainWindow;
}

QT_BEGIN_NAMESPACE
class AboutDialog;
class QAction;
class QMenu;
class QStringListModel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    //tray
    /**
     * @brief showHide
     */
    void showHide(QSystemTrayIcon::ActivationReason);

    /**
     * @brief slot_aboutOpenSite
     */
    void slot_aboutOpenSite();

    /**
     * @brief slot_selectOutputFolder
     */
    void slot_selectOutputFolder();

    /**
     * @brief slot_download
     */
    void slot_download();

    /**
     * @brief slot_addUrlFromFile
     */
    void slot_addUrlFromFile();

    /**
     * @brief slot_addUrlToList
     */
    void slot_addUrlToList();


private:
    Ui::MainWindow *ui;

    //about
    AboutDialog *about;    // about dialog

    //tray
    QSystemTrayIcon *trIcon;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    DownloadManager m_manager;

    /**
     * @brief createConnects
     */
    void createConnects();
    /**
     * @brief createTrayIcon
     */
    void createTrayIcon();
    /**
     * @brief createActions
     */
    void createActions();
    /**
     * @brief debug
     */
    void debug();

    void addUrlFromFile(const QString f_fileName);


};

#endif // MAINWINDOW_H
