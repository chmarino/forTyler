import requests
from bs4 import BeautifulSoup
import webbrowser
import time
import smtplib
from email.mime.text import MIMEText

url1 = 'https://www.bestbuy.com/site/nintendo-switch-32gb-console-gray-joy-con/6364253.p?skuId=6364253'
url2 = 'https://www.bestbuy.com/site/nintendo-switch-32gb-console-neon-red-neon-blue-joy-con/6364255.p?skuId=6364255'
headers = {
    'User-agent': 'PythonTest'
}

def sendmail(url):
    sender = 'pythonemailforswitch@gmail.com'
    receiver = 'christopher.r.marino@gmail.com'
    msg = MIMEText(url)
    msg['From'] = sender
    msg['To'] = receiver
    msg['Subject'] = 'SWITCH AVAILABLE!!!!'

    smtp_server_name = 'smtp.gmail.com'
    port = '587'

    if port == '465':
        server = smtplib.SMTP_SSL('{}:{}'.format(smtp_server_name, port))
    else :
        server = smtplib.SMTP('{}:{}'.format(smtp_server_name, port))
        server.starttls()

    server.login(sender, "SneakyTyler")
    server.send_message(msg)
    server.quit()

while True:
    r1 = requests.get(url1, headers=headers)
    r2 = requests.get(url2, headers=headers)

    soup1 = BeautifulSoup(r1.content, 'html.parser')
    soup2 = BeautifulSoup(r2.content, 'html.parser')

    button_container1 = soup1.find_all('div', class_ = 'fulfillment-add-to-cart-button')
    button_container2 = soup2.find_all('div', class_ = 'fulfillment-add-to-cart-button')

    for i in button_container1:
        if i.text == 'Add to Cart':
            webbrowser.open(url1)
            sendmail(url1)
            quit()
    for j in button_container2:
        if j.text == 'Add to Cart':
            webbrowser.open(url2)
            sendmail(url2)
            quit()

    time.sleep(5)
