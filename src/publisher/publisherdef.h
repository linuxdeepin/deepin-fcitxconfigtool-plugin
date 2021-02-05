/*

* Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.

*

* Author:     lwh <liuwenhao@uniontech.com>

*

* Maintainer: lwh <liuwenhao@uniontech.com>

*

* This program is free software: you can redistribute it and/or modify

* it under the terms of the GNU General Public License as published by

* the Free Software Foundation, either version 3 of the License, or

* any later version.

*

* This program is distributed in the hope that it will be useful,

* but WITHOUT ANY WARRANTY; without even the implied warranty of

* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the

* GNU General Public License for more details.

*

* You should have received a copy of the GNU General Public License

* along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef PUBLISHERDEF_H
#define PUBLISHERDEF_H

#define deleteObject_Null(obj) \
    if (obj) \
        delete obj; \
    obj = nullptr;

#define for_int(count) for (int i = 0; i < count; ++i)
#define Debug 1

#endif // PUBLISHERDEF_H
