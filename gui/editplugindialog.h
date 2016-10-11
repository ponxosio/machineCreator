#ifndef EDITPLUGINDIALOG_H
#define EDITPLUGINDIALOG_H

#include <vector>

//Qt
#include <QDialog>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


//local
#include <plugin/actuators/selfconfiguringplugin.h>

class EditPluginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EditPluginDialog(const std::string & name, std::shared_ptr<SelfConfiguringPlugin> plugin, QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~EditPluginDialog();

signals:

public slots:
    void done();
    void cancel();

protected:
    std::shared_ptr<SelfConfiguringPlugin> plugin;
    std::vector<std::pair<std::string, QLineEdit*>> paramsLineEditMap;

    void updatePlugin();
};

#endif // EDITPLUGINDIALOG_H
