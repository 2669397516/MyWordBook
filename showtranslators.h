#ifndef SHOWTRANSLATORS_H
#define SHOWTRANSLATORS_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class ShowTranslators;
}

class ShowTranslators : public QDialog
{
    Q_OBJECT

public:
    explicit ShowTranslators(QWidget *parent = nullptr);
    ~ShowTranslators();
    void setText(const QString &str);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::ShowTranslators *ui;
    bool m_isPressed = false;
    QPoint m_pressPos;
    QPoint m_globalMovePos;
};

#endif // SHOWTRANSLATORS_H
