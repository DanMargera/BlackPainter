#include "settings.h"

Settings::Settings()
{
    settings = new QSettings("Black Seed","Black Painter");
}

QString Settings::getImageFolderPath()
{
    return imageFolderPath;
}

Settings::~Settings()
{
    delete settings;
}
