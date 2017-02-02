# GunDuel

This repository corresponds to the Futuristic Gun Duel Tournament organized at [Programming Puzzles & Code Golf at Stack Exchange][1]. The tournament ended on Thu, 02 Feb 2017 07:56:36 GMT.

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

## Tournament Standing

Thu, 02 Feb 2017 08:02:23 GMT

| Player                                   | Language   | Points |     1 |     2 |     3 |     4 |     5 |     6 |     7 |     8 |     9 |    10 |    11 |    12 |    13 |    14 |    15 |    16 |
|:---------------------------------------- |:---------- | ------:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:| -----:|
| [MontePlayer][16]                        | C++        |  11413 |  1415 |  1326 |  1247 |  1106 |  1049 |   942 |   845 |   754 |   685 |   555 |   482 |   381 |   287 |   163 |   115 |    61 |
| [CBetaPlayer][15]                        | C++        |   7014 |   855 |   755 |   706 |   683 |   611 |   593 |   513 |   470 |   414 |   371 |   309 |   251 |   192 |   143 |   109 |    39 |
| [StudiousPlayer][12]                     | C++        |  10014 |  1324 |  1233 |  1125 |  1015 |   907 |   843 |   763 |   635 |   555 |   478 |   403 |   300 |   201 |   156 |    76 |
| [FatedPlayer][14]                        | C++        |   6222 |   745 |   683 |   621 |   655 |   605 |   508 |   494 |   456 |   395 |   317 |   241 |   197 |   167 |   138 |
| [HanSoloPlayer][18]                      | C++        |   5524 |   748 |   668 |   584 |   523 |   490 |   477 |   455 |   403 |   335 |   293 |   209 |   186 |   153 |
| [SurvivorPlayer][13]                     | C++        |   5384 |   769 |   790 |   667 |   574 |   465 |   402 |   354 |   338 |   294 |   290 |   256 |   185 |
| [SpecificPlayer][19]                     | C++        |   5316 |   845 |   752 |   669 |   559 |   488 |   427 |   387 |   386 |   340 |   263 |   200 |
| [DeceptivePlayer][11]                    | C++        |   4187 |   559 |   445 |   464 |   474 |   462 |   442 |   438 |   369 |   301 |   233 |
| [NotSoPatientPlayer][20]                 | C++        |   5105 |   931 |   832 |   742 |   626 |   515 |   469 |   352 |   357 |   281 |
| [BarricadePlayer][7]                     | C++        |   4171 |   661 |   677 |   614 |   567 |   527 |   415 |   378 |   332 |
| [BotRobotPlayer][8]                      | C++        |   3381 |   607 |   510 |   523 |   499 |   496 |   425 |   321 |
| [SadisticShooter][10]                    | C++        |   3826 |   905 |   780 |   686 |   590 |   475 |   390 |
| [TurtlePlayer][6]                        | C++        |   3047 |   754 |   722 |   608 |   539 |   424 |
| [CamtoPlayer][17]                        | C++        |   2308 |   725 |   641 |   537 |   405 |
| [OpportunistPlayer][5]                   | C++        |   1173 |   426 |   420 |   327 |
| [GunClubPlayer][4]                       | C++        |    888 |   500 |   388 |
| [PlasmaPlayer][9]                        | C++        |    399 |   399 |

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
 [19]: http://codegolf.stackexchange.com/a/107499/11933
 [20]: http://codegolf.stackexchange.com/a/108836/11933