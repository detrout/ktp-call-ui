#include "systemtray-icon.h"


SystemTrayIcon::SystemTrayIcon(QObject *parent)
{
    setIconByPixmap(QIcon::fromTheme("call-start"));
    setCategory(KStatusNotifierItem::SystemServices);
    setStatus(KStatusNotifierItem::Passive);
    setStandardActionsEnabled(false);
     if(parent!=0){
         QObject::setParent(parent);
     }
    activateNextTime=true;
}

void SystemTrayIcon::showCustomMessage()
{
    showMessage(contextMenu()->title(), i18n("This is a fantastic and very funny message which tells the user he could use the system tray icon to manage the call ui, but it's late and I have no idea about what to write here"), nullptr, 3000);
}

void SystemTrayIcon::show()
{
    if(activateNextTime==true)
    {
        setStatus(KStatusNotifierItem::Active);
        showCustomMessage();
    }else{
        activateNextTime=true;
    }
}

void SystemTrayIcon::activateNext(bool yesno)
{
    activateNextTime=yesno;
}