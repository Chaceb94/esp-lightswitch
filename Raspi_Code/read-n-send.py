import datetime
import socket
import httplib, urllib

UDP_IP = "0.0.0.0"
UDP_PORT = 19252

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

def send_point(temp):
    
  params = urllib.urlencode({'field1': temp, 'key':'YOUR API KEY'})     # use your API key generated in the thingspeak channels for the value of 'key'
  # temp is the data you will be sending to the thingspeak channel for plotting the graph. You can add more than one channel and plot more graphs
  headers = {"Content-typZZe": "application/x-www-form-urlencoded","Accept": "text/plain"}
  conn = httplib.HTTPConnection("api.thingspeak.com:80")                
  try:
    conn.request("POST", "/update", params, headers)
    response = conn.getresponse()
    print temp
    print response.status, response.reason
    dta = response.read()
    conn.close()
  except:
    print "connection failed"

while True:
  # Grab incoming data from ESP via UDP
  data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
  print 'data was revieved:' + data
  send_point(data)

