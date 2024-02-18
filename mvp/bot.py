"""
bot configuration
"""


import os
import sys
import requests
from dotenv import load_dotenv
from pydantic import BaseModel

load_dotenv()


class Bot(BaseModel):
	id: int
	name: str
	description: str


class CreateBot(Bot):
	def __init__(self, id: int, name: str, description: str):
		super().__init__(id=id, name=name, description=description)

	# def connect_to_master(self, endpoint: str, path_to_master: str = os.environ["PATH_TO_MASTER"]):
	# 	bot = {"id": self.id, "name": self.name, "description": self.description}
	# 	r = requests.post(path_to_master + endpoint, json=bot)
	# 	return r.status_code

	def get_request(self, path_to_destination: str = os.environ["PATH_TO_DESTINATION"]):
		get_request = requests.get(path_to_destination)
		return {"request_status": get_request.status_code, "request_data": get_request.text}
