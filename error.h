//
// Created by chrim on 12/06/2020.
//

/*
	Usaggio suggerito:
		class ClasseTargetError : public Error {
		public:
			enum ErrorCode {
				UNDEFINED,
				... // altro in base alle esigenze
			};
		private:
			static const char * codeToMessage(ErrorCode); // con una conversione da codice definito in ErrorCode a stringa.
		public:
			costruttore(ErrorCode) per messaggi serializzati
			costruttore(const char * ) per messaggi non serializzati (richiamerà Error(const char *)
			
			con l'operatore di Error potrà essere usato nei contesti dove è richiesto uno string literal
		}

*/

#ifndef ZOMBIEDUNGEON_ERROR_H
#define ZOMBIEDUNGEON_ERROR_H


class Error {
    const char * _message;
public:
    Error(const char *);

    // non c'è bisogno di definire distruttore assegnazione e copia
    // i const char * sono degli string literal, non occorre gestirli

    operator const char *() const;
};

// TEMPO 0.5h

#endif //ZOMBIEDUNGEON_ERROR_H
