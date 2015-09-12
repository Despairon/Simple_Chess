#include "Chess.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QQuickWindow *wnd = qobject_cast<QQuickWindow*>(engine.rootObjects().at(0));
    wnd->setIcon(QIcon(":/Chess.ico"));
    QObject* rootObject = engine.rootObjects().at(0);
    QObject* chessPiecesGrid = rootObject->findChild<QObject*>("ChessPieces");
    QObject* chessBoardGrid = rootObject->findChild<QObject*>("ChessBoard");
    QObject* menubar = rootObject->findChild<QObject*>("Menubar");
    ChessPieces *chess = new ChessPieces(chessPiecesGrid,chessBoardGrid);
    GameListener *listener = new GameListener(menubar);
    chess->setGameListener(listener);
    return app.exec();
}
