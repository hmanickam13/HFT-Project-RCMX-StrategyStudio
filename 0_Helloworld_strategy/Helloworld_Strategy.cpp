// Refer to the header files for the explanation of the functions in detail
// In VSCode, hovering your mouse above the function renders the explanation of from the .h file as a pop up

/**
 * This is a preprocessor directive that includes the "stdafx.h" header file if the target operating system is Windows. 
 * "stdafx.h" is a precompiled header file that contains common includes, declarations, and macros that are used throughout the project.
**/
#ifdef _WIN32
    #include "stdafx.h"
#endif

// Include the header file for the Helloworld_Strategy class.
#include "Helloworld_Strategy.h"

// This is the constructor for the Helloworld_Strategy class. 
// It initializes the member variables of the class to their initial values.
Helloworld_Strategy::Helloworld_Strategy(StrategyID strategyID,
                    const std::string& strategyName,
                    const std::string& groupName):
    Strategy(strategyID, strategyName, groupName) {

    // Purpose of each variable explained in the header file.
    trade_size_each_time = 10;
	total_stock_position = 0;
	buy_price = 0;
	total_revenue = 0.0;
    total_trade_count = 0;

}

// This is the destructor for the Helloworld_Strategy class.
// It does not perform any operations.
Helloworld_Strategy::~Helloworld_Strategy() {
}

void Helloworld_Strategy::DefineStrategyParams() {
}

void Helloworld_Strategy::RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate) {
}

void Helloworld_Strategy::OnTrade(const TradeDataEventMsg& msg) {
    
    // Declare a pointer to the instrument that the trade occurred on.
    const Instrument* instrument = &msg.instrument();
    // Calculates the bid-price of the instrument.
    double bid_price = msg.instrument().top_quote().bid();

    // If we don't own an stock, buy trade_size_each_time quantity of stock,
    if (total_stock_position == 0) {
        
        // Send order to matching engine
        SendOrder(instrument, trade_size_each_time);
        
        // Buying price = level 1 bid price
        buy_price = bid_price;
        
        // Our total position
        total_stock_position += trade_size_each_time;
        
        // Reduce total total_revenue because we buy aka cash outflow
        total_revenue -= bid_price * trade_size_each_time;    
        
        // increment counter for number of times traded
        total_trade_count += 1;

        } 
    
    // If the bid price is larger than the buy price by 0.05, sell the position and generate profit
    else if ((bid_price - buy_price) >= buy_price * 0.05) {
        
        // We multiply -1 into trade_size_each_time because we are selling the position.
        SendOrder(instrument, -1 * trade_size_each_time);

        //Update the size of your position
        total_stock_position -= trade_size_each_time;

        //Update the total_revenue generated from this sell order. If total_revenue decreases when buying a position, then selling a position means...
        total_revenue += bid_price * trade_size_each_time;

        }
    
    // If the bid price is lesser than the buy price by 0.05, sell the position and minimize out loss
    else if ((bid_price - buy_price) <= buy_price * 0.05) {
        // We multiply -1 into trade_size_each_time because we are selling the position.
        SendOrder(instrument, -1 * trade_size_each_time);

        //Update the size of your position
        total_stock_position -= trade_size_each_time;

        //Update the total_revenue generated from this sell order. If total_revenue decreases when buying a position, then selling a position means...
        total_revenue += bid_price * trade_size_each_time;
        }
}


void Helloworld_Strategy::OnScheduledEvent(const ScheduledEventMsg& msg) {
}

void Helloworld_Strategy::OnOrderUpdate(const OrderUpdateEventMsg& msg) {
    
    // The commented out lines are examples of other information that can be accessed through the msg object, but they are not used in this implementation.
    // std::cout << "name = " << msg.name() << std::endl;
    // std::cout << "order id = " << msg.order_id() << std::endl;
    // std::cout << "fill occurred = " << msg.fill_occurred() << std::endl;
    // std::cout << "update type = " << msg.update_type() << std::endl;
    
    // In this function, the update time of the order update event is printed to the console using std::cout.
    std::cout << "time " << msg.update_time() << std::endl;

}

//  Function empty for now
void Helloworld_Strategy::OnBar(const BarEventMsg& msg) {
}

//  Function empty for now
void Helloworld_Strategy::AdjustPortfolio() {
    
}

void Helloworld_Strategy::SendOrder(const Instrument* instrument, int trade_size_each_time) {

    // Declare a variable for the price to use for the order
    double price;

    /**
     * This code block checks whether the trade_size_each_time is positive or negative. 
     * If trade_size_each_time is positive, it means that the strategy wants to buy the instrument. 
     * In this case, the price of the instrument is set to the current ask price, which is the price that the market is currently asking for the instrument. 
     * On the other hand, if trade_size_each_time is negative, it means that the strategy wants to sell the instrument. 
     * In this case, the price of the instrument is set to the current bid price, which is the price that the market is currently bidding for the instrument.
    */
    if (trade_size_each_time > 0) { // buy
        price = instrument->top_quote().ask();
    } else { // sell
        price = instrument->top_quote().bid();
    }

    // Create an order object with the specified parameters
    OrderParams params(
                    *instrument,     // Instrument to trade
                    abs(trade_size_each_time), // Absolute value of trade size
                    price,           // Price at which to trade
                    MARKET_CENTER_ID_IEX, // Market center ID
                    (trade_size_each_time > 0) ? ORDER_SIDE_BUY : ORDER_SIDE_SELL, // Order side (buy or sell)
                    ORDER_TIF_DAY,   // Time in force (how long the order is valid for)
                    ORDER_TYPE_LIMIT // Order type (limit or market)
                    );

    /**
     * The code creates a string variable named "action" and assigns a value to it based on the value of the "trade_size_each_time" argument.
     * If "trade_size_each_time" is greater than 0, the string "buy " is assigned to "action". Otherwise, the string "sell " is assigned to "action".
     * This is used later in the function for outputting information about the trade order being sent.
    **/
    std::string action;
    if (trade_size_each_time > 0) {
            action = "buy ";
    } else {
            action = "sell ";
    }

    // Print a message indicating that a new order is being sent
    std::cout << "SendTradeOrder(): about to send new order for size "
            << trade_size_each_time
            << " at $"
            << price
            << " to "
            << action
            << instrument->symbol()
            << std::endl;

    /**
     * This line of code sends a new order to the market using the trade_actions() object, which is an instance of the TradeActions class that provides functionality for managing orders and trades in the market.
     * The SendNewOrder() method takes an OrderParams object as an argument, which contains information about the order to be sent, such as the instrument, order size, price, order type, and time-in-force.
     * The method returns a TradeActionResult value, which indicates whether the order was successfully submitted to the market or not.
    **/
    TradeActionResult tra = trade_actions()->SendNewOrder(params);

    // Check if the order was sent successfully and print a message indicating the result
    if (tra == TRADE_ACTION_RESULT_SUCCESSFUL) {
            std::cout << "Sending new trade order successful!" << std::endl;
    } else {
            std::cout << "Error sending new trade order..." << tra << std::endl;
    }

}

void Helloworld_Strategy::OnResetStrategyState() {
}

void Helloworld_Strategy::OnParamChanged(StrategyParam& param) {
}
