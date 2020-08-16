#include "FindReplaceDialogue.h"
#include <QMessageBox>

FindReplaceDialogue::FindReplaceDialogue(QPlainTextEdit* target, QWidget* parent):
QDialog(parent)
{
    setupUi(this);
    connect(chkReplace, SIGNAL(clicked(bool)), this, SLOT(ToggleFindReplace(bool)));
    connect(btnFindNext, SIGNAL(clicked()), this, SLOT(ReplaceThisClicked()));
    connect(btnReplaceThis, SIGNAL(clicked()), this, SLOT(FindNextClicked()));
    connect(btnReplaceAll, SIGNAL(clicked()), this, SLOT(ReplaceAllClicked()));
    this->txtNotepad = target;
}

void FindReplaceDialogue::setInitText(const QString& initText) {
    this->txtFindText->setText(initText);
}

void FindReplaceDialogue::ToggleFindReplace(bool isToReplace) {
    // 设置控件可用
    this->txtReplaceTo->setEnabled(isToReplace);
    this->btnReplaceAll->setEnabled(isToReplace);
}

// 点击了“查找下一个”按钮
void FindReplaceDialogue::FindNextClicked() {
    const QString findText = this->txtFindText->text();
    if (this->chkRegExp->isChecked()) {
        // 利用正则表达式查找！
        int pos = this->txtNotepad->textCursor().position();
        QRegExp regExp;
        regExp.setPattern(findText);
        if ((pos = regExp.indexIn(this->txtNotepad->toPlainText(), pos)) != -1) {
            // 找到了，选中它
            QTextCursor cur = txtNotepad->textCursor();
            cur.setPosition(pos, QTextCursor::MoveAnchor);
            cur.setPosition(pos + regExp.matchedLength(), QTextCursor::KeepAnchor);
            txtNotepad->setTextCursor(cur);
            btnReplaceThis->setEnabled(true && this->chkReplace->isChecked());
        } else {
            // 没找到，关掉它
            QMessageBox::information(this,tr("Note"),tr("Finder reaches the end of document."),QMessageBox::Ok);
            btnReplaceThis->setEnabled(false);
        }
    } else {
        // 普通查找，直接调用API！
        bool isFound;
        if (this->chkIgnoreCases->isChecked()) {
            isFound = txtNotepad->find(findText);
        } else {
            isFound = txtNotepad->find(findText, QTextDocument::FindCaseSensitively);
        }
        if (isFound) {
            // 找到后选中
            QTextCursor cur = txtNotepad->textCursor();
            int pos = cur.position();
            cur.setPosition(pos, QTextCursor::MoveAnchor);
            cur.setPosition(pos - findText.length(), QTextCursor::KeepAnchor);
            txtNotepad->setTextCursor(cur);
            btnReplaceThis->setEnabled(true && this->chkReplace->isChecked());
        } else {
            // 没找到，关掉它
            QMessageBox::information(this,tr("Note"),tr("Finder reaches the end of document."),QMessageBox::Ok);
            btnReplaceThis->setEnabled(false);
        }
    }
}

// 点击了“替换这一个”按钮
void FindReplaceDialogue::ReplaceThisClicked() {
    this->txtNotepad->insertPlainText(this->txtReplaceTo->text());
}

// 点击了“替换全部”按钮
void FindReplaceDialogue::ReplaceAllClicked() {
    const QString findText = this->txtFindText->text();
    if (this->chkRegExp->isChecked()) {
        // 利用正则表达式直接替换！
        QRegExp regExp;
        regExp.setPattern(findText);
        this->txtNotepad->setPlainText(this->txtNotepad->toPlainText().replace(regExp, txtReplaceTo->text()));
    } else {
        // 普通替换，直接调用API！
        if (this->chkIgnoreCases->isChecked()) {
            while (txtNotepad->find(findText)) {
                // 找到后选中
                QTextCursor cur = txtNotepad->textCursor();
                int pos = cur.position();
                cur.setPosition(pos, QTextCursor::MoveAnchor);
                cur.setPosition(pos - findText.length(), QTextCursor::KeepAnchor);
                txtNotepad->setTextCursor(cur);
                txtNotepad->insertPlainText(this->txtReplaceTo->text());
            }
            QMessageBox::information(this,tr("Note"),tr("Finder reaches the end of document."),QMessageBox::Ok);
        } else {
            while (txtNotepad->find(findText, QTextDocument::FindCaseSensitively)) {
                // 找到后选中
                QTextCursor cur = txtNotepad->textCursor();
                int pos = cur.position();
                cur.setPosition(pos, QTextCursor::MoveAnchor);
                cur.setPosition(pos - findText.length(), QTextCursor::KeepAnchor);
                txtNotepad->setTextCursor(cur);
                txtNotepad->insertPlainText(this->txtReplaceTo->text());
            }
            QMessageBox::information(this,tr("Note"),tr("Finder reaches the end of document."),QMessageBox::Ok);
        }
    }
}
