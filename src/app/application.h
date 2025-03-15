#pragma once

#include <QApplication>
#include "playback.h"

namespace Dp {
    namespace App {
        class Application : QApplication {
            Q_OBJECT
        public:
            Application(int &argc, char **argv);
            ~Application();

            int run();
        };
    }
}
