#include "application.h"
#include <QCommandLineParser>
#include <QString>
#include <QDebug>
#include <QScreen>
#include "../player/player.h"

Dp::App::Application::Application(int& argc, char** argv)
: QApplication(argc, argv) {
    setApplicationName(QStringLiteral(u"Real Desert Player"));
    setApplicationVersion(QStringLiteral(u"0.1"));
    setOrganizationDomain(QStringLiteral(u"realdesert.com"));
    setOrganizationName(QStringLiteral(u"Real Desert Productions"));
}

Dp::App::Application::~Application() {
}

int Dp::App::Application::run() {
    QCommandLineParser parser;
    QCommandLineOption playOption(QStringList() << "p" << "play", "Player mode");
    parser.addOption(playOption);
    parser.process(*this);

    if (parser.isSet(playOption)) {
        Dp::Player::Player player = Dp::Player::Player(primaryScreen()->availableGeometry(), this);
        player.start();
        return exec();
    } else {
        qDebug() << "Library mode" << Qt::endl;
        return 0;
    }
}
