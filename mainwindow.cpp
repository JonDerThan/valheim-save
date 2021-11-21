#include "mainwindow.h"
#include "ui_mainwindow.h"

const QRegularExpression MainWindow::statusBarRegExp{"^(\\w+)! \\(x(\\d+)\\)$"};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    savedGamesView = this->findChild<QListWidget*>("savedGamesView");
    updateSavedGamesView();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_saveButton_clicked()
{
    game.saveGame();
    updateSavedGamesView();
    updateStatusbar(Saved);
}


void MainWindow::on_loadButton_clicked()
{
    const QString &id = getSelectedId();

    if (id.length() != 0) {
        game.loadGame(id);
        updateStatusbar(Loaded);
    }
}


void MainWindow::on_deleteButton_clicked()
{
    const QString &id = getSelectedId();

    if (id.length() != 0) {
        QMessageBox messageBox;
        messageBox.setText("Do you really want to delete this save file?");
        messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        const int &ret = messageBox.exec();

        if (ret == QMessageBox::Yes) {
            game.deleteGame(id);
            updateSavedGamesView();
            updateStatusbar(Deleted);
        }
    }
}

void MainWindow::updateSavedGamesView()
{
    const QStringList savedGames = game.getSavedGames();

    savedGamesView->clear();

    for (const QString &id: savedGames) {
        QDateTime time;
        time.setSecsSinceEpoch(id.toULongLong());

        QListWidgetItem *item = new QListWidgetItem(time.toString("yyyy-MM-dd HH:mm:ss"), savedGamesView);
        item->setData(Qt::UserRole, id);
    }
}

QString MainWindow::getSelectedId() const
{
    QList<QListWidgetItem*> list = savedGamesView->selectedItems();

    if (list.length() < 1) return "";

    else return list.at(0)->data(Qt::UserRole).toString();
}

void MainWindow::updateStatusbar(const Status &status)
{
    QPair<MainWindow::Status, int> currentStatus = this->statusBarState();

    int count = 1;
    if (status == currentStatus.first) count += currentStatus.second;
    QString countStr = QString::fromStdString(std::to_string(count));

    // TODO: optimizie this: qmap<qstring, status>
    switch (status) {
    case Loaded:
        statusBar()->showMessage("Loaded! (x" + countStr + ")");
        break;

    case Saved:
        statusBar()->showMessage("Saved! (x" + countStr + ")");
        break;

    case Deleted:
        statusBar()->showMessage("Deleted! (x" + countStr + ")");
        break;

    case None:

        break;
    }
}

QPair<MainWindow::Status, int> MainWindow::statusBarState() const
{
    QRegularExpressionMatch match = statusBarRegExp.match(statusBar()->currentMessage());

    if (match.hasMatch()) {
        // TODO: optimizie this: qmap<qstring, status>
        int count = match.captured(2).toInt();

        if (match.captured(1) == "Loaded") {
            return QPair<Status, int>{Loaded, count};
        }

        else if (match.captured(1) == "Saved") {
            return QPair<Status, int>{Saved, count};
        }

        else if (match.captured(1) == "Deleted") {
            return QPair<Status, int>{Deleted, count};
        }

        else return QPair<Status, int>{None, 0};
    }

    else return QPair<Status, int>{None, 0};
}

