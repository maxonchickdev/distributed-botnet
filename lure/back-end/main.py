"""
main config
"""

from fastapi import FastAPI
from openai import OpenAI
from subprocess import run
from dotenv import load_dotenv
from os import environ

app = FastAPI()
client = OpenAI(
	api_key=environ.get("OPENAI_API_KEY")
)
load_dotenv()

@app.get('/sub')
def popup_endpoint():
	ip_addr = run(['ifconfig'], capture_output=True, text=True).stdout
	root_username = run(['whoami'], capture_output=True, text=True).stdout
	with open('secret_info.txt', 'w') as file:
		file.write(ip_addr)
		file.write(root_username)

	return {'data': '200'}

@app.get('/generate-image')
def generate_image_endpoint():
	response = client.chat.completions.create(
	model="tts-1-hd",
	messages=[
		{"role": "system", "content": "You are a helpful assistant."},
		{"role": "user", "content": "Who won the world series in 2020?"},
		{"role": "assistant", "content": "The Los Angeles Dodgers won the World Series in 2020."},
		{"role": "user", "content": "Where was it played?"}
	]
	)

	return {'data': response}
