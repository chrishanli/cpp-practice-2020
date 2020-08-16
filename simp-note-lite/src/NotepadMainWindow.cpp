#include "NotepadMainWindow.h"
#include "AboutDialogue.h"
#include "ui_notepadmain.h"
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

NotepadMain::NotepadMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NotepadMain)
    {
    ui->setupUi(this);
    txtNotepad = ui->centralwidget->findChild<QPlainTextEdit *>("txtNotepad");
    notepadManager.setNotepad(txtNotepad);
    frd = new FindReplaceDialogue(txtNotepad);
    /* 画界面 */
    ui->action_Enable_Status_Bar->setChecked(true);
    ui->action_Auto_Wrap_Text->setChecked(true);
    SetNewDocument(true);
    /* 添加事件 */
    // 普通操作
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(OpenFile()));
    connect(ui->action_New_Document, SIGNAL(triggered()), this, SLOT(NewFile()));
    connect(ui->actionNew_Document_from_Clipboard, SIGNAL(triggered()), this, SLOT(NewFileFromClip()));
    connect(ui->action_Enable_Status_Bar, SIGNAL(triggered()), this, SLOT(ToggleStatusBarDisplay()));
    connect(ui->action_Auto_Wrap_Text, SIGNAL(triggered()), this, SLOT(ToggleAutoWrapText()));
    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(SaveFile()));
    connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(SaveAsFile()));
    connect(ui->actionFind_Replace, SIGNAL(triggered()), this, SLOT(OpenFindReplace()));
    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(QuitApp()));

    // 编辑操作
    connect(ui->action_Copy, SIGNAL(triggered()), this, SLOT(copy()));
    connect(ui->actionCut, SIGNAL(triggered()), this, SLOT(cut()));
    connect(ui->action_Paste, SIGNAL(triggered()), this, SLOT(paste()));
    connect(ui->actionDelete_Selection, SIGNAL(triggered()), this, SLOT(deleteSelection()));

    // 撤销、重做、全选操作
    connect(ui->action_Undo, SIGNAL(triggered()), this, SLOT(undo()));
    connect(ui->action_Redo, SIGNAL(triggered()), this, SLOT(redo()));
    connect(ui->actionSelect_All, SIGNAL(triggered()), this, SLOT(selectAll()));

    // 更新状态栏操作
    connect(txtNotepad, SIGNAL(cursorPositionChanged()), this, SLOT(UpdateColLine()));
    connect(txtNotepad, SIGNAL(selectionChanged()), this, SLOT(UpdateSel()));
    connect(txtNotepad, SIGNAL(textChanged()), this, SLOT(UpdateNotSaved()));

    // “关于”窗口操作
    connect(ui->actionAbout_SimpNote_Lite, SIGNAL(triggered()), this, SLOT(OpenAboutWindow()));

    /* 绘制状态栏 */
    SetStatusLabels();
    UpdateColLine();
    UpdateSel();
}

NotepadMain::~NotepadMain() {
    delete ui;
    delete frd;
}

// 设置是否是新文件
void NotepadMain::SetNewDocument(bool newDocument) {
    this->isNewDoc = newDocument;
    this->isSaved = !newDocument;
    if (newDocument) {
        this->setWindowTitle(tr("Untitled - SimpNote Lite"));
    } else {
        this->setWindowTitle(this->docName + " - SimpNote Lite");
    }
}

// 设置状态栏
void NotepadMain::SetStatusLabels() {
    QFont statusBarFont;
    statusBarFont.setBold(true);
    this->lblCol = new QLabel(this);
    this->lblLin = new QLabel(this);
    this->lblSel = new QLabel(this);
    QLabel* lblColTxt = new QLabel(this);
    lblColTxt->setText("Column:");
    lblColTxt->setFont(statusBarFont);
    QLabel* lblLinTxt = new QLabel(this);
    lblLinTxt->setText("Line:");
    lblLinTxt->setFont(statusBarFont);
    QLabel* lblSelTxt = new QLabel(this);
    lblSelTxt->setText("Selected:");
    lblSelTxt->setFont(statusBarFont);
    ui->statusbar->addPermanentWidget(lblColTxt);
    ui->statusbar->addPermanentWidget(this->lblCol);
    ui->statusbar->addPermanentWidget(lblLinTxt);
    ui->statusbar->addPermanentWidget(this->lblLin);
    ui->statusbar->addPermanentWidget(lblSelTxt);
    ui->statusbar->addPermanentWidget(this->lblSel);
}

// 新建文档
void NotepadMain::NewFile() {
    NotepadMain* newNotepad = new NotepadMain;
    newNotepad->show();
}

// 从剪贴簿新建文档
void NotepadMain::NewFileFromClip() {
    NotepadMain* newNotepad = new NotepadMain;
    newNotepad->notepadManager.appendText(notepadManager.getClipboard());
    newNotepad->show();
}

// 打开文件
void NotepadMain::OpenFile() {
    QString filepath = QFileDialog::getOpenFileName(this, tr("Open Document"));
    if (filepath.isNull()) {
        // 点击取消，关闭
        return;
    }
    // 点击确认，打开
    NotepadMain* newNotepad = new NotepadMain;
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Open module reports an error"));
    }
    if (!newNotepad->notepadManager.loadFile(file)) {
        QMessageBox::critical(this, tr("Error"), tr("Open module reports an error"));
    }
    QFileInfo fi(file);
    newNotepad->docPath = fi.filePath();
    newNotepad->docName = fi.fileName();
    file.close();
    newNotepad->SetNewDocument(false);
    newNotepad->show();
}

// 保存文件
void NotepadMain::SaveFile() {
    // 如果是新创建的文件
    QString newDocPath;
    if (isNewDoc) {
        newDocPath = QFileDialog::getSaveFileName(this, tr("Save Document"));
        if (newDocPath.isNull()) {
            // 点击取消，关闭
            return;
        }
    } else {
        newDocPath = docPath;
    }
    // 点击确认，保存
    QFile file(newDocPath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Save module reports an error: path error"));
        return;
    }
    if (!notepadManager.saveFile(file)) {
        QMessageBox::critical(this, tr("Error"), tr("Save module reports an error"));
        return;
    }
    if (isNewDoc) {
        QFileInfo fi(file);
        docName = fi.fileName();
        docPath = newDocPath;
    }
    // 更新标题
    SetNewDocument(false);
    file.close();

    // 发送讯息
    this->ui->statusbar->showMessage(tr("File saved at: ") + docPath, 2500);
}

// 另存文件
void NotepadMain::SaveAsFile() {
    QString newDocPath = QFileDialog::getSaveFileName(this, tr("Save Document"));
    if (newDocPath.isNull()) {
        // 点击取消，关闭
        return;
    }
    // 点击确认，保存
    QFile file(newDocPath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Save module reports an error: path error"));
        return;
    }
    if (!notepadManager.saveFile(file)) {
        QMessageBox::critical(this, tr("Error"), tr("Save module reports an error"));
        return;
    }
    QFileInfo fi(file);
    docName = fi.fileName();
    docPath = fi.absoluteFilePath();
    // 更新标题
    SetNewDocument(false);
    file.close();

    // 发送讯息
    this->ui->statusbar->showMessage(tr("File saved at: ") + docPath, 2500);
}

// 更新行列指示
void NotepadMain::UpdateColLine() {
    int col, lin;
    this->notepadManager.getCaretPosition(&lin, &col);
    this->lblCol->setNum(col);
    this->lblLin->setNum(lin+1);
}

// 更新选中文字指示
void NotepadMain::UpdateSel() {
    this->lblSel->setNum(this->notepadManager.getSelectedTextLength());
}


// 更新“显示状态栏”
void NotepadMain::ToggleStatusBarDisplay() {
    this->ui->statusbar->setVisible(!this->ui->statusbar->isVisible());
}

// 更新“是否自动换行”
void NotepadMain::ToggleAutoWrapText() {
    this->notepadManager.setAutoWrapEnabled(!this->notepadManager.isAutoWrapEnabled());
}

// 拷贝、剪下、粘贴、删除
void NotepadMain::copy() {
    if (notepadManager.getSelectedTextLength() > 0) {
        this->txtNotepad->copy();
    }
}
void NotepadMain::cut() {
    if (notepadManager.getSelectedTextLength() > 0) {
        this->txtNotepad->cut();
    }
}
void NotepadMain::paste() {
    this->txtNotepad->paste();
}
void NotepadMain::deleteSelection() {
    this->txtNotepad->insertPlainText("");
}

// 撤销
void NotepadMain::undo() {
    this->txtNotepad->undo();
}

// 重做
void NotepadMain::redo() {
    this->txtNotepad->redo();
}

// 全选
void NotepadMain::selectAll() {
    this->txtNotepad->selectAll();
}

// 打开“查找及替换”窗口
void NotepadMain::OpenFindReplace() {
    OpenFindReplace(this->txtNotepad->textCursor().selectedText());
}

void NotepadMain::OpenFindReplace(const QString& initString) {
    frd->setInitText(initString);
    frd->setWindowTitle(tr("Find / Replace"));
    frd->show();
}

// 打开“关于”窗口
void NotepadMain::OpenAboutWindow() {
    AboutDialogue abd;
    abd.exec();
}

// “退出”功能
bool NotepadMain::QuitApp() {
    if (!isSaved) {
        // 没保存，提示保存
        int result = QMessageBox::question( this,
                                            tr("Quit SimpNote Lite"),
                                            tr("Are you sure to exit SimpNote Lite without saving \"") +
                                            (this->docName.isNull() ? tr("Untitled") : this->docName)  +
                                            tr("\"?"));
        if (result == QMessageBox::Yes) {
            // 不保存，直接退出
            close();
            return true;
        } // 其他情况，则不做任何操作
    } else {
        // 不保存，直接退出
        close();
        return true;
    }
    return false;
}

// 更新“未保存”状态
void NotepadMain::UpdateNotSaved() {
    this->isSaved = false;
}

// 重写“窗口关闭”方法
void NotepadMain::closeEvent(QCloseEvent *event) {
    if (!QuitApp()) {
        event->ignore();
    }
}
