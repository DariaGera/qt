#include <iostream>
#include <vector>
#include <string>
#include <QtSql>
using namespace std;

class recipe{
private:
    class Dish{
    public:
        char* dish_name;

        void set_dish(char* name){
            dish_name = name;
            QSqlQuery a_query;
            a_query.prepare("INSERT INTO dish(dish_name) VALUES (?)");
            a_query.addBindValue(dish_name);
            if(!a_query.exec()) {cout<<"not executed for dish\n";};
        }
    };

    Dish dish;
    char* dish_name;
    vector<tuple<string,int>> recip_ingredients;
public:
    //constructor
    recipe(string name){
       dish_name = const_cast<char*>(name.c_str());
    }
    void set_dish(vector<tuple<string, int>> recip_ingred){
        recip_ingredients = recip_ingred;
        dish.set_dish(dish_name);
        QSqlQuery a_query;
        cout<<dish_name<<endl;
        for(const auto& i : recip_ingredients){
            cout<<get<0>(i)<<get<1>(i)<<endl;
            a_query.prepare("INSERT INTO recipe(dish_name, product, amount) VALUES (?, ?, ?)");
            a_query.addBindValue(dish_name);
            a_query.addBindValue(const_cast<char*>(get<0>(i).c_str()));
            a_query.addBindValue(get<1>(i));
            if(!a_query.exec()) {cout<<"not executed for recipe\n";};
        }
    }
};

