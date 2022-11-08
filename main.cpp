#include <iostream>
#include <set>
#include <unordered_map>
#include <queue>
#include <bits/stdc++.h>
#include <string>
#include "Order.cpp"
#include "OrderSide.cpp"
#include "OrderType.cpp"
#include "OrderBook.cpp"


int main() {
    std::string orderInput;
    double marketPrice;
    int orderID = 0;
    std::cout << "***Welcome to Stock Market Simulator***" << std::endl;
    std::cout << "Orders Supported" << std::endl;
    std::cout << "Enter your order in the following format: {Buy/Sell},{Type of Order},{Quantity},{Price - if not market order}" << std::endl;
    while(std::cin >> orderInput){
        std::string buyType, orderType, quantity, price;
        std::stringstream ss(orderInput);
        int i = 0;
        while(ss.good()){
            switch(i) {
                case 0:
                    getline(ss, buyType, ',');
                case 1:
                    getline(ss, orderType, ',');
                case 2:
                    getline(ss, quantity, ',');
                case 3:
                    getline(ss, price, ',');
            }
            ++i;
        }
        if(i == 3){
            Order currOrder (buyType, orderType, quantity);
        } else {
            Order currOrder (buyType, orderType, quantity, price);
        }

        
    }


}