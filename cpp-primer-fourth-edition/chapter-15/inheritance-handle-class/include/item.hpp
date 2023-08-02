#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <string>

class ItemBase {
private:
    std::string isbn; // identifier for the item

protected:
    double price;     // normal price

public:
    ItemBase(const std::string &isbn = "", const double price = 0.0)
        : isbn(isbn), price(price) {}

    const std::string& book() const {
        return isbn;
    }

    // returns total sales price for a specified number of items    
    // derived classes will override and apply different discount algorithms
    virtual double net_price(const size_t count) const {
        return price * count;
    }

    // no work, but virtual destructor needed 
    // if base pointer that points to a derived object is ever deleted
    virtual ~ItemBase() {}
};

class BulkItem : public ItemBase {
private:
    size_t min_qty; // minimum purchase for discount to apply
    double discount; // fractional discount to apply

public:
    BulkItem() : min_qty(0), discount(0) {}
    BulkItem(const std::string &isbn = "", const double price = 0.0,
        const size_t min_qty = 0, const double discount = 0.0)
        : ItemBase(isbn, price), min_qty(min_qty), discount(discount) {}
    
    // redefines base version so as to implement bulk purchase discount policy
    double net_price(const size_t count);
};

// use counted handle class for the Item_base hierarchy 
class SalesItem {
private:
    ItemBase *base; // pointer to shared item
    size_t *use;    // pointer to shared use count

    void decr_use() {
        if (--*use == 0) {
            delete base; delete use;
        }
    }

public:
    SalesItem() : base(nullptr), use(new size_t(1)) {}

    // attaches a handle to a copy of the Item_base object
    SalesItem(const ItemBase&); 

    // copy control members to manage the use count and pointers
    SalesItem(const SalesItem &i): base(i.base), use(i.use) { ++*use; }
    
    SalesItem& operator=(const SalesItem&);

    // member access operators
    const ItemBase* operator->() const { 
        return base ? base : nullptr;
    
    const ItemBase& operator*() const {
        return *base;
    }

    ~SalesItem() { decr_use(); }
};


#endif /* __ITEM_HPP__ */