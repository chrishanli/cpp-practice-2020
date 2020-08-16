#include "AboutDialogue.h"
#include "ui_AboutDialogue.h"

AboutDialogue::AboutDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialogue)
{
    ui->setupUi(this);

    // 设置Build Time、QT版本等
    ui->lblBuildTime->setText(tr(__DATE__) + tr(" ") + tr(__TIME__));
    ui->lblQTVersion->setText(tr(QT_VERSION_STR));
    setFixedSize(this->width(), this->height());
    setWindowFlags(windowFlags()& ~ Qt::WindowMaximizeButtonHint);
    setWindowTitle(tr("About SimpNote Lite"));
}

AboutDialogue::~AboutDialogue()
{
    delete ui;
}
