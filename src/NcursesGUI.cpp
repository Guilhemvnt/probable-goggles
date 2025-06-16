/*
** probable-goggles
** File description:
** NcursesGUI
*/

#include "NcursesGUI.hpp"

NcursesGUI::NcursesGUI()
{
}

NcursesGUI::~NcursesGUI()
{
}

void NcursesGUI::init() 
{
    if (initscr() == nullptr) {
        // Handle initialization error
        throw std::runtime_error("Error initializing Ncurses");
    }

    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    if (start_color() == ERR) {
        endwin();
        throw std::runtime_error("Error initializing colors");
    }

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    windowPadding = 2;

}

void NcursesGUI::drawAscii(std::string ascii)
{
    mvprintw(1, 1, "%s", ascii.c_str());
}

int NcursesGUI::handleInput() 
{
    ch = getch();
    switch(ch) {
        case 'q':
            return 1;
        default:
            return 0;
    }
}

void NcursesGUI::update() 
{
}       

void NcursesGUI::clear() 
{
    erase();
}

void NcursesGUI::refresh() 
{
    ::refresh();
}

void NcursesGUI::close() 
{
    endwin();
}

void drawSquare()
{
    init_pair(2, COLOR_BLACK, COLOR_WHITE);  // Définir une paire de couleurs (fond blanc, texte noir)
    attron(COLOR_PAIR(2));  // Activer la paire de couleurs

    int height = 2;
    int width = 2;
    int start_y = 40;
    int start_x = 5;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            mvprintw(start_y + i, start_x + j, " ");  // Afficher un espace à la position spécifiée
        }
    }
    attroff(COLOR_PAIR(2));  // Désactiver la paire de couleurs
}

std::string NcursesGUI::readFile(const std::string &filePath) {
    std::ifstream file(filePath); // Open the file
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // Read the file into the buffer
    file.close(); // Close the file
    return buffer.str(); // Return the buffer content as a string
}

void NcursesGUI::draw() 
{
    clear();
    mvprintw(1, 1, "Welcome to probable-goggles a RPG GUI for D&D games ! ");
    mvprintw(2, 1, "Q to quit");
    mvprintw(3, 1, "------------------------------------------------------------------------------------------------------");
    drawAscii(readFile("asciiArt/profil.txt"));
    refresh();
}

void NcursesGUI::drawBlock(Block block) {
    // Obtenez les coordonnées du bloc
    int x = block.getPos()[0];
    int y = block.getPos()[1];

    // Définissez la taille du bloc
    int width = block.getSize()[0];
    int height = block.getSize()[1];

    // Définissez la couleur de la bordure
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    wattron(stdscr, COLOR_PAIR(1));

    // Dessinez la bordure du carré
    for (int i = 0; i < width; ++i) {
        mvwaddch(stdscr, y, x + i, ACS_HLINE); // Dessinez la ligne supérieure
        mvwaddch(stdscr, y + height - 1, x + i, ACS_HLINE); // Dessinez la ligne inférieure
    }

    for (int i = 0; i < height; ++i) {
        mvwaddch(stdscr, y + i, x, ACS_VLINE); // Dessinez la colonne de gauche
        mvwaddch(stdscr, y + i, x + width - 1, ACS_VLINE); // Dessinez la colonne de droite
    }

    // Dessinez les coins du carré
    mvwaddch(stdscr, y, x, ACS_ULCORNER); // Coin supérieur gauche
    mvwaddch(stdscr, y, x + width - 1, ACS_URCORNER); // Coin supérieur droit
    mvwaddch(stdscr, y + height - 1, x, ACS_LLCORNER); // Coin inférieur gauche
    mvwaddch(stdscr, y + height - 1, x + width - 1, ACS_LRCORNER); // Coin inférieur droit

    wattroff(stdscr, COLOR_PAIR(1));
}

void NcursesGUI::drawBlocks(std::vector<Block>& arrayBlocks) {
    for (size_t i = 0; i < arrayBlocks.size(); ++i) {
        drawBlock(arrayBlocks[i]);
        drawContent(arrayBlocks[i]);
    }
}

void NcursesGUI::drawContent(Block block)
{
    int x = block.getPos()[0];
    int y = block.getPos()[1];

    int contentX = x + 1;
    int contentY = y + 1;

    int i = 0;
    //attacks blocks
    std::map<std::string, std::string> content = block.getContent();

    for (const auto &key : displayOrder) {
        if (content.find(key) == content.end())
            continue;
        auto value = content[key];

        mvprintw(contentY, contentX, "%s", key.c_str());

        if (std::atoi(value.c_str()) > 100 && key == "NB of packets")
            attron(COLOR_PAIR(3));
        mvprintw(contentY, contentX + key.size() + 1, "%s", value.c_str());
        attron(COLOR_PAIR(1));
        contentY++;
    }

    //device block
    for (const auto& entry : arrayBlocks[0].getContent()) {
        mvprintw(arrayBlocks[0].getPos()[1] + i + 1, arrayBlocks[0].getPos()[0] + 1, "%s", entry.second.c_str());
        i ++;
    };
}
