#include "NotepadMainWindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    NotepadMain notepad;
    notepad.show();
    return app.exec();
}
