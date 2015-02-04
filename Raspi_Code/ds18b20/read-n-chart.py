import datetime
import socket
import pygal

UDP_IP = "0.0.0.0"
UDP_PORT = 19252

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

def graph_points():

    graph = pygal.Line()
    temp_list = []
    hum_list = []
    date_list = []
    short_date_list = []

    values = open('temps.log', 'r')
    for line in values:
        split_line = line.split(' ')
        date = split_line[0]
        time = split_line[1]
        temp = float( split_line[2] )
        temp_list.append(temp)
        date_list.append(time)
    values.close()

    len_date_list = len(date_list)
    gap_val = len_date_list / 10

    i = 0	
    while i < len_date_list:
        short_date_list.append(date_list[i])
        i = i + gap_val

    graph.x_labels = short_date_list
    graph.add('Temperature', temp_list)	# Add some values
    graph.title = 'Temperature / Time'
    graph.render_to_file('www/images/temp_graph.svg')	# Save the svg to a file

while True:
    # Grab incoming data from ESP via UDP
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes

    print >> open('temps.log', 'a'), datetime.datetime.now().strftime("%Y-%m-%d %H:%M"), data
    print datetime.datetime.now().strftime("%Y-%m-%d %H:%M\t") + data + ' F'
    graph_points()
