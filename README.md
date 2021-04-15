# Chess
Simple console chess app using C++ and object-oriented approach


Opis projektu w języku polskim

Pliki źródłowe:
chess.cpp - uruchomienie konsoli i sterowanie przebiegiem wykonywania programu

chessboard.cpp - wyświetlenie szachownicy i interfejsu użytkownika na konsoli
	void sendMessage(string)        - wyświetlinie komunikatów
	string getInput()               - wczytywanie poleceń
	void boardRefresh()             - odświeżenie szachownicy po dokonanych zmaianach
	void roof()------------------}
	void ceiling()               }  - funkcje pomocnicze do boardRefresh()
	void floor()-----------------}

game.cpp - przebieg gry i weryfikacja ogólnych zasad
	bool checkInput(string input)           - sprawdza czy polecenie gracza jest poprawne
	void loadGame()                         - odtwarza zapisaną wcześniej partię
	void saveGame()                         - zapisuje niedokończoną partię
	void startGame()                        - zaczyna nową partię
	int* parseCommand(string)               - rozpoznaje wczytane polecenie
	Piece* getPiece(int, int)               - zwraca obiekt bierki z pola szachownicy
	string getTurn()                        - sprawdza bieżącą kolej ruchu
	void changeTurn()                       - zmienia kolej ruchu
	void moveKing(int, int)                 - zapisuje zmianę pozycji króla
	bool checkBoard(int, int, int, int)     - sprawdza czy można wykonać posunięcie pomiędzy tymi polami
	void changePosition(int, int, int, int) - zmienia pozycję bierki
	void saveMove(int, int, int, int);
	
	bool simulateMove(int, int, int, int);  - sprawdza czy nie zostanie własny król szachowany po wykonaniu posunięcia
	void cleanBoard();                      - funkcja pomocnicza do simulateMove(int, int, int, int)
	bool checkUnderAttack(string);          - sprawdza czy nie jest król szacowany
	bool checkMate(string);                 - sprawdza czy nie jest mat
	bool checkStalemate(string);            - sprawdza czy nie jest pat
	
piece.cpp - wirtualna klasa bierki i dziedziczące:
	bishop.cpp  - goniec
	king.cpp    - król
	knight.cpp  - skoczek
	queen.cpp   - hetman
	pawn.cpp    - pion
	rook.cpp    - wieża
Metody wirtualne, nadpisywane w klasach pochodnych:
	    virtual bool movePiece(int, int, int, int, string) = 0; - wykonanie posunięcia
	    virtual string getSymbol() = 0;                         - zwraca oznaczenie bierki na szachownicy
	    virtual bool checkMove(int, int, int, int) = 0;         - sprawdza czy bierkę można tak posunąć
Ogólne metody:    
	string getType();           - pobiera rodzaj bierki
	string getColor();          - pobiera kolor bierki
bool getEnPassant();            - sprawdza czy pion jest w sytuacji, gdy jest możliwe jego "Bicie w przelocie"
