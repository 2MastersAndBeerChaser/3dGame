#ifndef CAVEGENERATOR_H
#define CAVEGENERATOR_H
#include <vector>
#include <QTime>

class CaveGenerator
{
public:
    CaveGenerator(int width, int height, int simulationSteps = 5, double initChance = 0.35f, int birthLimit = 4, int deathLimit = 3);
    std::vector<std::vector<int> > GetCaveMap();
private:
    void Init();
    void DoSimulationStep();
    int CountAliveNeighbours(int x, int y);
    void ToDebug();

    std::vector<std::vector<int> > m_map;
    double m_initialChance;
    int m_width;
    int m_height;
    int m_birthLimit;
    int m_deathLimit;
    bool m_beenSimulated;
    int m_simulationSteps;
};

#endif // CAVEGENERATOR_H
