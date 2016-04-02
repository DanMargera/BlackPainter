#include <QtWidgets>
#include <QFileDialog>
#include <QActionGroup>
#include "mainwindow.h"

#include "histogram.h"
#include <pidtools.h>
#include <metadatafile.h>
#include "newimage.h"
#include "currentsearchdialog.h"
#include <QProcess>
#include "asyncprocess.h"
#include "thresholdfilterdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QCoreApplication::setApplicationName("Black Painter");

    resize(800,600);

    createLayout();
    createActions();
    createMenu();
    createToolbars();
    createStatusBar();
    createSidepanel();
    createImageSlider();
    createDrawTools();
    createDialogs();
    createControllers();

    fileInfo = NULL;

}

void MainWindow::createActions()
{
    //File
    newAct         = new QAction(tr("&New"), this);
    openAct        = new QAction(tr("&Open"), this);
    saveAct        = new QAction(tr("&Save"), this);
    saveAsAct      = new QAction(tr("Save &As"), this);
    preferencesAct = new QAction(tr("&Preferences"), this);
    exitAct        = new QAction(tr("E&xit"), this);

    newAct->setShortcut(QKeySequence::New);
    openAct->setShortcut(QKeySequence::Open);
    saveAct->setShortcut(QKeySequence::Save);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    exitAct->setShortcut(QKeySequence::Quit);

    //Edit
    undoAct = new QAction(QIcon(":/icons/back-arrow.png"),tr("&Undo"), this);
    redoAct = new QAction(QIcon(":/icons/foward-arrow.png"),tr("&Redo"), this);

    undoAct->setShortcut(QKeySequence::Undo);
    redoAct->setShortcut(QKeySequence::Redo);

    undoAct->setDisabled(true);
    redoAct->setDisabled(true);

    //Draw
    drawActGroup = new QActionGroup(this);

    paintAct        = new QAction(QIcon(":/icons/paint-bucket.png"),tr("Paint &Bucket"), this);
    rectAct         = new QAction(QIcon(":/icons/square.png"),tr("&Rectangle"), this);
    ellipseAct      = new QAction(QIcon(":/icons/blank-circle.png"),tr("&Ellipse"), this);
    lineAct         = new QAction(QIcon(":/icons/vector-line.png"),tr("&Line"), this);
    pencilAct       = new QAction(QIcon(":/icons/artistic-brush.png"),tr("&Pencil"), this);

    chooseFillAct   = new ColorAction(QSize(512,512), QColor(255,255,255), tr("&Fill"), this);
    chooseBorderAct = new ColorAction(QSize(512,64), QColor(0,0,0), tr("&Border"), this);

    chooseBorderWidthAct = new SpinBoxAction(this);
    chooseBorderWidthAct->setText("Border: ");
    chooseBorderWidthAct->setRange(1,100);
    chooseBorderWidthAct->setValue(1);
    chooseBorderWidthAct->setVisible(false);

    paintAct->setCheckable(true);
    rectAct->setCheckable(true);
    ellipseAct->setCheckable(true);
    lineAct->setCheckable(true);
    pencilAct->setCheckable(true);

    chooseFillAct->setVisible(false);
    chooseBorderAct->setVisible(false);
    chooseBorderWidthAct->setVisible(false);

    drawActGroup->setExclusive(true);
    drawActGroup->addAction(paintAct  );
    drawActGroup->addAction(rectAct   );
    drawActGroup->addAction(ellipseAct);
    drawActGroup->addAction(lineAct   );
    drawActGroup->addAction(pencilAct );

    //View
    zoomInAct      = new QAction(QIcon(":/icons/zoom-tool.png"),tr("Zoom &In"), this);
    zoomOutAct     = new QAction(QIcon(":/icons/zoom-out.png"),tr("Zoom &Out"), this);
    normalSizeAct  = new QAction(tr("&Normal Size"), this);
    fitToWindowAct = new QAction(tr("&Fit to Window"), this);

    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);

    //Filters
    negativeAct           = new QAction(tr("&Negative"),this);
    grayScaleAct          = new QAction(tr("&Gray Scale"),this);
    convolutionAct        = new QAction(tr("&Convolution RGB"),this);
    convolutionGSAct      = new QAction(tr("C&onvolution GS"),this);
    thresholdAct          = new QAction(tr("&Threshold"),this);
    levelsAct             = new QAction(tr("&Levels"),this);
    brightnessContrastAct = new QAction(tr("&Brightness/Contrast"),this);

    //Search
    currentAct = new QAction(tr("&Current Image"),this);

    //About
    aboutAct = new QAction(tr("&About"), this);
}

void MainWindow::createMenu()
{
    QMenuBar* menu = new QMenuBar(this);

    fileMenu   = new QMenu(tr("&File"), this);
    editMenu   = new QMenu(tr("&Edit"), this);
    drawMenu   = new QMenu(tr("&Draw"), this);
    viewMenu   = new QMenu(tr("&View"), this);
    filterMenu = new QMenu(tr("F&ilter"), this);
    searchMenu = new QMenu(tr("&Search"), this);
    helpMenu   = new QMenu(tr("&Help"), this);

    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(preferencesAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    drawMenu->addAction(pencilAct);
    drawMenu->addAction(paintAct);
    drawMenu->addAction(rectAct);
    drawMenu->addAction(ellipseAct);
    drawMenu->addAction(lineAct);
    drawMenu->addSeparator();
    drawMenu->addAction(chooseFillAct);
    drawMenu->addAction(chooseBorderAct);
    drawMenu->addAction(chooseBorderWidthAct);

    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addAction(fitToWindowAct);

    filterMenu->addAction(negativeAct);
    filterMenu->addAction(grayScaleAct);
    filterMenu->addAction(convolutionAct);
    filterMenu->addAction(convolutionGSAct);
    filterMenu->addAction(thresholdAct);
    filterMenu->addAction(levelsAct);
    filterMenu->addAction(brightnessContrastAct);

    searchMenu->addAction(currentAct);

    helpMenu->addAction(aboutAct);

    menu->addMenu(fileMenu);
    menu->addMenu(editMenu);
    menu->addMenu(drawMenu);
    menu->addMenu(viewMenu);
    menu->addMenu(filterMenu);
    menu->addMenu(searchMenu);
    menu->addMenu(helpMenu);

    connect(fileMenu,SIGNAL(triggered(QAction*)),this,SLOT(fileAct(QAction*)));
    connect(editMenu,SIGNAL(triggered(QAction*)),this,SLOT(editAct(QAction*)));
    connect(drawMenu,SIGNAL(triggered(QAction*)),this,SLOT(drawAct(QAction*)));
    connect(viewMenu,SIGNAL(triggered(QAction*)),this,SLOT(viewAct(QAction*)));
    connect(filterMenu,SIGNAL(triggered(QAction*)),this,SLOT(filterAct(QAction*)));
    connect(searchMenu,SIGNAL(triggered(QAction*)),this,SLOT(searchAct(QAction*)));
    connect(helpMenu,SIGNAL(triggered(QAction*)),this,SLOT(helpAct(QAction*)));

    setMenuBar(menu);
}

void MainWindow::createToolbars()
{
    drawToolbar = new QToolBar(tr("Draw ToolBar"),this);
    editToolbar = new QToolBar(tr("Edit ToolBar"),this);
    viewToolbar = new QToolBar(tr("View ToolBar"),this);

    addToolBar(Qt::RightToolBarArea,drawToolbar);
    addToolBar(Qt::RightToolBarArea,editToolbar);
    addToolBar(Qt::RightToolBarArea,viewToolbar);

    drawToolbar->addAction(pencilAct);
    drawToolbar->addAction(paintAct);
    drawToolbar->addAction(rectAct);
    drawToolbar->addAction(ellipseAct);
    drawToolbar->addAction(lineAct);
    drawToolbar->addSeparator();
    drawToolbar->addAction(chooseFillAct);
    drawToolbar->addAction(chooseBorderAct);
    drawToolbar->addAction(chooseBorderWidthAct);

    editToolbar->addAction(undoAct);
    editToolbar->addAction(redoAct);

    viewToolbar->addAction(zoomInAct);
    viewToolbar->addAction(zoomOutAct);
}

void MainWindow::createStatusBar()
{
    statusBar = new StatusBar(this);
    setStatusBar(statusBar);
    view->setMouseTrackingLabel(statusBar->getMouseTrackingLabel());
}

void MainWindow::createLayout()
{
    view = new GraphicsView(this);
    view->setEnabled(false);
    setCentralWidget(view);

    connect(view,SIGNAL(done()),this,SLOT(doIt()));
}

void MainWindow::createSidepanel()
{
    dock = new QDockWidget(this);
    sidePanel = new SidePanel(dock);
    dock->setWidget(sidePanel);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    dock->setTitleBarWidget(new QWidget());
    addDockWidget(Qt::LeftDockWidgetArea,dock,Qt::Vertical);
}

void MainWindow::createImageSlider()
{
    imageSliderDock = new QDockWidget(this);
    imageSlider = new ImageSlider(this);

    imageSliderDock->setWidget(imageSlider);
    imageSliderDock->setAllowedAreas(Qt::BottomDockWidgetArea);
    imageSliderDock->setTitleBarWidget(new QWidget());
    addDockWidget(Qt::BottomDockWidgetArea,imageSliderDock,Qt::Horizontal);

    connect(imageSlider,SIGNAL(imageDoubleClicked(QString)),this,SLOT(imageDoubleClicked(QString)));
}

void MainWindow::createDrawTools()
{
    paintDraw    = new PaintDraw();
    rectDraw     = new RectDraw();
    ellipseDraw  = new EllipseDraw();
    lineDraw     = new LineDraw();
    pencilDraw   = new PencilDraw();

    connect(paintDraw,  SIGNAL(toolTracking(QString)),this,SLOT(toolTracking(QString)));
    connect(rectDraw,   SIGNAL(toolTracking(QString)),this,SLOT(toolTracking(QString)));
    connect(ellipseDraw,SIGNAL(toolTracking(QString)),this,SLOT(toolTracking(QString)));
    connect(lineDraw,   SIGNAL(toolTracking(QString)),this,SLOT(toolTracking(QString)));
    connect(pencilDraw, SIGNAL(toolTracking(QString)),this,SLOT(toolTracking(QString)));
}

void MainWindow::createDialogs()
{
    saveMessageBox = new QMessageBox(this);
    saveMessageBox->setText("The image has been modified.");
    saveMessageBox->setInformativeText("Do you want to save your changes?");
    saveMessageBox->setStandardButtons(QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);
    saveMessageBox->setDefaultButton(QMessageBox::Save);

    preferences = new Preferences(this);
    connect(preferences,SIGNAL(apply()),this,SLOT(applyPreferences()));
    connect(preferences,SIGNAL(cancel()),this,SLOT(cancelPreferences()));

    QSettings settings("Black Seed","Black Painter",this);
    settings.beginGroup("Preferences");
    preferences->setPath(settings.value("defaultPath",QCoreApplication::applicationDirPath()).toString());
    settings.endGroup();

    // Inicia o processo de geracao de metadados
    AsyncProcess* process = new AsyncProcess();
    process->start("../offline/offline",  preferences->getPath());

    loadImages();
}

void MainWindow::closeEvent (QCloseEvent *event){ Q_UNUSED(event) }
//Edit
void MainWindow::doIt()
{
    undoStack->doIt(view->getQImage());
    undoAct->setEnabled(undoStack->hasUndo());
    redoAct->setEnabled(undoStack->hasRedo());
    setupTitle();


    sidePanel->getHistogram()->setRGBHistogram(PIDTools::rgbHistogram(*view->getQImage()));
}

void MainWindow::loadImage(QImage* imageObject)
{
    view->setModifed(false);
    setupTitle();
    view->scene()->clear();
    view->setQImage(imageObject);
    view->setEnabled(true);
    undoStack = new UndoStack(imageObject);
    undoAct->setEnabled(undoStack->hasUndo());
    redoAct->setEnabled(undoStack->hasRedo());
    sidePanel->setScene(view->scene());
    sidePanel->getGraphicsView()->fitInView(view->scene()->sceneRect(),Qt::KeepAspectRatio);
    sidePanel->getHistogram()->setRGBHistogram(PIDTools::rgbHistogram(*imageObject));
}

void MainWindow::setupTitle()
{
    setWindowTitle(QString("%1%2 - Black Painter").arg(fileInfo != NULL ? fileInfo->fileName() : "untitle").arg(view->isModified() ? "*" : ""));
}

void MainWindow::toolTracking(QString tool)
{
    statusBar->setToolTrackingLabel(tool);
}

void MainWindow::openFile(QString filePath)
{
    fileInfo = new QFileInfo(filePath);
    fileName = fileInfo->fileName();
    QImage* imageObject = new QImage();
    imageObject->load(filePath);
    view->setModifed(false);
    setupTitle();
    view->scene()->clear();
    view->setQImage(imageObject);
    loadImage(imageObject);

}

void MainWindow::fileAct(QAction* fileAction)
{
    if(view->isModified() && (fileAction == newAct || fileAction == openAct || fileAction == exitAct))
    {
        int result = saveMessageBox->exec();
        if(result == QMessageBox::Save) fileAct(saveAct);
        else if(result != QMessageBox::No) return;
    }

    if(fileAction == newAct)
    {
        NewImage newDialog(this,800,600);
        if(!newDialog.exec()) return;
        QImage* imageObject = new QImage(newDialog.selectedSize(),
                                         QImage::Format_ARGB32_Premultiplied);
        imageObject->fill(newDialog.selectedColor());
        loadImage(imageObject);

        fileInfo = NULL;
    }
    else if(fileAction == openAct)
    {
        QFileDialog openDialog(this,
                               tr("Open File"),
                               "",
                               tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
        if(!openDialog.exec()) return;

        openFile(openDialog.selectedFiles().first());
    }
    else if(fileAction == saveAct)
    {
        if(fileInfo == NULL)
            fileAct(saveAsAct);
        else
        {
            view->getQImage()->save(fileInfo->filePath(),0,100);
            view->setModifed(false);
            setupTitle();
        }

    }
    else if(fileAction == saveAsAct)
    {
        QString imagePath = QFileDialog::getSaveFileName(
                    this,
                    tr("Save File"),
                    "",
                    tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" )
                    );
        if(imagePath.isEmpty()) return;
        view->getQImage()->save(imagePath,0,100);
        view->setModifed(false);
        fileInfo = new QFileInfo(imagePath);
        setupTitle();
    }
    else if(fileAction == preferencesAct)
        preferences->exec();
    else if(fileAction == exitAct) close();
}
void MainWindow::editAct(QAction* editAction)
{
    if(editAction == undoAct) view->setQImage(undoStack->undo());
    else if(editAction == redoAct) view->setQImage(undoStack->redo());
    undoAct->setEnabled(undoStack->hasUndo());
    redoAct->setEnabled(undoStack->hasRedo());
}
void MainWindow::drawAct(QAction* drawAction)
{
    if(drawAction == paintAct)
    {
        view->setAbstractDraw(paintDraw);
        chooseBorderAct->setVisible(false);
        chooseFillAct->setVisible(true);
        chooseBorderWidthAct->setVisible(false);
    }
    else if(drawAction == rectAct)
    {
        view->setAbstractDraw(rectDraw);
        chooseBorderAct->setVisible(true);
        chooseFillAct->setVisible(true);
        chooseBorderWidthAct->setVisible(true);
    }
    else if(drawAction == ellipseAct)
    {
        view->setAbstractDraw(ellipseDraw);
        chooseBorderAct->setVisible(true);
        chooseFillAct->setVisible(true);
        chooseBorderWidthAct->setVisible(true);
    }
    else if(drawAction == lineAct)
    {
        view->setAbstractDraw(lineDraw);
        chooseBorderAct->setVisible(true);
        chooseFillAct->setVisible(false);
        chooseBorderWidthAct->setVisible(true);
    }
    else if(drawAction == pencilAct)
    {
        view->setAbstractDraw(pencilDraw);
        chooseBorderAct->setVisible(true);
        chooseFillAct->setVisible(false);
        chooseBorderWidthAct->setVisible(true);
    }

    if(view->getAbstractDraw() != NULL)
    {
        view->getAbstractDraw()->setBorderColor(chooseBorderAct->getColor());
        view->getAbstractDraw()->setFillColor(chooseFillAct->getColor());
        view->getAbstractDraw()->setBorderWidth(chooseBorderWidthAct->getValue());
    }
}
void MainWindow::viewAct(QAction* viewAction)
{
    if(viewAction == zoomInAct)
        view->zoomIn(0.1);
    else if(viewAction == zoomOutAct)
        view->zoomOut(0.1);
    else if(viewAction == normalSizeAct)
        view->normalSize();
    else if(viewAction == fitToWindowAct)
        view->fitInView(view->scene()->sceneRect(),Qt::KeepAspectRatio);
}

void MainWindow::filterAct(QAction* filterAction)
{
    QImage image;
    if(filterAction == negativeAct)
        image = PIDTools::negative(*view->getQImage());
    else if(filterAction == grayScaleAct)
        image = PIDTools::gray_scale(*view->getQImage());
    else if(filterAction == convolutionAct)
        image = PIDTools::convolution(*view->getQImage());
    else if(filterAction == convolutionGSAct)
        image = PIDTools::convolution_GS(*view->getQImage());
    else if(filterAction == thresholdAct)
    {
        filterController->execBinaring(*view->getQImage());
        return;
    }
    else if(filterAction == levelsAct)
    {
        filterController->execLevels(*view->getQImage());
        return;
    }
    else if(filterAction == brightnessContrastAct)
    {
        filterController->execBrightnessContrast(*view->getQImage());
        return;
    }
    else return;

    view->setQImage(&image);
    view->setModifed(true);
    doIt();
}

void MainWindow::searchAct(QAction* searchAction)
{
    if(searchAction == currentAct) {
        CurrentSearchDialog newDialog(this);
        if(!newDialog.exec()) return;
        // faz a busca com newDialog.selectedComparisonType e selectedDistanceMethod
        QDirIterator it(preferences->getPath(), QStringList() << "*.data", QDir::Files, QDirIterator::NoIteratorFlags);

        int cType = newDialog.selectedComparisonType();
        ImageCell* tempIc;
        QList<ImageCell*> list;
        Metadata* current = new Metadata();
        Metadata* m = new Metadata();

        switch(cType) {
        case Rgb:
            current->generateRGB(*view->getQImage());
            break;
        case Hsv:
            current->generateHSV(*view->getQImage());
            break;
        case Yuv:
            current->generateYUV(*view->getQImage());
            break;
        case Sampling:
            current->generateSampling(*view->getQImage());
            break;
        }

        while(it.hasNext()) {
            QString filePath = it.next();

            switch(cType) {
            // Resgata os dados do arquivo .data
            case Rgb:
                m->setRGB(MetadataFile::getRGB(filePath));
                break;
            case Hsv:
                m->setHSV(MetadataFile::getHSV(filePath));
                break;
            case Yuv:
                m->setYUV(MetadataFile::getYUV(filePath));
                break;
            case Sampling:
                m->setSampling(MetadataFile::getSamplingData(filePath));
                break;
            }

            tempIc = new ImageCell();
            tempIc->distance = current->compareTo(m, newDialog.selectedComparisonType(), newDialog.selectedDistanceMethod());
            tempIc->path = filePath.replace(".data", "");
            list << tempIc;
        }
        qSort(list.begin(), list.end());
        loadOrderedImages(list);
    }
}

void MainWindow::helpAct(QAction* helpAction)
{
    if(helpAction == aboutAct)
        QMessageBox::about(this, tr("About Black Paint"),
                 tr("The <b>Black Paint</b> is an image editor developed for "
                    "Digital Image Processing Class by: "
                    "Andre, Daniel Terenzi, Tales Bontempo Cunha"));
}

void MainWindow::imageDoubleClicked(QString path)
{

    if(view->isModified())
    {
        int result = saveMessageBox->exec();
        if(result == QMessageBox::Save) fileAct(saveAct);
        else if(result != QMessageBox::No) return;
    }
    openFile(path);
}

void MainWindow::applyPreferences()
{
    loadImages();

    QSettings settings("Black Seed","Black Painter",this);
    settings.beginGroup("Preferences");
    settings.setValue("defaultPath",preferences->getPath());
    settings.endGroup();
}

void MainWindow::cancelPreferences()
{
    QSettings settings("Black Seed","Black Painter",this);
    settings.beginGroup("Preferences");
    preferences->setPath(settings.value("defaultPath",QCoreApplication::applicationDirPath()).toString());
    settings.endGroup();
}

void MainWindow::loadImages()
{
    imageSlider->clear();
    QDirIterator it(preferences->getPath(), QStringList() << "*.jpg", QDir::Files, QDirIterator::NoIteratorFlags);
    while (it.hasNext())
        imageSlider->appendImagePath(it.next());
}

/*
 * Recebe uma lista de células contendo o Path de cada imagem,
 * e carrega no imageSlider na ordem da lista;
 * */
void MainWindow::loadOrderedImages(QList<ImageCell*> list)
{

    imageSlider->clear();
    QListIterator<ImageCell*> it(list);
    ImageCell* ic;
    while(it.hasNext()) {
        ic = it.next();
        imageSlider->appendImagePath(ic->path);
    }
}

void MainWindow::createControllers()
{
    filterController = new FilterController(this);
    connect(filterController,SIGNAL(filterChanged(QImage)),this,SLOT(filterChanged(QImage)));
    connect(filterController,SIGNAL(filterApplied(QImage)),this,SLOT(filterApplied(QImage)));
    connect(filterController,SIGNAL(filterCanceled(QImage)),this,SLOT(filterCanceled(QImage)));
}

void MainWindow::filterChanged(QImage image)
{
    view->setQImage(&image);
}

void MainWindow::filterApplied(QImage image)
{
    view->setQImage(&image);
    doIt();
}

void MainWindow::filterCanceled(QImage image)
{
    view->setQImage(&image);
}

MainWindow::~MainWindow()
{

}
