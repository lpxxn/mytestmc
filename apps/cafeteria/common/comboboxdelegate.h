#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>

namespace McCommon {

class ComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ComboBoxDelegate(QObject *parent = nullptr);
    void setItems(const QStringList &items, bool isEdit);

    ~ComboBoxDelegate() override;

    // QAbstractItemDelegate interface
public:
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QStringList m_itemList;
    bool m_isEdit;
};
}

#endif // COMBOBOXDELEGATE_H
