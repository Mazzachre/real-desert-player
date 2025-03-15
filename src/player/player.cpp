#include "player.h"
#include "../const.h"
#include <QDebug>
#include <QQuickWindow>

Dp::Player::Player::Player(const QRect& dimensions, QObject* parent)
: QObject(parent)
, m_engine{new QQmlApplicationEngine}
, m_interface{new QDBusInterface(SERVICE_NAME, "/", "", QDBusConnection::sessionBus())} {

    registerQmlTypes();
    m_engine->load(QUrl(QStringLiteral("qrc:/player.qml")));

    m_window = qobject_cast<QQuickWindow*>(m_engine->rootObjects().first());
    if (!m_window) qFatal("No root window created");
    if (m_engine->rootObjects().isEmpty()) qFatal("No root objects");

    m_window->resize(dimensions.width() / 2, dimensions.height() / 2);

    connectSignals();
}

Dp::Player::Player::~Player() noexcept {
    m_engine->deleteLater();
    m_interface->deleteLater();
}

bool Dp::Player::Player::isControlsVisible() {
    return m_controlsVisible;
}

void Dp::Player::Player::toggleFullScreen() {
    if (m_window != nullptr) {
        if (m_window->windowState() == Qt::WindowNoState) {
            m_window->setWindowState(Qt::WindowFullScreen);
        } else {
            m_window->setWindowState(Qt::WindowNoState);
        }
    }
}

bool Dp::Player::Player::isFullScreen() {
    qDebug() << "Asking for window state: " << (m_window != nullptr && m_window->windowState() == Qt::WindowFullScreen) << Qt::endl;
	return m_window != nullptr && m_window->windowState() == Qt::WindowFullScreen;
}


void Dp::Player::Player::start() {
    qDebug() << "Started player" << m_interface->isValid() << Qt::endl;

    //DBusInterface->call("play-next")

    //Use Qt D-BUS adapter?
}

void Dp::Player::Player::registerQmlTypes() {
    qmlRegisterSingletonType<Dp::Player::Player>("desert", 1, 0, "App",
        [this](QQmlEngine *qmlEngine, QJSEngine *jsEngine) -> QObject* {
            Q_UNUSED(qmlEngine);
            Q_UNUSED(jsEngine);
            return this;
        }
    );
}

void Dp::Player::Player::connectSignals() {
    connect(m_window, &QWindow::windowStateChanged, this, &Player::windowStateChanged);
}

void Dp::Player::Player::windowStateChanged() {
    qDebug() << "Changed state" << Qt::endl;
    Q_EMIT fullScreenChanged();
}

