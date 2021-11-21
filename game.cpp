#include "game.h"

// const QString Game::defaultGamePath{"%USERPROFILE%\\AppData\\LocalLow\\IronGate\\Valheim\\"};
// const QString Game::defaultSavePath{"%APPDATA%\\ValheimSavedGames\\"};
// const QString Game::defaultGamePath{QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/AppData/LocalLow/IronGate/Valheim"};
// const QString Game::defaultSavePath{QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(0)};

Game::Game(QObject *parent) :
    QObject{parent},

    defaultGamePath{QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/AppData/LocalLow/IronGate/Valheim"},
    defaultSavePath{QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(0)},

    gamePath{defaultGamePath},
    savePath{defaultSavePath}
{

}

void Game::saveGame() const
{
    QDir savedGameDir{createNewPathName()};

    // wait until folder doesn't exists anymore
    while (savedGameDir.exists()) {
        savedGameDir = createNewPathName();
    }

    copyFolder(gamePath, savedGameDir.path());
}

void Game::loadGame(const QString &id) const
{
    QDir savedGameDir{savePath + "/" + id};

    if (!savedGameDir.exists()) throw std::runtime_error{"Saved game folder couldn't be found! " + savedGameDir.path().toStdString()};

    copyFolder(savedGameDir.path(), gamePath);
}

void Game::deleteGame(const QString &id) const
{
    QDir savedGameDir{savePath + "/" + id};

    if (!savedGameDir.exists()) throw std::runtime_error{"Saved game folder couldn't be found! " + savedGameDir.path().toStdString()};

    savedGameDir.removeRecursively();
}

QStringList Game::getSavedGames() const
{
    QDir savedGamesDir{savePath};

    savedGamesDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    savedGamesDir.setSorting(QDir::Name | QDir::Reversed); // todo maybe change

    return savedGamesDir.entryList();
}

const QString &Game::getGamePath() const
{
    return gamePath;
}

void Game::setGamePath(const QString &newGamePath)
{
    gamePath = newGamePath;
}

const QString &Game::getSavePath() const
{
    return savePath;
}

void Game::setSavePath(const QString &newSavePath)
{
    savePath = newSavePath;
}

QString Game::createNewPathName() const
{
    return savePath + "/" + QString::fromStdString(std::to_string(QDateTime::currentSecsSinceEpoch()));
}

void Game::copyFolder(const QString &src, const QString &dest) const
{
    QDir destDir{dest};
    if (!destDir.exists()) QDir{}.mkpath(dest);

    else {
        // delete elements of destination folder first
        destDir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

        for (const QFileInfo &entry: destDir.entryInfoList()) {
            if (entry.isFile()) {
                QFile{entry.filePath()}.remove();
            }

            else if (entry.isDir()) {
                QDir{entry.filePath()}.removeRecursively();
            }
        }
    }

    QDir srcDir{src};
    srcDir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QFileInfo &entry: srcDir.entryInfoList()) {
        if (entry.isFile()) {
            QFile::copy(entry.filePath(), dest + "/" + entry.fileName());
        }

        else if (entry.isDir()) {
            copyFolder(entry.filePath(), dest + "/" + entry.fileName());
        }
    }
}
