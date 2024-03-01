import requests

r = requests.get("http://localhost:8080/url-to-bot/")

print(r.text)
