#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QToolBar>
#include <QColor>
#include <QFileInfo>

#include "graphicsview.h"
#include "coloraction.h"
#include "undostack.h"
#include "sidepanel.h"
#include "statusbar.h"
#include "paintdraw.h"
#include "multidraw.h"
#include "imageslider.h"
#include "preferences.h"
#include "spinboxaction.h"
#include "thresholdfilterdialog.h"
#include "filtercontroller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void openFile(QString filePath);

private slots:
    void fileAct(QAction* fileAction);
    void editAct(QAction* editAction);
    void drawAct(QAction* drawAction);
    void viewAct(QAction* viewAction);
    void filterAct(QAction* filterAction);
    void searchAct(QAction* searchAction);
    void helpAct(QAction* helpAction);



    void closeEvent (QCloseEvent *event);

    void doIt();

    void toolTracking(QString tool);
    void imageDoubleClicked(QString path);

    void applyPreferences();
    void cancelPreferences();

    void filterChanged(QImage image);
    void filterApplied(QImage image);
    void filterCanceled(QImage image);

private:
    QString fileName;
    QFileInfo* fileInfo;


    void createActions();
    void createMenu();
    void createToolbars();
    void createStatusBar();
    void createLayout();
    void createDrawTools();
    void createSidepanel();
    void createImageSlider();
    void createDialogs();
    void createControllers();

    void loadImage(QImage* imageObject);
    void setupTitle();
    void loadImages();
    void loadOrderedImages(QList<ImageCell*> list);

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* drawMenu;
    QMenu* viewMenu;
    QMenu* filterMenu;
    QMenu* searchMenu;
    QMenu* helpMenu;

    QToolBar* drawToolbar;
    QToolBar* editToolbar;
    QToolBar* viewToolbar;

    StatusBar* statusBar;

    GraphicsView* view;
    UndoStack* undoStack;
    SidePanel* sidePanel;
    QDockWidget *dock;

    QMessageBox* saveMessageBox;
    ImageSlider* imageSlider;
    QDockWidget* imageSliderDock;
    Preferences* preferences;

    //File
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *preferencesAct;
    QAction *exitAct;

    //Edit
    QAction *undoAct;
    QAction *redoAct;

    //Draw
    QActionGroup* drawActGroup;

    QAction       *paintAct;
    QAction       *rectAct;
    QAction       *ellipseAct;
    QAction       *lineAct;
    QAction       *pencilAct;
    ColorAction   *chooseFillAct;
    ColorAction   *chooseBorderAct;
    SpinBoxAction *chooseBorderWidthAct;

    //View
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;

    //Filters
    QAction *negativeAct;
    QAction *grayScaleAct;
    QAction *convolutionAct;
    QAction *convolutionGSAct;
    QAction *thresholdAct;
    QAction *levelsAct;
    QAction *brightnessContrastAct;

    //Search
    QAction *currentAct;

    //About
    QAction *aboutAct;

    //Draw tools
    PaintDraw*   paintDraw;
    RectDraw*    rectDraw;
    EllipseDraw* ellipseDraw;
    LineDraw*    lineDraw;
    PencilDraw*  pencilDraw;

    //Controllers
    FilterController * filterController;
};

#endif // MAINWINDOW_H
