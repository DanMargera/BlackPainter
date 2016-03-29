#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include <QStack>
#include <QImage>
#include <QObject>


class UndoStack : public QObject
{
    Q_OBJECT

private:
    QStack <QImage*> *undoStack;
    QStack <QImage*> *redoStack;

public:
    UndoStack(QImage* first)
        : QObject()
    {
        undoStack = new QStack<QImage*>();
        redoStack = new QStack<QImage*>();
        undoStack->push(first);
    }


    ~UndoStack() { delete undoStack; delete redoStack; }
    void doIt(QImage* t);
    QImage* undo();
    QImage* redo();
    bool hasUndo() { return !(undoStack->size() < 2);  }
    bool hasRedo() { return !(redoStack->size() == 0); }
};


#endif // UNDOSTACK_H
