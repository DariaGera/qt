#include <vector>
#include <iostream>
#include <QtSql>
using namespace std;

class abstract_product {
protected:
    char* product_name;
    int amount;
    int temperature;
    int humidity;
public:
    virtual void Storage_form(int temperature, int humidity) = 0;

    //constructor
    void Construct_product(int amoUnt, string name, int temp = 0, int humi = 0) {
        product_name = const_cast<char*>(name.c_str());
        amount = amoUnt;
        //product_name = name;
        temperature = temp;
        humidity = humi;
    }

    //destructor
    ~abstract_product(){cout<<"\ndestructor(abstract_product) is called"<<endl;}

    //setter

    void Amount(int amoUnt) { amount = amoUnt; }
    void Product_name(char* name) { product_name = name; }
    void Temperature(int temp) { temperature = temp; }
    void Humidity(int humi) { humidity = humi; }


    //getter

    int GetAmount() { return amount; }
    char* GetProductName() { return product_name; }
    int GetTemperature() { return temperature; }
    int GetHumidity() { return humidity; }
};


class meat : public abstract_product {

public:
    //virtual function that keeps products fresh
    void Storage_form(int temperature, int humidity) override {
        cout << "special temperature " << temperature << " and humidity " << humidity << " and special control";
    }

};


class milk_product : public abstract_product {

public:


    //virtual function that keeps products fresh
    void Storage_form(int temperature, int humidity) override {
        cout << "special temperature " << temperature << " and humidity " << humidity<<" and special control";
    }

};


class fruit : public abstract_product {

public:
//virtual function that keeps products fresh
    void Storage_form(int temperature, int humidity) override {
        cout << "special temperature " << temperature << " and humidity " << humidity << " and special control";
    }

};

class vegetable : public abstract_product {

public:
//virtual function that keeps products fresh
    void Storage_form(int temperature, int humidity) override {
        cout << "special temperature " << temperature << " and humidity " << humidity << " and special control";
    }

};

class spices : public abstract_product {

public:
    //virtual function that keeps products fresh
    void Storage_form(int temperature, int humidity) override {
        cout << "special temperature " << temperature << " and humidity " << humidity << " and special control";
    }

};


class groats : public abstract_product {
public:
    //virtual function that keeps products fresh
    void Storage_form(int temperature, int humidity) override {
        cout << "special temperature " << temperature << " and humidity " << humidity << " and special control";
    }

};


class drink : public abstract_product {

public:
    //virtual function that keeps products fresh
    void Storage_form(int temperature, int humidity) override {
        cout << "special temperature " << temperature << " and humidity " << humidity << " and special control";
    }

};


class storage {

public:
    void prod_insert(abstract_product& product) {
        QSqlQuery a_query;
        a_query.prepare("INSERT INTO storage(product, amount,temperature, humidity) VALUES (?, ?, ?, ?)");

        a_query.addBindValue(product.GetProductName());
        a_query.addBindValue(product.GetAmount());
        a_query.addBindValue(product.GetTemperature());
        a_query.addBindValue(product.GetHumidity());

        if(a_query.exec()){
            cout<<"\nyooohooo\n";
        }
        else{
            qDebug() << a_query.executedQuery();
            qDebug() << a_query.lastError();
        }
    }

    void prod_delete(QString name, int amount_1){
        QSqlQuery a_query, query_1;
        query_1.prepare("SELECT amount from storage WHERE product = ?");
        query_1.addBindValue(name);
        if(query_1.exec()){
            while (query_1.next()) {
              int amm = query_1.value(0).toInt();

                cout<<"our amm"<<amm<<endl;
                int amount = amm - amount_1;
                cout<<"our amount"<<amount;
                a_query.prepare("UPDATE storage SET amount = ? WHERE product = ?");

                a_query.addBindValue(amount);
                a_query.addBindValue(name);

                if(a_query.exec()){
                    cout<<"\nyooohooo\n";
                }
                else{
                    qDebug() << a_query.executedQuery();
                    qDebug() << a_query.lastError();
                }
            }
        }
    }

    void prod_update(QString name, int amount_1){
        QSqlQuery a_query, query_1;
        query_1.prepare("SELECT amount from storage WHERE product = ?");
        query_1.addBindValue(name);
        if(query_1.exec()){
            while (query_1.next()) {
               int amm = query_1.value(0).toInt();

               cout<<"our amm"<<amm<<endl;
                int amount = amm + amount_1;
                cout<<"our amount"<<amount;
                a_query.prepare("UPDATE storage SET amount = ? WHERE product = ?");
                a_query.addBindValue(amount);
                a_query.addBindValue(name);

                if(a_query.exec()){
                    cout<<"\nyooohooo\n";
                }
                else{
                    qDebug() << a_query.executedQuery();
                    qDebug() << a_query.lastError();
                }
        }}
    }

    int in_storage(QString product, int amount){
        QSqlQuery a_query;

        a_query.prepare("SELECT product FROM storage WHERE product = ? AND amount >= ?");
        a_query.addBindValue(product);
        a_query.addBindValue(amount);

        if(!a_query.exec()){ qDebug() << "this is problem with select";return false;}
        else{
            while (a_query.next()) {
                QString name = a_query.value(0).toString();
                if(name == "") return 0;
                return 1;
            }
            return -1;
        }
    }

};


