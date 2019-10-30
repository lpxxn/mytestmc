#ifndef FLOWLAYOUT_H
#define FLOWLAYOUT_H
#include <QLayout>
#include <QRect>
#include <QStyle>

class FlowLayout : public QLayout
{
public:
    FlowLayout(QWidget *parent, int margin = -1, int hSpace = -1, int vSpacing = -1);
    FlowLayout(int margin = -1, int hSpace = -1, int vSpacing = -1);
    int horizontalSpacing() const;
    int verticalSpacing() const;

    ~FlowLayout() override;

    // QLayoutItem interface
public:
    void addItem(QLayoutItem *) override;
    Qt::Orientations expandingDirections() const override;
    bool hasHeightForWidth() const override;
    int heightForWidth(int) const override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &) override;
    QSize sizeHint() const override;
    QLayoutItem *takeAt(int index) override;

private:
    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

    QList<QLayoutItem*> itemList;
    int m_hSpace;
    int m_vSpace;

};

#endif // FLOWLAYOUT_H
