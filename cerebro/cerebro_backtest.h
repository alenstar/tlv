#pragma once
#include "cerebro_struct.h"

class CerebroBroker;
class CerebroAccountWrap;
class CerebroBacktest
{
    public:
    CerebroBacktest();
    ~CerebroBacktest();
    int init(const CerebroConfig& conf);
    int run();

    void add_strategy(CerebroStrategyPtr strategy) 
    {
        strategys_[strategy->name()] = strategy;
    }
    protected:

    private:
    CerebroConfig conf_;
    std::map<std::string, CerebroStrategyPtr> strategys_;
    CerebroBroker* broker_{nullptr};
        // CerebroAccountWrapPtr account_{nullptr};
       std::shared_ptr<CerebroAccountWrap> account_{nullptr};
    int64_t last_order_id_{0};
};