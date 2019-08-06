/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "SeparatorWidget_p.h"
#include "multisplitter/MultiSplitterLayout_p.h"
#include "multisplitter/Anchor_p.h"
#include "Logging_p.h"

#include <QPainter>
#include <QStyleOption>
#include <QMouseEvent>

using namespace KDDockWidgets;

SeparatorWidget::SeparatorWidget(KDDockWidgets::Anchor *anchor, QWidget *parent)
    : Separator(anchor, parent)
{
    const int thickness = Anchor::thickness(isStatic());
    if (isVertical())
        setFixedWidth(thickness);
    else
        setFixedHeight(thickness);

    setMouseTracking(true);
}

void SeparatorWidget::move(int p)
{
    if (isVertical()) {
        QWidget::move(p, y());
    } else {
        QWidget::move(x(), p);
    }
}

void SeparatorWidget::paintEvent(QPaintEvent *)
{
    if (!anchor())
        return;

    QPainter p(this);

    QStyleOption opt;
    opt.palette = palette();
    opt.rect = rect();
    opt.state = QStyle::State_None;
    if (isVertical())
        opt.state |= QStyle::State_Horizontal;

    if (isEnabled())
        opt.state |= QStyle::State_Enabled;

    parentWidget()->style()->drawControl(QStyle::CE_Splitter, &opt, &p, this);
}

void SeparatorWidget::enterEvent(QEvent *)
{
    qCDebug(anchors) << Q_FUNC_INFO << anchor() << isEnabled() << this;
    if (!anchor())
        return;

    if (!isStatic()) {
        if (isVertical())
            setCursor(Qt::SizeHorCursor);
        else
            setCursor(Qt::SizeVerCursor);
    }
}

void SeparatorWidget::leaveEvent(QEvent *)
{
    setCursor(Qt::ArrowCursor);
}

void SeparatorWidget::mousePressEvent(QMouseEvent *)
{
    onMousePress();
}

void SeparatorWidget::mouseMoveEvent(QMouseEvent *e)
{
    onMouseMove(e->globalPos());
}

void SeparatorWidget::mouseReleaseEvent(QMouseEvent *)
{
    onMouseRelease();
}