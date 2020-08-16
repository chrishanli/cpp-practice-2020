#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QPlainTextEdit>
#include <QApplication>
#include <QClipboard>
#include <QTextStream>

class NotepadManager {
private:
    QPlainTextEdit* txtNotepad;
public:
    void setNotepad(QPlainTextEdit* txtNotepad) { this->txtNotepad = txtNotepad; }
    // 获取当前光标位置（行、列）
    void getCaretPosition(int* line, int* col);
    // 获取当前选定之文字长度
    int getSelectedTextLength();
    // 获取是否自动换行
    bool isAutoWrapEnabled();
    void setAutoWrapEnabled(bool enabled);
    // 获取剪贴板文字内容
    QString getClipboard();
    // 设置文字
    void appendText(const QString& str);
    // 打开文件
    bool loadFile(QFile& file);
    // 写回文件
    bool saveFile(QFile& file);

    ~NotepadManager() {}
};

#endif // NOTEPAD_H
