#include "customerurisetting.h"
#include "ui_customeurisetting.h"

#include <QDir>
#include <QMessageBox>
#include <QSqlDatabase>


CustomerUriSetting::CustomerUriSetting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CostomeURISetting)
{
    ui->setupUi(this);
    //QWidget::setWindowFlags(this->windowFlags()|Qt::Dialog);
    //QWidget::setWindowModality(Qt::WindowModal);
    // as modal type
    QMainWindow::setWindowModality(Qt::ApplicationModal);
    if (parent == nullptr) {
        this->setAttribute(Qt::WA_DeleteOnClose);
    }

    if (openDb()) {
        openTable();
    }
}

CustomerUriSetting::~CustomerUriSetting()
{
    delete ui;
}

bool CustomerUriSetting::openDb(const QString &dbPath)
{
    qDebug() << dbPath;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        QMessageBox::warning(this, "error", "open database false\n" + db.lastError().text(), QMessageBox::Ok);
        return false;
    }
    this->ui->actOpenNewDB->setEnabled(false);
    return true;
}

void CustomerUriSetting::openTable()
{
    tableModel = new QSqlTableModel(this, this->db);
    tableModel->setTable("uri_info");
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    //tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    if (!tableModel->select()) {
        QMessageBox::critical(this, "error", "open table error\n" + tableModel->lastError().text(), QMessageBox::Ok);
        return;
    }
    tableModel->setHeaderData(tableModel->fieldIndex("id"),Qt::Horizontal,"ID");
    tableModel->setHeaderData(tableModel->fieldIndex("project_id"),Qt::Horizontal,"projectID");
    tableModel->setHeaderData(tableModel->fieldIndex("name"),Qt::Horizontal,"name");
    tableModel->setHeaderData(tableModel->fieldIndex("uri"),Qt::Horizontal,"URI");
    tableModel->setHeaderData(tableModel->fieldIndex("method"),Qt::Horizontal,"method");
    tableModel->setHeaderData(tableModel->fieldIndex("body_type"),Qt::Horizontal,"body_type");
    tableModel->setHeaderData(tableModel->fieldIndex("body1"),Qt::Horizontal,"body1");
    tableModel->setHeaderData(tableModel->fieldIndex("body2"),Qt::Horizontal,"body2");
    tableModel->setHeaderData(tableModel->fieldIndex("need_oauth"),Qt::Horizontal,"need_oauth");

    itemSelectionModel = new QItemSelectionModel(tableModel);

    ui->tableView->setModel(tableModel);
    ui->tableView->setSelectionModel(itemSelectionModel);

    QSqlQuery projectQuery("select * from projects;");
    projectQuery.exec();
    int idIdx = projectQuery.record().indexOf("id");
    int nameIdx = projectQuery.record().indexOf("name");
    QList<QPair<QString, int>> itemList;
    while (projectQuery.next()) {
        auto name = projectQuery.record().value(nameIdx).toString();
        auto id = projectQuery.record().value(idIdx).toInt();
        itemList.append(qMakePair(name, id));
    }
    projectDelegate.setItems(itemList, false);
    ui->tableView->setItemDelegateForColumn(tableModel->fieldIndex("project_id"), &projectDelegate);
    auto departmentIdx = tableModel->fieldIndex("project_id");
    for (int i = 0; i < tableModel->rowCount(); i++)
    {
        ui->tableView->openPersistentEditor(tableModel->index(i, departmentIdx));
    }
    connect(tableModel, &QSqlTableModel::beforeUpdate, this, [=](int row, QSqlRecord &record){
        qDebug() << row;
        for (int i = 0; i < record.count();  i++) {
            qDebug() << record.fieldName(i);
            qDebug() << record.value(i);
        }
    });
}
