#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>
#include <QRegularExpression>

#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Status {
        None,
        Loaded,
        Saved,
        Deleted
    };

    static const QRegularExpression statusBarRegExp;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;

    Game game;
    QListWidget *savedGamesView;

    void updateSavedGamesView();
    QString getSelectedId() const;
    void updateStatusbar(const Status &status);
    QPair<Status, int> statusBarState() const;
};
#endif // MAINWINDOW_H
