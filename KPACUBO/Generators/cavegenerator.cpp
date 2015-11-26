#include "cavegenerator.h"

CaveGenerator::CaveGenerator(int width, int height, int simulationSteps, double initChance, int birthLimit, int deathLimit)
    : m_initialChance(initChance),
      m_width(width),
      m_height(height),
      m_birthLimit(birthLimit),
      m_deathLimit(deathLimit),
      m_beenSimulated(true),
      m_simulationSteps(simulationSteps)
{
    m_map.resize(m_width);
    for (int i = 0; i < m_width; i++)
    {
        m_map[i].resize(m_height);
    }

}

std::vector<std::vector<int> > CaveGenerator::GetCaveMap()
{
    Init();
    for (int i = 0; i < m_simulationSteps && m_beenSimulated; i++)
    {
        DoSimulationStep();
    }
    //ToDebug();
    return m_map;
}

void CaveGenerator::Init()
{

    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height; j++)
        {
            double rnd = (qrand() % 100) / 100.0f;
            if (rnd < m_initialChance)
            {
                m_map[i][j] = 1;
            }
            else
            {
                m_map[i][j] = 0;
            }
        }
    }
}

void CaveGenerator::DoSimulationStep()
{
    std::vector<std::vector<int> > newMap = m_map;
    m_beenSimulated = false;
    for (int x = 0; x < m_width; x++)
    {
        for (int y = 0; y < m_height; y++)
        {
            int numberOfNeighbours = CountAliveNeighbours(x, y);
            if (m_map[x][y] == 1)
            {
                if (numberOfNeighbours < m_deathLimit)
                {
                    newMap[x][y] = 0;
                    m_beenSimulated = true;
                }
            }
            else
            {
                if (numberOfNeighbours > m_birthLimit)
                {
                    newMap[x][y] = 1;
                    m_beenSimulated = true;
                }
            }
        }
    }
    m_map = newMap;
}

int CaveGenerator::CountAliveNeighbours(int x, int y)
{
    int count = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            else
            {
                int neiX = x + i;
                int neiY = y + j;
                if (neiX < 0 || neiY < 0 || neiX >= m_width || neiY >= m_height)
                {
                    count++;
                }
                else if (m_map[neiX][neiY] == 1)
                {
                    count++;
                }
            }
        }
    }
    return count;
}

void CaveGenerator::ToDebug()
{
    for (int i = 0; i < m_width; i++)
    {
        QString s = "";
        for (int j = 0; j < m_height; j++)
        {
            s += QString::number(m_map[i][j]);
        }
        qDebug() << s;
    }
}
