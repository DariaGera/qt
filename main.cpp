#include <QCoreApplication>
#include <chef.cpp>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("C:/Users/pavel/Documents/Дарія Герасимчук/OOPlaba/database/restaurant.sqlite");
    if (!dbase.open()) { qDebug() << "something went wrong!"; }

    //for storage_man
    fruit orange, apple;
    vegetable cucumber;
    orange.Construct_product(2, "orange", 100,12);
    apple.Construct_product(4, "apple", 10,12);
    cucumber.Construct_product(5, "cucumber", 5,2);

    storage_man rob;
    rob.order_prod(&orange);
    rob.order_prod(&apple);

    cout<<"\nWe have ordered, now chef can add new dish recipe\n"<<endl;

    //for chef
    string dish_name_1 = "Fish with rice";
    vector<tuple<string,int>>recip_ingredredients_1 = {{"fish", 1}, {"rice", 50}};

    string dish_name_2 = "Apples";
    vector<tuple<string,int>>recip_ingredredients_2 = {{"apple", 1}};

    chef robo;
    robo.new_recipe_dish(dish_name_1, recip_ingredredients_1);
    robo.add_item();
    robo.new_recipe_dish(dish_name_2, recip_ingredredients_2);
    robo.add_item();

    cout<<"\nWe have added dishes, now chef can(or not) cook\n"<<endl;
    cout<<"first\n";
    robo.cook_dish(dish_name_1);

    cout<<"\nsecond\n";
    robo.cook_dish(dish_name_1);


    cout<<"\nbyyee\n"<<endl;
   return a.exec();
}
