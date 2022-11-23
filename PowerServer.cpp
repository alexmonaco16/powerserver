#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <cstring>
#include <random>

#include "UDPSocket.h"
#include "SQLDatabase.h"

#define port 16000
#define debug_fill_mode true

string systemtime2datetime(SYSTEMTIME);

void randomFillDatabase(SQLDatabase*, int, int);

int main() {

	UDPSocket* sckt = new UDPSocket();
	cout << " SQL | Inizializzazione Socket UDP sul porto " << port << "\n";
	sckt->init(port);

	cout << " SQL | Connessione al database MySQL\n";
	SQLDatabase* sqld = new SQLDatabase();
	sqld->connect();

	Pacchetto misurazione;
	SYSTEMTIME lt;

	if(debug_fill_mode)
		randomFillDatabase(sqld, 5, 2022);
	else {
		while (1) {
			cout << " UDP | Attendo ricezione pacchetto\n";
			misurazione = sckt->receivePacchetto();

			// prendo il temp attuale
			GetLocalTime(&lt);

			cout << "     | \n";
			cout << " UDP | id = " << misurazione.id << " | consumo = " << misurazione.power << "W \n";
			// converti in formato appropriato
			cout << " SQL | Inserimento dato nel database\n";
			sqld->insertMisurazione(misurazione.id, misurazione.power, systemtime2datetime(lt));
			cout << "     | \n";
		}
	}

	return 0;
}


string systemtime2datetime(SYSTEMTIME localTime) {

	string sqlDatetime = "";
	string temp;

	sqlDatetime += to_string(localTime.wYear);
	sqlDatetime += "-";

	temp = to_string(localTime.wMonth);
	if (temp.length() == 1)
		sqlDatetime += "0";
	sqlDatetime += temp;

	sqlDatetime += "-";

	temp = to_string(localTime.wDay);
	if (temp.length() == 1)
		sqlDatetime += "0";
	sqlDatetime += temp;

	sqlDatetime += " ";

	temp = to_string(localTime.wHour);
	if (temp.length() == 1)
		sqlDatetime += "0";
	sqlDatetime += temp;

	sqlDatetime += ":";

	temp = to_string(localTime.wMinute);
	if (temp.length() == 1)
		sqlDatetime += "0";
	sqlDatetime += temp;

	sqlDatetime += ":";

	temp = to_string(localTime.wSecond);
	if (temp.length() == 1)
		sqlDatetime += "0";
	sqlDatetime += temp;

	return sqlDatetime;
}


void randomFillDatabase(SQLDatabase* sqld, int numberOfSensors, int year) {

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(50, 6000);

	for(int iSensor=50; iSensor<50+numberOfSensors; iSensor++)
		for (int iMonth = 1; iMonth <= 12; iMonth++)
			for (int iDay = 1; iDay <= 28; iDay++)
				for (int iHour = 0; iHour < 24; iHour+=8) {
						string sqlDatetime = "";
						string temp;

						sqlDatetime += to_string(year);
						sqlDatetime += "-";

						temp = to_string(iMonth);
						if (temp.length() == 1)
							sqlDatetime += "0";
						sqlDatetime += temp;

						sqlDatetime += "-";

						temp = to_string(iDay);
						if (temp.length() == 1)
							sqlDatetime += "0";
						sqlDatetime += temp;

						sqlDatetime += " ";

						temp = to_string(iHour);
						if (temp.length() == 1)
							sqlDatetime += "0";
						sqlDatetime += temp;

						sqlDatetime += ":00:00";

						sqld->insertMisurazione(iSensor, distr(gen), sqlDatetime);

						}

}