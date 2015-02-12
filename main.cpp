#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtSql/QtSql>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    QSqlDatabase db;
    db =  QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("myRestSQL.db3");

    if (db.open()) {
        QSqlQuery query(db);
        qDebug() << "Before inserting";
        query.exec("SELECT * FROM testing");
        while (query.next()) {
            int oid = query.value(0).toInt();
            qDebug() << oid;
        }
        if (query.exec("CREATE TABLE testing ( INTEGER oid PRIMARY KEY);")) {
            qDebug() << "Created 'testing' table";
            if (query.exec("INSERT INTO testing (oid) VALUES (42)")) {
                qDebug() << "Insert row in 'testing' table";
            }
            qDebug() << "After inserting";
            query.exec("SELECT * FROM testing");
            while (query.next()) {
                int oid = query.value(0).toInt();
                qDebug() << oid;
            }
        } else {
            qDebug() << "Unable to create 'testing' table" << query.lastError();
        }
    } else {
        qDebug() << "Unable to open the database";
    }
    db.close();

    return app.exec();
}
