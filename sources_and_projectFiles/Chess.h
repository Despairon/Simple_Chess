#ifndef CHESS_H
#define CHESS_H
#include "GameListener.h"

class Chess : public QObject
{
    Q_OBJECT
public:
    Chess(QObject*);
    ~Chess(){}
protected:
    QList<QQuickItem*> gridCells;
};

class ChessPieces : public Chess
{
    Q_OBJECT
public:
    ChessPieces(QObject*, QObject*);
    ~ChessPieces(){}
    void setGameListener (GameListener*);
public slots:
    void onCellPressed(const int&);
    void setChessAtInitialPosition();
    void movePiece(const int&, const int&, QUrl);
signals:
    void moveMade();
private:
    QList<int> availableMoves(const int&);
    int pickedChessPieceIndex;
    QUrl pickedChessPiece;
    QUrl pieceAt(const int&);
    void setPieceAt(const int&, QUrl);
    void movePiece(const int&);
    bool isChessPiecePicked;
    bool correspondsCurrentTurn(QUrl);
    bool canStrikeAt(const int&);
    void pickChessPiece(const int&);
    void calcTowerMoves(QList<int>&, const int&);
    void calcBishopsMoves(QList<int> &, const int&);
    GameListener *listener;
};

#endif // CHESS_H
