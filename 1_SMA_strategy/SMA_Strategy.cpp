// Refer to the header files for the explanation of the functions in detail
// In VSCode, hovering your mouse above the function renders the explanation of from the .h file as a pop up

/**
 * This is a preprocessor directive that includes the "stdafx.h" header file if the target operating system is Windows. 
 * "stdafx.h" is a precompiled header file that contains common includes, declarations, and macros that are used throughout the project.
**/
#ifdef _WIN32
    #include "stdafx.h"
#endif

// Include the header file for the SMA_Strategy class.
#include "SMA_Strategy.h"

// This is the constructor for the SMA_Strategy class. 
// It initializes the member variables of the class to their initial values.
SMA_Strategy::SMA_Strategy(StrategyID strategyID,
                    const std::string& strategyName,
                    const std::string& groupName):
    Strategy(strategyID, strategyName, groupName) {

        // Purpose of each variable explained in the header file.
        small_window = 40;
        big_window = 100;
        small_sum = 0.0;
        big_sum = 0.0;
        stock_size = 0;
        revenue = 0.0;
        capital = 0.0;
        trade_times = 0;

}

// This is the destructor for the SMA_Strategy class.
// It does not perform any operations.
SMA_Strategy::~SMA_Strategy() {
}

void SMA_Strategy::DefineStrategyParams() {
}

void SMA_Strategy::RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate) {
}

void SMA_Strategy::OnTrade(const TradeDataEventMsg& msg) {
    // Declare a pointer to the instrument that the trade occurred on.
    const Instrument* instrument = &msg.instrument();
    // Calculates the mid-price of the instrument.
    double mid_price = (msg.instrument().top_quote().ask() + msg.instrument().top_quote().bid()) / 2;

    /**
     * Below lines update the moving averages of the mid-price using a queue data structure.
     * If the queue size exceeds the moving window size, the oldest element is removed from the queue and the sum is adjusted accordingly
    */
    small_sum += mid_price;
    big_sum += mid_price;
    // Add to the back of the list
    small_set.push(mid_price);
    big_set.push(mid_price);
    
    /** If the window size has been exceeded, remove the oldest element from the queue and subtract it from the rolling sum.
    * If the small average is greater than the big average, the function sends a buy order for 100 shares of the instrument, updates the stock size and revenue, and increments the trade times
    * If the small average is less than the big average and the stock size is greater than 0, the function sends a sell order for 100 shares of the instrument, updates the stock size and revenue, and increments the trade times.
    * If the small average is equal to the big average, the function does nothing.
    **/
    if (small_set.size() > small_window) {
        small_sum -= small_set.front();
        small_set.pop();
    }
    if (big_set.size() > big_window) {
        big_sum -= big_set.front();
        big_set.pop();
    }
    
    // Compute the averages for the small and big windows.
    double small_average = small_sum / (double) small_set.size();
    double big_average = big_sum / (double) big_set.size();
    
    // These conditions determine whether to buy, sell, or hold the instrument based on the current state of the moving averages.
    //  If the small_average is greater than the big_average, BUY
    if (small_average > big_average) {
        // Place an order to buy 100 shares of the instrument. 
        // The instrument parameter is a pointer to the instrument that the trade occurred on.
        SendOrder(instrument, 100);
        // The stock_size variable is then updated to reflect the new quantity of shares that the strategy holds
        stock_size += 100;
        // The revenue variable is also updated to reflect the amount of money spent on buying the shares.
        // This is calculated by multiplying the ask price of the instrument by the quantity of shares bought, which is 100 in this case.
        revenue -= instrument->top_quote().ask() * 100;
        // The trade_times variable is incremented to keep track of the number of trades that the strategy has made
        trade_times++;
    } 
    // If the small_average is smaller than the big_average, SELL
    else if (small_average < big_average && stock_size > 0) {
        // Place an order to SELL 100 shares of the instrument.
        SendOrder(instrument, -100);
        // The stock_size variable is then updated to reflect the new quantity of shares that the strategy holds
        stock_size -= 100;
        // The revenue variable is also updated to reflect the amount of money spent on buying the shares.
        // This is calculated by multiplying the bid price of the instrument by the quantity of shares sold, which is 100 in this case.
        revenue += instrument->top_quote().bid() * 100;
        // The trade_times variable is incremented to keep track of the number of trades that the strategy has made
        trade_times++;
    } 
    // If neither, 
    else { // do nothing
    }

    // Compute the total capital, including both the value of the stocks and the revenue from trades.
    capital = stock_size * instrument->top_quote().bid() + revenue; // money in stock + money in cash

    // Print the current capital, stock size, and number of trades.
    std::cout << "capital = " << capital << " , size = " << stock_size << ", trade times = " << trade_times << std::endl;

}

void SMA_Strategy::OnOrderUpdate(const OrderUpdateEventMsg& msg) {
    
    // The commented out lines are examples of other information that can be accessed through the msg object, but they are not used in this implementation.
    // std::cout << "name = " << msg.name() << std::endl;
    // std::cout << "order id = " << msg.order_id() << std::endl;
    // std::cout << "fill occurred = " << msg.fill_occurred() << std::endl;
    // std::cout << "update type = " << msg.update_type() << std::endl;
    
    // In this function, the update time of the order update event is printed to the console using std::cout.
    std::cout << "time " << msg.update_time() << std::endl;

}

void SMA_Strategy::OnBar(const BarEventMsg& msg) {
}

void SMA_Strategy::AdjustPortfolio() {
    
}

void SMA_Strategy::SendOrder(const Instrument* instrument, int trade_size) {

    // Declare a variable for the price to use for the order
    double price;

    /**
     * This code block checks whether the trade_size is positive or negative. 
     * If trade_size is positive, it means that the strategy wants to buy the instrument. 
     * In this case, the price of the instrument is set to the current ask price, which is the price that the market is currently asking for the instrument. 
     * On the other hand, if trade_size is negative, it means that the strategy wants to sell the instrument. 
     * In this case, the price of the instrument is set to the current bid price, which is the price that the market is currently bidding for the instrument.
    */
    if (trade_size > 0) { // buy
        price = instrument->top_quote().ask();
    } else { // sell
        price = instrument->top_quote().bid();
    }

    // Create an order object with the specified parameters
    OrderParams params(
                    *instrument,     // Instrument to trade
                    abs(trade_size), // Absolute value of trade size
                    price,           // Price at which to trade
                    MARKET_CENTER_ID_IEX, // Market center ID
                    (trade_size > 0) ? ORDER_SIDE_BUY : ORDER_SIDE_SELL, // Order side (buy or sell)
                    ORDER_TIF_DAY,   // Time in force (how long the order is valid for)
                    ORDER_TYPE_LIMIT // Order type (limit or market)
                    );

    /**
     * The code creates a string variable named "action" and assigns a value to it based on the value of the "trade_size" argument.
     * If "trade_size" is greater than 0, the string "buy " is assigned to "action". Otherwise, the string "sell " is assigned to "action".
     * This is used later in the function for outputting information about the trade order being sent.
    **/
    std::string action;
    if (trade_size > 0) {
            action = "buy ";
    } else {
            action = "sell ";
    }

    // Print a message indicating that a new order is being sent
    std::cout << "SendTradeOrder(): about to send new order for size "
            << trade_size
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

void SMA_Strategy::OnResetStrategyState() {
}

void SMA_Strategy::OnParamChanged(StrategyParam& param) {
}
