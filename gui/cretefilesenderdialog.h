#ifndef CRETEFILESENDERDIALOG_H
#define CRETEFILESENDERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextEdit>

#include "fluidControl/executable/containers/actuators/communications/CommandSender.h"
#include "fluidControl/executable/containers/actuators/communications/FileSender.h"
#include "gui/graphicsmanager.h"


class CreteFileSenderDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreteFileSenderDialog(GraphicsManager* manager, QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~CreteFileSenderDialog();

signals:   

public slots:
    void searchOutFile();
    void searchInFile();
    void ok();
    void cancel();

protected:
    QLineEdit* outEdit;
    QLineEdit* inEdit;
    QPushButton* createBtn;
    GraphicsManager* manager;

    void checkSetCreateBtn();
};

#endif // CRETEFILESENDERDIALOG_H
