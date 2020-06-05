#include <storage_man.cpp>
#include <recipe-dish.cpp>
using namespace std;

class chef: public Iadder{
private:
    string dish_name;
    vector<tuple<string,int>> recip_ingredients;
    storage_man robo;
public:
    void add_item() override{
        //add_new_recipe
        cout<<"adding new recipe (with ordering products): ";
        recipe rec(dish_name);
        rec.set_dish(recip_ingredients);
    }

    void new_recipe_dish(string new_dish, vector<tuple<string,int>> recip_ingred){
        dish_name = new_dish;
        recip_ingredients = recip_ingred;
    }

    bool cook_dish(string dish){
        dish_name = dish;
        char* name = const_cast<char*>(dish_name.c_str());

        QSqlQuery query_1, query_2;
        query_1.prepare("SELECT storage.product, storage.amount "
                        "FROM storage JOIN recipe "
                        "ON storage.product = recipe.product "
                        "AND storage.amount >= recipe.amount "
                        "WHERE recipe.dish_name = ? ");
        query_1.addBindValue(name);

        query_2.prepare("SELECT COUNT(product) FROM recipe WHERE dish_name = ? ");
        query_2.addBindValue(name);
        if(!query_1.exec() or !query_2.exec() ){
            cout<<"not executed((\n";
            return false;
        }

        else{
            int count_1 = 0;
            if (query_1.isActive()) while(query_1.next()){ count_1++; }
            while (query_2.next()) {
                int count_2 = query_2.value(0).toInt();
                if (count_1 == count_2){
                    cout<<"we can cook!!\n";
                    robo.to_modify(name);
                    robo.delete_item();
                    return true;
                }
                else{
                    cout<<"we can not cook((\n";
                    robo.to_modify(name);
                    robo.add_item();
                    return false;
                }
            }
        }
    }
};



