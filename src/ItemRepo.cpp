#include "header/ItemRepo.h"

namespace Repo{

    ItemRepo::ItemRepo(){}

    ItemRepo& ItemRepo::add(const AbsItem* item){
        IRepository.push_back(item);
        return *this;
    } 

    bool ItemRepo::findId(unsigned int id) const {
        for(const auto& prod : IRepository){
            if(prod->getId() == id)
                return true;
        }
        return false;
    }

    const AbsItem& ItemRepo::getItem(unsigned int id) const {
        for(auto it = IRepository.begin(); it!=IRepository.end(); it++){
            if((*it)->getId()==id){
                return *(*it);
            }
        }
        throw string("L'id non è presente");
    }

    ItemRepo& ItemRepo::remove(unsigned int id){
        for(auto it = IRepository.begin(); it!= IRepository.end(); it++){
            if((*it)->getId() == id){
                delete *it;
                IRepository.erase(it);
                return *this;
            }
        }
        return *this;
    }

    size_t ItemRepo::size() const {
        return IRepository.size();
    }

    std::vector<const Item::AbsItem*>::const_iterator ItemRepo::begin() const{
        return IRepository.begin();
    }

    std::vector<const Item::AbsItem*>::const_iterator ItemRepo::end() const{
        return IRepository.end();
    }

    ItemRepo& ItemRepo::clear(){
        for(auto it = IRepository.begin(); it!= IRepository.end(); it++){
            delete *it;
        }
        IRepository.clear();
        return *this;
    }

    std::vector<const Item::AbsItem*> ItemRepo::getAll() const {
        return IRepository;
    }

}
