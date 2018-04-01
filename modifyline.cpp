#include "modifyline.h"
#include "ui_modifyline.h"
#include "playerline.h"
#include "form.h"
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QKeyEvent>

ModifyLine::ModifyLine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyLine)
{
    ui->setupUi(this);
    QPushButton* buttonOK = findChild<QPushButton*>("pushButton_2");
    QPushButton* buttonCancel = findChild<QPushButton*>("pushButton");
    m_comboBox = findChild<QComboBox*>("comboBox");
    m_lineEdit = findChild<QLineEdit*>("lineEdit");

    if(buttonOK)
    {
        QObject::connect(buttonOK, SIGNAL(clicked()), this, SLOT(clickedOk()));
    }
    if(buttonCancel)
    {
        QObject::connect(buttonCancel, SIGNAL(clicked()), this,
                         SLOT(clickedCancel()));
    }

}

void ModifyLine::setParams(const QString &nom, bool homme, PlayerLine *refPlayerLine)
{
    if(m_comboBox && m_lineEdit)
    {
        if(homme)
        {
            m_comboBox->setCurrentIndex(HOMME);
        }
        else
        {
            m_comboBox->setCurrentIndex(FEMME);
        }
        m_PreviousLabelValue = nom;
        m_lineEdit->setText(nom);
        m_memPlayerLine = refPlayerLine;
    }
}

void ModifyLine::clickedOk()
{
    if(m_comboBox && m_lineEdit && m_memPlayerLine)
    {
        modifyPlayerLineGender();

        if(! modifyPlayerLineLabel())
        {
            return;
        }
    }
    m_memPlayerLine = nullptr;
    Form::getInstance()->setDataSaved(false);
    hide();
}

bool ModifyLine::modifyPlayerLineLabel()
{
    Form* instance = Form::getInstance();
    const QString &memStrLabel = m_lineEdit->text();
    if(m_PreviousLabelValue != memStrLabel && instance)
    {
        if(! instance->checkGlobalExist(memStrLabel))
        {
            m_memPlayerLine->setLabel(memStrLabel);
        }
        else
        {
            QMessageBox::warning(this, "Erreur", "Le nom entré est déja existant.");
            return false;
        }
    }
    return true;
}

void ModifyLine::modifyPlayerLineGender()
{
    bool currentGender = m_memPlayerLine->getGender();
    if(m_comboBox->currentIndex() == HOMME)
    {
        m_memPlayerLine->setGender(true);
    }
    else if(m_comboBox->currentIndex() == FEMME)
    {
        m_memPlayerLine->setGender(false);
    }
    if(currentGender != m_memPlayerLine->getGender())
    {
        changeArrayLine();
    }
}

void ModifyLine::clickedCancel()
{
    m_memPlayerLine = nullptr;
    hide();
}

void ModifyLine::changeArrayLine()
{
    Form::getInstance()->changePlayerLineGenderArray(m_memPlayerLine);
}

void ModifyLine::keyPressEvent(QKeyEvent *e)
{
    switch (e->key ()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
    clickedOk();
        break;

    default:
        QDialog::keyPressEvent (e);
    }
}

ModifyLine::~ModifyLine()
{
    delete ui;
}
