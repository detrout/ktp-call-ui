#ifndef SYSTEMTRAYICON
#define SYSTEMTRAYICON

#include <KStatusNotifierItem>
#include <KMenu>
#include <KLocalizedString>

class SystemTrayIcon : public KStatusNotifierItem
{
public:
    //KMenu trayIconMenu;

public:
    SystemTrayIcon(QObject *parent = 0);
    void show();
    void activateNext(bool yesno);

public Q_SLOTS:
    void showCustomMessage();

private:
    bool activateNextTime;
};

#endif //SYSTEMTRAYICON