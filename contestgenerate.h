#ifndef CONTESTGENERATE_H
#define CONTESTGENERATE_H

#include <QDialog>
#include <vector>

class QVBoxLayout;
class QLabel;
class QSpinBox;
namespace Ui {
class ContestGenerate;
}

using vectVectString = std::vector<std::vector<std::string>>;

enum
{
    MELEE, MELEE_MELEE, MANUAL
};

class ContestGenerate : public QDialog
{
    Q_OBJECT

private:
    vectVectString m_threePlayersTeam, m_twoPlayersTeam;
    QLabel *m_MenTotal, *m_WomenTotal, *m_DoubletNumber, *m_ThreesomeNumber;
    unsigned int m_threePlayersTeamNumber, m_twoPlayersTeamNumber;
    const QVBoxLayout* m_manLayout, *m_womanLayout;
    unsigned int m_numberMan = 0, m_numberWoman = 0;
    Ui::ContestGenerate *ui;
    unsigned int m_teamBuildOption = MELEE, m_gamesNumber = 0;
    std::vector<std::string> m_stockPlayersMen, m_stockPlayersWomen;
private:
    bool setNumberContestTeam();
    bool setNumberContestTeamForDefinedThreesome();
    bool linkWidgets();
    void updateUI();

public:
    explicit ContestGenerate(QWidget *parent = 0);
    void setTeamBuildOption(unsigned int option, unsigned int gamesNumber);
    void storePlayersNames();
    void generateTeam();
    void generateThreePlayersTeam();
    void generateTwoPlayersTeam();
    bool updateCurrentContest(const QVBoxLayout *manLayout, const QVBoxLayout *womanLayout);
    ~ContestGenerate();
};

#endif // CONTESTGENERATE_H