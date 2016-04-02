#ifndef LEVELSFILTERDIALOG_H
#define LEVELSFILTERDIALOG_H

#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QImage>

class LevelsFilterDialog : public QDialog
{
    Q_OBJECT

public:
    LevelsFilterDialog(QWidget * parent = 0);

    static QString FILTER;

    int getLowValue()  { return lowValue;  }
    int getHighValue() { return highValue; }

signals:
    void changed(QString filter);
    void ok();
    void cancel();

private:

    int max;
    int min;
    int lowValue;
    int highValue;

    QLabel      *levelsLabel;
    QLineEdit   *lowValueLineEdit;
    QLineEdit   *highValueLineEdit;
    QSlider     *lowLevelsSlider;
    QSlider     *highLevelsSlider;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void createLayout();
    void createWidgets();

private slots:
    void okLevels();
    void cancelLevels();
    void lowValueEdited(QString value);
    void lowValueEdited(int value);
    void highValueEdited(QString value);
    void highValueEdited(int value);
};

#endif // LEVELSFILTERDIALOG_H
