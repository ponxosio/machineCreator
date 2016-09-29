#ifndef IDEMITINGPUSHBUTTON_H
#define IDEMITINGPUSHBUTTON_H

#include <QPushButton>

class IdEmitingPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit IdEmitingPushButton(int id, const QString &text, QWidget *parent = Q_NULLPTR);
    explicit IdEmitingPushButton(int id, const QString &text, const QIcon &icon, QWidget *parent = Q_NULLPTR);
    virtual ~IdEmitingPushButton();

signals:
    void clicked_id(int id);
public slots:
    void buttonClick(bool checked = false);

protected:
    int id;
};

#endif // IDEMITINGPUSHBUTTON_H
