#include "undostack.h"

void UndoStack::doIt(QImage* t)
{
    undoStack->push(t);
    redoStack->clear();
}

QImage* UndoStack::undo()
{
    if(!hasUndo()) return NULL;
    QImage* t = undoStack->pop();
    redoStack->push(t);
    return undoStack->top();
}

QImage* UndoStack::redo()
{
    if(!hasRedo()) return NULL;
    QImage* t = redoStack->pop();
    undoStack->push(t);
    return t;
}
