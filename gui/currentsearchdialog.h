#ifndef CURRENTSEARCHDIALOG_H
#define CURRENTSEARCHDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QColor>
#include <metadata.h>

class CurrentSearchDialog : public QDialog
{
    Q_OBJECT

public:
    CurrentSearchDialog(QWidget * parent = 0);
    int selectedComparisonType(); // retorna o tipo de histograma a ser comparado
    int selectedDistanceMethod();  // retorna o tipo de cálculo de distancia entre histogramas

private:
    QLabel*      comparisonLabel;
    QComboBox*   comparisonBox;

    QLabel*      distanceLabel;
    QComboBox*   distanceBox;

    QLabel*      samplingLabel;
    QLineEdit*   valueLineEdit;
    QSlider*     samplingSlider;

    QPushButton* searchBtn;
    QPushButton* cancelBtn;

    void createWidgets();
    void createLayout();

private slots:
    void valueEdited(QString value);
    void valueEdited(int value);
};

#endif // CURRENTSEARCHDIALOG_H
