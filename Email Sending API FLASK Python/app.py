from flask import Flask, jsonify, request
import smtplib as s

app = Flask(__name__)

def sendMail(sender_email, sender_password, subject, body, listRecipients):
    try:
        ob = s.SMTP('smtp.gmail.com', 587)
        ob.ehlo()
        ob.starttls()
        ob.login(sender_email, sender_password)

        message = f"Subject: {subject}\n\n{body}"

        for receiver in listRecipients:
            ob.sendmail(sender_email, receiver, message)

        ob.quit()
        return {"status": "success", "message": "Emails sent successfully"}
    except Exception as e:
        return {"status": "error", "message": str(e)}

@app.route("/", methods=["GET"])
def home():
    return jsonify({"message": "Welcome to the Email Sending API!"})

@app.route("/sendMail", methods=["POST"])
def send_mail():
    mail_data = request.json

    required_fields = ["sender_email", "sender_password", "subject", "body", "listRecipients"]
    for field in required_fields:
        if field not in mail_data:
            return jsonify({"error": f"Missing field: {field}"}), 400

    sender_email = mail_data["sender_email"]
    sender_password = mail_data["sender_password"]
    subject = mail_data["subject"]
    body = mail_data["body"]
    listRecipients = mail_data["listRecipients"]

    if not isinstance(listRecipients, list) or not listRecipients:
        return jsonify({"error": "listRecipients must be a non-empty list of email addresses"}), 400

    result = sendMail(sender_email, sender_password, subject, body, listRecipients)
    return jsonify(result)

if __name__ == "__main__":
    app.run(debug=True)


#  .venv\Scripts\activate