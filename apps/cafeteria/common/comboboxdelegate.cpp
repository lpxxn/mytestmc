#include "comboboxdelegate.h"

namespace McCommon {

ComboBoxDelegate::ComboBoxDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void ComboBoxDelegate::setItems(const QStringList &items, bool isEdit)
{
    this->m_itemList = items;
    this->m_isEdit = isEdit;
}

ComboBoxDelegate::~ComboBoxDelegate()
{

}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString str = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentText(str);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    auto str = comboBox->currentText();
    model->setData(index, str, Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   Q_UNUSED(option)
   Q_UNUSED(index)
   QComboBox *editor = new QComboBox(parent);
   for (const auto &item : m_itemList) {
        editor->addItem(item);
   }
   editor->setEditable(m_isEdit);
   return editor;
}
}
