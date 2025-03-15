#include "app/application.h"

int main(int argc, char *argv[])
{
    Dp::App::Application app(argc, argv);
    return app.run();
}
