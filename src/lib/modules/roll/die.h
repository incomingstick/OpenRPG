/*
roll - die.h
Created on: Nov 10, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
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