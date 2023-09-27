#include "showtranslators.h"
#include "ui_showtranslators.h"

ShowTranslators::ShowTranslators(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowTranslators)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("翻译器"));
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

ShowTranslators::~ShowTranslators()
{
    delete ui;
}

void ShowTranslators::setText(const QString &str)
{
    // 获取文本的宽度
    QFont font("Arial", 15);  // 字体名称和字号
    QFontMetrics fontMetrics(font);  // 根据字体创建字体测量器
    int textWidth = fontMetrics.width(str);  // 获取文本的宽度
    int textHeight = fontMetrics.height();
    ui->label->setFont(font);
    ui->label->setFixedWidth(textWidth + 20);
    // 改变窗口的尺寸
    this->setFixedSize(textWidth + 100, textHeight + 50);
    ui->label->setText(str);
}

void ShowTranslators::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isPressed = true;
        m_pressPos = event->pos();
    }
}

void ShowTranslators::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isPressed)
    {
        m_globalMovePos = event->globalPos();
        QPoint offset = m_globalMovePos - m_pressPos;
        this->move(offset);
    }
}

void ShowTranslators::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
}

void ShowTranslators::on_pushButton_close_clicked()
{
    this->close();
}
