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

| Player                                   | Language   | Rounds |     1 |     2 |     3 |     4 |     5 |     6 |     7 |     8 |     9 |    10 |    11 |    12 |    13 |    14 |
|:---------------------------------------- |:---------- | ------:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:|
| [MontePlayer][16]                        | C++        |     14 |  1199 |  1098 |  1055 |   905 |   817 |   755 |   649 |   560 |   453 |   364 |   255 |   198 |   109 |    82 |
| [StudiousPlayer][12]                     | C++        |     13 |  1117 |  1047 |   930 |   875 |   787 |   680 |   590 |   532 |   451 |   340 |   235 |   150 |   104 |    18 |
| [CBetaPlayer][15]                        | C++        |     12 |   721 |   672 |   601 |   549 |   480 |   463 |   403 |   347 |   270 |   250 |   201 |   137 |    87 |
| [FatedPlayer][14]                        | C++        |     11 |   638 |   601 |   553 |   516 |   446 |   372 |   362 |   319 |   274 |   215 |   165 |   115 |
| [BarricadePlayer][7]                     | C++        |     10 |   597 |   639 |   549 |   514 |   474 |   419 |   370 |   305 |   262 |   176 |   144 |
| [BotRobotPlayer][8]                      | C++        |      9 |   498 |   509 |   403 |   375 |   358 |   331 |   325 |   246 |   243 |   155 |
| [SadisticShooter][10]                    | C++        |      8 |   888 |   786 |   696 |   592 |   496 |   397 |   299 |   199 |   147 |
| [SurvivorPlayer][13]                     | C++        |      7 |   741 |   617 |   602 |   551 |   464 |   378 |   271 |   171 |
| [TurtlePlayer][6]                        | C++        |      6 |   680 |   581 |   515 |   447 |   367 |   300 |   221 |
| [CamtoPlayer][17]                        | C++        |      5 |   736 |   594 |   538 |   426 |   357 |   291 |
| [HanSoloPlayer][18]                      | C++        |      4 |   619 |   553 |   460 |   432 |   330 |
| [GunClubPlayer][4]                       | C++        |      3 |   492 |   482 |   410 |   299 |
| [DeceptivePlayer][11]                    | C++        |      2 |   477 |   435 |   370 |
| [PlasmaPlayer][9]                        | C++        |      1 |   412 |   319 |
| [OpportunistPlayer][5]                   | C++        |      0 |   411 |

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
