#ifndef GAMELISTENER_H
#define GAMELISTENER_H

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QDebug>
#include <QQuickItem>
#include <QObject>
#include <QList>
#include <QMessageBox>
#include <QFileDialog>
#include <Qfile>

//---------------------------------------------------------------------
#define BLACK_TOWER QUrl(QStringLiteral("qrc:/chess/chess/bTower.png"))
#define BLACK_HORSE QUrl(QStringLiteral("qrc:/chess/chess/bHorse.png"))
#define BLACK_BISHOP QUrl(QStringLiteral("qrc:/chess/chess/bBishop.png"))
#define BLACK_KING QUrl(QStringLiteral("qrc:/chess/chess/bKing.png"))
#define BLACK_QUEEN QUrl(QStringLiteral("qrc:/chess/chess/bQueen.png"))
#define BLACK_PAWN QUrl(QStringLiteral("qrc:/chess/chess/bPawn.png"))
#define EMPTY QUrl(QStringLiteral(""))
#define WHITE_TOWER QUrl(QStringLiteral("qrc:/chess/chess/wTower.png"))
#define WHITE_HORSE QUrl(QStringLiteral("qrc:/chess/chess/wHorse.png"))
#define WHITE_BISHOP QUrl(QStringLiteral("qrc:/chess/chess/wBishop.png"))
#define WHITE_KING QUrl(QStringLiteral("qrc:/chess/chess/wKing.png"))
#define WHITE_QUEEN QUrl(QStringLiteral("qrc:/chess/chess/wQueen.png"))
#define WHITE_PAWN QUrl(QStringLiteral("qrc:/chess/chess/wPawn.png"))
//---------------------------------------------------------------------

struct Move
{
    QString abbreaviation;
    int from;
    int to;
};

struct GameHistory
{
    int moves_count;
    int current_move;
    QList<Move> moves;
};

class GameListener : public QObject
{
    Q_OBJECT
public:
    GameListener(QObject*);
    ~GameListener(){}
     bool isGameInProgress;
     enum turn {white_turn = 0, black_turn = 1};
     int current_turn;
     void history_proceed(QUrl, const int&, const int&);
signals:
    void gameStarted();
    void gameStopped();
    void gameLoaded();
    void rollback(QVariant);
    void makeCurrentMove(int,int,QUrl);
public slots:
    void beginGame();
    void stopGame();
    void saveGame();
    void loadGame();
    void nextMove();
    void prevMove();
    void change_turn();
private:
    enum gameState {screen_1 = 1, screen_2 = 2, screen_3 = 3};
    int current_state;
    GameHistory gameHistory;
    QString urlToAbbreviation(QUrl);
    QUrl abbreviationToUrl(QString);
};

#endif // GAMELISTENER_H
