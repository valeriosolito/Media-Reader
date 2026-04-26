#ifndef FILM_H
#define FILM_H

#include "AbsItem.h"
#include <string>
using std::string;
namespace Item{
    class Film: public AbsItem{
        private:
        string Regista;
        string Produttore;
        unsigned int Durata;
        
        public:
        Film(unsigned int id, string nome, string descrizione, string imgpath, unsigned int anno, string regista, string produttore, unsigned int durata);
        
        const string& getRegista() const;
        const string& getProduttore() const;
        unsigned int getDurata() const;

        Film& setRegista(const string& regista);
        Film& setProduttore(const string& produttore);
        Film& setDurata(unsigned int durata);

        virtual void accept(Visitor::IVisitor& visitor) final;
        virtual void acceptconst(Visitor::IConstVisitor& constvisitor) const final;
    };
}
#endif
