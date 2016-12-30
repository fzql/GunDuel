# GunDuel

Futuristic Gun Duel Tournament at [Programming Puzzles & Code Golf at Stack Exchange][1]

## C++ Submissions

Please :

 - Post your submission as an answer to the PPCG.SE post.
 - Fork this project and request your files to be pulled.

## Non C++ Submissions

Language Allowed: Python 3, Java.

Executables Allowed.

Command Line and Return Code Requirements

    Expected Command Line Argument Format:
    	<opponent-id> <turn> <status> <ammo> <ammo-opponent> <history> <history-opponent>

    Expected Return Code: The ascii value of a valid action character.
    	'0' = 48, '1' = 49, '2' = 50, '-' = 45, '=' = 61
    
    Player identifier is an integer in [0, N), where N is size of tournament.
    Turn is 0-based.
    If duel is in progress, status is 3.
    If duel is draw / won / lost, status is 0 / 1 / 2.
    If turn is 0, <history> and <history-opponent> are not provided.
    Histories are strings of actions, e.g. 002 0-=
    You can ignore arguments you don't particularly need.

The binaries will be added to the repository if they meet the requirements and does no harm to any computer.

 [1]: http://codegolf.stackexchange.com/q/104896/11933

## Current Standing (a random run)

06:24:07 UTC, Friday, 30 December 2016

| Player                | Survival | Points|
|:--------------------- | --------:| -----:|
| StudiousPlayer        | 8 rounds |  3246 |
| SadisticShooterPlayer | 7 rounds |  1678 |
| BotRobotPlayer        | 6 rounds |  1611 |
| BarricadePlayer       | 5 rounds |  1497 |
| TurtlePlayer          | 4 rounds |  1277 |
| GunClubPlayer         | 3 rounds |   931 |
| OpportunistPlayer     | 2 rounds |   727 |
| DeceptivePlayer       | 1 rounds |   489 | 
| PlasmaPlayer          | 0 rounds |   244 |
