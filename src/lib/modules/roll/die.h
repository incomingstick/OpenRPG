/*
roll - die.h
Created on: Jan 8, 2017

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/

#ifndef SRC_DIE_H_
#define SRC_DIE_H_

class Die {
    private:
        const int MAX;
    public:
        Die();
        Die(int max);
        ~Die();
        int roll();
};

#endif /* SRC_DIE_H_ */
