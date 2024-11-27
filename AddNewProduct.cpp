#include "View/AddNewProduct.h"
#include <QFile>

AddProductWidget::AddProductWidget(QWidget *parent) : QWidget(parent) {
    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        setStyleSheet(style);
    }
    setWindowTitle("Add New Product");
    setFixedWidth(800);

    QFormLayout *formLayout = new QFormLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    nameEdit = new QLineEdit;
    categoryEdit = new QLineEdit;
    priceSpin = new QDoubleSpinBox;
    stockSpin = new QSpinBox;
    descriptionEdit = new QLineEdit;
    detailEdit = new QLineEdit;
    brandEdit = new QLineEdit;

    priceSpin->setRange(0.0, 1000000.0);
    priceSpin->setDecimals(2);
    stockSpin->setRange(0, 1000000);

    formLayout->addRow("Name:", nameEdit);
    formLayout->addRow("Category:", categoryEdit);
    formLayout->addRow("Price:", priceSpin);
    formLayout->addRow("Stock:", stockSpin);
    formLayout->addRow("Description:", descriptionEdit);
    formLayout->addRow("Detail (comma-separated):", detailEdit);
    formLayout->addRow("Brand:", brandEdit);

    QPushButton *okButton = new QPushButton("OK");
    QPushButton *cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    connect(okButton, &QPushButton::clicked, this, &AddProductWidget::onOkButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AddProductWidget::onCancelButtonClicked);

    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void AddProductWidget::onOkButtonClicked() {
    Product newProduct;
    AppController appController;
    DataController dataController;

    newProduct.setProductId(appController.createProductId());
    newProduct.setName(nameEdit->text().toStdString());
    newProduct.setCategory(categoryEdit->text().toStdString());
    newProduct.setPrice(priceSpin->value());
    newProduct.setStock(stockSpin->value());
    newProduct.setDescription(descriptionEdit->text().toStdString());

    QStringList detailsList = detailEdit->text().split(',');
    Vector<string> detailVector;
    for (const QString &detailStr : detailsList) {
        detailVector.pushback(detailStr.trimmed().toStdString());
    }
    newProduct.setDetail(detailVector);
    newProduct.setBrand(brandEdit->text().toStdString());

    dataController.addNewProduct(newProduct);

    emit productAdded();  // Gửi signal để thông báo sản phẩm đã được thêm
    this->hide();
    parentWidget()->show();
}

void AddProductWidget::onCancelButtonClicked() {
    emit canceled();  // Gửi signal để thông báo người dùng hủy bỏ
    this->hide();
    parentWidget()->show();
}
