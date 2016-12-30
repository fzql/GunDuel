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

## Current Standing (update upon new submission)

06:24:07 UTC, Friday, 30 December 2016

| Player                     | Language | Survival | Points |
|:-------------------------- |:-------- | --------:| ------:|
| [StudiousPlayer][12]       | C++      | 8 rounds |   3246 |
| [SadisticShooterPlayer][8] | C++      | 7 rounds |   1678 |
| [BotRobotPlayer][6]        | C++      | 6 rounds |   1611 |
| [BarricadePlayer][5]       | C++      | 5 rounds |   1497 |
| [TurtlePlayer][4]          | C++      | 4 rounds |   1277 |
| [GunClubPlayer][2]         | C++      | 3 rounds |    931 |
| [OpportunistPlayer][3]     | C++      | 2 rounds |    727 |
| [DeceptivePlayer][9]       | C++      | 1 rounds |    489 | 
| [PlasmaPlayer][7]          | C++      | 0 rounds |    244 |

Disqualified Players (Honorable Mentions)

 - [BlackHatPlayer][10] (Locates and modifies [vtable][11] of rival entries)

 [1]: http://codegolf.stackexchange.com/q/104896/11933
 [2]: http://codegolf.stackexchange.com/a/104899/11933
 [3]: http://codegolf.stackexchange.com/a/104902/11933
 [4]: http://codegolf.stackexchange.com/a/104905/11933
 [5]: http://codegolf.stackexchange.com/a/104909/11933
 [6]: http://codegolf.stackexchange.com/a/104910/11933
 [7]: http://codegolf.stackexchange.com/a/104933/11933
 [8]: http://codegolf.stackexchange.com/a/104947/11933
 [9]: http://codegolf.stackexchange.com/a/104972/11933
 [10]: http://codegolf.stackexchange.com/a/105061/11933
 [11]: https://en.wikipedia.org/wiki/Vtable
 [12]: http://codegolf.stackexchange.com/a/105066/11933