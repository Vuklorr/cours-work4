#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    issuerModel = new QSqlTableModel();
    issuerModel->setTable("issuer");
    issuerModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    issuerModel->setHeaderData(0, Qt::Horizontal, "id");
    issuerModel->setHeaderData(1, Qt::Horizontal, "name");
    issuerModel->setHeaderData(2, Qt::Horizontal, "capital");
    issuerModel->setHeaderData(3,Qt::Horizontal, "registration_date");
    issuerModel->select();
    ui->issuerTableView->setModel(issuerModel);
    ui->issuerTableView->setColumnHidden(-1, true);
    ui->issuerTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->issuerTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->issuerTableView->horizontalHeader()->setStretchLastSection(true);

    stockholderModel = new QSqlTableModel();
    stockholderModel->setTable("stockholder");
    stockholderModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    stockholderModel->setHeaderData(0, Qt::Horizontal, "id");
    stockholderModel->setHeaderData(1, Qt::Horizontal, "name");
    stockholderModel->setHeaderData(2,Qt::Horizontal, "type");
    stockholderModel->setHeaderData(3, Qt::Horizontal, "status");
    stockholderModel->select();
    ui->stockholderTableView->setModel(stockholderModel);
    ui->stockholderTableView->setColumnHidden(-1, true);
    ui->stockholderTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->stockholderTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->stockholderTableView->horizontalHeader()->setStretchLastSection(true);

    stockModel = new QSqlTableModel();
    stockModel->setTable("stock");
    stockModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    stockModel->setHeaderData(0, Qt::Horizontal, "id");
    stockModel->setHeaderData(1, Qt::Horizontal, "idIssuer");
    stockModel->setHeaderData(2, Qt::Horizontal, "idStockholder");
    stockModel->setHeaderData(3, Qt::Horizontal, "release_form");
    stockModel->setHeaderData(4, Qt::Horizontal, "amount");
    stockModel->setHeaderData(5, Qt::Horizontal, "nominal_value");
    stockModel->setHeaderData(6, Qt::Horizontal, "date_release");
    stockModel->setHeaderData(7, Qt::Horizontal, "date_expiration");
    stockModel->select();
    ui->stockTableView->setModel(stockModel);
    ui->stockTableView->setColumnHidden(-1, true);
    ui->stockTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->stockTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->stockTableView->horizontalHeader()->setStretchLastSection(true);

    operationModel = new QSqlTableModel();
    operationModel ->setTable("operation");
    operationModel ->setEditStrategy(QSqlTableModel::OnManualSubmit);
    operationModel ->setHeaderData(0, Qt::Horizontal, "id");
    operationModel ->setHeaderData(1, Qt::Horizontal, "idStockholder");
    operationModel ->setHeaderData(2, Qt::Horizontal, "idStock");
    operationModel ->setHeaderData(3, Qt::Horizontal, "date_and_time");
    operationModel ->setHeaderData(4, Qt::Horizontal, "type");
    operationModel ->select();
    ui->operationTableView->setModel(operationModel);
    ui->operationTableView->setColumnHidden(-1, true);
    ui->operationTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->operationTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->operationTableView->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete issuerModel;
    delete stockholderModel;
    delete stockModel;
    delete operationModel;
    delete issuerQueryModel;
    delete stockholderQueryModel;
    delete stockQueryModel;
    delete operationQueryModel;

}

void MainWindow::on_addIssuerPushButton_clicked()
{
    if(!issuerModel->insertRow(issuerModel->rowCount())) {
        QMessageBox::critical(this, "Ошибка при добавлении!",
            QString("Ошибка: %1").arg(issuerModel->lastError().text()),
            QMessageBox::Cancel);
    }

    ui->issuerTableView->selectRow(issuerModel->rowCount() - 1);
}


void MainWindow::on_asseptIssuerPushButton_clicked()
{
    if(!issuerModel->submitAll()) {
        QMessageBox::critical(this, "Ошибка подтверждения!",
            QString("Ошибка: %1").arg(issuerModel->lastError().text()),
            QMessageBox::Cancel);
    }
}

void MainWindow::on_RemoveIssuerPushButton_clicked()
{
    int row = ui->issuerTableView->selectionModel()->currentIndex().row();
    if (row == -1)
        return;
    if (!issuerModel->removeRow(row))
    {
        QMessageBox::critical(this, "Ошибка при удалении!",
            QString("Ошибка: %1").arg(issuerModel->lastError().text()),
            QMessageBox::Cancel);
        return;
    }
}

void MainWindow::on_cancelIssuerPushButton_clicked()
{
    issuerModel->revertAll();
}

void MainWindow::on_SearchPushButton_clicked()
{
    if(ui->YearLineEdit->text().isEmpty() || ui->YearLineEdit->text() < "1791") {
        QMessageBox::critical(nullptr,"Ошибка!", "Введите корректные данные или заполните поле!", QMessageBox::Cancel);
        return;
    }
    issuerModel->setFilter("YEAR(registration_date) = " + ui->YearLineEdit->text());
    issuerModel->select();

}

void MainWindow::on_CancelSearchPushButton_clicked()
{
    issuerModel->setFilter("");
    issuerModel->select();
}

void MainWindow::on_QueryPushButton_clicked()
{
    issuerQueryModel = new QSqlQueryModel();
    if(ui->QueryTextEdit->toPlainText().isEmpty()) {
        QMessageBox::critical(nullptr,"Ошибка!", "Не удалось выполнить поиск. Введите корректный запрос или заполните поле!", QMessageBox::Cancel);
        return;
    }
    issuerQueryModel->setQuery(ui->QueryTextEdit->toPlainText());
    ui->issuerTableView->setModel(issuerQueryModel);

}

void MainWindow::on_CancelQueryPushButton_clicked()
{
    ui->issuerTableView->setModel(issuerModel);
}

void MainWindow::on_addStockholderPushButton_clicked()
{
    if(!stockholderModel->insertRow(stockholderModel->rowCount())) {
        QMessageBox::critical(this, "Ошибка при добавлении!",
            QString("Ошибка: %1").arg(issuerModel->lastError().text()),
            QMessageBox::Cancel);
    }
    ui->stockholderTableView->selectRow(stockholderModel->rowCount() - 1);
}

void MainWindow::on_RemoveStockholderPushButton_clicked()
{
    int row = ui->stockholderTableView->selectionModel()->currentIndex().row();
    if (row == -1)
        return;
    if (!stockholderModel->removeRow(row))
    {
        QMessageBox::critical(this, "Ошибка при удалении!",
            QString("Ошибка: %1").arg(stockholderModel->lastError().text()),
            QMessageBox::Cancel);
        return;
    }
}

void MainWindow::on_asseptStockholderPushButton_clicked()
{
    if(!stockholderModel->submitAll()) {
        QMessageBox::critical(this, "Ошибка подтверждения!",
            QString("Ошибка: %1").arg(stockholderModel->lastError().text()),
            QMessageBox::Cancel);
    }
}

void MainWindow::on_cancelStockholderPushButton_clicked()
{
    stockholderModel->revertAll();
}

void MainWindow::on_stockholderQueryPushButton_clicked()
{
    stockholderQueryModel = new QSqlQueryModel();
    if(ui->stockholderQueryTextEdit->toPlainText().isEmpty()) {
        QMessageBox::critical(nullptr,"Ошибка!", "Не удалось выполнить поиск. Введите корректный запрос или заполните поле!", QMessageBox::Cancel);
        return;
    }
    stockholderQueryModel->setQuery(ui->stockholderQueryTextEdit->toPlainText());
    ui->stockholderTableView->setModel(stockholderQueryModel);
}

void MainWindow::on_stockholderCancelQueryPushButton_2_clicked()
{
    ui->stockholderTableView->setModel(stockholderModel);
}

void MainWindow::on_addOperationPushButton_clicked()
{
    if(!operationModel->insertRow(operationModel->rowCount())) {
        QMessageBox::critical(this, "Ошибка при добавлении!",
            QString("Ошибка: %1").arg(operationModel->lastError().text()),
            QMessageBox::Cancel);
    }
    ui->operationTableView->selectRow(operationModel->rowCount() - 1);
}

void MainWindow::on_RemoveOperationPushButton_clicked()
{
    int row = ui->operationTableView->selectionModel()->currentIndex().row();
    if (row == -1)
        return;
    if (!operationModel->removeRow(row))
    {
        QMessageBox::critical(this, "Ошибка при удалении!",
            QString("Ошибка: %1").arg(operationModel->lastError().text()),
            QMessageBox::Cancel);
        return;
    }
}

void MainWindow::on_asseptOperationPushButton_clicked()
{
    if(!operationModel->submitAll()) {
        QMessageBox::critical(this, "Ошибка подтверждения!",
            QString("Ошибка: %1").arg(operationModel->lastError().text()),
            QMessageBox::Cancel);
    }
}

void MainWindow::on_cancelOperationPushButton_clicked()
{
    operationModel->revertAll();
}

void MainWindow::on_operationQueryPushButton_clicked()
{
    operationQueryModel = new QSqlQueryModel();
    if(ui->operationQueryTextEdit->toPlainText().isEmpty()) {
        QMessageBox::critical(nullptr,"Ошибка!", "Не удалось выполнить поиск. Введите корректный запрос или заполните поле!", QMessageBox::Cancel);
        return;
    }
    operationQueryModel->setQuery(ui->operationQueryTextEdit->toPlainText());
    ui->operationTableView->setModel(operationQueryModel);

}

void MainWindow::on_operationCancelQueryPushButton_clicked()
{
    ui->operationTableView->setModel(operationModel);
}

void MainWindow::on_addStockPushButton_clicked()
{
    if(!stockModel->insertRow(stockModel->rowCount())) {
        QMessageBox::critical(this, "Ошибка при добавлении!",
            QString("Ошибка: %1").arg(stockModel->lastError().text()),
            QMessageBox::Cancel);
    }
    ui->stockTableView->selectRow(stockModel->rowCount() - 1);
}

void MainWindow::on_RemoveStockPushButton_clicked()
{
    int row = ui->stockTableView->selectionModel()->currentIndex().row();
    if (row == -1)
        return;
    if (!stockModel->removeRow(row))
    {
        QMessageBox::critical(this, "Ошибка при удалении!",
            QString("Ошибка: %1").arg(stockModel->lastError().text()),
            QMessageBox::Cancel);
        return;
    }
}

void MainWindow::on_asseptStockPushButton_clicked()
{
    if(!stockModel->submitAll()) {
        QMessageBox::critical(this, "Ошибка подтверждения!",
            QString("Ошибка: %1").arg(stockModel->lastError().text()),
            QMessageBox::Cancel);
    }
}

void MainWindow::on_cancelStockPushButton_clicked()
{
    stockModel->revertAll();
}

void MainWindow::on_stockQueryPushButton_clicked()
{
    stockQueryModel = new QSqlQueryModel();
    if(ui->stockQueryTextEdit->toPlainText().isEmpty()) {
        QMessageBox::critical(nullptr,"Ошибка!", "Не удалось выполнить поиск. Введите корректный запрос или заполните поле!", QMessageBox::Cancel);
        return;
    }
    stockQueryModel->setQuery(ui->stockQueryTextEdit->toPlainText());
    ui->stockTableView->setModel(stockQueryModel);
}

void MainWindow::on_stockCancelQueryPushButton_clicked()
{
    stockModel->setFilter("");
    ui->stockTableView->setModel(stockModel);
}

void MainWindow::on_sumPushButton_clicked()
{
    if(ui->sumLineEdit->text().isEmpty() || ui->sumLineEdit->text() < "0") {
        QMessageBox::critical(nullptr,"Ошибка!", "Введите корректные данные или заполните поле!", QMessageBox::Cancel);
        return;
    }
    stockModel->setFilter("nominal_value > " + ui->sumLineEdit->text());
    stockModel->select();
}

void MainWindow::on_operationPushButton_clicked()
{
    stockQueryModel = new QSqlQueryModel();
    if(ui->comboBox->currentText() == "Дробление") {
        stockQueryModel->setQuery("SELECT s.id,s.release_form,s.amount,s.nominal_value, o.type FROM stock s, operation o WHERE o.idStock = s.id AND o.type = 'Дробление'");
    } else {
        stockQueryModel->setQuery("SELECT s.id,s.release_form,s.amount,s.nominal_value, o.type FROM stock s, operation o WHERE o.idStock = s.id AND o.type = 'Консолидация'");
    }
    ui->stockTableView->setModel(stockQueryModel);
}

void MainWindow::on_periodPushButton_clicked()
{
    if(ui->beginLineEdit->text().isEmpty() || ui->endLineEdit->text().isEmpty()) {// || ui->endLineEdit->text() < '0000-00-00'
        QMessageBox::critical(nullptr,"Ошибка!", "Введите корректные данные или заполните поле!", QMessageBox::Cancel);
        return;
    }
    stockModel->setFilter("'" + ui->beginLineEdit->text() + "' <= date_expiration AND '" + ui->endLineEdit->text() + "' >= date_expiration");
    stockModel->select();
}
