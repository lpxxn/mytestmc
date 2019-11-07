#ifndef KVCOMBOBOXDELEGATE_H
#define KVCOMBOBOXDELEGATE_H

#include <QObject>
#include <QList>
#include <QPair>
#include <QStyledItemDelegate>

namespace McCommon {

template<typename T>
class KvComboBoxDelegate : public QStyledItemDelegate
{
public:
    KvComboBoxDelegate(QObject *parent = nullptr);


private:
    QList<QPair<QString, T>> m_itemList;
    bool m_isEdit;

    // QAbstractItemDelegate interface
public:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
}
#endif // KVCOMBOBOXDELEGATE_H
