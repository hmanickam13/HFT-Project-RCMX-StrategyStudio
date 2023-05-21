#ifdef _WIN32
    #include "stdafx.h"
#endif

#include "TorchStrategy.h"

const std::string path_to_model = "path/to/your/torch/model/torch.pt";


TorchStrategy::TorchStrategy(StrategyID strategyID,
                    const std::string& strategyName,
                    const std::string& groupName):
    Strategy(strategyID, strategyName, groupName) {
        
        try {
            // Deserialize the ScriptModule from a file using torch::jit::load().
            model = torch::jit::load(path_to_model);
        }
        
        catch (const c10::Error& e) {
            std::cerr << "error loading the model\n";
        }

}

TorchStrategy::~TorchStrategy() {
}

void TorchStrategy::DefineStrategyParams() {
}

void TorchStrategy::RegisterForStrategyEvents(
    StrategyEventRegister* eventRegister, DateType currDate) {
}

void TorchStrategy::OnTrade(const TradeDataEventMsg& msg) {

}


void TorchStrategy::OnOrderUpdate(const OrderUpdateEventMsg& msg) {
}

void TorchStrategy::OnBar(const BarEventMsg& msg) {
}

void TorchStrategy::AdjustPortfolio() {
}

void TorchStrategy::SendOrder(const Instrument* instrument, int trade_size) {
    
}

void TorchStrategy::OnResetStrategyState() {
}

void TorchStrategy::OnParamChanged(StrategyParam& param) {
}