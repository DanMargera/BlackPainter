#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class Preferences : public QDialog
{
    Q_OBJECT

public:
    Preferences(QWidget * parent = 0);
    ~Preferences();

    QString getPath();
    void setPath(QString path);

private:
    QLabel      *imagePahtLabel;

    QLineEdit   *pathLineEdit;
    QPushButton *choosePathBtn;

    QPushButton *applyPathBtn;
    QPushButton *okPathBtn;
    QPushButton *cancelPathBtn;

    void createLayout();
    void createWidgets();

public slots:
    void choosePath();
    void applyPath();
    void okPath();
    void cancelPath();
    void updateBtns();

signals:
    void apply();
    void cancel();
};

#endif // PREFERENCES_H
