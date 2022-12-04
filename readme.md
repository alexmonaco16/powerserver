# Powerserver
## _The Last Markdown Editor, Ever_

[![N|Solid](https://cldup.com/dTxpPi9lDf.thumb.png)](https://nodesource.com/products/nsolid)

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

Dillinger is a cloud-enabled, mobile-ready, offline-storage compatible,
AngularJS-powered HTML5 Markdown editor.

- Type some Markdown on the left
- See HTML in the right
- ✨Magic ✨

# Obiettivi

Si vuole sviluppare un applicativo (powerserver), in esecuzione 24/7 su una macchina dedicata, che sia dedicato alla ricezione e alla gestione dei dati sulle misurazioni ricevuti tramite rete dai sensori di consumo elettrico.\\
Il powerserver ha anche la responsabilità di gestire l'autoregistrazione dei sensori e la memorizzazione dei dati sulle misurazioni in un database.
Il database in non deve necessariamente risiedere sulla medesima macchina del powerserver, sebbene nelle nostre prove sia di fatto così.


# Librerie utilizzate

### MySQL Connector/C++
Per la connessione al database MySQL, essendo il nostro applicativo realizzato in linguaggio C++, si è optato per l'utilizzo della libreria MySQL Connector/C++ 8.0.
Tale libreria, per l'interazione con un database, implementa tre diverse API:
- X DevAPI scritte in C++
- X DevAPI scritte in C
- le API legacy basate su JDBC4 (presenti fin dalla versione 1.1 della libreria)

Considerando la maggiore intuitività di utilizzo, la più ricca documentazione disponibile e la relativa semplicità delle query che il powerserver deve eseguire, si è optato per la terza.

### Winsock2
Per la comunicazione tramite rete con i sensori IoT si è scelto di utilizzare il protocollo di trasporto User Datagram Protocol (UDP) che, per la sua natura connection-less (rispetto a TCP), risulta molto rapido ed efficiente per applicazioni leggere e time-sensitive come la nostra.
Si è utilizzato un server Windows (ma si potrebbe tranquillamente fare un porting per server Linux).
Al fine di implementare la socket UDP lato server si utilizza la libreria Winsock fornita da tale sistema operativo.
Winsock è un adattamento per Windows delle socket Berkeley di UNIX.
Winsock, attraverso la sua dynamic-link library winsock.dll fa da tramite fra il nostro applicativo e il modello TCP/IP.
