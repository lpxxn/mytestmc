#include "kvcomboboxdelegate.h"
#include <QComboBox>

namespace McCommon {

template<typename T>
KvComboBoxDelegate<T>::KvComboBoxDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

template<typename T>
QWidget *KvComboBoxDelegate<T>::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QComboBox *editor = new QComboBox(parent);
    for (const auto &item : m_itemList) {
         editor->addItem(item.first(), item.second());
    }
    editor->setEditable(m_isEdit);
    return editor;
}

template<typename T>
void KvComboBoxDelegate<T>::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto currentModel = index.model();
    auto str = currentModel->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentText(str);
}

template<typename T>
void KvComboBoxDelegate<T>::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString str = comboBox->currentText();
    auto userData = comboBox->currentData();
    model->setData(index, str, Qt::EditRole);
    model->setData(index, userData, Qt::UserRole);
}

template<typename T>
void KvComboBoxDelegate<T>::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

}
