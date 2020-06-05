#include "prods_in_storage.cpp"
#include "interface.cpp"
using namespace std;


class storage_man: public Ideleter, public Iadder{
private:
    storage stor;
    abstract_product* product;
    char* d_name;
public:
    //order_item
    void order_prod(abstract_product* prod){
        product = prod;
        stor.prod_insert(*product);
    }

    void to_modify(char* dish_name){
        d_name = dish_name;
    }

    //delete_
    void delete_item() override{
        QSqlQuery query_1, query_2;
        query_1.prepare("SELECT product, amount FROM recipe WHERE dish_name = ? ");
        query_1.addBindValue(d_name);
        if(!query_1.exec()){ qDebug() << "this is problem with select";}
        else{
            while (query_1.next()) {
                QString name = query_1.value(0).toString();
                int amount = query_1.value(1).toInt();
                stor.prod_delete(name, amount);
            }
        }
    }

    //add_to_stor
    void add_item() override{
       QSqlQuery query_1, query_2;
       query_1.prepare("SELECT product, amount FROM recipe WHERE dish_name = ? ");
       query_1.addBindValue(d_name);
       if(!query_1.exec()){ qDebug() << "this is problem with select";}
       else{
           while (query_1.next()) {
               QString name = query_1.value(0).toString();
               int amount = query_1.value(1).toInt();
               if(stor.in_storage(name, amount) == 1) {
                   cout<<"\nexists\n";
               }
               else if(stor.in_storage(name, amount) == -1){
                   cout<<"\n not exists -> need to add products\n";
                   QSqlQuery a_query;
                   a_query.prepare("INSERT INTO storage(product, amount,temperature, humidity) VALUES (?, ?, 0, 15)");
                   a_query.addBindValue(name);
                   a_query.addBindValue(amount);
                   if(!a_query.exec()){
                       cout<<"\nproduct is in stor but it isnt enough\n";
                       stor.prod_update(name, amount);
                   }
               }
           }
       }
    }
};
