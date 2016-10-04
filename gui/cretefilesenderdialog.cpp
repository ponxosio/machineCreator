#include "cretefilesenderdialog.h"

CreteFileSenderDialog::CreteFileSenderDialog(GraphicsManager* manager, QWidget* parent, Qt::WindowFlags f) :
    QDialog(parent, f)
{
    this->manager = manager;

    createBtn = new QPushButton("create");
    createBtn->setEnabled(false);

    QPushButton* cancelBtn = new QPushButton("calcel");
    QPushButton* searchInFile = new QPushButton("search in file");
    QPushButton* searchOutFile = new QPushButton("search out file");

    inEdit = new QLineEdit();
    inEdit->setReadOnly(true);

    outEdit = new QLineEdit();
    outEdit->setReadOnly(true);

    QTextEdit* description = new QTextEdit();
    description->setReadOnly(true);
    description->setText("<p>This sets the files used to test the machine, when a machine test a protocols the commands that the machine will receive are written in the \"out file\", any value read from the machine sensors will be read from the \"in file\" starting in  the frist line and looping when the end is met.</p>");

    QGroupBox* fileBox = new QGroupBox();
    QGridLayout* fileLayout = new QGridLayout();
    fileLayout->addWidget(inEdit, 0, 0);
    fileLayout->addWidget(searchInFile, 0, 1);
    fileLayout->addWidget(outEdit, 1, 0);
    fileLayout->addWidget(searchOutFile, 1, 1);
    fileBox->setLayout(fileLayout);

    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(description, 0, 0);
    mainLayout->addWidget(fileBox, 0, 1);
    mainLayout->addWidget(createBtn, 1, 0);
    mainLayout->addWidget(cancelBtn, 1, 1);
    setLayout(mainLayout);

    connect(searchInFile, SIGNAL(clicked(bool)), this, SLOT(searchInFile()));
    connect(searchOutFile, SIGNAL(clicked(bool)), this, SLOT(searchOutFile()));
    connect(createBtn, SIGNAL(clicked(bool)), this, SLOT(ok()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancel()));
}

CreteFileSenderDialog::~CreteFileSenderDialog()  {

}

void CreteFileSenderDialog::searchOutFile() {
    QString path = QFileDialog::getSaveFileName(this, "select out file to open", QString(), tr("ALL (*.*)"));
    if (!path.isEmpty()) {
        outEdit->setText(path);
        checkSetCreateBtn();
    }
}

void CreteFileSenderDialog::searchInFile() {
    QString path = QFileDialog::getOpenFileName(this, "select in file to open", QString(), tr("ALL (*.*)"));
    if (!path.isEmpty()) {
        inEdit->setText(path);
        checkSetCreateBtn();
    }
}

void CreteFileSenderDialog::ok() {
    std::unique_ptr<CommandSender> test = std::unique_ptr<CommandSender>(new FileSender(inEdit->text().toUtf8().constData(),
                                                                         outEdit->text().toUtf8().constData()));
    manager->setTestPrototype(std::move(test));
    accept();
}

void CreteFileSenderDialog::cancel() {
    reject();
}

void CreteFileSenderDialog::checkSetCreateBtn() {
    if (!inEdit->text().isEmpty() && !outEdit->text().isEmpty()) {
        createBtn->setEnabled(true);
    }
}
