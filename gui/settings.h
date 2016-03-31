#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>


class Settings
{
public:
    Settings();
    ~Settings();

    QString getImageFolderPath();

private:
    QSettings* settings;

    QString imageFolderPath;
};

#endif // SETTINGS_H
