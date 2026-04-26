#include "header/AbsItem.h"

namespace Item{
    
    AbsItem::AbsItem(unsigned int id, string nome, string descrizione, string imgpath, unsigned int anno): 
    Id(id), Nome(nome), Descrizione(descrizione), Imgpath(imgpath), Anno(anno) {}

    unsigned int AbsItem::getId() const {
        return Id;
    }
    const string& AbsItem::getNome() const{
        return Nome;
    }
    const string& AbsItem::getDescrizione() const {
        return Descrizione;
    }
    const string& AbsItem::getImgpath() const{
        return Imgpath;
    }
    unsigned int AbsItem::getAnno() const {
        return Anno;
    }

    AbsItem& AbsItem::setId(unsigned int id){
        this->Id = id;
        return *this;
    }

    AbsItem& AbsItem::setNome(const string& nome){
        this->Nome = nome;
        return *this;
    }

    AbsItem& AbsItem::setDescrizione(const string& descrizione){
        this->Descrizione = descrizione;
        return *this;
    }

    AbsItem& AbsItem::setImgPath(const string& imgpath){
        this->Imgpath = imgpath;
        return *this;
    }

    AbsItem& AbsItem::setAnno(unsigned int anno){
        this->Anno= anno;
        return *this;
    }

}