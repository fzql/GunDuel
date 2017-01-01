# GunDuel

Futuristic Gun Duel Tournament at [Programming Puzzles & Code Golf at Stack Exchange][1]

## C++ Submissions

Please :

 - Post your submission as an answer to the PPCG.SE post.
 - Fork this project and request your files to be pulled.

## Python Submissions

Edit `PythonPlayer\<architecture>\PythonPlayer.py` to test your submission.

 - You can save state files, which are subject to removal at the beginning of a tournament.
 - Your script is called once per turn.
 - Commandline interface may change before Jan. 7, 2017.

## Other Submissions

Language Allowed: Java.

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

05:11 AM Sunday, January 1, 2016 Coordinated Universal Time (UTC)

| Player                                   | Language   | Survival  | Round  1 | Round  2 | Round  3 | Round  4 | Round  5 | Round  6 | Round  7 | Round  8 | Round  9 | Round 10 | Round 11 | Round 12 | Round 13 | Round 14 | Round 15 |
|:---------------------------------------- |:---------- | ---------:| --------:| --------:| --------:| --------:| --------:| --------:| --------:| --------:| --------:| --------:| --------:| --------:| --------:| --------:| --------:|
| [MontePlayer][16]                        | C++        | 14 rounds |     1201 |     1115 |     1063 |      936 |      839 |      724 |      660 |      557 |      475 |      356 |      224 |      174 |      112 |       53 |
| [CBetaPlayer][15]                        | C++        | 13 rounds |      719 |      700 |      618 |      574 |      511 |      453 |      409 |      361 |      284 |      228 |      214 |      157 |      110 |       47 |
| [StudiousPlayer][12]                     | C++        | 12 rounds |     1085 |     1058 |      958 |      854 |      803 |      703 |      620 |      528 |      415 |      319 |      233 |      153 |       78 |
| [FatedPlayer][14]                        | C++        | 11 rounds |      625 |      547 |      530 |      496 |      449 |      391 |      363 |      292 |      282 |      242 |      202 |      116 |
| [BarricadePlayer][7]                     | C++        | 10 rounds |      618 |      561 |      513 |      464 |      465 |      422 |      348 |      295 |      230 |      199 |      127 |
| [BotRobotPlayer][8]                      | C++        |  9 rounds |      507 |      407 |      359 |      373 |      368 |      354 |      281 |      289 |      249 |      156 |
| [SadisticShooter][10]                    | C++        |  8 rounds |      886 |      782 |      687 |      590 |      494 |      407 |      290 |      249 |      165 |
| [HanSoloPlayer][18]                      | C++        |  7 rounds |      668 |      567 |      494 |      392 |      330 |      283 |      258 |      229 |
| [SurvivorPlayer][13]                     | C++        |  6 rounds |      710 |      707 |      660 |      557 |      463 |      376 |      249 |
| [TurtlePlayer][6]                        | C++        |  5 rounds |      669 |      631 |      539 |      460 |      346 |      270 |
| [CamtoPlayer][17]                        | C++        |  4 rounds |      718 |      628 |      535 |      448 |      319 |
| [OpportunistPlayer][5]                   | C++        |  3 rounds |      441 |      414 |      332 |      235 |
| [GunClubPlayer][4]                       | C++        |  2 rounds |      497 |      383 |      300 |
| [DeceptivePlayer][11]                    | C++        |  1 round  |      477 |      380 |
| [PlasmaPlayer][9]                        | C++        |  0 rounds |      420 |

Disqualified Players (Honorable Mentions)

 - [BlackHatPlayer][2] (Locates and modifies [vtable][3] of rival entries)

 [1]: http://codegolf.stackexchange.com/q/104896/11933
 [2]: http://codegolf.stackexchange.com/a/105061/11933
 [3]: https://en.wikipedia.org/wiki/Vtable
 [4]: http://codegolf.stackexchange.com/a/104899/11933
 [5]: http://codegolf.stackexchange.com/a/104902/11933
 [6]: http://codegolf.stackexchange.com/a/104905/11933
 [7]: http://codegolf.stackexchange.com/a/104909/11933
 [8]: http://codegolf.stackexchange.com/a/104910/11933
 [9]: http://codegolf.stackexchange.com/a/104933/11933
 [10]: http://codegolf.stackexchange.com/a/104947/11933
 [11]: http://codegolf.stackexchange.com/a/104972/11933
 [12]: http://codegolf.stackexchange.com/a/105066/11933
 [13]: http://codegolf.stackexchange.com/a/105084/11933
 [14]: http://codegolf.stackexchange.com/a/105131/11933
 [15]: http://codegolf.stackexchange.com/a/105154/11933
 [16]: http://codegolf.stackexchange.com/a/105175/11933
 [17]: http://codegolf.stackexchange.com/a/105224/11933
 [18]: http://codegolf.stackexchange.com/a/105263/11933
