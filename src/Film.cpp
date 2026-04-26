#include "header/Film.h"

namespace Item{

    Film::Film(unsigned int id, string nome, string descrizione, string imgpath, unsigned int anno, string regista, string produttore, unsigned int durata):
    AbsItem(id, nome, descrizione,imgpath, anno), Regista(regista), Produttore(produttore), Durata(durata){}

    const string& Film::getRegista() const{
        return Regista;
    }

    const string& Film::getProduttore() const{
        return Produttore;
    }

    unsigned int Film::getDurata() const{
        return Durata;
    }

    Film& Film::setRegista(const string& regista){
        this->Regista= regista;
        return *this;
    }

    Film& Film::setProduttore(const string& produttore){
        this->Produttore= produttore;
        return *this;
    }

    Film& Film::setDurata(unsigned int durata){
        this->Durata= durata;
        return *this;
    }

    void Film::accept(Visitor::IVisitor& visitor){
        visitor.visit(*this);
    }

    void Film::acceptconst(Visitor::IConstVisitor& constvisitor) const {
        constvisitor.visit(*this);
    }
    
}
