import json
from dateutil.parser import parse
from datetime import datetime
import twitter

consumer_key = "XXXXXX"
consumer_secret = "XXXXXX"
access_token =  "XXXXX"
access_token_secret = "XXXXXX"

api = twitter.Api(consumer_key=consumer_key,
                      consumer_secret=consumer_secret,
                      access_token_key=access_token,
                      access_token_secret=access_token_secret)


with open('sunrise_sunset.json') as json_data:
    d = json.load(json_data)

    sunrise = d["results"]["sunrise"]
    sunset = d["results"]["sunset"]

    parsed_sunrise = parse(sunrise)
    parsed_sunset = parse(sunset)
    time_now = datetime.now()

    print(parsed_sunrise < time_now)
    print(parsed_sunset > time_now)

    # if daytime
    if(parsed_sunrise < time_now and parsed_sunset > time_now):
       status = "GARDEN latest - "+str(time_now)
       fileObj  = open("results.txt", "r")
       last_bit = fileObj.readlines()[-10:]
       ll = " (humidity: "
       found = {}
       for line in last_bit:
          l =  line.rstrip()
          a = l.split("/") 
          if(len(a) > 2):
            n = a[1]
            v = a[2].split("\t")[0].rstrip()
            print n
            print v
            if(n in found):
              print("found ")
            else:
              found[n] = v
       foo = "unknown"
       if(len(found) > 0):
          foo = ', '.join(['%s: %s' % (key, value) for (key, value) in found.items()])
       ll = ll+foo+")"
       status = status + ll
       print("status: ")
       print(status)
       print("verifying twitter creds") 
       print(api.VerifyCredentials())
       file = open('/home/pi/camera/last_picture.jpg', 'rb')
       status = api.PostUpdate(status = status, media = file)

    else:
      print("nighttime!")
