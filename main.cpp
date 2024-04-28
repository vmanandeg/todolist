#include <QApplication>
#include "todolistapp.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TodoListApp window;
    window.show();
    return app.exec();
}
