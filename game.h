#ifndef GAME_H
#define GAME_H

#include <QDir>
#include <QString>
#include <QDateTime>
#include <QStandardPaths>

class Game : QObject
{
    Q_OBJECT

public:
    // would be static variables but some standard paths only become available later
    const QString defaultGamePath;
    const QString defaultSavePath;

    explicit Game(QObject *parent = nullptr);

    void saveGame() const;
    void loadGame(const QString &id) const;
    void deleteGame(const QString &id) const;

    QStringList getSavedGames() const;

    const QString &getGamePath() const;
    void setGamePath(const QString &newGamePath);

    const QString &getSavePath() const;
    void setSavePath(const QString &newSavePath);

private:
    QString gamePath;
    QString savePath;

    QString createNewPathName() const;
    void copyFolder(const QString &src, const QString &dest) const;
};

#endif // GAME_H
