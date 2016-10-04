#include "createserialsenderdialog.h"

CreateSerialSenderDialog::CreateSerialSenderDialog(GraphicsManager* manager, QWidget* parent, Qt::WindowFlags f) :
    QDialog(parent, f)
{
    this->manager = manager;

    createBtn = new QPushButton("create");
    QPushButton* cancelBtn = new QPushButton("cancel");

    portEdit = new QLineEdit();
    comboBaud = new QComboBox();
    createComboBaud();

    QGroupBox* dataBox = new QGroupBox();
    QGridLayout* dataLayout = new QGridLayout();
    dataLayout->addWidget(new QLabel("device port:"), 0, 0);
    dataLayout->addWidget(portEdit, 0, 1);
    dataLayout->addWidget(new QLabel("baud rate:"), 1, 0);
    dataLayout->addWidget(comboBaud, 1, 1);
    dataBox->setLayout(dataLayout);

    QGroupBox* btnBox = new QGroupBox();
    QGridLayout* btnLayout = new QGridLayout();
    btnLayout->addWidget(createBtn, 0, 0);
    btnLayout->addWidget(cancelBtn, 1, 0);
    btnBox->setLayout(btnLayout);

    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(dataBox, 0, 0);
    mainLayout->addWidget(btnBox, 0, 1);
    setLayout(mainLayout);

    connect(createBtn, SIGNAL(clicked(bool)), this, SLOT(ok()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancel()));
}

CreateSerialSenderDialog::~CreateSerialSenderDialog() {

}


void CreateSerialSenderDialog::ok() {
    QString currentText = comboBaud->currentText();
    qint32 baudRate = boudMap[currentText];
    std::unique_ptr<CommandSender> exec = std::unique_ptr<CommandSender>(new SerialSender(portEdit->text().toUtf8().constData(), baudRate));
    manager->setExecPrototype(std::move(exec));
    accept();
}

void CreateSerialSenderDialog::cancel() {
    reject();
}

void CreateSerialSenderDialog::createComboBaud() {
    comboBaud->addItem("1200");
    boudMap.insert("1200", QSerialPort::Baud1200);

    comboBaud->addItem("2400");
    boudMap.insert("2400", QSerialPort::Baud2400);

    comboBaud->addItem("4800");
    boudMap.insert("4800", QSerialPort::Baud4800);

    comboBaud->addItem("9600");
    boudMap.insert("9600", QSerialPort::Baud9600);

    comboBaud->addItem("19200");
    boudMap.insert("19200", QSerialPort::Baud19200);

    comboBaud->addItem("38400");
    boudMap.insert("38400", QSerialPort::Baud38400);

    comboBaud->addItem("57600");
    boudMap.insert("57600", QSerialPort::Baud57600);

    comboBaud->addItem("115200");
    boudMap.insert("115200", QSerialPort::Baud115200);
}
