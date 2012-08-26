#ifndef __SP_SPPACKINGSTRATEGY_H__
#define __SP_SPPACKINGSTRATEGY_H__
#include <vector>
#include <utility>
#include "PackingStrategy.h"

namespace RECTPACKING {
using namespace std;

class Layout;
class SPPackingStrategy : public PackingStrategy
{
public:
    SPPackingStrategy():PackingStrategy() {}
    ~SPPackingStrategy() {}
    void initialPacking(Layout &layout);
    void compPackingLayout(Layout &layout);
    void nextPackingCommand();
    void fallBack(Layout &layout);
    void getCommand(std::vector<int> &s1, std::vector<int> &s2);
};

}

#endif	//__SP_PACKINGSTRATEGY_H__
