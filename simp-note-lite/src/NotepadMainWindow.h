#ifndef NOTEPADMAIN_H
#define NOTEPADMAIN_H

#include <QMainWindow>
#include <QLabel>
#include "Notepad/Notepad.h"
#include "Notepad/FindReplaceDialogue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NotepadMain; }
QT_END_NAMESPACE

class NotepadMain : public QMainWindow {
    Q_OBJECT
    // Manager
    NotepadManager notepadManager;
    // 文本框
    QPlainTextEdit* txtNotepad;
    // 查找/替换窗口
    FindReplaceDialogue* frd;
public:
    NotepadMain(QWidget *parent = nullptr);
    ~NotepadMain();
private:
    // UI
    Ui::NotepadMain *ui;
    // 自定义的控件
    QLabel *lblCol;
    QLabel *lblLin;
    QLabel *lblSel;

    // 标志位
    bool isSaved;
    bool isNewDoc;
    QString docName;
    QString docPath;

    // 绘制状态栏
    void SetStatusLabels();
    // 设置是否是新文件
    void SetNewDocument(bool newDocument);
    // 重写“关闭窗口”方法
    void closeEvent(QCloseEvent *event);
private slots:
    // 新建文件
    void NewFile();
    void NewFileFromClip();
    // 打开、保存文件
    void OpenFile();
    void SaveFile();
    void SaveAsFile();

    // 更新光标的「列、行」
    void UpdateColLine();
    // 更新光标的「选中字符数」
    void UpdateSel();
    // 更新“未保存”的状态
    void UpdateNotSaved();
    // 更新“显示状态栏”
    void ToggleStatusBarDisplay();
    // 更新“是否同意自动换行”
    void ToggleAutoWrapText();

    // 拷贝、粘贴、复制及删除
    void copy();
    void cut();
    void paste();
    void deleteSelection();

    // 撤销、重做、全选
    void undo();
    void redo();
    void selectAll();

    // 打开“查找及替换”窗口
    void OpenFindReplace();
    void OpenFindReplace(const QString &initString);

    // 打开“关于”窗口
    void OpenAboutWindow();

    // 退出
    bool QuitApp();
};
#endif // NOTEPADMAIN_H
