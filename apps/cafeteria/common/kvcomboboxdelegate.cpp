#include "kvcomboboxdelegate.h"
#include <QComboBox>

namespace McCommon {

KvComboBoxDelegate::KvComboBoxDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

void KvComboBoxDelegate::setItems(const QList<QPair<QString, int>> &items, bool isEdit)
{
    this->m_itemList = items;
    this->m_isEdit = isEdit;
}

QWidget *KvComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QComboBox *editor = new QComboBox(parent);
    for (const auto &item : m_itemList) {
         editor->addItem(item.first, QVariant::fromValue(item.second));
    }
    editor->setEditable(m_isEdit);
    return editor;
}

void KvComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto currentModel = index.model();
    auto str = currentModel->data(index, Qt::DisplayRole).toString();
    auto id = currentModel->data(index, Qt::EditRole).toString().toInt();
    for (const auto &item : m_itemList) {
        if (item.second == id) {
            str = item.first;
            break;
        }
    }
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setFocus();
    comboBox->setCurrentText(str);
}

void KvComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString str = comboBox->currentText();
    auto userData = comboBox->currentData().toInt();
    model->setData(index, str, Qt::DisplayRole);
    model->setData(index, userData, Qt::EditRole);
}

void KvComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

}
