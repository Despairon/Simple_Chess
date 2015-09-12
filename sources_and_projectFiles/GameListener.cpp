#include "GameListener.h"

GameListener::GameListener(QObject* menubar)
{
    this->isGameInProgress = false;
    this->current_turn = white_turn;
    this->gameHistory.moves_count = 0;
    this->gameHistory.current_move = 0;
    this->current_state = screen_1;
    QObject* startmenu = menubar->findChild<QObject*>("startmenu");
    QObject* stopmenu = menubar->findChild<QObject*>("stopmenu");
    QObject* loadmenu = menubar->findChild<QObject*>("loadmenu");
    QObject* savemenu = menubar->findChild<QObject*>("savemenu");
    QObject* next = menubar->findChild<QObject*>("nextMenu");
    QObject* prev = menubar->findChild<QObject*>("prevMenu");

    connect(startmenu, SIGNAL(triggered()), this, SLOT(beginGame()));
    connect(stopmenu, SIGNAL(triggered()), this, SLOT(stopGame()));
    connect(loadmenu, SIGNAL(triggered()), this, SLOT(loadGame()));
    connect(this, SIGNAL(rollback(QVariant)), loadmenu, SLOT(rollBack(QVariant)) );
    connect(savemenu, SIGNAL(triggered()), this, SLOT(saveGame()));

    connect(next, SIGNAL(triggered()), this, SLOT(nextMove()));
    connect(prev, SIGNAL(triggered()), this, SLOT(prevMove()));

}

QString GameListener::urlToAbbreviation(QUrl piece) // returns QString that corresponds to abbreviaton
{                                        // of chess piece name (f.e. WHITE_PAWN returns "wp")
    if (piece == BLACK_TOWER)
        return "bt";
    if (piece == BLACK_HORSE)
        return "bh";
    if (piece == BLACK_BISHOP)
        return "bb";
    if (piece == BLACK_QUEEN)
        return "bq";
    if (piece == BLACK_KING)
        return "bk";
    if (piece == BLACK_PAWN)
        return "bp";

    if (piece == WHITE_TOWER)
        return "wt";
    if (piece == WHITE_HORSE)
        return "wh";
    if (piece == WHITE_BISHOP)
        return "wb";
    if (piece == WHITE_QUEEN)
        return "wq";
    if (piece == WHITE_KING)
        return "wk";
    if (piece == WHITE_PAWN)
        return "wp";
    return "";
}

QUrl GameListener::abbreviationToUrl(QString abbreviation)
{
    if (abbreviation == "bt")
        return BLACK_TOWER;
    if (abbreviation == "bh")
        return BLACK_HORSE;
    if (abbreviation == "bb")
        return BLACK_BISHOP;
    if (abbreviation == "bq")
        return BLACK_QUEEN;
    if (abbreviation == "bk")
        return BLACK_KING;
    if (abbreviation == "bp")
        return BLACK_PAWN;

    if (abbreviation == "wt")
        return WHITE_TOWER;
    if (abbreviation == "wh")
        return WHITE_HORSE;
    if (abbreviation == "wb")
        return WHITE_BISHOP;
    if (abbreviation == "wq")
        return WHITE_QUEEN;
    if (abbreviation == "wk")
        return WHITE_KING;
    if (abbreviation == "wp")
        return WHITE_PAWN;
    return "";
}

void GameListener::history_proceed(QUrl chess_piece, const int &from, const int &to)
{
    Move current_move;
    current_move.abbreaviation = urlToAbbreviation(chess_piece);
    current_move.from = from;
    current_move.to = to;
    gameHistory.moves.push_back(current_move);
    gameHistory.moves_count++;
}

void GameListener::beginGame()
{
    isGameInProgress = true;
    current_state = screen_2;
    emit gameStarted();
}

void GameListener::stopGame()
{
    isGameInProgress = false;
    current_turn = white_turn;
    gameHistory.moves_count = 0;
    gameHistory.current_move = 0;
    gameHistory.moves.clear();
    current_state = screen_1;
    emit gameStopped();
}

void GameListener::loadGame()
{
    isGameInProgress = false;
    gameHistory.moves_count = 0;
    gameHistory.current_move = 0;
    gameHistory.moves.clear();
    QString filename = QFileDialog::getOpenFileName(0,"Open game history from file",QDir::currentPath(),"");
    if (filename != "")
    {
        QFile fileToOpen(filename);
        QTextStream fileIn(&fileToOpen);
        fileToOpen.open( QIODevice::ReadOnly );
        QString buffer;
        Move mbuffer;
        fileIn >> buffer;
        if (buffer != "Moves_made")
        {
            QMessageBox::critical(0,"oops!","Wrong file opened!");
            emit rollback(QVariant(current_state));
        }
        else
        {
            fileIn >> gameHistory.moves_count;
            while (!fileIn.atEnd())
            {
                fileIn >> mbuffer.abbreaviation;
                fileIn >> mbuffer.from;
                fileIn >> mbuffer.to;
                gameHistory.moves.push_back(mbuffer);
            }
            gameHistory.moves.pop_back();
            fileToOpen.close();

            current_state = screen_3;
            emit gameLoaded();
        }
    }
    else
        emit rollback(QVariant(current_state));
}

void GameListener::saveGame()
{
    if (gameHistory.moves_count > 0)
    {
        QString filename = QFileDialog::getSaveFileName(0,"Save history to file",QDir::currentPath(),"");
        if (filename != "")
        {
            QFile fileToSave(filename);
            QTextStream fileOut(&fileToSave);
            fileToSave.open( QIODevice::WriteOnly );
            fileOut << "Moves_made " << gameHistory.moves_count << " ";
            for (int i=0; i<gameHistory.moves_count; i++)
            {
                fileOut << gameHistory.moves.at(i).abbreaviation << " ";
                fileOut << gameHistory.moves.at(i).from << " ";
                fileOut << gameHistory.moves.at(i).to << " ";
            }
            fileToSave.close();
        }
    }
    else
        QMessageBox::warning(0,"oops!","Nothing to save! make at least one move...");

}

void GameListener::nextMove()
{
    if (gameHistory.current_move < gameHistory.moves_count)
    {
        emit makeCurrentMove(
                    gameHistory.moves.at(gameHistory.current_move).from,
                    gameHistory.moves.at(gameHistory.current_move).to,
                    abbreviationToUrl(gameHistory.moves.at(gameHistory.current_move).abbreaviation)
                    );
        gameHistory.current_move++;
    }
}

void GameListener::prevMove()
{
    if (gameHistory.current_move > 0)
    {
        emit makeCurrentMove(
                    gameHistory.moves.at(gameHistory.current_move-1).to,
                    gameHistory.moves.at(gameHistory.current_move-1).from,
                    abbreviationToUrl(gameHistory.moves.at(gameHistory.current_move-1).abbreaviation)
                    );

        gameHistory.current_move--;
    }
}

void GameListener::change_turn()
{
    if (current_turn == white_turn)
        current_turn = black_turn;
    else
        current_turn = white_turn;
}

