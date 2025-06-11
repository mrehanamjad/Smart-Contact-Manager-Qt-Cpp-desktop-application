# 📇 Contact Management System (CMS)

A full-featured **Contact Management System** built using **Qt C++ (OOP)** and **MySQL**, with integrated **email sending functionality**. The application allows users to manage their personal or professional contacts with ease — including login, sign-up, and sending emails directly from the app.

---

## ✨ Features

- 🔐 **User Authentication**
  - Sign up / Login
  - Edit profile
  - Change password
  - Delete account

- 📞 **Contact Management**
  - Add, view, edit, and delete contacts
  - Store name, phone, email, address, and description
  - All data is stored securely in a MySQL database

- 📧 **Email Sending**
  - Send emails to one or multiple contacts directly from the application
  - Email sending is handled via an integrated **Flask API** that connects to **Google SMTP**

---

## 🏗️ Technology Stack

| Component         | Technology                  |
| ----------------- | --------------------------- |
| Frontend (GUI)    | Qt Framework (C++)          |
| Backend Logic     | C++ with OOP Design         |
| Database          | MySQL                       |
| Email Service     | Flask (Python) + Gmail SMTP |
| API Communication | HTTP (Qt to Flask)          |

---


## 📡 Email Sending Architecture
- The Qt C++ app sends a POST request to a Flask API.
- The Flask API handles email dispatch using Google SMTP.
- You can send to individual or multiple contacts with a single request.

## Flask API (Conceptual Overview)
Route: POST `/sendMail`
- Body includes:
  - sender email and credentials
  - list of recipient emails
  - subject and body content
  - Email sending is handled outside the main Qt application for better separation of concerns and easier debugging.

## Project SetUp:
- clone the repo
```bash
https://github.com/mrehanamjad/Smart-Contact-Manager-Qt-Cpp-desktop-application.git

cd Smart-Contact-Manager-Qt-Cpp-desktop-application
```
- Qt C++ setup:
  - open QT Creator
  - import the project
  - configure the project settings (e.g., MySQL driver, Qt version, etc.)
  - build and run the project

- Email sending Api setup:
  ```
  cd Email Sending API FLASK Python
  ```
  - install requirements:
  ```bash
  pip install -r requirements.txt
  ```
  - run the Flask app:
  ```bash
  flask run
  ```
  - ensure the Flask app is running on the correct port (default is 5000)



## 🧰 Database Setup
```sql
-- Create database
CREATE DATABASE CMSDB;
USE CMSDB;

-- Users table
CREATE TABLE users (
    user_id VARCHAR(240) PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    password VARCHAR(1005) NOT NULL,
    email VARCHAR(255) NOT NULL UNIQUE,
    phone_number VARCHAR(20),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Contacts table
CREATE TABLE contacts (
    contact_id INT AUTO_INCREMENT PRIMARY KEY,
    user_id VARCHAR(40) NOT NULL,
    name VARCHAR(222) NOT NULL,
    phone VARCHAR(15) NOT NULL UNIQUE,
    email VARCHAR(60) NOT NULL UNIQUE,
    address VARCHAR(330),
    description VARCHAR(1999)
);

```

## 🔗 MySQL Connection (Qt C++)
In databasemanager.cpp:

```cpp
db.setHostName("localhost");
db.setPort(3306);
db.setDatabaseName("CMSDB");
db.setUserName("your_mysql_user");
db.setPassword("your_mysql_password");
// ✅ Replace with your actual credentials as per your environment.
```
