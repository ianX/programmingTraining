#include <iostream>
#include <algorithm>
#include "SPPackingStrategy.h"
#include "SPPackingCommand.h"
#include "Layout.h"

using namespace std;
namespace RECTPACKING {

void SPPackingStrategy::initialPacking(Layout &layout)
{
    int rectNum = layout.getRectNum();
    if (rectNum < 2)
        return;

    vector<int> s1, s2;
    for (int i = 0; i < rectNum; ++ i)
    {
        s1.push_back(i);
    }
    s2 = s1;
    random_shuffle(s1.begin(), s1.end());
    random_shuffle(s2.begin(), s2.end());
    SPPackingCommand *spcmd = new SPPackingCommand(s1, s2);
    cout << "Packing Command in SPPackingStrategy::initialPacking" << endl;
    cout << *spcmd;

    setPackingCommand(spcmd);
    spcmd->interpretToLayout(layout);
    cout << "Layout after SPPackingStrategy::initialPacking" << endl;
    cout << layout;
    cout << "init finish" << endl;
}

void SPPackingStrategy::fallBack(Layout &layout)
{
    m_pCommand->fallBack(layout);
}

void SPPackingStrategy::nextPackingCommand()
{
    if (m_pCommand)
    {
        m_pCommand->next();
    }
}

void SPPackingStrategy::compPackingLayout(Layout &layout)
{
    layout.backup();
    if (m_pCommand)
        m_pCommand->interpretToLayout(layout);
}

void SPPackingStrategy::getCommand(std::vector<int> &s1, std::vector<int> &s2)
{
    ((SPPackingCommand*)m_pCommand)->getS1(s1);
    ((SPPackingCommand*)m_pCommand)->getS2(s2);
}

}
