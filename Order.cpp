#include "OrderSide.cpp"
#include "OrderType.cpp"

class Order {
    public:
        //Limit order
        Order(int quantity, int price, int orderId, OrderSide side, OrderType type) {
            this->quantity = quantity;
            this->price = price;
            this->orderId = orderId;
            this->side = side;
            this->type = type;
        }

        //Market Order
        Order(int quantity, int orderId, OrderSide side) {
            this->quantity = quantity;
            this->orderId = orderId;
            this->side = side;
        }

        int getQuantity() {
            return quantity;
        }

        int getPrice() {
            return price;
        }

        int getOrderId() {
            return orderId;
        }

        OrderSide getOrderSide() {
            return side;
        }

        OrderType getOrderType() { 
            return type;
        }

        void decreaseOrderQuantity(int decreaseQuantity) { 
            quantity -= decreaseQuantity;
        }

        bool operator==(Order other) { 
            return orderId == other.getOrderId();
        }

    private:
        int quantity;
        int price;
        int orderId;
        OrderSide side;
        OrderType type;
}