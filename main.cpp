#include "mainwindow.h"

bool conect() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("test");
    db.setPassword("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");
    db.setDatabaseName("4kurs");

    if(!db.open()) {
        QMessageBox::critical(nullptr,"Ошибка!", "Не удалось подключится к БД", QMessageBox::Cancel);
        return false;
    }
    return true;
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!conect()) {
        exit(0);
    }

    MainWindow w;
    w.show();
    return a.exec();
}
