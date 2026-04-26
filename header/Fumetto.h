#ifndef FUMETTO_H
#define FUMETTO_H

#include "AbsItem.h"
#include <string>
using std::string;
namespace Item{
    class Fumetto: public AbsItem{
        private:
        string Autore;
        string Disegnatore;
        unsigned int Pagine;
        string Editore;

        public:
        Fumetto(unsigned int id, string nome, string descrizione, string imgpath, unsigned int anno, string autore, string disegnatore, unsigned int pagine, string editore);

        const string& getAutore() const;
        const string& getDisegnatore() const;
        unsigned int getPagine() const;
        const string& getEditore() const;

        Fumetto& setAutore(const string& autore);
        Fumetto& setDisegnatore(const string& disegnatore);
        Fumetto& setPagine(unsigned int pagine);
        Fumetto& setEditore(const string& editore);

        virtual void accept(Visitor::IVisitor& visitor) final;
        virtual void acceptconst(Visitor::IConstVisitor& constvisitor) const final;


    };
}
#endif