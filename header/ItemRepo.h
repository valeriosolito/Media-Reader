#ifndef ITEMREPO_H
#define ITEMREPO_H

#include <vector>
#include"AbsItem.h"
//#include <Qstring>
using Item::AbsItem;



    namespace Repo{

        class ItemRepo{
            private:

            std::vector<const AbsItem*> IRepository;
            public:
            ItemRepo();
            ~ItemRepo() = default;
            static ItemRepo& getInstance() {
            static ItemRepo instance;
            return instance;
            }
            
            ItemRepo(const ItemRepo&) = delete;
            ItemRepo& operator=(const ItemRepo&) = delete;
            ItemRepo& add(const AbsItem* item);
            bool findId(unsigned int id) const;
            const AbsItem& getItem(unsigned int id) const;
            ItemRepo& remove(unsigned int id);
            size_t size() const;
            std::vector<const AbsItem*>::const_iterator begin() const;
            std::vector<const AbsItem*>::const_iterator end() const;
            ItemRepo& clear();
            std::vector<const Item::AbsItem*> getAll() const;

        };
    }

#endif
