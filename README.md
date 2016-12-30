# GunDuel

Futuristic Gun Duel Tournament at [Programming Puzzles & Code Golf at Stack Exchange][1]

## C++ Submissions

Please post your submission as an answer to the PPCG.SE post. If it meets the rules, your submission will be added to the repository, at which point you can commit on your own files.

## Wrapper for external .exe binary

To make sure that your non-C++ player can communicate with the tournament manager, please compile your binary which will follow the rules in this snippet:

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

    06:24:07 UTC
    Friday, 30 December 2016

    StudiousPlayer         survived   8 rounds with 3246 total points.
    SadisticShooterPlayer  survived   7 rounds with 1678 total points.
    BotRobotPlayer         survived   6 rounds with 1611 total points.
    BarricadePlayer        survived   5 rounds with 1497 total points.
    TurtlePlayer           survived   4 rounds with 1277 total points.
    GunClubPlayer          survived   3 rounds with 931 total points.
    OpportunistPlayer      survived   2 rounds with 727 total points.
    DeceptivePlayer        survived   1 rounds with 489 total points.
    PlasmaPlayer           survived   0 rounds with 244 total points.

 :: Press Enter to Quit...