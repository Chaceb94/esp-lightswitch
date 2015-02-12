The code in these files is to reside on your pi or another server.

I have my ESP broadcasting on port 19252. 'ds18b20/read-n-chart.py' listens on all ip port 19252 for just a number.
Then it adds a timestamp before writing it to temps.log. The second part reads said file and uses pygal to create a
line graph which gets put in 'www/images/temp_graph.svg'.

UPDATE: Now instead of using 'read-n-chart.py' to chart the temps, you can use 'read-n'send.py' to send the data
over to Thingpeak.com. Be sure to update line 14 with your own api key. I know it's a stupid process having raspi as a middleman,
but I don't know any other way. Someday I'll figure out how to make the ESP do it instead.

All the files in 'www' can be put into your webroot folder. The 'index.html' is real simple and just displays the svg with a title and a stylesheet.
