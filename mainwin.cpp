#include "mainwin.h"
#include "ui_mainwin.h"
#include <QHeaderView>
#include "contactmanager.h"
#include <QDebug>
#include <QList>
#include <QStringList>
#include "mainwindow.h"
#include <QMessageBox>
#include "auth.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QJsonArray>

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);

    // Resize columns to contents
    for (int i = 0; i < ui->tableWidget->columnCount(); ++i) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    InsertDataInTable();

    // Connect the finished signal of the network manager to a custom slot
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWin::onNetworkReplyFinished);
}

MainWin::~MainWin()
{
    delete ui;
}


void MainWin::onNetworkReplyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        qDebug() << "Response:" << responseData;

        QMessageBox::information(this, "Success", "Message sent successfully!");
        ui->isSendingEmailLabel->setText("");
        ui->sendEmailBtn->setText(" Send Email");
        whichButtonActive("toAllContactBtn");
        ui->stackedWidget->setCurrentIndex(0);
        ui->senderEmailPasswordInput->clear();
        ui->recipientsEmailInput->clear();
        ui->emailSubjectInput->clear();
        ui->emailBodyInput->clear();

    } else {
        qDebug() << "Error:" << reply->errorString();

        QMessageBox::critical(this, "Error", "Failed to send message.");
    }

    // Clean up the reply object
    reply->deleteLater();
}

void MainWin::openNextWindow(){
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->hide();
}


QString MainWin::setBtnStyle(const QString &Img, const QString &clr) {
    return QString(
               "image: url(%1);"
               "background-color: %2;"
               "border: none;"
               "padding: 15px;"
               ).arg(Img).arg(clr);
}

void MainWin::whichButtonActive(const QString &button) {
    if (button == "toAllContactBtn") {
        ui->toAllContactBtn->setStyleSheet(setBtnStyle(":/asserts/contact-list.png", "white"));
        ui->toAddContactBtn->setStyleSheet(setBtnStyle(":/asserts/add-user.png", "orange"));
        ui->toSettingBtn->setStyleSheet(setBtnStyle(":/asserts/settings.png", "orange"));
    } else if (button == "toAddContactBtn") {
        ui->toAllContactBtn->setStyleSheet(setBtnStyle(":/asserts/contact-list.png", "orange"));
        ui->toAddContactBtn->setStyleSheet(setBtnStyle(":/asserts/add-user.png", "white"));
        ui->toSettingBtn->setStyleSheet(setBtnStyle(":/asserts/settings.png", "orange"));
    } else if (button == "toSettingBtn") {
        ui->toAllContactBtn->setStyleSheet(setBtnStyle(":/asserts/contact-list.png", "orange"));
        ui->toAddContactBtn->setStyleSheet(setBtnStyle(":/asserts/add-user.png", "orange"));
        ui->toSettingBtn->setStyleSheet(setBtnStyle(":/asserts/settings.png", "white"));
    } else {
        ui->toAllContactBtn->setStyleSheet(setBtnStyle(":/asserts/contact-list.png", "orange"));
        ui->toAddContactBtn->setStyleSheet(setBtnStyle(":/asserts/add-user.png", "orange"));
        ui->toSettingBtn->setStyleSheet(setBtnStyle(":/asserts/settings.png", "orange"));
    }
}

QString MainWin::setAccountSettingNavBtnStyle(const QString &clr){
    // clr => white |  rgb(255, 191, 64)
    return QString(
               "font: 700 12pt;"
               "padding: 1px 20px;"
               "background-color: %1;"
               "border:none;"
               ).arg(clr);
}

void MainWin::whichButtonActiveOnAccountSettingTab(const QString &button) {
    if (button == "toUserInfoBtn") {
        ui->toUserInfoBtn->setStyleSheet(setAccountSettingNavBtnStyle("white"));
        ui->toEdituserInfoBtn->setStyleSheet(setAccountSettingNavBtnStyle(" rgb(255, 191, 64)"));
        ui->toChangePassword->setStyleSheet(setAccountSettingNavBtnStyle(" rgb(255, 191, 64)"));
        ui->toDeleteAccount->setStyleSheet(setAccountSettingNavBtnStyle(" rgb(255, 191, 64)"));
    } else if (button == "toEdituserInfoBtn") {
        ui->toUserInfoBtn->setStyleSheet(setAccountSettingNavBtnStyle(" rgb(255, 191, 64)"));
        ui->toEdituserInfoBtn->setStyleSheet(setAccountSettingNavBtnStyle("white"));
        ui->toChangePassword->setStyleSheet(setAccountSettingNavBtnStyle(" rgb(255, 191, 64)"));
        ui->toDeleteAccount->setStyleSheet(setAccountSettingNavBtnStyle(" rgb(255, 191, 64)"));
    } else if (button == "toChangePassword") {
        ui->toUserInfoBtn->setStyleSheet(setAccountSettingNavBtnStyle(" rgb(255, 191, 64)"));
        ui->toEdituserInfoBtn->setStyleSheet(setAccountSettingNavBtnStyle(" rgb(255, 191, 64)"));
        ui->toChangePassword->setStyleSheet(setAccountSettingNavBtnStyle("white"));
        ui->toDeleteAccount->setStyleSheet(setAccountSettingNavBtnStyle(" rgb(255, 191, 64)"));
    } else if (button == "toDeleteAccount") {
        ui->toUserInfoBtn->setStyleSheet(setAccountSettingNavBtnStyle(" rgb(255, 191, 64)"));
        ui->toEdituserInfoBtn->setStyleSheet(setAccountSettingNavBtnStyle(" rgb(255, 191, 64)"));
        ui->toChangePassword->setStyleSheet(setAccountSettingNavBtnStyle(" rgb(255, 191, 64)"));
        ui->toDeleteAccount->setStyleSheet(setAccountSettingNavBtnStyle("white"));
    }
}


void MainWin::InsertRowToTable(QStringList contact){
    int newRowIndex = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRowIndex);
for(int i=0;i<6;i++){
    ui->tableWidget->setItem(newRowIndex, i, new QTableWidgetItem(contact[i]));
}
    // ui->tableWidget->setItem(newRowIndex, 1, new QTableWidgetItem(contact[1]));
    // ui->tableWidget->setItem(newRowIndex, 2, new QTableWidgetItem(contact[2]));
    // ui->tableWidget->setItem(newRowIndex, 3, new QTableWidgetItem(contact[3]));
    // ui->tableWidget->setItem(newRowIndex, 4, new QTableWidgetItem(contact[4]));
    // ui->tableWidget->setItem(newRowIndex, 5, new QTableWidgetItem(contact[5]));
}

void MainWin::InsertDataInTable(){

    ContactManager contactM;
    ui->tableWidget->setRowCount(0);
    for(int i = 0 ; i < contactM.allContacts.size(); i++){
        InsertRowToTable(contactM.allContacts[i]);
    }

}

QStringList MainWin::getSelectedRow() {
    int selectedRowIndex = ui->tableWidget->currentRow();

    if (selectedRowIndex == -1) {
        QMessageBox::warning(this, "No Selection", "Please select a row first!");
        return QStringList();
    }

    QStringList rowValues;

    for (int i = 0; i < 6; i++) {
        QTableWidgetItem *item = ui->tableWidget->item(selectedRowIndex, i);
        // If a cell in the selected row is empty could return nullptr, couse issues so:
        if (item) {
            rowValues.append(item->text());
        } else {
            rowValues.append("");
        }
    }

    return rowValues;
}


QList<QStringList> MainWin::getMultipleSelectedRows(){
    QList<QStringList> selectedData;
    QList<QTableWidgetSelectionRange> selectedRanges = ui->tableWidget->selectedRanges();

    if (selectedRanges.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select a row first!");
        qDebug() << "No rows selected!";
        return selectedData;
    }

    for (const QTableWidgetSelectionRange &range : selectedRanges) {
        for (int row = range.topRow(); row <= range.bottomRow(); ++row) {
            QStringList rowData;

            for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
                QTableWidgetItem *item = ui->tableWidget->item(row, col);
                if (item) {
                    rowData.append(item->text());
                } else {
                    rowData.append("");
                }
            }

            selectedData.append(rowData);
        }
    }

    return selectedData;
}

void MainWin::on_toAllContactBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    whichButtonActive("toAllContactBtn");
}

void MainWin::on_toAddContactBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    whichButtonActive("toAddContactBtn");
}

void MainWin::setUserDataInUi(){
    Auth auth;
    QStringList data = auth.getAccountData();
    if (!data.isEmpty()) {
        ui->editAccountInputName->setText(data[0]);
        ui->editAccountInputEmail->setText(data[2]);
        ui->editAccountInputPhone->setText(data[3]);
        ui->editAccountInputCreatedAt->setText(data[4].section('T',0,0));

        ui->nameUserInfoLabel->setText(data[0]);
        ui->emailUserInfoLabel->setText(data[2]);
        ui->phoneUserInfoLabel->setText(data[3]);
        ui->joiningDateUserInfoLabel->setText(data[4].section('T',0,0));

    } else {
        QMessageBox::warning(this,"Error","Error fetching user info");
    }
}

void MainWin::on_toSettingBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->stackedWidget_2->setCurrentIndex(0);
    whichButtonActive("toSettingBtn");
    whichButtonActiveOnAccountSettingTab("toUserInfoBtn");
    setUserDataInUi();
}

void MainWin::on_addContactBtn_clicked()
{
    ContactManager contactM;
    QString name = ui->addContactInputName->text().trimmed();
    QString phone = ui->addContactInputPhone->text().trimmed();
    QString email = ui->addContactInputEmail->text().trimmed();
    QString address = ui->addContactInputAddress->text().trimmed();
    QString description = ui->addContactInputDescription->text().trimmed();

    if(!name.isEmpty() && !email.isEmpty() && !phone.isEmpty()){
        if(email.isLower() && email.contains('@') && email.contains('.')){
            if(phone.size() > 10){
             QString res = contactM.addContact(name,phone,email,address,description);
                if(res == "true"){
                    ui->stackedWidget->setCurrentIndex(0);
                    InsertDataInTable();
                    whichButtonActive("toAllContactBtn");

                    ui->addContactInputName->clear();
                    ui->addContactInputPhone->clear();
                    ui->addContactInputEmail->clear();
                    ui->addContactInputAddress->clear();
                    ui->addContactInputDescription->clear();
                    ui->addContactErrortextBrowser->clear();
                } else {
                    ui->addContactErrortextBrowser->setText(res);
                }
            } else {
                ui->addContactErrortextBrowser->setText("*Invalid Phone number");
            }
        } else {
             ui->addContactErrortextBrowser->setText("*Invalid Email format");
        }
    } else {
        ui->addContactErrortextBrowser->setText("*Name, Phone and Email are required Fields");
    }
}


void MainWin::on_toEditBtn_clicked()
{
    QStringList rowValues = getSelectedRow();
    if(!rowValues.isEmpty()){
        ui->editContactInputContactId->setText(rowValues[0]);
        ui->editContactInputName->setText(rowValues[1]);
        ui->editContactInputPhone->setText(rowValues[2]);
        ui->editContactInputEmail->setText(rowValues[3]);
        ui->editContactInputAddress->setText(rowValues[4]);
        ui->editContactInputDescription->setText(rowValues[5]);


        ui->stackedWidget->setCurrentIndex(2);
        whichButtonActive("toEditBtn");
    }
}


void MainWin::on_editContactBtn_clicked()
{
    QString contactId = ui->editContactInputContactId->text();
    QString name = ui->editContactInputName->text().trimmed();
    QString phone = ui->editContactInputPhone->text().trimmed();
    QString email = ui->editContactInputEmail->text().trimmed();
    QString address = ui->editContactInputAddress->text().trimmed();
    QString description = ui->editContactInputDescription->text().trimmed();

    if (!name.isEmpty() && !email.isEmpty() && !phone.isEmpty()) {
        if (email.isLower() && email.contains('@') && email.contains('.')) {
            if (phone.size() > 10) {
                ContactManager contactM;
                QString res = contactM.editContact(contactId.toInt(),name, phone, email, address, description);
                if (res == "true") {
                    ui->stackedWidget->setCurrentIndex(0);
                    whichButtonActive("toAllContactBtn");
                    InsertDataInTable();

                    ui->editContactInputName->clear();
                    ui->editContactInputPhone->clear();
                    ui->editContactInputEmail->clear();
                    ui->editContactInputAddress->clear();
                    ui->editContactInputDescription->clear();
                    ui->editContactErrortextBrowser->clear();
                } else {
                    ui->editContactErrortextBrowser->setText(res);
                }
            } else {
                ui->editContactErrortextBrowser->setText("*Invalid Phone number");
            }
        } else {
            ui->editContactErrortextBrowser->setText("*Invalid Email format");
        }
    } else {
        ui->editContactErrortextBrowser->setText("*Name, Phone and Email are required Fields");
    }

}

void MainWin::on_DeleteContactBtn_clicked()
{
    QStringList rowValues = getSelectedRow();
    if(!rowValues.isEmpty()){
        int contactId = rowValues[0].toInt();
        QString name = rowValues[1];

        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Delete Contact",
            QString("Are you sure you want to delete the contact '%1'?").arg(name),
            QMessageBox::Yes | QMessageBox::No
            );
        if (reply == QMessageBox::Yes) {
            ContactManager contactM;
            QString res = contactM.removeContact(contactId);
            if(res == "true"){
                InsertDataInTable();
                QMessageBox::information(this, "Success", "Contact deleted successfully!");
            } else {
                QMessageBox::critical(this,"Error",res);
            }
        }
    }
}


void MainWin::on_logoutBtn_clicked()
{
    Auth auth;
    bool res = auth.logout();
    if(res){
        openNextWindow();
    }

}


void MainWin::on_editAccountBtn_clicked()
{
    QString name =  ui->editAccountInputName->text().trimmed();
    QString phone = ui->editAccountInputPhone->text().trimmed();

        Auth auth;
        QString res = auth.editAccount(name,phone);
        if(res == "true"){
            QMessageBox::information(this,"Success","Account has successfully Updated");
        } else {
            ui->editAccountErrorlabel->setText(res);
        }

}


void MainWin::on_showHideChangePasswordBtn_clicked()
{
    if(ui->showHideChangePasswordBtn->text() == "Show Password"){
        ui->oldPasswordInput->setEchoMode(QLineEdit::Normal);
        ui->newPasswordInput->setEchoMode(QLineEdit::Normal);
        ui->confirmPasswordInput->setEchoMode(QLineEdit::Normal);
        ui->showHideChangePasswordBtn->setText("Hide Password");
    } else {
        ui->oldPasswordInput->setEchoMode(QLineEdit::Password);
        ui->newPasswordInput->setEchoMode(QLineEdit::Password);
        ui->confirmPasswordInput->setEchoMode(QLineEdit::Password);
        ui->showHideChangePasswordBtn->setText("Show Password");
    }
}


void MainWin::on_changePassworBtn_clicked()
{
    QString oldPassword = ui->oldPasswordInput->text();
    QString newPassword = ui->newPasswordInput->text();
    QString confirmPassword = ui->confirmPasswordInput->text();

    Auth auth;
    QString res = auth.changePassword(oldPassword,newPassword,confirmPassword);
    if(res == "true"){
        QMessageBox::information(this,"succcess","Password changed successfully");
        ui->oldPasswordInput->setText("");
        ui->newPasswordInput->setText("");
        ui->confirmPasswordInput->setText("");
    } else {
       ui->changePasswordErrortextBrowser->setText(res);
    }

}


void MainWin::on_toEdituserInfoBtn_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    whichButtonActiveOnAccountSettingTab("toEdituserInfoBtn");
}


void MainWin::on_toChangePassword_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
    whichButtonActiveOnAccountSettingTab("toChangePassword");
}


void MainWin::on_toUserInfoBtn_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
    setUserDataInUi();
    whichButtonActiveOnAccountSettingTab("toUserInfoBtn");
}


void MainWin::on_toDeleteAccount_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
    whichButtonActiveOnAccountSettingTab("toDeleteAccount");
}

// void searchAndSetInTable(){

// }

void MainWin::on_searchInput_textChanged(const QString &arg1)
{
    QString searchedText = ui->searchInput->text().toLower().trimmed();
    if(!searchedText.isEmpty()){
    ContactManager contactM;
    QList<QStringList> searchedItems = contactM.searchContact(searchedText);
     ui->tableWidget->setRowCount(0);
    for(int i = 0 ; i < searchedItems.size(); i++){
        InsertRowToTable(searchedItems[i]);
    }
    } else {
        InsertDataInTable();
    }
}


void MainWin::on_sendEmailBtn_clicked()
{
    ui->isSendingEmailLabel->setText("Sending...");
    ui->sendEmailBtn->setText(" Sending....");
    QList<QStringList> selectedRowsValues = getMultipleSelectedRows();
    QJsonObject jsonPayload;
    jsonPayload["sender_email"] = ui->senderEmailInput->text().trimmed();
    jsonPayload["sender_password"] = ui->senderEmailPasswordInput->text();
    jsonPayload["subject"] = ui->emailSubjectInput->text().trimmed();
    jsonPayload["body"] = ui->emailBodyInput->toPlainText().trimmed();
    QJsonArray recipients;
    for(int i = 0 ; i < selectedRowsValues.size(); i++){
        recipients.append(selectedRowsValues[i][3]);
    }
    jsonPayload["listRecipients"] = recipients;

    // Convert JSON object to QByteArray
    QJsonDocument jsonDoc(jsonPayload);
    QByteArray jsonData = jsonDoc.toJson();

    // Set up the POST request
    QNetworkRequest request(QUrl("http://127.0.0.1:5000/sendMail"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Make the POST request
    networkManager->post(request, jsonData);
}

void MainWin::on_toSendEmailBtn_clicked()
{

    QList<QStringList> selectedRowsValues = getMultipleSelectedRows();
    if(!selectedRowsValues.isEmpty()){
    ui->stackedWidget->setCurrentIndex(4);
    whichButtonActive("SendEmail");
    QString selectedEmailStr;

    for(int i = 0 ; i < selectedRowsValues.size(); i++){
        if(!selectedEmailStr.isEmpty()){
           selectedEmailStr.append(", ");
        }
        selectedEmailStr.append(selectedRowsValues[i][3]);
    }

    ui->recipientsEmailInput->setPlainText(selectedEmailStr);
    }
}


void MainWin::on_cancelSendEmailBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->senderEmailInput->clear();
    ui->senderEmailPasswordInput->clear();
    ui->recipientsEmailInput->clear();
    ui->emailSubjectInput->clear();
    ui->emailBodyInput->clear();
    whichButtonActive("toAllContactBtn");
}


void MainWin::on_deleteAccountBtn_clicked()
{
    Auth auth;
    QString res = auth.deleteAccount(ui->deleteAcxoutPasswordInput->text());
    if(res == "true"){
        if(auth.logout()){
            openNextWindow();
        }
    } else {
        QMessageBox::warning(this,"Error",res);
    }
}

