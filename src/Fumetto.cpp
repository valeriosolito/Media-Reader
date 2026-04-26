#include "header/Fumetto.h"

namespace Item{

    Fumetto::Fumetto(unsigned int id, string nome, string descrizione, string imgpath, unsigned int anno, string autore, string disegnatore, unsigned int pagine, string editore):
    AbsItem(id, nome, descrizione, imgpath, anno), Autore(autore), Disegnatore(disegnatore), Pagine(pagine), Editore(editore){}

    const string& Fumetto::getAutore() const {
        return Autore;
    }

    const string& Fumetto::getDisegnatore() const {
        return Disegnatore;
    }

    unsigned int Fumetto::getPagine() const {
        return Pagine;
    }

    const string& Fumetto::getEditore() const {
        return Editore;
    }

    Fumetto& Fumetto::setAutore(const string& autore){
        this->Autore = autore;
        return *this;
    }

    Fumetto& Fumetto::setDisegnatore(const string& disegnatore){
        this->Disegnatore = disegnatore;
        return *this;
    }

    Fumetto& Fumetto::setPagine(unsigned int pagine){
        this->Pagine = pagine;
        return *this;
    }

    Fumetto& Fumetto::setEditore(const string& editore){
        this->Editore = editore;
        return *this;
    }

    void Fumetto::accept(Visitor::IVisitor& visitor){
        visitor.visit(*this);
    }

    void Fumetto::acceptconst(Visitor::IConstVisitor& constvisitor) const {
        constvisitor.visit(*this);
    }

}
