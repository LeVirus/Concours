#include "presetteamform.h"
#include "ui_presetteamform.h"
#include "teamline.h"
#include <QMessageBox>

PresetTeamForm::PresetTeamForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PresetTeamForm)
{
    ui->setupUi(this);
    setLayouts();
    linkUIElement();
}

bool PresetTeamForm::delTeam(const std::string &playerA,
                             const std::string &playerB,
                             const std::string &playerC)
{
    for(itStrVect_t it = m_vectPlayers.begin(); it != m_vectPlayers.end(); ++it)
    {
        if((*it)[0] == playerA &&
           (*it)[1] == playerB &&
           ((*it).size() <= 2 || (*it)[2] == playerC))
        {
            m_vectPlayers.erase(it);
            return true;
        }
    }
    return false;
}

PresetTeamForm::~PresetTeamForm()
{
    delete ui;
}

void PresetTeamForm::linkUIElement()
{
    playerA = findChild<QLineEdit*>("lineEdit");
    playerB = findChild<QLineEdit*>("lineEdit_2");
    playerC = findChild<QLineEdit*>("lineEdit_3");

}

void PresetTeamForm::displayError(const std::string &message)const
{
    QMessageBox msgBox;
    msgBox.setText(QString(message.c_str()));
    msgBox.exec();
}


void PresetTeamForm::on_pushButton_clicked()
{
    QString strA = playerA->text();
    QString strB = playerB->text();
    QString strC = playerC->text();
    if(strA.isEmpty() || strB.isEmpty())
    {
        displayError("Erreur: Mauvaises entrée(s) d'équipe.");
        return;
    }
    std::string strStdA = strA.toStdString();
    std::string strStdB = strB.toStdString();
    std::string strStdC = strC.toStdString();
    if(checkEqualsEntries(strStdA, strStdB, strStdC) ||
            checkExistingPlayers(strStdA, strStdB, strStdC))
    {
        return;
    }
    if(!strC.isEmpty())
    {
        m_vectPlayers.emplace_back(vectStr_t{strStdA, strStdB, strStdC});
    }
    else
    {
        m_vectPlayers.emplace_back(vectStr_t{strStdA, strStdB});
    }
    m_TeamLayout->addLayout(new TeamLine(*this, strStdA, strStdB, strStdC));
    clearLineEdit();
}

void PresetTeamForm::setLayouts()
{
    QScrollArea *sds = findChild<QScrollArea*>("scrollArea");
    m_TeamLayout = new QVBoxLayout(sds);
    sds->setLayout(m_TeamLayout);
    QWidget* wid = findChild<QScrollArea*>("scrollArea")->
            findChild<QWidget*>("scrollAreaWidgetContents");
    wid->setLayout(m_TeamLayout);
    wid->setMaximumWidth(300);
}

void PresetTeamForm::clearLineEdit()
{
    playerA->clear();
    playerB->clear();
    playerC->clear();
}

bool PresetTeamForm::checkEqualsEntries(const std::string &strA,
                                        const std::string &strB,
                                        const std::string &strC)const
{
    if(strA == strB || strA == strC || strB == strC)
    {
        displayError("Erreur noms entrés similaires.");
        return true;
    }
    return false;
}

bool PresetTeamForm::checkExistingPlayers(const std::string &strA,
                                          const std::string &strB,
                                          const std::string &strC)const
{
    bool res = false;
    bool playerFoundA = false,
         playerFoundB = false,
         playerFoundC = false;
    std::string message = "Erreur joueur(s) déja existant(s)\n";
    for(size_t i = 0; i < m_vectPlayers.size(); ++i)
    {
        if((!playerFoundA && m_vectPlayers[i][0] == strA) ||
                (m_vectPlayers[i][1] == strA) ||
                (m_vectPlayers[i].size() > 2 && m_vectPlayers[i][2] == strA))
        {
            res = true;
            playerFoundA = true;
            message += " " + strA;
        }
        if((!playerFoundB && m_vectPlayers[i][0] == strB) ||
                (m_vectPlayers[i][1] == strB) ||
                (m_vectPlayers[i].size() > 2 && m_vectPlayers[i][2] == strB))
        {
            res = true;
            playerFoundB = true;
            message += " " + strB;
        }
        if((!playerFoundC && m_vectPlayers[i][0] == strC) ||
                (m_vectPlayers[i][1] == strC) ||
                (m_vectPlayers[i].size() > 2 && m_vectPlayers[i][2] == strC))
        {
            res = true;
            playerFoundC = true;
            message += " " + strC;
        }
    }
    if(res)
    {
        displayError(message);
    }
    return res;
}