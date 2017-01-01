// HanSoloPlayer.hpp
// A reluctant rebel. Always shoots first.

// Revision 1: [13HanSoloPlayer][17] | 6 rounds | 2863

#ifndef __HAN_SOLO_PLAYER_HPP__
#define __HAN_SOLO_PLAYER_HPP__

#include "Player.hpp"

class HanSoloPlayer final: public Player
{
public:
    HanSoloPlayer(size_t opponent = -1) : Player(opponent) {}

public:
    virtual Action fight()
    {
        if(getTurn() == 0){
            // let's do some initial work
            agenda.push_back(bullet());     // action 2--han shot first!
            agenda.push_back(load());       // action 1--load a shot
        } else if(getTurn() == 2){
            randomDefensive();
        } else if(getRandomBool(2)){
            // go on the defensive about 1/3rd of the time
            randomDefensive();
        } else if(getRandomBool(5)){
            // all-out attack!
            if(getAmmo() == 0){
                // do nothing, let the agenda work its course
            } else if(getAmmo() == 1){
                // not quite all-out... :/
                agenda.push_back(load());   // overnext
                agenda.push_back(bullet()); // next
            } else if(getAmmo() == 2){
                agenda.push_back(load());   // overnext
                agenda.push_back(plasma()); // next
            } else {
                int ammoCopy = getAmmo();
                while(ammoCopy >= 2){
                    agenda.push_back(plasma());
                    ammoCopy -= 2;
                }
            }
        }
        
        // execute the next item on the agenda
        if(agenda.size() > 0){
            Action nextAction = agenda.back();
            agenda.pop_back();
            return nextAction;
        } else {
            agenda.push_back(getRandomBool() ? thermal() : bullet()); // overnext
            agenda.push_back(load());                                 // next
            return load();
        }
    }
private:
    std::vector<Action> agenda;
    bool getRandomBool(int weight = 1){
        return GetRandomInteger(weight) == 0;
    }
    void randomDefensive(){
        switch(getAmmoOpponent()){
            case 0:
                // they most likely loaded and fired. load, then metal shield
                agenda.push_back(metal());  // action 4
                agenda.push_back(load());   // action 3
                break;
            case 1:
                agenda.push_back(metal());
                break;
            case 2:
                agenda.push_back(getRandomBool() ? thermal() : metal());
                break;
            default:
                agenda.push_back(getRandomBool(2) ? metal() : thermal());
                break;
        }
        return;
    }
};

#endif // !__HAN_SOLO_PLAYER_HPP__