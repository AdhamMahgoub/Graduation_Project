import requests
import time

def get_url_content(url):
    response = requests.get(url)
    return response.text


while True:
	url = "http://192.168.4.1/temperature"
	content = get_url_content(url)
	print(content)
	print("Fetching content...")
	#time.sleep(0.5)  # delay for 0.5 seconds
