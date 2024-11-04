# One Time Passcode Challenge

For this challenge, a server is open on port 3000 and you must find the flag from the server.

You are not allowed to look into the src folder, but you may look at a copy of server.c that is in the root directory of this repo. This copy of server.c doesn't contain the real flag, but everything else is the same.

Since we cannot go into the src folder, we will be running the server through a docker-compose, which should allow us to run the code with minimal risk to spoilers.

```
$ cd OneTimePasscodeChallenge
$ docker-compose up --build -d
```
