# 2D Driving Game with Arduino

A driving game with a top perspective. 
Simple setup, 3-4 lanes. The player controls the car. Main goal, dodge all obstacles and collect bonus items.

-  **Accelerometer:** The car steers left or right.

-  **Light sensor:** 
    - *option 1:* we change invert the colors (day and night mode). 
    - *option 2:* turn on the car lights. 
                  (e.g.: to warn human obstacles, if we hit them after turning on the lights we lose 1 point, otherwise 5 points)

-  **Microphone (sound sensor):** yell at others. A bit like the macho car-fight. If an other driver yells at you, you have to yell at him, etc. If you are the one to yell during most time, you win the duel and the opponent diver gets lost.

-  **Button:** you shoot an aid missile (you have only 3). The missile interacts with the next object in a straight line in front of the car and blows it (in case it is a human, it does some other shit and saves them). It is an ultimate resource for the situations where you can’t use lights or shift to an other lane to avoid an obstacle.

-  **Joystick:**  any idea?
