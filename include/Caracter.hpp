/*
** probable-goggles
** File description:
** Caracter
*/

#include <string>
#include <map>

#ifndef CARACTER_HPP_
    #define CARACTER_HPP_
    class Caracter {        
        public:
            std::string name;
            std::string race;
            std::string class_role;
            int level;
            int xp:
            std::map<std::string, int> skills;
            Caracter();
            ~Caracter();
    };
#endif /* CARACTER_HPP_ */
