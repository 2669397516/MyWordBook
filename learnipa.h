#ifndef LEARNIPA_H
#define LEARNIPA_H

#include <QWidget>

namespace Ui {
class LearnIPA;
}

class LearnIPA : public QWidget
{
    Q_OBJECT

public:
    explicit LearnIPA(QWidget *parent = nullptr);
    ~LearnIPA();

private:
    Ui::LearnIPA *ui;
};

#endif // LEARNIPA_H
