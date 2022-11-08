#include "OrderType.cpp"
#include "Order.cpp"
#include <"OrderSide.cpp">
#include <set>
#include <queue>
#include <unordered_map>
#include <fstream>

    class OrderBook {
        public:
            OrderBook(){ 
                outputFile.open("MarketSummary.txt");
            }

            static Order getOrder(int orderId) {
                return allOrders.at(orderId);
            }

            void recordTrade(int tradePrice, int tradeQuantity, int sellId, int BuyId) {
                outputFile << f"Order with Id"
            }

            void executeLimitOrder(Order order){
                if (order.getOrderType() == OrderSide::Sell) { 
                    while(!buyBook.empty() && order.getQuantity() > 0 && getOrder(*buyBook.begin()).getPrice() >= order.getPrice()) {
                        Order matchedOrder = getOrder(*buyBook.begin());
                        int tradePrice = matchedOrder.getPrice();
                        int tradeQuantity = Math.min(matchedOrder.getQuantity(), order.getQuantity());

                        order.decreaseOrderQuantity(tradeQuantity);
                        if (tradeQuantity == matchedOrder.getQuantity()) {
                            buyBook.erase(matchedOrder.getOrderId());
                            allOrders.erase(matchedOrder);
                        }
                        else {
                            matchedOrder.decreaseOrderQuantity(tradeQuantity);
                        }
                        
                        recordTrade(tradePrice, tradeQuantity, sellId, buyId);
                    }

                    if (order.getQuantity())
                        sellBook.insert(order.getOrderId());
                }
                
                else { 
                    while(!sellBook.empty() && order.getQuantity() > 0 && getOrder(*sellBook.begin()).getPrice() <= order.getPrice()) {
                        Order matchedOrder = getOrder(*sellBook.begin());
                        int tradePrice = matchedOrder.getPrice();
                        int tradeQuantity = Math.min(matchedOrder.getQuantity(), order.getQuantity());

                        order.decreaseOrderQuantity(tradeQuantity);
                        if (tradeQuantity == matchedOrder.getQuantity()) {
                            sellBook.erase(matchedOrder.getOrderId());
                            allOrders.erase(matchedOrder);
                        }
                        else {
                            matchedOrder.decreaseOrderQuantity(tradeQuantity);
                        }
                        
                        recordTrade(tradePrice, tradeQuantity, sellId, buyId);
                    }

                    if (order.getQuantity())
                        buyBook.insert(order.getOrderId());
                }
            }

            void executeMarketOrder(Order order){
                int quantity = order.getQuantity();
                if(order.getOrderType() == OrderSide::SELL){
                    while(!buyBook.empty() && quantity > 0){
                        Order buyOrder = OrderBook::getOrder(*(buyBook.begin()));
                        int tradePrice = (buyOrder.getPrice() + order.getPrice()) / 2;
                        int tradeQuantity = Math.min(buyOrder.getQuantity(), order.getQuantity());
                        quantity -= tradeQuantity;
                        if(buyOrder.getQuantity() <= tradeQuantity){
                            buyBook.erase(buyOrder.getOrderId());
                            allOrders.erase(buyOrder.getOrderId());
                        }
                    }
                    if(quantity > 0){
                        sellMarket.push(order.getOrderId());
                    } else {
                        recordTrade(tradePrice, tradeQuantity, order.getOrderId(), buyOrder.getOrderId());
                    }
                } else {
                    while(!sellBook.empty() && quantity > 0){
                        Order sellOrder = OrderBook::getOrder(*(sellBook.begin()));
                        int tradePrice = (sellOrder.getPrice() + order.getPrice()) / 2;
                        int tradeQuantity = Math.min(sellOrder.getQuantity(), order.getQuantity());
                        quantity -= tradeQuantity;
                        if(sellOrder.getQuantity() <= tradeQuantity){
                            sellBook.erase(sellOrder.getOrderId());
                            allOrders.erase(sellOrder.getOrderId());
                        }
                    }
                    if(quantity > 0){
                        buyMarket.push(order.getOrderId());
                    } else {
                        recordTrade(tradePrice, tradeQuantity, buyOrder.getOrderId(), order.getOrderId());
                    }
                }
            }

            
        private:
            static std::set<int,buy_cmp> buyBook;
            static std::set<int,sell_cmp> sellBook;
            static std::unordered_map<int, Order> allOrders;
            static std::queue<int> sellMarket;
            static std::queue<int> buyMarket;
            static std::ofstream outputFile;
    }

    struct buy_cmp {
        bool operator() (int order1, int order2) const {
            Order ord1, ord2 = OrderBook::getOrder(order1), OrderBook::getOrder(order2);
            if (ord1.getPrice() == ord2.getPrice())
                return ord1.getOrderId() > ord2.getOrderId();
            return ord1.getPrice() < ord2.getPrice();
        }
    };

    struct sell_cmp {
        bool operator() (int order1, int order2) const {
            Order ord1, ord2 = OrderBook::getOrder(order1), OrderBook::getOrder(order2);
            if(ord1.getPrice() == ord2.getPrice())
                return ord1.getPrice() > ord2.getOrderId();
            return ord1.getPrice() > ord2.getPrice();
        }
    };