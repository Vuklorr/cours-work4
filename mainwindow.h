#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QSqlTableModel>
#include <QTableView>
#include <QMessageBox>
#include <QString>

#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addIssuerPushButton_clicked();
    void on_asseptIssuerPushButton_clicked();
    void on_RemoveIssuerPushButton_clicked();
    void on_cancelIssuerPushButton_clicked();
    void on_SearchPushButton_clicked();
    void on_CancelSearchPushButton_clicked();
    void on_QueryPushButton_clicked();
    void on_CancelQueryPushButton_clicked();



    void on_addStockholderPushButton_clicked();

    void on_RemoveStockholderPushButton_clicked();

    void on_asseptStockholderPushButton_clicked();

    void on_cancelStockholderPushButton_clicked();

    void on_stockholderQueryPushButton_clicked();

    void on_stockholderCancelQueryPushButton_2_clicked();

    void on_addOperationPushButton_clicked();

    void on_RemoveOperationPushButton_clicked();

    void on_asseptOperationPushButton_clicked();

    void on_cancelOperationPushButton_clicked();

    void on_operationQueryPushButton_clicked();

    void on_operationCancelQueryPushButton_clicked();

    void on_addStockPushButton_clicked();

    void on_RemoveStockPushButton_clicked();

    void on_asseptStockPushButton_clicked();

    void on_cancelStockPushButton_clicked();

    void on_stockQueryPushButton_clicked();

    void on_stockCancelQueryPushButton_clicked();

    void on_sumPushButton_clicked();

    void on_operationPushButton_clicked();

    void on_periodPushButton_clicked();

private:
    Ui::MainWindow *ui;

    QSqlTableModel *issuerModel;
    QSqlQueryModel *issuerQueryModel;

    QSqlTableModel *stockholderModel;
    QSqlQueryModel *stockholderQueryModel;

    QSqlTableModel *stockModel;
    QSqlQueryModel *stockQueryModel;

    QSqlTableModel *operationModel;
    QSqlQueryModel *operationQueryModel;

};
#endif // MAINWINDOW_H
