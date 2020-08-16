
#include "Notepad/Notepad.h"
#include <QFile>

void NotepadManager::getCaretPosition(int* line, int* col) {
    int pos = txtNotepad->textCursor().position();
    QString text = txtNotepad->toPlainText();//获取编辑器中的内容
    *line = 0;
    *line = 0;
    int flag = -1;
    for(int i=0; i < pos; i++) {
        if(text[i] == '\n') {
            (*line)++;
            flag = i;
        }
    }

    flag++;//如光标在第十一行的某个位置，那么一共有十个换行符，flag++就是在第十行最后一个位置（即最后一个光标所在位置）
    *col = pos - flag;//用第十一行光标所在位置减去前十行的总数就得第十一行的字符个数，即纵坐标
}

int NotepadManager::getSelectedTextLength() {
    return this->txtNotepad->textCursor().selectedText().length();
}

QString NotepadManager::getClipboard() {
    const QClipboard *clipboard = QApplication::clipboard();
    return clipboard->text();
}

void NotepadManager::appendText(const QString& str) {
    this->txtNotepad->appendPlainText(str);
}

bool NotepadManager::loadFile(QFile& file) {
    QTextStream ts(&file);
    while (!ts.atEnd()) {
        // 按行显示文件内容
        this->txtNotepad->appendPlainText(ts.readLine());
    }
    return true;
}

bool NotepadManager::saveFile(QFile& file) {
    QTextStream ts(&file);
    ts << this->txtNotepad->toPlainText();
    return true;
}

void NotepadManager::setAutoWrapEnabled(bool enabled) {
    if (enabled) {
        this->txtNotepad->setLineWrapMode(QPlainTextEdit::LineWrapMode::WidgetWidth);
    } else {
        this->txtNotepad->setLineWrapMode(QPlainTextEdit::LineWrapMode::NoWrap);
    }
}

bool NotepadManager::isAutoWrapEnabled() {
    QPlainTextEdit::LineWrapMode m = this->txtNotepad->lineWrapMode();
    return !(m == QPlainTextEdit::LineWrapMode::NoWrap);
}
