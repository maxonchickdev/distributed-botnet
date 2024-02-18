"""
master configuration
"""


import os
from fastapi import FastAPI
from bot import CreateBot
from typing import List


app = FastAPI()

bot_list = []


@app.get('/get-all')
def get_all_bots_endpoint():
	return bot_list


@app.post('/connect')
def connect_bot_endpoint(bot: CreateBot):
	bot.id = len(bot_list)
	for i in bot_list:
		if i.id == bot.id:
			return {'message': 'Bot with this id is already added'}
	bot_list.append(bot)
	return {'message': 'Bot added correctly'}


@app.delete('/delete')
def delete_bot_endpoint(bot_id: int):
	for i in bot_list:
		if i.id == bot_id:
			bot_list.remove(i)
			return {'message': 'Bot deleted'}
	return {'message': 'Bot with this ID not found'}


@app.get('/destination-get')
def get_from_destination(bot_id: int):
    for bot in bot_list:
        if bot.id == bot_id:
            request = bot.get_request()
            return {
                'data': {
                    'bot': {
                        'bot_name': bot.name,
                        'bot_description': bot.description
                    },
                    'request': {
                        'request_status_code': request['request_status'],
                        'request_data': request['request_data']
                    }
                }
            }
    return {'message': 'Bot with this ID not found'}
