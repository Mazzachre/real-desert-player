#pragma once
#include <QObject>
#include <QQuickWindow>
#include <QQmlApplicationEngine>
#include <QScopedPointer>
#include <QDBusInterface>
#include "../app/playback.h"

namespace Dp {
    namespace Player {
        class Player : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool controlsVisible READ isControlsVisible NOTIFY controlsVisisbleChanged)
            Q_PROPERTY(bool fullScreen READ isFullScreen NOTIFY fullScreenChanged)
        public:
            Player(const QRect& dimensions, QObject* parent = nullptr);
            ~Player();

            bool isControlsVisible();
            Q_SIGNAL void controlsVisisbleChanged();

            Q_SLOT void toggleFullScreen();
            bool isFullScreen();
            Q_SIGNAL void fullScreenChanged();

            void start();
        private:
            Q_SLOT void windowStateChanged();

            //Both of these should be QPointer
            QQmlApplicationEngine *m_engine;
            QQuickWindow *m_window{nullptr};
            QDBusInterface *m_interface{nullptr};


            QTimer* m_controlsTimer{nullptr};
//            Display* m_display{nullptr};
            bool m_controlsVisible = true;

            void registerQmlTypes();
            void connectSignals();
        };
    }
}
