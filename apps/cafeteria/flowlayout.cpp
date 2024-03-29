#include "flowlayout.h"

#include <QtWidgets>

FlowLayout::FlowLayout(QWidget *parent, int margin, int hSpace, int vSpacing)
    : QLayout(parent), m_hSpace(hSpace), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::FlowLayout(int margin, int hSpace, int vSpacing)
    : m_hSpace(hSpace), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

int FlowLayout::horizontalSpacing() const
{
    if (m_hSpace >= 0) {
        return m_hSpace;
    }
    return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
}

int FlowLayout::verticalSpacing() const
{
    if (m_vSpace >= 0) {
        return m_vSpace;
    }
    return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
}

FlowLayout::~FlowLayout()
{
   qDeleteAll(this->itemList);
}

void FlowLayout::addItem(QLayoutItem *item)
{
    itemList.append(item);
}

Qt::Orientations FlowLayout::expandingDirections() const
{
    return 0;
}

bool FlowLayout::hasHeightForWidth() const
{
    return true;
}

int FlowLayout::heightForWidth(int width) const
{
    int height = doLayout(QRect(0, 0, width, 0), true);
    return height;
}

int FlowLayout::count() const
{
    return itemList.size();
}

QLayoutItem *FlowLayout::itemAt(int index) const
{
    return itemList.value(index);
}

QSize FlowLayout::minimumSize() const
{
     QSize size;
     for (const QLayoutItem *item : qAsConst(itemList)) {
         size = size.expandedTo(item->minimumSize());
     }
     const QMargins margins = contentsMargins();
     size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
     return size;
}

void FlowLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

QSize FlowLayout::sizeHint() const
{
    return minimumSize();
}

QLayoutItem *FlowLayout::takeAt(int index)
{
    if (index >= 0 && index <= itemList.size()) {
        return itemList.takeAt(index);
    }
    return nullptr;
}

int FlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect =rect.adjusted(+left, +top, +right, +bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;
    foreach (auto item, itemList) {
         QWidget *wid = item->widget();
         int spaceX = horizontalSpacing();
         if (spaceX == -1)
             spaceX = wid->style()->layoutSpacing(
                 QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
         int spaceY = verticalSpacing();
         if (spaceY == -1)
             spaceY = wid->style()->layoutSpacing(
                 QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);
         int nextX = x + item->sizeHint().width() + spaceX;
         if (nextX - spaceX > effectiveRect.right() && lineHeight > 0) {
             x = effectiveRect.x();
             y = y + lineHeight + spaceY;
             nextX = x + item->sizeHint().width() + spaceX;
             lineHeight = 0;
         }

         if (!testOnly)
             item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

         x = nextX;
         lineHeight = qMax(lineHeight, item->sizeHint().height());
     }
     return y + lineHeight - rect.y() + bottom;
}

int FlowLayout::smartSpacing(QStyle::PixelMetric pm) const
{
    QObject *parent = this->parent();
    if (!parent) {
        return -1;
    } else if (parent->isWidgetType()) {
        QWidget *pw = static_cast<QWidget *>(parent);
        return pw->style()->pixelMetric(pm, nullptr, pw);
    } else {
        return static_cast<QLayout *>(parent)->spacing();
    }
}
