/*
    Copyright (C) 2009  George Kiagiadakis <kiagiadakis.george@gmail.com>

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _KGSTDEVICES_TABLEDEVICECHOOSER_H
#define _KGSTDEVICES_TABLEDEVICECHOOSER_H

#include "devicemanager.h"
#include <QtGui/QWidget>

namespace KGstDevices {

class KGSTDEVICES_EXPORT TableDeviceChooser : public QWidget
{
    Q_OBJECT
public:
    TableDeviceChooser(DeviceManager *manager, DeviceManager::DeviceType type, QWidget *parent = 0);
    virtual ~TableDeviceChooser();

private:
    struct Private;
    Private *const d;
    Q_PRIVATE_SLOT(d, void onCurrentDeviceChanged(DeviceManager::DeviceType type));
    Q_PRIVATE_SLOT(d, void onSelectionChanged(const QItemSelection & selected));
    Q_PRIVATE_SLOT(d, void onModelReset());
    Q_PRIVATE_SLOT(d, void testDevice());
    Q_PRIVATE_SLOT(d, void toggleDetails());
};

}

#endif