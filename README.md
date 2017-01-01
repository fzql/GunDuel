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

| Player                                   | Language   | Survival  | R#  1 | R#  2 | R#  3 | R#  4 | R#  5 | R#  6 | R#  7 | R#  8 | R#  9 | R# 10 | R# 11 | R# 12 | R# 13 | R# 14 |
|:---------------------------------------- |:---------- | ---------:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:|
| [MontePlayer][16]                        | C++        | 14 rounds |  1235 |  1115 |   997 |   919 |   829 |   740 |   656 |   560 |   469 |   350 |   248 |   196 |   108 |    53 |
| [StudiousPlayer][12]                     | C++        | 13 rounds |  1117 |   995 |   918 |   794 |   742 |   652 |   559 |   463 |   380 |   293 |   214 |   137 |   115 |    47 |
| [CBetaPlayer][15]                        | C++        | 12 rounds |   694 |   656 |   632 |   545 |   478 |   465 |   400 |   341 |   302 |   249 |   200 |   142 |    77 |
| [FatedPlayer][14]                        | C++        | 11 rounds |   634 |   562 |   548 |   505 |   452 |   408 |   372 |   322 |   283 |   232 |   195 |   125 |
| [BarricadePlayer][7]                     | C++        | 10 rounds |   631 |   574 |   534 |   516 |   475 |   425 |   349 |   318 |   233 |   188 |   143 |
| [HanSoloPlayer][18]                      | C++        |  9 rounds |   620 |   565 |   496 |   466 |   397 |   331 |   303 |   267 |   252 |   188 |
| [BotRobotPlayer][8]                      | C++        |  8 rounds |   506 |   407 |   395 |   405 |   361 |   355 |   283 |   292 |   181 |
| [SadisticShooter][10]                    | C++        |  7 rounds |   879 |   764 |   675 |   599 |   511 |   387 |   296 |   237 |
| [SurvivorPlayer][13]                     | C++        |  6 rounds |   736 |   720 |   632 |   504 |   455 |   370 |   265 |
| [TurtlePlayer][6]                        | C++        |  5 rounds |   672 |   665 |   546 |   455 |   347 |   258 |
| [CamtoPlayer][17]                        | C++        |  4 rounds |   724 |   629 |   507 |   427 |   335 |
| [DeceptivePlayer][11]                    | C++        |  3 rounds |   448 |   412 |   388 |   354 |
| [OpportunistPlayer][5]                   | C++        |  2 rounds |   429 |   429 |   317 |
| [GunClubPlayer][4]                       | C++        |  1 round  |   502 |   394 |
| [PlasmaPlayer][9]                        | C++        |  0 rounds |   408 |
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
