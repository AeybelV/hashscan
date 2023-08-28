import hashlib

f = open("test/words.txt","r")

for line in f:
    md5hash = hashlib.sha256(line.encode('ascii'))
    print(md5hash.hexdigest())

