/*
** probable-goggles
** File description:
** NcursesGUI
*/


#ifndef NCURSESGUI_HPP_
    #define NCURSESGUI_HPP_

    #include <ncurses.h>
    #include <string>
    #include "IGUI.hpp"
    #include "Block.hpp"
    #include <vector>
    #include "FactoryBlock.hpp"
    #include <stdexcept>
    #include <fstream>
    #include <sstream>
    #include <iostream>

    class NcursesGUI : public virtual IGUI {
        private:
            std::vector<Block> arrayBlocks;
            void drawBlock(Block);
            void drawBlocks(std::vector<Block> &);
            void drawContent(Block);
            std::string readFile(const std::string &filePath);
            void drawAscii(std::string);
            FactoryBlock factoryBlock = FactoryBlock();
            std::vector<std::string> displayOrder = {"Type:", "Victim:", "From", "NB of packets"};
            int windowPadding;
            int ch;
        public:
            NcursesGUI();
            ~NcursesGUI();

            void init();
            void draw();
            int handleInput();
            void update();
            void clear();
            void refresh();
            void close();
    };

#endif /* !NCURSESGUI_HPP_ */
