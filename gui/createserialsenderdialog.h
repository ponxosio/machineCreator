#ifndef CREATESERIALSENDERDIALOG_H
#define CREATESERIALSENDERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QHash>
#include <QtSerialPort/QSerialPort>

#include "gui/graphicsmanager.h"
#include "fluidControl/executable/containers/actuators/communications/CommandSender.h"
#include "fluidControl/executable/containers/actuators/communications/SerialSender.h"

class CreateSerialSenderDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreateSerialSenderDialog(GraphicsManager* manager, QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~CreateSerialSenderDialog();

public slots:
    void ok();
    void cancel();

protected:
    QLineEdit* portEdit;
    QComboBox* comboBaud;
    QPushButton* createBtn;
    GraphicsManager* manager;
    QHash<QString, int> boudMap;

    void checkSetCreateBtn();
    void createComboBaud();
};

#endif // CREATESERIALSENDERDIALOG_H
