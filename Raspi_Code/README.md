The code in these files is to reside on your pi or another server.

I have my ESP broadcasting on port 19252. 'ds18b20/read-n-chart.py' listens on all ip port 19252 for just a number.
Then it adds a timestamp before writing it to temps.log. The second part reads said file and uses pygal to create a
line graph which gets put in 'www/images/temp_graph.svg'.

All the files in 'www' can be put into your webroot folder. The 'index.html' is real simple and just displays the svg with a title and a stylesheet.
