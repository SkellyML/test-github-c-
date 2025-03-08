#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

class Product {
private:
    string productId;
    string name;
    float price;
    string productDescription;

public:
    Product(string id, string n, float p, string desc)
        : productId(id), name(n), price(p), productDescription(desc) {}

    string getProductId() const { return productId; }
    string getName() const { return name; }
    float getPrice() const { return price; }
    string getProductDescription() const { return productDescription; }
};

class ShoppingCart {
private:
    int cartId;
    vector<pair<Product, int>> productLists;

public:
    ShoppingCart(int id) : cartId(id) {}

    void addItem(Product product, int quantity) {
        for (auto& item : productLists) {
            if (item.first.getProductId() == product.getProductId()) {
                item.second += quantity;
                cout << "Product added successfully!\n";
                return;
            }
        }
        productLists.push_back(make_pair(product, quantity));
        cout << "Product added successfully!\n";
    }

    vector<pair<Product, int>> viewCart() const {
        return productLists;
    }

    float calculateTotal() {
        float total = 0;
        for (const auto& item : productLists) {
            total += item.first.getPrice() * item.second;
        }
        return total;
    }

    void displayCart() {
        if (productLists.empty()) {
            cout << "Shopping cart is empty.\n";
            return;
        }
        cout << "\nShopping Cart:\n";
        cout << left << setw(15) << "Product ID" << setw(20) << "Name"
             << setw(10) << "Price" << setw(15) << "Quantity" << "Description\n";
        cout << "------------------------------------------------------------------\n";
        for (const auto& item : productLists) {
            cout << left << setw(15) << item.first.getProductId()
                 << setw(20) << item.first.getName()
                 << setw(10) << item.first.getPrice()
                 << setw(15) << item.second
                 << item.first.getProductDescription() << endl;
        }
        cout << "Total: $" << fixed << setprecision(2) << calculateTotal() << endl;
    }

    void clearCart() {
        productLists.clear();
    }
};

class Order {
private:
    int orderId;
    float totalAmount;
    vector<pair<Product, int>> orderItems;

public:
    Order(int id, vector<pair<Product, int>> items, float total)
        : orderId(id), orderItems(items), totalAmount(total) {}

    void displayOrder() {
        cout << "\nOrder ID: " << orderId << endl;
        cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
        cout << "Order Details:\n";
        cout << left << setw(15) << "Product ID" << setw(20) << "Name"
             << setw(10) << "Price" << setw(15) << "Quantity" << "Description\n";
        cout << "------------------------------------------------------------------\n";
        for (const auto& item : orderItems) {
            cout << left << setw(15) << item.first.getProductId()
                 << setw(20) << item.first.getName()
                 << setw(10) << item.first.getPrice()
                 << setw(15) << item.second
                 << item.first.getProductDescription() << endl;
        }
    }
};

int getValidChoice() {
    string input;
    int choice;

    while (true) {
        cout << "\nEnter your choice (1-4): ";
        cin >> input;

        bool isValid = true;
        for (char c : input) {
            if (!isdigit(c)) { 
                isValid = false;  
                break;
            }
        }

        if (isValid) {
            choice = stoi(input);
            if (choice >= 1 && choice <= 4) {
                return choice;
            }
        }
        
        cout << "Invalid choice! Please enter a number between 1 to 4.\n";
    }
}

int main() {
    vector<Product> products = {
        Product("ABC123", "50 dias", 50.0, "50 + 5 dias"),
        Product("DEF456", "100 dias", 98.0, "100 + 10 dias"),
        Product("GHI789", "250", 230.0, "250 + 30 dias"),
        Product("JKL012", "Starlight", 300.0, "1 Starlight Card"),
        Product("MNO345", "500 dias", 500.0, "500 + 50 dias")
    };

    ShoppingCart cart(1);
    vector<Order> orderHistory;
    int orderCount = 0;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. View Products\n";
        cout << "2. View Shopping Cart\n";
        cout << "3. View Orders\n";
        cout << "4. Exit\n";

        int choice = getValidChoice();

        if (choice == 1) {
            cout << "\nAvailable Products:\n";
            cout << left << setw(15) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << "Description\n";
            cout << "------------------------------------------------------------------\n";
            for (const auto& product : products) {
                cout << left << setw(15) << product.getProductId()
                     << setw(20) << product.getName()
                     << setw(10) << product.getPrice()
                     << product.getProductDescription() << endl;
            }
            while (true) {
                cout << "\nEnter the Product ID to add (or '0' to return to menu): ";
                string productId;
                cin >> productId;
                if (productId == "0") break;
                int quantity;
                cout << "Enter quantity: ";
                cin >> quantity;
                bool found = false;
                for (const auto& product : products) {
                    if (product.getProductId() == productId) {
                        cart.addItem(product, quantity);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Invalid product ID! Try again.\n";
                } else {
                    cout << "Do you want to add another product? (Y/N): ";
                    char another;
                    cin >> another;
                    if (another == 'N' || another == 'n') break;
                }
            }
        } 
        else if (choice == 2) {
            cart.displayCart();
            if (!cart.viewCart().empty()) {
                cout << "Do you want to check out all the products? (Y/N): ";
                char checkout;
                cin >> checkout;
                if (checkout == 'Y' || checkout == 'y') {
                    orderCount++;
                    orderHistory.push_back(Order(orderCount, cart.viewCart(), cart.calculateTotal()));
                    cart.clearCart();
                    cout << "You have successfully checked out the products!\n";
                }
            }
        } 
        else if (choice == 3) {
            if (orderHistory.empty()) {
                cout << "No orders available.\n";
            } else {
                for (Order& order : orderHistory) {
                    order.displayOrder();
                }
            }
        } 
        else if (choice == 4) {
            cout << "Exiting program...\n";
            break;
        } 
    }
    return 0;
}
