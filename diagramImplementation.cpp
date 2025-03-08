#include <iostream> 
#include <ctime>
using namespace std;

class Order{

private: 
    int orderId;
    float totalAmount;

    
public: 

    void placeOrder(){

     }
    void removeOrder(){

    }
    string getOrderSummary(){

    }
    float calculateTotal(){

    }
};

class ShoppingCart{

private: 
    int cartId;
    list<Product> products;
};
public:
    void addItem(){

    };
    void removeItem(){

    };
    float calculateTotal(){

    };



class Product{
    
private:
    int productId;
    string productName;
    float price;
    string description;
    int quantity;  

public: 

    string getProductDetails(){

    }
};

int main() {






    return 0;
}