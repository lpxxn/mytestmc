#include "supplierform.h"
#include "ui_supplierform.h"

#include <QLabel>
#include <QDockWidget>
#include <QPushButton>
#include <QVBoxLayout>

void SupplierForm::addButtons(FlowLayout &layout) {
    QPushButton *pb2 = new QPushButton("b");
    pb2->setMaximumWidth(100);
    pb2->setMinimumHeight(80);
    layout.addWidget(pb2);
}

SupplierForm::SupplierForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SupplierForm)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);
    this->setWindowModality(Qt::WindowModal);
    if (parent == nullptr) {
        this->setAttribute(Qt::WA_DeleteOnClose, true);
    }
    //this->centralWidget()->hide();
    this->setCentralWidget(nullptr);
    this->setDockNestingEnabled(true);

    leftDock = new QDockWidget(QLatin1String("Left"), this);
    QWidget* multiWidget = new QWidget();
    //multiWidget->setMaximumWidth(110);

    FlowLayout* layout = new FlowLayout;
    QPushButton *pb = new QPushButton("a");
    pb->setMaximumWidth(100);
    pb->setMinimumHeight(80);
    connect(pb, &QPushButton::clicked, this, &SupplierForm::leftDockWidgetReset);
    layout->addWidget(pb);

    addButtons(*layout);
    addButtons(*layout);
    addButtons(*layout);


    multiWidget->setLayout(layout);
    leftDock->setWidget(multiWidget);
    //dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    //dock->setAllowedAreas(Qt::NoDockWidgetArea);
    //leftDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);


    addNewDock();
    addNewDock();
    addNewDock();
}

SupplierForm::~SupplierForm()
{
    delete ui;
}

void SupplierForm::on_btnAddDock_clicked()
{
    addNewDock();

}

void SupplierForm::leftDockWidgetReset()
{
    this->leftDock->setFloating(false);
    //this->restoreDockWidget(this->leftDock);
}

void SupplierForm::addNewDock()
{
    QDockWidget *dock = new QDockWidget(QLatin1String("Last filters"), this);
    QWidget* multiWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    QPushButton* filter1 = new QPushButton(QLatin1String("Filter number 1"));
    QPushButton* filter2 = new QPushButton(QLatin1String("Filter number 2"));
    QPushButton* filter3 = new QPushButton(QLatin1String("Filter number 3"));
    QPushButton* filter4 = new QPushButton(QLatin1String("Filter number 4"));
    QPushButton* filter5 = new QPushButton(QLatin1String("Filter number 5"));
    QLabel* label = new QLabel(QLatin1String("QPushButtons"));

    layout->addWidget(filter1);
    layout->addWidget(filter2);
    layout->addWidget(filter3);
    layout->addWidget(filter4);
    layout->addWidget(filter5);
    layout->addWidget(label);
    multiWidget->setLayout(layout);
    dock->setWidget(multiWidget);
    //dock->setFeatures(QDockWidget::AllDockWidgetFeatures);//设置此窗体所有特性--可关闭,可移动,可浮动
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);
    //dock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock);
}
