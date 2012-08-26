#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>
#include "SPPackingCommand.h"
#include "GraphPacking.h"
#include "Layout.h"

namespace RECTPACKING {
using namespace std;

void SPPackingCommand::interpretToLayout(Layout &layout)
{
    //cout << "In SPPackingCommand::interpretToLayout" << endl;
    //build position map
    int length = m_s1.size();
    vector<int> s1(length, 0), s2(length, 0);
    for (int i = 0; i < length; ++ i)
    {
        s1[m_s1[i]] = i;
        s2[m_s2[i]] = i;
    }
    //compute the horizontal constraint pairs and vertical constraint pairs
    vector<pair<int, int> > horCons;
    vector<pair<int, int> > verCons;
    for (int i = 0; i < length; ++ i)
    {
        for (int j = 0; j < length; ++ j)
        {
            if (i != j)
            {
                //bb->left: i is to the left of j
                if (s1[i] < s1[j] && s2[i] < s2[j])
                {
                    horCons.push_back(make_pair(i, j));
                }
                //ab->below: i is below j
                if (s1[i] > s1[j] && s2[i] < s2[j])
                {
                    verCons.push_back(make_pair(i, j));
                }
            }
        }
    }
    //packing by the longest path algorithm
    LongestGraphPacking(horCons, verCons, layout);
    //std::cout<<layout;
}

void SPPackingCommand::change(vector<int> &m_s)
{
    int size = m_s.size();
    int i1 = rand() % size;
    int i2 = rand() % size;
    while (i1 == i2)
    {
        i2 = rand() % size;
    }
    int tmp = m_s[i1];
    m_s[i1] = m_s[i2];
    m_s[i2] = tmp;
}

void SPPackingCommand::fallBack(Layout &layout)
{
    layout.setRects(layout.getBack());
    m_s1.clear();
    m_s1.insert(m_s1.end(),back_s1.begin(),back_s1.end());
    m_s2.clear();
    m_s2.insert(m_s2.end(),back_s2.begin(),back_s2.end());
}

void SPPackingCommand::backup()
{
    back_s1.clear();
    back_s1.insert(back_s1.end(), m_s1.begin(),m_s1.end());
    back_s2.clear();
    back_s2.insert(back_s2.end(), m_s2.begin(),m_s2.end());
}

void SPPackingCommand::next()
{
    backup();
    if (rand() % 2)
        change(m_s1);
    else
        change(m_s2);
}

void SPPackingCommand::dump(ostream &out)
{
    out << "Sequence Pair:";
    for (int i = 0; i < (int)m_s1.size(); ++ i)
    {
        out << " " << m_s1[i];
    }
    out << ",";
    for (int i = 0; i < (int)m_s2.size(); ++ i)
    {
        out << " " << m_s2[i];
    }
    out << endl;
}

}
