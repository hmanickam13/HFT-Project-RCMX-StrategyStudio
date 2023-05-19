// This header file contains the explanation and purpose of the functions inside the SMA_Strategy class

// This is a preprocessor directive that ensures that the header file is included only once in a given compilation unit, to avoid multiple definitions.
#pragma once

// These are include guards that prevent redefinition of class names, macro constants, and typedef names. 
// Include guards help avoiding name conflicts in large software projects.
#ifndef _STRATEGY_STUDIO_LIB_EXAMPLES_SIMPLE_MOMENTUM_STRATEGY_H_
#define _STRATEGY_STUDIO_LIB_EXAMPLES_SIMPLE_MOMENTUM_STRATEGY_H_

// This is a conditional preprocessor directive that defines a macro _STRATEGY_EXPORTS as __declspec(dllexport) on Windows platform, and empty on other platforms.
// This macro is used to export the SMA_Strategy class to the dynamic link library (DLL) that is loaded by the trading engine.
#ifdef _WIN32
    #define _STRATEGY_EXPORTS __declspec(dllexport)
#else
    #ifndef _STRATEGY_EXPORTS
    #define _STRATEGY_EXPORTS
    #endif
#endif

/**
 * Below are header files that are used by the SMA_Strategy class. We just tell the compiler to look for these files.
 * You will not have Strategy.h & Instrument.h in your directory. These are part of the SDK.
 * Strategy.h is the main header file for the strategy development kit and provides access to the core functionality of the trading engine.
 * Instrument.h is a header file for instrument specific data. 
 * The remaining headers provide various utility functions.
**/
#include <Strategy.h>
#include <MarketModels/Instrument.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm> 

// Import namespace RCM::StrategyStudio to avoid explicit namespace qualification when using names from this namespace
using namespace RCM::StrategyStudio;

// Class declaration
class SMA_Strategy : public Strategy {
public:
    // Constructor & Destructor functions for this class
    SMA_Strategy(StrategyID strategyID,
        const std::string& strategyName,
        const std::string& groupName);
    ~SMA_Strategy();


public:

    // Below are event handling functions that the 'SMA_Strategy' class overrides to receive trading events from the trading engine.

    /**
    * OnBar is a member function of the SMA_Strategy class that gets called by the backtesting framework in Strategy Studio whenever a bar event occurs for an instrument that the strategy is subscribed to.
    * A bar event is a notification that a new bar has been formed in the price data of the instrument, where a bar represents a fixed period of time (e.g., 1 minute, 5 minutes, 1 hour) and contains information such as the opening price, closing price, highest price, and lowest price for that period.
    * The msg parameter of the OnBar function is an object of type BarEventMsg that contains information about the bar event that occurred, such as the instrument for which the event occurred and the details of the bar itself.
    * OnBar is a virtual function in the Strategy base class which gets called by the Strategy Studio whenever a bar is completed for any of the instruments subscribed to by the strategy.
    * The function provides information about the instrument, such as the open, high, low and close prices for the bar interval, as well as other useful information like the volume and the date and time of the bar.
    * The user can override this function in their derived strategy class to implement their own trading logic based on this information.
    * By overriding this function, the user can customize their strategy to execute trades based on their own analysis of the bar data, for example by using the price and volume information to calculate moving averages, look for patterns or trends, and decide on a buy or sell signal.
    **/
    virtual void OnBar(const BarEventMsg& msg);


    /**
    * The OnTrade function is a member function of the SMA_Strategy class and is called by the backtesting framework in Strategy Studio whenever a trade event occurs for an instrument that the strategy is subscribed to.
    * The msg parameter of the OnTrade function is an object of type TradeDataEventMsg that contains information about the trade event that occurred, such as the instrument for which the event occurred and the details of the trade itself.
    * The function calculates moving averages for the instrument using a small and big window and makes a decision to buy, sell, or hold the instrument based on the current state of the moving averages.
    * If a buy or sell order is executed, the function updates the stock size, revenue, and trade times variables accordingly.
    * The function also calculates the capital of the strategy at each trade event by adding the value of the stock holdings and revenue.
    * The function prints out the current capital, stock size, and trade times at each trade event for debugging purposes.
    * The OnTrade function can be overridden by the user to implement their own trading logic based on the information provided in the msg parameter.
    * Polymorphic behavior is achieved in C++ by using virtual functions, which allows the same function to behave differently depending on the type of object it is called on.
    */
    virtual void OnTrade(const TradeDataEventMsg& msg);

    /**
     * The OnOrderUpdate function is a member function of the SMA_Strategy class in the trading strategy code. It is triggered whenever a completed order is detected and computes the quantityHeld.
     * When an order is executed in the market, the information about the order is sent back to the trading strategy, which can then update its internal state.
     * The msg parameter of the OnOrderUpdate function is an object of type OrderUpdateEventMsg that contains information about the order that was just completed, such as the order ID, fill price, and quantity.
     * The function is responsible for computing the quantityHeld of the instrument after the order has been executed.
     * This is important for keeping track of the current position the strategy has in the instrument, as it may have executed multiple orders for different quantities.
     * The quantityHeld is calculated by summing up the quantity of all orders that have not been filled or cancelled.
     * The OnOrderUpdate function does not return anything, as its purpose is solely to update the internal state of the trading strategy.
    */
    void OnOrderUpdate(const OrderUpdateEventMsg& msg);
 
    /**
     * The OnResetStrategyState() function is used to reset the strategy state.
     * The OnResetStrategyState() function is called by the backtesting framework in Strategy Studio whenever a reset event occurs.
     * The purpose of the function is to clear out any previous state information and start fresh.
     * This is useful for running multiple backtests or testing different strategy parameters.
     * The function is a virtual function in the Strategy base class, which means it can be overridden by a derived strategy class to perform additional actions during the reset event if needed.
    */
    void OnResetStrategyState();

    /**
     * The OnParamChanged function is a member function of the SMA_Strategy class in the Strategy Studio.
     * It is called by the framework to notify the strategy of every successful change in the value of a strategy parameter.
     * The function takes a StrategyParam object as a parameter, which represents the changed parameter value.
     * The function will be called any time a new parameter value passes validation, including during strategy initialization when default parameter values are set in the call to CreateParam, and when any persisted values are loaded.
     * The function will also trigger after OnResetStrategyState to remind the strategy of the current parameter values.
     **/ 
    void OnParamChanged(StrategyParam& param);


/**
 * The SMA_Strategy class uses the private access modifier multiple times to declare different types of member functions and member variables.
 * The first private section declares two private helper functions specific to the SMA_Strategy class, named AdjustPortfolio() and SendOrder().
 * The second private section declares two virtual functions that are being overridden by the SMA_Strategy class to register for strategy events and define the strategy parameters.
 * The third private section declares several private member variables used to store the state and data of the strategy.
 * The reason for using private access modifiers is to encapsulate the internal workings of the SMA_Strategy class and prevent other classes or functions from accessing or modifying its private members directly.
 * This helps to maintain the integrity of the class and minimize potential bugs or errors caused by external interference.
**/
private:  

    /**
     * This function is responsible for adjusting the portfolio holdings of the strategy based on its current state and the signals generated by the trading logic.
     * It updates the stock size and revenue variables of the strategy based on the trades executed and the current market conditions.
     * The function is called by the trading logic to make adjustments to the portfolio holdings and can be customized by the user to implement their own portfolio management strategies.
    **/
    void AdjustPortfolio();

    /**
     * This function is responsible for sending orders to the market to execute trades based on the trading logic.
     * It takes two parameters:
        * a pointer to the instrument being traded
        * the trade size (positive for buy and negative for sell.
     * The function executes the trade by sending the order to the market and updates the stock size and revenue variables of the strategy based on the executed trade.
     * The function can be customized by the user to implement their own order execution strategies.
    */
    void SendOrder(const Instrument* instrument, int trade_size);

private: 
    
    /**
     * This function is used to register the strategy for events that it will receive during the backtest.
     * It is a virtual function in the base class that is overridden by the SMA_Strategy class to register for the specific events that it needs.
     * The function takes two parameters:
        * A pointer to a StrategyEventRegister object that is used to register for events.
        * A DateType object representing the current date of the backtest.
     * Inside the function, the SMA_Strategy class can register for any events that it needs using the provided eventRegister object.
    */
    virtual void RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate); 

    /**
     * DefineStrategyParams() is a virtual function in the SMA_Strategy class.
     * The purpose of this function is to define any parameters that the strategy will use.
     * It is called during the initialization of the strategy.
     * The virtual keyword indicates that this function can be overridden by a derived class.
     * Parameters can be defined using the CreateParam function provided by the backtesting framework.
     * Parameters can be accessed and modified using the GetParam and SetParam functions provided by the backtesting framework.
     */     
    virtual void DefineStrategyParams();

private:
    // private member variables of the SMA_Strategy class.
    // Used to store the state and data of the strategy.
    double small_sum; // the sum of mid-prices for the small moving average window.
    double big_sum; // the sum of mid-prices for the big moving average window.
    std::queue<double> small_set; // a queue of mid-prices used to calculate the small moving average.
    std::queue<double> big_set; // a queue of mid-prices used to calculate the big moving average.
    unsigned small_window; // the number of mid-prices used to calculate the small moving average.
    unsigned big_window; // the number of mid-prices used to calculate the big moving average.
    int stock_size; // the number of shares of the instrument currently held in the strategy's portfolio.
    double revenue; // the amount of cash (positive or negative) earned from buying and selling the instrument.
    double capital; // the total value of the strategy's portfolio, including cash and the value of the shares held.
    int trade_times; // the number of trades executed by the strategy.

};

// extern "C" is used to tell the compiler that these functions have C-style linkage instead of C++-style linkage, which means the function names will not be mangled.
// What is mangling? What does it mean for the functions inside this?
extern "C" {

    /** 
     * If a function is marked with the _STRATEGY_EXPORTS preprocessor directive, it is being used to export symbols from the DLL in Windows. What is a DLL?
     * The function is platform-dependent and may need to be modified for different operating systems or compilers, depending on their requirements for symbol exporting and DLL loading.
    **/

    /**
     * The function GetType() is a global function that is used to return a string representing the type of the strategy, which is used to identify the strategy in Strategy Studio.
     * The function is defined as part of the SMA_Strategy class, which is a derived class of the Strategy base class
     * The function returns a const char pointer, which points to the string "SMA_Strategy".
     * The purpose of returning the type of the strategy is to allow Strategy Studio to identify the strategy and make it available for backtesting and live trading.
     * The string returned by the function is used to match the strategy with its corresponding DLL, which is loaded into memory when the strategy is selected in Strategy Studio
     **/
    _STRATEGY_EXPORTS const char* GetType() {
        return "SMA_Strategy";
    }

    /**
     * Creates an instance of the SMA_Strategy class
     * Checks whether the provided strategyType matches the type of the SMA_Strategy class using the GetType() function
     * Returns a pointer to the new SMA_Strategy object if there is a match, or a null pointer if there is no match
     * This function is necessary for the Strategy Studio to create and manage instances of the SMA_Strategy class during backtesting and simulation.
    */
    _STRATEGY_EXPORTS IStrategy* CreateStrategy(const char* strategyType,
                                   unsigned strategyID,
                                   const char* strategyName,
                                   const char* groupName) {
        if (strcmp(strategyType, GetType()) == 0) {
            return *(new SMA_Strategy(strategyID, strategyName, groupName));
        } else {
            return NULL;
        }
    }

    // The GetAuthor() function returns a string representing the author of the strategy.
    // This must match an existing user within the system
    _STRATEGY_EXPORTS const char* GetAuthor() {
        return "dlariviere";
    }

    // The GetAuthorGroup() function returns a string representing the trading group associated with the author.
    // must match an existing trading group within the system
    _STRATEGY_EXPORTS const char* GetAuthorGroup() {
        return "UIUC";
    }

    // The GetReleaseVersion() function returns a string representing the release version of the Strategy Studio.
    // used to ensure the strategy was built against a version of
    // the SDK compatible with the server version
    _STRATEGY_EXPORTS const char* GetReleaseVersion() {
        return Strategy::release_version();
    }
}

// The #endif statement marks the end of the include guard to prevent the header file from being included multiple times.
#endif
