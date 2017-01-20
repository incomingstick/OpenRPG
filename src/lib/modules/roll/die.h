/*
roll - die.cpp
Created on: Nov 10, 2016

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_DIE_H_
#define SRC_GENERATOR_H_

class Die {
    private:
        int MAX = 6;
    public:
        Die();
        Die(int max);
        ~Die();
        int roll();
        int roll(int max);
};

#endif /* SRC_DIE_H_ */