import random

f = open("test/words.txt","r")

email_domains =  [
    "gmail.com",
    "yahoo.com",
    "outlook.com",
    "proton.me",
    "aol.com",
    "icloud.com",
    "hotmail.com",
]
for line in f:
    print(line.rstrip() + "@" + random.choice(email_domains))

