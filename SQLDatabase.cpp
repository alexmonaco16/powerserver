#include "SQLDatabase.h"

SQLDatabase::SQLDatabase() {
    driver = get_driver_instance();
    con = NULL;
    stmt = NULL;
    pstmt = NULL;
}

void SQLDatabase::connect() {
    try {
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    try {
        con->setSchema(db_name);
    }
    catch (sql::SQLException e) {
        cout << "Impossibile aprire il database \"" << db_name << "\". Errore: " << e.what() << endl;
        system("pause");
        exit(1);
    }
}

void SQLDatabase::insertMisurazione(int idSensore, int potenzaConsumata, string dataOra) {
    insertNewSensoreIfNotExists(idSensore);

    pstmt = con->prepareStatement("INSERT INTO misurazioni(id, consumo, data, idSensore) VALUES(?,?,?,?)");
    pstmt->setInt(1, 0);
    pstmt->setInt(2, potenzaConsumata);
    pstmt->setString(3, dataOra);
    pstmt->setInt(4, idSensore);
    try {
        pstmt->execute();
    }
    catch (sql::SQLException e) {
        cout << "Impossibile inserire nel database. Errore: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    cout << " SQL | Riga (" << potenzaConsumata << ", " << dataOra << ", " << idSensore << ") inserita nel database." << endl;
    delete pstmt;
}


void SQLDatabase::insertNewSensoreIfNotExists(int idSensore) {
    pstmt = con->prepareStatement("INSERT IGNORE INTO sensori(id, descrizione, sogliaMax, idAzienda) VALUES(?,?,99999,0)");
    pstmt->setInt(1, idSensore);
    pstmt->setString(2, "nuovo sensore");
    try {
        pstmt->execute();
    }
    catch (sql::SQLException e) {
        cout << "Impossibile inserire nel database. Errore: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    cout << " SQL | NUOVO Sensore (" << idSensore << ") registrato nel database (se non presente)." << endl;
    delete pstmt;
}