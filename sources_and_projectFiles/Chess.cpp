#include "chess.h"

Chess::Chess(QObject* pieces)
{
    QQuickItem *gridViewItem = qobject_cast<QQuickItem *>(pieces);
    if (gridViewItem->property("contentItem").isValid())
    {
        QQuickItem *listModel = qvariant_cast<QQuickItem *>(gridViewItem->property("contentItem"));
        for (int i=0; i<listModel->childItems().size()-1; i++)
            this->gridCells.push_back(listModel->childItems().at(i)->childItems().at(0)->childItems().at(0));
    }
}

void ChessPieces::setGameListener(GameListener *glistener)
{
    this->listener = glistener;
    connect(this,SIGNAL(moveMade()),listener,SLOT(change_turn()));
    connect(listener,SIGNAL(gameStopped()),this,SLOT(setChessAtInitialPosition()));
    connect(listener,SIGNAL(gameStarted()),this,SLOT(setChessAtInitialPosition()));
    connect(listener,SIGNAL(gameLoaded()),this,SLOT(setChessAtInitialPosition()));
    connect(listener, SIGNAL(makeCurrentMove(int,int,QUrl)), this, SLOT(movePiece(const int&,const int&,QUrl)));
}

ChessPieces::ChessPieces(QObject* pieces, QObject* board) : Chess(pieces)
{
    connect(board,SIGNAL (cellClicked(int)),this,SLOT(onCellPressed(int)));
    this->isChessPiecePicked = false;
}
bool ChessPieces::correspondsCurrentTurn(QUrl curr_piece)
{
    if (listener->current_turn == listener->white_turn
        && (curr_piece == WHITE_PAWN || curr_piece == WHITE_HORSE ||
            curr_piece == WHITE_BISHOP || curr_piece == WHITE_TOWER ||
            curr_piece == WHITE_KING || curr_piece == WHITE_QUEEN)
        )
        return true;
    if (listener->current_turn == listener->black_turn &&
        (curr_piece == BLACK_PAWN || curr_piece == BLACK_HORSE ||
         curr_piece == BLACK_BISHOP || curr_piece == BLACK_TOWER ||
         curr_piece == BLACK_KING || curr_piece == BLACK_QUEEN)
        )
        return true;

return false;
}

QUrl ChessPieces::pieceAt(const int &at)
{
    return gridCells.at(at)->property("source").toUrl();
}

void ChessPieces::setPieceAt(const int &at, QUrl piece)
{
    gridCells.at(at)->setProperty("source",piece);
}

void ChessPieces::onCellPressed(const int &at)
{
    QUrl current_cell = pieceAt(at);
    if (listener->isGameInProgress)
        if (correspondsCurrentTurn(current_cell))
                pickChessPiece(at);
        else
            if (isChessPiecePicked)
                movePiece(at);
}


void ChessPieces::pickChessPiece(const int &index)
{
    pickedChessPiece = pieceAt(index);
    pickedChessPieceIndex = index;
    isChessPiecePicked = true;
}

bool ChessPieces::canStrikeAt(const int &at)
{
    if( pieceAt(at) != EMPTY && !correspondsCurrentTurn(pieceAt(at)) )
        return true;
    else
        return false;
}

QList<int> ChessPieces::availableMoves(const int &index)
{
    QList<int> moves;

    if (pickedChessPiece == BLACK_PAWN)
    {
        if (index>7 && index <16) // pawn can move 2 cells forward if it stays at initial position
        {
            if (pieceAt(index+8) == EMPTY)
            {
                moves.push_back(index+16);
                moves.push_back(index+8);
            }
        }
        else
            if (pieceAt(index+8) == EMPTY)
                moves.push_back(index+8);
        if (canStrikeAt(index+7))
            moves.push_back(index+7);
        if (canStrikeAt(index+9))
            moves.push_back(index+9);
     }

    if (pickedChessPiece == WHITE_PAWN)
    {
        if (index>47 && index <56)
        {
            if (pieceAt(index-8) == EMPTY)
            {
                moves.push_back(index-16);
                moves.push_back(index-8);
            }
        }
        else
            if (pieceAt(index-8) == EMPTY)
                moves.push_back(index-8);
        if (canStrikeAt(index-7))
            moves.push_back(index-7);
        if (canStrikeAt(index-9))
            moves.push_back(index-9);
     }

    if (pickedChessPiece == BLACK_TOWER || pickedChessPiece == WHITE_TOWER)
    {
        calcTowerMoves(moves,index);
    }

    if (pickedChessPiece == BLACK_BISHOP || pickedChessPiece == WHITE_BISHOP)
    {
        calcBishopsMoves(moves,index);
    }

    if (pickedChessPiece == BLACK_QUEEN || pickedChessPiece == WHITE_QUEEN)
    {
        calcTowerMoves(moves,index);
        calcBishopsMoves(moves,index);
    }

    if (pickedChessPiece == BLACK_HORSE || pickedChessPiece == WHITE_HORSE)
    {
        const int ShortDownRight = (index + 8) + 2;
        const int LongDownRight = (index + 16) + 1;
        const int ShortDownLeft = (index + 8) - 2;
        const int LongDownLeft = (index + 16) - 1;
        const int ShortUpRight = (index - 8) + 2;
        const int LongUpRight = (index - 16) + 1;
        const int ShortUpLeft = (index - 8) - 2;
        const int LongUpLeft = (index - 16) - 1;
        moves.push_back(ShortDownRight);
        moves.push_back(LongDownRight);
        moves.push_back(ShortUpRight);
        moves.push_back(LongUpRight);
        moves.push_back(ShortDownLeft);
        moves.push_back(LongDownLeft);
        moves.push_back(ShortUpLeft);
        moves.push_back(LongUpLeft);
    }

    if (pickedChessPiece == BLACK_KING || pickedChessPiece == WHITE_KING)
    {
        moves.push_back(index+1);
        moves.push_back(index-1);
        moves.push_back(index+8);
        moves.push_back(index-8);
        moves.push_back(index+9);
        moves.push_back(index-9);
        moves.push_back(index+7);
        moves.push_back(index-7);
    }

    for (int i=0; i<moves.size(); i++)
      if (moves.at(i) < 0 || moves.at(i) > 63)  // here we make sure our indices of grid cells,
       moves.erase(moves.begin()+i,moves.begin()+i+1); // which chess pieces can move to are in the range of 0..63
    return moves;
}

void ChessPieces::movePiece(const int &destination)
{
    if (availableMoves(pickedChessPieceIndex).contains(destination)
        && (pieceAt(destination) != WHITE_KING && pieceAt(destination) != BLACK_KING))
    {
        setPieceAt(destination,pickedChessPiece);
        setPieceAt(pickedChessPieceIndex,EMPTY);
        isChessPiecePicked = false;
        listener->history_proceed(pickedChessPiece,pickedChessPieceIndex,destination);
        emit moveMade();
    }
    else
        isChessPiecePicked = false; // if player picked chess piece and pressed on cell it can not move to,
                                    // chess piece makes deselected!
}

void ChessPieces::movePiece(const int &from, const int &to, QUrl piece)
{
    setPieceAt(to,piece);
    setPieceAt(from,EMPTY);
}

void ChessPieces::setChessAtInitialPosition()
{
    setPieceAt(0,BLACK_TOWER);
    setPieceAt(1,BLACK_HORSE);
    setPieceAt(2,BLACK_BISHOP);
    setPieceAt(3,BLACK_QUEEN);
    setPieceAt(4,BLACK_KING);
    setPieceAt(5,BLACK_BISHOP);
    setPieceAt(6,BLACK_HORSE);
    setPieceAt(7,BLACK_TOWER);
    for (int i=8; i<16; i++)
        setPieceAt(i,BLACK_PAWN);
    for (int i=16; i<48; i++)
        setPieceAt(i,EMPTY);
    for (int i=48; i<56; i++)
        setPieceAt(i,WHITE_PAWN);
    setPieceAt(56,WHITE_TOWER);
    setPieceAt(57,WHITE_HORSE);
    setPieceAt(58,WHITE_BISHOP);
    setPieceAt(59,WHITE_QUEEN);
    setPieceAt(60,WHITE_KING);
    setPieceAt(61,WHITE_BISHOP);
    setPieceAt(62,WHITE_HORSE);
    setPieceAt(63,WHITE_TOWER);

}

void ChessPieces::calcTowerMoves(QList<int> &moves ,const int &index)
{
    int row = index/8;
    int column = index;
    while (column >= 8)
        column -= 8;

    const int Left = (row*8)-1, Right = Left+9, Top = column-1, Bottom = 64-(6-Top);
    for (int i = index; i > Left; i--)
    {
        if (pieceAt(i) != EMPTY && i != index)
        {
            if (canStrikeAt(i))
                moves.push_back(i);
            break;
        }
        if (i != index)
            moves.push_back(i);
    }
    for (int i = index; i < Right; i++)
    {
        if (pieceAt(i) != EMPTY && i != index)
        {
            if (canStrikeAt(i))
                moves.push_back(i);
            break;
        }
        if (i != index)
            moves.push_back(i);
    }
    for (int i = index; i > Top; i-=8)
    {
        if (pieceAt(i) != EMPTY && i != index)
        {
            if (canStrikeAt(i))
                moves.push_back(i);
            break;
        }
        if (i != index)
            moves.push_back(i);
    }
    for (int i = index; i < Bottom; i+=8)
    {
        if (pieceAt(i) != EMPTY && i != index)
        {
            if (canStrikeAt(i))
                moves.push_back(i);
            break;
        }
        if (i != index)
            moves.push_back(i);
    }
}

void ChessPieces::calcBishopsMoves(QList<int> &moves, const int &index)
{
    int row = index/8;
    int column = index;
    while (column >= 8)
        column -= 8;
    int upLeft = index, upRight = index, downLeft = index, downRight = index;
    int currRow = row, currCol = column;
    while (currRow > 0 && currCol > 0)
    {
        if (pieceAt(upLeft) != EMPTY && upLeft != index)
        {
            if (canStrikeAt(upLeft))
                moves.push_back(upLeft);
            break;
        }
        currRow--;
        currCol--;
        upLeft -= 9;
        moves.push_back(upLeft);
    }
    currRow = row, currCol = column;
    while (currRow > 0 && currCol < 7)
    {
        if (pieceAt(upRight) != EMPTY && upRight != index)
        {
            if (canStrikeAt(upRight))
                moves.push_back(upRight);
            break;
        }
        currRow--;
        currCol++;
        upRight -= 7;
        moves.push_back(upRight);
    }
    currRow = row, currCol = column;
    while (currRow < 7 && currCol < 7)
    {
        if (pieceAt(downRight) != EMPTY && downRight != index)
        {
            if (canStrikeAt(downRight))
                moves.push_back(downRight);
            break;
        }
        currRow++;
        currCol++;
        downRight += 9;
        moves.push_back(downRight);
    }
    currRow = row, currCol = column;
    while (currRow < 7 && currCol > 0)
    {
        if (pieceAt(downLeft) != EMPTY && downLeft != index)
        {
            if (canStrikeAt(downLeft))
                moves.push_back(downLeft);
            break;
        }
        currRow++;
        currCol--;
        downLeft += 7;
        moves.push_back(downLeft);
    }
}
