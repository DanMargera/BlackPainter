#ifndef SPINBOXACTION_H
#define SPINBOXACTION_H

#include <QWidgetAction>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QIntValidator>


class SpinBoxAction : public QWidgetAction
{
    Q_OBJECT

public:
    SpinBoxAction(QObject * parent = 0, int value = 0);
    void setText(const QString &text);
    void setRange(int min, int max);
    int getValue();

protected:
    QWidget* createWidget(QWidget * parent);

private:
    QLabel*      menuTextLabel;
    QLineEdit*   menuValueLineEdit;
    QPushButton* menuIncreaseBtn;
    QPushButton* menuDicreaseBtn;

    QLineEdit*   toolBarValueLineEdit;
    QPushButton* toolBarIncreaseBtn;
    QPushButton* toolBarDicreaseBtn;

    QWidget* menuWidget;
    QWidget* toolBarWidget;

    QIntValidator* validator;

    int min, max;
    int value;

public slots:
    void increase();
    void dicrease();

    void setValue(QString value);
    void setValue(int value);
};

#endif // SPINBOXACTION_H
