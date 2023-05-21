#ifdef _WIN32
    #include "stdafx.h"
#endif

#include "HelloWorldClearStrategy.h"
/**This assignment is made to be an introduction in coding your own strategy. There are other examples and full samples provided. For this assignment, you are provided the .h file and code (strongly recommended
to go through that first as that serves as the background for the implementation used) as well as this cpp skeleton and pseudocode.


*/

'''
Constructor for the strategy. Here, set trade_size to 10 and initialize the three other relevant variables to 0.
'''
HelloWorldClearStrategy::HelloWorldClearStrategy(StrategyID strategyID,
                    const std::string& strategyName,
                    const std::string& groupName):
    Strategy(strategyID, strategyName, groupName) {

}

//No additional, internal code needed here (added to make sure the RCM X software runs properly. Feel free to change to add complexity)
HelloWorldClearStrategy::~HelloWorldClearStrategy() {
}

//No additional, internal code needed here (added to make sure the RCM X software runs properly. Feel free to change to add complexity)
void HelloWorldClearStrategy::DefineStrategyParams() {
}

//No additional, internal code needed here (added to make sure the RCM X software runs properly. Feel free to change to add complexity)
void HelloWorldClearStrategy::RegisterForStrategyEvents(
    StrategyEventRegister* eventRegister, DateType currDate) {
}


'''
This function will execute whenever a trade occurs.

'''
void HelloWorldClearStrategy::OnTrade(const TradeDataEventMsg& msg) {

	const Instrument* instrument = &msg.instrument();
	double bid_price = msg.instrument().top_quote().bid();

        //You want to add the code for auto timer events here to automate trading at certain market state

	if (trade_position == 0) { // buy stock when don't have any
		SendOrder(instrument, trade_size);
		buy_price = bid_price;
        trade_position += trade_size;
		trade_revenue -= bid_price * trade_size;
		
	} else if ((bid_price - buy_price) >= buy_price * 0.5) { // sell when profit >= 0.5 -> make profit
        //If buying means you send an order of positive 1 * trade_size, then selling means...

        //Update the size of your position

        //Update the revenue generated from this sell. If revenue decreases when buying a position, then selling a position means...

	} else if () { // sell when loss >= 0.05 -> stop loss
        //If buying means you send an order of positive 1 * trade_size, then selling means...

        //Update the size of your position

        //Update the revenue generated from this sell
        
	}


}

//No additional, internal code needed here (added to make sure the RCM X software runs properly. Feel free to change to add complexity)
void HelloWorldClearStrategy::OnScheduledEvent(const ScheduledEventMsg& msg) {
}


void HelloWorldClearStrategy::OnOrderUpdate(const OrderUpdateEventMsg& msg) {

    std::cout << "time " << msg.update_time() << std::endl;

}

//No additional, internal code needed here (added to make sure the RCM X software runs properly. Feel free to change to add complexity)
void HelloWorldClearStrategy::OnBar(const BarEventMsg& msg) {
}

//No additional, internal code needed here (added to make sure the RCM X software runs properly. Feel free to change to add complexity)
void HelloWorldClearStrategy::AdjustPortfolio() {
}

void HelloWorldClearStrategy::SendOrder(const Instrument* instrument, int trade_size) {

    double price;
        if (trade_size > 0) { // buy
                price = instrument->top_quote().ask();
        } else { // sell
                price = instrument->top_quote().bid();
        }

        OrderParams params(
                        *instrument,
                        abs(trade_size),
                        price,
                        MARKET_CENTER_ID_IEX,
                        (trade_size > 0) ? ORDER_SIDE_BUY : ORDER_SIDE_SELL,
                        ORDER_TIF_DAY,
                        ORDER_TYPE_LIMIT
                        );

        std::string action;
        if (trade_size > 0) {
                action = "buy ";
        } else {
                action = "sell ";
        }

        std::cout << "SendTradeOrder(): about to send new order for size "
                << trade_size
                << " at $"
                << price
                << " to "
                << action
                << instrument->symbol()
                << std::endl;

        TradeActionResult tra = trade_actions()->SendNewOrder(params);
        if (tra == TRADE_ACTION_RESULT_SUCCESSFUL) {
                std::cout << "Sending new trade order successful!" << std::endl;
		std::cout << "Current Revenue = " << trade_revenue << std::endl;
		std::cout << "Stock at hand = " << trade_position << std::endl;
        } else {
                std::cout << "Error sending new trade order..." << tra << std::endl;
        }
    
}

//No additional, internal code needed here (added to make sure the RCM X software runs properly. Feel free to change to add complexity)
void HelloWorldClearStrategy::OnResetStrategyState() {
}

//No additional, internal code needed here (added to make sure the RCM X software runs properly. Feel free to change to add complexity)
void HelloWorldClearStrategy::OnParamChanged(StrategyParam& param) {
}
