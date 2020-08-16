#ifndef FINDREPLACEDIALOGUE_H
#define FINDREPLACEDIALOGUE_H

#include <QDialog>
#include <QPlainTextEdit>
#include "ui_findreplacedialogue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FindReplaceDialogue; }
QT_END_NAMESPACE

class FindReplaceDialogue : public QDialog, public Ui::FindReplaceDialogue {
    Q_OBJECT
public:
    FindReplaceDialogue(QPlainTextEdit* target, QWidget *parent = 0);
    // 设置查找的初始值
    void setInitText(const QString& initText);
private slots:
    // 调整查找/替换
    void ToggleFindReplace(bool isToReplace);
    // 点击了“查找下一个”按钮
    void FindNextClicked();
    // 点击了“替换这一个”按钮
    void ReplaceThisClicked();
    // 点击了“替换全部”按钮
    void ReplaceAllClicked();
private:
    // 查找的写字板
    QPlainTextEdit* txtNotepad;
};

#endif // FINDREPLACEDIALOGUE_H
